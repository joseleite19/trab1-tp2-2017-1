#include "user.hpp"
#include "stubPR.hpp"
#include "subject.hpp"
#include <queue>

StubPR::StubPR() {
    this->dummy_sub = new Subject("Matematica");
    this->dummy_topic = new Topic("Algebra");
    this->dummy_quiz = new Quiz("Quiz 1");
    this->dummy_quiz->addQuestion(Question("1+1 = 2?", 'V'));
    this->dummy_quiz->addQuestion(Question("2+2 = 2?", 'F'));
    this->dummy_quiz->addQuestion(Question("2+0 = 2?", 'V'));
    this->dummy_quiz->addQuestion(Question("0+0 = 2?", 'F'));
    this->dummy_quiz->addQuestion(Question("2 = 2?", 'V'));
    this->dummy_quiz->addQuestion(Question("1 = 2?", 'F'));
    this->dummy_quiz->addQuestion(Question("4/2 = 2?", 'V'));
    this->dummy_quiz->addQuestion(Question("6/2 = 2?", 'F'));
    this->dummy_quiz->addQuestion(Question("1*2 = 2?", 'V'));
    this->dummy_quiz->addQuestion(Question("4*4 = 2?", 'F'));
    this->dummy_topic->addQuiz(*this->dummy_quiz);
    this->dummy_sub->addTopic(*this->dummy_topic);

    this->dummy_user = new User("Dummy User", "dummy01", "abc123", true);
    this->dummy_user->includeSubject(*this->dummy_sub);
    this->dummy_user->includeSubject(Subject("Portugues"));
    this->dummy_user->includeSubject(Subject("Geografia"));
    

    std::queue<Subject> db;
    this->dummy_subs_bank = db;
    this->dummy_subs_bank.push(*this->dummy_sub);
    this->dummy_subs_bank.push(Subject("Portugues"));
    this->dummy_subs_bank.push(Subject("Geografia"));
    this->dummy_subs_bank.push(Subject("Historia"));
    this->dummy_subs_bank.push(Subject("Biologia"));
    this->dummy_subs_bank.push(Subject("Física"));
    this->dummy_subs_bank.push(Subject("Quimica"));
    this->dummy_subs_bank.push(Subject("Filosofia"));
    this->dummy_subs_bank.push(Subject("Artes"));

    std::queue<User> user_db;
    this->dummy_user_bank = user_db;
    this->dummy_user_bank.push(User("Albert Einstein", "alb05", "e=mc2", false));
    this->dummy_user_bank.push(User("Kurt Goedel", "kurtg", "kennwort", false));
    this->dummy_user_bank.push(User("Homer Simpson", "homer", "zoeira", false));
    this->dummy_user_bank.push(User("Jane Austen", "jane01", "16121775", false));
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

/// ADMIN

bool StubPR::storeUserData(User * user) {
    int already_in = 0;
    std::queue<User> aux;
    while(!this->dummy_user_bank.empty()) {
        if(this->dummy_user_bank.front().getLogin() == user->getLogin()) {
            already_in = 1;
        }
        aux.push(this->dummy_user_bank.front());
        this->dummy_user_bank.pop();
    }
    this->dummy_user_bank = aux;
    if(!already_in) {
        this->dummy_user_bank.push(*user);
        return true;
    }
    return false;
}

std::queue<User> StubPR::getUserBank() {
    return this->dummy_user_bank;
}

void StubPR::deleteUser(User * user) {
    std::queue<User> aux;
    std::string login = user->getLogin(); 
    while(!this->dummy_user_bank.empty()) {
        if(this->dummy_user_bank.front().getLogin() != login) {
            aux.push(this->dummy_user_bank.front());
        }
        this->dummy_user_bank.pop();
    }
    this->dummy_user_bank = aux;
}
