#include <stdexcept>

template <typename T> class Queue {
    private:
        struct Node {
            T data;
            Node* next;
        };

        Node* front;
        Node* rear;
    
    public:
        Queue(){
            front = nullptr;
            rear = nullptr;
        }

        void enqueue(T data){
            if (front == nullptr) {
                front = new Node{data, nullptr};
                rear = front;
            } else if (rear == nullptr){
                rear = new Node{data, nullptr};
                front->next = rear;
            } else {
                rear->next = new Node{data, nullptr};
                rear = rear->next;
            }
        }

        void dequeue(){
            if(front == nullptr) throw std::length_error("No Elements in Queue");
            else{
                Node* temp = front;
                front = front->next;
                delete temp;

                if(front == nullptr) {
                    rear = nullptr;
                }
            }
        }

        T peek() const {
            if (front == nullptr) throw std::length_error("No Elements in Queue");
            return front->data;
        }

        bool isEmpty() const {
            return front == nullptr;
        }
};