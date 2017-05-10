#ifndef INTERFACES_H
#define INTERFACES_H

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

#include <queue>
#include "user.hpp"
#include "stubPR.hpp"
#include "subject.hpp"

class InterfaceBLAuth;
class InterfaceBLUser;
class InterfaceBLAdmin;
class InterfaceBLQuiz;
class StubPR;

/// Interface do Módulo UI de Autenticação
class InterfaceUIAuth {
public:
    virtual User * requestAuth (void) = 0;
    virtual void setDownstreamController(InterfaceBLAuth *) = 0;
    virtual ~InterfaceUIAuth(void) {}
};

/// Interface do Módulo BL de Autenticação
class InterfaceBLAuth {
public:
    virtual User * authenticate(const string &, const string &) = 0;
    virtual void setDownstreamController(StubPR *) = 0;
    virtual ~InterfaceBLAuth(void) {}
};

/// Interface do Módulo UI de Usuário
class InterfaceUIUser {
public:
    virtual void manageUserData (User*) = 0;
    virtual void manageUserSubjects (User*) = 0;
    virtual void changeName(User *) = 0;
    virtual void changePass(User *) = 0;
    virtual void showSubjects(User *) = 0;
    virtual void includeSubject(User *) = 0;
    virtual void removeSubject(User *) = 0;
    virtual void setDownstreamController(InterfaceBLUser *) = 0;
    virtual ~InterfaceUIUser(void) {}
};

/// Interface do Módulo BL de Usuário
class InterfaceBLUser {
public:
    virtual bool changeName(User *, const string &) = 0;
    virtual bool changePass(User *, const string &, const string &) = 0;
    virtual std::queue<Subject> getSubjectsBank(void) = 0;
    virtual void includeSubject(User *, const string &) = 0;
    virtual void removeSubject(User *, const string &) = 0;
    virtual void setDownstreamController(StubPR *) = 0;
    virtual ~InterfaceBLUser(void) {}
};

/// Interface do Módulo UI de Admin
class InterfaceUIAdmin {
public:
    virtual void manageStudents(void) = 0;
    virtual void includeStudent(void) = 0;
    virtual void removeStudent(void) = 0;
    virtual void setDownstreamController(InterfaceBLAdmin *) = 0;
    virtual ~InterfaceUIAdmin(void) {}
};

/// Interface do Módulo BL de Admin
class InterfaceBLAdmin {
public:
    virtual bool includeStudent(const string &, const string &, const string &, int) = 0;
    virtual std::queue<User> getUserBank(void) = 0;
    virtual void removeStudent(User *) = 0;
    virtual void setDownstreamController(StubPR *) = 0;
    virtual ~InterfaceBLAdmin(void) {}
};

/// Interface do Módulo UI de Quiz
class InterfaceUIQuiz {
public:
    virtual void (answerQuiz(User *)) = 0;
    virtual void setDownstreamController(InterfaceBLQuiz *) = 0;
    virtual ~InterfaceUIQuiz(void) {}
};

/// Interface do Módulo BL de Admin
class InterfaceBLQuiz {
public:
    virtual void setDownstreamController(StubPR *) = 0;
    virtual ~InterfaceBLQuiz(void) {}
};

#endif