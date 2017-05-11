#include "user.hpp"
#include <string>
#include <vector>
#include <algorithm>
#include "helper.hpp"
#include "subject.hpp"
#include "topic.hpp"
#include "quiz.hpp"

User::User(const string& name, const string& login, const string& pass,
	 const bool& admin) : name(name), login(login), password(pass), admin(admin){ }

User::~User() { }
	
string User::getName() const{
	return this->name;
}

string User::getPassword() const{
    return this->password;
}

void User::setName(const  string& name) {
    this->name = name;
}

string User :: getLogin() const{
    return this->login;
}

bool User::tryLogin(const string& plogin, const string& ppassword) const{
	return (plogin == this->login) && (ppassword == this->password);
}

bool User::isAdmin() {
	return this->admin;
}

bool User::setPassword(const string& oldpass, const string& newpass){
	if(oldpass == this->password){
		this->password = newpass;
		return true;
	}
	return false;
}

void User::includeSubject(Subject subject) {
    auto it=std::find_if(this->subjects.begin(),this->subjects.end(),[subject](const Subject& comp){return comp.getName()==subject.getName();});
    if(it==this->subjects.end()) this->subjects.push_back(subject);
}

void User::removeSubject(const string &subject) {
    auto it=std::find_if(this->subjects.begin(),this->subjects.end(),[subject](const Subject& comp){return comp.getName()==subject;});
    if(it!=this->subjects.end()) this->subjects.erase(it);
}

std::vector<Subject>& User::getSubjects() {
    return this->subjects;
}

void User::showSubjects() {
    for(Subject &sub:subjects)printf("%s\n", sub.getName().c_str());
}
