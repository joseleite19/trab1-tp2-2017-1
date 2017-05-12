#include "user.hpp"
#include "stubPR.hpp"
#include "subject.hpp"
#include <vector>
#include <fstream>
#include <sstream>

StubPR::StubPR() {
	loadSubjects();
	loadUsers();
}

StubPR::~StubPR() {
	saveSubjects();
	saveUsers();

	for(auto &user:users)delete user.second;
	users.clear();
	for(auto &subj:subjects)delete subj.second;
	users.clear();
}


void StubPR::loadUsers(const string fileName){
	std::ifstream file;
	std::string line,name,login,pw,subject;
	User* user;
	int admin;
	int countSubj;
	file.open(fileName);
	if(file.is_open()){
		while(std::getline(file,line) && !line.empty()){
			std::stringstream lineStream(line);

			std::getline(lineStream,name,'\\');
			std::getline(lineStream,login,'\\');
			std::getline(lineStream,pw,'\\');
			lineStream >> admin;
			lineStream.ignore(256,'\\');
			lineStream >> countSubj;
			lineStream.ignore(256,'\\');

			user=new User(name,login,pw,admin);
			users[login]=user;

			for(int i=0;i<countSubj;i++){
				std::getline(lineStream,subject,'\\');
				if(subjects.count(subject)==0)printf("Erro encontrado em '%s': usuario '%s' tem matéria não existente '%s'\n",fileName.c_str(),name.c_str(),subject.c_str());
				else user->includeSubject(*subjects[subject]);
			}
		}
		file.close();
	}
	else{
		printf("Erro ao ler arquivo '%s'\n",fileName.c_str());
	}
}
void StubPR::saveUsers(string fileName){
	ofstream file(fileName);
	if(!file.is_open()){
		printf("Erro ao abrir arquivo %s\n",fileName.c_str());
		return;
	}
	for(auto it:users){
		User* user=it.second;
		file << user->getName() << "\\";
		file << user->getLogin() << "\\";
		file << user->getPassword() << "\\";
		file << user->isAdmin() << "\\";

		std::vector<Subject>& subs=user->getSubjects();
		file << subs.size() << "\\";
		for(uint i=0;i<subs.size();i++)file << subs[i].getName() << "\\";

		file << "\n";
	}
	file.close();
}

void StubPR::loadSubjects(string fileName){
	std::ifstream file;
	std::string line,name;
	int countTopics,countQuiz,countQuestions,isTrue;
	Subject *subject;
	Topic *topic;
	Quiz *quiz;
	Question *question;
	file.open(fileName);
	if(file.is_open()){
		while(std::getline(file,line) && !line.empty()){
			std::stringstream lineStream(line);

			std::getline(lineStream,name,'\\');
			lineStream >> countTopics;
			lineStream.ignore(256,'\\');
			subject=new Subject(name);
			subjects[name]=subject;
			
			for(int i=0;i<countTopics;i++){
				std::getline(file,line);
				lineStream.str(line);

				std::getline(lineStream,name,'\\');
				lineStream >> countQuiz;
				lineStream.ignore(256,'\\');
				topic=new Topic(name);

				for(int i=0;i<countQuiz;i++){
					std::getline(file,line);
					lineStream.str(line);

					std::getline(lineStream,name,'\\');
					lineStream >> countQuestions;
					lineStream.ignore(256,'\\');
					quiz=new Quiz(name);

					for(int i=0;i<countQuestions;i++){
						std::getline(file,line);
						lineStream.str(line);

						std::getline(lineStream,name,'\\');
						lineStream >> isTrue;
						lineStream.ignore(256,'\\');

						question=new Question(name,isTrue);
						quiz->addQuestion(*question);
						delete question;

					}
					topic->addQuiz(*quiz);
					delete quiz;
				}
				subject->addTopic(*topic);
				delete topic;
			}
		}
		file.close();
	}
	else{
		printf("Erro ao ler arquivo '%s'\n",fileName.c_str());
	}
}
void StubPR::saveSubjects(string fileName){
	ofstream file(fileName);
	if(!file.is_open()){
		printf("Erro ao abrir arquivo %s\n",fileName.c_str());
		return;
	}
	for(auto it:subjects){
		Subject* sub=it.second;
		file << sub->getName() << "\\";
		const std::vector<Topic>& topics=sub->getTopics();
		file << topics.size() << "\\";
		file << std::endl;

		for(const Topic &topic:topics){
			file << topic.getName() << "\\";
			const std::vector<Quiz>& quizes=topic.getQuizes();
			file << quizes.size() << "\\";
			file << std::endl;

			for(const Quiz &quiz:quizes){
				file << quiz.getname() << "\\";
				const std::vector<Question>& questions=quiz.getQuestions();
				file << questions.size() << "\\";
				file << std::endl;

				for(const Question &question:questions){
					file << question.getText() << "\\";
					file << (int)question.getresp() << "\\";
					file << std::endl;
				}
			}
		}
	}
	file.close();
}


User * StubPR::retrieveUser(const string & login) {
	if(users.count(login))return users[login];
	return nullptr;
}

void StubPR::storeName(User * user, const string & name) {
	user->setName(name);
}

void StubPR::storePass(User * user, const string & pass) {
	user->setPassword(user->getPassword(), pass);
}

std::map<std::string,Subject*>& StubPR::getSubjectsBank() {
	return subjects;
}

void StubPR::storeSubject(User * user, const string & name) {
	user->includeSubject(name);
}

void StubPR::deleteSubject(User * user, const string & name) {
	user->removeSubject(name);
}

/// ADMIN

bool StubPR::storeUserData(User * user) {
	if(users.count(user->getLogin()))return false;
	users[user->getLogin()]=user;
	return true;
}

std::map<std::string,User*>& StubPR::getUserBank() {
	return users;
}

void StubPR::deleteUser(User * user) {
	if(users.count(user->getLogin()))users.erase(user->getLogin());
}

void StubPR::storeSubjectDB(Subject * sub) {}
