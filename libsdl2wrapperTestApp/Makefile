ARCH := $(shell getconf LONG_BIT)
ifeq ($(OS),Windows_NT)
DYN_LIB_EXT := .dll
BUILD_ROOT := Build-Cygwin
else
DYN_LIB_EXT := .so
BUILD_ROOT := Build-Linux
endif

DIAG_FLAG := -fdiagnostics-color=always
COMPILER := g++
#COMPILER := clang++-6.0
CC_STAND := -std=c++17
CC := $(COMPILER) $(CC_STAND) $(DIAG_FLAG) -fPIC -pedantic -Wall -Wno-ignored-attributes
CC_LINK := $(COMPILER) $(CC_STAND) $(DIAG_FLAG)

DEBUG_FLAGS = -ggdb3
RELEASE_FLAGS = -Ofast
PROJECT_NAME = libsdl2wrapperTestApp
BINARY_NAME = $(PROJECT_NAME).exe
OUTPUT_DIR := ../$(BUILD_ROOT)
OUTPUT_DIR_DEBUG = $(OUTPUT_DIR)/Debug
OUTPUT_DIR_RELEASE = $(OUTPUT_DIR)/Release
RUN_DIR := ../runDir

# DEPS
DEPS_HOME := ../deps




# DEPS::CUL
CUL_HOME := $(DEPS_HOME)/CUL
CUL_INC := $(CUL_HOME)/libcul/inc
CUL_LIB := $(CUL_HOME)/$(BUILD_ROOT)
CUL_LIB_NAME := libcul.so
CUL_LIB_DEBUG := $(CUL_LIB)/Debug/$(CUL_LIB_NAME)
CUL_LIB_RELEASE := $(CUL_LIB)/Release/$(CUL_LIB_NAME)

# DEPS::SDL2Wrapper
SDL2W_HOME := ../libsdl2wrapper
SDL2W_INC := $(SDL2W_HOME)/inc
SDL2W_LIB := ../$(BUILD_ROOT)
SDL2W_LIB_NAME := libsdl2wrapper.so
SDL2W_LIB_DEBUG := $(SDL2W_LIB)/Debug/$(SDL2W_LIB_NAME)
SDL2W_LIB_RELEASE := $(SDL2W_LIB)/Release/$(SDL2W_LIB_NAME)

IMPORT_LIBS := -pthread
IMPORT_LIBS += $(shell pkg-config --libs IL)
IMPORT_LIBS += $(shell pkg-config --libs ILU)
IMPORT_LIBS += $(shell pkg-config --libs ILUT)
IMPORT_LIBS += $(shell pkg-config --libs libpng)
IMPORT_LIBS += $(shell pkg-config --libs sdl2)
IMPORT_LIBS_DEBUG := $(IMPORT_LIBS) $(CUL_LIB_DEBUG) $(SDL2W_LIB_DEBUG)
IMPORT_LIBS_RELEASE := $(IMPORT_LIBS) $(CUL_LIB_RELEASE) $(SDL2W_LIB_RELEASE)





CPP_FILES := $(wildcard *.cpp)

# OBJ:
OBJ_DEBUG_DIR := $(OUTPUT_DIR_DEBUG)/intermediate_$(PROJECT_NAME)/debug/
OBJ_RELEASE_DIR := $(OUTPUT_DIR_RELEASE)/intermediate_$(PROJECT_NAME)/release/
OBJ_DEBUG_FILES := $(addprefix $(OBJ_DEBUG_DIR),$(CPP_FILES:.cpp=.o))
OBJ_RELEASE_FILES := $(addprefix $(OBJ_RELEASE_DIR),$(CPP_FILES:.cpp=.o))

HEADERS_INC := -I $(CUL_INC) -I $(SDL2W_INC)

debug:
	$(MAKE) -C $(SDL2W_HOME) debug
	$(MAKE) $(OUTPUT_DIR_DEBUG)/$(BINARY_NAME)

release: $(SDL2W_LIB_RELEASE)
	$(MAKE) -C $(SDL2W_HOME) release
	$(MAKE) $(OUTPUT_DIR_RELEASE)/$(BINARY_NAME)

run_debug: debug
	cd $(RUN_DIR);LD_LIBRARY_PATH=$(RUN_DIR) ./$(OUTPUT_DIR_DEBUG)/$(BINARY_NAME)

run_release: release
	cd $(RUN_DIR);LD_LIBRARY_PATH=$(RUN_DIR) ./$(OUTPUT_DIR_RELEASE)/$(BINARY_NAME)

$(OUTPUT_DIR_DEBUG)/$(BINARY_NAME): $(OBJ_DEBUG_FILES) $(OUTPUT_DIR_DEBUG)
	@mkdir -p $(@D)
	$(CC_LINK) -o $(OUTPUT_DIR_DEBUG)/$(BINARY_NAME) $(OBJ_DEBUG_FILES) $(IMPORT_LIBS_DEBUG) $(IMPORT_LIBS_FILES)
	mkdir -p $(RUN_DIR)
	cp $(SDL2W_LIB_DEBUG) $(RUN_DIR)

$(OUTPUT_DIR_RELEASE)/$(BINARY_NAME): $(OBJ_RELEASE_FILES) $(OUTPUT_DIR_RELEASE)
	@mkdir -p $(@D)
	$(CC_LINK) -o $(OUTPUT_DIR_RELEASE)/$(BINARY_NAME) $(OBJ_RELEASE_FILES) $(IMPORT_LIBS_RELEASE) $(IMPORT_LIBS_FILES)
	mkdir -p $(RUN_DIR)
	cp $(SDL2W_LIB_RELEASE) $(RUN_DIR)

$(OUTPUT_DIR_DEBUG):
	mkdir -p $@

$(OUTPUT_DIR_RELEASE):
	mkdir -p $@

$(OBJ_DEBUG_DIR)%.o: %.cpp
	mkdir -p $(dir $@)
	$(CC) $(HEADERS_INC) $(COMPILER_FLAGS) $(DEBUG_FLAGS) -c -o $@ $<

$(OBJ_RELEASE_DIR)%.o: %.cpp
	mkdir -p $(dir $@)
	$(CC) $(HEADERS_INC) $(COMPILER_FLAGS) $(RELEASE_FLAGS) -c -o $@ $<

clean:
	$(MAKE) -C $(SDL2W_HOME) clean
	rm -rf $(OUTPUT_DIR)

clear_all:
	find . -name '*.o' | xargs rm

test:
	@echo "All .o files: $(OBJ_DEBUG_FILES)"
	@echo "All .cpp files: $(CPP_FILES)"
	@echo "ARCH: $(ARCH)"
help:
	echo "If run first time, please run \"make first_run\" it will create necessary dirs."
