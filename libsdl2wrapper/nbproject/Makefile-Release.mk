#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=Cygwin-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include SDL2Wrapper-Makefile.mk

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/IObject.o \
	${OBJECTDIR}/src/ISDL2Wrapper.o \
	${OBJECTDIR}/src/IWindow.o \
	${OBJECTDIR}/src/RegularSDL2Window.o \
	${OBJECTDIR}/src/SDL2Wrapper.o \
	${OBJECTDIR}/src/SDL2WrapperImpl.o \
	${OBJECTDIR}/src/Sprite.o \
	${OBJECTDIR}/src/TextureWrapper.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-pedantic -Ofast
CXXFLAGS=-pedantic -Ofast

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=../deps/SDL2-2.0.7/Build-Cygwin/libSDL2main.a ../deps/SDL2-2.0.7/Build-Cygwin/libSDL2.dll.a -L../deps/CUL/CUL/libcul/../../build/Cygwin-Windows-Debug -lcul -L../deps/CUL/CUL/libcul/../../build/Cygwin-Windows-Release -lcul

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../build/${CND_PLATFORM}-${CND_CONF}/libSDL2Wrapper.${CND_DLIB_EXT}
	${CP} ../deps/CUL/CUL/libcul/../../build/Cygwin-Windows-Debug/libcul.dll ../build/${CND_PLATFORM}-${CND_CONF}
	${CP} ../deps/CUL/CUL/libcul/../../build/Cygwin-Windows-Release/libcul.dll ../build/${CND_PLATFORM}-${CND_CONF}

../build/${CND_PLATFORM}-${CND_CONF}/libSDL2Wrapper.${CND_DLIB_EXT}: ../deps/SDL2-2.0.7/Build-Cygwin/libSDL2main.a

../build/${CND_PLATFORM}-${CND_CONF}/libSDL2Wrapper.${CND_DLIB_EXT}: ../deps/SDL2-2.0.7/Build-Cygwin/libSDL2.dll.a

../build/${CND_PLATFORM}-${CND_CONF}/libSDL2Wrapper.${CND_DLIB_EXT}: ../deps/CUL/CUL/libcul/../../build/Cygwin-Windows-Debug/libcul.dll

../build/${CND_PLATFORM}-${CND_CONF}/libSDL2Wrapper.${CND_DLIB_EXT}: ../deps/CUL/CUL/libcul/../../build/Cygwin-Windows-Release/libcul.dll

../build/${CND_PLATFORM}-${CND_CONF}/libSDL2Wrapper.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ../build/${CND_PLATFORM}-${CND_CONF}
	${LINK.cc} -o ../build/${CND_PLATFORM}-${CND_CONF}/libSDL2Wrapper.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -Wl,--out-implib,../build/${CND_PLATFORM}-${CND_CONF}/libSDL2Wrapper.a -shared

${OBJECTDIR}/src/IObject.o: src/IObject.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Werror -DSDL2Wrapper_DYNAMIC -Iinc -I../deps/CUL/CUL -I../deps/CUL/deps/boost_1_64_0 -I../deps/SDL2-2.0.7/include -std=c++14  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/IObject.o src/IObject.cpp

${OBJECTDIR}/src/ISDL2Wrapper.o: src/ISDL2Wrapper.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Werror -DSDL2Wrapper_DYNAMIC -Iinc -I../deps/CUL/CUL -I../deps/CUL/deps/boost_1_64_0 -I../deps/SDL2-2.0.7/include -std=c++14  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/ISDL2Wrapper.o src/ISDL2Wrapper.cpp

${OBJECTDIR}/src/IWindow.o: src/IWindow.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Werror -DSDL2Wrapper_DYNAMIC -Iinc -I../deps/CUL/CUL -I../deps/CUL/deps/boost_1_64_0 -I../deps/SDL2-2.0.7/include -std=c++14  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/IWindow.o src/IWindow.cpp

${OBJECTDIR}/src/RegularSDL2Window.o: src/RegularSDL2Window.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Werror -DSDL2Wrapper_DYNAMIC -Iinc -I../deps/CUL/CUL -I../deps/CUL/deps/boost_1_64_0 -I../deps/SDL2-2.0.7/include -std=c++14  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/RegularSDL2Window.o src/RegularSDL2Window.cpp

${OBJECTDIR}/src/SDL2Wrapper.o: src/SDL2Wrapper.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Werror -DSDL2Wrapper_DYNAMIC -Iinc -I../deps/CUL/CUL -I../deps/CUL/deps/boost_1_64_0 -I../deps/SDL2-2.0.7/include -std=c++14  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/SDL2Wrapper.o src/SDL2Wrapper.cpp

${OBJECTDIR}/src/SDL2WrapperImpl.o: src/SDL2WrapperImpl.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Werror -DSDL2Wrapper_DYNAMIC -Iinc -I../deps/CUL/CUL -I../deps/CUL/deps/boost_1_64_0 -I../deps/SDL2-2.0.7/include -std=c++14  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/SDL2WrapperImpl.o src/SDL2WrapperImpl.cpp

${OBJECTDIR}/src/Sprite.o: src/Sprite.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Werror -DSDL2Wrapper_DYNAMIC -Iinc -I../deps/CUL/CUL -I../deps/CUL/deps/boost_1_64_0 -I../deps/SDL2-2.0.7/include -std=c++14  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Sprite.o src/Sprite.cpp

${OBJECTDIR}/src/TextureWrapper.o: src/TextureWrapper.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Werror -DSDL2Wrapper_DYNAMIC -Iinc -I../deps/CUL/CUL -I../deps/CUL/deps/boost_1_64_0 -I../deps/SDL2-2.0.7/include -std=c++14  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/TextureWrapper.o src/TextureWrapper.cpp

# Subprojects
.build-subprojects:
	cd ../deps/CUL/CUL/libcul && ${MAKE} -j8 -f Makefile CONF=Debug
	cd ../deps/CUL/CUL/libcul && ${MAKE} -j8 -f Makefile CONF=Release

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} -r ../build/${CND_PLATFORM}-${CND_CONF}/libcul.dll ../build/${CND_PLATFORM}-${CND_CONF}/libcul.dll
	${RM} ../build/${CND_PLATFORM}-${CND_CONF}/libSDL2Wrapper.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:
	cd ../deps/CUL/CUL/libcul && ${MAKE} -j8 -f Makefile CONF=Debug clean
	cd ../deps/CUL/CUL/libcul && ${MAKE} -j8 -f Makefile CONF=Release clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
