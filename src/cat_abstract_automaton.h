#ifndef CAT_ABSTRACT_AUTOMATON_H
#define CAT_ABSTRACT_AUTOMATON_H
#include"common_include.h"
#include"cat_xfa_defines.h"
struct cat_automaton_node
{
public:
    int id;
    bool is_accepted;
};
struct cat_automaton_edge
{
    int next_node_id;
    int response;
    int process_length;


    bool operator <(const cat_automaton_edge& node)const
    {
        if(process_length!=node.process_length)
            return process_length<node.process_length;
        if(response!=node.response)
            return response<node.response;
        if(process_length!=node.process_length)
            return process_length<node.process_length;
        return true;
    }
};

struct cat_automaton_op_dict
{
    map<int ,int > op_loc;
    int get_edges_loc(int op)
    {
        if(op_loc.find(op)!=op_loc.end())
            return cat_xfa_defines::NOT_FOUND;
        else
            return op_loc[op];
    }
    bool find(int op)
    {
        return op_loc.find(op)!=op_loc.end();
    }
};
struct cat_io_automaton_op
{
    vector<cat_automaton_edge> out_going_edges;
    set<cat_automaton_edge > can_go_to;
    void add_edge(cat_automaton_edge& e)
    {
        if(can_go_to.find(e)==can_go_to.end())
        {
            can_go_to.insert(e);
            out_going_edges.push_back(e);
        }
    }
    void append_edges(vector<cat_automaton_edge>&edges)
    {
        for(cat_automaton_edge& e:out_going_edges)
        {
            edges.push_back(e);
        }
    }
};
struct cat_io_automaton_cell:public cat_automaton_node
{
    cat_automaton_op_dict op_dict;
    vector<cat_io_automaton_op> ops;
    void set_ops(int op,cat_io_automaton_op data)
    {
        if(!op_dict.find(op))
        {
            op_dict.op_loc[op]=ops.size();
            ops.push_back(data);
        }
        ops[op_dict.get_edges_loc(op)]=data;
    }


    void add_op(int op,cat_automaton_edge e)
    {
        if(!op_dict.find(op))
        {
            op_dict.op_loc[op]=ops.size();
            ops.push_back(cat_io_automaton_op());
        }
        cat_io_automaton_op&o=ops[op_dict.get_edges_loc(op)];
        o.add_edge(e);
    }


    void set_null_op(cat_io_automaton_op data)
    {
        set_ops(cat_xfa_defines::CMD_NULL,data);
    }

    void collect(int op,vector<cat_automaton_edge>& ret)
    {
        if(op_dict.find(op))
        {
            cat_io_automaton_op&o=ops[op_dict.get_edges_loc(op)];
            o.append_edges(ret);
        }
        if(op!=cat_xfa_defines::CMD_NULL)
        {
            collect(cat_xfa_defines::CMD_NULL,ret);
        }
    }
};
struct node_config
{

};
struct cat_io_automaton
{
    int start_stat_id;
    vector<cat_io_automaton_cell > nodes;
    int node_count;
    set<int > accept_nodes;

    /// make nodes order fits the e edged
    void null_dfs(int node,vector<int > visit,int vid)
    {

    }
public:
    cat_io_automaton();

    cat_io_automaton operator |(const cat_io_automaton& m)const
    {
        cat_io_automaton ret_fsm;
        cat_io_automaton_cell cell;
    }
    void add_node()
    {
        cat_io_automaton_cell node;
        node.id=node_count;
        nodes.push_back(node);
    }
    void set_accept(int node_id)
    {
        cat_io_automaton_cell & n=nodes.at(node_id);
        n.is_accepted=true;
        accept_nodes.insert(node_id);

    }

    void add_edge(int from,int to,int input,int output)
    {
        cat_automaton_edge e;
        e.next_node_id=to;
        if(input==cat_xfa_defines::CMD_NULL)
        {
            e.process_length=0;
        }
        else
            e.process_length=1;
        e.next_node_id=to;
        e.response=output;

        cat_io_automaton_cell& node=nodes[from];
        node.add_op(input,e);
    }

    void null_topology_sort()
    {

    }
};
///
/// \brief The cat_io_automaton_searcher class
///a search instance
struct automaton_process_state_hash
{
    long long hash;
    int processed_length;
    int hash_base;
    int output_size;

