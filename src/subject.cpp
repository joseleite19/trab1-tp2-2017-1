#include "subject.hpp"
#include <vector>
#include <string>
#include "helper.hpp"
#include "topic.hpp"

Subject::Subject(const std::string & name) {
    this->name = name;
}

Subject::~Subject() {

}

void Subject::setName(std::string new_name) {
    this->name = new_name;
}

std::string Subject::getName() const{
    return this->name;
}

void Subject::addTopic(Topic topic) {
    this->topics.push_back(topic);
}

void Subject::showTopics(int user_id) const{
    std::vector<int> id = randompermutation(topics.size());

	for(int i:id)topics[i].showQuizzes(user_id);
}

const std::vector<Topic>& Subject::getTopics() const{
	return topics;
}
