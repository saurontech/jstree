LIB_SRC = $(shell find ../json -name '*.c' -print)
LIB_HDR = $(shell find ../json -name '*.h' -print)

all: jstree_write_excp

jstree_write_excp: jstree_write_excp.c ${LIB_SRC} ${LIB_HDR}
	gcc -o $@ ${LIB_SRC} $< -Wall -Werror -I ../json

clean:
	rm -f jstree_write_excp
