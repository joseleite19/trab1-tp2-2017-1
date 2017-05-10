#include "subject.hpp"
#include <queue>
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

std::string Subject::getName() {
    return this->name;
}

void Subject::addTopic(Topic topic) {
    this->topics.push_back(topic);
}

void Subject::showTopics(int user_id) {
    std::vector<int> id = randompermutation(topics.size());
	std::queue<Topic> t;

	for(uint i = 0; i < topics.size(); i++)
		t.push(topics[ id[i] ]);
    while(!t.empty()){
		Topic topic = t.front(); t.pop();

		topic.showQuizzes(user_id);
    }
}
