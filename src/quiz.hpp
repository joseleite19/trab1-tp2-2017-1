#ifndef QUIZ
#define QUIZ

#include <string>
#include <vector>
#include "question.hpp"

class Quiz{
	std::string name;
	std::vector<Question> questions;
	std::vector<int> answers;

public:
	Quiz();
	~Quiz();
	std::string getname() const;
	std::string setname(std::string);

	void run(int user_id) const;
};



#endif