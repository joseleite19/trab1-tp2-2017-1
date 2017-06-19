#include "question.hpp"

Question::Question(const std::string& text, const char resp, int pontuacao): text(text), resp(resp), pontuacao(pontuacao) {

}

Question::~Question(){

}

void Question::show() const{
	printf("%s\n", this->text.c_str());
}

char Question::getresp() const{
	return resp;
}

int Question::getPontuacao() const {
    return pontuacao;
}

const std::string& Question::getText() const{
	return text;
}
