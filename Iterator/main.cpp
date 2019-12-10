/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: carlos
 *
 * Created on December 3, 2019, 7:46 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

class Iterator {
public:
    virtual void first() = 0;
    virtual void next() = 0;
    virtual bool isDone() = 0;
    virtual int currentItem() = 0;
};

class Queue {
    int items[10];
    int front;
    int rear;
    int nums;
public:
    friend class QueueIter;
    Iterator *createIterator()const;
    
    Queue() {
        front = 0;
        rear = -1;
        nums = 0;
    }

    void enqueue(int in) {
        rear = (rear + 1) % 10;
        items[rear] = in;
        nums++;
    }

    int dequeue() {
        int temp = items[front];
        front = (front + 1) % 10;
        nums--;
        return temp;
    }

    bool isEmpty() {
        return (nums == 0);
    }
};

class QueueIter : public Iterator {
    const Queue *que;
    int index;
    bool flag;
public:
    QueueIter(const Queue* q){
        que = q;
    }

    void first() {
        flag = true;
        index = que->front;
    }

    void next() {
        flag = false;
        index = (index + 1) % 10;
    }

    bool isDone() {
        if (flag == false)
            return (index == (que->rear + 1) % 10);
    }

    int currentItem() {
        return que->items[index];
       
    }
};

Iterator *Queue::createIterator()const {
    return new QueueIter(this);
}
void printQueue(const Queue& q){
    Iterator *it = q.createIterator();
    
    for (it->first(); !it->isDone(); it->next()){
        cout << it->currentItem() << endl;
    }
    delete it;
}
/*
 * 
 */
int main() {
    Queue q1;
    for (int i = 1; i < 5; i++)
        q1.enqueue(i);
    q1.dequeue();
    q1.dequeue();
    q1.enqueue(7);
    q1.enqueue(9);
    
    printQueue(q1);
    
    
    
    cout<<"=================================="<<endl;
    
    while (!q1.isEmpty()) {
        cout << q1.dequeue() << endl;
    }
    
    
    cout<<"=================================="<<endl;
    
    for (int i = 0; i < 10; i++){
        q1.enqueue(i);
    }
    printQueue(q1);
    return 0;
}

