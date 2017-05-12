#include <cstdio>
#include <iostream>
#include <string>
#include <typeinfo>
#include <map>
#include <algorithm>

#include "user.hpp"
#include "controllers.hpp"
#include "stubPR.hpp"

/// INITIALIZATION

void ControllerInit::initialize() {
    this->controllerUIAuth  = new ControllerUIAuth();
    this->controllerUIUser  = new ControllerUIUser();
    this->controllerUIAdmin = new ControllerUIAdmin();
    this->controllerUIQuiz  = new ControllerUIQuiz();
    this->controllerBLAuth  = new ControllerBLAuth();
    this->controllerBLUser  = new ControllerBLUser();
    this->controllerBLAdmin = new ControllerBLAdmin();
    this->controllerBLQuiz  = new ControllerBLQuiz();
 
    this->controllerPR      = new StubPR();
    this->controllerUIAuth ->setDownstreamController(controllerBLAuth);
    this->controllerUIUser ->setDownstreamController(controllerBLUser);
    this->controllerUIAdmin->setDownstreamController(controllerBLAdmin);
    this->controllerUIQuiz ->setDownstreamController(controllerBLQuiz);
    this->controllerBLAuth ->setDownstreamController(controllerPR);
    this->controllerBLUser ->setDownstreamController(controllerPR);
    this->controllerBLAdmin->setDownstreamController(controllerPR);
    this->controllerBLQuiz ->setDownstreamController(controllerPR);
}

ControllerInit::~ControllerInit() {
    delete controllerUIAuth;
    delete controllerBLAuth;
    delete controllerUIUser;
    delete controllerBLUser;
    delete controllerUIAdmin;
    delete controllerBLAdmin;
    delete controllerUIQuiz;
    delete controllerBLQuiz;
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
                printf("4. Gerenciar banco de dados de alunos\n");
                printf("5. Gerenciar banco de dados de disciplinas\n");
            }
            printf("9. Fazer log-out\n");
        }
        printf("0. Sair\n");
        printf("\nInforme a opcao desejada: ");

        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &sel);

        switch(sel) {
            case 1: if (user == nullptr) user = this->controllerUIAuth->requestAuth();
                    else this->controllerUIUser->manageUserData(user);
                    sel = -1; break;
            case 2: this->controllerUIUser->manageUserSubjects(user); sel = -1; break;
            case 3: this->controllerUIQuiz->answerQuiz(user); sel = -1; break;
            case 4: this->controllerUIAdmin->manageStudents(); sel = -1; break;
            case 5: this->controllerUIAdmin->manageSubjects(); sel = -1; break;
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
    printf("O seu nome atual é %s\n", name.c_str());
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
    std::map <int, string> subs_map;
    int sel = -1;
    int i;
    while(sel != 0) {
        auto subs=user->getSubjects();
        char buffer[64];
        system(CLEAR);
        printf("QuizTime - Matricula em Disciplina\n\n");
        i = 1;
        for(auto it:controllerBL->getSubjectsBank()){

            auto iter=std::find_if(subs.begin(),subs.end(),[it](const Subject& comp){return comp.getName()==it.second->getName();});
            if(iter!=subs.end())continue;

            printf("%d. %s\n", i, it.second->getName().c_str());
            subs_map[i] = it.second->getName();
            i++;
        }
        printf("0. Voltar\n");
        printf("\nInforme a opcao desejada: ");

        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &sel);

        if(sel != 0 && sel < i) {
            controllerBL->includeSubject(user, subs_map[sel]);
        }
    } 
}

std::map<std::string,Subject*>& ControllerBLUser::getSubjectsBank() {
    return controllerPR->getSubjectsBank();
}

void ControllerBLUser::includeSubject(User * user, const string & name) {
    controllerPR->storeSubject(user, name);
    user = controllerPR->retrieveUser(user->getLogin());
}

void ControllerUIUser::removeSubject(User * user) {
    std::vector<Subject> subjects;
    std::map <int, string> subs_map;
    int sel = -1;
    int i;
    while(sel != 0) {
        char buffer[64];
        system(CLEAR);
        printf("QuizTime - Trancamento de Disciplina\n\n");
        subjects = user->getSubjects();
        i = 1;
        for(Subject &sub:subjects){
            printf("%d. %s\n", i, sub.getName().c_str());
            subs_map[i] = sub.getName();
            i++;
        }
        printf("0. Voltar\n");
        printf("\nInforme a opcao desejada: ");

        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &sel);

        if(sel != 0 && i<0) {
            controllerBL->removeSubject(user, subs_map[sel]);
        }
    }
} 

