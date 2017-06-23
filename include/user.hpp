/**
*   Classe das funcoes.
*   Contem funcoes relativas ao usuario como: incluir e remover disciplinas, verificar se eh admin.
*   @author joseleite19
*   @since 07/05/2017
*   @version 3.0
*/


#ifndef USER
#define USER

#include <string>
#include <vector>
#include "subject.hpp"
#include "topic.hpp"
#include "quiz.hpp"
using namespace std;

using uint = unsigned int; /// Po, tem que funfar em Windows tmb ne

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

    /**
    *   Funcao que verifica se login e password estao corretos.
    *   @param duas strings que representam login e senha
    *   @ret retorna um booleano que indica se password e senha estao corretos.
    */
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
