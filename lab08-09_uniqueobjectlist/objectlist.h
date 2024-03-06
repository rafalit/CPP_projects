#pragma once

#include <cinttypes>  // std::size_t
#include <memory>  // std::unique_ptr (dla chętnych)
#include <set>
#include<cstring>

class Object;


class ObjectList
{
    struct Node
    {
        Object* obj;
        Node* next;

        Node(Object* obj) : obj(obj), next(nullptr) {}
    };

public:


    Node* head;

    size_t size_;

    using value_type = Object;

    ObjectList();
    ~ObjectList();

    size_t size();

    bool empty();

    void push_front(Object* obj);

    void pop_front();

    value_type& front();

    void clear();

    void reverse() noexcept;




    struct iterator
    {
        Node* current;

        iterator& operator++() {
            if (current != nullptr) {
                current = current->next;
            }
            return *this;
        }

        iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const iterator& other) const {

            return current == other.current;
        }

        bool operator!=(const iterator& other) const {

            return !(*this == other);
        }

        Object& operator*() const {

            return *(current->obj);
        }

        iterator& operator=(const iterator& other){
            if (this == &other) {
                return *this;
            }
            current = other.current;
            return *this;
        }
        iterator(Node* node) : current(node) {}




    };
    iterator begin() {
        return iterator(head);
    }

    iterator end() {
        return iterator(nullptr);
    }

    void erase(iterator position);

    void erase_after(iterator position);

    ObjectList(const ObjectList& other);

    ObjectList(ObjectList&& other) noexcept;

    ObjectList& operator=(const ObjectList& other);

    ObjectList& operator=(ObjectList&& other) noexcept;



protected:

};
