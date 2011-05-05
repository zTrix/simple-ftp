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
    FTP_CMD_COUNT,
    INVALID
};

struct ftp_cmd {
    char *name;
    enum FTP_CMD cmd;
};

struct ftp_cmd FTP_CMD_LIST[FTP_CMD_COUNT] = {
    {"USER", USER},
    {"PASS", PASS},
    {"RETR", RETR},
    {"STOR", STOR},
    {"STOU", STOU},
    {"APPE", APPE},
    {"REST", REST},
    {"RNFR", RNFR},
    {"RNTO", RNTO},
    {"ABOR", ABOR},
    {"DELE", DELE},
    {"RMD" , RMD },
    {"MKD" , MKD },
    {"PWD" , PWD },
    {"CWD" , CWD },
    {"CDUP", CDUP},
    {"LIST", LIST},
    {"NLST", NLST},
    {"SITE", SITE},
    {"STAT", STAT},
    {"HELP", HELP},
    {"TYPE", TYPE},
    {"PASV", PASV},
    {"PORT", PORT},
    {"SYST", SYST},
    {"NOOP", NOOP},
    {"QUIT", QUIT},
    {"MDTM", MDTM},
    {"SIZE", SIZE}
};

#define RPL_RESTART 110
#define RPL_WAITRDY 120
#define RPL_DATACONN 125
#define RPL_FILERDY 150
#define RPL_OK 200
#define RPL_FILEST 213
#define RPL_SYST 215
#define RPL_RDY 220
#define RPL_QUIT 221
#define RPL_TRSFOK226
#define RPL_PASVOK 227
#define RPL_NAMEOK 331
#define RPL_CWD 250
#define RPL_CDUP 250
#define RPL_RNTO 250
#define RPL_DELE 250
#define RPL_PWD 257
#define RPL_MKDIR 257
#define RPL_LOGGEDIN 230
#define RPL_RESTOK 350
#define RPL_RNFR 350
#define RPL_ERRUNKWN 500
#define RPL_ERRPARM 501
#define RPL_ERRIGN 202
#define RPL_ERRNOTIMPL 502
#define RPL_BADSEQ 503
#define RPL_ERRNOTIMPLPARM 504

#define W(s,d) "%d "#s" \r\n",d
#define FTP_OK W(OK,RPL_OK)
#define FTP_RDY W(Welcome to zTrix FTP, RPL_RDY)

#endif
