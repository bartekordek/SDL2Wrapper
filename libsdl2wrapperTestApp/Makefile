ARCH := $(shell getconf LONG_BIT)
ifeq ($(OS),Windows_NT)
DYN_LIB_EXT := .dll
BUILD_ROOT := Cygwin
else
DYN_LIB_EXT := .so
BUILD_ROOT := Build-Linux
endif

ifeq ($(ARCH),64)
ARCH_FLAG := -m64
else
ARCH_FLAG := -m32
endif

DIAG_FLAG := -fdiagnostics-color=always
CC := g++ $(ARCH_FLAG) $(DIAG_FLAG)
CC_LINK := g++ $(ARCH_FLAG) $(DIAG_FLAG)
CUL_PREPROCESOR_FLAGS := -D CULLib_EXPORT -D CUL_DYNAMIC
COMPILER_FLAGS = -pedantic -Wall -std=gnu++11 $(CUL_PREPROCESOR_FLAGS) -Wno-ignored-attributes
DEBUG_FLAGS = -ggdb
RELEASE_FLAGS = -Ofast
PROJECT_NAME = Tests
BINARY_NAME = $(PROJECT_NAME).exe
OUTPUT_DIR := ../build
OUTPUT_DIR_DEBUG = $(OUTPUT_DIR)/Debug
OUTPUT_DIR_RELEASE = $(OUTPUT_DIR)/Release
RUN_DIR := ../runTests

DEPS_ROOT := ../deps
ROOT_LIBMOGE := ../libcul

HEADER_INC := -I . -isystem $(GTEST_INCLUDE) -I $(ROOT_LIBMOGE)/inc
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
	cd $(RUN_DIR);./$(OUTPUT_DIR_DEBUG)/$(BINARY_NAME)

run_release: release
	cd $(RUN_DIR);./$(OUTPUT_DIR_RELEASE)/$(BINARY_NAME)

$(OUTPUT_DIR_DEBUG)/$(BINARY_NAME): run_debug_deps $(OBJ_DEBUG_FILES) $(OUTPUT_DIR_DEBUG)
	@mkdir -p $(@D)
	$(CC_LINK) -o $(OUTPUT_DIR_DEBUG)/$(BINARY_NAME) $(OBJ_DEBUG_FILES) $(IMPORT_LIBS_DEBUG) $(IMPORT_LIBS_FILES)

$(OUTPUT_DIR_RELEASE)/$(BINARY_NAME): run_release_deps $(OBJ_RELEASE_FILES) $(OUTPUT_DIR_RELEASE)
	@mkdir -p $(@D)
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
	make -C $(ROOT_LIBMOGE) clean
	rm -f $(OBJ_DEBUG_FILES)
	rm -f $(OBJ_RELEASE_FILES)
	rm -f $(OUTPUT_DEBUG)
	rm -f $(OUTPUT_RELEASE)

run_debug_deps:
	make -C $(ROOT_LIBMOGE) debug

run_release_deps:
	make -C $(ROOT_LIBMOGE) release

clear_all:
	find . -name '*.o' | xargs rm

test:
	@echo "All .o files: $(OBJ_DEBUG_FILES)"
	@echo "All .cpp files: $(CPP_FILES)"
	@echo "ARCH: $(ARCH)"