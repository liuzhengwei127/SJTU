#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <map>
#include <vector>
using namespace std;

struct Node{
    char ch;
    int sum;
    Node* left = NULL;
    Node* right = NULL;
};

struct cmp{
    bool operator()(Node* a,Node* b)
    {
        return a->sum > b->sum;
    }
};

void naiveCopy(string inputFilename, string outputFilename) {
  ofstream ofs(outputFilename.c_str(), ios::out | ios::binary);
  ifstream ifs(inputFilename.c_str(), ios::in | ios::binary);
  char c;
  while (ifs.get(c)) ofs.put(c);
  ofs.close();
  ifs.close();
}

void GenerateHfmcode(map<char,string>& hfmtree, Node* node, string code="")
{
    if (node->left == NULL && node->right == NULL)
    {
        hfmtree[node->ch] = code;
    }
    else
    {
        GenerateHfmcode(hfmtree,node->left,code+"0");
        GenerateHfmcode(hfmtree,node->right,code+"1");
    }
}

void release(Node* node)
{
    if (node == NULL)
        return;
    if (node->left == NULL && node->right == NULL)
    {
        delete node;
    }
    else
    {
        release(node->left);
        release(node->right);
        delete node;
    }
}

void compress(string inputFilename, string outputFilename) {
    ofstream ofs(outputFilename.c_str(), ios::out | ios::binary);
    ifstream ifs(inputFilename.c_str(), ios::in | ios::binary);
    char ch;
    Node* root = NULL;
    map<char,int> ch_count;
    map<char,string> hfmtree;
    priority_queue<Node*, vector<Node*>, cmp> heap;
    while (ifs.get(ch))
    {
        ch_count[ch]++;
    }
    string tmp = to_string(ch_count.size());
    for (unsigned i=0;i<tmp.size();i++)
        ofs << (char)tmp[i];
    ofs<<' ';
    for(auto it = ch_count.begin(); it != ch_count.end(); it++)
    {
        Node* node =new Node{it->first,it->second};
        heap.push(node);
        ofs<<node->ch;
        string tmp = to_string(node->sum);
        for (unsigned i=0;i<tmp.size();i++)
            ofs << (char)tmp[i];
        ofs<<' ';
    }
    while(!heap.empty())
    {
        Node* left = heap.top();
        heap.pop();
        if (!heap.empty())
        {
            Node* right = heap.top();
            heap.pop();
            Node* parent = new Node;
            parent->sum = left->sum + right->sum;
            parent->left = left;
            parent->right = right;
            heap.push(parent);
        }
        else
        {
            root = left;
        }
    }
    if (root != NULL)
        GenerateHfmcode(hfmtree, root);

    ifs.clear(std::ios::goodbit);
    ifs.seekg(std::ios::beg);
    int bit = 7;
    char write = 0;
    while (ifs.get(ch))
    {
        string code = hfmtree[ch];
        for (unsigned i=0;i<code.size();i++)
        {
            if (bit>=0)
            {
                write = write | ((code[i]-'0') << bit);
                bit--;
            }
            if (bit<0)
            {
                ofs<<write;
                bit = 7;
                write=0;
            }
        }
    }
    ofs<<write;
    ofs.close();
    ifs.close();
    release(root);
}

void decompress(string inputFilename, string outputFilename) {
    ofstream ofs(outputFilename.c_str(), ios::out | ios::binary);
    ifstream ifs(inputFilename.c_str(), ios::in | ios::binary);
    char ch;
    int ch_number = 0;
    int total = 0;
    Node* root = NULL;
    map<char,int> ch_count;
    map<char,string> hfmtree;
    priority_queue<Node*, vector<Node*>, cmp> heap;

    string tmp;
    ch = ifs.get();
    while (ch != ' ')
    {
        tmp+=ch;
        ch = ifs.get();
    }
    ch_number = stoi(tmp);

    for (int i=0;i<ch_number;i++)
    {
        ch = ifs.get();
        string tmp;
        char n;
        n = ifs.get();
        while (n != ' ')
        {
            tmp+=n;
            n = ifs.get();
        }
        ch_count[ch]+=stoi(tmp);
    }

    for(auto it = ch_count.begin(); it != ch_count.end(); it++)
    {
        Node* node =new Node{it->first,it->second};
        heap.push(node);
    }
    while(!heap.empty())
    {
        Node* left = heap.top();
        heap.pop();
        if (!heap.empty())
        {
            Node* right = heap.top();
            heap.pop();
            Node* parent = new Node;
            parent->sum = left->sum + right->sum;
            parent->left = left;
            parent->right = right;
            heap.push(parent);
        }
        else
        {
            root = left;
        }
    }

    ch = ifs.get();
    if (root != NULL)
        total = root->sum;
    Node* node = root;
    if (ch_count.size() == 1)
    {
        for (int i=0;i<total;i++)
            ofs << node->ch;
    }
    else
    {
        while (total)
        {
            int bit = 7;
            while (bit>=0)
            {
                if (ch & (1 << bit))
                {
                    node = node->right;
                    bit--;
                }
                else
                {
                    node = node->left;
                    bit--;
                }
                if (node->left == NULL && node->right == NULL)
                {
                    ofs<<node->ch;
                    node = root;
                    total--;
                    if (!total)
                        break;
                }
            }
            ch = ifs.get();
        }
    }
    delete node;
    release(root);
    ofs.close();
    ifs.close();
}

void usage(string prog) {
  cerr << "Usage: " << endl
      << "    " << prog << "[-d] input_file output_file" << endl;
  exit(2);
}

int main(int argc, char* argv[]) {
  int i;
  string inputFilename, outputFilename;
  bool isDecompress = false;
  for (i = 1; i < argc; i++) {
    if (argv[i] == string("-d")) isDecompress = true;
    else if (inputFilename == "") inputFilename = argv[i];
    else if (outputFilename == "") outputFilename = argv[i];
    else usage(argv[0]);
  }
  if (outputFilename == "") usage(argv[0]);
  if (isDecompress) decompress(inputFilename, outputFilename);
  else compress(inputFilename, outputFilename);
  return 0;
}
