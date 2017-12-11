DYN_LIB_EXT := .so
BUILD_ROOT := Build-Linux
ifeq ($(OS),Windows_NT)
	DYN_LIB_EXT := .dll
	BUILD_ROOT := Cygwin
endif

CC = g++ -fdiagnostics-color=always
CC_LINK = g++ -shared -m64 -fPIC
CUL_PREPROCESOR_FLAGS := -D CULLib_EXPORT -D CUL_DYNAMIC
COMPILER_FLAGS = -pedantic -Wall -std=c++11 $(CUL_PREPROCESOR_FLAGS) -Wno-ignored-attributes -m64

EXPORT_ALL_SYMBOLS := -Wl,--export-all-symbols
ENABLE_AUTO_IMPORT := ""

DEBUG_FLAGS = -ggdb
RELEASE_FLAGS = -Ofast
PROJECT_NAME = libcul
IMP_LIB_NAME = $(PROJECT_NAME).a
DEPS_ROOT := ../deps
BOOST_ROOT := $(DEPS_ROOT)/boost_1_64_0
BOOST_INCLUDE := $(BOOST_ROOT)
BOOST_LIB_ROOT := Build-$(BUILD_ROOT)
BOOST_IMPORT_LIB := $(BOOST_ROOT)/$(BOOST_LIB_ROOT)/libboost_filesystem-mt.a  $(BOOST_ROOT)/$(BOOST_LIB_ROOT)/libboost_system-mt.a

OUTPUT_DIR := ../build
OUTPUT_DIR_DEBUG = $(OUTPUT_DIR)/$(BUILD_ROOT)_Debug
OUTPUT_DIR_RELEASE = $(OUTPUT_DIR)/$(BUILD_ROOT)_Release

HEADER_INC = -I . -I $(BOOST_ROOT)

IMPORT_LIBS_DEBUG = $(BOOST_IMPORT_LIB)
IMPORT_LIBS_RELEASE = $(BOOST_IMPORT_LIB)
IMP_LIB_DEBUG = $(OUTPUT_DIR_DEBUG)/$(IMP_LIB_NAME)
IMP_LIB_RELEASE = $(OUTPUT_DIR_RELEASE)/$(IMP_LIB_NAME)

CPP_FILES := $(wildcard */*.cpp)

# OBJ:
OBJ_DEBUG_DIR := $(OUTPUT_DIR_DEBUG)/intermediate_$(PROJECT_NAME)/
OBJ_RELEASE_DIR := $(OUTPUT_DIR_RELEASE)/intermediate_$(PROJECT_NAME)/
OBJ_DEBUG_FILES := $(addprefix $(OBJ_DEBUG_DIR),$(CPP_FILES:.cpp=.o))
OBJ_RELEASE_FILES := $(addprefix $(OBJ_RELEASE_DIR),$(CPP_FILES:.cpp=.o))

DLL_NAME = $(PROJECT_NAME)$(DYN_LIB_EXT)

debug: $(OUTPUT_DIR_DEBUG)/$(DLL_NAME)
release: $(OUTPUT_DIR_RELEASE)/$(DLL_NAME)

$(OUTPUT_DIR_DEBUG)/$(DLL_NAME): $(OBJ_DEBUG_FILES) $(OUTPUT_DIR_DEBUG)
	$(CC_LINK) -o $(OUTPUT_DIR_DEBUG)/$(DLL_NAME) $(OBJ_DEBUG_FILES) $(DEBUG_FLAGS) $(IMPORT_LIBS_DEBUG) \
	-Wl,--out-implib,$(OUTPUT_DIR_DEBUG)/$(IMP_LIB_NAME) 

$(OUTPUT_DIR_RELEASE)/$(DLL_NAME): $(OBJ_RELEASE_FILES) $(OUTPUT_DIR_RELEASE)
	$(CC_LINK) -o $(OUTPUT_DIR_RELEASE)/$(DLL_NAME) $(OBJ_RELEASE_FILES) $(RELEASE_FLAGS) $(IMPORT_LIBS_RELEASE) \
	-Wl,--out-implib,$(OUTPUT_DIR_RELEASE)/$(IMP_LIB_NAME)

$(OUTPUT_DIR_DEBUG):
	@mkdir -p $@

$(OUTPUT_DIR_RELEASE):
	@mkdir -p $@

$(OBJ_DEBUG_DIR)%.o: %.cpp
	mkdir -p $(dir $@)
	$(CC) $(HEADER_INC) $(COMPILER_FLAGS) $(DEBUG_FLAGS) -c -o $@ $<

$(OBJ_RELEASE_DIR)%.o: %.cpp
	mkdir -p $(dir $@)
	$(CC) $(HEADER_INC) $(COMPILER_FLAGS) $(RELEASE_FLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ_DEBUG_FILES)
	rm -f $(OBJ_RELEASE_FILES)
	rm -f $(OUTPUT_DEBUG)
	rm -f $(OUTPUT_RELEASE)

test:
	@echo "All .o files: $(OBJ_DEBUG_FILES)"
	@echo "All .cpp files: $(CPP_FILES)"
	@echo "BOOST_ROOT: $(BOOST_ROOT)"

help:
	echo "If run first time, please run \"make first_run\" it will create necessary dirs."
