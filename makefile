CC:=gcc
#CCFLAGS:=-Wall -Iinclude
CCFLAGS:=-Iinclude
BIN:=bin

all: ftpd

ftpd:server.c lib/utils.c lib/zlog.c lib/vars.c
	${CC} ${CCFLAGS} -o./${BIN}/$@ $^ && ./${BIN}/$@

print_server:test/print_server.c lib/utils.c
	${CC} ${CCFLAGS} -o./${BIN}/$@ $^

clean:
	rm ./${BIN}/*.o
	rm ./${BIN}/ftp*
	rm ./${BIN}/print_server
