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
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=../build/Cygwin-Windows-Debug/libSDL2Wrapper.a ../deps/CUL/build/Cygwin-Windows-Debug/libcul.a ../deps/CUL/build/Cygwin-Windows-Debug/libcul.dll ../deps/SDL2-2.0.7/Build-Cygwin/SDL2.dll -L../SDL2Wrapper/../build/Cygwin-Windows-Debug -lSDL2Wrapper

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../build/${CND_PLATFORM}-${CND_CONF}/TestApp.exe

../build/${CND_PLATFORM}-${CND_CONF}/TestApp.exe: ../build/Cygwin-Windows-Debug/libSDL2Wrapper.a

../build/${CND_PLATFORM}-${CND_CONF}/TestApp.exe: ../deps/CUL/build/Cygwin-Windows-Debug/libcul.a

../build/${CND_PLATFORM}-${CND_CONF}/TestApp.exe: ../deps/CUL/build/Cygwin-Windows-Debug/libcul.dll

../build/${CND_PLATFORM}-${CND_CONF}/TestApp.exe: ../deps/SDL2-2.0.7/Build-Cygwin/SDL2.dll

../build/${CND_PLATFORM}-${CND_CONF}/TestApp.exe: ../SDL2Wrapper/../build/Cygwin-Windows-Debug/libSDL2Wrapper.dll

../build/${CND_PLATFORM}-${CND_CONF}/TestApp.exe: ${OBJECTFILES}
	${MKDIR} -p ../build/${CND_PLATFORM}-${CND_CONF}
	${LINK.cc} -o ../build/${CND_PLATFORM}-${CND_CONF}/TestApp ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/main.o: main.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I../SDL2Wrapper/inc -I../deps/CUL -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:
	cd ../SDL2Wrapper && ${MAKE} -j -f SDL2Wrapper-Makefile.mk CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} -r ../build/${CND_PLATFORM}-${CND_CONF}/libcul.dll ../build/${CND_PLATFORM}-${CND_CONF}/SDL2.dll ../build/${CND_PLATFORM}-${CND_CONF}/libSDL2Wrapper.dll
	${RM} ../build/${CND_PLATFORM}-${CND_CONF}/TestApp.exe

# Subprojects
.clean-subprojects:
	cd ../SDL2Wrapper && ${MAKE} -j -f SDL2Wrapper-Makefile.mk CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
