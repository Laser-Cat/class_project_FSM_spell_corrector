#ifndef CAT_FSM_H
#define CAT_FSM_H
#include"cat_abstract_automa.h"
///
/// \brief The cat_dict_automata struct
///
class trie:public cat_abstract_automa_core
{
    int match_word(vector<int> &s)
    {
        for(int i=0;i<s.size();i++)
        {
            int tmp_stat=next(s[i]);
            if(tmp_stat<0)
            {
                return i;
            }
            current_status=tmp_stat;
        }
        return s.size();
    }
    int grow_node(int op)
    {
        int new_id=add_node();
        cat_abstract_automa_cell& c=*(status[current_status]);
        c.add_next(op,new_id);
        current_status=next(op);
        return cat_xfa_defines::OKAY;
    }
public:
    int test_and_add_word(vector<int> &s)
    {
        int match_offset;
        current_status=enterance_status;
        if((match_offset=test_word(s))==s.size())
        {
            return cat_xfa_defines::FOUND;
        }
        for(--match_offset;match_offset<s.size();match_offset++)
        {
            grow_node(s[match_offset]);
        }
        set_acceptance(current_status);
        return cat_xfa_defines::NOT_FOUND;
    }
    bool test_word(vector<int >& s)
    {
        current_status=enterance_status;
        if(match_word(s)==s.size())
        {
            return cat_xfa_defines::ACCEPTED==test_accepted();
        }
    }


};

struct cat_dict_automata
{

};

#endif // CAT_FSM_H
