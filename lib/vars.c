#include "vars.h"

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

