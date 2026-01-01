#include "SearchResult.h"
#include<unordered_map>
#include<string>
#include<vector>


class SearchIndex
{
    public:
        unordered_map<string, vector<SearchResult> > fileIndex;

        void add(string path,FileNode* nodePtr);
        void remove(FileNode* nodePtr);
        vector<SearchResult> find(string name);
};
