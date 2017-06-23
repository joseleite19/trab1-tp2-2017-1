/**
*   Arquivo contendo funcoes que servem de auxilio para topic.cpp, subject.cpp, user.cpp, helper.cpp, controllers.cpp
*   @author joseleite19
*   @since 07/05/2017
*   @version 3.0
*/

#ifndef HELPER
#define HELPER

#include <vector>
#include <queue>

std::vector<int> randompermutation(int size);
std::queue<int> randompermutationQ(int size);
/**
*   Fun��o para verificar se um inteiro lido do teclado est� em um range (intervalo) v�lido.
*   Ser� lido do teclado o inteiro e depois vamos continuar lendo at� que o inteiro esteja no range v�lido.
*   @param um inteiro L e R que representa o range.
*   @return um inteiro.
*/
int readIntInRange(int, int);

/**
*   Fun�ao que le um caractere ret do teclado enquanto o caractere ret lido n�o � alfanumerico.
*   @param n�o h�.
*   @see isAlphaNumerical()
*   @return o caractere ret.
*/
char readchar();

/**
*   Fun��o para verificar se um caractere lido do teclado � alfanum�rico, usando a tabela ASCII.
*   @param um char.
*   @return um booleano indicando se o caractere � alfanum�rico ou n�o.
*/
bool isAlphaNumerical(char);

#endif
