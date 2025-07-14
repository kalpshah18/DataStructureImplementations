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

        ~Set(){
            if(root != nullptr){
                root->deleteTree(root);
            }
        }
};

int main(){
    std::cout << "=== Set Class Implementation Tests ===" << std::endl;
    
    // Test 1: Basic operations
    std::cout << "\n1. Testing basic operations:" << std::endl;
    Set<int> s1;
    s1.add(5);
    s1.add(3);
    s1.add(7);
    s1.add(1);
    s1.add(9);
    s1.add(3); // Duplicate - should not increase size
    
    std::cout << "Set size after adding elements (with duplicate): " << s1.getSize() << std::endl;
    std::cout << "Contains 3: " << (s1.contains(3) ? "Yes" : "No") << std::endl;
    std::cout << "Contains 10: " << (s1.contains(10) ? "Yes" : "No") << std::endl;
    
    // Test 2: Union operation
    std::cout << "\n2. Testing union operation:" << std::endl;
    Set<int> s2;
    s2.add(3);
    s2.add(4);
    s2.add(8);
    s2.add(2);
    
    Set<int> unionResult = s1.unionSet(s2);
    std::cout << "Union size: " << unionResult.getSize() << std::endl;
    std::cout << "Union contains 4: " << (unionResult.contains(4) ? "Yes" : "No") << std::endl;
    std::cout << "Union contains 7: " << (unionResult.contains(7) ? "Yes" : "No") << std::endl;
    
    // Test 3: Intersection operation
    std::cout << "\n3. Testing intersection operation:" << std::endl;
    Set<int> intersectResult = s1.intersectionSet(s2);
    std::cout << "Intersection size: " << intersectResult.getSize() << std::endl;
    std::cout << "Intersection contains 3: " << (intersectResult.contains(3) ? "Yes" : "No") << std::endl;
    std::cout << "Intersection contains 5: " << (intersectResult.contains(5) ? "Yes" : "No") << std::endl;
    
    // Test 4: Difference operation
    std::cout << "\n4. Testing difference operation:" << std::endl;
    Set<int> diffResult = s1 - s2;
    std::cout << "Difference (s1 - s2) size: " << diffResult.getSize() << std::endl;
    std::cout << "Difference contains 5: " << (diffResult.contains(5) ? "Yes" : "No") << std::endl;
    std::cout << "Difference contains 3: " << (diffResult.contains(3) ? "Yes" : "No") << std::endl;
    
    // Test 5: Equality operation
    std::cout << "\n5. Testing equality operation:" << std::endl;
    Set<int> s3;
    s3.add(5);
    s3.add(3);
    s3.add(7);
    s3.add(1);
    s3.add(9);
    
    std::cout << "s1 == s3: " << (s1 == s3 ? "Yes" : "No") << std::endl;
    std::cout << "s1 == s2: " << (s1 == s2 ? "Yes" : "No") << std::endl;
    
    // Test 6: Power set operation
    std::cout << "\n6. Testing power set operation:" << std::endl;
    Set<int> smallSet;
    smallSet.add(1);
    smallSet.add(2);
    smallSet.add(3);
    
    std::vector<std::vector<int>> powerSetResult = smallSet.powerSet();
    std::cout << "Power set size for {1,2,3}: " << powerSetResult.size() << std::endl;
    std::cout << "Power set subsets:" << std::endl;
    for(int i = 0; i < powerSetResult.size(); i++){
        std::cout << "{ ";
        for(int j = 0; j < powerSetResult[i].size(); j++){
            std::cout << powerSetResult[i][j] << " ";
        }
        std::cout << "}" << std::endl;
    }
    
    // Test 7: Empty set operations
    std::cout << "\n7. Testing empty set operations:" << std::endl;
    Set<int> emptySet;
    std::cout << "Empty set size: " << emptySet.getSize() << std::endl;
    std::cout << "Empty set contains 1: " << (emptySet.contains(1) ? "Yes" : "No") << std::endl;
    
    Set<int> unionWithEmpty = s1.unionSet(emptySet);
    std::cout << "Union with empty set size: " << unionWithEmpty.getSize() << std::endl;
    
    Set<int> intersectWithEmpty = s1.intersectionSet(emptySet);
    std::cout << "Intersection with empty set size: " << intersectWithEmpty.getSize() << std::endl;
    
    // Test 8: toArray operation
    std::cout << "\n8. Testing toArray operation:" << std::endl;
    int* arr = s1.toArray();
    if(arr != nullptr){
        std::cout << "Array elements: ";
        for(int i = 0; i < s1.getSize(); i++){
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
        delete[] arr;
    }
    
    // Test 9: String type test
    std::cout << "\n9. Testing with string type:" << std::endl;
    Set<std::string> stringSet;
    stringSet.add("apple");
    stringSet.add("banana");
    stringSet.add("cherry");
    stringSet.add("apple"); // Duplicate
    
    std::cout << "String set size: " << stringSet.getSize() << std::endl;
    std::cout << "Contains 'banana': " << (stringSet.contains("banana") ? "Yes" : "No") << std::endl;
    std::cout << "Contains 'grape': " << (stringSet.contains("grape") ? "Yes" : "No") << std::endl;
    
    // Test 10: Destructor test
    std::cout << "\n10. Testing destructor:" << std::endl;
    {
        Set<int> tempSet;
        tempSet.add(100);
        tempSet.add(50);
        tempSet.add(150);
        tempSet.add(25);
        tempSet.add(75);
        std::cout << "Created temporary set with " << tempSet.getSize() << " elements" << std::endl;
        std::cout << "Temporary set going out of scope - destructor should be called..." << std::endl;
    } // Destructor is called here when tempSet goes out of scope
    std::cout << "Temporary set destroyed successfully (no memory leaks if destructor works)" << std::endl;
    
    // Additional destructor test with dynamic allocation
    std::cout << "Testing destructor with dynamically allocated set:" << std::endl;
    Set<int>* dynamicSet = new Set<int>();
    dynamicSet->add(10);
    dynamicSet->add(20);
    dynamicSet->add(30);
    std::cout << "Created dynamic set with " << dynamicSet->getSize() << " elements" << std::endl;
    delete dynamicSet; // Explicit destructor call
    std::cout << "Dynamic set destroyed successfully" << std::endl;
    
    std::cout << "\n=== All Tests Completed ===" << std::endl;
    return 0;
}