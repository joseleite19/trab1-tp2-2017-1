#ifndef QUESTION
#define QUESTION

#include <string>

class Question{
	std::string text;
	char resp;
public:
	Question(const std::string&, const char);
	~Question();
	void show() const;
	char getresp() const;

	const std::string& getText() const;
};


#endif