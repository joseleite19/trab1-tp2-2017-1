#include "user.hpp"

User::User(const string& name, const string& login, const string& pass,
	 const bool& admin) : name(name), login(login), password(pass), admin(admin){}

User::~User(){
	
}

string User::getname() const{
	return name;
}

bool User::try_login(const string& plogin, const string& ppassword) const{
	return plogin == login && ppassword == password;
}

inline bool User::is_admin() const{
	return admin;
}

bool User::change_password(const string& oldpass, const string& newpass){
	if(oldpass == password){
		password = newpass;
		return true;
	}
	return false;
}
