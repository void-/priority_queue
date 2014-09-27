#include <iostream>
#include <random>
#include <vector>
#include <cassert>
#include <algorithm>
#include <time.h>

template <class T>
class tester;
#define TEST friend class tester<T>
#include "priority_queue.h"

using namespace std;

template <class T>
class tester
{
  public:
  static bool isHeapOrder(PriorityQueue<T> *);
};

/**
 *  @brief test the heap-order property of the priority queue.
 *
 *  I.e. make sure that each parent is greater than both its left and right
 *  children.
 *
 *  @return if the PriorityQueue satisfies the heap order property.
 */
template <class T>
bool tester<T>::isHeapOrder(PriorityQueue<T> *p)
//bool tester(PriorityQueue<T> *p)
{
  bool yes = true;
  for(unsigned int i = 1; i <= p->size(); ++i)
  {
    //check parent less than
    if(p->parent(i) > 0)
    {
      yes &= (p->heap[p->parent(i)] < p->heap[i]);
    }
    //check left child greater
    if(p->leftInBounds(i))
    {
      yes &= (p->heap[i] < p->heap[p->leftChild(i)]);
    }
    //check right child greater
    if(p->rightInBounds(i))
    {
      yes &= (p->heap[i] < p->heap[p->rightChild(i)]);
    }
  }
  return yes;
}

/**
 *  @brief test PriorityQueue.
 *
 *  Testing procedure:\n
 *  <p>
 *  - Add elements to a vector and a priority queue
 *  - Sort the vector
 *  - Check the vector's elements match the priority queue
 *  <\p>
 */
int main(void)
{
  PriorityQueue<int> p;
  vector<int> v;
  unsigned int t;

  srand(time(NULL));

  for(unsigned int i = 0; i < 0x100; ++i)
  {
    t = rand();
    v.push_back(t);
    p.insert(t);
    assert(tester<int>::isHeapOrder(&p));
  }

  sort(v.begin(), v.end());

  for(auto i = v.begin(); i != v.end(); ++i)
  {
    assert(tester<int>::isHeapOrder(&p));
    assert(*i == p.removeMin());
  }
}
