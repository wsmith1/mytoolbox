
CFLAGS	= -I../../../../include -D_FILE_OFFSET_BITS=64 -Wall $(MYTOOLBOX_CFLAGS_EXTRA_WARNINGS)
OFLAGS	= -O2

CFLAGS += -Werror

OBJS=   t-bug.o t-bug-warn.o t-compiler.o  \
        t-cpu_cycles.o t-list.o t-list_sort.o  \
        t-macros.o t-poison.o t-random.o  \
        t-rbtree.o t-rbtree_test.o  \
        t-stddef-mytoolbox.o t-types-mytoolbox.o


.PHONY: all

all: $(OBJS)

.c.o:
	@echo "  CC    $<"
	$(CC) $(CFLAGS) $(OFLAGS) -c $<

.PHONY: clean

clean:
	rm -f *.o

