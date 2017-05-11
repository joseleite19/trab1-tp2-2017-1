#ifndef USERHPP
#define USERHPP

#include "quiz.hpp"
#include <string>
#include <vector>

class Topic {
    std::string name;
    std::vector<Quiz> quizzes;
public:
    Topic(const std::string &);
    ~Topic();
    std::string getName() const;
    void setName(std::string new_name);
    void addQuiz(Quiz);
    void showQuizzes(int user_id) const;
    const std::vector<Quiz>& getQuizes() const;
};

#endif // USERHPP
