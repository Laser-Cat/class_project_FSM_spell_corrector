#ifndef CAT_XFA_FACTORY_H
#define CAT_XFA_FACTORY_H
#include"cat_abstract_automa.h"
#include"cat_abstract_automaton.h"

///going to use json to describe a dfa.
class typo_prob
{
    double prob[1000][1000];
    double get_prob(int a, int b)
    {
        return 1.0;
    }
};

struct codec_ascii
{
    void encode(const string& src,vi&dst)
    {
        dst.clear();
        for(char c:src)
            dst.push_back(c);
    }
    void decode(vi& src,string& dst)
    {
        dst="";
        for(int c:src)
            if(c!=cat_xfa_defines::CMD_NULL)
            dst+=c;
    }
};
class cat_abstract_automaton_factory
{
public:
    virtual int  load_automaton(string file_name,void* automaton )=0;
    virtual int  save_automaton(string file_name,void* automaton)=0;

};

struct io_automaton_factory
{
    static cat_io_automaton* make_transducer(vector<int > char_set,int modification_no)
    {
        cat_io_automaton* trans=new cat_io_automaton;
        trans->add_node();
        trans->set_accept(0);
        for(int i=0;i<modification_no;i++)
        {
            trans->add_node();
            trans->set_accept(i+1);
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
        return trans;

    }
    static void add_to_dict(cat_io_automaton_searcher& s,vi& str)
    {
        int current_id=0;
        int next_id;
        vector<int > next;
        vector<int > baz;
        for(int i=0;i<str.size();i++)
        {
            next.clear();
            baz.clear();
            if(!s.next_(current_id,str[i],next,baz))
            {
               next_id=s.get_machine()->add_node();
               s.get_machine()->add_edge(current_id,next_id,str[i],str[i]);
            }
            else
            {
                next_id=next[0];
            }
            current_id=next_id;
        }
        s.get_machine()->set_accept(current_id);
    }
    static cat_io_automaton* make_dict(vvi& strings)
    {
        cat_io_automaton_searcher s;
        cat_io_automaton* a;
        a=new cat_io_automaton;
        a->add_node();
        s.set_automaton(*a);
        for(int i=0;i<strings.size();i++)
        {
            add_to_dict(s,strings[i]);
        }
        *a=*(s.get_machine());
        return a;
    }
    static cat_io_automaton* make_ascii_dict(vector<string >& words)
    {
        vvi _words;
        codec_ascii c;
        for(string &s:words)
        {
            vi tmp;
            c.encode(s,tmp);
            _words.push_back(tmp);
        }
        return make_dict(_words);
    }
    static cat_io_automaton* make_ascii_dict(string word_path)
    {
        FILE* fp=fopen(word_path.c_str(),"r");
        vector<string > words;
        char buf[1000];
        while(fscanf(fp,"%s",buf)==1)
        {
            words.push_back(buf);
        }
        return make_ascii_dict(words);

    }
    static cat_io_automaton* make_ascii_transducer()
    {
        vector<int >char_set;
        for(int i='a';i<='z';i++)
        {
            char_set.push_back(i);
        }
/*
        for(int i='A';i<='Z';i++)
        {
            char_set.push_back(i);
        }*/
        return make_transducer(char_set,1);
    }

};


#endif // CAT_XFA_FACTORY_H
