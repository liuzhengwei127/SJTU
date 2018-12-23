#include <string>

using namespace std;

class Dictionary
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

    bool repsearch(string word, Node* node)
    {
        for (unsigned i=0;i<word.size();i++)
        {
            if (word[i] != '*')
            {
                auto it = node->children.find(word[i]);
                if (it == node->children.end())
                    return false;
                else
                    node = it->second;
            }
            else
            {
                for (auto it = node->children.begin();it != node->children.end();it++)
                {
                    string repword = word.substr(i+1,word.size());
                    if (repsearch(repword,it->second))
                        return true;
                }
                return false;
            }
        }

        if (node->isend)
            return true;
        else
            return false;
    }
public:
    Dictionary()
    {
        root = new Node();
    }

    ~Dictionary()
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
        return repsearch(word,node);
    }
};
