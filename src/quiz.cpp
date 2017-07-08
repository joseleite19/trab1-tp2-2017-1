/**
/*
*   @author joseleite19
*   @since 07/05/2017
*   @version 3.0
*/


#include "quiz.hpp"

#include <vector>
#include "helper.hpp"

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

Quiz::Quiz(const std::string & name){
    this->name = name;
}

Quiz::~Quiz(){

}

std::string Quiz::getname() const{
	return name;
}

std::string Quiz::setname(std::string newname){
	return name = newname;
}

void Quiz::addQuestion(Question question) {
    this->questions.push_back(question);
}

void Quiz::run(int user_id){
    int pts = 0;
    char ans;
    char buffer[64];

    for(int i = 1; i < 10; i++){
        system(CLEAR);
        printf("Questao %d: ", i);
        questions[i].show();
        printf("\n1. Responder\n");
        printf("0. Pular\n");
        /** menu: 1 = responder; 0 = pular; -1 = sair. */
        printf("Selecione a opcao desejada: ");
        int op = readIntInRange(0, 1);
        if(op == 0) i = i;
        else{
            ans = 'O';
            printf("Resposta: ");
            while(ans != 'V' && ans != 'F') {
                fgets(buffer, sizeof(buffer), stdin);
                sscanf(buffer, "%c", &ans);
            }
            if(ans == questions[i].getresp())
                pts += questions[i].getPontuacao();
        }
    }
    system(CLEAR);
    printf("\nQuantidade de respostas corretas: %d\n", pts);
    while(getchar() != '\n');

    // user_id pts

    insert_pontuacao(pts, user_id);
    /** Aqui a pessoa terminou de fazer o Quiz. */

}

const std::vector<Question>& Quiz::getQuestions() const{
	return questions;
}

void Quiz::insert_pontuacao(int pt, int user_id){
    pontuacoes.insert(std::make_pair(pt, user_id));
    while(pontuacoes.size() > 10) pontuacoes.erase(pontuacoes.begin());
}
const std::multiset<std::pair<int, int>>& Quiz::getPontuacoes() const{
    return pontuacoes;
}


