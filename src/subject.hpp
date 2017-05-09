#ifndef SUBJECTHPP
#define SUBJECTHPP

#include "topic.hpp"
#include <string>
#include <vector>

class Subject {
    std::string name;
    std::vector<Quiz> quizzes;
    std::vector<Topic> topics;
public:
    std::string getName();
    void setName(std::string new_name);
    void showTopics(int user_id);
    Subject();
    ~Subject();
};

#endif // SUBJECTHPP
