
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

CFLAGS	= -I../include -D_FILE_OFFSET_BITS=64 -Wall $(MYTOOLBOX_CFLAGS_EXTRA_WARNINGS)
OFLAGS	= -O2
LDFLAGS	= -L../library -lmytoolbox

ifndef MYTOOLBOX_CFLAGS_NO_WARNINGS_AS_ERRORS
CFLAGS += -Werror
endif # MYTOOLBOX_CFLAGS_NO_WARNINGS_AS_ERRORS

APPS = test/test_cpu_cycles test/test_list_sort test/test_random test/test_rbtree

OBJDUMP ?= objdump
OBJDUMP_OPTS ?= --archive-headers --disassemble --file-headers --line-numbers

.PHONY: all

all: $(APPS)

test/test_cpu_cycles: test/test_cpu_cycles.c ../library/libmytoolbox.a
	@echo "  CC    $<"
	$(CC) $(CFLAGS) $(OFLAGS) test/test_cpu_cycles.c    $(LDFLAGS) -o $@
	@echo "  OBJDUMP $@ -> $@.asm.log"
	$(OBJDUMP) $(OBJDUMP_OPTS) $@ > $@.asm.log

test/test_list_sort: test/test_list_sort.c ../library/libmytoolbox.a
	@echo "  CC    $<"
	$(CC) $(CFLAGS) $(OFLAGS) test/test_list_sort.c    $(LDFLAGS) -o $@
	@echo "  OBJDUMP $@ -> $@.asm.log"
	$(OBJDUMP) $(OBJDUMP_OPTS) $@ > $@.asm.log

test/test_random: test/test_random.c ../library/libmytoolbox.a
	@echo "  CC    $<"
	$(CC) $(CFLAGS) $(OFLAGS) test/test_random.c    $(LDFLAGS) -o $@
	@echo "  OBJDUMP $@ -> $@.asm.log"
	$(OBJDUMP) $(OBJDUMP_OPTS) $@ > $@.asm.log

test/test_rbtree: test/test_rbtree.c ../library/libmytoolbox.a
	@echo "  CC    $<"
	$(CC) $(CFLAGS) $(OFLAGS) test/test_rbtree.c    $(LDFLAGS) -o $@
	@echo "  OBJDUMP $@ -> $@.asm.log"
	$(OBJDUMP) $(OBJDUMP_OPTS) $@ > $@.asm.log


.PHONY: clean

clean:
	rm -f $(APPS) $(addsuffix .asm.log,$(APPS))

