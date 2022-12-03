#include "ConcatStringTree.h"

////////////// HELPER FUNCTIONS ///////////////

int power(int a,int b)
{
    int res = 1;
    if (b == 0) return res;
    for(int i=0; i<b; i++)
    {
        res = res*a;
    }
    return res;
}

string reverseStr(string str)
{
    string res="";
    for(int i=str.length()-1; i>=0; i--)
    {
        res = res + str[i];
    }
    return res;
}

int Max(int a, int b)
{
    return (a>b)?a:b;
}

double Floor(double num) 
{
    long long n = (long long)num;
    double d = (double)n;
    if (d == num || num >= 0) return d;
    else return d - 1;
}

////////////// NODE ///////////////

Node::Node(bool is_red = false)
{
    leftLength = 0;
    leng = 0;
    data = "";
    left = NULL;
    right = NULL;
    parent = ParentTree();
    if(is_red)
    {
        if(glob_id_2 + 1<lim) id = ++glob_id_2;
        else throw overflow_error("Id is overflow!");
    }
    else 
    {
        if(glob_id + 1<lim) id = ++glob_id;
        else throw overflow_error("Id is overflow!");
    }
    parent.root = parent.insertNode(parent.root, this->id);
    parent.count++;
}

Node::Node(const char* s, bool is_red = false)
{
    leftLength = 0;
    leng = string(s).length();
    data = string(s);
    left = NULL;
    right = NULL;
    parent = ParentTree();
    if(is_red)
    {
        if(glob_id_2 + 1<lim) id = ++glob_id_2;
        else throw overflow_error("Id is overflow!");
    }
    else 
    {
        if(glob_id + 1<lim) id = ++glob_id;
        else throw overflow_error("Id is overflow!");
    }
    parent.root = parent.insertNode(parent.root, this->id);
    parent.count++;
}

Node::~Node()
{
    parent.recursiveDelete(parent.root);  
}

////////////// CONCAT STRING TREE ///////////////

ConcatStringTree::ConcatStringTree()
{
    root = NULL;
    height = 0;
    isReduced = false;
    is_special = false;
}

ConcatStringTree::ConcatStringTree(const char* s)
{
    root = new Node(s);
    height = 0;
    isReduced = false;
    is_special = false;
}

ConcatStringTree::ConcatStringTree(const ConcatStringTree& other)
{
    this->root = other.root;
    this->height = other.height;
    this->isReduced = other.isReduced;
    this->is_special = other.is_special;
}

int ConcatStringTree::length() const
{
    return root->leng;
}

char ConcatStringTree::get(int index) const
{
    //handle exception
    if(index>root->leng || index<0) 
        throw std::out_of_range("Index of string is invalid!");
    Node* temp = root;
    while(true)
    {
        if(temp->left==NULL && temp->right==NULL) break; //stop if reach the leaf 
        if(index>=temp->leftLength) 
        {
            index = index - temp->leftLength;
            temp = temp->right;
        }
        if(index<temp->leftLength)  temp = temp->left;
    }

    return temp->data[index];
}

int ConcatStringTree::indexUtil(Node* rot, char c) const
{
    if(rot == NULL) return 0;
    int count = -1;
    int i = 0;
    if (!rot->data.empty()) 
    {
        for(i=0; i<rot->data.length(); i++)
        {
            if(rot->data[i] == c) return i;
        }
    }
    else 
    {
        int temp1 = indexUtil(rot->left,c);
        int temp2 = indexUtil(rot->right,c);
        if(temp1 == -1 && temp2 == -1) return -1; //not found return -1

        count = count + 1 + temp1; //update the position
        if (temp1 != -1) return count; //if already found in left not need to find on the right side
        if (temp1 == -1) count = count + rot->leftLength; //is not found in left yet plus the length of the left
        //if (temp2==-1) count = count + rot->right->leng;
        count = count + 1 + temp2; //update the position   
    } 
    return count;
}

int ConcatStringTree::indexOf(char c) const 
{
    int pos = indexUtil(root, c);
    return pos;
}

