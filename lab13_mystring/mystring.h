#include <iostream>
#include<cstring>
#include <string>
#include <cctype>
#include <set>
#include <string>
#include <map>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <random>
#include <algorithm>
#include <iterator>
#ifndef ZAD14MYSTRING_DLASTUDENTOW_MYSTRING_H
#define ZAD14MYSTRING_DLASTUDENTOW_MYSTRING_H

#endif //ZAD14MYSTRING_DLASTUDENTOW_MYSTRING_H


class MyString{
public:
    typedef char* iterator;
    typedef char* const_iterator;
    size_t size_;
    size_t capacity_;
    char* buffer_;
    constexpr static size_t initialBufferSize_=16;

    size_t size() const{return size_;}
    size_t capacity() const{return capacity_;}
    bool empty()const{return size_==0;}
    MyString()noexcept;
    MyString(const char *text);
    MyString(const MyString &text);
    void clear();
    friend std::ostream& operator<<(std::ostream& os, const MyString &p);
    char& operator[](size_t index);
    const char& operator[](size_t index) const;
    friend std::istream& operator>>(std::istream& is, MyString &p);
    void trim();
    MyString& operator+=(const MyString& other);
    bool operator!=(const MyString& other) const {return !(*this == other);}
    iterator begin(){return buffer_;}
    iterator end(){return buffer_+size_;}
    const_iterator begin() const{return buffer_;}
    const_iterator end() const{return buffer_+size_;}
    MyString& operator+=(char str);
    std::set<MyString> getUniqueWords(const MyString& text);
    bool operator==(const MyString& other) const;
    bool operator<(const MyString& other) const;
    MyString& operator=(const MyString& other);
    std::map<MyString, size_t> countWordsUsageIgnoringCases()const;
    static bool isPunctuation(char c);
    void toLower();
    static std::string generateRandomWord(size_t wordLength);
    bool startsWith(const char* prefix) const;
    bool endsWith(const char* suffix) const;
    static const MyString separator_;
    MyString join(const std::vector<MyString>& strings) const;
    bool all_of(int (*predicate)(int)) const;
};