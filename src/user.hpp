#ifndef USER
#define USER

#include <string>
using namespace std;

class User{
private:
	string name, login, password;
	bool admin;
public:
	User(const string&, const string&, const string&, const bool&);
	~User();

	string get_name() const;
    string get_login() const;
	bool try_login(const string&, const string&) const;
	bool is_admin(void);
	bool change_password(const string&, const string&);
};

#endif
