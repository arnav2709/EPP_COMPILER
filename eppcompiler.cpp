/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"
#include <iostream>
using namespace std;
/* #include "symtable.cpp"
#include "parser.cpp"
#include "symnode.cpp"
#include "exprtreenode.cpp"
#include "minheap.cpp"
#include "heapnode.cpp"  */ 
// Write your code below this line

EPPCompiler::EPPCompiler(){

    targ=Parser();
    output_file="punu3.txt";
    mem_loc={0};
}

EPPCompiler::EPPCompiler(string out_file,int mem_limit){
    targ=Parser();
    output_file=out_file;
    memory_size=mem_limit;
    // cout << memory_size << endl;cout
    least_mem_loc=MinHeap();
    for(int i=0;i<memory_size;i++){
        least_mem_loc.push_heap(i);
    }
    // cout << "hi" << endl;
}

void EPPCompiler::compile(vector<vector<string>> code){
    // cout << code.size() << endl;
    for(auto i:code){
        // cout << "x" << endl;
        targ.parse(i);
        // cout << targ.expr_trees.back()->right->type << endl;
        //cout << "y" << endl;
        //cout << "x" << endl;
        write_to_file(generate_targ_commands());
        //cout << "x" << endl;
    }
    return;
}
void generator(vector<string>& ans,ExprTreeNode* node,MinHeap& m,SymbolTable* & s){
    if(node->type=="UN"){
        if(node->left->type=="DEL"){
            //cout << "mm1" << endl;
            m.push_heap(s->search(node->right->id));
            // cout << s->search(node->right->id) << endl;
            ans.push_back("DEL = mem[" + std::to_string(s->search(node->right->id)) + "]");
            //cout << "mamboo" << endl;
            s->remove(node->right->id);
            //cout << "bamboo" << endl;
            return;
        }
        else if(node->left->type=="RET"){
            ans.push_back("RET = POP");
            //cout << "mm2" << endl;
            generator(ans,node->right,m,s);
             //cout << ans.back() << endl;
            return;
        }
        else{
             // cout << node->left->id << endl;
            // cout << "mm3" << endl;
            int t=0;
            if(s->search(node->left->id) == -1){
                t=m.get_min();
                 m.pop();
            }
            else{
                t=s->search(node->left->id);
            }
            // cout << t << endl;
            // cout << "mm2" << endl;
            //cout << "mm3" << endl;
            // cout << t << endl;
            s->assign_address(node->left->id,t);
            // cout << s->search(node->id) << endl;
            //cout << "mm3" << endl;
            ans.push_back("mem[" + std::to_string(t) + "] = POP");
            // cout << ans.back() << endl;
            //cout << "mm4" << endl;
            generator(ans,node->right,m,s);
        }
    
    }
    else if(node->type=="VAR"){
        // cout << "y" << endl;
        int t=0;
        if(s->search(node->id) == -1){
            t=m.get_min();
                m.pop();
            s->assign_address(node->id,t);
        }
        ans.push_back("PUSH mem[" + std::to_string(s->search(node->id))+ "]" ) ;
        return;
    }
    else if(node->type=="VAL"){
        ans.push_back("PUSH " + std::to_string(node->num));
        // cout << ans.back() << endl;
        return;
    }
    else{
        if(node->type=="ADD"){
            ans.push_back("ADD");
            generator(ans,node->left,m,s);
            generator(ans,node->right,m,s);
        }
        else if(node->type=="SUB"){
            ans.push_back("SUB");
            generator(ans,node->left,m,s);
            generator(ans,node->right,m,s);
        }
        else if(node->type=="DIV"){
            ans.push_back("DIV");
            generator(ans,node->left,m,s);
            generator(ans,node->right,m,s);
        }
        else if(node->type=="MUL"){
            ans.push_back("MUL");
            generator(ans,node->left,m,s);
            generator(ans,node->right,m,s);
        }
    }
}
vector<string> EPPCompiler::generate_targ_commands(){
    vector<string>ans;
    ExprTreeNode* n1=targ.expr_trees.back();
    //cout << "mm" << endl;
    generator(ans,n1,least_mem_loc,targ.symtable);
    //cout << "mm" << endl;
    return ans;

}

void EPPCompiler::write_to_file(vector<string> commands){
     std::ofstream outputFile(output_file,std::ios::app);
     // cout << "x" << endl;
    if (outputFile.is_open()) {
        for (auto it = commands.rbegin(); it != commands.rend(); ++it) {
            outputFile << *it << '\n';
        }

        // std::cout << "Commands written to " << output_file << " successfully." << std::endl;
        outputFile.close();
     }
    return ;
}

EPPCompiler::~EPPCompiler(){
    
    delete targ.symtable;

} 
/* int main()  {
    EPPCompiler e1("noname12.txt",4);
    vector<vector<string>>v1;
    v1.push_back({"x",":=","3"});
    v1.push_back({"y",":=","2"});
    v1.push_back({"x",":=","(","x","+","5",")"});
    v1.push_back({"z",":=","6"});
    v1.push_back({"ret",":=","7"});
    e1.compile(v1);
} 
    /* v1.push_back({ "del",":=","x" });

    
    v1.push_back({"del",":=","y"});
    v1.push_back({"w",":=","(","5","+","(","z","/","2",")",")"}); 
    v1.push_back({ "ret",":=","z" });
    e1.compile(v1);

 }*/