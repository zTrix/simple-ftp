CC:=gcc
#CCFLAGS:=-Wall -Iinclude
CCFLAGS:=-Iinclude
BIN:=bin

all: ftpd

ftpd:server.c lib/mysocket.c lib/zlog.c
	${CC} ${CCFLAGS} -o./${BIN}/$@ $^ && ./${BIN}/$@

clean:
	rm ./${BIN}/*.o
	rm ./${BIN}/ftp*
