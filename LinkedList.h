#include <cstddef>

template <typename T> class Node{
	T data;
	Node* next;
	
	Node()
	{
		data = NULL;
		next = nullptr;
	}
	
	Node(T data)
	{
		this->data = data;
		this->next = nullptr;
	}

	Node(T data, Node* next)
	{
		this->data = data;
		this->next = next;
	}
	
	void setData(T data){
		this->data = data;
	}

	void setNext(Node* next)
	{
		this->next = next;
	}
};
