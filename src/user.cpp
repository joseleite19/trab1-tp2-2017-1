#include "user.hpp"

User::User(const string& name, const string& login, const string& pass,
	 const bool& admin) : name(name), login(login), password(pass), admin(admin){}

User::~User() { }
	
string User::get_name() const{
	return this->name;
}

string User :: get_login() const{
    return this->login;
}

bool User::try_login(const string& plogin, const string& ppassword) const{
	return plogin == this->login && ppassword == this->password;
}

bool User::is_admin() {
	return this->admin;
}

bool User::change_password(const string& oldpass, const string& newpass){
	if(oldpass == this->password){
		this->password = newpass;
		return true;
	}
	return false;
}
