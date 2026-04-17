# Paths
ROOT_PATH := ..
# VM Lib
GC_LIB_ARTIFACTS_PATH := $(ROOT_PATH)/artifacts
GC_LIB_PATH := $(GC_LIB_ARTIFACTS_PATH)/lib_x
GC_SRC_PATH := $(ROOT_PATH)/src
# Examples
EXAMPLES_PATH := $(ROOT_PATH)/examples
SRC_PATH := $(EXAMPLES_PATH)
EXAMPLE_BIN := $(EXAMPLES_PATH)/bin
OBJS_PATH := $(EXAMPLES_PATH)/objs

# Build Type
TARGET_NAME := gc_example
BUILD ?= release
DEBUG_EXT := _g

ifeq ($(BUILD),debug)
    CXXFLAGS := -std=c++17 -O0 -g -Wall -Werror -Wextra
    TARGET_SUFFIX := $(DEBUG_EXT)
else
    CXXFLAGS := -std=c++17 -O2 -Wall -Werror -Wextra
    TARGET_SUFFIX :=
endif


# Targets defines
TARGET := $(EXAMPLE_BIN)/$(TARGET_NAME)$(TARGET_SUFFIX)
OBJ_TARGET := $(OBJS_PATH)/%$(TARGET_SUFFIX).o

# SRCS
SRCS := $(wildcard $(SRC_PATH)/*.cpp)
# OBJS := $(SRCS:.cpp=.o)
OBJS := $(patsubst $(SRC_PATH)/%.cpp,$(OBJ_TARGET),$(SRCS))
DEPS := $(OBJS:.o=.d)


# Flags
CXX := g++
LFLAGS := -lpthread
INCLUDES := -I$(SRC_PATH) \
-I$(GC_SRC_PATH)

all: setup $(TARGET)

debug:
	$(MAKE) BUILD="debug"

$(TARGET): GC_LIB_TARGET $(OBJS) 
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) -L$(GC_LIB_PATH) -lGC$(TARGET_SUFFIX)

$(OBJ_TARGET): $(SRC_PATH)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCLUDES) -MP -MD

GC_LIB_TARGET:
	$(MAKE) -C $(GC_SRC_PATH) BUILD="$(BUILD)" -j

setup:
	mkdir -p $(EXAMPLE_BIN)
	mkdir -p $(OBJS_PATH)

run: all
	$(TARGET) --help

-include $(DEPS)

clean:
	rm -rf $(OBJS_PATH)/*.o $(OBJS_PATH)/*.d $(EXAMPLE_BIN)/*
