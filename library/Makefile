
CFLAGS	= -I../include -D_FILE_OFFSET_BITS=64 -Wall $(MYTOOLBOX_CFLAGS_EXTRA_WARNINGS)
OFLAGS	= -O2

ifndef MYTOOLBOX_CFLAGS_NO_WARNINGS_AS_ERRORS
CFLAGS += -Werror
endif # MYTOOLBOX_CFLAGS_NO_WARNINGS_AS_ERRORS

# To compile as a shared library:
ifdef MYTOOLBOX_SHARED
CFLAGS += -fPIC
endif # MYTOOLBOX_SHARED

DLEXT=so

OBJS=   list_sort.o list_sort_test.o \
        random32.o rbtree.o rbtree_test.o

OBJDUMP ?= objdump
OBJDUMP_OPTS ?= --archive-headers --disassemble --file-headers --line-numbers
NM ?= nm
NM_OPTS ?= --debug-syms --print-size

.PHONY: all

ifdef MYTOOLBOX_SHARED
all: shared
else # MYTOOLBOX_SHARED
all: static
endif # MYTOOLBOX_SHARED

.PHONY: static

static: libmytoolbox.a

.PHONY: shared

shared: libmytoolbox.$(DLEXT)

libmytoolbox.a: $(OBJS)
	@echo "  AR    $@"
	ar r $@ $(OBJS)
	@echo "  RL    $@"
	ranlib $@
	@echo "  OBJDUMP $@ -> $@.asm.log"
	$(OBJDUMP) $(OBJDUMP_OPTS) $@ > $@.asm.log
	@echo "  NM    $@ -> $@.nm.log"
	$(NM) $(NM_OPTS) $@ > $@.nm.log

libmytoolbox.so: libmytoolbox.a
	@echo "  LD    $@"
	$(CC) -shared -Wl,-soname,$@ -o $@ $(OBJS)

.c.o:
	@echo "  CC    $<"
	$(CC) $(CFLAGS) $(OFLAGS) -c $<

.PHONY: clean

clean:
	rm -f *.o libmytoolbox.* *.asm.log *.nm.log

