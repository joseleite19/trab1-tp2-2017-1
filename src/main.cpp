/*

Universidade de Brasilia - UnB
Instituto de Ciencias Exatas - IE
Departamento de Ciencia da Computacao - CIC
Disciplina: Tecnicas de Programacao 2
Turma: A
Professor: Genaina Nunes Rodrigues
Alunos: Raphael Soares, Cristiano Krug, José Leite, Camila Pontes (15/0156120)

Trabalho 1 - Implementacao do programa QuizTime conforme especificacoes
disponibilizadas no moodle da disciplina.

Descricao: O QuizTime é um programa que permite ao usuario estudar diferentes
topicos de diversas disciplinas respondendo a quizzes. Durante o desenvolvimento do
trabalho, o grupo buscou aplicar os conceitos de programacao sistematica vistos em
sala de aula.

*/

#include "controllers.hpp"

int main() {
    ControllerInit controllerInit;
    controllerInit.initialize();
    controllerInit.showUI();
    return 0;
}
