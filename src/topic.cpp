#include "topic.hpp"
#include <queue>
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

void Topic::showQuizzes(int user_id) {
    std::vector<int> id = randompermutation(quizzes.size());
	std::queue<Quiz> qz;

	for(uint i = 0; i < quizzes.size(); i++)
		qz.push(quizzes[ id[i] ]);
    while(!qz.empty()){
		Quiz quizz = qz.front(); qz.pop();

		quizz.run(user_id);
    }
}
