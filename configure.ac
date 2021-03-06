#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

# initialize autoconf
#####################
AC_PREREQ([2.69])				# minimum autoconf version

# supply the name of the project, version number, and contact email
AC_INIT([qbf2asp], [0.1], [morak@dbai.tuwien.ac.at])

AC_CONFIG_SRCDIR([src/assembly.cpp]) 	# source directory
AC_CONFIG_HEADERS([config.h])			# name of generated header
AC_CONFIG_MACRO_DIR([m4])				# folder for autoconf macros
AC_CONFIG_AUX_DIR([build-aux])			# folder for auxilliary files

# initialize automake with the following options:
#################################################
#   subdir-objects:
#	tell automake to create object files in same directory as the source
AM_INIT_AUTOMAKE([1.15 subdir-objects])
#   tell automake not to be verbose when compiling
AM_SILENT_RULES([yes])

# enable libtool to build libraries
###################################
LT_PREREQ([2.4])		# minimum libtool version
LT_INIT					# initialize libtool
LT_LANG([C++])		 	# set libtool language(s)

# define needed variables
#########################

# check wether doxygen is present
#################################

AC_CHECK_PROGS([DOXYGEN], [doxygen])
if test -z "$DOXYGEN";
   then AC_MSG_WARN([Doxygen not found - continuing without Doxygen])
fi

AM_CONDITIONAL([HAVE_DOXYGEN], [test -n "$DOXYGEN"])
AM_COND_IF([HAVE_DOXYGEN],
	[AC_CONFIG_FILES([docs/Doxyfile])])

# check that relevant programs are present on the system and enable them
########################################################################
AC_LANG([C++])			# check for C++ support
AC_PROG_CXX				# check for C++ compiler support
AC_PROG_INSTALL			# check for 'install'
AC_PROG_LN_S			# check for 'ln -s'
AC_PROG_YACC			# check for yacc-compatible parser generator
AC_PROG_LEX				# check for lex-compatible lexer generator

# check for specific, required compiler/preprocessor characteristics
####################################################################

# check for, and enable C++11, otherwise fail
AX_CXX_COMPILE_STDCXX_11([noext], [mandatory])

# preprocessor flags should include the compiler flags (enabling C++11)
CPPFLAGS+=$CXXFLAGS

# define optional features (--enable-FEATURE)
#############################################

# add the option to enable the tree decomposition feature,
# also pass a corresponding conditional variable to automake,
# and generate our corresponding conditional header from the template
# also, if enabled, pass this to distcheck as well
AC_MSG_CHECKING([whether to build with tree decomposition support])
AC_ARG_ENABLE([decomposition],
	    [AS_HELP_STRING([--enable-decomposition],
						[enable support for tree decomposition])],
	    [case "$enableval" in			
	       yes|no) ;;				
		   *)
		   		AC_MSG_ERROR([bad value ${enableval} for decomposition option])
		   		;;
	     esac
       	   enable_decomposition=$enableval],
	    [enable_decomposition=no])
AC_MSG_RESULT([$enable_decomposition])
AM_CONDITIONAL([ENABLE_DECOMPOSITION], [test x$enable_decomposition = xyes])
AC_CONFIG_HEADERS([include/qbf2asp/ac_enable_decomposition.h])

# define optional packages to use (--with-PACKAGE)
##################################################

# definitions for config.h (the header file generated by the configure script)
##############################################################################

# define that we are building the library, and should export symbols
AC_DEFINE_UNQUOTED([QBF2ASP_EXPORTS], [1],
				   [Define to 1 if the library is being built.])

# define that we are using tree decompositions (or not)
AS_IF([test "x$enable_decomposition" = xyes],
	  [AC_DEFINE_UNQUOTED([ENABLE_DECOMPOSITION], [1],
						  [Define as 1 if tree decompositions are enabled.])])

# check that libraries are present on the system
################################################

# check for logichelpers library
#TODO: check for "none required" output of AC_SEARCH_LIBS
AC_SEARCH_LIBS([logichelpers_version], [logichelpers],
	        [LOGICHELPERS_LIBS=$ac_cv_search_logichelpers_version],
	        [AC_MSG_FAILURE([liblogichelpers not found])])

# check for logicparsers library
#TODO: check for "none required" output of AC_SEARCH_LIBS
AC_SEARCH_LIBS([logicparsers_version], [logicparsers],
			   [LOGICPARSERS_LIBS=$ac_cv_search_logicparsers_version],
			   [AC_MSG_FAILURE([liblogicparsers not found])])

# check for decomposition libraries if enabled
AS_IF([test "x$enable_decomposition" = xyes],
	  [
		# check for htd library
		#TODO: check for "none required" output of AC_SEARCH_LIBS
		AC_SEARCH_LIBS([htd_version], [htd],
					[HTD_LIBS=$ac_cv_search_htd_version],
					[AC_MSG_FAILURE([libhtd not found])])

		# check for htd library
		#TODO: check for "none required" output of AC_SEARCH_LIBS
		AC_SEARCH_LIBS([sharp_version], [sharp],
					[SHARP_LIBS=$ac_cv_search_sharp_version],
					[AC_MSG_FAILURE([libsharp not found])])
	  ])

# check for pthread (needed for googletest)
ACX_PTHREAD([], [AC_MSG_FAILURE([POSIX thread support not found])])

# checks for C header files
###########################

# checks for C++ header files
#############################
AC_LANG_PUSH([C++])

# check for logichelpers library header
AC_CHECK_HEADER([logic/helpers], [],	
				[AC_MSG_FAILURE([liblogichelpers library header not found])])

# check for logicparsers library header
AC_CHECK_HEADER([logic/parsers], [],	
				[AC_MSG_FAILURE([liblogicparsers library header not found])])

# check for decomposition libraries' headers if enabled
AS_IF([test "x$enable_decomposition" = xyes],
	  [
		# check for htd library header
		AC_CHECK_HEADER([htd/main.hpp], [],
				[AC_MSG_FAILURE([libhtd library header not found])])

		# check for htd library header
		AC_CHECK_HEADER([sharp/main], [],
				[AC_MSG_FAILURE([libsharp library header not found])])
	  ])

AC_LANG_POP([C++])

# checks for typedefs and structures
####################################

# checks for standard library functions
#######################################
#AC_CHECK_FUNCS([...])

# pass information to automake
##############################
#AC_SUBST([...])

# tell autoconf which files will be generated by it
###################################################
AC_CONFIG_FILES([Makefile
		 tests/Makefile
		 docs/Makefile])

# generate the config.status script and use it to generate the config files
###########################################################################
AC_OUTPUT
