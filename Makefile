PROJECT = myproject
BUILD_DIR = build

# source files
CFILES = \
src/main.c \
freertos/croutine.c \
freertos/event_groups.c \
freertos/heap_3.c \
freertos/list.c \
freertos/port.c \
freertos/queue.c \
freertos/stream_buffer.c \
freertos/tasks.c \
freertos/timers.c 


INCLUDES += -Iinclude -Ifreertos/include

# extra path to look for source files
#VPATH += $(some shared dir)

# device parameters
DEVICE=stm32f103c8
OOCD_TARGET=stm32f1x
OOCD_INTERFACE=stlink

# extra libraries to link if required
#LDLIBS += -lm -u _printf_float

# opencm3 directory
OPENCM3_DIR=libopencm3

### DON'T TOUCH
include $(OPENCM3_DIR)/mk/genlink-config.mk
include rules.mk
include $(OPENCM3_DIR)/mk/genlink-rules.mk