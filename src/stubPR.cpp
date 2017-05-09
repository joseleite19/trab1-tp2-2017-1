#include "user.hpp"
#include "stubPR.hpp"
#include "subject.hpp"
#include <queue>

StubPR::StubPR() {
    this->dummy_user = new User("Dummy User", "dummy01", "abc123", true);
    this->dummy_user->includeSubject("Matematica");
    this->dummy_user->includeSubject("Portugues");
    this->dummy_user->includeSubject("Geografia");

    std::queue<Subject> db;
    this->dummy_subs_bank = db;
    this->dummy_subs_bank.push(Subject("Matematica"));
    this->dummy_subs_bank.push(Subject("Portugues"));
    this->dummy_subs_bank.push(Subject("Geografia"));
    this->dummy_subs_bank.push(Subject("Historia"));
    this->dummy_subs_bank.push(Subject("Biologia"));
    this->dummy_subs_bank.push(Subject("Física"));
    this->dummy_subs_bank.push(Subject("Quimica"));
    this->dummy_subs_bank.push(Subject("Filosofia"));
    this->dummy_subs_bank.push(Subject("Artes"));
}

StubPR::~StubPR() {
    delete this->dummy_user;
}

User * StubPR::retrieveUser(const string & login) {
    if(login == this->dummy_user->getLogin()) {
        return this->dummy_user;
    }
    else {
        return nullptr;
    }
}

void StubPR::storeName(User * user, const string & name) {
    this->dummy_user->setName(name);
}

void StubPR::storePass(User * user, const string & pass) {
    this->dummy_user->setPassword(dummy_user->getPassword(), pass);
}

std::queue<Subject> StubPR::getSubjectsBank() {
    return this->dummy_subs_bank;
}

void StubPR::storeSubject(User * user, const string & name) {
    this->dummy_user->includeSubject(name);
}

void StubPR::deleteSubject(User * user, const string & name) {
    this->dummy_user->removeSubject(name);
}
