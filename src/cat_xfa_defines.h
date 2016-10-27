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
    static int WRONG_ANSWER;

    static int HASH_FACTOR;

    cat_xfa_defines();
};


#endif // CAT_XFA_DEFINES_H
