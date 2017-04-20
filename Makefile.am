############################
# FLAGS:                   #
############################

# tell automake to pass certain flags to autoconf on re-run
ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}

# tell automake to pass certain flags to 'ctags'
AM_CTAGSFLAGS = --extra=+f

# tell automake to pass certain flags to 'lex'
AM_LFLAGS = -olex.yy.c

# tell automake to pass certain flags to 'yacc'
AM_YFLAGS = --defines=y.tab.h -oy.tab.c

#FIXME: don't assume GCC, do feature detection in configure.ac
# tell automake to pass certain CPPFLAGS to the compiler
AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-pedantic-errors \
	-Wpedantic \
	-Wall \
	-Wextra \
	-Wdouble-promotion \
	-Wswitch-default \
	-fvisibility=hidden \
	-fvisibility-inlines-hidden

# initialize variables
EXTRA_DIST =
CLEANFILES =
BUILT_SOURCES = 
				
############################
# LIBRARIES TO BUILD:	   #
############################

# tell automake which libraries to build
lib_LTLIBRARIES = libqbf2asp.la

#----------------------------#
# libqbf2asp.la build options #
#----------------------------#

# list of generated header files
LIBQBF2ASP_GENERATED_HEADER = \
	src/parsers/QDIMACSBisonParser.hh \
	stack.hh \
	position.hh \
	location.hh

# list of generated source files
LIBQBF2ASP_GENERATED_SOURCE = \
	src/parsers/QDIMACSBisonParser.cc \
	src/parsers/QDIMACSLexer.cc

# add those to the automake variable for generated files
BUILT_SOURCES += $(LIBQBF2ASP_GENERATED_SOURCE)

# tell automake to clean up the generated headers on 'make clean'
# and to distribute the headers on 'make dist'
CLEANFILES += $(LIBQBF2ASP_GENERATED_HEADER)
EXTRA_DIST += $(LIBQBF2ASP_GENERATED_HEADER)

# list the names of the public header files of the libqbf2asp.la library
libqbf2asp_la_include_HEADERS = \
	include/qbf2asp/main \
	include/qbf2asp/global \
	\
	include/qbf2asp/IQbf2AspAlgorithmFactory.hpp \
	include/qbf2asp/IQbf2AspAlgorithm.hpp \
	include/qbf2asp/IQbfClauseFactory.hpp \
	include/qbf2asp/IQbfClause.hpp \
	include/qbf2asp/IQbfInstanceFactory.hpp \
	include/qbf2asp/IQbfInstance.hpp \
	include/qbf2asp/IQbfToHypergraphConverterFactory.hpp \
	include/qbf2asp/IQbfToHypergraphConverter.hpp \
	include/qbf2asp/IQDIMACSParserFactory.hpp \
	include/qbf2asp/IQDIMACSParser.hpp \
	\
	include/qbf2asp/create.hpp \
	\
	include/qbf2asp/Variable.hpp \
	include/qbf2asp/Clause.hpp 

# list all source code files for the libqbf2asp.la library
# don't need to list the generated .cc files from bison and flex
# since automake already knows about them, and adds them automatically
libqbf2asp_la_SOURCES = \
	src/assembly.cpp \
	\
	src/create.cpp \
	\
	src/instances/QbfInstance.cpp \
	src/instances/QbfInstance.hpp \
	src/instances/QbfClause.cpp \
	src/instances/QbfClause.hpp \
	\
	src/parsers/QDIMACSBisonParser.hpp \
	src/parsers/QDIMACSBisonParser.yy \
	src/parsers/QDIMACSLexer.hpp \
	src/parsers/QDIMACSLexer.ll \
	src/parsers/QDIMACSParser.cpp \
	src/parsers/QDIMACSParser.hpp \
	\
	src/util/errorhandling.cpp \
	src/util/errorhandling.hpp \
	src/util/debug.cpp \
	src/util/debug.hpp

# tell automake that the installation directory for public header files of the
# libqbf2asp.la library should be a subfolder in the default ${includedir}
libqbf2asp_la_includedir = ${includedir}/qbf2asp

# tell libtool to pass certain LDFLAGS to the compiler when building libsharp.la
#
# 1) Specify the Shared Object Version Information for the library, which
# consists of three numbers: CURRENT:REVISION:AGE
#
#   CURRENT: This is the version of the (external) ABI in the library.
#       Increase if the ABI changes (i.e. interfaces added or changed)!
#
#   REVISION: The revision represents how often the library was changed for a
#       given ABI version. Increase this whenever the library code changes, but
#       reset to 0 when incrementing CURRENT.
#
#   AGE: This is the difference between the oldest and newest ABI version
#       that the library is backwards compatible with (e.g. if CURRENT is 4,
#       but we are backwards compatible to ABI version 1, then AGE = 3). Set to
#       0 if there is a backwards-compatibility breaking change, otherwise
#       increase by 1 if CURRENT was increased by one.
#
libqbf2asp_la_LDFLAGS = -version-info 0:0:0

############################
# PROGRAMS TO BUILD:	   #
############################

# Link the main library (libqbf2asp.la) to all programs.
LDADD = libqbf2asp.la

# tell automake which programs to build
bin_PROGRAMS = qbf2asp

#----------------------#
# qbf2asp build options #
#----------------------#

# list all source code files for the qbf2asp program
qbf2asp_SOURCES = \
	src/main.cpp

############################
# DISTRIBUTION OPTIONS:	   #
############################

# tell automake about scripts that should be distributed in the tarball, but
# not installed on "make install"
dist_noinst_SCRIPTS = autogen.sh

# tell automake to clean the generated files on "make clean"
CLEANFILES += $(BUILT_SOURCES)

############################
# UNIT TESTS:              #
############################

# tell automake to recursively go into the test directory
SUBDIRS = tests
