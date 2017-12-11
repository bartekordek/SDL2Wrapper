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
	${OBJECTDIR}/_ext/511e4115/ConsoleUtilities.o \
	${OBJECTDIR}/_ext/511e4115/FS.o \
	${OBJECTDIR}/_ext/511e4115/FileRegularImpl.o \
	${OBJECTDIR}/_ext/511e4115/IFile.o \
	${OBJECTDIR}/_ext/511e4115/MyString.o \
	${OBJECTDIR}/_ext/511e4115/Named.o \
	${OBJECTDIR}/_ext/511e4115/Path.o \
	${OBJECTDIR}/_ext/511e4115/XYPosition.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-Ofast
CXXFLAGS=-Ofast

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=../../deps/boost_1_64_0/Build-Cygwin/libboost_system-mt.a ../../deps/boost_1_64_0/Build-Cygwin/libboost_filesystem-mt.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../../build/${CND_PLATFORM}-${CND_CONF}/libcul.${CND_DLIB_EXT}

../../build/${CND_PLATFORM}-${CND_CONF}/libcul.${CND_DLIB_EXT}: ../../deps/boost_1_64_0/Build-Cygwin/libboost_system-mt.a

../../build/${CND_PLATFORM}-${CND_CONF}/libcul.${CND_DLIB_EXT}: ../../deps/boost_1_64_0/Build-Cygwin/libboost_filesystem-mt.a

../../build/${CND_PLATFORM}-${CND_CONF}/libcul.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ../../build/${CND_PLATFORM}-${CND_CONF}
	${LINK.cc} -o ../../build/${CND_PLATFORM}-${CND_CONF}/libcul.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -Wl,--out-implib,../../build/${CND_PLATFORM}-${CND_CONF}/libcul.a -shared

${OBJECTDIR}/_ext/511e4115/ConsoleUtilities.o: ../src/ConsoleUtilities.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Werror -DCULLib_EXPORT -DCUL_DYNAMIC -I.. -I../src -I../../deps/boost_1_64_0 -std=c++14  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/ConsoleUtilities.o ../src/ConsoleUtilities.cpp

${OBJECTDIR}/_ext/511e4115/FS.o: ../src/FS.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Werror -DCULLib_EXPORT -DCUL_DYNAMIC -I.. -I../src -I../../deps/boost_1_64_0 -std=c++14  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/FS.o ../src/FS.cpp

${OBJECTDIR}/_ext/511e4115/FileRegularImpl.o: ../src/FileRegularImpl.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Werror -DCULLib_EXPORT -DCUL_DYNAMIC -I.. -I../src -I../../deps/boost_1_64_0 -std=c++14  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/FileRegularImpl.o ../src/FileRegularImpl.cpp

${OBJECTDIR}/_ext/511e4115/IFile.o: ../src/IFile.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Werror -DCULLib_EXPORT -DCUL_DYNAMIC -I.. -I../src -I../../deps/boost_1_64_0 -std=c++14  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/IFile.o ../src/IFile.cpp

${OBJECTDIR}/_ext/511e4115/MyString.o: ../src/MyString.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Werror -DCULLib_EXPORT -DCUL_DYNAMIC -I.. -I../src -I../../deps/boost_1_64_0 -std=c++14  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/MyString.o ../src/MyString.cpp

${OBJECTDIR}/_ext/511e4115/Named.o: ../src/Named.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Werror -DCULLib_EXPORT -DCUL_DYNAMIC -I.. -I../src -I../../deps/boost_1_64_0 -std=c++14  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/Named.o ../src/Named.cpp

${OBJECTDIR}/_ext/511e4115/Path.o: ../src/Path.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Werror -DCULLib_EXPORT -DCUL_DYNAMIC -I.. -I../src -I../../deps/boost_1_64_0 -std=c++14  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/Path.o ../src/Path.cpp

${OBJECTDIR}/_ext/511e4115/XYPosition.o: ../src/XYPosition.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Werror -DCULLib_EXPORT -DCUL_DYNAMIC -I.. -I../src -I../../deps/boost_1_64_0 -std=c++14  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/XYPosition.o ../src/XYPosition.cpp

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
