#include <iostream>

using namespace std;
#include"src/cat_xfa_factory.h"
class corrector
    {
    cat_io_automaton* transducer;
    cat_io_automaton_searcher s_trans;
    codec_ascii a;
    cat_io_automaton_searcher s_dict;
    cat_io_automaton* dict;
public:
    void init()
    {
        transducer=io_automaton_factory::make_ascii_transducer();
        s_trans.set_automaton(*transducer);
        dict=io_automaton_factory::make_ascii_dict("wordlist");
        s_dict.set_automaton(*dict);

    }
    int correct(string s)
    {
        vi in;
        vvi out;
        a.encode(s,in);
        out.clear();
        s_trans.process(in,out);
        vvi out2;
        set<string >ans;
        for(vi & o:out)
        {
            out2.clear();
            s_dict.process(o,out2);
            for(vi oo:out2)
            {
                string s;
                a.decode(oo,s);
                ans.insert(s);
            }
        }
        for(const string &s_:ans)
        {
            cout<<s_<<endl;
        }
        cout << "Hello World!" << endl;
        return 0;
    }
};
int main()
{
    corrector c;
    c.init();
    char buff[30];
    while( scanf("%s",buff)==1)
    {
        c.correct(buff);
    }
}
