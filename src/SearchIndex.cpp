#include<SearchIndex.h>

void SearchIndex::add(string path, FileNode* nodePtr){

    if(nodePtr==NULL) return;

    SearchResult newEntry(path,nodePtr);

    fileIndex[nodePtr->fileName].push_back(newEntry);
}

void SearchIndex::remove(FileNode* nodeToRemove){
    if(nodeToRemove==NULL) return;

    string name=nodeToRemove->fileName;
    if(fileIndex.find(name)==fileIndex.end()){
        return;
    }

    vector<SearchResult>&find=fileIndex[name];//as we taken refrence ...when we make change in find it will directly reflect in map's vector

    for(int i=0;i<find.size();i++){
        if(find[i].nodePtr==nodeToRemove){
            find.erase(find.begin()+i);
            break;
        }
    }
    if (find.empty()) {
        fileIndex.erase(name);
    }
}

vector<SearchResult> SearchIndex::find(string name) {
    // 1. Use .find() to check if the key exists in the map
    if (fileIndex.find(name) == fileIndex.end()) {
        // Not found, return a new, empty vector
        return std::vector<SearchResult>();
    }
    
    // 2. The key exists, so return the vector of results
    return fileIndex[name];
}