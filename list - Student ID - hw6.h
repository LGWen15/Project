// list standard header

#ifndef LIST
#define LIST

template< typename ValueType >
struct ListNode // list node
{
    ListNode* next;  // successor node, or first element if head
    ListNode* prev;  // predecessor node, or last element if head
    ValueType myVal; // the stored value, unused if head
};


// CLASS TEMPLATE ListVal
template< typename Ty  >
class ListVal
{
public:
    using node = ListNode< Ty >;
    using nodePtr = node*;

    using value_type = Ty;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;

    ListVal() // initialize data
        : myHead(),
        mySize(0)
    {
    }

    nodePtr myHead; // pointer to head node
    size_type mySize; // number of elements
};


// CLASS TEMPLATE list
template< typename Ty >
class list // bidirectional linked list
{
    using node = ListNode< Ty >;
    using nodePtr = node*;
    using ScaryVal = ListVal< Ty >;

public:
    using value_type = Ty;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;

    using iterator = node*;
    using const_iterator = const node*;

    // empty container constructor (default constructor)
    // Constructs an empty container, with no elements.
    list()
        : myData()
    {
        myData.myHead = new node;
        myData.myHead->myVal = Ty();
        myData.myHead->prev = myData.myHead->next = myData.myHead;
    }

    // fill constructor
    // Constructs a container with "count" elements.
    // Each element is initialized as 0.
    list(size_type count) // construct list from count * Ty()
        : myData()
    {
        myData.myHead = new node;
        myData.myHead->myVal = Ty();
        myData.myHead->prev = myData.myHead->next = myData.myHead;

        if (count > 0)
            for (size_type i = 0; i < count; ++i)
                insert(end(), Ty());
    }

    // copy constructor
    // Constructs a container with a copy of each of the elements in "right",
    // in the same order.
    list(const list& right)
        : myData()
    {
        myData.myHead = new node;
        myData.myHead->myVal = Ty();
        myData.myHead->prev = myData.myHead->next = myData.myHead;

        iterator temp = right.myData.myHead->next;

        while (temp != right.end()) {
            insert(end(), temp->myVal);
            temp = temp->next;
        }


    }

    // List destructor
    // Destroys the container object.
    // Deallocates all the storage capacity allocated by the list container.
    ~list()
    {
        clear();
        delete myData.myHead;
    }

    // Assigns new contents to the container, replacing its current contents,
    // and modifying its size accordingly.
    // Copies all the elements from "right" into the container
    // (with "right" preserving its contents).
    list& operator=(const list& right)
    {
        if (this != &right) {
            iterator now = myData.myHead->next;
            iterator temp = right.myData.myHead->next;

            while (now != end() && temp != right.end()) {
                now->myVal = temp->myVal;
                now = now->next;
                temp = temp->next;
            }

            if (size() < right.size()) {
                while (temp != right.end()) {
                    insert(now, temp->myVal);
                    temp = temp->next;
                }
            }
            else if (size() > right.size()) {
                while (now != end()) {
                    now = erase(now);
                }
            }
        }



        return *this;
    }

    // Returns an iterator pointing to the first element in the list container.
    // If the container is empty, the returned iterator value shall not be dereferenced.
    iterator begin()
    {
        return iterator(myData.myHead->next);
    }

    // Returns an iterator pointing to the first element in the list container.
    // If the container is empty, the returned iterator value shall not be dereferenced.
    const_iterator begin() const
    {
        return const_iterator(myData.myHead->next);
    }

    // Returns an iterator referring to the past-the-end element in the list container.
    // The past-the-end element is the theoretical element
    // that would follow the last element in the list container.
    // It does not point to any element, and thus shall not be dereferenced.
    // If the container is empty, this function returns the same as list::begin.
    iterator end()
    {
        return iterator(myData.myHead);
    }

    // Returns an iterator referring to the past-the-end element in the list container.
    // The past-the-end element is the theoretical element
    // that would follow the last element in the list container.
    // It does not point to any element, and thus shall not be dereferenced.
    // If the container is empty, this function returns the same as list::begin.
    const_iterator end() const
    {
        return const_iterator(myData.myHead);
    }

    // Returns the number of elements in the list container.
    size_type size() const
    {
        return myData.mySize;
    }

    // Returns whether the list container is empty (i.e. whether its size is 0).
    bool empty() const
    {
        return myData.mySize == 0;
    }

    // Returns a reference to the first element in the list container.
    // Calling this function on an empty container causes undefined behavior.
    reference front()
    {
        return myData.myHead->next->myVal;
    }

    // Returns a reference to the first element in the list container.
    // Calling this function on an empty container causes undefined behavior.
    const_reference front() const
    {
        return myData.myHead->next->myVal;
    }

    // Returns a reference to the last element in the list container.
    // Calling this function on an empty container causes undefined behavior.
    reference back()
    {
        return myData.myHead->prev->myVal;
    }

    // Returns a reference to the last element in the list container.
    // Calling this function on an empty container causes undefined behavior.
    const_reference back() const
    {
        return myData.myHead->prev->myVal;
    }

    // The container is extended by inserting a new element
    // before the element at the specified position.
    // This effectively increases the list size by the amount of elements inserted.
    // Returns an iterator that points to the newly inserted element.
    iterator insert(const_iterator where, const Ty& val) // insert val at where
    {
        nodePtr newNode = new node;
        newNode->myVal = val;

        iterator pos = myData.myHead->next;


        while (pos != where)
            pos = pos->next;


        newNode->next = pos;
        newNode->prev = pos->prev;
        pos->prev->next = newNode;
        pos->prev = newNode;

        ++myData.mySize;

        return iterator(newNode);
    }

    // Removes from the list container the element at the specified position.
    // This effectively reduces the container size one, which is destroyed.
    // Returns an iterator pointing to the element that followed the element erased.
    // This is the container end if the operation erased the last element in the sequence.
    iterator erase(const_iterator where)
    {
        if (myData.mySize == 0)
            return myData.myHead;

        iterator pos = myData.myHead->next;

        while (pos != where)
            pos = pos->next;

        if (pos == myData.myHead)
            pos = pos->prev;

        pos->next->prev = pos->prev;
        pos->prev->next = pos->next;
        pos = pos->next;

        --myData.mySize;

        return pos;
    }

    // Removes all elements from the list container (which are destroyed),
    // and leaving the container with a size of 0.
    void clear() // erase all
    {
        if (myData.mySize != 0) // the list is not empty
        {
            while (myData.mySize > 0)
                erase(end());
        }
    }

private:
    ScaryVal myData;
};

// determine if two lists are equal and return true, otherwise return false
template< typename Ty >
bool operator==(const list< Ty >& left, const list< Ty >& right)
{
    typename Ty::iterator it1 = left.myData.myHead->next;
    typename Ty::iterator it2 = right.myData.myHead->next;

    if (left.size() != right.size())
        return false;

    while (it1 != left.myData.myHead && it2 != right.myData.myHead) {
        if (it1->myVal != it2->myVal)
            return false;
        it1 = it1->next;
        it2 = it2->next;
    }
    return true;


}

template< typename Ty >
bool operator!=(const list< Ty >& left, const list< Ty >& right)
{
    return !(left == right);
}

#endif // LIST