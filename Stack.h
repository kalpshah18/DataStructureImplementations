#include <vector>
#include <stdexcept>

template <typename T> class Stack {
    private:
        T top; // Top Element Index
        std::vector<T> vect; // Array for Stack
    
    public:
        Stack() {
            top = -1;
        }

        void push(T data) {
            vect.push_back(data);
            top++;
        }

        void pop() {
            if(top >= 0){
                vect.pop_back();
                top--;
            } else {
                throw std::length_error("Stack has no Elements.");
            }
        }

        T peek() const {
            if(top >= 0) return vect[top];
            else throw std::length_error("Stack has no Elements");
        }

        bool isEmpty() const {
            if (top == -1) return true;
            return false;
        }
};