#ifndef LUE_H
#define LUE_H

#include <iostream>

using namespace std;

struct No {
    string info;
    No *elo;
};

struct LUE {
    No *comeco = NULL;
    No *fim = NULL;
};

// Inicializar lista
void inicializarLUE(LUE &lista);

// Inserir no final
bool inserirFinalLUE(LUE &lista, string valor);

// Mostrar lista
void mostrarLUE(LUE &lista);

// Ler arquivo para a lista
bool lerArquivoParaLista(LUE &lista, string nomeArquivo);

// Selecionar uma palavra aleatória
string selecionarPalavraAleatoria(LUE &lista);

// Salvar a lista em um arquivo
void salvarListaEmArquivo(LUE &lista, string nomeArquivo);

// Salvar a lista em um arquivo na hora de retirar
void salvarListaEmArquivoRetirar(LUE lista, string nomeArquivo);

// Remover uma palavra da lista
bool removerPalavraLUE(LUE &lista, string valor);

#endif //LUE_H