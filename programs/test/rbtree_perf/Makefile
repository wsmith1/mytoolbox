
# Suggested value for MYTOOLBOX_CFLAGS_EXTRA_WARNINGS to pass
# on the command line, for gcc (GCC) 4.4.6 20120305
# (Red Hat 4.4.6-4):
#
# make  all 'MYTOOLBOX_CFLAGS_EXTRA_WARNINGS= -Wextra -Wformat=2
#   -fstrict-aliasing -Wstrict-aliasing -Wfloat-equal
#   -Wundef -Wpointer-arith -Wbad-function-cast
#   -Wcast-qual -Wcast-align -Wwrite-strings -Waddress
#   -Waggregate-return -Wstrict-prototypes
#   -Wold-style-declaration -Wold-style-definition
#   -Wmissing-parameter-type -Wmissing-prototypes
#   -Wmissing-declarations -Wmissing-field-initializers
#   -Wmissing-noreturn -Wmissing-format-attribute -Wpacked
#   -Wredundant-decls -Wnested-externs'
#

CFLAGS	= -I../../../include -D_FILE_OFFSET_BITS=64 -Wall $(MYTOOLBOX_CFLAGS_EXTRA_WARNINGS)
OFLAGS	= -O2
LDFLAGS	= -L../../../library -lmytoolbox

ifndef MYTOOLBOX_CFLAGS_NO_WARNINGS_AS_ERRORS
CFLAGS += -Werror
endif # MYTOOLBOX_CFLAGS_NO_WARNINGS_AS_ERRORS

APPS = test_tree_callbacks1 test_tree_callbacks2 test_tree_superanchor test_tree_embedded

H_FILES= tree_callbacks1.h tree_callbacks2.h tree_superanchor.h tree_embedded.h tree_config.h

OBJDUMP ?= objdump
OBJDUMP_OPTS ?= --archive-headers --disassemble --file-headers --line-numbers
NM ?= nm
NM_OPTS ?= --debug-syms --print-size

.PHONY: all

all: $(APPS)

$(APPS): $(H_FILES) ../../../library/libmytoolbox.a

test_tree_callbacks1: test_tree_callbacks1.c tree_callbacks1.c
	@echo "  CC    $<"
	$(CC) $(CFLAGS) $(OFLAGS) $^ $(LDFLAGS) -o $@
	@echo "  OBJDUMP $@ -> $@.asm.log"
	$(OBJDUMP) $(OBJDUMP_OPTS) $@ > $@.asm.log
	@echo "  NM    $@ -> $@.nm.log"
	$(NM) $(NM_OPTS) $@ > $@.nm.log

test_tree_callbacks2: test_tree_callbacks2.c tree_callbacks2.c
	@echo "  CC    $<"
	$(CC) $(CFLAGS) $(OFLAGS) $^ $(LDFLAGS) -o $@
	@echo "  OBJDUMP $@ -> $@.asm.log"
	$(OBJDUMP) $(OBJDUMP_OPTS) $@ > $@.asm.log
	@echo "  NM    $@ -> $@.nm.log"
	$(NM) $(NM_OPTS) $@ > $@.nm.log

test_tree_superanchor: test_tree_superanchor.c tree_superanchor.c
	@echo "  CC    $<"
	$(CC) $(CFLAGS) $(OFLAGS) $^ $(LDFLAGS) -o $@
	@echo "  OBJDUMP $@ -> $@.asm.log"
	$(OBJDUMP) $(OBJDUMP_OPTS) $@ > $@.asm.log
	@echo "  NM    $@ -> $@.nm.log"
	$(NM) $(NM_OPTS) $@ > $@.nm.log

test_tree_embedded: test_tree_embedded.c tree_embedded.c
	@echo "  CC    $<"
	$(CC) $(CFLAGS) $(OFLAGS) $^ $(LDFLAGS) -o $@
	@echo "  OBJDUMP $@ -> $@.asm.log"
	$(OBJDUMP) $(OBJDUMP_OPTS) $@ > $@.asm.log
	@echo "  NM    $@ -> $@.nm.log"
	$(NM) $(NM_OPTS) $@ > $@.nm.log



.PHONY: clean

clean:
	rm -f $(APPS) $(addsuffix .asm.log,$(APPS)) $(addsuffix .nm.log,$(APPS))
