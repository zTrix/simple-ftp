#ifndef __FTP_VARS_H__
#define __FTP_VARS_H__

#include <sys/socket.h>
#include <netinet/in.h>

#define BUF_SIZE 1024

#define LISTEN_ADDR INADDR_ANY
#define LISTEN_PORT 2121
#define MAX_CONNECTIONS 5

enum FTP_CMD {
    INVALID = -1,
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
};

struct ftp_cmd {
    char *name;
    enum FTP_CMD cmd;
};

extern struct ftp_cmd FTP_CMD_LIST[FTP_CMD_COUNT];

#define RPL_RESTART 110
#define RPL_WAITRDY 120
#define RPL_DATACONN 125
#define RPL_FILERDY 150
#define RPL_OK 200
#define RPL_FILEST 213
#define RPL_SYST 215
#define RPL_RDY 220
#define RPL_QUIT 221
#define RPL_TRSFOK 226
#define RPL_PASVOK 227
#define RPL_NAMEOK 331
#define RPL_CWD 250
#define RPL_CDUP 250
#define RPL_RNTO 250
#define RPL_DELE 250
#define RPL_PWD 257
#define RPL_MKDIR 257
#define RPL_LOGIN 230
#define RPL_RESTOK 350
#define RPL_RNFR 350
#define RPL_ERR_UNKWNCMD 500
#define RPL_ERR_PARM 501
#define RPL_ERR_IGN 202
#define RPL_ERR_NOTIMPL 502
#define RPL_BADSEQ 503
#define RPL_CMDNOIM 504

#define W(s,d) "%d "s" \r\n",d
#define FTP_OK W("OK",RPL_OK)
#define FTP_RDY W("Welcome to zTrix FTP", RPL_RDY)
#define FTP_QUIT W("Welcome back", RPL_QUIT)
#define FTP_HELP W("Help msg", RPL_OK)
#define FTP_NAMEOK W("User name okay need password", RPL_NAMEOK)
#define FTP_LOGIN W("User logged in proceed", RPL_LOGIN)
#define FTP_PWD W("\"%s\"", RPL_PWD)
#define FTP_SYST W("UNIX", RPL_SYST)
#define FTP_CTYPE W("data type changed to %c", RPL_OK)
#define FTP_ERR_DATATYPE W("error type change cmd, current data type is %c", RPL_ERR_UNKWNCMD)
#define FTP_PASV W("Enter passive mode (%d,%d,%d,%d,%d,%d)", RPL_PASVOK)
#define FTP_PORT W("PORT command success", RPL_OK)
#define FTP_ERR_PORT W("port command failed, parameter error", RPL_ERR_PARM)
#define FTP_ASCII W("Opening ASCII mode data connection for cmd %s", RPL_FILERDY)
#define FTP_BIN W("Opening Binary mode data connection for cmd %s", RPL_FILERDY)
#define FTP_REST W("restart at %d. use STORE or RETR to begin transfer", RPL_RESTOK)
#define FTP_ERR_PARAM W("cmd %s: wrong param", RPL_ERR_PARM)
#define FTP_TRSF_OK W("Transfer completed", RPL_TRSFOK)
#define FTP_ERROR W("FTP error: %s ", RPL_ERR_UNKWNCMD)
#define FTP_CDUP W("changd to parent directory success", RPL_CDUP)
#define FTP_CWD W("dir changed", RPL_CWD)
#define FTP_MDTM W("%s", RPL_FILEST)
#define FTP_SIZE W("%d", RPL_FILEST)
#define FTP_DELE W("Delete success", RPL_DELE)
#define FTP_MKDIR W("mkdir success", RPL_MKDIR)
#define FTP_RNFR W("RNFR success, waiting RNT", RPL_RNFR)
#define FTP_RNTO W("RNTO success", RPL_RNTO)
#define FTP_CMDNOIM W("command not implemented", RPL_CMDNOIM)

enum DATA_TYPE {
    TYPE_ASCII,
    TYPE_EBDIC,
    TYPE_IMAGE,
    TYPE_LOCAL,
    TYPE_COUNT
};

enum TRSF_TYPE {
    TRSF_PASV,
    TRSF_PORT,
    TRSF_COUNT,
};

#endif
