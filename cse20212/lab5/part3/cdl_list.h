/*
Matt Rundle

Circularly doubly linked list header and implementation.
*/

#include <iostream>
#include <deque>
using namespace std;

template<typename T>
class cdl_list {

	public:

		cdl_list();
		~cdl_list();
		void insertFromFront(T);
		void insertFromBack(T);
		void deleteFront();
		void deleteBack();
		bool isEmpty();
		void print();
		int getSize();
		int getCurrent();

		void reset();
		void next();
		void previous();
		T currentValue();
		void removeNode();
		cdl_list& operator++(); // prefix
		cdl_list& operator++(int); // postfix
		cdl_list& operator--(); // prefix

	private:

		deque<T> List;
		int current;

};

template<typename T>
cdl_list<T>::cdl_list(){
	current = 0;
}

template<typename T>
cdl_list<T>::~cdl_list(){

}

template<typename T>
void cdl_list<T>::insertFromFront(T elem){
	List.push_front(elem);
}

template<typename T>
void cdl_list<T>::insertFromBack(T elem){
	List.push_back(elem);
}

template<typename T>
void cdl_list<T>::deleteFront(){
	if(List.size()>0){
		List.pop_front();
	}else{
		cout << "List is empty." << endl;
	}
}

template<typename T>
void cdl_list<T>::deleteBack(){
	if(List.size()>0){	
		List.pop_back();
	}else{
		cout << "List is empty." << endl;
	}
}

template<typename T>
bool cdl_list<T>::isEmpty(){
	if(List.size()<=0) return 1;
	if(List.size()>0) return 0;
}

template<typename T>
void cdl_list<T>::print(){
	for(int i=0;i<List.size();i++){
		cout << List[i] << " ";
	}
	cout << "\n";
}

template<typename T>
int cdl_list<T>::getSize(){
	return List.size();
}

template<typename T>
void cdl_list<T>::reset(){
	current = 0;
}

template<typename T>
void cdl_list<T>::next(){
	current++;
	if(current > (List.size()-1)){
		current = 0;
	}
}

template<typename T>
void cdl_list<T>::previous(){
	if(current > 0){
		current--;
	}else{
		current = (List.size()-1);
	}
}

template<typename T>
T cdl_list<T>::currentValue() {
	return List[current];
}

template<typename T>
void cdl_list<T>::removeNode() {
	List.erase(List.begin() + current);
	if(current > (List.size()-1)){
		current = 0;
	}
}

template<typename T>
cdl_list<T>& cdl_list<T>::operator++() {
	next();
	return *this;
}

template<typename T>
cdl_list<T>& cdl_list<T>::operator++(int) {
	++(*this);
}

template<typename T>
cdl_list<T>& cdl_list<T>::operator--() {
	current--;
	return *this;
}
