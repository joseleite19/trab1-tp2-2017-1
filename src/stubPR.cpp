#include "user.hpp"
#include "stubPR.hpp"

StubPR::StubPR() {
    this->dummy_user = new User("Dummy User", "dummy01", "abc123", true);
}

StubPR::~StubPR() {
    delete this->dummy_user;
}

User * StubPR::retrieveUser(const string & login) {
    if(login == this->dummy_user->get_login()) {
        return this->dummy_user;
    }
    else {
        return nullptr;
    }
}
