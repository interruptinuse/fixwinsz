# Install to $HOME/.local or /usr/local.

TAR     = tar
LS      = ls
GZIP    = gzip
VERSION = 0.10
TARBALL = fixwinsz-$(VERSION).tar
BINDIR  = $(PREFIX)/bin

fixwinsz:

install: fixwinsz
	$(if $(PREFIX),,$(error PREFIX not defined (try $$HOME/.local or /usr/local)))
	install -D -m0644 -t "$(PREFIX)/share/man/man1/" fixwinsz.1
	gzip --force --best "$(PREFIX)/share/man/man1/fixwinsz.1"
	install -D -t "$(BINDIR)/" fixwinsz

fixwinsz.1.txt: fixwinsz.1
	env LC_ALL=C MANWIDTH=80 man --nh -P cat "$(shell readlink -e $^)" > $@

clean:
	rm -f $(shell cat .gitignore) $(TARBALL) $(TARBALL).gz

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
