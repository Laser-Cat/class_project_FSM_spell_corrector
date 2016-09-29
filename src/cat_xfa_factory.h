#ifndef CAT_XFA_FACTORY_H
#define CAT_XFA_FACTORY_H
#include"cat_abstract_automa.h"
///going to use json to describe a dfa.
class cat_abstract_automaton_factory
{
public:
    virtual int  load_automaton(string file_name,void* automaton )=0;
    virtual int  save_automaton(string file_name,void* automaton)=0;

};

#endif // CAT_XFA_FACTORY_H
