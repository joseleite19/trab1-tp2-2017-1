#include <cstdio>
#include <iostream>
#include <string>
#include <typeinfo>
#include <map>

#include "user.hpp"
#include "controllers.hpp"
#include "stubPR.hpp"

/// INITIALIZATION

void ControllerInit::initialize() {
    this->controllerUIAuth = new ControllerUIAuth();
    this->controllerUIUser = new ControllerUIUser();
    this->controllerBLAuth = new ControllerBLAuth();
    this->controllerBLUser = new ControllerBLUser();
 
    this->controllerPR     = new StubPR();
    this->controllerUIAuth ->setDownstreamController(controllerBLAuth);
    this->controllerUIUser ->setDownstreamController(controllerBLUser);
    this->controllerBLAuth ->setDownstreamController(controllerPR);
    this->controllerBLUser ->setDownstreamController(controllerPR);
}

ControllerInit::~ControllerInit() {
    delete controllerUIAuth;
    delete controllerBLAuth;
    delete controllerUIUser;
    delete controllerBLUser;
    delete controllerPR;
}

void ControllerInit::showUI() {
    
    int sel = -1;
    while(sel != 0) {
        char buffer[64];
        system(CLEAR);
        printf("QuizTime - Menu principal\n\n");
        
        if(user == nullptr) {
            printf("1. Fazer log-in\n");
        } else {
            printf("1. Gerenciar informacoes pessoais\n");
            printf("2. Gerenciar disciplinas\n");
            printf("3. Responder quiz\n");
            if(user->isAdmin()) {
                printf("4. Cadastrar aluno\n");
                printf("5. Criar disciplina/quiz\n");
            }
        }
        printf("9. Fazer log-out\n");
        printf("0. Sair\n");
        printf("\nInforme a opcao desejada: ");

        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &sel);

        switch(sel) {
            case 1: if (user == nullptr) user = this->controllerUIAuth->requestAuth();
                    else this->controllerUIUser->manageUserData(user);
                    sel = -1; break;
            case 2: this->controllerUIUser->manageUserSubjects(user); sel = -1; break;
            //case 3: this->controllerUIUser->answerQuiz(user); sel = -1; break;
            //case 4: this->controllerUISystemData->manageStudents(); sel = -1; break;
            //case 5: this->controllerUISystemData->manageSubjects(); sel = -1; break;
            case 9: user = nullptr; sel = -1; break;
            default: break;
        }
    }
}

/// AUTHENTICATION

ControllerUIAuth::ControllerUIAuth () { }
ControllerUIAuth::~ControllerUIAuth() { }

User * ControllerUIAuth::requestAuth() {

    string login;
    string pass;

    system(CLEAR);
    printf("QuizTime - Log-in\n\n");
    printf("Login: ");
    getline(cin, login);
    printf("Senha: ");
    getline(cin, pass);

    return controllerBL->authenticate(login,pass);
}

ControllerBLAuth::ControllerBLAuth () { }
ControllerBLAuth::~ControllerBLAuth() { }

User * ControllerBLAuth::authenticate(const string & login, const string & pwd) {
    User * user = controllerPR->retrieveUser(login);
    if (user != nullptr) {
        if (user->tryLogin(login, pwd)) {
            return user;
        } else {
            return nullptr;
        }
    }
    else return nullptr;
}

/// USER

ControllerUIUser::ControllerUIUser () { }
ControllerUIUser::~ControllerUIUser() { }

void ControllerUIUser::manageUserData(User * user) {
    int sel = -1;
    while(sel != 0) {
        char buffer[64];
        system(CLEAR);
        printf("QuizTime - Gerenciamento de Informacoes Pessoais\n\n");

        printf("1. Alterar nome\n");
        printf("2. Alterar senha\n");
        printf("0. Voltar\n");
        printf("\nInforme a opcao desejada: ");

        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &sel);

        switch(sel) {
            case 1: changeName(user); sel = -1; break; 
            case 2: changePass(user); sel = -1; break;
            default: break;
        }
    }
}

