/**
*   Classe dos quizzes.
*   Mostra as questoes de cada quiz para o usuario responder, alem de poder adicionar novas questoes.
*   @author joseleite19
*   @since 07/05/2017
*   @version 3.0
*/


#ifndef QUIZ
#define QUIZ

#include <string>
#include <vector>
#include "question.hpp"

class Quiz{
	std::string name;
	std::vector<Question> questions;
public:
    /**
    *   Construtor.
    *   Recebe um nome n como parametro e cria um novo quizz com o nome n.
    */
	Quiz(const std::string &);

	~Quiz();
	std::string getname() const;
	std::string setname(std::string);
    void addQuestion(Question);

    /**
    *   Ira mostrar as perguntas e ler as respostas do usuario.
    *   Será verificado se a resposta esta conforme esperado (V ou F) e sera atribuido a pontuacao apos a solucao das questoes.
    *   @param um inteiro que representa o id do usuário.
    *   @see questions.getresp()
    *   @see questions.getPontuacao()
    *   @see questions.show()
    *   @return retorna nada.
    */
	void run(int user_id) const;

    const std::vector<Question>& getQuestions() const;
};



#endif
