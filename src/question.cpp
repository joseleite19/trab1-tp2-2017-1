#include "question.hpp"

Question::Question(const std::string& text, const char resp): text(text), resp(resp) {}

Question::~Question(){

}

void Question::show() const{
	//printa text
}

char Question::getresp() const{
	return resp;
}