#ifndef SORTED_LISTS_H_
#define SORTED_LISTS_H_

#include <assert.h>

namespace mtm {

    template<class T>
    class SortedList;

    template<class T>
    class Node {
        public:
            Node() = delete;
            ~Node() = default;
            explicit Node(const T val) : data(val), next(nullptr) {}
            Node(const Node<T>* node) : data(node->data), next(node->next) {}
            T data;
            Node<T>* next;
            friend class SortedList<T>;
    };

    template<class T>
    class SortedList {
        public:
            SortedList();
            ~SortedList();
            SortedList(const SortedList<T>& list);
            SortedList<T>& operator=(const SortedList<T>& list);

            void insert(const T& element);
            void remove(typename SortedList<T>::const_iterator iter);
            int length() const;

            template<class Predicate>
            SortedList<T> filter(Predicate predicate_func) const;
            template<class Apply>
            SortedList<T> apply(Apply apply_func) const;

            class const_iterator;
            typename SortedList<T>::const_iterator begin() const;
            typename SortedList<T>::const_iterator end() const;
            
        private:
            Node<T>* head;
            bool checkIfEmpty() const;
    };

    template<class T>
    SortedList<T>::SortedList() : head(nullptr) {}

    template<class T>
    SortedList<T>::~SortedList()
    {
        while (head != nullptr) {
            Node<T> *temp = head;
            head = head->next;
            delete temp;
        }
    }

    template<class T>
    SortedList<T>::SortedList(const SortedList<T>& list) : head(nullptr) 
    {
        Node<T> *temp = list.head;
        while (temp != nullptr) {
            this->insert(temp->data);
            temp = temp->next;
        }

    }

    template<class T>
    SortedList<T>& SortedList<T>::operator=(const SortedList<T>& list)
    {
        SortedList<T> temp(list);
        Node<T> *temp_head = head;
        head = temp.head;
        temp.head = temp_head;
        
        return *this;
    }

    template<class T>
    bool SortedList<T>::checkIfEmpty() const
    {
        if (head == nullptr) {
            return true;
        }
        return false;
    }

    template<class T>
    void SortedList<T>::insert(const T& element)
    {
        Node<T> *node_to_insert = new Node<T>(element);
        
        if (this->checkIfEmpty()) {
            head = node_to_insert;
            return;
        }
        Node<T> *temp = head;
        if (element < temp->data) {
            node_to_insert->next = head;
            head = node_to_insert;
            return;
        }
        while (temp->next != nullptr && temp->next->data < element) {
            temp = temp->next;
        }
        if (temp->next == nullptr) {
            temp->next = node_to_insert;
        }
        else {
            node_to_insert->next = temp->next;
            temp->next = node_to_insert;
        }
    }

    template<class T>
    void SortedList<T>::remove(typename SortedList<T>::const_iterator iter)
    {
         if (this->checkIfEmpty()) {
            return;
        }
        if (head->data == *iter) {
            Node<T> *temp_next = head->next;
            delete head;
            head = temp_next;
            return;
        }
        Node<T> *temp = head;
        while (temp->next != nullptr) {
             if (temp->next->data == *iter) {
                 Node<T> *temp_next = temp->next->next;
                 delete temp->next;
                 temp->next = temp_next;
                 break;
             }
        } 
    }

    template<class T>
    int SortedList<T>::length() const
    {
        int len = 0;
        Node<T> *temp = head;
        while (temp != nullptr) {
            len++;
            temp = temp->next;
        }
        return len;
    }

    template<class T>
    template<class Predicate>
    SortedList<T> SortedList<T>::filter(Predicate predicate_func) const 
    {
        SortedList<T> result;
        Node<T> *temp = head;
        while (temp != nullptr) {
            if (predicate_func(temp->data)) {
                 result.insert(temp->data);
            }
            temp = temp->next;
        }
        return result;
    }

    template<class T>
    template<class Apply>
    SortedList<T> SortedList<T>::apply(Apply apply_func) const 
    {
        SortedList<T> result;
        Node<T> *temp = head;
        while (temp != nullptr) {
            result.insert(apply_func(temp->data));
            temp = temp->next;
        }
        return result;
    }

    template<class T>
    typename SortedList<T>::const_iterator SortedList<T>::begin() const 
    {
        return const_iterator(this, 0);
    }

    template<class T>
    typename SortedList<T>::const_iterator SortedList<T>::end() const 
    { 
        return const_iterator(this, this->length());
    } 

    template<class T>
    class SortedList<T>::const_iterator 
    {    
        private:
            const SortedList<T>* sorted_list;
            int index;
            const_iterator(const SortedList<T> *list, int index);
            friend class SortedList<T>;

        public:
            const T& operator*() const;
            const_iterator& operator++();
            const_iterator operator++(int);
            bool operator==(const const_iterator& iterator) const;
            const_iterator(const const_iterator&) = default;
            const_iterator& operator=(const const_iterator&) = default;
            ~const_iterator() = default;
    };

    template<class T>
    SortedList<T>::const_iterator::const_iterator(const SortedList<T> *list, int index) :
        sorted_list(list),
        index(index)
    {}

    template<class T>
    const T& SortedList<T>::const_iterator::operator*() const
    {   
        assert(index < sorted_list->length());
        Node<T> *temp = sorted_list->head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        return temp->data;
    }

    template<class T>
    typename SortedList<T>::const_iterator& SortedList<T>::const_iterator::operator++()
    {
        ++index;
        return *this;
    }

    template<class T>
    typename SortedList<T>::const_iterator SortedList<T>::const_iterator::operator++(int)
    {
        const_iterator result = *this;
        ++*this;
        return result;
    }

    template<class T>
    bool SortedList<T>::const_iterator::operator==(const const_iterator& iterator) const
    {
        assert(sorted_list == iterator.sorted_list);
        return index == iterator.index;
    }
}


#endif /*SORTED_LISTS_H_*/