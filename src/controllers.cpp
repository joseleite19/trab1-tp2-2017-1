#include <cstdio>
#include <iostream>
#include <string>
#include <typeinfo>

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
            if(user->is_admin()) {
                printf("4. Cadastrar aluno\n");
                printf("5. Gerenciar disciplinas\n");
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
            //case 2: this->controllerUIUser->manageUserSubjects(user); sel = -1; break;
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
    if (user->try_login(login, pwd)) {
        return user;
    } else {
        return nullptr;
    }
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
    }

    switch(sel) {
        //case 1: this->controllerBLUser->changeName(); sel = -1; break; 
        //case 2: this->controllerBLUser->changePass(); sel = -1; break;
        default: break;
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
    }

    switch(sel) {
        //case 1: this->controllerBLUser->showSubjects(); sel = -1; break;
        //case 2: this->controllerBLUser->includeSubject(); sel = -1; break;
        //case 3: this->controllerBLUser->removeSubject(); sel = -1; break;
        default: break;
    }
}

ControllerBLUser::ControllerBLUser  () { }
ControllerBLUser::~ControllerBLUser () { }

void ControllerBLUser::changeName(User * user) {
}

void ControllerBLUser::changePass(User * user) {
}

void ControllerBLUser::showSubjects(User * user) {
}

void ControllerBLUser::includeSubject(User * user) {
}

void ControllerBLUser::removeSubject(User * user) {
}

