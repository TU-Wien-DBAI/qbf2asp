############################
# FLAGS:                   #
############################

# tell automake to pass certain flags to autoconf on re-run
ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}

# tell automake to pass certain flags to 'ctags'
AM_CTAGSFLAGS = --extra=+f

#FIXME: don't assume GCC, do feature detection in configure.ac
# tell automake to pass certain CPPFLAGS to the compiler
AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_builddir)/include \
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

#-----------------------------#
# libqbf2asp.la build options #
#-----------------------------#

# list the names of the public header files of the libqbf2asp.la library
libqbf2asp_la_include_HEADERS = \
	include/qbf2asp/main \
	include/qbf2asp/global \
	\
	include/qbf2asp/configuration.h \
	\
	include/qbf2asp/IQbf2AspRewriterFactory.hpp \
	include/qbf2asp/IQbf2AspRewriter.hpp \
	\
	include/qbf2asp/create.hpp

# list public header files that should be installed, but not distributed
# useful for generated headers, which should not be distributed as source code
nodist_libqbf2asp_la_include_HEADERS = \
	include/qbf2asp/ac_enable_decomposition.h

# list all source code files for the libqbf2asp.la library
libqbf2asp_la_SOURCES = \
	src/assembly.cpp \
	src/preamble.h \
	\
	src/create.cpp \
	\
	src/util/errorhandling.cpp \
	src/util/errorhandling.hpp \
	src/util/debug.cpp \
	src/util/debug.hpp

# list of public header files used when tree decomposition is enabled
HEADERS_DECOMPOSITION = \
	include/qbf2asp/IQbf2AspTreeAlgorithmFactory.hpp \
	include/qbf2asp/IQbf2AspTreeAlgorithm.hpp \
	include/qbf2asp/IQbf2AspTreeRewriterFactory.hpp \
	include/qbf2asp/IQbf2AspTreeRewriter.hpp \
	include/qbf2asp/IQbfToHypergraphConverterFactory.hpp \
	include/qbf2asp/IQbfToHypergraphConverter.hpp \
	\
	include/qbf2asp/DecomposableQbfInstance.hpp

# list source code files used when tree decomposition is enabled
SOURCES_DECOMPOSITION = \
	src/algorithms/Qbf2DatalogTable.cpp \
	src/algorithms/Qbf2DatalogTable.hpp \
	src/algorithms/Qbf2DatalogTreeAlgorithm.cpp \
	src/algorithms/Qbf2DatalogTreeAlgorithm.hpp \
	src/algorithms/Qbf2DatalogTreeRewriter.cpp \
	src/algorithms/Qbf2DatalogTreeRewriter.hpp \
	\
	src/instances/DecomposableQbfInstance.cpp \
	src/instances/PrimalHypergraphConverter.cpp \
	src/instances/PrimalHypergraphConverter.hpp

# tell automake to also distribute/compile the tree decomposition files
# if the ENABLE_DECOMPOSITION conditional variable is set
if ENABLE_DECOMPOSITION
libqbf2asp_la_include_HEADERS += $(HEADERS_DECOMPOSITION)
libqbf2asp_la_SOURCES += $(SOURCES_DECOMPOSITION)
endif

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
