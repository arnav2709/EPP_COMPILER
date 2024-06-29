/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "heapnode.h"

//Write your code below this line

HeapNode::HeapNode(){
    left=NULL;
    right=NULL;
    par=NULL;
}

HeapNode::HeapNode(int _val){
    val=_val;
    par=NULL;
    left=NULL;
    right=NULL;

}

HeapNode::~HeapNode(){
    if(left != NULL){
        delete left;
    }
    if(right !=  NULL){
        delete right;
    }
}