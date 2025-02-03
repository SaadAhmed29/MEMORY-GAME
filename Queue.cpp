#include "Queue.h"

Queue::Queue()
{
	size = 0;
	front = 0;
	rear = -1;
}

bool Queue::isFull()
{
	return (size == MAX_SIZE);
}

bool Queue::isEmpty()
{
	return size == 0;
}

void Queue::Enqueue(int val)
{
	if (isFull()) {
		return;
	}
	else {
		rear = (rear + 1) % MAX_SIZE;
		arr[rear] = val;
		size++;
	}
}

int Queue::Dequeue()
{
	if (isEmpty()) {
		return 0;
	}
	else {
		int temp = arr[front];
		front = (front + 1) % MAX_SIZE;
		size--;
		return temp;
	}
}

//Resets the queue
void Queue::clear()
{
	size = 0;
	front = 0;
	rear = -1;
}

//Returns queue size
int Queue::queue_size()
{
	return size;
}

//Returns queue front
int Queue::queue_front()
{
	return arr[front];
}


