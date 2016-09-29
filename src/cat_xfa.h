#ifndef CAT_XFA_H
#define CAT_XFA_H
#include"cat_abstract_automa.h"
/*
 * The programming homework....
 *
class cat_NFA: public cat_abstract_automa_core
{
    virtual int evaluate_string(bool& result,vi &input_string)
    {

    }
};
//// DFAs are some special NFAs
class cat_DFA:public cat_abstract_automa_core
{
    void add_id_to_hash(string& hash,int id)
    {
        char buf[10];
        sprintf(buf,"%d#",id);
        buf+=id;
    }

    int set_to_string(string &hash,set<int >& s)
    {
        hash="";
        for(int i:s)
        {
            add_id_to_hash(hash,i);
        }
        return cat_xfa_defines::OKAY;
    }
    int set_from_string(string&hash,set<int >& s)
    {
        int weight=1;
        int id=0;
        for(int i=hash.size()-1;i>=0;i--)
        {
            if(hash[i]=='#')
            {
                s.insert(id);
                id=0;
                weight[i]=1;
                continue;
            }
            id+=weight*(hash[i]-'0');
            weight*=10;
        }
        return cat_xfa_defines::OKAY;
    }
    int fix_with_trap()
    {

    }

public:
    int from_NFA(cat_NFA& nfa,vector<set<int > >status_mapping)
    {
        queue<string  > open_list;
        map<string ,int> visited;
        string init_list;

        string current_status;
        string next_status;

        if(nfa.get_enterance_id()<0)
        {
            return cat_xfa_defines::INVALID_ENTERANCE_ID;
        }
        add_id_to_hash(init_list,nfa.get_enterance_id());
        while (!open_list.empty())
        {
            current_status=open_list
        }
    }
};

*/
#endif // CAT_XFA_H
