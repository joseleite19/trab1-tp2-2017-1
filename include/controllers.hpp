#ifndef CONTROLLERS_H
#define CONTROLLERS_H

#include <vector>
#include <map>
#include "interfaces.hpp"
#include "subject.hpp"

/// INITIALIZATION

class ControllerInit {
private:
    InterfaceUIAuth * controllerUIAuth;
    InterfaceUIUser * controllerUIUser;
    InterfaceUIAdmin * controllerUIAdmin;
    InterfaceUIQuiz * controllerUIQuiz;
    InterfaceBLAuth * controllerBLAuth;
    InterfaceBLUser * controllerBLUser;
    InterfaceBLAdmin * controllerBLAdmin;
    InterfaceBLQuiz * controllerBLQuiz;
    StubPR * controllerPR;
    User * user = nullptr;

public:
    void showUI (void);
    void initialize(void);
    ~ControllerInit(void);
};

/// AUTHENTICATION

class ControllerUIAuth : public InterfaceUIAuth {

private:
    InterfaceBLAuth * controllerBL;
public:
    User * requestAuth (void);
    inline void setDownstreamController(InterfaceBLAuth * controllerBL) { this->controllerBL = controllerBL; }
    ~ControllerUIAuth(void);
    ControllerUIAuth(void);
};

class ControllerBLAuth : public InterfaceBLAuth {
private:
    StubPR * controllerPR;
public:
    User * authenticate(const string &, const string &);
    inline void setDownstreamController(StubPR * controllerPR) { this->controllerPR = controllerPR; }
    ControllerBLAuth(void);
    ~ControllerBLAuth(void);
};

/// USER

class ControllerUIUser : public InterfaceUIUser {
private:
    InterfaceBLUser * controllerBL;
public:
    void manageUserData (User *);
    void manageUserSubjects (User *);
    void changeName(User *);
    void changePass(User *);
    void showSubjects(User *);
    void includeSubject(User *);
    void removeSubject(User *);
    inline void setDownstreamController(InterfaceBLUser * controllerBL) { this->controllerBL = controllerBL; }
    ~ControllerUIUser(void);
    ControllerUIUser(void);
};

class ControllerBLUser : public InterfaceBLUser {
private:
    StubPR * controllerPR;
public:
    bool changeName(User *, const string &);
    bool changePass(User *, const string &, const string &);
    std::map<std::string,Subject*>& getSubjectsBank();
    void includeSubject(User *, const string &);
    void removeSubject(User *, const string &);
    inline void setDownstreamController(StubPR * controllerPR) { this->controllerPR = controllerPR; }
    ControllerBLUser(void);
    ~ControllerBLUser(void);
};

/// ADMIN

class ControllerUIAdmin : public InterfaceUIAdmin {
private:
    InterfaceBLAdmin * controllerBL;
public:
    void manageStudents();
    void includeStudent();
    void removeStudent();
    void manageSubjects();
    void includeSubject();
    void includeTopic();
    void includeQuiz();
    void removeSubject();
    void removeTopic();
    void removeQuiz();
    inline void setDownstreamController(InterfaceBLAdmin * controllerBL) { this->controllerBL = controllerBL; }
    ControllerUIAdmin();
    ~ControllerUIAdmin();
};

class ControllerBLAdmin : public InterfaceBLAdmin {
private:
    StubPR * controllerPR;
public:
    bool includeStudent(const string &, const string &, const string &, int);
    std::map<std::string,User*>& getUserBank();
    std::map<std::string,Subject*>& getSubjectsBank();
    void removeStudent(User *);
    bool includeSubject(const string &);
    bool includeTopic(const string &, Subject *);
    bool includeQuiz(const string &, std::vector<Question *>, Topic *);
    void removeSubject(Subject *);
    void removeTopic(Topic *, Subject *);
    void removeQuiz(Quiz *, Topic *, Subject *);
 
    inline void setDownstreamController(StubPR * controllerPR) { this->controllerPR = controllerPR; }
    ControllerBLAdmin();
    ~ControllerBLAdmin();
};

/// Quiz

class ControllerUIQuiz : public InterfaceUIQuiz {
private:
    InterfaceBLQuiz * controllerBL;
public:
    void answerQuiz(User *);
    inline void setDownstreamController(InterfaceBLQuiz * controllerBL) { this->controllerBL = controllerBL; }
    ControllerUIQuiz();
    ~ControllerUIQuiz();
};

class ControllerBLQuiz : public InterfaceBLQuiz {
private:
    StubPR * controllerPR;
public:
    inline void setDownstreamController(StubPR * controllerPR) { this->controllerPR = controllerPR; }
    ControllerBLQuiz();
    ~ControllerBLQuiz();
};

#endif
