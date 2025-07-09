#include <iostream>

template <typename T> class Vector{
	T* arr;
	int capacity;
	int size;
	
	public:
		Vector(){
			arr = new T[1];
			capacity = 1;
			size = 0;
		}
		
		~Vector(){
			delete[] arr;
		}
		
		void push_back(T data){
			if (size == capacity){
				T* temp = new T[2 * capacity];
				for(int i = 0; i < size; i++){
					temp[i] = std::move(arr[i]);
				}
				delete[] arr;
                temp.push_back(data);
                size++;
				capacity *= 2;
				arr = temp;
			} else {
				arr[size] = data;
				size++;
			}
		}
		
		void push(T data, int index){
			if (index > capacity - 1 && index >= 0) throw std::logic_error("Used push function to an Invalid Index");
			arr[index] = data;
		}
		
		void pop(){
			if (size == 0) {
				throw std::out_of_range("Vector is empty. Cannot pop.");
			}
			--size;
		}
		
		T get(int index){
			if (index < size) return arr[index];
			return -1;
		}
		
		int get_size(){
			return size;
		}
		
		int get_capacity(){
			return capacity;
		}
		
		void print(){
			for(int i = 0; i < size; i++){
				std::cout << arr[i] << " ";
			}
			std::cout << "\n";
		}
		
		void reserve(int reserve_size){
			T* temp = new T[reserve_size];
			delete[] arr;
			arr = temp;
			capacity = reserve_size;
			size = 0;
		}
};