/**
* Responsavel por adicionar novos topicos e mostrar topicos existentes de uma disciplina.
*   @author AngelicCoder
*   @since 08/05/2017
*   @version 2.0
*/


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

    /**
    *   Adiciona novo topico na disciplina.
    *   @param Um vetor Topic contendo os topicos.
    *   @return Retorno vazio.
    */
    void addTopic(Topic);

    void showTopics(int user_id) const;
    const std::vector<Topic>& getTopics() const;

    Subject(const std::string &);
    ~Subject();
};

#endif // SUBJECTHPP
