#include "ConcatStringTree.h"
/*
void tc1()
{
    ConcatStringTree::Node* a1 = new ConcatStringTree::Node("Hello");
    ConcatStringTree::Node* a2 = new ConcatStringTree::Node(",_t");
    ConcatStringTree::Node* a3 = new ConcatStringTree::Node("his_is");
    ConcatStringTree::Node* a4 = new ConcatStringTree::Node("_an");
    ConcatStringTree::Node* a5 = new ConcatStringTree::Node("_flying");
    ConcatStringTree::Node* a6 = new ConcatStringTree::Node("_duck");
    ConcatStringTree s1 = ConcatStringTree();
    ConcatStringTree s2 = ConcatStringTree();
    
    s1.root->left = a1;
    s1.root->right = a2;
    s1.root->leftLength = a1->leng;
    s1.root->leng = a1->leng + a2->leng;
    s1.height = 1;


    s2.root->left = a3;
    s2.root->right = a4;
    s2.root->leftLength = a3->leng;
    s2.root->leng = a3->leng + a4->leng;
    s2.height = 1;

    ConcatStringTree s3  = s1.concat(s2);
    ConcatStringTree s4 = ConcatStringTree();
    s4.root->left = a5;
    s4.root->right = a6;
    s4.root->leftLength = a5->leng;
    s4.root->leng = a5->leng + a6->leng;
    s4.height = 1;
    ConcatStringTree s5  = s3.concat(s4);
    cout<<s5.get(22)<<endl;
    cout<<s5.get(5)<<endl;
    cout<<s5.get(0)<<endl;
    cout<<s5.get(14)<<endl;
    cout<<s5.get(28)<<endl;
}

void tc2()
{
    ConcatStringTree::Node* a1 = new ConcatStringTree::Node("Hello");
    ConcatStringTree::Node* a2 = new ConcatStringTree::Node(",_t");
    ConcatStringTree::Node* a3 = new ConcatStringTree::Node("his_is");
    ConcatStringTree::Node* a4 = new ConcatStringTree::Node("_an");
    ConcatStringTree s1 = ConcatStringTree();
    ConcatStringTree s2 = ConcatStringTree();
    


    s1.root->left = a1;
    s1.root->right = a2;
    s1.root->leftLength = a1->leng;
    s1.root->leng = a1->leng + a2->leng;
    s1.height = 1;


    s2.root->left = a3;
    s2.root->right = a4;
    s2.root->leftLength = a3->leng;
    s2.root->leng = a3->leng + a4->leng;
    s2.height = 1;

    ConcatStringTree s3  = s1.concat(s2);

    ConcatStringTree s4 = s3.subString(1,10);
    // cout<<s4.toStringPreOrder()<<endl;
    cout<<s4.toString()<<endl;
    ConcatStringTree s5 = s4.reverse();
    cout<<s5.toString()<<endl;
    cout<<s5.toStringPreOrder()<<endl;
}*/
/*
void tc3()
{
    ConcatStringTree* a1 = new ConcatStringTree("Hello");
    ConcatStringTree* a2 = new ConcatStringTree(",_t");
    ConcatStringTree* a3 = new ConcatStringTree("his_is");
    ConcatStringTree* a4 = new ConcatStringTree("_a");
    ConcatStringTree* a5 = new ConcatStringTree("_flying");
    ConcatStringTree* a6 = new ConcatStringTree("_duck");

    ConcatStringTree* s1 = new ConcatStringTree(a1->concat(*a6)); //Hello_duck
    ConcatStringTree* s2 = new ConcatStringTree(a1->concat(*a4)); //Hello_a
    ConcatStringTree* s3 = new ConcatStringTree(s2->concat(*a6)); //Hello_a_duck
    ConcatStringTree* s4 = new ConcatStringTree(a1->concat(*a2)); //Hello,_t
    ConcatStringTree* s5 = new ConcatStringTree(a3->concat(*a4)); //his_is_a
    ConcatStringTree* s6 = new ConcatStringTree(s4->concat(*s5)); //Hello,_this_is_a
    ConcatStringTree* s7 = new ConcatStringTree(a5->concat(*a6)); //_flying_duck
    ConcatStringTree* s8 = new ConcatStringTree(s6->concat(*s7)); //Hello_,this_is_a_flying_duck
    
    ConcatStringTree* s9 = new ConcatStringTree(s3->reverse());
    cout<<s9->toStringPreOrder()<<endl;
    ConcatStringTree* s10 = new ConcatStringTree(s8->subString(3,15));
    cout<<s10->toStringPreOrder()<<endl;
    ConcatStringTree* s11 = new ConcatStringTree(s10->reverse());
    cout<<s11->toStringPreOrder()<<endl;

    
    cout<<s6->getParTreeSize("rr")<<endl;
    cout<<s8->getParTreeStringPreOrder("llr")<<endl;

}

void tc6() 
{
    ConcatStringTree *s1 = new ConcatStringTree("He");
    ConcatStringTree *s2 = new ConcatStringTree("t_roi_ban_oi_");
    ConcatStringTree *s3 = new ConcatStringTree("_lai_sang_thu");
    ConcatStringTree *s12 = new ConcatStringTree(s1->concat(*s2));
    cout << s12->toString() << endl;
    ConcatStringTree *s121 = new ConcatStringTree(s12->concat(*s1));
    cout << s121->toString() << endl;
    ConcatStringTree *s1213 = new ConcatStringTree(s121->concat(*s3));
    cout << s1213->toString() << endl;

    cout << s1->getParTreeStringPreOrder("") << endl;
    cout << s2->getParTreeStringPreOrder("") << endl;
    cout << s3->getParTreeStringPreOrder("") << endl;
    cout << s12->getParTreeStringPreOrder("") << endl;
    cout << s121->getParTreeStringPreOrder("") << endl;
    cout << s1213->getParTreeStringPreOrder("") << endl;
    
    delete s1;
    
    delete s2;
    delete s3;
    delete s12;
    delete s121;
    delete s1213;
    
}

void tc12() {
    // Test Substring
    ConcatStringTree * s1 = new ConcatStringTree("A");
    ConcatStringTree * s2 = new ConcatStringTree("B");

    ConcatStringTree *s12 = new ConcatStringTree(s1->concat(*s2));
    ConcatStringTree *s21 = new ConcatStringTree(s2->concat(*s1));

    ConcatStringTree * s1221 = new ConcatStringTree(s12->concat(*s21));
    ConcatStringTree * s2112 = new ConcatStringTree(s21->concat(*s12));

    ConcatStringTree * s4 = new ConcatStringTree(s1221->concat(*s2112));
    ConcatStringTree * s5 = new ConcatStringTree(s4->concat(*s2112));
    ConcatStringTree * s6 = new ConcatStringTree(s1221->concat(*s5));


    ConcatStringTree * s0 = new ConcatStringTree(s6->concat(*s1221));
    cout << s0->toString() << endl;
    cout << s0->toStringPreOrder() << endl << endl;

    delete s2;
    delete s1;
    
    delete s21;
    delete s12;

    delete s2112;
    delete s1221;

    ConcatStringTree *sub1 = new ConcatStringTree(s0->subString(0,2));
    cout << sub1->toString() << endl;
    cout << sub1->toStringPreOrder() << endl << endl;

    ConcatStringTree *sub2 = new ConcatStringTree(s0->subString(3,19));
    cout << sub2->toString() << endl;
    cout << sub2->toStringPreOrder() << endl << endl;

    ConcatStringTree *sub3 = new ConcatStringTree(s0->subString(5,6));
    cout << sub3->toString() << endl;
    cout << sub3->toStringPreOrder() << endl << endl;

    ConcatStringTree *sub4 = new ConcatStringTree(s0->subString(11,12));
    cout << sub4->toString() << endl;
    cout << sub4->toStringPreOrder() << endl << endl;
    
    ConcatStringTree *sub5 = new ConcatStringTree(s0->subString(2,18));
    cout << sub5->toString() << endl;
    cout << sub5->toStringPreOrder() << endl << endl;

    ConcatStringTree *sub6 = new ConcatStringTree(s0->subString(15,20));
    cout << sub6->toString() << endl;
    cout << sub6->toStringPreOrder() << endl << endl;

    delete s0;

    delete s5;
    delete s6;
    delete s4;

    delete sub5;
    delete sub2;
    delete sub1;
    delete sub4;
    delete sub3;
    delete sub6;
}


void tcBKEL() 
{
    HashConfig hashConfig(
        2,
        0.5,
        0.5,
        0.75,
        2,
        4
    );
    LitStringHash * litStringHash = new LitStringHash(hashConfig);

    ReducedConcatStringTree * s1 = new ReducedConcatStringTree("a", litStringHash);
    ReducedConcatStringTree * s2 = new ReducedConcatStringTree("bb", litStringHash);

    cout << s1->toString() << endl;
    cout << s2->toString() << endl;
    
    ReducedConcatStringTree * s3 = new ReducedConcatStringTree("bb", litStringHash);
    cout << s3->toString() << endl;
    
    cout << litStringHash->getLastInsertedIndex() <<endl;
    cout << litStringHash->toString() << endl;
    
    delete s3;
    delete s1;
    delete s2;
    delete litStringHash;

}

void tcT1() 
{
    HashConfig hashConfig(
        2,
        0.5,
        0.5,
        2,
        2,
        2
    );
    LitStringHash* litStringHash = new LitStringHash(hashConfig);
    ReducedConcatStringTree* s1 = new ReducedConcatStringTree("Hello", litStringHash);
    ReducedConcatStringTree* s2 = new ReducedConcatStringTree(",_t", litStringHash);
    cout << "litStringHash->toString(): " << litStringHash->toString() << endl;
    cout << "lastinserted: " << litStringHash->getLastInsertedIndex() << endl;
    try {

        ReducedConcatStringTree* s3 = new ReducedConcatStringTree("Hellotr", litStringHash);;
    }
    catch (runtime_error& ofr) {
        cout << "Exception runtime_error: " << ofr.what() << endl;
    }
    delete s1;
    delete s2;
    cout<<"litStringHash->toString(): " << litStringHash->toString()<<endl;
    cout << "lastinserted: " << litStringHash->getLastInsertedIndex() << endl;
    delete litStringHash;
}

void tcR1() {
    HashConfig hashConfig(
        2,
        0.5,
        0.5,
        0.75,
        2,
        4
    );
    LitStringHash * litStringHash = new LitStringHash(hashConfig);
    ReducedConcatStringTree * s1 = new ReducedConcatStringTree("a", litStringHash);
    ReducedConcatStringTree * s2 = new ReducedConcatStringTree("bb", litStringHash);

    cout << s1->toString() << endl;
    cout << s2->toString() << endl;

    ReducedConcatStringTree * s3 = new ReducedConcatStringTree(s1->concat(*s2));
    cout << s3->toString() << endl;

    cout << litStringHash->getLastInsertedIndex() <<endl;
    cout << litStringHash->toString() << endl;
    
    delete s3;
    delete s1;
    delete s2;
    delete litStringHash;
}

void tcR2() {
    HashConfig hashConfig(
        2,
        0.5,
        0.5,
        1.5, //lambda
        2,
        4
    );
    LitStringHash * litStringHash = new LitStringHash(hashConfig);
    ReducedConcatStringTree * s1 = new ReducedConcatStringTree("a", litStringHash);
    ReducedConcatStringTree * s2 = new ReducedConcatStringTree("bb", litStringHash);
    ReducedConcatStringTree * s3 = new ReducedConcatStringTree("ccc", litStringHash);
    ReducedConcatStringTree * s4 = new ReducedConcatStringTree("dddd", litStringHash);

    cout << s1->toString() << endl;
    cout << s2->toString() << endl;
    cout << s3->toString() << endl;
    cout << s4->toString() << endl;

    ReducedConcatStringTree * s0 = new ReducedConcatStringTree(s1->concat(*s2));
    cout << s0->toString() << endl;

    try
    {
        ReducedConcatStringTree * s5 = new ReducedConcatStringTree("eeeee", litStringHash);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    

    cout << litStringHash->getLastInsertedIndex() <<endl;
    cout << litStringHash->toString() << endl;
    
    delete s3;
    delete s1;
    delete s0;
    delete s4;
    delete s2;
    delete litStringHash;
}

void myownDebug()
{
    HashConfig hashConfig(
    2,
    0.5,
    0.5,
    1.5, //lambda
    2,
    4
    );
    LitStringHash * litStringHash = new LitStringHash(hashConfig);
    ReducedConcatStringTree * s1 = new ReducedConcatStringTree("a", litStringHash);
    ReducedConcatStringTree * s2 = new ReducedConcatStringTree("bb", litStringHash);
    ReducedConcatStringTree * s0 = new ReducedConcatStringTree(s1->concat(*s2));
    
    delete s1;
    
    delete s0;
    delete s2;
    //delete s0;
    delete litStringHash;
}

void tcmain()
{ 	
    ConcatStringTree s1("Hello");
    ConcatStringTree s2(",_t");
    ConcatStringTree s3 = s1.concat(s2);
    ConcatStringTree s4 = s3.subString(5, 6); //todo
    cout << s3.toStringPreOrder() << endl;
    cout << s3.toString() << endl;
    cout << s4.toString()<< endl;
    cout << s3.reverse().toString() << endl;
    //s1.~ConcatStringTree();
}


void tcR3() {
    HashConfig hashConfig(
        2,
        0.5,
        0.5,
        0, //lambda => always rehash
        2,
        4
    );
    LitStringHash * litStringHash = new LitStringHash(hashConfig);
    ReducedConcatStringTree * s1 = new ReducedConcatStringTree("a", litStringHash);
    cout << litStringHash->getLastInsertedIndex() <<endl;
    ReducedConcatStringTree * s2 = new ReducedConcatStringTree("bb", litStringHash);
    cout << litStringHash->getLastInsertedIndex() <<endl;
    ReducedConcatStringTree * s3 = new ReducedConcatStringTree("ccc", litStringHash);
    cout << litStringHash->getLastInsertedIndex() <<endl;
    ReducedConcatStringTree * s4 = new ReducedConcatStringTree("dddd", litStringHash);
    cout << litStringHash->getLastInsertedIndex() <<endl;

    cout << s1->toString() << endl;
    cout << s2->toString() << endl;
    cout << s3->toString() << endl;
    cout << s4->toString() << endl;

    ReducedConcatStringTree * s0 = new ReducedConcatStringTree(s1->concat(*s2));
    cout << s0->toString() << endl;

    cout << litStringHash->getLastInsertedIndex() <<endl;
    cout << litStringHash->toString() << endl;
    
    delete s3;
    delete s1;
    delete s0;
    delete s4;
    delete s2;
    delete litStringHash;
}


void tcR4() {
    HashConfig hashConfig(
        2,
        0.5,
        0.5,
        0.75,
        2,
        4
    );
    LitStringHash * litStringHash = new LitStringHash(hashConfig);
    ReducedConcatStringTree * s1 = new ReducedConcatStringTree("a", litStringHash);
    ReducedConcatStringTree * s2 = new ReducedConcatStringTree("bb", litStringHash);
    cout << litStringHash->toString() << endl;
    cout << litStringHash->getLastInsertedIndex() <<endl;
    delete s1;
    cout << litStringHash->toString() << endl;
    cout << litStringHash->getLastInsertedIndex() <<endl;
    s1 = new ReducedConcatStringTree("A", litStringHash);
    cout << litStringHash->toString() << endl;

    cout << s1->toString() << endl;
    cout << s2->toString() << endl;

    ReducedConcatStringTree * s3 = new ReducedConcatStringTree(s1->concat(*s2));
    cout << s3->toString() << endl;

    cout << litStringHash->getLastInsertedIndex() <<endl;
    cout << litStringHash->toString() << endl;
    
    delete s3;
    delete s2;
    delete s1;
    delete litStringHash;
}
*/
void tc4() {
    ConcatStringTree s1("Hello");
    cout << s1.getParTreeStringPreOrder("") << endl;
    ConcatStringTree s2 = s1.reverse();
    cout << s2.getParTreeStringPreOrder("") << endl;
    ConcatStringTree s3(" I'm new");
    ConcatStringTree s13 = s1.concat(s3);
    ConcatStringTree s31 = s13.reverse();
    cout << s31.length() << " - " << s31.getParTreeStringPreOrder("") << endl;
    cout << s31.getParTreeStringPreOrder("l") << endl;
    cout << s31.getParTreeStringPreOrder("r") << endl;
}

