#ifndef CAT_XFA_FACTORY_H
#define CAT_XFA_FACTORY_H
#include"cat_abstract_automa.h"
#include"cat_abstract_automaton.h"

///going to use json to describe a dfa.
class cat_abstract_automaton_factory
{
public:
    virtual int  load_automaton(string file_name,void* automaton )=0;
    virtual int  save_automaton(string file_name,void* automaton)=0;

};

class io_automaton_factory
{
    static cat_io_automaton* make_transducer(vector<int > char_set,int modification_no)
    {
        cat_io_automaton* trans=new cat_io_automaton;
        trans->add_node();
        for(int i=0;i<modification_no;i++)
        {
            trans->add_node();
            trans->set_accept(i);
        }
        for(int i=0;i<modification_no;i++)
        {
            for(int ic:char_set)
            {
                for(int oc:char_set)
                {
                    if(ic==oc)
                    {
                      trans->add_edge(i,i,ic,oc);
                    }
                    else
                    {
                        trans->add_edge(i,i+1,ic,oc);
                    }
                }
                trans->add_edge(i,i+1,cat_xfa_defines::CMD_NULL,ic);
                trans->add_edge(i,i+1,ic,cat_xfa_defines::CMD_NULL);
            }
        }

        for(int i=0;i<modification_no;i++)
        {
            for(int ic:char_set)
            {
                trans->add_edge(modification_no,modification_no,ic,ic);
            }
        }

    }
};

#endif // CAT_XFA_FACTORY_H
