#ifndef LIST_H
#define LIST_H
/* List.h
 *
 * doubly-linked, double-ended list with Iterator interface
 * Project UID c1f28c309e55405daf00c565d57ff9ad
 * EECS 280 Project 4
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL
using namespace std;


template <typename T>
class List {
public:
    List () {
        size_of_list = 0;
        first = nullptr;
        last = nullptr;
    }
    
    List (const List &other) : List() {
        copy_all(other);
    }
    
    ~List () {
        clear();
    }
    
    List &operator=(const List &rhs) {
        if (this != &rhs) {
            clear();
            copy_all(rhs);
        }
        return *this;
    }
    
  //EFFECTS:  returns true if the list is empty
    bool empty() const {
        return (size_of_list == 0);
    }

  //EFFECTS: returns the number of elements in this List
    int size() const {
        return size_of_list;
    }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
    T & front() {
        assert(!empty());
        return first->datum;
    }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
    T & back() {
        assert(!empty());
        return last->datum;
    }

  //EFFECTS:  inserts datum into the front of the list
    void push_front(const T &datum) {
        Node* new_datum = new Node;
        new_datum->datum = datum;
        new_datum->prev = nullptr;
        if (empty()) {
            first = last = new_datum;
        }
        else {
            new_datum->next = first;
            first = first->prev = new_datum;
        }
        size_of_list++;
    }

  //EFFECTS:  inserts datum into the back of the list
    void push_back(const T &datum) {
        Node* new_datum = new Node;
        new_datum->datum = datum;
        new_datum->next = nullptr;
        if (empty()) {
            new_datum->prev = nullptr;
            first = last = new_datum;
        }
        else {
            new_datum->prev = last;
            last = last->next = new_datum;
        }
        size_of_list++;
    }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
    void pop_front() {
        assert(!empty());
        Node *remove = first;
        first = first->next;
        delete remove;
        size_of_list--;
        if (!empty()) {first->prev = nullptr;}
        if (size_of_list == 0) {first = last = nullptr;}
    }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
    void pop_back() {
        assert(!empty());
        Node *remove = last;
        Node *new_last = last->prev;
        last = new_last;
        delete remove;
        size_of_list--;
        if (!empty()) {last->next = nullptr;}
        if (size_of_list == 0) {first = last = nullptr;}
    }

  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all items from the list
    void clear() {
        int initial_size = size_of_list;
        for (int i = 0; i < initial_size; ++i) {
            pop_front();
        }
    }

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you can omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists

private:
  //a private type
    
    int size_of_list;
    
  struct Node {
      Node *next;
      Node *prev;
      T datum;
      
      Node (Node *next_in, Node *prev_in, T datum_in) {
          next = next_in;
          prev = prev_in;
          datum = datum_in;
      }
      Node() {
          next = nullptr;
          prev = nullptr;
      }
  };
    
  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
    void copy_all(const List<T> &other) {
        for (Node *node_ptr = other.first; node_ptr; node_ptr = node_ptr->next) {
            push_back(node_ptr->datum);
        }
    }

  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty

public:
  ////////////////////////////////////////
  class Iterator {
    //OVERVIEW: Iterator interface to List

    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators: *,
    // ++ (prefix), default constructor, == and !=.

  public:
    // This operator will be used to test your code. Do not modify it.
    // Requires that the current element is dereferenceable.
      Iterator& operator--() {
          assert(node_ptr);
          node_ptr = node_ptr->prev;
          return *this;
      }
      
      Iterator() : node_ptr(nullptr) {}
      
      T& operator* () const {
          assert(node_ptr != nullptr);
          return node_ptr->datum;
      }
      
      Iterator& operator++() {
          assert(node_ptr != nullptr);
          node_ptr = node_ptr->next;
          return *this;
      }
      
      bool operator!= (Iterator rhs) const {
          return node_ptr != rhs.node_ptr;
      }
      
      bool operator== (Iterator rhs) const {
          return node_ptr == rhs.node_ptr;
      }

  private:
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here

    // add any friend declarations here
      friend class List;

    // construct an Iterator at a specific position
      Iterator(Node* p) {
          node_ptr = p;
      }

  };//List::Iterator
  ////////////////////////////////////////

    List (int size_in, Node* first_in, Node* last_in) {
       size_of_list = size_in;
       first = first_in;
       last = last_in;
     }
    
  // return an Iterator pointing to the first element
    Iterator begin() {
        return Iterator(first);
    }

  // return an Iterator pointing to "past the end"
    Iterator end() const {
        return Iterator();
    }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
    void erase(Iterator i) {
        if (i.node_ptr == first) {pop_front();}
        else if (i.node_ptr == last) {pop_back();}
        else {
            Node *victim = i.node_ptr;
            Node *previous_node = victim->prev;
            Node *next_node = victim->next;
            previous_node->next = next_node;
            next_node->prev = previous_node;
            size_of_list--;
            delete victim;
        }
    }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
    void insert(Iterator i, const T &datum) {
        if (i.node_ptr == first) {push_front(datum);}
        else {
            Node *insert_node = new Node;
            Node *new_prev = i.node_ptr->prev;
            Node *new_next = i.node_ptr;
            insert_node->datum = datum;
            insert_node->prev = new_prev;
            insert_node->next = new_next;
            new_next->prev = insert_node;
            new_prev->next = insert_node;
            size_of_list++;
        }
    }

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.


#endif // Do not remove this. Write all your code above this line.
