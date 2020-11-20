#ifndef ListNode_H
#define ListNode_H
#include <iostream>
using namespace std;

template <class T>
class ListNode
{
  public:
    ListNode();
    ListNode(T d);
    ~ListNode();

    T data;
    ListNode<T> *next;
    ListNode<T> *prev;
};


template<class T>
ListNode<T>::ListNode()
{

}

template<class T>
ListNode<T>::ListNode(T d)
{
  next = NULL;
  prev = NULL;
  data = d;
}


template<class T>
ListNode<T>::~ListNode()
{
  next = NULL;
  prev = NULL;
}
#endif
