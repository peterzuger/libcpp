TARGET_NAME ?= libcpp
VERBOSE     ?=
DEBUG       ?=
LIBCDIR   =../libc

ARCH        ?=
SYS         ?= none
CPU         ?=
FPU         ?= auto

EXCEPTIONS ?=
RTTI       ?=
THREADING  ?=

BUILD       ?= build
TARGET = $(BUILD)/$(TARGET_NAME).a

#
CXXSRC += $(wildcard src/exception/*.cpp)
CXXSRC += $(wildcard src/memory/*.cpp)
CXXSRC += $(wildcard src/new/*.cpp)
CXXSRC += $(wildcard src/typeinfo/*.cpp)

OBJECTS  = $(patsubst %.c,$(BUILD)/%.o,$(CSRC))
OBJECTS += $(patsubst %.cpp,$(BUILD)/%.o,$(CXXSRC))

DEPENDENCIES  = $(patsubst %.c,$(BUILD)/%.d,$(CSRC))
DEPENDENCIES += $(patsubst %.cpp,$(BUILD)/%.d,$(CXXSRC))

# Commands
ifeq ($(VERBOSE),1)
	Q =
	RM = rm --verbose
	RMDIR = rmdir --verbose
	MKDIR = mkdir --verbose
else
	Q = @
	RM = @rm
	RMDIR = @rmdir
	MKDIR = @mkdir
endif

ifeq ($(DEBUG),1)
	DBGFLAGS = -g3
else
	DBGFLAGS =
endif

ifeq ($(ARCH),arm)
CC_VAR = arm-none-eabi-
else ifeq ($(ARCH),thumb)
CC_VAR = arm-none-eabi-
else ifeq ($(ARCH),x86_64)
CC_VAR =
else
$(error Unknown ARCH)
endif

CC   = $(Q)$(CC_VAR)gcc
GCC  = $(Q)$(CC_VAR)gcc
GXX  = $(Q)$(CC_VAR)g++
CPP  = $(Q)$(CC_VAR)gcc --preprocess
AR   = $(Q)$(CC_VAR)ar
AS   = $(Q)$(CC_VAR)as

ECHO = @echo -e

# Flags
OPTFLAGS += -O3 -ffunction-sections -fdata-sections $(DBGFLAGS)
IFLAGS   += -Iinclude -I$(LIBCDIR)/include
WFLAGS   += -Wall -Wextra -Wpedantic -Wduplicated-cond -Wduplicated-branches
WFLAGS   += -Wlogical-op -Wnull-dereference -Wshadow -Wformat=2
WFLAGS   += -Wdouble-promotion -Winit-self -Wswitch-default -Wswitch-enum
WFLAGS   += -Wunsafe-loop-optimizations -Wundef -Wconversion -Winline
WFLAGS   += -Waddress
CWFLAGS  += -Wjump-misses-init
ifeq ($(DEBUG),1)
	WFLAGS += -Wsuggest-attribute=pure -Wsuggest-attribute=noreturn
endif

ifeq ($(ARCH),thumb)
ARCHFLAGS += -mthumb -mcpu=$(CPU) -mfpu=$(FPU)
else ifeq ($(ARCH),arm)
ARCHFLAGS += -marm -mcpu=$(CPU) -mfpu=$(FPU)
else ifeq ($(ARCH),x86_64)
ifneq ($(CPU),)
ARCHFLAGS += -mtune=$(CPU)
endif
endif

COMFLAGS += $(WFLAGS) $(OPTFLAGS) $(IFLAGS) $(ARCHFLAGS) -static -ffreestanding
COMFLAGS += -nostartfiles -nostdlib -nostdinc -fno-tree-loop-distribute-patterns -fno-stack-protector

GCCFLAGS = $(COMFLAGS) $(CWFLAGS) -c
CXXFLAGS = $(COMFLAGS) -c -std=c++17
ASFLAGS  = $(COMFLAGS) -c
ARFLAGS  =

ifeq ($(EXCEPTIONS), 1)
	CXXFLAGS +=
else
	CXXFLAGS += -fno-exceptions
endif

ifeq ($(RTTI), 1)
	CXXFLAGS +=
else
	CXXFLAGS += -fno-rtti
endif

ifeq ($(THREADING), 1)
	CXXFLAGS +=
else
	CXXFLAGS += -fno-threadsafe-statics
endif

# Targets
all: $(TARGET)

$(BUILD)/%.o: %.c
	$(ECHO) "GCC\t$@"
	$(MKDIR) --parents ${dir $@}
	$(GCC) $(GCCFLAGS) -MD -MF $(@:.o=.d) $< -o $@

$(BUILD)/%.o: %.cpp
	$(ECHO) "G++\t$@"
	$(MKDIR) --parents ${dir $@}
	$(GXX) $(CXXFLAGS) -MD -MF $(@:.o=.d) $< -o $@

-include $(DEPENDENCIES)

$(TARGET): $(OBJECTS)
	$(ECHO) "AR\t$@"
	$(AR) $(ARFLAGS) rcs $@ $^

.PHONY: clean
clean:
	$(RM) -f $(OBJECTS) $(DEPENDENCIES) $(TARGET)
	$(Q)find $(BUILD) -type d -empty -delete || true