void ControllerBLUser::removeSubject(User * user, const string & name) {
    controllerPR->deleteSubject(user, name);
    user = controllerPR->retrieveUser(user->getLogin());
}

// ADMINISTRATOR

ControllerUIAdmin::ControllerUIAdmin () { }
ControllerUIAdmin::~ControllerUIAdmin() { }

void ControllerUIAdmin::manageStudents() {
    int sel = -1;
    while(sel != 0) {
        char buffer[64];
        system(CLEAR);
        printf("QuizTime - Gerenciamento de Contas\n\n");

        printf("1. Cadastrar novo aluno\n");
        printf("2. Remover aluno\n");
        printf("0. Voltar\n");
        printf("\nInforme a opcao desejada: ");

        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &sel);

        switch(sel) {
            case 1: includeStudent(); sel = -1; break;
            case 2: removeStudent(); sel = -1; break;
            default: break;
        }
    }
}

void ControllerUIAdmin::includeStudent() {
    string name, login, pass, adm;
    system(CLEAR);
    printf("QuizTime - Cadastro de Aluno\n\n");
    printf("Nome do aluno: ");
    getline(cin, name);
    printf("Login: ");
    getline(cin, login);
    printf("Senha: ");
    getline(cin, pass);
    printf("Deseja atribuir ao aluno status de admin? (s/n)");
    while(adm != "s" && adm != "n") {
        getline(cin, adm);
    }
    if(!controllerBL->includeStudent(name, login, pass, adm == "s")){
        printf("\nErro: login já cadastrado.\n");
        getchar();
    } else {
        printf("\nAluno cadastrado com sucesso.\n");
        getchar();
    }
}

ControllerBLAdmin::ControllerBLAdmin () { }
ControllerBLAdmin::~ControllerBLAdmin() { }

bool ControllerBLAdmin::includeStudent(const string& name, const string& login, const string& pass, int adm) {
    User * user = new User(name, login, pass, adm);
    if(controllerPR->storeUserData(user)) return true;
    return false;
}

void ControllerUIAdmin::removeStudent() {
    std::map <int, User*> user_map;
    int sel = -1;
    int i;
    while(sel != 0) {
        char buffer[64];
        system(CLEAR);
        printf("QuizTime - Remover Usuario\n\n");
        i = 1;
        for(auto it:controllerBL->getUserBank()){
            User *user=it.second;
            if(!user->isAdmin()) {
                printf("%d. %s\n", i, it.first.c_str()/*username*/);
                user_map[i] = user;
                i++;
            }
        }
        printf("0. Voltar\n");
        printf("\nInforme o numero do usuario a ser removido: ");

        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &sel);

        if(sel != 0 && sel < i) {
            controllerBL->removeStudent(user_map[sel]);
        }
    }
}

void ControllerBLAdmin::removeStudent(User * user) {
    controllerPR->deleteUser(user);
}

std::map<std::string,User*>& ControllerBLAdmin::getUserBank() {
    return controllerPR->getUserBank();
}

void ControllerUIAdmin::manageSubjects() {
    int sel = -1;
    while(sel != 0) {
        char buffer[64];
        system(CLEAR);
        printf("QuizTime - Gerenciamento de Disciplinas\n\n");

        printf("1. Criar nova disciplina\n");
        printf("2. Adicionar novo topico a disciplina\n");
        printf("3. Criar novo quiz\n");
        printf("4. Remover disciplina\n");
        printf("5. Remover topico de disciplina\n");
        printf("6. Remover quiz\n");
        printf("0. Voltar\n");
        printf("\nInforme a opcao desejada: ");

        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &sel);

        switch(sel) {
            case 1: includeSubject(); sel = -1; break;
            case 2: includeTopic(); sel = -1; break;
            case 3: includeQuiz(); sel = -1; break;
            case 4: removeSubject(); sel = -1; break;
            case 5: removeTopic(); sel = -1; break;
            case 6: removeQuiz(); sel = -1; break;
            default: break;
        }
    }
}

