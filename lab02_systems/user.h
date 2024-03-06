#ifndef USER_H
#define USER_H

#include <string>

struct User
{
    std::string user_name_;
    std::string password_;
    bool admin_ = false;
};

static bool operator==(const User& lhs, const User& rhs)
{
    return lhs.user_name_ == rhs.user_name_ &&
           lhs.password_ == rhs.password_ &&
           lhs.admin_ == rhs.admin_;
}

#endif // USER_H
