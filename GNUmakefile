# Install to $HOME/.local or /usr/local.

fixcols.so: fixcols.o
	$(CC) -shared -o $@ $<

fixcols.o: fixcols.c get-tiocgwinsz
	$(eval TIOCGWINSZ := $(shell ./get-tiocgwinsz))
	$(CC) -c $(CFLAGS) -DTIOCGWINSZ=$(TIOCGWINSZ) -fpic -o $@ $<

get-tiocgwinsz: get-tiocgwinsz.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f fixcols.so fixcols.o get-tiocgwinsz

install: fixcols.so
	install fixcols.so "${PREFIX}/lib"
	install fixcols "${PREFIX}/bin"

.PHONY: clean install
