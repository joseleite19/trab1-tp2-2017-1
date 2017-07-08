/**
*   Topic eh a classe dos topicos de cada disciplina.
*   Mostra os topicos relacionados a cada quizz, alem de poder adicionar novo quiz e mudar nome de um topico de uma disciplina.
*   @author AngelicCoder
*   @since 08/05/2017
*   @version 2.0
*/


#ifndef USERHPP
#define USERHPP

#include "quiz.hpp"
#include <string>
#include <vector>

class Topic {
    std::string name;
    std::vector<Quiz> quizzes;
public:
    /**
    *   Construtor, cria um novo topico com o nome n.
    *   @param  uma string que sera o nome do topico.
    */
    Topic(const std::string &);

    ~Topic();
    std::string getName() const;

    /**
    *   Funcao que coloca novo nome pra determinado topico.
    *   @param uma string que representa o nome.
    *   @return vazio.
    */
    void setName(std::string new_name);

    void addQuiz(Quiz);

    /**
    *   Funcao que mostra todos os quizzes relacionados a determinado topico/disciplina.
    *   @param um inteiro que representa o id do usuario.
    *   @see quiz.run()
    *   @return vazio.
    */
    void showQuizzes(int user_id);

    const std::vector<Quiz>& getQuizes() const;
};

#endif // USERHPP
