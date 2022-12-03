#ifndef __CONCAT_STRING_TREE_H__
#define __CONCAT_STRING_TREE_H__

#include "main.h"

int power(int, int);
string reverseStr(string);
int Max(int, int);
int Floor(float);

class ParentTree;

static int glob_id = 0;
static int glob_id_2 = 0;
const int lim = 10000000;
enum Status_Type {NIL, NON_EMPTY, DELETED};

class PNode;//forward declaration
class Node;//forward declaration
class LitStringHash; // forward declaration

class ParentTree
{
    public:
    PNode* root;
    int count;
    ParentTree()
    {
        root = NULL;
        count = 0;
    }
    //methods
    int get_Height(PNode*);
    int getBalance(PNode*);
    PNode* insertNode(PNode*, int);//may need redeclare
    string PreorderUtil(PNode*) const;
    PNode* newNode(int);
    PNode* rightRotate(PNode*);
    PNode* leftRotate(PNode*);
    PNode* maxNode(PNode*);
    PNode* deleteNode(PNode*,int); //may need redeclare
    void deep_cop(PNode*, PNode**) const;
    //requirement methods
    int size();
    string toStringPreOrder() const;

    void recursiveDelete(PNode*  );
    ~ParentTree();
};

class Node
{
    public:
    int leftLength;
    int leng;
    int id;
    string data;
    Node* left;
    Node* right;
    ParentTree parent;
    Node(bool is_red );
    Node(const char* s, bool is_red );

    ~Node();
};

class ConcatStringTree {

public:
    LitStringHash * litStringHash;
    Node* root;
    
    int height;
    bool isReduced;
    bool is_special;

    ConcatStringTree();
    ConcatStringTree(const char * s);
    ConcatStringTree(const ConcatStringTree& other);
    int length() const;
    char get(int index) const;
    int indexUtil(Node*, char) const;
    int indexOf(char) const;
    string preOrderUtil(const Node*) const;
    string toStringPreOrder() const;
    string inOrderUtil(const Node*) const;
    string toString() const;
    ConcatStringTree concat(const ConcatStringTree & otherS) const;
    void deep_Copy(Node*, Node**) const;
    void subUtil(Node*, int, int, int&);
    void delEmpty(Node** rot);
    void upDate(Node** rot);
    ConcatStringTree subString(int, int) const;
    void deep_Copy_reverse(Node*, Node**) const;
    ConcatStringTree reverse() const;    
    int getParTreeSize(const string & query) const;
    string getParTreeStringPreOrder(const string & query) const;
    void recurDelete(Node *);
    void checkToDelete(Node*);
    void checkToDelete_Reduced(Node*);

    ~ConcatStringTree();
};

class PNode
{
    public:
    int key;
    PNode* left;
    PNode* right;
    int height;
    friend class ParentTree;
    public:
    PNode()
    {
        key = -99;
        left = right = NULL;
        height = 1;
    }
    PNode(int id)
    {  
        key = id;
        left = right = NULL;
        height = 1;
    }
    
};

class ReducedConcatStringTree; // forward declaration
class LitStringHash; // forward declaration

class HashConfig {
private:
    int p;
    double c1, c2;
    double lambda;
    double alpha;
    int initSize;
    
    friend class ReducedConcatStringTree;
    friend class LitStringHash;
    public:
    HashConfig(int p, double c1, double c2, double lambda, double alpha, int initSize)
    {
        this->p = p;
        this->c1 = c1;
        this->c2 = c2;
        this->lambda = lambda;
        this->alpha = alpha;
        this->initSize = initSize;
    }

};

class LitStringHash 
{
public:
    class LitString; //forward declaration

    LitString* table;
    Status_Type* status;
    int capacity;
    int count;
    float loadFactor;
    Node* lastNode;

    int p;
    double c1, c2;
    double lambda;
    double alpha;
    
public:
    LitStringHash(const HashConfig & hashConfig);

    bool empty();
    int size();
    int hashFunc(string) const;
    int quadHash(string, int) const;
    void insert(Node*);
    LitString search(string);

    void deleteLit(string);

    int getIndexOf(string) const;
    void reHash(int newCapacity);
    int getLastInsertedIndex() const;
    string toString() const;

    ~LitStringHash();
public:
    class LitString
    {
        public:
        Node* data;
        string str;
        int num_link;
        friend class LitStringHash;
        
        LitString()
        {
            this->data = NULL;
            str = "";
            num_link=0;
        }

        LitString(Node* newNode)
        {
            this->data = newNode;
            str = newNode->data;
            num_link = 1;
        }



    };
};

class ReducedConcatStringTree : public ConcatStringTree
{
public:
    
    ReducedConcatStringTree();
    ReducedConcatStringTree(const char * s, LitStringHash * litStringHash);
    ReducedConcatStringTree concat(const ReducedConcatStringTree & otherS) const;

};


#endif // __CONCAT_STRING_TREE_H__