#include "quiz.hpp"

#include <queue>
#include "helper.hpp"

Quiz::Quiz(){

}

Quiz::~Quiz(){

}


std::string Quiz::getname() const{
	return name;
}

std::string Quiz::setname(std::string newname){
	return name = newname;
}
void Quiz::run(int user_id) const{
	std::vector<int> id = randompermutation(questions.size());

	std::queue<Question> q;

	for(int i = 0; i < questions.size(); i++)
		q.push(questions[ id[i] ]);

	int qnt_resp_certas = 0;

	while(!q.empty()){
		Question questao = q.front(); q.pop();

		questao.show();

		// menu: 1 = resposnder; 0 = pular; -1 = sair

		int op = readIntInRange(-1, questions.size());
		if(op == 0) q.push(questao);
		else if(op == -1){
			// msg: voce escolheu sair do quiz
			return;
		}
		else{
			char c = readchar();
			if(c == questao.getresp()) qnt_resp_certas++;
		}
	}

	// aqui a pessoa terminou de fazer o Quiz

}