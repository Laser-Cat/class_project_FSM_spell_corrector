#ifndef CAT_INDEXED_SPARSE_LIST_H
#define CAT_INDEXED_SPARSE_LIST_H
#include"common_include.h"
class cat_indexed_sparse_list
{
    map<int,int > index;
public:
    vector<int > body;
    int insert(int t)
    {
        if(index.find(t)!=index.end())
        {
            return index[t];
        }
        index[t]=body.size();
        body.push_back(t);
        return index[t];
    }
};

#endif // CAT_INDEXED_SPARSE_LIST_H
