#include <iostream>
#include <queue>
#include <vector>

class AVL{
    private:
        // TreeNode definition taken and modified from lecture slides
        struct TreeNode{
            int val;
            std::string name;
            int height; // Balance factor
            TreeNode *left;
            TreeNode *right;
            
            TreeNode(int x, std::string title): val(x), name(title), left(nullptr), right(nullptr){}
            //~TreeNode();
            
        };

        TreeNode* insertHelper(TreeNode*& node, int key, std::string title);
        TreeNode* rotateLeft(TreeNode* node);
        TreeNode* rotateRight(TreeNode* node);
        void preorder(TreeNode* root, std::vector<std::string> &q);
        void inorder(TreeNode* root, std::vector<TreeNode*> &q);
        void postorder(TreeNode* root, std::vector<std::string> &q);
        TreeNode* findID(TreeNode*& node, int ID, TreeNode* &parent);
        void preorderSearch(TreeNode* root, std::queue<int> &q, std::string title);
        AVL::TreeNode* succesor(TreeNode* node);
        int maxHeight(TreeNode* root);
        TreeNode* root = nullptr;
        void destructTree(TreeNode* &node);

        
    // public prototypes of main functions
    public:
        void insert(int k, std::string name);
        void printPostorder();
        void printInorder();
        void printPreorder();
        void remove(int ID);
        void search(int ID);
        void searchName(std::string title);
        void removeInorder(int N);
        void printLevelCount();

        //Destructor
        ~AVL();    
};

//Tree destructor to prevent memory leaks (hopefully)
    void AVL::destructTree(TreeNode* &node){
        if(node != nullptr){
        destructTree(node->left);
        destructTree(node->right);
        delete node;
        }
    }
    AVL::~AVL(){
        destructTree(root);
    }


// From lecture slides
AVL::TreeNode* AVL::insertHelper(TreeNode*& node, int key, std::string title){
    //insert node
    if(node == nullptr){
        std::cout<<"successful"<<std::endl;
        node = new TreeNode(key, title);
    }
    else if(key == node->val){
        std::cout<<"unsuccessful"<<std::endl;
        return node;
    }
    else if(key < node->val)
        node->left = insertHelper(node->left, key, title);
    else
        node->right = insertHelper(node->right, key, title);
    
    // calculate height (calculated recursively when inserted)
    node->height = (maxHeight(node->left) - maxHeight(node->right));

    //rotations
    //right heavy
    if(node->height == -2){
        // right left
        if(node->right->height == 1){
            node->right = rotateRight(node->right);
            node = rotateLeft(node);
        }
        // right right
        else
            node = rotateLeft(node);
    }
    // left heavy tree
    else if(node->height == 2){
        //left right
        if(node->left->height == -1){
            node->left = rotateLeft(node->left);
            node = rotateRight(node);
        }
        //left left
        else
            node = rotateRight(node);
    }
    return node;
}
void AVL::insert(int k, std::string name){
    insertHelper(root, k, name);
}




// Left rotation (from lecture slides)
AVL::TreeNode* AVL::rotateLeft(TreeNode* node){
    TreeNode* grandchild = node->right->left;
    TreeNode* newParent = node->right;
    newParent->left = node;
    node->right = grandchild;
    return newParent;
}
// Right Rotation (mirror of left)
AVL::TreeNode* AVL::rotateRight(TreeNode* node){
    TreeNode* grandchild = node->left->right;
    TreeNode* newParent = node->left;
    newParent->right = node;
    node->left = grandchild;
    return newParent;
}




// Traversals (did this on leetcode before)
//Preorder traversal and print
void AVL::preorder(TreeNode* node, std::vector<std::string> &q){
    if(node != nullptr){
    q.push_back(node->name);
    preorder(node->left, q);
    preorder(node->right, q);
    }
}
void AVL::printPreorder(){
    std::vector<std::string> preQ;
    preorder(root, preQ);
    if(preQ.size()>0){
        for(int i = 0; i < preQ.size()-1; i++){
            std::cout<< preQ[i]<<", ";
        }
        std::cout<<preQ[preQ.size()-1]<<std::endl;
    }
}




