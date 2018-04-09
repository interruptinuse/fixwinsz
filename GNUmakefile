# Install to $HOME/.local or /usr/local.

TAR = tar
VERSION = 0.03
TARBALL = fixwinsz-v${VERSION}.tar.gz

fixwinsz.so: fixwinsz.so.o
	$(CC) -o $@ -shared -Wl,--no-as-needed $(CFLAGS) $< -ldl $(LDFLAGS)

fixwinsz.so.o: fixwinsz.so.c get-tiocgwinsz
	$(eval TIOCGWINSZ := $(shell ./get-tiocgwinsz))
	$(CC) -c -o $@ -DTIOCGWINSZ=$(TIOCGWINSZ) -fpic $(CFLAGS) $< $(LDFLAGS)

get-tiocgwinsz: get-tiocgwinsz.c
	$(CC) -o $@ $(CFLAGS) $< $(LDFLAGS)

clean:
	rm -f fixwinsz.so fixwinsz.so.o get-tiocgwinsz ${TARBALL}

install: fixwinsz.so
	install -D -m0644 fixwinsz.1  "${PREFIX}/share/man/man1/"
	install -D -m0644 fixwinsz.so "${PREFIX}/lib/"
	install -D        fixwinsz    "${PREFIX}/bin/"

dist: clean
	$(TAR) -cf - --exclude='*.tar*' --exclude='.git' --exclude-from=.gitignore --numeric-owner --transform="s:^.:fixwinsz-v${VERSION}:" . | gzip --best > ${TARBALL}
	$(TAR) -tvzf ${TARBALL}

.PHONY: clean install dist
