
/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"
#include <iostream>
int heigh( SymNode* node){
    if(node==NULL){
        return -1;  }
    else{
        return node->height;
    }
}
int getBalance(SymNode* node)
{
    if (node == NULL){
        return 0;}
    return heigh(node->right)-heigh(node->left);
}
SymNode::SymNode(){
    left=NULL;
    right=NULL;
    par=NULL;
    height=0;
}

SymNode::SymNode(string k){
    key=k;
    left=NULL;
    right=NULL;
    par=NULL;
    height=0;

}

SymNode* SymNode::LeftLeftRotation(){
    SymNode* b=right;SymNode* c=b->left;
    this->right=c;b->par=par;
    if(c != NULL){
        c->par=this;
    }
    if(par != NULL){
        if(b->key > par->key){par->right=b;}
        else{par->left=b;}} 
    b->left=this;par=b;
    this->height=max(heigh(left),heigh(right))+1;
    b->height=max(heigh(b->left),heigh(b->right))+1;
    return b;
}

SymNode* SymNode::RightRightRotation(){
    SymNode* b=left;SymNode* c=b->right;
    this->left=c;b->par=par;
    if(c != NULL){
        c->par=this;
    }
    if(par != NULL){
        if(b->key > par->key){par->right=b;}
        else{par->left=b;}} 
    b->right=this;par=b;
    this->height=max(heigh(left),heigh(right))+1;
    b->height=max(heigh(b->left),heigh(b->right))+1;
    return b;

}

SymNode* SymNode::LeftRightRotation(){
    SymNode* b=right;SymNode* c=b->left;
     // cout << b->key << endl;cout << c->key << endl;
    SymNode* d=c->left;SymNode* e=c->right;b->left=e;right=d;SymNode* x=par;
    if(e != NULL){e->par=b;}
    if(d != NULL){d->par=this;}
    c->left=this;c->right=b;c->par=par;par=c;b->par=c;
    // cout << this->key << endl;
    // cout << c->left->key << " " << "hhg" << endl;
    if(x != NULL){
        if(c->key > x->key){x->right=c;}
        else{x->left=c;}} 
    this->height=max(heigh(left),heigh(right))+1;
    b->height=max(heigh(b->left),heigh(b->right))+1;
    c->height=max(heigh(c->left),heigh(c->right))+1;
    //  << c->left->key << " " << "hhg" << endl;y
    return c;
}

SymNode* SymNode::RightLeftRotation(){
    SymNode* b=left;SymNode* c=b->right;
    SymNode* d=c->left;SymNode* e=c->right;b->right=d;left=e;SymNode* x=par;
    if(e != NULL){e->par=this;}
    if(d != NULL){d->par=b;}
    c->left=b;c->right=this;c->par=par;par=c;b->par=c;
    if(x != NULL){
        if(c->key > x->key){x->right=c;}
        else{x->left=c;}} 
    this->height=max(heigh(left),heigh(right))+1;
    b->height=max(heigh(b->left),heigh(b->right))+1;
    c->height=max(heigh(c->left),heigh(c->right))+1;
    return c;

}

SymNode::~SymNode(){
     if(left != NULL){delete left;left=NULL;}
    if(right != NULL){delete right;right=NULL;}
}