string ConcatStringTree::preOrderUtil(const Node* rot) const
{
    if(rot == NULL) return "";
    else
    {
        string res;
        res = "(LL=" + to_string(rot->leftLength) + ",L=" + to_string(rot->leng)+ "," ;
        if(rot->data.empty())
             res = res + "<NULL>"  + ");";
        else res = res+ "\"" + rot->data + "\"" + ");";
        res = res  + preOrderUtil(rot->left)  + preOrderUtil(rot->right);
        return res;
    }
}

string ConcatStringTree::toStringPreOrder() const
{
    string res = "ConcatStringTree[";
    res = res + preOrderUtil(this->root);
    res.erase(res.size()-1);
    res= res +"]";
    return res;
}

string ConcatStringTree::inOrderUtil(const Node* rot) const
{
    if(rot==NULL) return "";
    else
    {
        string res;
        if(rot->data.empty()) res = "";
        else res = rot->data;
        res = res  + inOrderUtil(rot->left)  + inOrderUtil(rot->right);
        return res;
    }
}

string ConcatStringTree::toString() const
{
    string res = "ConcatStringTree[\"";
    res = res + inOrderUtil(root) + "\"]";
    return res;
}

ConcatStringTree ConcatStringTree::concat(const ConcatStringTree& otherS) const
{
    ConcatStringTree newObj = ConcatStringTree();
    newObj.root = new Node();
    newObj.isReduced = false;
    newObj.is_special = false;
    newObj.root->left = this->root;
    newObj.root->right = otherS.root;
    newObj.root->leftLength = this->length();
    newObj.root->leng = this->length() + otherS.length();
    if (this->height > otherS.height) newObj.height = this->height + 1;
    else newObj.height = otherS.height + 1;
    //add to parent tree
    this->root->parent.root = this->root->parent.insertNode(this->root->parent.root, newObj.root->id);
    otherS.root->parent.root = otherS.root->parent.insertNode(otherS.root->parent.root, newObj.root->id);
    this->root->parent.count++; //update the size
    otherS.root->parent.count++; //update the size
    return newObj;
}

void ConcatStringTree::deep_Copy(Node* rot, Node** other) const
{
    if(rot==NULL) return;
    else
    {
        *other = new Node();
        (*other)->leftLength = rot->leftLength;
        (*other)->leng = rot->leng;
        //(*other)->parent.deep_cop(rot->parent.root, &((*other)->parent.root));
        //(*other)->parent.count = rot->parent.count;
        (*other)->data = rot->data;
        (*other)->left = NULL;
        (*other)->right = NULL;
        
        deep_Copy(rot->left,&((*other)->left));
        deep_Copy(rot->right,&((*other)->right));
    }

}

void ConcatStringTree::subUtil(Node* rot, int from, int to, int& count)
{
    if(rot == NULL) return;
    if(!rot->data.empty())
    {
        if(count<=from && (count+rot->leng > from))
        {
            int temp = from-count;
            string res = "";
            int temp2;
            if((to-from>rot->leng)||(to>count+rot->leng))
            {
                temp2 = rot->leng;
            }
            else temp2 = to-count;
            for(int i=temp;i<temp2 ;i++)
            {
                res = res + rot->data[i];
            }
            rot->data = res;
        }
        if(count<to && count+rot->leng>to && count>from)
        {
            int temp = to-count;
            string res = "";
            for(int i=0;i<temp ;i++)
            {
                res = res + rot->data[i];
            }
            rot->data = res;
        }
        count = count + rot->leng; 
        if (from>=count || to<=count-rot->leng )
        {
            rot->data = "";
        }
    }
    subUtil(rot->left, from, to, count);
    subUtil(rot->right, from, to, count);

}

void ConcatStringTree::delEmpty(Node** rot)
{
    if(*rot==NULL) return;
    delEmpty(&((*rot)->left));
    delEmpty(&((*rot)->right));
    if((*rot)->left==NULL && (*rot)->right==NULL && (*rot)->data.empty())
    {
        delete *rot;
        *rot = NULL; 
    }   
}

void ConcatStringTree::upDate(Node** rot)
{
    if(*rot==NULL) return;
    upDate(&((*rot)->left));
    upDate(&((*rot)->right));
    if (!(*rot)->data.empty()) (*rot)->leng = (*rot)->data.length();
    else (*rot)->leng = 0;

    if((*rot)->left) 
    {
        (*rot)->leftLength = (*rot)->left->leng;
        (*rot)->leng = (*rot)->leng + (*rot)->left->leng;
    }
    else (*rot)->leftLength = 0;

    if((*rot)->right)
    {
        (*rot)->leng = (*rot)->leng + (*rot)->right->leng;
    } 
}

