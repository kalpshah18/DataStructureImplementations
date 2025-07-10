#include <iostream>
#include <stdexcept>

template <typename T> class CircularQueue {
    private:
        struct Node{
            T data;
            Node* next;
        };
        Node* rear;
    public:
        CircularQueue(){
            rear = nullptr;
        }
        
        bool isEmpty(){
            if(!rear) return true;
            return false;
        }

        void enqueue(T data){
            Node* newNode = new Node{data, nullptr};

            if(this->isEmpty()){
                newNode->next = newNode;
                rear = newNode;
            } else {
                newNode->next = rear->next;
                rear->next = newNode;
                rear = newNode;
            }
        }

        void dequeue(){
            if(this->isEmpty()){
                throw std::underflow_error("Queue Underflow");
                return;
            }

            if(rear->next == rear){
                delete rear;
                rear = nullptr;
            } else {
                Node* temp = rear->next;
                rear->next = temp->next;
                delete temp;
            }
        }

        T peek(){
            if(this->isEmpty()){
                throw std::length_error("Empty Queue");
                return -1;
            }
            return rear->next->data;
        }

        void print(){
            Node* temp = rear->next;
            do {
                std::cout << temp->data << " ";
                temp = temp->next;
            } while(temp != rear);
            std::cout << std::endl;
        }
};