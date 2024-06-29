
#include <iostream> 
using namespace std;
#include "symtable.h"
//#include "symnode.cpp"
 int heigh3(SymNode* node){
    if(node==NULL){
        return -1;  }
    else{
        return node->height;
    }
}
int getBalance2(SymNode* node)
{
    if (node == NULL){
        return 0;}
    return heigh3(node->right)-heigh3(node->left);
 }  
SymNode* solve(SymNode* temp){
    SymNode* backtrack;
    if(temp->left == NULL && temp->right == NULL) {
        if(temp->par != NULL){
            backtrack=temp->par;
            temp->key > temp->par->key ? temp->par->right=NULL : temp->par->left=NULL ; }//delete temp;       
          }
    else {
        if(temp->left==NULL){backtrack=temp->right; temp->right->par=temp->par;
        temp->key > temp->par->key ? temp->par->right=temp->right : temp->par->left=temp->right ; }// delete temp;
        else{
            backtrack=temp->left;temp->left->par=temp->par;
        temp->key > temp->par->key ? temp->par->right=temp->left : temp->par->left=temp->left ; //delete temp;
        }    }
    return backtrack;
}
SymNode* balance(SymNode* temp1,SymNode* & root) {
    SymNode* d;
    if(getBalance2(temp1)>1){
                if(getBalance2(temp1->right)<0){
                    d=temp1->LeftRightRotation();
                    // cout << d->key << " " << "y" << endl;
                    // cout << "z0" << endl;
                    if(d->par==NULL){root=d;}
                }
                else{
                    d=temp1->LeftLeftRotation();
                     //cout << "z1" << endl;
                    if(d->par==NULL){root=d;}
                }
            }
            else{
                if(getBalance2(temp1->left)>0){
                    d=temp1->RightLeftRotation();
                     //cout << "z2" << endl;
                    if(d->par==NULL){root=d;}
                    //cout << "z2" << endl;
                }
                else{
                    d=temp1->RightRightRotation();
                     //cout << "z3" << endl;
                    if(d->par==NULL){root=d;}
                    //cout << "z3" << endl;
                }
            }
    return d;
}
SymbolTable::SymbolTable(){
    root=NULL;
    size=0;
}

void SymbolTable::insert(string k)  {
    if(size==0){
        size++;
        root=new SymNode(k);
        root->height=0;    }
    else{
        //cout << "z" << endl;
        size++;
        SymNode* temp=root;
        SymNode* n1=new SymNode(k);
        while(temp != NULL){
            if(temp->key > k){
                if(temp->left == NULL){
                    temp->left=n1;
                    n1->par=temp; break;  }
                temp=temp->left;
            }
            else{
                if(temp->right == NULL){
                    temp->right=n1;
                    n1->par=temp;break;  }
                temp=temp->right;
            }
         }
        SymNode* temp1=n1;
        bool imbalanced=false;
        while(temp1 != NULL){
            temp1=temp1->par;
            if(temp1 == NULL){
                break;
            }
            if(abs(getBalance2(temp1))>1){
                imbalanced=true;
                break;}
            temp1->height=max(heigh3(temp1->left),heigh3(temp1->right))+1;     }
        if(imbalanced){
            balance(temp1,root);
            }
        return;

     }
 }

void SymbolTable::remove(string k)  {
    size--;
    if(size==0){
        root=NULL;
        return;
    }
    SymNode* temp=root;
        while(temp != NULL){
            if(temp->key == k){
                break;
            }
            else if(temp->key > k){
                temp=temp->left;}
            else{
                temp=temp->right;  }
        }
    if(temp==NULL){
        return ;
    }
    //cout << "gamboo" << endl;
    //cout << temp->key << endl;
    SymNode* backtrack;
    if(temp->left == NULL && temp->right == NULL){
        //cout << "funkinf" << endl;
        if(temp->par != NULL){
            backtrack=temp->par;
          temp->key > temp->par->key ? temp->par->right=NULL : temp->par->left=NULL ; } delete temp;       
          }
    else if(temp->left == NULL || temp->right == NULL)  {
        if(temp->left==NULL) {
        backtrack=temp->right; temp->right->par=temp->par;
            if(temp->par != NULL) {
                 //cout << temp->par->key << endl;
                 //cout << temp->right->key << endl;
             if(temp->key > temp->par->key){ temp->par->right=temp->right;}
            else{ temp->par->left=temp->right;}
            // delete temp;
              }
            }
        else{
            //cout << "rrnkinre" << endl;
            backtrack=temp->left;temp->left->par=temp->par;
        if(temp->par != NULL){temp->key > temp->par->key ? temp->par->right=temp->left : temp->par->left=temp->left ;}
        }    }
    else{
        // cout << "taxnkinre" << endl;
        SymNode* temp1=temp->right;
        while(temp1->left != NULL){
            temp1=temp1->left;
        }
        string k1=temp1->key;int i=temp1->address;
        backtrack=solve(temp1);
        temp->address=i;temp->key=k1;
        }
        // cout << "tambu" << endl; 
        if(backtrack->par==NULL){root=backtrack;}
        // cout << backtrack->key << endl;
        // cout << backtrack->par->right->key << endl;
        while(backtrack != NULL){
            // cout << "maxi" << endl;
            backtrack->height=max(heigh3(backtrack->left),heigh3(backtrack->right))+1;
            // cout << backtrack->right->height << endl;
            SymNode* t=backtrack->par;
            // cout << getBalance(backtrack) << endl;
            if(abs(getBalance2(backtrack))>1){
                // cout << "crash" << endl;
                t=balance(backtrack,root);
            }
            // cout << backtrack->key << endl;
            // cout << root->key << " " << "x" << endl;
            backtrack=t;
            if(backtrack != NULL){if(backtrack->par==NULL){root=backtrack;}}
        }
    

}

int SymbolTable::search(string k){
    SymNode* temp=root;
        while(temp != NULL){
            if(temp->key == k){
                return temp->address;
            }
            else if(temp->key > k){
                temp=temp->left;}
            else{
                temp=temp->right;  }
        }
    return -2;
}

void SymbolTable::assign_address(string k,int idx){
    SymNode* temp=root;
        while(temp != NULL){
            if(temp->key == k){
                temp->address=idx;
                return;
            }
            else if(temp->key > k){
                temp=temp->left;}
            else{
                temp=temp->right;  }
        }
    return ;
}

int SymbolTable::get_size(){
    return size;
}

SymNode* SymbolTable::get_root(){
    return root;
}

SymbolTable::~SymbolTable(){
    if(root != NULL){delete root;root=NULL;}
}
