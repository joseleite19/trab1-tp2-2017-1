#ifndef USER
#define USER

#include <string>
using namespace std;

class User{
	string name, login, password;
	bool admin;
public:
	User(const string&, const string&, const string&, const bool&);
	~User();

	string getname() const;
	bool try_login(const string&, const string&) const;
	inline bool is_admin() const;
	bool change_password(const string&, const string&);
};

#endif