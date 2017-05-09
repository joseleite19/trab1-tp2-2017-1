#include "user.hpp"
#include <string>
#include <queue>
#include "helper.hpp"
#include "subject.hpp"
#include "topic.hpp"
#include "quiz.hpp"

User::User(const string& name, const string& login, const string& pass,
	 const bool& admin) : name(name), login(login), password(pass), admin(admin){

    std::queue<Subject> s;
    this->subjects = s;

    }

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
	return plogin == this->login && ppassword == this->password;
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

void User::includeSubject(const string & subject) {
    this->subjects.push(Subject(subject));
}

void User::removeSubject(const string & subject) {
    std::queue<Subject> aux;
    while(!this->subjects.empty()) {
        if(this->subjects.front().getName() != subject) {
            aux.push(this->subjects.front());
        }
        this->subjects.pop();
    }
    this->subjects = aux;
}

std::queue<Subject> User::getSubjects() {
    return this->subjects;
}

void User::showSubjects() {
    std::queue<Subject> aux;
    while(!this->subjects.empty()) {
        printf("%s\n", this->subjects.front().getName().c_str());
        aux.push(this->subjects.front());
        this->subjects.pop();
    }
    this->subjects = aux;
}