    bool operator <(const automaton_process_state_hash& n)const
    {
        if(processed_length!=n.processed_length)
        {
            return processed_length<n.processed_length;
        }
        ///we ignore hash conflicts here
        if(hash==n.hash)
        {
            if(output_size==n.output_size)
            {
                return false;
            }
            else
                return output_size<n.output_size;
        }
        else
            return hash<n.hash;

    }
    automaton_process_state_hash grow(int character)
    {
        automaton_process_state_hash s;
        s=*this;
        if(character==cat_xfa_defines::CMD_NULL)
        {
            return s;
        }
        s.output_size++;
        s.hash*=hash_base;
        s.hash%=cat_xfa_defines::HASH_FACTOR;
        s.hash+=character;
        s.hash%=cat_xfa_defines::HASH_FACTOR;
    }
};

////io fsm won't contain episilon loop with output
/// thus it only accepts strings of a finite set
///
struct automaton_process_state
{
    vector<int > output_str;
    ///called only when two with the same hash and same size
    bool adv_cmp(const automaton_process_state& n)const
    {
        for(int i=0;i<output_str.size();i++)
        {
            if(output_str[i]<n.output_str[i])
                return true;
            else if(output_str[i]>n.output_str[i])
                return false;
        }
    }
    automaton_process_state grow(int character)
    {
        automaton_process_state s=*this;
        if(character!=cat_xfa_defines::CMD_NULL)
        s.output_str.push_back(character);
    }
};
struct automaton_node_state
{
    vector<automaton_process_state> states;
    vector<automaton_process_state_hash> hashs;
    map<automaton_process_state_hash,int > locs;
    bool has_state(automaton_process_state_hash &h)
    {
        return locs.find(h)!=locs.end();
    }
    void add_state(const automaton_process_state_hash &h,const automaton_process_state&s)
    {
        locs[h]=states.size();
        states.push_back(s);
        hashs.push_back(h);
    }
    void clear()
    {
        states.clear();
        hashs.clear();
        locs.clear();
    }


};


class cat_io_automaton_searcher
{
    vector<vector<int > > accepted_str;

    vector <automaton_node_state> states[2];
    cat_io_automaton machine;
    int current,next;

    void set_automaton(cat_io_automaton& m)
    {
        this->machine=m;
        states[0].resize(m.node_count);
        states[1].resize(m.node_count);
    }
    //call with topology order pls;
    void process_trans(int node_id,int charcter)
    {
        vector<cat_automaton_edge > next_edges;
        cat_io_automaton_cell& n=machine.nodes[node_id];
        automaton_node_state &current_node_status=states[current][node_id];

        for(int i=0;i<next_edges.size();i++)
        {
            cat_automaton_edge&e=next_edges[i];
            int target_stat=(e.process_length==0);
            for(int i=0;i<current_node_status.states.size();i++)
            {
                automaton_process_state& current_process_state=current_node_status.states[i];
                automaton_process_state_hash&  current_process_state_hash=current_node_status.hashs[i];

                automaton_node_state &next_node_status=states[target_stat][e.next_node_id];
                automaton_process_state_hash next_hash=current_process_state_hash.grow(charcter);
                if(next_node_status.has_state(next_hash))
                {
                    continue;
                }
                next_node_status.add_state(next_hash,current_process_state.grow(charcter));
            }
        }
    }
    void collect(set<int >& output_hash,vector<vector<int > >&outputs)
    {
        for(int t:machine.accept_nodes)
        {
             automaton_node_state &node_state=states[current][t];
             for(int i=0;i<node_state.states.size();i++)
             {
                 automaton_process_state_hash& hash=node_state.hashs[i];
                 automaton_process_state& s=node_state.states[i];
                 if(output_hash.find(hash.hash)==output_hash.end())
                 {
                     output_hash.insert(hash.hash);
                     outputs.push_back(s.output_str);
                 }
             }
        }
    }
    void process_trans(int character)
    {
        for(int i=0;i<machine.node_count;i++)
        {
            if(character!=cat_xfa_defines::CMD_NULL)
            process_trans(i,cat_xfa_defines::CMD_NULL);
            process_trans(i,character);
        }
        current^=1;
        next^=1;
        for(int i=0;i<machine.node_count;i++)
        {
            automaton_node_state &node_state=states[next][i];
            node_state.clear();
        }
    }
    cat_io_automaton compose(cat_io_automaton& pre,cat_io_automaton& post)
    {

    }
    void process(vector<int > input_str,vvi& output_strings)
    {
        for(int i=0;i<input_str.size();i++)
        {
            process_trans(input_str[i]);
        }
        process_trans(cat_xfa_defines::CMD_NULL);
        set<int > output_hash;
        collect(output_hash,output_strings);
    }
};


#endif // CAT_ABSTRACT_AUTOMATON_H
