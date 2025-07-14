#include <iostream>
#include <stack>
#include <vector>
#include <cmath>
#include <string>

template <typename T> struct Node {
    T data;
    Node* left;
    Node* right;

    public:
        int containsNode(Node * root, T data){
            if(root == nullptr) return 0;
            int x = root->data == data ? 1 : 0;
            return x | containsNode(root->left, data) | containsNode(root->right, data);
        }

        Node* insert(Node* root, T data){
            if(root == nullptr){
                Node<T>* tmp = new Node<T>;
                tmp->data = data;
                tmp->left = tmp->right = nullptr;
                return tmp;
            }

            if(data < root->data){
                root->left = insert(root->left, data);
                return root;
            } else if(data > root->data){
                root->right = insert(root->right, data);
                return root;
            } else {
                return root;
            }
        }

        void deleteTree(Node* root){
            if(root != nullptr){
                deleteTree(root->left);
                deleteTree(root->right);
                delete root;
            }
        }
};

template <typename T> class Set {
    Node<T>* root;
    int size;

    public:
        Set(){
            root = nullptr;
            size = 0;
        }

        Set(const Set& s){
            root = s.root;
            size = s.size;
        }

        ~Set(){
            if(root != nullptr){
                root->deleteTree(root);
            }
        }

        void add(const T data){
            if(!contains(data)){
                root = root ? root->insert(root, data) : root->insert(nullptr, data);
                size++;
            }
        }

        Set unionSet(Set& s){
            Set<T> res;
            if(root == nullptr) return s;
            if(s.root == nullptr) return *this;

            std::stack<Node<T>*> nodeStack1;
            nodeStack1.push(root);

            while(!nodeStack1.empty()){
                Node<T>* node;
                node = nodeStack1.top();
                nodeStack1.pop();

                res.add(node->data);

                if(node->right) nodeStack1.push(node->right);
                if(node->left) nodeStack1.push(node->left);
            }

            std::stack<Node<T>*> nodeStack2;
            nodeStack2.push(s.root);

            while(!nodeStack2.empty()){
                Node<T>* node;
                node = nodeStack2.top();
                nodeStack2.pop();

                res.add(node->data);
                if(node->right) nodeStack2.push(node->right);
                if(node->left) nodeStack2.push(node->left);
            }

            return res;
        }

        Set intersectionSet(Set& s){
            Set<T> res;
            if(root == nullptr) return res;
            
            std::stack<Node<T>*> nodeStack;
            nodeStack.push(root);

            while(!nodeStack.empty()){
                Node<T>* node;
                node = nodeStack.top();
                nodeStack.pop();
                if(s.contains(node->data)) res.add(node->data);
                if(node->right) nodeStack.push(node->right);
                if(node->left) nodeStack.push(node->left);
            }

            return res;
        }

        Set complementSet(Set& U){
            return (U - *this);
        }

        Set operator-(Set& s){
            Set<T> res;
            if(root == nullptr) return res;
            
            std::stack<Node<T>*> nodeStack;
            nodeStack.push(this->root);

            while(!nodeStack.empty()){
                Node<T>* node;
                node = nodeStack.top();
                nodeStack.pop();
                if(!s.contains(node->data)) res.add(node->data);
                if(node->right) nodeStack.push(node->right);
                if(node->left) nodeStack.push(node->left);
            }

            return res;
        }

        bool operator==(Set& s){
            if(s.getSize() != size){
                return false;
            }
            
            if(root == nullptr) return s.root == nullptr;

            std::stack<Node<T>*> nodeStack;
            nodeStack.push(this->root);

            while (!nodeStack.empty()) {
                Node<T>* node;
                node = nodeStack.top();
                nodeStack.pop();
                if (!s.contains(node->data)) {
                    return false;
                }
                if (node->right)
                    nodeStack.push(node->right);
                if (node->left)
                    nodeStack.push(node->left);
            }
            return true;
        }

        T* toArray(){
            if(size == 0) return nullptr;
            
            T* arr = new T[size];
            int i = 0;
            std::stack<Node<T>*> nodeStack;
            nodeStack.push(this->root);

            while (!nodeStack.empty()) {
                Node<T>* node;
                node = nodeStack.top();
                nodeStack.pop();

                arr[i++] = node->data;

                if (node->right)
                    nodeStack.push(node->right);
                if (node->left)
                    nodeStack.push(node->left);
            }
            return arr;
        }

        bool contains(T data){
            if(root == nullptr) return false;
            return root->containsNode(root, data) ? true : false;
        }

        int getSize(){
            return size;
        }

        std::vector<std::vector<T>> powerSet(){
            std::vector<std::vector<T>> res;
            if(size == 0){
                res.push_back(std::vector<T>());
                return res;
            }
            
            int n = pow(2, size);
            T* arr = toArray();

            for(int i = 0; i < n; i++){
                std::vector<T> subset;
                for(int j = 0; j < size; j++){
                    if((i & (1 << j)) != 0) {
                        subset.push_back(arr[j]);
                    }
                }
                res.push_back(subset);
            }
            
            delete[] arr;
            return res;
        }
};