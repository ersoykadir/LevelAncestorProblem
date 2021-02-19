#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
using namespace std;

class Node{
public:
    int id;
    int parentID;
    int label;
    int depth;
    Node(int id,int parentID);
    vector<Node*> children;
};
Node::Node(int id,int parentID=-1) {
    this->id = id;
    this->parentID = parentID;
}
int searchForAncestor(int id,int n);
void processTree(vector<Node*> &tree, vector<vector<int>> &dynamicArrays,unordered_map<int,Node*> &hashTable, Node* root, int* counter,int depth);
int main(int argc, char const *argv[])
{
    string infile_name = argv[1];//READ INPUT FILE NAME
    string outfile_name = argv[2];//READ OUTPUT FILE NAME

    //OPEN INPUT AND OUTPUT FILE STREAMS
    ifstream infile;
    infile.open(infile_name);
    ofstream outfile;
    outfile.open(outfile_name);

    int numOfPeople;
    infile >> numOfPeople;
    vector<Node*>tree;
    //int * tree = new int[numOfPeople];
    for (int i = 0; i < numOfPeople; ++i)
    {
        int parent;
        infile >> parent;
        Node* n = new Node(i,parent);
        if(tree.size()>parent){
            tree[parent]->children.push_back(n);
        }
        //tree.push_back(make_pair(e,-1));
        tree.push_back(n);
    }
    vector<vector<int>> dynamicArrays;
    unordered_map<int,Node*> hashTable;
    //cout << dynamicArrays.size() << endl;
    int counter = 0;
    processTree(tree,dynamicArrays,hashTable,tree[0],&counter,0);
    cout << "hello " << endl;
    int queries;
    infile >> queries;
    while(queries > 0){
        queries--;
        int id,n;
        infile >> id >> n;
        int ancestorID;
        //searchForAncestor(tree[id]->label,n);
        int label = tree[id]->label;
        if((tree[id]->depth)-n < 0){
            outfile << -1 << endl;
            continue;
        }
        vector<int> v = dynamicArrays[(tree[id]->depth)-n];
        int x = -1;
        for (int i = 0; i < v.size(); ++i) {
            if(v[i]>label){
                x = v[i-1];
                break;
            }
        }
        if(x==-1){
            x = v[v.size()-1];
        }
        ancestorID = hashTable[x]->id;
        outfile << ancestorID << endl;
    }
//    for(auto v : dynamicArrays){
//        for(auto n : v){
//            if(hashTable[n]->id==15724){
//                cout << "hereee " << endl;
//            }
//        }
//    }
    //cout << tree[15724]->label << endl;
    return 0;
}
int searchForAncestor(int id,int n){


}
void processTree(vector<Node*> &tree, vector<vector<int>> &dynamicArrays,unordered_map<int,Node*> &hashTable, Node* root, int* counter,int depth){
    //hash table from label to id
    //process itself
    // while loop and process children recursively
    //if() return;
    (*counter)++;
    tree[root->id]->label = *counter;
    //tree[root].second = *counter;
    tree[root->id]->depth = depth;
    if(dynamicArrays.size() > depth){
        dynamicArrays[depth].push_back(*counter);
    }
    else{
        vector<int> v;
        v.push_back(*counter);
        dynamicArrays.push_back(v);
    }

    hashTable[*counter] = tree[root->id];

    //int id = 0;
    for(auto node : tree[root->id]->children){
        processTree(tree,dynamicArrays,hashTable,node,counter,++depth);
        depth--;
        //id++;
    }
//    for(auto node : tree){
//        if(node.first == root){
//            processTree(tree,dynamicArrays,hashTable,id,counter,++depth);
//            //counter++;
//            depth--;
//        }
//        id++;
//    }

}