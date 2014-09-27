#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
#include <vector>

#ifndef TEST
  #define TEST
#endif

/**
 *  PriorityQueue class defines a min-heap that is useful for maintaining a
 *  sorted collection of entries and allowing for quick access to the smallest
 *  entry in the collection.
 *
 *  <p>
 *  Entries are stored in contiguous memory and internal resizing may occur as
 *  new entries are inserted. As new items are inserted, old items are shuffled
 *  around to maintain the heap property of the internal data structure.
 *  Comparisons are made using the less-than, <, operator. In the future, this
 *  can be generalized by a template parameter.
 *  </p>
 *
 *  Template Parameters:\n
 *    T Type of the entries stored in the PriorityQueue().
 *
 *  Member Variables:\n
 *    heap std::vector maintaining internal storage of entries.
 *    TEST macro used for tests to access to private member variables.
 *
 *  Member Functions:
 *  <p>
 *    - (Constructor) public constructor.
 *    - (Destructor) public destructor.
 *    - size() return logical size.
 *    - min() return the minimum entry.
 *    - removeMin() remove the minimum entry and return it.
 *    - insert() insert a new entry.
 *    - parent() private helper return the parent location given a position.
 *    - leftChild() private helper return left child location given a position.
 *    - rightChild() private helper return right child location given a
 *        position.
 *    - leftInBounds() private helper return whether left child is inbounds.
 *    - rightInBounds() private helper return whether right child is inbounds.
 *    - minChild() private helper return the lesser child of a given position.
 *  </p>
 */
template <class T>
class PriorityQueue
{
  public:
    PriorityQueue();
    ~PriorityQueue();
    size_t size() const noexcept;
    T min() const;
    T removeMin();
    void insert(T);

  private:
    inline void swap(size_t, size_t);
    static inline size_t parent(size_t) noexcept;
    static inline size_t leftChild(size_t) noexcept;
    static inline size_t rightChild(size_t) noexcept;
    inline bool leftInBounds(size_t) const noexcept;
    inline bool rightInBounds(size_t) const noexcept;
    size_t minChild(size_t);
    std::vector<T> heap;
    TEST;
};

#include "priority_queue.hxx"
#endif
