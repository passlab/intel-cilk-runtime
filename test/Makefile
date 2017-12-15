# cilkrts install path
CILKRTS_PATH=../../intel-cilk-runtime-install

INCLUDE_FLAGS = -I${CILKRTS_PATH}/include
LIB_FLAGS = -L${CILKRTS_PATH}/lib -lcilkrts

GCC=gcc
#GCC=/opt/gcc-5.3.0-install/bin/gcc
ICC=icc

fib: fib_serial fib_cilkrts_api fib_cilkplus

fib_serial: fib_serial.c
	${GCC} $< -o $@-gcc
	icc $< -o $@-icc

fib_cilkrts_api: fib_cilkrts_api.c
	${GCC} ${INCLUDE_FLAGS} ${LIB_FLAGS} $< -o $@-${GCC}
	icc ${INCLUDE_FLAGS} ${LIB_FLAGS} $< -o $@-icc

fib_cilkplus: fib_cilkplus.c
	${GCC} -fcilkplus $< -o $@-gcc
	icc $< -o $@-icc

clean:
	rm -rf ${OBJS} fib *.log
