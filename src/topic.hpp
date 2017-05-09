#ifndef USERHPP
#define USERHPP

#include "quiz.hpp"
#include <string>
#include <vector>

class Topic {
    std::string name;
    std::vector<Quiz> quizzes;
public:
    Topic();
    ~Topic();
    std::string getName() const;
    void setName(std::string new_name);
    void showQuizzes(int user_id);
};

#endif // USERHPP
