# This Makefile is to be symbolic-linked inside subfolders.
# It is generic enough that, to the asumption the subfolder contains one .ino
# file and only one, it'll work as expected.

source = $(wildcard *.ino)
target = build/$(source).with_bootloader.hex
opt =

ALL: $(target)

$(target): $(source)
ifdef color
	./am2 $(opt) $<
else
	GCC_COLORS="" ./am2 --no-color $(opt) $<
endif

.PHONY : clean mrproper

# FIXME
# As of November 2022, the presence of /tmp/arduino-core-cache leads to an
# error message when compiling.
# The short-term hack to fix this is, to simply delete this cache directory.
# Still this means, 'make' will only work after 'make clean'.

clean:
	rm -rf build /tmp/arduino-core-cache

mrproper: clean
	
	rm -rf out
