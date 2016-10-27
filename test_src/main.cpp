#include <iostream>

using namespace std;
#include"src/cat_xfa_factory.h"

int main(int argc, char *argv[])
{
    cat_io_automaton* transducer;
    transducer=io_automaton_factory::make_ascii_transducer();
    cat_io_automaton_searcher s;
    s.set_automaton(*transducer);
    vi in;
    vvi out;
    codec_ascii a;
    a.encode("ab",in);
    s.process(in,out);
    for(vi & o:out)
    {
        string candidate;
        a.decode(o,candidate);
        cout<<candidate<<endl;

    }
    cout << "Hello World!" << endl;
    return 0;
}
