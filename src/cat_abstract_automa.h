#ifndef CAT_ABSTRACT_AUTOMA_H
#define CAT_ABSTRACT_AUTOMA_H
#include"common_include.h"
#include"cat_xfa_defines.h"
class cat_abstract_automa_cell
{
protected:
    int id;
    bool is_accepted;
    vvi next_status;
    mat<int ,int > next_status_locs;
    /// this is quick, but you need to make sure no repeating
    /// element involved....
    int ___add_next(vi& array,int next)
    {
        array.push_back(target);
        return cat_xfa_defines::OKAY;
    }
    ///add assist ds to accelerate this~
    /// that assume you DONT connect more that 1000 targets behind one input.

    int __add_next(vi& array,int next)
    {
        for(int next:default_next)
        {
            if(next==default_next)
            {
                return cat_xfa_defines::OKAY;                 ;
            }
        }
        return ___add_next(array,next);
    }

public:
    ///in case some guy may want to make a stupid GUI
    /// to build the DAMN Automaton ^_<
    /// so we have this incremental build method to you..

    /// you can also extend it to a AC automaton
    /// or a Trie
    int set_id(int id)
    {
        this->id=id;
        return cat_xfa_defines::OKAY;
    }
    int set_accepted(int is_accepted)
    {
        this->is_accepted=is_accepted;
        return cat_xfa_defines::OKAY;

    }
    int add_next(int op,int next)
    {
        if(next_status_locs.find(op)==next_status_locs.end())
        {
            return __add_next(next_status_locs[op],next);
        }
    }
    int add_next(int op,vi & next_status)
    {
        int flag;
        for(int i:next_status)
        {
            if((flag=add_next(op,i)!=cat_xfa_defines::OKAY))
                return flag;
        }
        return cat_xfa_defines::OKAY;
    }
    int next(int op,vi& next_status)
    {
        if(next_status_locs.find(op)==next_status_locs.end())
        {
            return cat_xfa_defines::ERR_ILLEGAL_INPUT;
        }
        next_status=this->next_status[next_status_locs[op]];
        return cat_xfa_defines::OKAY;
    }
    int next(int op,int& next_status,int seq_num=0 )
    {
        if(next_status_locs.find(op)==next_status_locs.end())
        {
            return cat_xfa_defines::ERR_ILLEGAL_INPUT;
        }
        next_status=this->next_status[next_status_locs[op]][seq_num];
        return cat_xfa_defines::OKAY;
    }
    int set(int id , bool accepted,vector<pair<int , vi> >status_transfer)
    {
        int flag;
        if((flag=set_id(id))!=cat_xfa_defines::OKAY)
            return flag;

        if((flag=set_accepted(id))!=cat_xfa_defines::OKAY)
            return flag;
        for(pair<int ,vi> & trans_rule:status_transfer)
        {
            if((flag=add_next(trans_rule.first,trans_rule.second))!=cat_xfa_defines::OKAY)
                return flag;
        }
        this->is_accepted=accepted;
        return cat_xfa_defines::OKAY;

    }
    bool test()
    {
        return  is_accepted;
    }
};

class cat_abstract_automa_core
{
protected:
    int current_status;
    int enterance_status;
    vector<cat_abstract_automa_cell*  >status;
    set<int > operaion_list;
    int node_count;

    void clear()
    {
        for(cat_abstract_automa_cell* p:status)
        {
            delete p;
        }
        status.clear();
    }
    void init()
    {
        node_count=0;
        current_status=cat_xfa_defines::NOT_DEFINED;
        enterance_status=cat_xfa_defines::NOT_DEFINED;

    }
    void reset()
    {
        clear();
        init();
    }
    int set_enterance_node(int node_id=0)
    {
        if(node_id<0||node_id>=node_count)
        {
            return cat_xfa_defines::INDEX_OUT_OF_BOUNDARY;
        }
        enterance_status=node_id;
    }
    int add_node()
    {
        node_count++;
        cat_abstract_automa_cell* new_cell=new cat_abstract_automa_cell(node_count);
        status.push_back(new_cell);
        return cat_xfa_defines::OKAY;
    }
    int add_operation(int op)
    {
        operaion_list.insert(op);
    }
    int add_transfer(int sid,int op, vi& targets)
    {
        if(sid<0||sid>=status.size())
        {
            return cat_xfa_defines::INDEX_OUT_OF_BOUNDARY;
        }
        cat_abstract_automa_cell& c=*(status[sid]);

        return c.add_next(op,targets);
    }
    int add_transfer(int sid,int op, int& target)
    {
        if(sid<0||sid>=status.size())
        {
            return cat_xfa_defines::INDEX_OUT_OF_BOUNDARY;
        }
        cat_abstract_automa_cell& c=*(status[sid]);
        return c.add_next(op,target);
    }
    int set_acceptance(int node_id,int acc=cat_xfa_defines::ACCEPTED)
    {
        try
        {
            cat_abstract_automa_cell* tar=status.at(node_id);
            return tar->set_accepted(acc);
        }
        catch(...)
        {
            return cat_xfa_defines::UNKNOW_ERROR;
        }
    }
    int test_accepted(int node_id=current_status)
    {
        try
        {
            cat_abstract_automa_cell* tar=status.at(node_id);
            return tar->is_accepted();
        }
        catch(...)
        {
            return cat_xfa_defines::UNKNOW_ERROR;
        }
    }
    cat_abstract_automa_core()
    {
        init();
    }

    ~cat_abstract_automa_core()
    {
        clear();
    }
    int next_possible_status(int op, vi& next_status)
    {
        cat_abstract_automa_cell& c=*(status[current_status]);
        return c.next(op,next_status);
    }
    int next(int op,int seq_id=0)
    {
        cat_abstract_automa_cell& c=*(status[current_status]);
        return c.next(op,current_status,seq_id);
    }
    int get_enterance_id()
    {
        return enterance_status;
    }
    void set_current_status(int status_id)
    {
        current_status=status_id;
    }

};

#endif // CAT_ABSTRACT_AUTOMA_H
