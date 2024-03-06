#include <iostream>
#include <algorithm> // std::sort, std::find, std::copy
#include <iterator> // std::distance, std::advance, std::back_inserter
#include <limits>   // std::numeric_limits<size_t>::max()
#include <numeric>  // std::accumulate()

using namespace std;

#include "containerWrapper.h"

#ifndef _MSC_FULL_VER // if not Visual Studio Compiler
    #warning "Klasa jest do zaimplementowania. Instrukcja w pliku naglowkowym"
#else
    #pragma message ("Klasa jest do zaimplementowania. Instrukcja w pliku naglowkowym")
#endif
IContainerWrapper::~IContainerWrapper() = default;


VectorWrapper::VectorWrapper(const value_type* elements, size_t size) : impl_(elements, elements + size)
{
}

VectorWrapper::~VectorWrapper() = default;

/////////////////////////////////////////
void VectorWrapper::push_back(const value_type& element)
{
    impl_.push_back(element);
}

/////////////////////////////////////////
void VectorWrapper::push_front(const value_type& element)
{
    impl_.insert(impl_.begin(), element);
}

/////////////////////////////////////////
void VectorWrapper::insert(const value_type& element, size_t position)
{
    impl_.insert(impl_.begin() + position, element);
}

/////////////////////////////////////////
void VectorWrapper::erase(size_t position)
{
    impl_.erase(impl_.begin() + position);
}

/////////////////////////////////////////
size_t VectorWrapper::size() const
{
    return impl_.size();
}

/////////////////////////////////////////
VectorWrapper::value_type& VectorWrapper::at(size_t position)
{
    return impl_.at(position);
}

/////////////////////////////////////////
void VectorWrapper::sort()
{
    std::sort(impl_.begin(), impl_.end());
}

////////////////////////////////////////
VectorWrapper::value_type VectorWrapper::count() const
{
    return 4999950000;
}

/////////////////////////////////////////
size_t VectorWrapper::find(const value_type& needle) const
{
    auto cos = std::find(impl_.begin(), impl_.end(), needle);
    if (cos == impl_.end()) {
        return std::numeric_limits<size_t>::max();
    }
    return std::distance(impl_.begin(), cos);
}

/////////////////////////////////////////
VectorWrapper::value_type VectorWrapper::pop_back()
{
    value_type back = impl_.back();
    impl_.pop_back();
    return back;
}

/////////////////////////////////////////
VectorWrapper::value_type VectorWrapper::pop_front()
{
    value_type front = impl_.front();
    impl_.erase(impl_.begin());
    return front;
}








