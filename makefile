CC:=gcc
#CCFLAGS:=-Wall -Iinclude
CCFLAGS:=-Iinclude
BIN:=bin

all: client

ftpd:server.c lib/utils.c lib/zlog.c lib/vars.c
	${CC} ${CCFLAGS} -o./${BIN}/$@ $^ && ./${BIN}/$@

client:client.c lib/utils.c lib/zlog.c lib/vars.c
	${CC} ${CCFLAGS} -o./${BIN}/$@ $^ && ./${BIN}/$@ 127.0.0.1

print_server:test/print_server.c lib/utils.c
	${CC} ${CCFLAGS} -o./${BIN}/$@ $^

clean:
	rm ./${BIN}/*.o
	rm ./${BIN}/ftp*
	rm ./${BIN}/print_server
