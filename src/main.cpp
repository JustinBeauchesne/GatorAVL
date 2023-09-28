#include <iostream>
#include <regex>
#include "Tree.h"


int main(){
    AVL tree;

    // Data validation
    // get num of instuctions
    std::string line;
    getline(std::cin,line);
    int num = stoi(line);
    std::queue<std::string> textQ;
    std::queue<int> numQ;

    // get instructions
    for(int i = 0; i < num; i++){
    getline(std::cin,line);
    //std::regex insert = std::regex("^insert \"[A-Z][a-z]*\" [0-9]{8}$");
    std::regex insert = std::regex("^insert \"([A-Z]?[a-z]* *)*\" [0-9]{8}$");
    std::regex remove = std::regex("^remove [0-9]{8}$");
    std::regex searchID = std::regex("^search [0-9]{8}$");
    std::regex searchName = std::regex("^search \"[A-Z]?[a-z]* *?[A-Z]?[a-z]*?\"$");
    std::regex printInorder = std::regex("^printInorder$");
    std::regex printPreorder = std::regex("^printPreorder$");
    std::regex printPostorder = std::regex("^printPostorder$");
    std::regex printLevelCount = std::regex("^printLevelCount$");
    std::regex removeInorder = std::regex("^removeInorder [0-9]*$");

    // validate
    if(std::regex_match(line,insert)){
        textQ.push("insert");
        std::string sub = line.substr(8);
        int end = sub.find("\"");
        sub = line.substr(8, end);
        textQ.push(sub);
        sub = line.substr(8+end+2, 8);
        numQ.push(stoi(sub));
    }
    else if(std::regex_match(line,remove)){
        textQ.push("remove");
        std::string sub = line.substr(7,8);
        numQ.push(stoi(sub));
    }
    else if(std::regex_match(line,searchID)){
        textQ.push("searchID");
        std::string sub = line.substr(7,8);
        numQ.push(stoi(sub));
    }
    else if(std::regex_match(line,searchName)){
        textQ.push("searchName");
        std::string sub = line.substr(8);
        int end = sub.find("\"");
        sub = line.substr(8, end);
        textQ.push(sub);
    }
    else if(std::regex_match(line,printInorder)){
        textQ.push("printInorder");
    }
    else if(std::regex_match(line,printPreorder)){
        textQ.push("printPreorder");
    }
    else if(std::regex_match(line,printPostorder)){
        textQ.push("printPostorder");
    }
    else if(std::regex_match(line,printLevelCount)){
        textQ.push("printLevelCount");
    }
    else if(std::regex_match(line,removeInorder)){
        textQ.push("removeInorder");
        std::string sub = line.substr(14,8);
        numQ.push(stoi(sub));
    }
    else
        textQ.push("unsuccessful");
    }

    // do instructions from queue
    while(!textQ.empty()){
        //get next instruction
        std::string instruction = textQ.front();
        textQ.pop();

        if(instruction == "insert"){
            // do insert funcion
            // pop from numQ and textQ
            int temp = numQ.front();
            numQ.pop();
            instruction = textQ.front();
            textQ.pop();
            tree.insert(temp, instruction);
        }
        else if(instruction == "remove"){
            // removeID
            int temp = numQ.front();
            numQ.pop();
            tree.remove(temp);
        }
        else if(instruction == "searchID"){
            // search using ID
            int temp = numQ.front();
            numQ.pop();
            tree.search(temp);
        }
        else if(instruction == "searchName"){
            // search using name
            instruction = textQ.front();
            textQ.pop();
            tree.searchName(instruction);
        }
        else if (instruction == "printInorder"){
            // print inorder
            tree.printInorder();
        }
        else if (instruction == "printPreorder"){
            // print Preorder
            tree.printPreorder();
        }
        else if (instruction == "printPostorder"){
            // print Postorder
            tree.printPostorder();
        }
        else if (instruction == "printLevelCount"){
            // print level count
            tree.printLevelCount();
        }
        else if (instruction == "removeInorder"){
            // remove Nth node
            int temp = numQ.front();
            numQ.pop();
            tree.removeInorder(temp);
        }
        else if(instruction == "unsuccessful"){
            std::cout<< "unsuccessful" <<std::endl;
        }
    }  
    return 0;
}

