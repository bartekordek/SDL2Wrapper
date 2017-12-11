DYN_LIB_EXT := .so
BUILD_ROOT := Build-Linux
ifeq ($(OS),Windows_NT)
	DYN_LIB_EXT := .dll
	BUILD_ROOT := Cygwin
endif

CC := g++ -fdiagnostics-color=always -no-pie
CC_LINK := g++ -m64
CUL_PREPROCESOR_FLAGS := -D CULLib_EXPORT -D CUL_DYNAMIC
COMPILER_FLAGS = -pedantic -Wall -std=gnu++11 $(CUL_PREPROCESOR_FLAGS) -Wno-ignored-attributes -m64
DEBUG_FLAGS = -ggdb
RELEASE_FLAGS = -Ofast
PROJECT_NAME = Tests
BINARY_NAME = $(PROJECT_NAME).exe 
OUTPUT_DIR := ../build
OUTPUT_DIR_DEBUG = $(OUTPUT_DIR)/$(BUILD_ROOT)_Debug
OUTPUT_DIR_RELEASE = $(OUTPUT_DIR)/$(BUILD_ROOT)_Release

DEPS_ROOT := ../deps
GTEST_ROOT := $(DEPS_ROOT)/gtest
GTEST_INCLUDE := $(GTEST_ROOT)/googletest/include
GTEST_LIBRARY_DIR := $(GTEST_ROOT)/Build-$(BUILD_ROOT)

HEADER_INC := -I . -isystem $(GTEST_INCLUDE) -I ../CUL
IMPORT_LIBS_DEBUG := -L$(OUTPUT_DIR_DEBUG) -L$(GTEST_LIBRARY_DIR)
IMPORT_LIBS_RELEASE := -L$(OUTPUT_DIR_RELEASE) -L$(GTEST_LIBRARY_DIR)
IMPORT_LIBS_FILES := -lgtest -lgtest_main -lcul

CPP_FILES := $(wildcard */*.cpp)
CPP_FILES += $(wildcard *.cpp)

# OBJ:
OBJ_DEBUG_DIR := $(OUTPUT_DIR_DEBUG)/intermediate_$(PROJECT_NAME)/debug/
OBJ_RELEASE_DIR := $(OUTPUT_DIR_RELEASE)/intermediate_$(PROJECT_NAME)/release/
OBJ_DEBUG_FILES := $(addprefix $(OBJ_DEBUG_DIR),$(CPP_FILES:.cpp=.o))
OBJ_RELEASE_FILES := $(addprefix $(OBJ_RELEASE_DIR),$(CPP_FILES:.cpp=.o))

debug: $(OUTPUT_DIR_DEBUG)/$(BINARY_NAME)
release: $(OUTPUT_DIR_RELEASE)/$(BINARY_NAME)

run_debug: debug
	cd $(OUTPUT_DIR_DEBUG);./$(BINARY_NAME)

run_release: release
	cd $(OUTPUT_DIR_RELEASE);./$(BINARY_NAME)

$(OUTPUT_DIR_DEBUG)/$(BINARY_NAME): run_debug_deps $(OBJ_DEBUG_FILES) $(OUTPUT_DIR_DEBUG)
	$(CC_LINK) -o $(OUTPUT_DIR_DEBUG)/$(BINARY_NAME) $(OBJ_DEBUG_FILES) $(IMPORT_LIBS_DEBUG) $(IMPORT_LIBS_FILES)

$(OUTPUT_DIR_RELEASE)/$(BINARY_NAME): run_release_deps $(OBJ_RELEASE_FILES) $(OUTPUT_DIR_RELEASE)
	$(CC_LINK) -o $(OUTPUT_DIR_RELEASE)/$(BINARY_NAME) $(OBJ_RELEASE_FILES) $(IMPORT_LIBS_RELEASE) $(IMPORT_LIBS_FILES)

$(OUTPUT_DIR_DEBUG):
	mkdir -p $@

$(OUTPUT_DIR_RELEASE):
	mkdir -p $@

$(OBJ_DEBUG_DIR)%.o: %.cpp
	mkdir -p $(dir $@)
	$(CC) $(HEADER_INC) $(COMPILER_FLAGS) $(DEBUG_FLAGS) -c -o $@ $<

$(OBJ_RELEASE_DIR)%.o: %.cpp
	mkdir -p $(dir $@)
	$(CC) $(HEADER_INC) $(COMPILER_FLAGS) $(RELEASE_FLAGS) -c -o $@ $<

clean:
	make -C ../CUL clean
	rm -f $(OBJ_DEBUG_FILES)
	rm -f $(OBJ_RELEASE_FILES)
	rm -f $(OUTPUT_DEBUG)
	rm -f $(OUTPUT_RELEASE)

run_debug_deps:
	make -C ../CUL debug

run_release_deps:
	make -C ../CUL release

clear_all:
	find . -name '*.o' | xargs rm

test:
	@echo "All .o files: $(OBJ_DEBUG_FILES)"
	@echo "All .cpp files: $(CPP_FILES)" 

help:
	echo "If run first time, please run \"make first_run\" it will create necessary dirs."
