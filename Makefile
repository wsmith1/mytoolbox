
.PHONY: all

all:
	make -C library/compiletest/headertest/c all
	make -C library/compiletest/headertest/cc all
	make -C library all
	make -C programs all

.PHONY: clean

clean:
	make -C library/compiletest/headertest/c clean
	make -C library/compiletest/headertest/cc clean
	make -C library clean
	make -C programs clean

