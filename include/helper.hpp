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
*   Função para verificar se um inteiro lido do teclado está em um range (intervalo) válido.
*   Será lido do teclado o inteiro e depois vamos continuar lendo até que o inteiro esteja no range válido.
*   @param um inteiro L e R que representa o range.
*   @return um inteiro.
*/
int readIntInRange(int, int);

/**
*   Funçao que le um caractere ret do teclado enquanto o caractere ret lido não é alfanumerico.
*   @param não há.
*   @see isAlphaNumerical()
*   @return o caractere ret.
*/
char readchar();

/**
*   Função para verificar se um caractere lido do teclado é alfanumérico, usando a tabela ASCII.
*   @param um char.
*   @return um booleano indicando se o caractere é alfanumérico ou não.
*/
bool isAlphaNumerical(char);

#endif
