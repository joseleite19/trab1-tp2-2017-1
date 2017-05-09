#include "subject.hpp"
#include <queue>
#include "helper.hpp"

Subject::Subject() {

}

Subject::~Subject() {

}

void Subject::setName(std::string new_name) {
    this->name = new_name;
}

std::string Subject::getName() {
    return this->name;
}

void Subject::showTopics(int user_id) {
    std::vector<int> id = randompermutation(topics.size());
	std::queue<Topic> t;

	for(int i = 0; i < topics.size(); i++)
		t.push(topics[ id[i] ]);
    while(!t.empty()){
		Topic topic = t.front(); t.pop();

		topic.showQuizzes(user_id);
    }
}
