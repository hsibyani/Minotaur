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
OBJECTFILES=


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
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minotaur ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Client.cpp.gch: Client.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o "$@" Client.cpp

${OBJECTDIR}/Server.cpp.gch: Server.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o "$@" Server.cpp

${OBJECTDIR}/app.cpp.gch: app.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o "$@" app.cpp

${OBJECTDIR}/count.cpp.gch: count.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o "$@" count.cpp

${OBJECTDIR}/countExec.cpp.gch: countExec.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o "$@" countExec.cpp

${OBJECTDIR}/splitExec.cpp.gch: splitExec.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o "$@" splitExec.cpp

${OBJECTDIR}/splitter.cpp.gch: splitter.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o "$@" splitter.cpp

${OBJECTDIR}/spout.cpp.gch: spout.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o "$@" spout.cpp

${OBJECTDIR}/spoutExec.cpp.gch: spoutExec.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o "$@" spoutExec.cpp

${OBJECTDIR}/test.cpp.gch: test.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o "$@" test.cpp

${OBJECTDIR}/utils.cpp.gch: utils.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o "$@" utils.cpp

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
