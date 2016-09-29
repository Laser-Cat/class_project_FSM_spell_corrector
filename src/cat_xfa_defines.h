#ifndef CAT_XFA_DEFINES_H
#define CAT_XFA_DEFINES_H


struct  cat_xfa_defines
{
public:
    static int ERR_ILLEGAL_INPUT;
    static int OKAY;
    static int CMD_RESET;
    static int CMD_DEFAULT;
    static int CMD_NULL;

    static int NOT_DEFINED;
    static int INDEX_OUT_OF_BOUNDARY;
    static int INVALID_ENTERANCE_ID;

    static int NOT_FOUND;
    static int FOUND;

    static int UNKNOW_ERROR;

    static char SPLITER;

    static int ACCEPTED;

    cat_xfa_defines();
};

char cat_xfa_defines::SPLITER='#';


int cat_xfa_defines::NOT_FOUND=0;

int cat_xfa_defines::FOUND=1;


int cat_xfa_defines::ACCEPTED=1;

int cat_xfa_defines::UNKNOW_ERROR=-9;

int cat_xfa_defines::ERR_ILLEGAL_INPUT=-4869;

int cat_xfa_defines::INVALID_ENTERANCE_ID=-4368;

int cat_xfa_defines::OKAY=-0502;

int cat_xfa_defines::CMD_DEFAULT=-10032;

int cat_xfa_defines::CMD_NULL=-0504;


int cat_xfa_defines::CMD_RESET=-486;

int cat_xfa_defines::NOT_DEFINED=-20003;

int cat_xfa_defines::INDEX_OUT_OF_BOUNDARY=-20001;

#endif // CAT_XFA_DEFINES_H