void ControllerUIAdmin::includeSubject() {
    string name;
    system(CLEAR);
    printf("QuizTime - Cadastro de Disciplina\n\n");
    printf("Nome da disciplina: ");
    getline(cin, name);
    if(!controllerBL->includeSubject(name)){
        printf("\nErro: disciplina já cadastrada.\n");
        getchar();
    } else {
        printf("\nDisciplina cadastrada com sucesso.\n");
        getchar();
    }
}
void ControllerUIAdmin::includeTopic() {
    std::map <int, Subject*> subs_map;
    string name;
    int sel = -1;
    int i;
    while(sel != 0) {
        char buffer[64];
        system(CLEAR);
        printf("QuizTime - Inserir Topico\n\n");
        i = 1;
        for(auto it:controllerBL->getSubjectsBank()){
            Subject *sub=it.second;
            printf("%d. %s\n", i, it.first.c_str());
            subs_map[i] = sub;
            i++;
        }
        printf("0. Voltar\n");
        printf("\nSelecione uma disciplina para inserir o topico: ");

        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &sel);

       if(sel != 0 && sel < i) {

            printf("Nome do novo topico: ");
            getline(cin, name);

            if(!controllerBL->includeTopic(name, subs_map[sel])){
                printf("\nErro: topico já cadastrado.\n");
                getchar();
            } else {
                printf("\nTopico cadastrado com sucesso.\n");
                getchar();
            }
        }
        else {
            if(sel != 0) {
                printf("Selecao de disciplina invalida.\n");
                getchar();
            }
        }
    }
}

void ControllerUIAdmin::includeQuiz() {
    std::vector<Topic> topics;
    std::map <int, Subject*> subs_map;
    std::map <int, Topic*> tops_map;
    std::vector<Question*> questions;
    string name, quest;
    char ans;
    int sel1 = -1, sel2 = -1;
    int i;
    while(sel1 != 0) {
        char buffer[64];
        system(CLEAR);
        printf("QuizTime - Criar Novo Quiz\n\n");
        i = 1;
        for(auto it:controllerBL->getSubjectsBank()){
            Subject *sub=it.second;
            printf("%d. %s\n", i, it.first.c_str()/*username*/);
            subs_map[i] = sub;
            i++;
        }
        printf("0. Voltar\n");
        printf("\nSelecione uma disciplina para inserir o quiz: ");

        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &sel1);

        if(sel1 != 0 && sel1 < i) {
            while(sel2 != 0) {
                char buffer[64];
                system(CLEAR);
                printf("QuizTime - Criar Novo Quiz\n\n");
                i = 1;
                topics = subs_map[sel1]->getTopics();
                for(Topic &top:topics){
                    printf("%d. %s\n", i, top.getName().c_str());
                    tops_map[i] = &top;
                    i++;
                }
                printf("0. Voltar\n");
                printf("\nSelecione um topico para inserir o quiz: ");

                fgets(buffer, sizeof(buffer), stdin);
                sscanf(buffer, "%d", &sel2);

                if(sel2 != 0 && sel2 < i) {

                    printf("Nome do novo quiz: ");
                    getline(cin, name);

                    for(int k=0; k<10; k++) {
                        ans = 'O';
                        printf("Pergunta numero %d: ", k+1);
                        getline(cin, quest);
                        while(ans != 'V' && ans != 'F') {
                            printf("Resposta (V/F): ");
                            fgets(buffer, sizeof(buffer), stdin);
                            sscanf(buffer, "%c", &ans); 
                        }
                        questions.push_back(new Question(quest, ans));
                    }

                    if(!controllerBL->includeQuiz(name, questions, subs_map[sel1], tops_map[sel2])){
                        printf("\nErro: topico já cadastrado.\n");
                        getchar();
                    } else {
                        printf("\nTopico cadastrado com sucesso.\n");
                        getchar();
                    }
                } else {
                    if(sel2 != 0) {
                        printf("Selecao de topico invalida.\n");
                        getchar();
                    }
                }
            }
        } else {
            if(sel1 != 0) {
                printf("Selecao de disciplina invalida.\n");
                getchar();
            }
        }
    }
}

