#include <memory>
#include <stdexcept>
#include <utility>  // std::exchange()
#include "objectlist.h"
#include "object.h"





ObjectList::ObjectList() : head(nullptr), size_(0){}

ObjectList::~ObjectList(){
    while(head != nullptr){
        Node * next = head->next;
        delete head;
        head = next;
    }
}

size_t  ObjectList::size(){
    return size_;
}
bool ObjectList::empty() {
    return size_ == 0;
}

void ObjectList::push_front(Object* object) {
    for (Node* currentNode = head; currentNode != nullptr; currentNode = currentNode->next) {
        if (*currentNode->obj == *object) {
            return;
        }
    }

    Node* newNode = new Node(object);
    newNode->next = head;
    head = newNode;
    ++size_;
}

void ObjectList::pop_front(){
    if(head == nullptr){
        return;
    }
    Node* next = head->next;
    delete head->obj;
    delete head;
    head = next;

    size_--;
}

ObjectList::value_type& ObjectList::front(){

    return *(head->obj);
}

void ObjectList::clear() {
    while (head != nullptr) {
        pop_front();
    }
}

void ObjectList::reverse() noexcept{
    if(head == nullptr || head->next == nullptr){
        return;
    }
    Node* previous = nullptr;
    Node* current= head;
    Node* next = nullptr;

    while(current != nullptr){
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    head = previous;
}

void ObjectList::erase_after(iterator position) {
    if(position.current == nullptr || position.current->next == nullptr){
        return;
    }

    Node* toErase = position.current->next;
    position.current->next = position.current->next->next;
    size_--;
    delete toErase->obj;
    delete toErase;
}

void ObjectList::erase(iterator position){
    if (position == end() || position.current == nullptr) {
        return;
    }

    if (position.current == head) {
        pop_front();
    } else {
        Node* previousNode = head;
        while (previousNode != nullptr && previousNode->next != position.current) {
            previousNode = previousNode->next;
        }
        if (previousNode != nullptr) {
            previousNode->next = position.current->next;
            delete position.current->obj;
            delete position.current;
            --size_;
        }
    }
}

ObjectList::ObjectList(const ObjectList& other) : head(nullptr), size_(0)
{
    Node* current = other.head;


    while (current != nullptr) {
        Node* newNode = new Node(current->obj->clone());
        newNode->next = head;
        head = newNode;
        ++size_;

        current = current->next;
    }


    reverse();
}

ObjectList::ObjectList(ObjectList&& other) noexcept : head(nullptr), size_(0)
{
    head = other.head;
    size_ = other.size_;


    other.head = nullptr;
    other.size_ = 0;
}

ObjectList& ObjectList::operator=(const ObjectList& other)
{
    if (this == &other)
        return *this;

    clear();

    for (Node* current = other.head; current != nullptr; current = current->next)
    {
        push_front(current->obj->clone());
    }

    reverse();

    return *this;
}

ObjectList& ObjectList::operator=(ObjectList&& other) noexcept
{
    if (this == &other)
        return *this;

    clear();

    head = other.head;
    size_ = other.size_;

    other.head = nullptr;
    other.size_ = 0;

    return *this;
}