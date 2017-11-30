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
LDLIBSOPTIONS=../build/Cygwin-Windows-Release/libSDL2Wrapper.a ../deps/CUL/build/Cygwin-Windows-Release/libcul.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../build/${CND_PLATFORM}-${CND_CONF}/TestApp.exe

../build/${CND_PLATFORM}-${CND_CONF}/TestApp.exe: ../build/Cygwin-Windows-Release/libSDL2Wrapper.a

../build/${CND_PLATFORM}-${CND_CONF}/TestApp.exe: ../deps/CUL/build/Cygwin-Windows-Release/libcul.a

../build/${CND_PLATFORM}-${CND_CONF}/TestApp.exe: ${OBJECTFILES}
	${MKDIR} -p ../build/${CND_PLATFORM}-${CND_CONF}
	${LINK.cc} -o ../build/${CND_PLATFORM}-${CND_CONF}/TestApp ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Werror -I../SDL2Wrapper/inc -I../deps/CUL -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