std::map<std::string,Subject*>& ControllerBLAdmin::getSubjectsBank() {
    return controllerPR->getSubjectsBank();
}
bool ControllerBLAdmin::includeSubject(const string & name) {
    std::map<std::string,Subject*> subs = controllerPR->getSubjectsBank();
    for(auto it:subs){
        if(name == it.first) return false;
    }
    //controllerPR->storeSubjectDB(new Subject(name));
    return true;
}
bool ControllerBLAdmin::includeTopic(const string & name, Subject * sub) {
    for(auto it:sub->getTopics()){
        if(name == it.getName()) return false;
    }
    sub->addTopic(Topic(name));
    //controllerPR->storeSubjectDB(sub); 
    return true;
}
bool ControllerBLAdmin::includeQuiz(const string & name, std::vector<Question*> questions, Subject * sub, Topic * top) {
    for(auto it:top->getQuizes()){
        if(name == it.getname()) return false;
    }
    Quiz quiz = Quiz(name);
    for(int i=0; i<10; i++) {
        quiz.addQuestion(*questions[i]);
    }
    top->addQuiz(quiz);
    //controllerPR->storeSubjectDB(sub);
    return true;
}

void ControllerUIAdmin::removeSubject() {}
void ControllerUIAdmin::removeTopic() {}
void ControllerUIAdmin::removeQuiz() {}

void ControllerBLAdmin::removeSubject(Subject * sub) {}
void ControllerBLAdmin::removeTopic(Topic * top, Subject * sub) {}
void ControllerBLAdmin::removeQuiz(Quiz * quiz, Topic * top, Subject * sub) {}

/// QUIZ

ControllerUIQuiz::ControllerUIQuiz () { }
ControllerUIQuiz::~ControllerUIQuiz() { }

ControllerBLQuiz::ControllerBLQuiz () { }
ControllerBLQuiz::~ControllerBLQuiz() { }

void ControllerUIQuiz::answerQuiz(User * user) {
    std::vector<Subject> subjects;
    std::map <int, Subject*> subs_map;
    std::vector<Topic> topics;
    std::map <int, Topic*> tops_map;
    std::vector<Quiz> quizzes;
    std::map <int, Quiz*> quizzes_map;
    int sel1 = -1, sel2 = -1, sel3 = -1;
    int i;
    while(sel1 != 0) {
        char buffer[64];
        system(CLEAR);
        printf("QuizTime - Responder Quiz\n\n");
        subjects = user->getSubjects();
        i = 1;
        for(Subject &sub:subjects){
            printf("%d. %s\n", i, sub.getName().c_str());
            subs_map[i] = &sub;
            i++;
        }
        printf("0. Voltar\n");
        printf("\nSelecione uma disciplina: ");

        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &sel1);

        if(sel1 != 0 && sel1 < i) {
            while(sel2 != 0) {
                char buffer[64];
                system(CLEAR);
                printf("QuizTime - Responder Quiz\n\n");
                topics = subs_map[sel1]->getTopics();
                i = 1;
                for(Topic &top:topics){
                    printf("%d. %s\n", i, top.getName().c_str());
                    tops_map[i] = &top;
                    i++;
                }
                printf("0. Voltar\n");
                printf("\nSelecione um topico: ");

                fgets(buffer, sizeof(buffer), stdin);
                sscanf(buffer, "%d", &sel2);

                if(sel2 != 0 && sel2 < i) {
                    while(sel3 != 0) {
                        char buffer[64];
                        system(CLEAR);
                        printf("QuizTime - Responder Quiz\n\n");
                        quizzes = tops_map[sel2]->getQuizes();
                        i = 1;
                        for(Quiz &quiz:quizzes){
                            printf("%d. %s\n", i, quiz.getname().c_str());
                            quizzes_map[i] = &quiz;
                            i++;
                        }
                        printf("0. Voltar\n");
                        printf("\nSelecione um quiz: ");

                        fgets(buffer, sizeof(buffer), stdin);
                        sscanf(buffer, "%d", &sel3);

                        if(sel3 != 0 && sel3 < i) {
                            quizzes_map[sel3]->run(10);
                        } else {
                            if(sel3 != 0) {
                                printf("Selecao invalida.\n");
                                getchar ();
                            }
                        }
                    }
                } else {
                    if(sel2 != 0) {
                        printf("Selecao invalida.\n");
                        getchar();
                    }
                }      
            }            
        } else {
            if(sel1 != 0) {
                printf("Selecao invalida.\n");
                getchar ();
            }
        }
    } 
}
