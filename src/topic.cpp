/**
/*
*   @author AngelicCoder
*   @since 08/05/2017
*   @version 2.0
*/


#include "topic.hpp"
#include <vector>
#include "helper.hpp"
#include "quiz.hpp"

Topic::Topic(const std::string & name){
    this->name = name;
}

Topic::~Topic(){

}

std::string Topic::getName() const {
    return name;
}

void Topic::setName(std::string new_name) {
    this->name = new_name;
}

void Topic::addQuiz(Quiz quiz) {
    this->quizzes.push_back(quiz);
}

/**
*   Função que mostra os quizzes de um determinado tópico de uma disciplina.
*   @param um inteiro que representa o id do usuário.
*   @see    quiz.run()
*   @return vazio.
*/
void Topic::showQuizzes(int user_id) const {
    std::vector<int> id = randompermutation(quizzes.size());

    for(int i:id)quizzes[i].run(user_id);
}

const std::vector<Quiz>& Topic::getQuizes() const{
	return quizzes;
}
