
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

APPS = demo_cpu_cycles demo_list_sort \
        demo_random demo_rbtree

OBJDUMP ?= objdump
OBJDUMP_OPTS ?= --archive-headers --disassemble --file-headers --line-numbers
NM ?= nm
NM_OPTS ?= --debug-syms --print-size

.PHONY: all

all: $(APPS)


demo_cpu_cycles: demo_cpu_cycles.c
	@echo "  CC    $<"
	$(CC) $(CFLAGS) $(OFLAGS) $< $(LDFLAGS) -o $@
	@echo "  OBJDUMP $@ -> $@.asm.log"
	$(OBJDUMP) $(OBJDUMP_OPTS) $@ > $@.asm.log
	@echo "  NM    $@ -> $@.nm.log"
	$(NM) $(NM_OPTS) $@ > $@.nm.log

demo_list_sort: demo_list_sort.c
	@echo "  CC    $<"
	$(CC) $(CFLAGS) $(OFLAGS) $< $(LDFLAGS) -o $@
	@echo "  OBJDUMP $@ -> $@.asm.log"
	$(OBJDUMP) $(OBJDUMP_OPTS) $@ > $@.asm.log
	@echo "  NM    $@ -> $@.nm.log"
	$(NM) $(NM_OPTS) $@ > $@.nm.log

demo_random: demo_random.c
	@echo "  CC    $<"
	$(CC) $(CFLAGS) $(OFLAGS) $< $(LDFLAGS) -o $@
	@echo "  OBJDUMP $@ -> $@.asm.log"
	$(OBJDUMP) $(OBJDUMP_OPTS) $@ > $@.asm.log
	@echo "  NM    $@ -> $@.nm.log"
	$(NM) $(NM_OPTS) $@ > $@.nm.log

demo_rbtree: demo_rbtree.c
	@echo "  CC    $<"
	$(CC) $(CFLAGS) $(OFLAGS) $< $(LDFLAGS) -o $@
	@echo "  OBJDUMP $@ -> $@.asm.log"
	$(OBJDUMP) $(OBJDUMP_OPTS) $@ > $@.asm.log
	@echo "  NM    $@ -> $@.nm.log"
	$(NM) $(NM_OPTS) $@ > $@.nm.log

.PHONY: clean

clean:
	rm -f $(APPS) $(addsuffix .asm.log,$(APPS)) $(addsuffix .nm.log,$(APPS))
