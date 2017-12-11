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
	${OBJECTDIR}/_ext/5c0/FileTest.o \
	${OBJECTDIR}/_ext/5c0/IteratorTests.o \
	${OBJECTDIR}/_ext/5c0/PathTests.o \
	${OBJECTDIR}/_ext/5c0/Vector3DTests.o \
	${OBJECTDIR}/_ext/5c0/main.o


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
LDLIBSOPTIONS=../../deps/gtest/Build-Cygwin/libgtest.a ../../deps/gtest/Build-Cygwin/libgtest_main.a ../../build/Cygwin-Windows-Debug/libcul.a ../../build/Cygwin-Windows-Debug/libcul.dll

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/Tests.exe
	${CP} ../../build/Cygwin-Windows-Debug/libcul.dll ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/Tests.exe: ../../deps/gtest/Build-Cygwin/libgtest.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/Tests.exe: ../../deps/gtest/Build-Cygwin/libgtest_main.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/Tests.exe: ../../build/Cygwin-Windows-Debug/libcul.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/Tests.exe: ../../build/Cygwin-Windows-Debug/libcul.dll

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/Tests.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/Tests ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/5c0/FileTest.o: ../FileTest.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/5c0
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I.. -I../../deps/gtest/googletest/include -I../../deps/gtest/googlemock/include -I../../CUL -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/5c0/FileTest.o ../FileTest.cpp

${OBJECTDIR}/_ext/5c0/IteratorTests.o: ../IteratorTests.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/5c0
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I.. -I../../deps/gtest/googletest/include -I../../deps/gtest/googlemock/include -I../../CUL -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/5c0/IteratorTests.o ../IteratorTests.cpp

${OBJECTDIR}/_ext/5c0/PathTests.o: ../PathTests.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/5c0
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I.. -I../../deps/gtest/googletest/include -I../../deps/gtest/googlemock/include -I../../CUL -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/5c0/PathTests.o ../PathTests.cpp

${OBJECTDIR}/_ext/5c0/Vector3DTests.o: ../Vector3DTests.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/5c0
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I.. -I../../deps/gtest/googletest/include -I../../deps/gtest/googlemock/include -I../../CUL -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/5c0/Vector3DTests.o ../Vector3DTests.cpp

${OBJECTDIR}/_ext/5c0/main.o: ../main.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/5c0
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I.. -I../../deps/gtest/googletest/include -I../../deps/gtest/googlemock/include -I../../CUL -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/5c0/main.o ../main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} -r ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcul.dll
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/Tests.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