ConcatStringTree ConcatStringTree::subString(int from, int to) const
{
    if(from >= to) throw logic_error("Invalid range!");
    if(from < 0 || to>this->root->leng) throw out_of_range("Invalid range!");
    //Step1: Create a deep copy
    ConcatStringTree res = ConcatStringTree();
    res.is_special = true;
    this->deep_Copy(root, &res.root);
    res.height = this->height;
    //Step2: Set all leaf node which not in the range [from, to) data of them to be ""
    int a = 0;
    res.subUtil(res.root, from, to, a);
    //Step3: Delete all leaf node with the data = "" and set again the key and length
    res.delEmpty(&res.root);
    res.upDate(&res.root);
    return res;
}

void ConcatStringTree::deep_Copy_reverse(Node* rot, Node** other) const
{
    if (rot == NULL) return;
    else
    {
        *other = new Node();
        (*other)->leftLength = rot->leftLength;
        (*other)->leng = rot->leng;
        //(*other)->parent.deep_cop(rot->parent.root, &((*other)->parent.root));
        (*other)->data = reverseStr(rot->data); 
        (*other)->left = NULL;
        (*other)->right = NULL;

        deep_Copy_reverse(rot->right,&((*other)->left));
        deep_Copy_reverse(rot->left,&((*other)->right));
    }
}

ConcatStringTree ConcatStringTree::reverse() const
{
    ConcatStringTree res = ConcatStringTree();
    res.is_special = true;
    this->deep_Copy_reverse(this->root, &res.root);
    res.upDate(&res.root);
    return res;
}

int ConcatStringTree::getParTreeSize(const string & query) const
{
    if (this->root == NULL) throw runtime_error("Invalid query: reaching NULL");
    int n = query.length();
    Node* temp = this->root;
    for(int i=0; i<n; i++)
    {
        if (query[i]=='l')  temp = temp->left;
        else if (query[i] == 'r') temp = temp->right;
        else throw runtime_error("Invalid character of query");
        if (temp== NULL) throw runtime_error("Invalid query: reaching NULL");
    }
    return temp->parent.size();
}

string ConcatStringTree::getParTreeStringPreOrder(const string & query) const
{
    if (this->root == NULL) throw runtime_error("Invalid query: reaching NULL");
    int n = query.length();
    Node* temp = this->root;
    for(int i=0; i<n; i++)
    {
        if (query[i]=='l')  temp = temp->left;
        else if (query[i] == 'r') temp = temp->right;
        else throw runtime_error("Invalid character of query");
        if (temp== NULL) throw runtime_error("Invalid query: reaching NULL");
    }
    return temp->parent.toStringPreOrder();
}

void ConcatStringTree::recurDelete(Node* rot)
{
    if (rot)
    {
        recurDelete(rot->left);
        recurDelete(rot->right);
        delete rot;
    }
}

void ConcatStringTree::checkToDelete(Node* rot)
{
    if (rot)
    {
        if (rot->left)
        {
            if (rot->left->parent.size()==0) 
            {
                delete rot->left;
            }
        }
        if(rot->right)
        {
            if (rot->right->parent.size()==0) 
            {
                delete rot->right;
            }
        }
        if (rot->parent.size()==0) 
        {
            delete rot;
        }
    }
}

void ConcatStringTree::checkToDelete_Reduced(Node* rot)
{
    if (rot)
    {
        if (rot->left)
        {
            if (rot->left->parent.size()==0) 
            {
                this->litStringHash->deleteLit(rot->left->data);
                delete rot->left;
            }
        }
        if(rot->right)
        {
            if (rot->right->parent.size()==0) 
            {
                this->litStringHash->deleteLit(rot->right->data);
                delete rot->right;
            }
        }
        if (rot->parent.size()==0) 
        {
            this->litStringHash->deleteLit(rot->data);
            delete rot;
        }
    }
}

