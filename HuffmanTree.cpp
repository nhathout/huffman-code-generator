#include "HuffmanTree.h"
#include <fstream>
#include <unordered_map>

using namespace std;

// Function to create a new Huffman tree node
Node* createNode(string data, int freq, Node* left, Node* right) {
    Node* node = new Node();
    node->data = data;
    node->freq = freq;
    node->left = left;
    node->right = right;
    return node;
}

// Build the Huffman tree from characters and their frequencies
void HuffmanTree::buildTree(char* characters, int* freq, int size) {
    priority_queue<Node*, vector<Node*>, NodeComparator> pq;

    char temp;
    string str;

    // Ensure characters with equal frequencies are sorted
    for (int i = 1; i < size; i++) {
        if (freq[i - 1] == freq[i]) {
            temp = characters[i - 1];
            characters[i - 1] = characters[i];
            characters[i] = temp;
        }
    }

    unordered_map<char, int> frequencyMap;
    for (int i = 0; i < size; i++) {
        frequencyMap[characters[i]] = freq[i];
        charList.push_back(characters[i]);
    }

    // Create initial nodes for characters and insert them into the priority queue
    for (auto pair : frequencyMap) {
        string s(1, pair.first);
        pq.push(createNode(s, pair.second, nullptr, nullptr));
    }

    // Build the Huffman tree by merging nodes
    while (pq.size() != 1) {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();

        int sum = left->freq + right->freq;
        str = left->data + right->data;
        pq.push(createNode(str, sum, left, right));
    }

    this->root = pq.top();
    this->pq = pq;
    this->size = size;
}

void HuffmanTree::printCodes() {
    vector<pair<string, char>> huffmanCodes; // Store Huffman codes and characters

    Node* temp = this->root;
    for (int x = size - 1; x >= 0; x--) {
        temp = this->root;
        string s = string(1, this->charList[x]);
        string huff = "";

        // Traverse the tree to find Huffman codes
        while (s != temp->data) {
            if (s == temp->left->data) {
                huff += "0";
                codeMap.insert({ huff, this->charList[x] });
                break;
            } else if (s == temp->right->data) {
                huff += "1";
                codeMap.insert({ huff, this->charList[x] });
                break;
            } else if (temp->left->data.find(s) != string::npos) {
                temp = temp->left;
                huff += "0";
            } else if (temp->right->data.find(s) != string::npos) {
                temp = temp->right;
                huff += "1";
            }
        }
        huffmanCodes.push_back({huff, this->charList[x]});
    }

    // Sort Huffman codes and characters in tree order
    sort(huffmanCodes.begin(), huffmanCodes.end());

    for (const auto& codePair : huffmanCodes) {
        cout << codePair.second << " " << codePair.first << endl;
    }
}

// Decode Huffman encoded text from a file
void HuffmanTree::decodeFile(string fileName) {
    multimap<string, char>::iterator itr;

    ifstream file(fileName);
    string encodedText;
    getline(file, encodedText);

    string temp = "";

    cout << endl;
    for (int i = 0; i < encodedText.length(); i++) {
        temp += encodedText[i];
        for (itr = codeMap.begin(); itr != codeMap.end(); ++itr) {
            if (temp == itr->first) {
                cout << itr->second;
                temp = "";
            }
        }
    }
    cout << endl;
}
