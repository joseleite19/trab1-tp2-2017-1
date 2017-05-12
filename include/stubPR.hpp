#ifndef STUBS_H
#define STUBS_H

#include <map>

//como só são usado ponteiros, não é necessario incluir todo o header das classes
class User;
class Subject;

class StubPR {
private:
	std::map<std::string,User*> users;
	std::map<std::string,Subject*> subjects;

	void loadUsers(string s="data/users");
	void saveUsers(string s="data/users");
	void loadSubjects(string s="data/materias");
	void saveSubjects(string s="data/materias");
public:
	StubPR(void);
	~StubPR(void);

	User * retrieveUser(const string &);
	void storeName(User *, const string &);
	void storePass(User *, const string &);
	std::map<std::string,Subject*>& getSubjectsBank();
	void storeSubject(User *, const string &);
	void deleteSubject(User *, const string &);
	bool storeUserData(User *);
    void storeSubjectDB(Subject *);
	std::map<std::string,User*>& getUserBank();
	void deleteUser(User *);
};
#endif