ConcatStringTree::~ConcatStringTree()
{
    if (this->is_special)
    {
        recurDelete(this->root);
        return;
    }

    Node* leftChild = this->root->left;
    Node* rightChild = this->root->right;
    int del_Id = this->root->id;
    //delete the id out of subtree
    if(leftChild)
    { 
        leftChild->parent.root = leftChild->parent.deleteNode(leftChild->parent.root, del_Id);
    }
    if(rightChild)
    {
        rightChild->parent.root = rightChild->parent.deleteNode(rightChild->parent.root, del_Id);
    }
    root->parent.root = root->parent.deleteNode(root->parent.root, del_Id); //delete the id in itself parent tree
    if (isReduced) this->checkToDelete_Reduced(this->root); 
    else checkToDelete(this->root);
}

//////////////PARENT TREE///////////////

int ParentTree::get_Height(PNode* rot)
{
    if (rot == NULL) return 0;
    return rot->height;
}

int ParentTree::getBalance(PNode* rot)
{
    if(rot==NULL) return 0;
    return get_Height(rot->left) - get_Height(rot->right);
}

PNode* ParentTree::insertNode(PNode* rot, int id)
{
    if (rot==NULL) 
    {
        rot = newNode(id);
        return rot;;
    }
    
    int key = id;
    if (key<rot->key) rot->left = insertNode(rot->left, id);
    else if(key > rot->key) rot->right = insertNode(rot->right, id);
    //else return rot; equal node are not allowed

    rot->height = Max(get_Height(rot->left),get_Height(rot->right)) + 1;

    int balance = getBalance(rot);
    //left left case
    if(balance > 1 && key < rot->left->key)
    {
        return rightRotate(rot);
    }
    //right right case
    if(balance < -1 && key>rot->right->key)
    {
        return leftRotate(rot);
    }

    //left right case
    if(balance > 1 && key > rot->left->key)
    {
        rot->left = leftRotate(rot->left);
        return rightRotate(rot);
    }
    //right left case
    if(balance < -1 && key < rot->right->key)
    {
        rot->right = rightRotate(rot->right);
        return leftRotate(rot);
    }

    return rot;
}

PNode* ParentTree::newNode(int id)
{
    PNode* temp = new PNode(id);
    return temp;
}

PNode* ParentTree::rightRotate(PNode* rot)
{
    PNode* temp = rot->left;
    PNode* temp2 = temp->right;

    temp->right = rot;
    rot->left = temp2;

    rot->height = Max(get_Height(rot->left),get_Height(rot->right)) + 1;
    temp->height = Max(get_Height(temp->left),get_Height(temp->right)) + 1;
    return temp;
}

PNode* ParentTree::leftRotate(PNode* rot)
{
    PNode* temp = rot->right;
    PNode* temp2 = temp->left;

    temp->left = rot;
    rot->right = temp2;

    rot->height = Max(get_Height(rot->left),get_Height(rot->right)) + 1;
    temp->height = Max(get_Height(temp->left),get_Height(temp->right)) + 1;
    return temp;
}

PNode* ParentTree::maxNode(PNode* rot)
{
    if(rot==NULL) return rot;
    if(rot->right==NULL) return rot;
    else return maxNode(rot->right);
}

PNode* ParentTree::deleteNode(PNode* rot, int key)
{
//Step 1: perform normal BST deletion
    if (rot == NULL) return rot;
    if (key<rot->key) rot->left = deleteNode(rot->left, key);
    else if(key>rot->key) rot->right = deleteNode(rot->right, key);
    else //found the node
    {   
        //Case1: Node found is a leaf 
        if(rot->left == NULL && rot->right == NULL)
        {
            delete rot;
            rot = NULL;
            count--; //reduce the size
        }
        else //Case 2: Node with one child
        if ((rot->left != NULL && rot->right == NULL)
                ||(rot->left == NULL && rot->right != NULL))
            {
                PNode* temp = rot;
                if(rot->left != NULL) rot = rot->left;
                else if(rot->right != NULL) rot = rot->right;
                delete temp;
                count--; //reduce the size
            }
        else //case with 2 children
        {
            PNode* temp = maxNode(rot->left);
            rot->key = temp->key;
            rot->left = deleteNode(rot->left, temp->key);
            count--; //reduce the size
        }
    }

    // if the tree hase only one node then return
    if(rot==NULL) return rot;

    //Step 2: update height 
    rot->height = Max(get_Height(rot->left),get_Height(rot->right)) + 1;

    //Step 3: rebalance if not balance
    int balance = getBalance(rot);
    //left left case
    if(balance > 1 && getBalance(rot->left) >=0)
    return rightRotate(rot);

    //right right case
    if (balance < -1 && getBalance(root->right) <=0)
    return leftRotate(rot);

    //left right case
    if(balance > 1 && getBalance(rot->left) <0)
    {
        rot->left = leftRotate(rot->left);
        return rightRotate(rot);
    }

    //right left case
    if(balance < -1 && getBalance(rot->right)>0)
    {
        rot->right = rightRotate(rot->right);
        return leftRotate(rot);
    }

    return rot;
}

