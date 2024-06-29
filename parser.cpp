/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"
#include <iostream>
bool containsNonDigits(const std::string& str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return true; 
        }
    }
    return false; 
}
bool isOperator(const string& token) {
    return (token == "+" || token == "-" || token == "*" || token == "/" || token == ":=");
}
int precedence(const string& op) {
    if (op == ":=") {
        return 3; 
    } else if (op == "*" || op == "/") {
        return 2;
    } else if (op == "+" || op == "-") {
        return 1;
    }
    return 0;
}
vector<string> infixToPostfix(const vector<string>& infix) {
    vector<string> operatorStack;
    vector<string> postfix;
    for (const string& token : infix) {
        if (isOperator(token)) {
            while (!operatorStack.empty() && precedence(token) <= precedence(operatorStack.back())) {
                postfix.push_back(operatorStack.back());
                operatorStack.pop_back();
            }
            operatorStack.push_back(token);
        } else if (token == "(") {
            operatorStack.push_back(token);
        } else if (token == ")") {
            while (!operatorStack.empty() && operatorStack.back() != "(" ) {
                postfix.push_back(operatorStack.back());
                operatorStack.pop_back();
            }
            if (!operatorStack.empty() && operatorStack.back() == "("  ) {
                operatorStack.pop_back();
            }
        } else {
            postfix.push_back(token); 
        }
    }

    while (!operatorStack.empty()) {
        postfix.push_back(operatorStack.back());
        operatorStack.pop_back();
    }

    return postfix;
}
Parser::Parser(){

    symtable=new SymbolTable();
}

void Parser::parse(vector<string> expression){
    if(expression[0]=="DEL"){
        ExprTreeNode* operatorNode = new ExprTreeNode();
        // symtable->remove(expression[2]);
        ExprTreeNode* operandNode1 = new ExprTreeNode();
        ExprTreeNode* operandNode2 = new ExprTreeNode();
        operatorNode->type="UN";operandNode1->type="VAR"; operandNode2->type="DEL";
        operatorNode->left=operandNode2;operatorNode->left=operandNode2;
        expr_trees.push_back(operatorNode);
    }
    else{
        vector<string> postfix = infixToPostfix(expression);
        vector<ExprTreeNode*> nodeVector;
        for (const string& token : postfix) {
            if (token == "+" || token == "-" || token == "*" || token == "/" || token == ":=") {
                ExprTreeNode* operatorNode = new ExprTreeNode();
                if(token==":="){
                    operatorNode->type="UN";
                }
                else if(token=="+"){
                     operatorNode->type="ADD";}
                else if(token=="*"){
                     operatorNode->type="MUL";}
                else if(token=="-"){
                     operatorNode->type="SUB";}
                else if(token=="/"){
                     operatorNode->type="DIV";
                     }
                operatorNode->right = nodeVector.back();
                nodeVector.pop_back();
                operatorNode->left = nodeVector.back();
                nodeVector.pop_back();
                nodeVector.push_back(operatorNode);
            } else {
                ExprTreeNode* operandNode = new ExprTreeNode();
                if(token=="ret"){
                    operandNode->type="RET";
                }
                else if(token=="del"){
                    operandNode->type="DEL";
                    operandNode->id=token;
                }
                else if(containsNonDigits(token)){
                    operandNode->type="VAR";
                    if(symtable->search(token) == -2){
                        symtable->insert(token);
                        // cout << token << endl;
                        symtable->assign_address(token,-1);
                    }
                    operandNode->id=token;
                }
                else{
                    operandNode->type="VAL";
                    operandNode->num=stoi(token);
                }
                
                nodeVector.push_back(operandNode);
            }
        }
        // std::cout << "m" << std::endl;
        if (!nodeVector.empty()) {
            expr_trees.push_back(nodeVector.back());
        }
        nodeVector.clear();
    }
}

Parser::~Parser(){
     for(auto i:expr_trees){
         delete i;
     }
 
}