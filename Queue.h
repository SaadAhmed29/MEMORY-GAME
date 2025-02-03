#include<iostream>
#define MAX_SIZE 50
using namespace std;

class Queue {
private:

	int arr[MAX_SIZE];
	int front, rear, size;

public:
	
	Queue();
	bool isFull();
	bool isEmpty();
	void Enqueue(int val);
	int Dequeue();
	void clear();
	int queue_size();
	int queue_front();

};

