LVGL_DIR_NAME ?= lvgl
LVGL_DIR ?= ${shell pwd}
include $(LVGL_DIR)/$(LVGL_DIR_NAME)/lvgl.mk

BIN = lvgl_demo_benchmark

CFLAGS += -O3 -I. -DLV_CONF_INCLUDE_SIMPLE

CSRCS += src/main.c lv_drivers/display/fbdev.c
OBJS := $(patsubst %.c, %.o, $(CSRCS))
TARGET 			= $(patsubst ./%, %, $(OBJS))


.PHONY: all clean

all: default

%.o: %.c lv_conf.h
	@$(CC)  $(CFLAGS) -c $< -o $@
	@echo "CC $<"

default: $(TARGET)
	$(CC) -o $(BIN) $(MAINOBJ) $(TARGET) $(LDFLAGS)

clean: 
	@echo "Cleaning ... "
	rm -f $(BIN) $(MAINOBJ) $(OBJS)

