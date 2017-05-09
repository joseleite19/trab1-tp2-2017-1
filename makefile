all:
	g++ -Wall -std=c++11 -Isrc src/main2.cpp src/controllers.cpp src/stubPR.cpp src/user.cpp src/subject.cpp src/topic.cpp src/quiz.cpp src/question.cpp src/helper.cpp
