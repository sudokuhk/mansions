OBJS = $(patsubst %.c, %, $(wildcard *.c))

CC=gcc
CFLAG=-g -DMON_HAVE_GCC_VARIADIC_MACROS
INCLUDE_DIR=-I../src/common -I../src/log -I../src/string

RELY_ON_SRC=../src/log/log.c	\
	../src/string/mon_string.c	\
	../src/string/mon_printf.c	\

BUILD_C= @                                                            \
	for src in $(C_FILES);  	\
	do                         \
	    clen=`echo $$src | wc -L`; \
	    clen=`expr $$clen - 2`;    \
	    tobj=`echo $$src | cut -c1-$$clen`;  \
	    echo "$(CC) $(CFLAG) $(INCLUDE_DIR) $$src -o $$tobj";  \
	    $(CC) $(CFLAG) $(INCLUDE_DIR) $$src -o $$tobj;         \
	done

all: $(OBJS)

test_list:
	$(CC) $(CFLAG) $(INCLUDE_DIR) $@.c -o $@
	
test_log:
	$(CC) $(CFLAG) $(INCLUDE_DIR) $@.c $(RELY_ON_SRC) -o $@

test_string:
	$(CC) $(CFLAG) $(INCLUDE_DIR) $@.c $(RELY_ON_SRC) -o $@

.PHONY:clean
clean:
	-rm -f $(OBJS)
