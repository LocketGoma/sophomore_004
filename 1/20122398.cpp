#include <iostream>
#include <string>
#include <list>
#include <iterator>
#include <stdlib.h>
using namespace std;

// 1. 템플릿 링크드 리스트 구현
// 2. 반복자 투입
// 3. 반복자 = 노드?


template <class T> class Chain;

template <class T>
class ChainIterator{ // 반복자 = 노드
	public:
	friend class Chain<T>;
	ChainIterator(T i) {
		this->data = i;
		}
		ChainIterator() {
		}

	typedef int size_type;
	typedef ChainIterator self_type;
	typedef ChainIterator value_type;
	typedef T& reference; // 데이터
	typedef ChainIterator* pointer; // 주소
	typedef std::forward_iterator_tag iterator_category;
	typedef int difference_type;
	ChainIterator(pointer ptr) : ptr_(ptr) { }
	self_type operator++() {  self_type i = *this; ptr_ = ptr_->next; return i;
	}
	self_type operator++(int junk) { ptr_ = ptr_->next;; return *this; } //후위?
	reference operator*() { return ptr_->data; }
	pointer operator->() { return ptr_; }
	bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
	bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }


private:
	T data;
	ChainIterator<T> *next = NULL;
	pointer ptr_ = next;
}; // 반복자

template <class T>
class Chain {
	public :
	Chain(int);
	~Chain();

	T& Front(); // 1번 원소를 반환하는 함수
	T& Back(); // 마지막 원소를 반환하는 함수
	T& Get(int i); // i번째 원소를 반환하는 함수
	void Print_all();

	void Input_front(const T& data); // 첫번째에 삽입
	void Input_back(const T& data);	// 마지막에 삽입
	void Input(const T& data,int location);

	void Del_front();// 첫번째 삭제
	void Del_back(); // 마지막 삭제
	void Del(int); // 중간 삭제

	void Destroy(); // 죄다 삭제

	ChainIterator<T> begin() {
	return ChainIterator<T>(head);
	}

	private :
	ChainIterator<T> *head;


	T* data_;
};

