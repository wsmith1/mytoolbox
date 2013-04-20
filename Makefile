
.PHONY: all

all:
	make -C library/headertest all
	make -C library all

.PHONY: clean

clean:
	make -C library/headertest clean
	make -C library clean

