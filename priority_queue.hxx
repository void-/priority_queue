#include <utility> //for std::swap

/**
 *  Implementation Notes:
 *  <p>
 *  The internal heap is implemented using a std::vector. Access to this vector
 *  is 1-based rather than zero-based unlike most c arrays. This is done so
 *  that all parent/child relationships can be generalized without having
 *  special cases for entries at position zero. The parent-child relationship
 *  works as follows: Suppose a parent is located at position n, its left child
 *  is location at position 2n, and its right child is located at 2n+1. To
 *  implement this, a meaningless entry is placed at position zero in the heap.
 *  Entries are inserted into the heap is a level-order manner, this is why
 *  the parent and child relationships are how they are, because new children
 *  are simply appended to the array.
 *  </p>
 */

/**
 *  @brief Constructs an empty PriorityQueue.
 *
 *  Initialize the internal heap to have an initial capacity of 1.
 *
 *  Complexity:\n
 *    Constant
 *
 *  @tparam T type of object stored.
 */
template <class T>
PriorityQueue<T>::PriorityQueue() : heap(01)
{
}

/**
 *  @brief Destructs a PriorityQueue and all its entries.
 *
 *  Complexity:\n
 *    O(n) where n is the PriorityQueue::size(), but this depends on whether
 *    the type parameter also needs to be destructed.
 * 
 *  @tparam T type of object stored.
 */
template <class T>
PriorityQueue<T>::~PriorityQueue()
{
}

/**
 *  @brief Returns the logical size of the PriorityQueue.
 *
 *  This is the number of entries that have been inserted into the
 *  PriorityQueue rather than the storage capacity.
 *
 *  Algorithm Note: 
 *  <p>
 *    1 is subtracted from the size of the internal heap because a filler value
 *    is placed at position zero. This filler value does not count as a part of
 *    the PriorityQueue. If a INT_MAX is returned, this means that the filler
 *    value has been deleted somehow.
 *  </p>
 *
 *  Complexity:
 *    Constant
 *
 *  @tparam T type of object stored.
 *  @return size_t size of PriorityQueue.
 */
template <class T>
size_t PriorityQueue<T>::size() const noexcept
{
  return (heap.size() - 01);
}

/**
 *  @brief Returns the minimum entry in the PriorityQueue.
 *
 *  In this implementation, the minimum entry in the PriorityQueue is always
 *  stored at location 1 in the internal heap.
 *
 *  Complexity:\n
 *    Constant time
 * 
 *  @tparam T type of object stored.
 *  @return T copy of the minimum entry in the PriorityQueue.
 */
template <class T>
T PriorityQueue<T>::min() const
{
  return heap[01];
}

/**
 *  @brief Removes the minimum entry in the PriorityQueue.
 *
 *  Remove and return the item with the minimum entry in the PriorityQueue,
 *  shrinking PriorityQueue::size() by a value of 1. The internal heap will be
 *  modified to preserve the internal heap-order property. The behavior when
 *  the heap is empty is undefined.
 *
 *  Algorithm:
 *  <p>
 *    - Put the last entry into the root of the heap.
 *    - Bubble it down the heap until it satisfies the heap-order property.
 *    - If, while bubbling down, the entry of interest has a value greater than
 *        that of <em>both</em> of its children: swap with the lesser of the
 *        two.
 *  </p>
 *
 *  Implementation notes:\n
 *    Always swap the bubbled entry with the lesser of the two children.
 *    Refer to the bubbled entry by its index i within the vector.
 *
 *  Complexity:\n
 *    O(log(n)) where n is PriorityQueue::size()
 * 
 *  @tparam T type of the object stored.
 *  @return T object stored at the minimum entry in the PriorityQueue.
 */
template <class T>
T PriorityQueue<T>::removeMin()
{
  T save = heap[1]; //save the min entry for returning
  heap[1] = heap.back();
  heap.pop_back(); //swap the first and last items

  size_t i = 1;
  size_t swaper;

  while(heap[(swaper = minChild(i))] < heap[i])
  {
    swap(i, swaper);
    i = swaper;
  }
  return save;
}

/**
 *  @brief Inserts a new entry into the PriorityQueue.
 *
 *  The internal heap will automatically modify itself to maintain the internal
 *  heap-order property.
 *
 *  Algorithm:
 *  <p>
 *    - Insert the new entry into the next free spot in the heap.
 *    - Bubble the new entry up the heap until the heap-order property is
 *        satisfied.
 *    - The heap-order property is satisfied when the new entry has children
 *        that are both greater than it and the entry has a parent that is less
 *        than it.
 *  </p>
 *
 *  Developer Note: Do we need to check both parent and children, or just
 *    parent?
 *
 *  Complexity:\n
 *    O(log(n)) amortized time, where n is PriorityQueue::size().
 *    In the worst case, this takes O(n) when the heap needs to resize.
 * 
 *  @tparam T type of object stored.
 *  @param val new object to be stored, will be copied.
 */
