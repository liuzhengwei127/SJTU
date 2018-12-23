#include <string>
#include <map>
#include <iostream>

using namespace std;

class Trie
{
private:
    struct Node
    {
        map<char,Node*> children;
        char val;
        bool isend = false;
    };
    Node* root;

    void Free(Node* node)
    {
        for (auto it = node->children.begin();it != node->children.end();it++)
            Free(it->second);
        delete node;
    }
public:
    Trie()
    {
        root = new Node();
    }

    ~Trie()
    {
        Free(root);
    }

    void insert(string word)
    {
        Node* node = root;
        for (unsigned i=0;i<word.size();i++)
        {
            auto it = node->children.find(word[i]);
            if (it == node->children.end())
            {
                Node* newchild = new Node();
                newchild->val = word[i];
                node->children.insert(pair<char,Node*>(word[i],newchild));
                node = node->children[word[i]];
            }
            else
            {
                node = it->second;
            }
        }
        node->isend = true;
    }

    bool search(string word)
    {
        Node* node = root;

        for (unsigned i=0;i<word.size();i++)
        {
            auto it = node->children.find(word[i]);
            if (it == node->children.end())
                return false;
            else
                node = it->second;
        }

        if (node->isend)
            return true;
        else
            return false;
    }
};
