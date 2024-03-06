#include "stringObject.h"

StringObject::StringObject(const std::string& text) : text_(text) {}

bool StringObject::operator==(const Object& obj) const
{
    const StringObject* other = dynamic_cast<const StringObject*>(&obj);
    if (other) {
        return text_ == other->text_;
    }
    return false;
}

Object* StringObject::clone() const
{
    return new StringObject(*this);
}

const std::string& StringObject::getText() const
{
    return text_;
}