template <class T>
void PriorityQueue<T>::insert(T val)
{
  heap.push_back(val);
  size_t entryNo = size(); //location the new entry is at
  while(entryNo > 01 && val < heap[parent(entryNo)])
  {
    swap(entryNo, parent(entryNo)); //swap entry and its parent
    entryNo = parent(entryNo);
  }
}

/**
 *  @brief Given two indices swap them in the heap.
 *
 *  Algorithm:
 *  <p>
 *  Call std::swap on the elements at \p a and \p b.
 *  </p>
 *
 *  Complexity:\n
 *    O(1) for the swap, but proportional to the time to copy T.
 * 
 *  @tparam T type of the object stored.
 *  @param a first index to swap.
 *  @param b second index to swap.
 */
template <class T>
void PriorityQueue<T>::swap(size_t a, size_t b)
{
  std::swap(heap[a], heap[b]);
}

/**
 *  @brief Given a location will return the parent location.
 *
 *  The internal heap is maintained in contiguous memory, if an entry resides
 *  at a location n, its parent resides at location n/2.
 *
 *  Algorithm:
 *    Right shift operator is used for preformance to divide by two.
 *
 *  Complexity:\n
 *    Constant.
 * 
 *  @tparam T type of object stored.
 *  @param loc the location that you want the parent of.
 * 
 *  @return the parent location of the given location.
 */
template <class T>
inline size_t PriorityQueue<T>::parent(size_t loc) noexcept
{
  return (loc>>01);
}

/**
 *  @brief Given a location will return the leftChild location.
 *
 *  The internal heap is maintained in contiguous memory, if an entry resides
 *  at a location n, its leftChild resides at location n*2.
 *
 *  Algorithm:
 *    Left shift operator is used for preformance to multiply by two.
 *
 *  Complexity:\n
 *    Constant.
 * 
 *  @tparam T type of object stored.
 *  @param loc the array index to return the parent of.
 * 
 *  @return the parent location of the given location.
 */
template <class T>
inline size_t PriorityQueue<T>::leftChild(size_t loc) noexcept
{
  return (loc<<01);
}

/**
 *  @brief Given a location will return the rightChild location.
 *
 *  The internal heap is maintained in contiguous memory, if an entry resides
 *  at a location n, its rightChild resides at location n*2 + 1.
 *
 *  Algorithm:
 *    Left shift operator is used for preformance to multiply by two.
 *
 *  Complexity:\n
 *    Constant.
 * 
 *  @tparam T type of object stored.
 *  @param loc the location that you want the parent of.
 * 
 *  @return the parent location of the given location.
 */
template <class T>
inline size_t PriorityQueue<T>::rightChild(size_t loc) noexcept
{
  return ((loc<<01) + 01);
}

/**
 *  @brief Determines if the leftChild of the given location is within bounds
 *  of the PriorityQueue internal heap.
 * 
 *  @tparam T type of the object stored.
 *  @param loc int representing the location to test.
 * 
 *  @return whether the leftChild of the given location is a valid heap index.
 */
template <class T>
inline bool PriorityQueue<T>::leftInBounds(size_t loc) const noexcept
{
  return (leftChild(loc) <= size());
}

/**
 *  @brief Determines if the rightChild of the given location is within bounds
 *  of the PriorityQueue internal heap.
 * 
 *  @tparam T type of the object stored.
 *  @param loc int representing the location to test.
 * 
 *  @return whether the rightChild of the given location is a valid heap index.
 */
template <class T>
inline bool PriorityQueue<T>::rightInBounds(size_t loc) const noexcept
{
  return (rightChild(loc) <= size());
}

/**
 *  @brief Given an index into the heap returns the index of the semantically
 *  lesser child entry.
 *
 *  If one of the two indicies is out of bounds in the heap, then the in bounds
 *  index is returned.
 *
 *  If neither indicies are in bounds, then size() is returned.
 *
 *  @tparam T type of the object stored.
 *  @param pos the heap position to return the minimum child of.
 *
 *  @return the least entry or pos if both l and r are out of bounds.
 */
template <class T>
size_t PriorityQueue<T>::minChild(size_t pos)
{
  bool lInBounds = leftInBounds(pos);
  if(lInBounds && rightInBounds(pos))
  {
    return (heap[leftChild(pos)] < heap[rightChild(pos)]) ?
      leftChild(pos) : rightChild(pos);
  }
  else if(lInBounds)
  {
    return leftChild(pos);
  }
  return pos;
}
