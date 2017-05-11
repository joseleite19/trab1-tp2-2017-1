#include "quiz.hpp"

#include <vector>
#include "helper.hpp"

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

void Quiz::run(int user_id) const{
	std::queue<int> id = randompermutationQ(questions.size());

	int qnt_resp_certas = 0;

	for(int i=id.front();!id.empty();id.pop()){
		questions[i].show();

		// menu: 1 = responder; 0 = pular; -1 = sair

		int op = readIntInRange(-1, 1);
		if(op == 0) id.push(i);
		else if(op == -1){
			// msg: voce escolheu sair do quiz
			return;
		}
		else{
			char c = readchar();
			if(c == questions[i].getresp()) qnt_resp_certas++;
		}
	}

	// aqui a pessoa terminou de fazer o Quiz

}

const std::vector<Question>& Quiz::getQuestions() const{
	return questions;
}
