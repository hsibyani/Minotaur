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
CND_PLATFORM=GNU-MacOSX
CND_DLIB_EXT=dylib
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Client.o \
	${OBJECTDIR}/Server.o \
	${OBJECTDIR}/app.o \
	${OBJECTDIR}/count.o \
	${OBJECTDIR}/splitter.o \
	${OBJECTDIR}/spout.o \
	${OBJECTDIR}/test.o \
	${OBJECTDIR}/utils.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-lzmq
CXXFLAGS=-lzmq

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/usr/local/lib

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minotaur

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minotaur: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minotaur ${OBJECTFILES} ${LDLIBSOPTIONS} -lzmq

${OBJECTDIR}/Client.o: Client.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Client.o Client.cpp

${OBJECTDIR}/Server.o: Server.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Server.o Server.cpp

${OBJECTDIR}/app.o: app.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/app.o app.cpp

${OBJECTDIR}/count.o: count.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/count.o count.cpp

${OBJECTDIR}/splitter.o: splitter.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/splitter.o splitter.cpp

${OBJECTDIR}/spout.o: spout.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/spout.o spout.cpp

${OBJECTDIR}/test.o: test.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/test.o test.cpp

${OBJECTDIR}/utils.o: utils.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils.o utils.cpp

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
