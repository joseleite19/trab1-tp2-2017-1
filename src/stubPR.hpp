#ifndef STUBS_H
#define STUBS_H

#include "user.hpp"

class StubPR {
private:
public:
    User * dummy_user;
    StubPR(void);
    ~StubPR(void);

    User * retrieveUser(const string &);
};
#endif
