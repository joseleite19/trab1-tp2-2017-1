#ifndef STUBS_H
#define STUBS_H

#include <queue>
#include "user.hpp"
#include "subject.hpp"
#include "quiz.hpp"
#include "topic.hpp"

class StubPR {
private:
public:
    User * dummy_user;
    Subject * dummy_sub;
    Topic * dummy_topic;
    Quiz * dummy_quiz;
    std::queue<Subject> dummy_subs_bank;
    std::queue<User> dummy_user_bank;
    StubPR(void);
    ~StubPR(void);

    User * retrieveUser(const string &);
    void storeName(User *, const string &);
    void storePass(User *, const string &);
    std::queue<Subject> getSubjectsBank();
    void storeSubject(User *, const string &);
    void deleteSubject(User *, const string &);
    bool storeUserData(User *);
    std::queue<User> getUserBank();
    void deleteUser(User *);
};
#endif