void ControllerUIUser::manageUserSubjects(User * user) {
    int sel = -1;
    while(sel != 0) {
        char buffer[64];
        system(CLEAR);
        printf("QuizTime - Gerenciamento de Disciplinas\n\n");

        printf("1. Mostrar disciplinas em curso\n");
        printf("2. Fazer matricula em disciplina\n");
        printf("3. Trancar disciplina\n");
        printf("0. Voltar\n");
        printf("\nInforme a opcao desejada: ");

        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &sel);

        switch(sel) {
            case 1: showSubjects(user); sel = -1; break;
            case 2: includeSubject(user); sel = -1; break;
            case 3: removeSubject(user); sel = -1; break;
            default: break;
        }
    }
}

ControllerBLUser::ControllerBLUser  () { }
ControllerBLUser::~ControllerBLUser () { }

void ControllerUIUser::changeName(User * user) {
    string name;
    string new_name;
    name = user->getName();
    system(CLEAR);
    printf("QuizTime - Alterar Nome\n\n");
    printf("O seu nome atual eh %s\n", name.c_str());
    printf("Insira um novo nome: ");
    getline(cin, new_name);

    controllerBL->changeName(user, new_name);
}

bool ControllerBLUser::changeName(User * user, const string & name) {
    controllerPR->storeName(user, name);
    user = controllerPR->retrieveUser(user->getLogin());
    return true;
}

void ControllerUIUser::changePass(User * user) {
    string pass;
    string new_pass;
    system(CLEAR);
    printf("QuizTime - Alterar Senha\n\n");
    printf("Senha atual: ");
    getline(cin, pass);
    printf("Nova senha: ");
    getline(cin, new_pass);
    if(!controllerBL->changePass(user, pass, new_pass)){
        printf("\nErro: senha atual incorreta.\n");
        getchar();
    }
}

bool ControllerBLUser::changePass(User * user, const string & pass, const string & new_pass) {
    if (user->setPassword(pass, new_pass)) {
        controllerPR->storePass(user, new_pass);
        return true;
    }
    else return false;
}

void ControllerUIUser::showSubjects(User * user) {
    user->showSubjects();
    getchar();
}

void ControllerUIUser::includeSubject(User * user) {
    std::queue<Subject> subjects_bank;
    std::queue<Subject> aux;
    std::map <int, string> subs_map;
    int sel = -1;
    int i;
    while(sel != 0) {
        char buffer[64];
        system(CLEAR);
        printf("QuizTime - Matricula em Disciplina\n\n");
        subjects_bank = controllerBL->getSubjectsBank();
        i = 1;
        while(!subjects_bank.empty()) {
            printf("%d. %s\n", i, subjects_bank.front().getName().c_str());
            aux.push(subjects_bank.front());
            subs_map[i] = subjects_bank.front().getName();
            subjects_bank.pop();
            i++;
        }
        printf("0. Voltar\n");
        printf("\nInforme a opcao desejada: ");

        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &sel);

        if(sel != 0) {
            controllerBL->includeSubject(user, subs_map[sel]);
        }
    } 
}

std::queue<Subject> ControllerBLUser::getSubjectsBank() {
    return controllerPR->getSubjectsBank();
}

void ControllerBLUser::includeSubject(User * user, const string & name) {
    controllerPR->storeSubject(user, name);
    user = controllerPR->retrieveUser(user->getLogin());
}

void ControllerUIUser::removeSubject(User * user) {
    std::queue<Subject> subjects;
    std::queue<Subject> aux;
    std::map <int, string> subs_map;
    int sel = -1;
    int i;
    while(sel != 0) {
        char buffer[64];
        system(CLEAR);
        printf("QuizTime - Trancamento de Disciplina\n\n");
        subjects = user->getSubjects();
        i = 1;
        while(!subjects.empty()) {
            printf("%d. %s\n", i, subjects.front().getName().c_str());
            aux.push(subjects.front());
            subs_map[i] = subjects.front().getName();
            subjects.pop();
            i++;
        }
        printf("0. Voltar\n");
        printf("\nInforme a opcao desejada: ");

        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &sel);

        if(sel != 0) {
            controllerBL->removeSubject(user, subs_map[sel]);
        }
    }
} 

void ControllerBLUser::removeSubject(User * user, const string & name) {
    controllerPR->deleteSubject(user, name);
    user = controllerPR->retrieveUser(user->getLogin());
}
