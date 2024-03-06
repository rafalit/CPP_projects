#include <functional>
#include <algorithm>
#include <string>
#include <cstring>
#include <stdexcept>
#include <utility> // std::exchange
#include "PtrCStringVector.h"
using namespace std;


PtrCStringVector::PtrCStringVector()
{
    size_ = 0;
    capacity_ = 0;
    data_ = nullptr;

}

PtrCStringVector::PtrCStringVector(const PtrCStringVector &srcPtrCStringVector): PtrCStringVector()
{
    size_ = srcPtrCStringVector.size_;
    capacity_ = srcPtrCStringVector.capacity_;
    data_ = new char*[capacity_];

    for(int i=0; i<size_; i++){
        size_t stringLength = strlen(srcPtrCStringVector.data_[i]);
        data_[i] = new char[stringLength + 1];
        strcpy(data_[i], srcPtrCStringVector.data_[i]);

    }

}

PtrCStringVector::~PtrCStringVector()
{
    for(int i=0; i<size_; ++i){
        delete[] data_[i];
    }
    delete[] data_;

    size_ = 0;
    capacity_ = 0;
    data_ = nullptr;
}

PtrCStringVector& PtrCStringVector::operator=(const PtrCStringVector& source)
{
    if (this != &source)
    {
        for (int i = 0; i < size_; ++i)
        {
            delete[] data_[i];
        }
        delete[] data_;

        size_ = source.size_;
        capacity_ = source.capacity_;

        data_ = new char*[capacity_];

        for (int i = 0; i < size_; ++i)
        {
            size_t textLength = strlen(source.data_[i]);
            data_[i] = new char[textLength + 1];
            strcpy(data_[i], source.data_[i]);
        }
    }

    return *this;
}

PtrCStringVector& PtrCStringVector::operator=(PtrCStringVector&& source)
{
    if (this != &source)
    {
        free();

        size_ = source.size_;
        capacity_ = source.capacity_;
        data_ = source.data_;

        source.size_ = 0;
        source.capacity_ = 0;
        source.data_ = nullptr;
    }

    return *this;
}

void PtrCStringVector::push_back(const char *text2Add)
{
    size_t textLength = strlen(text2Add);
    if(size_ == capacity_){
        size_t newCapacity = (capacity_ == 0) ? 1: capacity_ * 2;
        char **newData = new char*[newCapacity];
        for(size_t i=0; i<size_; i++){
            newData[i] = data_[i];
        }
        delete[] data_;

        data_ = newData;
        capacity_ = newCapacity;
    }
    char* newString = new char[textLength+1];
    strcpy(newString,text2Add);

    data_[size_] = newString;
    ++size_;
}

PtrCStringVector PtrCStringVector::operator+(const PtrCStringVector &anotherVector) const
{
    PtrCStringVector result;

    for(int i=0; i<size_; i++){
        result.push_back(data_[i]);
    }
    for(int i=0; i<anotherVector.size_; i++){
        result.push_back(anotherVector.data_[i]);
    }
    return result;
}

char *PtrCStringVector::operator[](size_t index)
{
    if(index >= size_){
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

const char *PtrCStringVector::operator[](size_t index) const
{
    if(index >= size_){
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

PtrCStringVector PtrCStringVector::operator&(const PtrCStringVector &rhs) const
{
    PtrCStringVector result;

    std::size_t minLength = std::min(size_, rhs.size_);
    std::size_t maxLength = std::max(size_, rhs.size_);

    for (std::size_t i = 0; i < minLength; ++i) {
        const char* text1 = data_[i];
        const char* text2 = rhs.data_[i];
        std::string concatenatedText = std::string(text1) + std::string(text2);
        result.push_back(concatenatedText.c_str());
    }

    const PtrCStringVector& longerVector = (size_ >= rhs.size_) ? *this : rhs;
    for (std::size_t i = minLength; i < maxLength; ++i) {
        const char* text = longerVector.data_[i];
        result.push_back(text);
    }

    return result;

}

void PtrCStringVector::free()
{
    for(int i=0; i<size_; i++){
        delete[] data_[i];
    }
    delete[] data_;

    data_=nullptr;
    capacity_ =0;
    size_ = 0;

}

void PtrCStringVector::reserve(size_t new_capacity)
{
    if(new_capacity <= capacity_){
        return;
    }

    char** new_data = new char*[new_capacity];

    for(int i=0; i<size_; i++){
        new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;

}
