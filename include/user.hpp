#ifndef USER
#define USER

#include <string>
#include <vector>
#include "subject.hpp"
#include "topic.hpp"
#include "quiz.hpp"
using namespace std;

class User{
private:
	string name, login, password;
	bool admin;
    std::vector<Subject> subjects;
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
    std::vector<Subject>& getSubjects();
    void includeSubject(Subject);
    void removeSubject(const string &);
};

#endif