//Inorder Traversal and print
void AVL::inorder(TreeNode* node, std::vector<TreeNode*> &q){
    if(node != nullptr){
    inorder(node->left, q);
    q.push_back(node);
    inorder(node->right, q);
    }
}
void AVL::printInorder(){
    std::vector<TreeNode*> inQ;
    inorder(root, inQ);
    if(inQ.size()>0){
        for(int i = 0; i < inQ.size()-1; i++){
            std::cout<< inQ[i]->name<<", ";
        }
        std::cout<<inQ[inQ.size()-1]->name<<std::endl;
    }
}




// Postorder traversal and print
void AVL::postorder(TreeNode* node, std::vector<std::string>& q){
    if(node != nullptr){
    postorder(node->left, q);
    postorder(node->right, q);
    q.push_back(node->name);
    }
}
void AVL::printPostorder(){
    std::vector<std::string> postQ;
    postorder(root, postQ);
    if(postQ.size()>0){
        for(int i = 0; i < postQ.size()-1; i++){
            std::cout<< postQ[i]<<", ";
        }
        std::cout<<postQ[postQ.size()-1]<<std::endl;
    }
}




//search and remove by ID
AVL::TreeNode* AVL::findID(TreeNode*& node, int ID, TreeNode*& parent){
    if(node == nullptr){
        return nullptr;
    }
    else if(node->val == ID)
        return node;
    else if(ID < node->val){
        parent = node;
        return findID(node->left, ID, parent);
    }
    else if(ID > node->val){
        parent = node;
        return findID(node->right, ID, parent);
    }
    return nullptr;
}

// remove by ID
void AVL::remove(int ID){
    TreeNode* parent = nullptr;
    TreeNode* found = findID(root, ID, parent);
    if(found != nullptr){
        // right child
        if(found->left== nullptr && found->right != nullptr){
            if(found!= root){
                parent->right = found->right;
            }
            else{
                root = found->right;
            }
            delete found;
        }
        //left child
        else if(found->left != nullptr && found->right == nullptr){
            if(found != root){
                parent->left = found->left;
            }
            else{
                root = found->left;
            }
            delete found;
        }
        // 2 child succesor
        else if(found->left != nullptr && found->right != nullptr){
            // struggled with 2 child deletion and got inspiration from https://www.techiedelight.com/deletion-from-bst/
            TreeNode* succ = succesor(found);
            std::string name = succ->name;
            int num = succ->val;
            remove(num);
            found->name = name;
            found->val = num;
            return;
        }
        // no child
         else{
            if(found == root){
                root = nullptr;
            }
            else{
                if(parent->left == found)
                    parent->left = nullptr;
                else
                    parent->right = nullptr;
            }
            delete found;
         }   
        std::cout<< "successful" <<std::endl;
    }
    else{
        std::cout<< "unsuccessful" <<std::endl;
    }
}
//search by ID
void AVL::search(int ID){
    TreeNode* non = nullptr;
    TreeNode* found = findID(root, ID, non);
    if(found != nullptr){
        std::cout<< found->name <<std::endl;
    }
    else
        std::cout<< "unsuccessful" <<std::endl;
}




//Search by name
void AVL::preorderSearch(TreeNode* node, std::queue<int> &q, std::string title){
    if(node != nullptr){
        if(node->name == title){
            q.push(node->val);
        }
        preorderSearch(node->left, q, title);
        preorderSearch(node->right, q, title);
    }
}
void AVL::searchName(std::string title){
    std::queue<int> nameQ;
    preorderSearch(root, nameQ, title);
    if(nameQ.empty())
        std::cout<<"unsuccessful"<<std::endl;
    else{
        while(!nameQ.empty()){
            std::cout<< nameQ.front()<<std::endl;
            nameQ.pop();
        }
    }
}



// remove inorder
void AVL::removeInorder(int N){
    std::vector<TreeNode*> removeQ;
    inorder(root,removeQ);
    if(removeQ.size() < N+1){
        std::cout<< "unsuccessful"<<std::endl;
    }
    else{
        int ID = removeQ[N]->val;
        // use previos remove function
        remove(ID);
    }
}
//successor 
AVL::TreeNode* AVL::succesor(TreeNode* node){
    TreeNode* successor = node->right;
    while(successor->left != nullptr){
        successor = successor->left;
    }
    return successor;
}



// Find height of left and right subtree to find max height
int AVL::maxHeight(TreeNode* node){
    if(node == nullptr)
        return 0;
    else
        return (1 + std::max(maxHeight(node->left), maxHeight(node->right)));
}
void AVL::printLevelCount(){
    int level = maxHeight(root);
    std::cout<<level<<std::endl;
}
