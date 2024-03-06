#include <iostream>


#include "user.h"
#include "linux.h"


size_t Linux:: open_source_sympathizers_=0;
std::string Linux:: distribution(){
    return distribution_;
}
Linux :: Linux(){
    std::cout<<"+" << distribution_ << '\n';
    open_source_sympathizers_++;}

size_t Linux :: open_source_sympathizers(){
    return open_source_sympathizers_;
}

Linux :: Linux(const std::string& distributi){
    distribution_=distributi;
    std::cout<<"+" << distribution_ << '\n';
    open_source_sympathizers_++;}

Linux :: ~Linux(){
    std::cout<< "~" << distribution_ << '\n';
    open_source_sympathizers_--;}

std::size_t Linux::add_user(const std::string& user_name, const std::string& password){
    User new_user;
    new_user.user_name_= user_name;
    new_user.password_=password;
    users_.push_back(new_user);
    return users_.size()-1;
}
User Linux::user(size_t user_id){
    return users_[user_id];
}
std::string Linux::user_home_directory(size_t user_id){
    return "/home/"+users_[user_id].user_name_+"/";
}
void Linux::set_graphic_environment(std::string dupa){
    graphic_environment_=dupa;
}
std::optional<std::string> Linux::graphic_environment() const{
    return graphic_environment_;
}
