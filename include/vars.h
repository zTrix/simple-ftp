#ifndef __FTP_VARS_H__
#define __FTP_VARS_H__

#include <sys/socket.h>
#include <netinet/in.h>

#define BUF_SIZE 1024

#define LISTEN_ADDR INADDR_ANY
#define LISTEN_PORT 2121
#define MAX_CONNECTIONS 5

enum FTP_CMD {
    USER,
    PASS,
    RETR,
    STOR,
    STOU,
    APPE,
    REST,
    RNFR,
    RNTO,
    ABOR,
    DELE,
    RMD,
    MKD,
    PWD,
    CWD,
    CDUP,
    LIST,
    NLST,
    SITE,
    STAT,
    HELP,
    NOOP,
    TYPE,
    PASV,
    PORT,
    SYST,
    QUIT,
    MDTM,
    SIZE,
    FTP_CMD_COUNT
};

enum FTP_REPLY {
    REP_OPENDATA = 150,
    REP_OK = 200,
    REP_MDTM = 213,
    REP_SIZE = 213,
    REP_SYST = 215,
    REP_READY = 220,
    REP_QUIT = 221,
    REP_TRANSFERCOMPLETE = 226,
    REP_PASVOK = 227,
    REP_NAMEOK = 331,
    REP_CWD = 250,
    REP_CDUP = 250,
    REP_RNTO = 250,
    REP_DELE = 250,
    REP_PWD = 257,
    REP_MKDIR = 257,
    REP_LOGGEDIN = 230,
    REP_RESTOK = 350,
    REP_RNFR = 350,
    REP_ERRUNKWN = 500,
    REP_ERRPARM = 501,
    REP_ERRIGN = 202,
    REP_ERRNOTIMPL = 502,
    REP_BADSEQ = 503,
    REP_ERRNOTIMPLPARM = 504
};

#endif