void ParentTree::deep_cop(PNode* rot, PNode** other) const
{
    if(rot==NULL) return;
    else
    {
        *other = new PNode();
        (*other)->key = rot->key;/////////Not right by luckily not check
        (*other)->height = rot->height;
        (*other)->left = NULL;
        (*other)->right = NULL;

        deep_cop(rot->left,&((*other)->left));
        deep_cop(rot->right,&((*other)->right));
    }
}

int ParentTree::size()
{
    return this->count;
}

string ParentTree::PreorderUtil(PNode* rot) const
{
    string res = "";
    if(rot == NULL) return res;
    res = res + "(id=" + to_string(rot->key) + ");"; 
    res = res + PreorderUtil(rot->left);
    res = res + PreorderUtil(rot->right);
    return res;
}

string ParentTree::toStringPreOrder() const
{
    string res = "ParentsTree[";
    res = res + PreorderUtil(this->root);
    res.erase(res.size()-1);
    res = res +"]";
    return res;
}

void ParentTree::recursiveDelete(PNode* rot)
{
    if(rot)
    {
        recursiveDelete(rot->left);
        recursiveDelete(rot->right);
        delete rot;
    }
}

ParentTree::~ParentTree()
{
}

//////////////REDUCED CONCAT TREE///////////////

ReducedConcatStringTree::ReducedConcatStringTree()
{
    root = NULL;
    height = 0;
    litStringHash = NULL;
    isReduced = true;
    is_special = false;
}

ReducedConcatStringTree::ReducedConcatStringTree(const char * s, LitStringHash * litStringHash)
{
    this->litStringHash = litStringHash;
    isReduced = true;
    is_special = false;
    LitStringHash::LitString temp = litStringHash->search(string(s));
    if(temp.data == NULL) 
    {
        root = new Node(s,true);
        this->litStringHash->insert(root);
    }
    else 
    {
        root = temp.data;
        root->parent.count++;
        temp.num_link++;
    }
    height = 0;
}

ReducedConcatStringTree ReducedConcatStringTree::concat(const ReducedConcatStringTree & otherS) const
{
    ReducedConcatStringTree newObj;
    newObj.root = new Node(true);
    newObj.isReduced = true;
    newObj.root->left = this->root;
    newObj.root->right = otherS.root;
    newObj.root->leftLength = this->length();
    newObj.root->leng = this->length() + otherS.length();

    newObj.litStringHash = this->litStringHash;

    if (this->height > otherS.height) newObj.height = this->height + 1;
    else newObj.height = otherS.height + 1;
    //add to parent tree
    this->root->parent.root = this->root->parent.insertNode(this->root->parent.root, newObj.root->id);
    otherS.root->parent.root = otherS.root->parent.insertNode(otherS.root->parent.root, newObj.root->id);
    this->root->parent.count++;
    otherS.root->parent.count++;
    return newObj;
}

//////////////LIT STRING HASH///////////////////

LitStringHash::LitStringHash(const HashConfig & hashConfig)
{
    capacity = hashConfig.initSize;
    this->table = new LitString[capacity];
    this->status = new Status_Type[capacity];
    for(int i = 0; i<capacity; i++)
    {
        this->status[i] = NIL;
    }

    count = 0;
    loadFactor = 0;
    p = hashConfig.p;
    c1 = hashConfig.c1;
    c2 = hashConfig.c2;
    lambda = hashConfig.lambda;
    alpha = hashConfig.alpha;
    lastNode = NULL;
}

bool LitStringHash::empty()
{
    return count == 0;
}

int LitStringHash::size()
{
    return this->capacity;
}

