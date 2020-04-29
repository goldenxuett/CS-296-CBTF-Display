#ifndef QUEUE_H
#define QUEUE_H

#include <Arduino.h>

template<class T>
class Queue {
    public:
        Queue(const T* array, size_t n);
        Queue();
        ~Queue();
        void push(const T &node);
        T pop();
        T peek();
        bool isEmpty();
        void clear();
        void lock();
        int size();

    private:
        bool locked;
        size_t current;
        size_t front;
        size_t back;
        T* elements;
        int max_elements;
};

template<class T>
Queue<T>::Queue(const T* array, size_t n) {
    max_elements = 256;
    elements = new T[max_elements + 1];
    front = 0;
    back = 0;
    current = 0;
    locked = false;
    for (size_t i = 0; i < n; i++) {
        push(array[i]);
    }
}

template<class T>
Queue<T>::Queue() {
  max_elements = 256;
  locked = false;
  elements = new T[max_elements + 1];
  front = 0;
  back = 0;
  current = 0;
}

template<class T>
int Queue<T>::size() {
    return back - front;
}

template <class T>
void Queue<T>::lock() {
    locked = !locked;
}

template<class T>
Queue<T>::~Queue<T>() {
  clear();
}

template<class T>
void Queue<T>::push(const T &node) {
    elements[back] = node;
    back++;
    if (back > max_elements - 2) {
        T* holder =  new T[max_elements + 1];
        for (size_t i = front; i < back; i ++) {
            holder[i - front] = holder[front];
        }
        clear();
        elements = holder;
        back = back - front;
        current = current - front;
        front = 0;
    } 
}

template<class T>
T Queue<T>::pop() {
    if (!(locked) && (back - front) != 0) {
        T top_element = peek();
        front++;
        current++;
        return top_element;
    } else if (locked && current < back) {
        T top_element = peek();
        current++;
        return top_element;
    } else if (locked && current == back && back - front != 0) {
        current = front;
        T top_element = peek();
        current++;
        return top_element;
    }

    return T();
}

template<class T>
T Queue<T>::peek() {
    return elements[current];
}

template<class T>
bool Queue<T>::isEmpty() {
    return size() == 0;
}

template<class T>
void Queue<T>::clear() {
    delete[] elements;
    elements = NULL;
}

#endif