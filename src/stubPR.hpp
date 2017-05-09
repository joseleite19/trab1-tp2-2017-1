#ifndef STUBS_H
#define STUBS_H

#include <queue>
#include "user.hpp"
#include "subject.hpp"

class StubPR {
private:
public:
    User * dummy_user;
    std::queue<Subject> dummy_subs_bank;
    StubPR(void);
    ~StubPR(void);

    User * retrieveUser(const string &);
    void storeName(User *, const string &);
    void storePass(User *, const string &);
    std::queue<Subject> getSubjectsBank();
    void storeSubject(User *, const string &);
    void deleteSubject(User *, const string &);
};
#endif
