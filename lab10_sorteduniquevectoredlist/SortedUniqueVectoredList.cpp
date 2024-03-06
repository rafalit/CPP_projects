#include <stdexcept> // std::out_of_range
#include <utility>   // std::exchange
#include <array>
#include <limits>
#include <algorithm>
#include <string>
#include "SortedUniqueVectoredList.h"
using namespace std;


/** class SortedUniqueVectoredList::Bucket
 * @param size ilosc elementow w kubelku, tworzac pusty ma byc 0
 * @param values elementy kubelka, jako tablica statyczna
 * @param BUCKET_SIZE ilosc elementow w statycznej tablicy
 * @param bucketCount_ ilosc kubelkow
 * @param next wskaznik na nastepny @ref Bucket, a jesli takiego nie ma na nullptr
 * @param previous wskaznik na poprzedni @ref Bucket, a jesli takiego nie ma na nullptr
 * @note jest to klasa zrobiona przy pomocy [idiomu PIMPL](https://en.cppreference.com/w/cpp/language/pimpl),
 *       ktory polega na tym, ze w klasie zewnetrznej jest jedynie deklaracja klasy wewnetrznej, ktora jest zaimplementowana w pliku zrodlowym **/
struct SortedUniqueVectoredList::Bucket
{
    constexpr static size_t BUCKET_SIZE = 10;

    std::array<std::string, BUCKET_SIZE> values;
    size_t size{};

    Bucket* next = nullptr;
    Bucket* previous = nullptr;
};


SortedUniqueVectoredList::SortedUniqueVectoredList(const SortedUniqueVectoredList &source)
{
    copy(source);
}

SortedUniqueVectoredList::SortedUniqueVectoredList(SortedUniqueVectoredList &&another)
{
    this->move(std::move(another));
}

SortedUniqueVectoredList::~SortedUniqueVectoredList()
{
    free();
}

SortedUniqueVectoredList &SortedUniqueVectoredList::operator=(SortedUniqueVectoredList &&another)
{
    if (this != &another) {

        free();

        head = another.head;
        tail = another.tail;
        bucketCount_ = another.bucketCount_;
        size_ = another.size_;
        capacity_ = another.capacity_;


        another.head = nullptr;
        another.tail = nullptr;
        another.bucketCount_ = 0;
        another.size_ = 0;
        another.capacity_ = 0;
    }
    return *this;

}

void SortedUniqueVectoredList::insert(const string &value)
{
    if (contains(value)) {
        return;
    }

    if (tail == nullptr || tail->size >= Bucket::BUCKET_SIZE) {
        allocate_new_bucket();
    }
    size_t insertIndex = 0;
    while (insertIndex < tail->size && tail->values[insertIndex] < value) {
        ++insertIndex;
    }
    for (size_t i = tail->size; i > insertIndex; --i) {
        tail->values[i] = tail->values[i - 1];
    }

    tail->values[insertIndex] = value;
    tail->size++;
    size_++;
}

void SortedUniqueVectoredList::erase(const string &value)
{
    Bucket *current = head;
    while(current != nullptr){
        for(std::string &element: current->values){
            if(element == value){
                element.clear();
                --current->size;
                --size_;
                return;
            }
        }
        current = current->next;
    }

}

SortedUniqueVectoredList::operator std::string() const
{
    std::string result;
    Bucket* current = head;

    while (current != nullptr) {
        for (size_t i = 0; i < current->size; i++) {
            if (i < current->values.size()) {
                result += current->values[i];
            }
        }
        current = current->next;
    }

    return result;
}

void SortedUniqueVectoredList::allocate_new_bucket()
{
    Bucket* newBucket = new Bucket;
    newBucket -> next =nullptr;
    newBucket -> previous= tail;

    if(tail != nullptr){
        tail->next = newBucket;
    }
    tail = newBucket;

    if(head == nullptr){
        head = tail;
    }

    capacity_ += Bucket::BUCKET_SIZE;
    bucketCount_++;
}

void SortedUniqueVectoredList::free()
{
    head = nullptr;
    tail = nullptr;
    bucketCount_ = 0;
    size_ = 0;
    capacity_ = 0;
}

void SortedUniqueVectoredList::move(SortedUniqueVectoredList &&another)
{
    if( this == &another){
        return;
    }

    free();

    head = another.head;
    tail = another.tail;
    bucketCount_ = another.bucketCount_;
    size_ = another.size_;
    capacity_ = another.capacity_;

    another.head = nullptr;
    another.tail = nullptr;
    another.bucketCount_ = 0;
    another.size_ = 0;
    another.capacity_ = 0;

}

void SortedUniqueVectoredList::copy(const SortedUniqueVectoredList &other)
{
    if( this == &other){
        return;
    }

    free();

    bucketCount_ = other.bucketCount_;
    size_ = other.size_;
    capacity_ = other.capacity_;

    head= nullptr;
    tail = nullptr;

    Bucket * current = other.head;

    while(current!=nullptr){
        Bucket *newBucket = new Bucket(*current);
        if(head == nullptr){
            head= newBucket;
            tail = newBucket;
        }
        else{
            tail->next = newBucket;
            tail = newBucket;
        }
        current = current->next;
    }


}

bool SortedUniqueVectoredList::contains(const string& value) const
{
    Bucket* current = head;
    while (current != nullptr) {
        for (const std::string& element : current->values) {
            if (element == value) {
                return true;
            }
        }
        current = current->next;
    }
    return false;
}

SortedUniqueVectoredList SortedUniqueVectoredList::operator-(const SortedUniqueVectoredList &another) const
{
    SortedUniqueVectoredList ret;

    Bucket* current = head;

    while (current != nullptr) {
        for (size_t i = 0; i < current->size; i++) {
            if (!another.contains(current->values[i])) {
                ret.insert(current->values[i]);
            }
        }
        current = current->next;
    }

    return ret;
}
SortedUniqueVectoredList& SortedUniqueVectoredList::operator*=(const size_t howManyTimesMultiply)
{
    SortedUniqueVectoredList result;
    const size_t originalSize = size();

    for (size_t i = 0; i < howManyTimesMultiply; ++i)
    {
        for (size_t j = 0; j < originalSize; ++j)
        {
            result.insert(operator[](j));
        }
    }

    *this = std::move(result);
    return *this;
}

string& SortedUniqueVectoredList::operator[](size_t index)
{
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }

    Bucket* current = head;
    size_t currentIndex = 0;

    while (current != nullptr) {
        if (index < currentIndex + current->size) {
            return current->values[index - currentIndex];
        }
        currentIndex += current->size;
        current = current->next;
    }

    throw std::out_of_range("Index out of range");
}

const string& SortedUniqueVectoredList::operator[](size_t index) const
{
    static const string defaultValue = "";

    if (index >= size_) {
        return defaultValue;
    }

    Bucket* current = head;

    while (current != nullptr) {
        if (index < current->size) {
            return current->values[index];
        }
        index -= current->size;
        current = current->next;
    }

    return defaultValue;
}

SortedUniqueVectoredList &SortedUniqueVectoredList::operator=(const SortedUniqueVectoredList &another)
{
    if (this != &another) {

        SortedUniqueVectoredList temp(another);

        std::swap(head, temp.head);
        std::swap(tail, temp.tail);
        std::swap(bucketCount_, temp.bucketCount_);
        std::swap(size_, temp.size_);
        std::swap(capacity_, temp.capacity_);
    }
    return *this;
}

void SortedUniqueVectoredList::sort_buckets()
{
    Bucket* current = head;
    while (current != nullptr) {
        std::sort(current->values.begin(), current->values.begin() + current->size);
        current = current->next;
    }
}