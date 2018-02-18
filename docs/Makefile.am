if HAVE_DOXYGEN

$(directory): doxyfile.stamp

doxyfile.stamp: Doxyfile
	$(DOXYGEN) $^
	echo Timestamp > $@

CLEANFILES = doxyfile.stamp

all-local: doxyfile.stamp

clean-local:
	rm -rf $(top_srcdir)/docs/man

endif
