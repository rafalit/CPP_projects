#include <iostream>


#include "user.h"
#include "windows.h"
#include<string>
using namespace std;

std::size_t Windows :: activated_systems_=0;

std::string Windows :: version(){
    return version_;
}

Windows :: Windows(){
    std:: cout<<"Windows " << version_ << "\n";
    activated_systems_++;

}

Windows :: Windows(const std::string& vers){
    version_=vers;
    std:: cout<<"Windows " << version_ << "\n";
    activated_systems_++;
}
std::size_t Windows::activated_systems(){
    return activated_systems_;
}

std::size_t Windows::add_user(const std::string& user_name, const std::string& password){
    User new_user;
    new_user.user_name_=user_name;
    new_user.password_=password;
    users_.push_back(new_user);
    return users_.size()-1;
}
User Windows::user(size_t user_id){
    return users_[user_id];
}
std::string Windows::user_home_directory(size_t user_id){
    return "C:\\Users\\"+users_[user_id].user_name_+"";
}