template <class T>
Chain<T>::Chain(int i) {
	head = NULL;
}
template <class T>
Chain<T>::~Chain() {
	Destroy();
	free(head);
}
template <class T>
void Chain<T>::Input(const T& data, int location) {
	ChainIterator<T> *insertChainIterator = new ChainIterator<T>(data);
	ChainIterator<T> *current = head;
	ChainIterator<T> *temp = NULL;
	int i = 0; // 위치 검사
	int ins = 1; // 삽입여부 검사
	if (location == 0) { // 맨 앞 삽입
	insertChainIterator->next = current;
	head = insertChainIterator;
}
else {
	for (ChainIterator<T> *ptr = head; ptr != NULL; ptr = ptr->next) {
	current = ptr;
	if (i == location - 1) {
		temp = current->next;
		insertChainIterator->next = temp;
		current->next = insertChainIterator;
		ins--;
	}
	i++;
	}
	if (ins) { // 범위 초과시 자동으로 맨 마지막 삽입.
		cout << "No point" << endl;
	Input_back(insertChainIterator->data);
		}
	}
}
template <class T>
void Chain<T>::Input_front(const T& data) {
	Input(data, 0);
}
template <class T> 
void Chain<T>::Input_back(const T& data) {
	ChainIterator<T> *insertChainIterator=new ChainIterator<T>(data);
	if (head == NULL) {
		head = insertChainIterator;
	}
	else {
		ChainIterator<T> *current = head;
		insertChainIterator->next = NULL;
	for (ChainIterator<T> *ptr = head; ptr != NULL; ptr = ptr->next) {
	current = ptr;
	}
	current->next = insertChainIterator;
	}
}
template <class T>
void Chain<T>::Print_all() { // 임시. 전체 출력구문
	if (head == NULL) {
	cout << "Chain is emply" << endl;
	}

	ChainIterator<T> *ret = NULL;
	for (ChainIterator<T> *ptr = head; ptr != NULL; ptr = ptr->next) {
	cout << ptr->data << " ";
	} cout << endl;
}
template <class T>
T& Chain<T>::Get(int location) { // 출력
	if (head == NULL) {
	cout << "Empty...;" << endl;
	return head->data;
	}
	else if (location == -1) { // 맨 마지막 출력
		ChainIterator<T> *ptr = head;
	for (; ptr != NULL; ptr = ptr->next) {
		if (ptr->next == NULL) {
		return ptr->data;
			}
		}
	}
	else if (location < 0) { // 잘못된 값 입력시 오류구문
	cout << "out of bound" << endl;
	return head->data;
	}
	else { // 기본형. 맨 앞 출력시 location에 0 때려박으면 됨.
	int i = 0;
	for (ChainIterator<T> *ptr = head; ptr != NULL; ptr = ptr->next) {
	if (i == location) {
	return ptr->data;
			}
		i++;
		}
	}
}
template <class T>
T& Chain<T>::Front() {
	return Get(0);
}
template <class T>
T& Chain<T>::Back() {
	return Get(-1);
}
template <class T>
void Chain<T>::Del(int location) {
	if (head == NULL) {
	cout << "Can't delete!" << endl;
	}
	else if (location == -1) { // 맨 마지막 지우기
	ChainIterator<T> *ptr = head; // 기본
	ChainIterator<T> *temp = NULL; // 임시
	for (; ptr != NULL; ptr = ptr->next) {
	if (ptr->next->next == NULL) {
	temp = ptr->next;
	ptr->next = NULL;
		}
	}
}
	else if (location == 0) {
	ChainIterator<T> *ptr = head; // 기본
	ChainIterator<T> *temp = NULL; // 임시
	head = ptr->next;
	}
	else {
	int i = 0;
	ChainIterator<T> *ptr = head; // 기본
	ChainIterator<T> *temp = NULL; // 임시
	for (; ptr != NULL; ptr = ptr->next) {
		if (i == location - 1) {
		temp = ptr->next->next;
		ptr->next = temp;
			}
		i++;
		}
	}
}
template <class T>
void Chain<T>::Del_front() {
	Del(0);
}
template <class T>
void Chain<T>::Del_back() {
	Del(-1);
}
template <class T>
void Chain<T>::Destroy() {
	ChainIterator<T> *ptr = head; // 기본
	ChainIterator<T> *temp = NULL; // 임시
	for (; ptr != NULL; ptr = temp) {
	{
	temp = ptr->next;
	free(ptr);
		}
	}
	head = NULL;
}
int main() {
	Chain<int> chain(1);
	chain.Input_back(1);
	chain.Input_back(2);
	chain.Input_back(3);
	chain.Input_back(4);
	chain.Input_back(5);
	chain.Input_back(6);
	chain.Input_back(7);
	chain.Input_back(8);
	chain.Input_back(9); // 1)
	chain.Print_all(); // 2) <- 편의를 위한 전체출력용 함수
	chain.Input_front(0); // 3)
	chain.Print_all(); // 4)
	chain.Input_back(10); // 5)
	chain.Print_all(); // 6)
	cout << chain.Front() << endl; // 7)
	cout << chain.Back() << endl; // 8)
	cout<<chain.Get(2)<<endl; // 9)
	chain.Del(0); // 10)
	chain.Print_all(); // 11)
	chain.Del(-1); // 12 :: -1 = 마지막 삭제 구문
	chain.Print_all(); // 13)
	chain.Input(100,2); // 14)
	chain.Print_all(); // 15)
	chain.Del(6); // 16
	chain.Print_all(); // 17)
	cout << "반복자 확인용" << endl;
	ChainIterator<int> id;
	id = chain.begin();
	id++;
	cout << *id << endl;
}

