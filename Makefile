
.PHONY: all

all:
	make -C library/headertest all
	make -C library all
	make -C programs all

.PHONY: clean

clean:
	make -C library/headertest clean
	make -C library clean
	make -C programs clean