int LitStringHash::hashFunc(string s) const
{
    int res = 0;
    for(int i=0; i<s.length();i++)
    {
        res = res + (int)s[i]*power(p,i);
        res = res%capacity;
    }
    return res;
}

int LitStringHash::quadHash(string s, int i) const
{
    int temp = hashFunc(s);
    int res = temp + (int)(c1*i + c2*power(i,2))%capacity;
    res = res%capacity;
    return res;
}

void LitStringHash::insert(Node* newNode)
{
    bool flag_inserted = false;
    for(int i=0; i<capacity; i++)
    {
        int index = quadHash(newNode->data, i);
        
        if(status[index] == NIL || status[index] == DELETED)
        {
            table[index] = LitString(newNode);
            status[index] = NON_EMPTY;
            flag_inserted = true;
            break;
        }
    }
    if(flag_inserted)
    {
        
        count++;
        loadFactor = (float)count/(float)capacity;
        int newCapacity = Floor((double)(capacity*alpha));
        if (loadFactor > lambda) this->reHash(newCapacity);
        lastNode = newNode;
    }
    else throw runtime_error("No possible slot");
}

LitStringHash::LitString LitStringHash::search(string s)
{
    LitString res = LitString();
    for(int i=0;i<capacity;i++)
    {
        int index = quadHash(s, i);
        if ((status[index] == NON_EMPTY) && (s.compare(table[index].str) == 0))
        {
            res = table[index];
            break; 
        }
    }
    return res;
}

void LitStringHash::deleteLit(string s)
{
    int index;
    for(int i = 0; i<capacity; i++)
    {
        index = quadHash(s, i);
        if ((status[index] == NON_EMPTY) && (s.compare(table[index].str) == 0))
        {
            table[index].data = NULL;
            table[index].num_link = 0;
            table[index].str = "";
            status[index] = DELETED;
            break;
        }
    }
}

int LitStringHash::getIndexOf(string s) const
{
    for(int i=0; i<capacity; i++)
    {
        int index = quadHash(s, i);
        if(s.compare(table[index].str) == 0) 
        {
            return index;
        }
    }
    return -1;
}

void LitStringHash::reHash(int newCapacity)
{
    LitString* oldTable = this->table;
    Status_Type* oldStatus = this->status;

    int oldCapacity = this->capacity;

    //create new table

    this->table = new LitString[newCapacity];
    this->status = new Status_Type[newCapacity];
    for(int i = 0; i<newCapacity; i++)
    {
        this->status[i] = NIL;
    }
    this->capacity = newCapacity;
    //cout<<"câp"<<newCapacity<<endl;
    //move all the data to new table
    //also rehash again for new index
    for(int old_idx = 0; old_idx< oldCapacity; old_idx++)
    {
        if(oldStatus[old_idx] == NON_EMPTY)
        {
            LitString oldNode = oldTable[old_idx];
            for(int i=0; i<newCapacity; i++)
            {
                int new_idx = this->quadHash(oldNode.str, i);
                //cout<<"new_idx"<<new_idx<<endl;
                if(this->status[new_idx]==NIL)
                {
                    this->table[new_idx] = oldNode;
                    this->status[new_idx] = NON_EMPTY;
                    break;
                }

            }
        }
    }

    //remove data in oldTable
    for(int idx=0; idx<oldCapacity;idx++)
    {
        if (oldStatus[idx] == NON_EMPTY) 
        {
            LitString temp = oldTable[idx];
            oldTable[idx].data = NULL;
        }
    }
    //remove oldTable
    delete[] oldTable;
    delete[] oldStatus;

}

int LitStringHash::getLastInsertedIndex() const
{
    if(lastNode == NULL) return -1;
    else 
    {
        return getIndexOf(lastNode->data);
    }
}

string LitStringHash::toString() const
{
    string res = "LitStringHash[";
    for(int idx=0; idx<this->capacity; idx++)
    {
        if(status[idx] != NON_EMPTY) res = res + "();";
        else res = res + "(litS=\"" + table[idx].str + "\");";
    }
    res.erase(res.size()-1);
    res = res + "]";
    return res;
}

LitStringHash::~LitStringHash()
{
    delete[] table;
    delete[] status;
}

////////////// END ///////////////

