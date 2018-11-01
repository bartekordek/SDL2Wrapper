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
CC_STAND := -std=c++17
CC := g++ $(CC_STAND) $(ARCH_FLAG) $(DIAG_FLAG) -fPIC
CC_LINK := g++ $(CC_STAND) $(ARCH_FLAG) $(DIAG_FLAG) -shared
COMPILER_FLAGS := -pedantic -Wall -Wno-ignored-attributes
DEBUG_FLAGS = -ggdb
RELEASE_FLAGS = -Ofast
PROJECT_NAME = libsdl2wrapper
IMP_LIB_NAME = $(PROJECT_NAME).a
OUTPUT_DIR := ../build
OUTPUT_DIR_DEBUG = $(OUTPUT_DIR)/Debug
OUTPUT_DIR_RELEASE = $(OUTPUT_DIR)/Release

# DEPS
DEPS_HOME := ../deps
# DEPS::CUL
CUL_HOME := $(DEPS_HOME)/CUL
CUL_INC := $(CUL_HOME)/libcul/inc
CUL_LIB := $(CUL_HOME)/build
CUL_LIB_DEBUG := $(CUL_LIB)/Debug/libcul.so
CUL_LIB_RELEASE := $(CUL_LIB)/Release/libcul.so

# DEPS::SDL2
SDL_HOME := $(DEPS_HOME)/SDL2-2.0.8
SDL_INC := $(SDL_HOME)/include
SDL_LIB := $(SDL_HOME)/$(BUILD_ROOT)/$(PLATFORM)
SDL_LIB_FILES := $(SDL_LIB)/libSDL2.a $(SDL_LIB)/libSDL2main.a
SDL_LIB_IMPORT := $(SDL_LIB)/libSDL2-2.0.so.0.7.0

# DEPS::SDL2::image
SDL_IMAGE_HOME := $(DEPS_HOME)/SDL2_image-2.0.3
SDL_IMAGE_INC := $(SDL_IMAGE_HOME)/include
SDL_IMAGE_LIB := $(SDL_IMAGE_HOME)/Build-Linux
SDL_IMAGE_LIB_FILES := $(SDL_IMAGE_LIB)/libSDL2_image.a
SDL_IMAGE_LIB_IMPORT := $(SDL_IMAGE_LIB)/libSDL2_image-2.0.so.0.2.1

# DEPS::BOOST
HOME_BOOST := $(CUL_HOME)/deps/boost_1_67_0

HEADERS_INC := -I inc
HEADERS_INC += -I src
HEADERS_INC += -I $(CUL_INC)
HEADERS_INC += -I $(SDL_INC)
HEADERS_INC += -I $(SDL_IMAGE_INC)
HEADERS_INC += -I $(HOME_BOOST)

IMPORT_FILES := $(SDL_LIB_FILES)
IMPORT_FILES += $(SDL_IMAGE_LIB_FILES)

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

ifeq ($(OS),Windows_NT)
    DYN_LIB_EXT = .dll
else
    DYN_LIB_EXT = .so
endif

DLL_NAME = $(PROJECT_NAME)$(DYN_LIB_EXT)

debug: $(OUTPUT_DEBUG)
release: $(OUTPUT_RELEASE)

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
