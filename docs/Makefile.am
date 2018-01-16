if HAVE_DOXYGEN
directory = $(top_srcdir)/docs/man/man3/

dist_man_MANS = $(directory)/man_page_1.3 $(directory)/man_page_2.3
$(directory)/man_page_1.3: doxyfile.stamp
$(directory)/man_page_2.3: doxyfile.stamp

$(directory): doxyfile.stamp

doxyfile.stamp: Doxyfile
	$(DOXYGEN) $^
	echo Timestamp > $@

CLEANFILES = doxyfile.stamp

all-local: doxyfile.stamp

clean-local:
	rm -rf $(top_srcdir)/docs/man

endif
