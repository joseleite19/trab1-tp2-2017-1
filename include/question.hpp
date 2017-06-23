/**
*   Classe das questoes.
*  Possui as questoes, resposta e pontuacao, vai mostrando as questoes.
*   @author joseleite19
*   @since 07/05/2017
*   @version 3.0
*/


#ifndef QUESTION
#define QUESTION

#include <string>

class Question{
	std::string text;
	char resp;
	int pontuacao;
public:
	Question(const std::string&, const char, int pontuacao);
	~Question();
	void show() const;
	char getresp() const;
	int getPontuacao() const;

	const std::string& getText() const;
};


#endif
