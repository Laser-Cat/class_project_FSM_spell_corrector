#ifndef CAT_FSM_H
#define CAT_FSM_H
#include<bits/stdc++.h>
using namespace std;

struct cat_fsm_process_result
{
    int targe_state;
    int response;
};

class cat_abstract_automaton
{
public:
    void add_edge(int from,int to,int input,void* data);
    int add_node();

};

class cat_fsm:public cat_abstract_automaton
{
public:
    cat_fsm_process_result process(int status,int response);
    cat_fsm();
    cat_fsm operator |(const cat_fsm& m)const
    {
        cat_fsm ret_fsm;
        
    }

};

#endif // CAT_FSM_H
