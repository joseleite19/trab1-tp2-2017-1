#ifndef SUBJECTHPP
#define SUBJECTHPP

#include <string>
#include <vector>
#include "topic.hpp"
#include "quiz.hpp"

class Subject {
    std::string name;
    std::vector<Quiz> quizzes;
    std::vector<Topic> topics;
public:
    std::string getName() const;
    void setName(std::string new_name);
    void addTopic(Topic);
    void showTopics(int user_id) const;
    const std::vector<Topic>& getTopics() const;

    Subject(const std::string &);
    ~Subject();
};

#endif // SUBJECTHPP
