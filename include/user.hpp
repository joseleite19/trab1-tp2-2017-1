#ifndef USER
#define USER

#include <string>
#include <queue>
#include "subject.hpp"
#include "topic.hpp"
#include "quiz.hpp"
using namespace std;

class User{
private:
	string name, login, password;
	bool admin;
    std::queue<Subject> subjects;
public:
	User(const string&, const string&, const string&, const bool&);
	~User();

	string getName() const;
    string getPassword() const;
    string getLogin() const;
	bool tryLogin(const string&, const string&) const;
	bool isAdmin(void);
	bool setPassword(const string&, const string&);
    void setName(const string&);
    void showSubjects();
    std::queue<Subject> getSubjects();
    void includeSubject(const string &);
    void removeSubject(const string &);
};

#endif
