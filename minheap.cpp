/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "minheap.h"
 // #include "heapnode.cpp"
#include <iostream>
//Write your code below this line

MinHeap::MinHeap(){
    size=0;
    root=NULL;
}

void MinHeap::push_heap(int num){
    size++;
    HeapNode* n1=new HeapNode(num);
    if(root == NULL){root=n1;}
    else if(root->left==NULL){root->left=n1;n1->par=root;}
    else if(root->right==NULL){root->right=n1;n1->par=root;}
    else{
        // cout << "xy" << endl;
        HeapNode* temp=root;
        int binaryNum[64];
        int i = 0;int n=size;
        while (n > 0) {
            binaryNum[i] = n % 2;
            n = n / 2;
            i++;
            }
        for (int j = i - 2; j > 0; j--){
                if(binaryNum[j]==0){temp=temp->left;}
                else{temp=temp->right;}   
                    }
        if(binaryNum[0]==0){temp->left=n1;n1->par=temp;}
        else{temp->right=n1;n1->par=temp;}
            }
    while(n1->par != NULL && n1->val < n1->par->val){
         // cout << "z" << endl;
        int temp1=n1->val;n1->val=n1->par->val;n1->par->val=temp1;
        n1=n1->par;
    }
    return ;
    
}
int MinHeap::get_min(){
     // cout << "xy" << endl;
    return root->val;
}

void MinHeap::pop(){
    // cout << "x" << endl;
    if(size==1){
        root=NULL;
    }
    else{ 
        // cout << "m" << endl;
        HeapNode* temp=root;
        int binaryNum[32];
        int i = 0;int n=size;
        while (n > 0) {
            binaryNum[i] = n % 2;
            n = n / 2;
            i++;
            }
        for (int j = i - 2; j >= 0; j--){
                if(binaryNum[j]==0){temp=temp->left;}
                else{temp=temp->right;}   
                    }
        root->val=temp->val;
        if(temp->par->left==temp){
            temp->par->left=NULL;
            delete temp;
            temp=NULL;
        }
        else{
            temp->par->right=NULL;delete temp;
            temp=NULL;
        }
        // cout << "mt" << endl;
        HeapNode* current=root;
          while (current != NULL) {
            HeapNode* smallest = current;
            if (current->left != NULL && current->left->val < smallest->val) {
                smallest = current->left;
            }
            if (current->right != NULL && current->right->val < smallest->val) {
                smallest = current->right;
            }
            if (smallest->val == current->val) {
                break; 
            }
             int temp1 = current->val;
             if (smallest != NULL){
                 current->val = smallest->val;
                smallest->val = temp1;
             }

            current = smallest;  
        } 
    }
    size--; 
    return;



}

MinHeap::~MinHeap(){
    if(root != NULL){
        delete root;
    }
}
 /* int main(){
    MinHeap h;
    h.push_heap(0);
    h.push_heap(1);
    h.push_heap(2);
    h.pop();
     h.pop();
      h.pop();
      cout << "m" << endl;
    
}
*/