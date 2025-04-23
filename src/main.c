#include	<unistd.h>
#include	<time.h>
#include	<sys/time.h>
#include	<fcntl.h>
#include	<stdlib.h>
#include	<string.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<limits.h>
#include	<errno.h>
#include	<poll.h>
#include	<stdbool.h>
#include	<getopt.h>

#include	"lvgl/lvgl.h"
#include	"lvgl/demos/lv_demos.h"

/* ${SDKTARGETSYSROOT}/usr/include/lvgl/lv_drivers */
#include	"display/fbdev.h"

int main(int argc, char *argv[])
{
	/*LVGL init*/
	lv_init();

	fbdev_init();

	/*A static or global variable to store the buffers*/
	static lv_disp_draw_buf_t disp_buf;

	/*Static or global buffer(s). The second buffer is optional*/
	static lv_color_t buf_1[1920 * 1080];
	// static lv_color_t buf_2[MY_DISP_HOR_RES * 10];

	/*Initialize `disp_buf` with the buffer(s). With only one buffer use NULL instead buf_2 */
	lv_disp_draw_buf_init(&disp_buf, buf_1, NULL, 1920 * 1080);
	
	static lv_disp_drv_t disp_drv;          /*A variable to hold the drivers. Must be static or global.*/
	lv_disp_drv_init(&disp_drv);            /*Basic initialization*/
	disp_drv.draw_buf = &disp_buf;          /*Set an initialized buffer*/
	disp_drv.flush_cb = fbdev_flush;        /*Set a flush callback to draw to the display*/
	uint32_t wd, ht;
	fbdev_get_sizes(&wd, &ht, NULL);
	disp_drv.hor_res = wd;                 /*Set the horizontal resolution in pixels*/
	disp_drv.ver_res = ht;

	lv_disp_drv_register(&disp_drv);

	lv_demo_benchmark();

	while(1) {
		uint32_t del = lv_timer_handler();
		usleep(del * 1000);
	}

	return 1;
}

/**
 * Set in lv_conf.h as `LV_TICK_CUSTOM_SYS_TIME_EXPR`
 */
uint32_t custom_tick_get(void)
{
	static uint64_t start_ms = 0;
	struct timeval tv_start;
	struct timeval tv_now;
	uint64_t now_ms;

	if(start_ms == 0) {
		gettimeofday(&tv_start, NULL);
		start_ms = (tv_start.tv_sec * 1000000 + tv_start.tv_usec) / 1000;
	}
	gettimeofday(&tv_now, NULL);
	now_ms = (tv_now.tv_sec * 1000000 + tv_now.tv_usec) / 1000;

	return (uint32_t)(now_ms - start_ms);
}
