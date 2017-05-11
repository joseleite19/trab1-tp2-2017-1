#ifndef QUIZ
#define QUIZ

#include <string>
#include <vector>
#include "question.hpp"

class Quiz{
	std::string name;
	std::vector<Question> questions;
public:
	Quiz(const std::string &);
	~Quiz();
	std::string getname() const;
	std::string setname(std::string);
    void addQuestion(Question);

	void run(int user_id) const;

    const std::vector<Question>& getQuestions() const;
};



#endif
