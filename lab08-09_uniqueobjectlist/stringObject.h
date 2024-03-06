#pragma once

#include "object.h"

class StringObject : public Object
{
public:
    StringObject(const std::string& text);

    bool operator==(const Object& obj) const override;

    Object* clone() const override;

    const std::string& getText() const;

private:
    std::string text_;
};