#include <iostream>
#include <algorithm>
#include <cstring>
#include <cctype>
#include<string>
#include <utility> // std::exchange
using namespace std;

#include "simpleString.h"


int SimpleString::instances_=0;

unsigned int SimpleString::size() const{
    return size_;
}

unsigned int SimpleString::capacity() const{
    return capacity_;
}

const char* SimpleString:: data()const{
    return data_;
}

const char* SimpleString:: c_str() const{
    return data_;
}
////////////////////1///////
SimpleString::SimpleString(): size_(0), capacity_(0), data_(new char[0]){
    instances_++;
    data_[0] = '\0';
}

//////////////////2///////
SimpleString::SimpleString(const char* text) : size_(strlen(text)), data_(nullptr){
    ++instances_;
    char* new_data = new char[size_ + 1];
    memcpy(new_data, text, size_ + 1);
    std::exchange(data_, new_data);
    std::exchange(capacity_, size_);
}

//////////////////3//////////
SimpleString::SimpleString(const SimpleString& text): SimpleString (text.data_){

}
///////////////////4/////////
SimpleString:: ~SimpleString(){
    --instances_;
    delete[] data_;
}
/////////////////5////////////
int SimpleString::instances(){

    return instances_;
}
////////////////6//////////
void SimpleString::assign(const char* new_text) {
    size_t new_size = strlen(new_text);

    if (new_size > capacity_) {
        delete[] data_;
        data_ = new char[new_size + 1];
        capacity_ = new_size;
    }

    std::copy(new_text, new_text + new_size + 1, data_);

    size_ = new_size;
}
///////////////7///////////

bool SimpleString::equal_to(const SimpleString& text, bool case_sensitive)const{
    if(size_ != text.size_){
        return false;
    }
    int (*cmp_func)(int);

    if (case_sensitive) {
        cmp_func = [](int c) { return c; };
    } else {
        cmp_func = [](int c) { return tolower(c); };
    }

    for (size_t i = 0; i < size_; i++) {
        if (cmp_func(data_[i]) != cmp_func(text.data_[i])) {
            return false;
        }
    }

    return true;
}
///////8////////////
void SimpleString::append(const SimpleString& text){
    size_t new_size = size_ + text.size_;
    char* new_data = new char[new_size + 1];

    memcpy(new_data, data_, size_);
    memcpy(new_data + size_, text.data_, text.size_);
    new_data[new_size] = '\0';

    delete[] data_;

    data_ = new_data;
    size_ = new_size;
}


////////////////////9///////////////
SimpleString SimpleString::substr(size_t pos, size_t count) const {
    size_t copy_count = std::min(count, size_ - pos);
    char* new_data = new char[copy_count + 1];

    memcpy(new_data, data_ + pos, copy_count);
    new_data[copy_count] = '\0';

    SimpleString new_string(new_data);
    delete[] new_data;

    return new_string;
}

///////////////10//////////
int SimpleString::compare(const SimpleString& text, bool case_sensitive) const {
    int result = 0;
    size_t min_size = std::min(size_, text.size_);

    for (size_t i = 0; i < min_size; ++i) {
        char c1 = case_sensitive ? data_[i] : tolower(data_[i]);
        char c2 = case_sensitive ? text.data_[i] : tolower(text.data_[i]);
        if (c1 != c2) {
            result = (c1 < c2) ? -1 : 1;
            break;
        }
    }

    if (result == 0) {
        if (size_ < text.size_) {
            result = -1;
        } else if (size_ > text.size_) {
            result = 1;
        }
    }

    return result;
}
////////////////11////////

SimpleString::SimpleString(SimpleString&& obj):size_(0), capacity_(0) ,data_(){
    size_=obj.size_;
    capacity_=obj.capacity_;
    data_=obj.data_;
    obj.size_=0;
    obj.capacity_=0;
    obj.data_=new char[1]{'\0'};
}