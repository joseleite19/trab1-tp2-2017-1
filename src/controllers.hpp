#ifndef CONTROLLERS_H
#define CONTROLLERS_H

#include <queue>
#include "interfaces.hpp"
#include "subject.hpp"

/// INITIALIZATION

class ControllerInit {
private:
    InterfaceUIAuth * controllerUIAuth;
    InterfaceUIUser * controllerUIUser;
    InterfaceBLAuth * controllerBLAuth;
    InterfaceBLUser * controllerBLUser;
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
    std::queue<Subject> getSubjectsBank();
    void includeSubject(User *, const string &);
    void removeSubject(User *, const string &);
    inline void setDownstreamController(StubPR * controllerPR) { this->controllerPR = controllerPR; }
    ControllerBLUser(void);
    ~ControllerBLUser(void);
};

#endif
