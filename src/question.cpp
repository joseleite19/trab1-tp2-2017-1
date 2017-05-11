#include "question.hpp"

Question::Question(const std::string& text, const char resp): text(text), resp(resp) {}

Question::~Question(){

}

void Question::show() const{
	printf("%s\n", this->text.c_str());
}

char Question::getresp() const{
	return resp;
}

const std::string& Question::getText() const{
	return text;
}