void tc11() {
    // Test Substring
    ConcatStringTree * s1 = new ConcatStringTree("Bac");
    ConcatStringTree * s2 = new ConcatStringTree("a");
    ConcatStringTree * s3 = new ConcatStringTree("Den");
    ConcatStringTree * s4 = new ConcatStringTree("La");

    ConcatStringTree *s12 = new ConcatStringTree(s1->concat(*s2));
    ConcatStringTree *s32 = new ConcatStringTree(s3->concat(*s2));
    ConcatStringTree *s324 = new ConcatStringTree(s32->concat(*s4));

    ConcatStringTree *s0 = new ConcatStringTree(s12->concat(*s324));
    cout << s0->toString() << endl;
    cout << s0->toStringPreOrder() << endl << endl;

    ConcatStringTree *sub1 = new ConcatStringTree(s0->subString(0,2));
    cout << sub1->toString() << endl;
    cout << sub1->toStringPreOrder() << endl << endl;

    ConcatStringTree *sub2 = new ConcatStringTree(s0->subString(0,9));
    cout << sub2->toString() << endl;
    cout << sub2->toStringPreOrder() << endl << endl;

    ConcatStringTree *sub3 = new ConcatStringTree(s0->subString(3,4));
    cout << sub3->toString() << endl;
    cout << sub3->toStringPreOrder() << endl << endl;

    ConcatStringTree *sub4 = new ConcatStringTree(s0->subString(3,8));
    cout << sub4->toString() << endl;
    cout << sub4->toStringPreOrder() << endl;

    delete s0;
    delete s1;
    delete s2;
    delete s3;
    delete s4;
    delete s12;
    delete s32;
    delete s324;

    delete sub1;
    delete sub2;
    delete sub3;
    delete sub4;
}
int main() 
{
    //tcBKEL();
    //tc6();
    //tcT1();
    //tcR1();
    //tc12();
    //tcR2();
    //tcR3();
    //tcR4();
    //tc9();
    //myownDebug();
    //tcmain();
    tc11();
    system("Pause");
    return 0;
}