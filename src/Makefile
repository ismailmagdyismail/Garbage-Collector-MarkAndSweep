# Paths
ROOT_PATH := ..
SRC_PATH := $(ROOT_PATH)/src
ARTIFACTS_PATH := $(ROOT_PATH)/artifacts
BIN_PATH := $(ARTIFACTS_PATH)/bin
OBJS_PATH := $(ARTIFACTS_PATH)/objs
LIB_PATH := $(ARTIFACTS_PATH)/lib_x

# Build Type
TARGET_NAME := GC
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
TARGET := $(BIN_PATH)/$(TARGET_NAME)$(TARGET_SUFFIX)
LIB_NAME := lib$(TARGET_NAME)$(TARGET_SUFFIX).a
LIB_TARGET := $(LIB_PATH)/$(LIB_NAME)
OBJ_TARGET := $(OBJS_PATH)/%$(TARGET_SUFFIX).o

# SRCS
SRCS := $(wildcard $(SRC_PATH)/*.cpp)
# OBJS := $(SRCS:.cpp=.o)
OBJS := $(patsubst $(SRC_PATH)/%.cpp,$(OBJ_TARGET),$(SRCS))
DEPS := $(OBJS:.o=.d)


# Flags
CXX := g++
LFLAGS := -lpthread
INCLUDES := -I$(SRC_PATH)

all: setup $(LIB_TARGET)

debug:
	$(MAKE) BUILD="debug"

$(LIB_TARGET): $(OBJS)
	ar rcs $@ $(OBJS)

$(OBJ_TARGET): $(SRC_PATH)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCLUDES) -MP -MD

setup:
	mkdir -p $(BIN_PATH)
	mkdir -p $(OBJS_PATH)
	mkdir -p $(LIB_PATH)

-include $(DEPS)

clean:
	rm -rf $(OBJS_PATH)/*.o $(OBJS_PATH)/*.d $(LIB_PATH)/*
