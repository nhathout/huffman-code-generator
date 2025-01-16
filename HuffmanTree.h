#ifndef HuffmanTree_h
#define HuffmanTree_h

#include <iostream>
#include <utility>
#include <queue>
#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <algorithm> 

using namespace std;

struct Node {
    string data;
    int freq;
    Node* left, *right;
};

struct NodeComparator {
    bool operator()(Node* left, Node* right) {
        return left->freq > right->freq;
    }
};

class HuffmanTree {
public:
    Node* root;
    priority_queue<Node*, vector<Node*>, NodeComparator> pq;
    vector<char> charList;
    multimap<string, char> codeMap;
    int size;

    void buildTree(char* characters, int* freq, int size);
    void printCodes();
    void decodeFile(string fileName);
};

#endif
