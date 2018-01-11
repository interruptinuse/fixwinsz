# Install to $HOME/.local or /usr/local.

fixwinsz.so: fixwinsz.so.o
	$(CC) -o $@ -shared -Wl,--no-as-needed $(LDFLAGS) $< -ldl

fixwinsz.so.o: fixwinsz.so.c get-tiocgwinsz
	$(eval TIOCGWINSZ := $(shell ./get-tiocgwinsz))
	$(CC) -c -o $@ -DTIOCGWINSZ=$(TIOCGWINSZ) -fpic $(CFLAGS) $<

get-tiocgwinsz: get-tiocgwinsz.c
	$(CC) -o $@ $(CFLAGS) $<

clean:
	rm -f fixwinsz.so fixwinsz.so.o get-tiocgwinsz

install: fixwinsz.so
	install fixwinsz.so "${PREFIX}/lib"
	install fixwinsz "${PREFIX}/bin"

.PHONY: clean install
