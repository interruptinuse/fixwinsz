# Install to $HOME/.local or /usr/local.

TAR     = tar
LS      = ls
VERSION = 0.08
TARBALL = fixwinsz-$(VERSION).tar
LIBDIR  = $(PREFIX)/lib
BINDIR  = $(PREFIX)/bin


fixwinsz.so: fixwinsz.so.o
	$(CC) -o $@ -shared -Wl,--no-as-needed $(CFLAGS) $< -ldl $(LDFLAGS)

fixwinsz.so.o: fixwinsz.so.c get-tiocgwinsz
	$(eval TIOCGWINSZ := $(shell ./get-tiocgwinsz))
	$(CC) -c -o $@ -DTIOCGWINSZ=$(TIOCGWINSZ) -fpic $(CFLAGS) $< $(LDFLAGS)

fixwinsz.1.txt: fixwinsz.1
	env LC_ALL=C MANWIDTH=80 man --nh -P cat "$(shell readlink -e $^)" > $@

get-tiocgwinsz: get-tiocgwinsz.c
	$(CC) -o $@ $(CFLAGS) $< $(LDFLAGS)

clean:
	rm -f $(shell cat .gitignore) $(TARBALL) $(TARBALL).gz

install: fixwinsz.so
	$(if $(PREFIX),,$(error PREFIX not defined (try $$HOME/.local or /usr/local)))
	install -D -m0644 -t "$(PREFIX)/share/man/man1/"  fixwinsz.1
	gzip --best          "$(PREFIX)/share/man/man1/fixwinsz.1"
	install -D -m0644 -t "$(LIBDIR)/"                 fixwinsz.so
	install -D        -t "$(BINDIR)/"                 fixwinsz

dist: clean fixwinsz.1.txt
	env LC_ALL=C TZ=UTC $(LS) --group-directories-first -AX1 \
	| $(TAR) -cf $(TARBALL) \
	  --exclude='*.tar*' --exclude='.git' --exclude-from=.gitignore \
	  --owner=user:1000 --group=user:1000 --dereference \
	  --mtime="$(shell env TZ=UTC date -d 00:00)" \
	  --transform="s:^:fixwinsz-$(VERSION)/:" -T-
	touch -d 00:00 $(TARBALL)
	gzip --no-name --best --rsyncable $(TARBALL)
	$(TAR) -tvzf $(TARBALL).gz

.PHONY: clean install dist
