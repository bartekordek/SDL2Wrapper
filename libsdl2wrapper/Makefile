ARCH := $(shell getconf LONG_BIT)
ifeq ($(OS),Windows_NT)
DYN_LIB_EXT := .dll
BUILD_ROOT := Build-Cygwin
else
DYN_LIB_EXT := .so
BUILD_ROOT := Build-Linux
endif

ARCH_FLAG := -m32
PLATFORM := x86
ifeq ($(ARCH),64)
ARCH_FLAG := -m64
PLATFORM := x64
endif

DIAG_FLAG := -fdiagnostics-color=always
#COMPILER := g++
COMPILER := clang++-6.0
CPP_VERSION := -std=c++17
CC := $(COMPILER) $(CPP_VERSION) $(ARCH_FLAG) $(DIAG_FLAG) \
-fPIC -pedantic -Wall
CC_LINK := $(COMPILER) $(CPP_VERSION) $(ARCH_FLAG) $(DIAG_FLAG) -shared -fPIC

DEBUG_FLAGS = -ggdb
RELEASE_FLAGS = -Ofast
PROJECT_NAME = libsdl2wrapper
IMP_LIB_NAME = $(PROJECT_NAME).a
DLL_NAME = $(PROJECT_NAME)$(DYN_LIB_EXT)
OUTPUT_DIR := ../$(BUILD_ROOT)
OUTPUT_DIR_DEBUG = $(OUTPUT_DIR)/Debug
OUTPUT_DIR_RELEASE = $(OUTPUT_DIR)/Release

# DEPS
DEPS_HOME := ../deps


# DEPS::CUL
CUL_HOME := $(DEPS_HOME)/CUL
CUL_INC := $(CUL_HOME)/libcul/inc
CUL_LIB := $(CUL_HOME)/$(BUILD_ROOT)
CUL_LIB_DEBUG := $(CUL_LIB)/Debug/libcul.so
CUL_LIB_RELEASE := $(CUL_LIB)/Release/libcul.so

# HEADERS
HEADERS_INC := -I inc
HEADERS_INC += -I src
HEADERS_INC += -I $(CUL_INC)
HEADERS_INC += $(shell pkg-config --cflags sdl2)
HEADERS_INC += $(shell pkg-config --cflags SDL2_image)
HEADERS_INC += -I $(HOME_BOOST)

IMPORT_FILES := $(SDL_LIB_FILES)
IMPORT_FILES += $(SDL_IMAGE_LIB_FILES)
IMPORT_FILES += $(shell pkg-config --libs sdl2)
IMPORT_FILES += $(shell pkg-config --libs SDL2_image)

OUTPUT_DEBUG = $(OUTPUT_DIR_DEBUG)/$(DLL_NAME)
OUTPUT_RELEASE = $(OUTPUT_DIR_RELEASE)/$(DLL_NAME)
IMP_LIB_DEBUG = $(OUTPUT_DIR_DEBUG)/$(IMP_LIB_NAME)
IMP_LIB_RELEASE = $(OUTPUT_DIR_RELEASE)/$(IMP_LIB_NAME)

IMPORT_LIBS_DEBUG := $(SDL_LIB_IMPORT) $(SDL_IMAGE_LIB_IMPORT) -pthread
IMPORT_LIBS_RELEASE := $(SDL_LIB_IMPORT) $(SDL_IMAGE_LIB_IMPORT) -pthread

CPP_FILES := $(wildcard src/*.cpp)
CPP_FILES += $(wildcard src/*/*.cpp)

OBJ_DEBUG_DIR := obj/debug/
OBJ_DEBUG_FILES := $(addprefix $(OBJ_DEBUG_DIR),$(CPP_FILES:.cpp=.o))

OBJ_RELEASE_DIR := obj/release/
OBJ_RELEASE_FILES := $(addprefix $(OBJ_RELEASE_DIR),$(CPP_FILES:.cpp=.o))

debug:
	$(MAKE) $(CUL_LIB_DEBUG)
	$(MAKE) $(OUTPUT_DEBUG)

release:
	$(MAKE) $(CUL_LIB_RELEASE)
	$(MAKE) $(OUTPUT_RELEASE)

$(CUL_LIB_DEBUG):
	$(MAKE) -C $(CUL_HOME)/libcul

$(CUL_LIB_RELEASE):
	$(MAKE) -C $(CUL_HOME)/libcul

$(OUTPUT_DEBUG): $(OBJ_DEBUG_FILES)
	@mkdir -p $(dir $@)
	$(CC_LINK) -o $@ $(OBJ_DEBUG_FILES) $(DEBUG_FLAGS) $(IMPORT_LIBS_DEBUG) $(IMPORT_FILES)

$(OUTPUT_RELEASE): $(OBJ_RELEASE_FILES)
	@mkdir -p $(dir $@)
	$(CC_LINK) -o $@ $(OBJ_RELEASE_FILES) $(RELEASE_FLAGS) $(IMPORT_LIBS_RELEASE) $(IMPORT_FILES)

$(OBJ_DEBUG_DIR)%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(HEADERS_INC) $(COMPILER_FLAGS) $(DEBUG_FLAGS) -c -o $@ $<

$(OBJ_RELEASE_DIR)%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(HEADERS_INC) $(COMPILER_FLAGS) $(RELEASE_FLAGS) -c -o $@ $<

clean:
	$(MAKE) -C $(CUL_HOME)/libcul clean
	rm -f $(OBJ_DEBUG_FILES)
	rm -f $(OBJ_RELEASE_FILES)
	rm -f $(OUTPUT_DEBUG)
	rm -f $(OUTPUT_RELEASE)
	find . -name '*.o' | xargs rm -fv

test:
	@echo "All .o files: $(OBJ_DEBUG_FILES)"
	@echo "All .cpp files: $(CPP_FILES)"
	@echo "SDL2: $(HOME_SDL2_LINUX)/"

help:
	echo "If run first time, please run \"make first_run\" it will create necessary dirs."
