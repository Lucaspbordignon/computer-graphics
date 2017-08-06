#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>
#include <stdexcept>
#include <iostream>

namespace structures {

template<typename T>
//! Class used in the implementation of a Linked List.
/*!
    This class has methods/functions to handle with a Linked List.
Each element has the pointer to the next one.
*/
class LinkedList {
public:
    
    //! Default constructor.
    /*!
        This constructor initialize the actual size(size_) of the list, 
    that must be 0 to say that the list is empty and the pointer of the
    control node(head).
    */
    LinkedList()
    {
        size_ = 0;
        head = nullptr;
    }

    //! Default destructor.
    /*!
        This destructor deallocate the memory from the Linked List elements,
    but keeps the data in memory.
    */
    ~LinkedList()
    {
        ClearFullList();
    }


    //! Clean the list.
    /*!
        Changes the 'size_' to 0. It means that the list is empty.
    */
    void clear()
    {
        size_ = 0;
        head = nullptr;
    }

    //! Put the given element in the end of the list.
    /*!
        This method receives a data, from any type, and put it
    after the last element on the list.
        \param data the element to put in the end of the list.
    */
    void push_back(const T& data)
    {
        insert(data, size_);
    }

    //! Put the given element in the front of the list.
    /*!
        This method receives a data, from any type, and put it
    on the first index of the list, changing the "next" pointer of head
    to the new element.
        \param data the element to put in the front of the list.
    */
    void push_front(const T& data)
    {
        Node* Aux;
        Aux = new Node(data);
        if(Aux == NULL) throw std::out_of_range("FullListError");
        Aux->next(head);
        head = Aux;
        ++size_;
    }

    //! Put the given element on the given index.
    /*!
        This method receives a data, from any type, and put it
    on the given index.
        \param data the element to insert in the list.
        \param index the index to insert the element.
    */
    void insert(const T& data, std::size_t index)
    {
        if(index > size_ or index < 0) throw std::out_of_range("PositionError");
        if(index == 0) return (push_front(data));
        Node *New, *Old;
        New = new Node(data);
        if(New == NULL) throw std::out_of_range("FullListError");
        Old = head;
        for(int i = 0; i < index-1; ++i) {
            Old = Old->next();
        }
        New->next(Old->next());
        Old->next(New);
        ++size_;
    }

    
    //! Put the given element, in order, on the list.
    /*!
        This method receives a data, from any type, search for an
    value greater than itself, and insert before it.
        \param data the element to insert in the list.
    */
    void insert_sorted(const T& data)
    {
        Node* actual;
        int index;
        if(empty()) return push_front(data);
        actual = head;
        index = 0;
        while(actual->next() != nullptr && data > actual->data()) {
            actual = actual->next();
            ++index;
        }
        if(data > actual->data()) return(insert(data, index+1));
        return(insert(data, index));
    }

    //! Receives an index and returns the element.
    /*!
        Returns the element in the given position.
    */
    T& at(std::size_t index)
    {
        if(index >= size_ or index < 0) throw std::out_of_range("PositionError");
        if(empty()) throw std::out_of_range("EmptyListError");
        Node* Aux = head;
        for(int i = 0; i < index; ++i) {
            Aux = Aux->next();
        }
        return(Aux->data());
    }

    //! Removes the element on the given index.
    /*!
        This method receives and index, remove the element
    located on this position and returns the element.
    */
    T pop(std::size_t index)
    {
        if(empty()) throw std::out_of_range("EmptyListError");
        if(index >= size_ or index < 0) throw std::out_of_range("PositionError");
        if(index == 0) return(pop_front());
        Node *Old, *Out;
        T aux;
        Old = head;
        for(int i = 0; i < index-1; ++i) {
            Old = Old->next();
        }
        Out = Old->next();
        aux = (Out->data());
        Old->next(Out->next());
        --size_;
        delete Out;
        return aux;
    }

    //! Removes the element in the end of the list.
    /*!
        This method takes the last element of the list, remove
    from the array and returns it.
    */
    T pop_back()
    {
        return pop(size_-1);
    }

    //! Removes the element on the start of the list.
    /*!
        This method takes the first element of the list, remove
    and returns it.
    */
    T pop_front()
    {
        if(empty()) throw std::out_of_range("EmptyListError");
        Node* out = head;
        T aux = (out->data());
        head = out->next();
        --size_;
        delete out;
        return aux;
    }

    //! Removes the element recieved by parameter.
    /*!
        This method receives an element, search for it on the
    list, and removes the first time he find.
    */
    void remove(const T& data)
    {
        if(empty()) throw std::out_of_range("EmptyListError");
        pop(find(data));
    }

    //! Test if the linked list is empty.
    /*!
        Returns the result of this test. True or False.
    */
    bool empty() const
    {
        if(size_ == 0) return true;
        return false;
    }

    //! Test if the given element is into the list.
    /*!
        Returns the result of this test. True or False.
    */
    bool contains(const T& data) const
    {
        if(empty()) throw std::out_of_range("EmptyListError");
        if(find(data) == size_) return false;
        return true;
    }

    //! Search for a given element into the list.
    /*!
        Returns the index of this element, if found. Otherwise, returns
    and index out of the list.
    */
    std::size_t find(const T& data) const
    {
        if(empty()) throw std::out_of_range("EmptyListError");
        Node* aux = head;
        for(int i = 0; i < size_; ++i) {
            if(aux->data() == data) return i;
            aux = aux->next();
        }
        return size_;         
    }

    //! Give the used size of the list.
    /*!
        This method returns the number of elements into the linked list.
    */
    std::size_t size() const
    {
        return size_;
    }

    //! Deallocate all the elements of the list.
    /*!
        "Walk" through the list and deallocate each element from memory.
    */
    void ClearFullList()
    {
        Node *Actual, *Old;
        Actual = head;
        while(Actual != nullptr) {
            Old = Actual;
            Actual = Actual->next();
            delete Old;
        }
    }

private:

    class Node {
        public:
            Node(const T& data):
                data_{data}
            {}

            Node(const T& data, Node* next):
                data_{data},
                next_{next}
            {}

            T& data() {
                return data_;
            }

            const T& data() const {
                return data_;
            }

            Node* next() {
                return next_;
            }

            const Node* next() const {
                return next_;
            }

            void next(Node* node) {
                next_ = node;
            }
        private:
            T data_;
            Node* next_{nullptr};
    };
    
    Node* end() { 
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }
    
    Node* head{nullptr};
    std::size_t size_{0u};
};

}

#endif
