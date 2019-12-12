TARGET_NAME ?= libcpp
VERBOSE     ?=
DEBUG       ?=
LIBCDIR   =../libc

EXCEPTIONS ?=
RTTI       ?=
THREADING  ?=

ifeq ($(VERBOSE),1)
	Q =
else
	Q = @
endif

CXXSRC  = $(wildcard src/*.cpp)
CXXSRC += $(wildcard src/new/*.cpp)
CXXSRC += $(wildcard src/exception/*.cpp)

OBJECTS  = $(CSRC:.c=.o)
OBJECTS += $(CXXSRC:.cpp=.o)

CC   = arm-none-eabi-
GCC  = $(Q)$(CC)gcc
GXX  = $(Q)$(CC)g++
CPP  = $(Q)$(CC)gcc -E
AR   = $(Q)$(CC)ar
AS   = $(Q)$(CC)as
ECHO = @echo -e

ifeq ($(VERBOSE),1)
	RM = rm -v
else
	RM = @rm
endif

ifeq ($(DEBUG),1)
	DBGFLAGS = -g
else
	DBGFLAGS =
endif

DFLAGS   =
OPTFLAGS = -O2 -ffunction-sections -fdata-sections $(DBGFLAGS)
IFLAGS   = -Iinclude -I$(LIBCDIR)/include
WFLAGS   = -Wall -Wextra -Wpedantic -Wduplicated-cond -Wduplicated-branches
WFLAGS  += -Wlogical-op -Wnull-dereference -Wshadow
WFLAGS  += -Wdouble-promotion -Winit-self -Wswitch-default -Wswitch-enum
WFLAGS  += -Wunsafe-loop-optimizations -Wundef -Wconversion -Winline
WFLAGS  += -Waddress
CWFLAGS  = -Wjump-misses-init
COMFLAGS = $(WFLAGS) -static -mthumb -mcpu=$(CPU) $(FPU) -nostartfiles -nostdlib
COMFLAGS += $(OPTFLAGS) $(IFLAGS) $(DFLAGS)

GCCFLAGS = $(COMFLAGS) -c $(CWFLAGS)
CXXFLAGS = $(COMFLAGS) -c -std=c++17
CPPFLAGS =
ARFLAGS  =
ASFLAGS  =

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

all: $(TARGET_NAME).a

%.o: %.c
	$(ECHO) "GCC\t$@"
	$(GCC) $(GCCFLAGS) $< -o $@

%.o: %.cpp
	$(ECHO) "G++\t$@"
	$(GXX) $(CXXFLAGS) $< -o $@

$(TARGET_NAME).a: $(OBJECTS)
	$(RM) -f $@
	$(ECHO) "AR\t$@"
	$(AR)  $(ARFLAGS) rcs $@ $^

.PHONY: clean
clean:
	$(RM) -f $(OBJECTS)
	$(RM) -f $(TARGET_NAME).a
