#include "LUE.h"
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;


void inicializarLUE(LUE &lista) {
    lista.comeco = NULL;
    lista.fim = NULL;
}

bool inserirFinalLUE(LUE &lista, string valor) {
    No *novo = new No;

    if (novo == NULL) return false;

    novo->info = valor;
    novo->elo = NULL;

    if (lista.comeco == NULL) {
        lista.comeco = novo;
        lista.fim = novo;
    } else {
        lista.fim->elo = novo;
        lista.fim = novo;
    }

    return true;
}

void mostrarLUE(LUE &lista) {
    No *aux = lista.comeco;

    while (aux != NULL) {
        cout << "\r\n";
        cout << aux->info << " ";
        aux = aux->elo;
    }
}

bool lerArquivoParaLista(LUE &lista, string nomeArquivo) {
    ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo: " << nomeArquivo << endl;
        return false;
    }

    string linha;
    while (getline(arquivo, linha)) {
        if (!inserirFinalLUE(lista, linha)) {
            cout << "Erro ao inserir valor na lista: " << linha << endl;
            return false;
        }
    }
    arquivo.close();
    return true;
}

string selecionarPalavraAleatoria(LUE &lista) {
    No *atual = lista.comeco;

    if (lista.comeco == NULL) return "";

    int cont = 0;
    while (atual != NULL) {
        cont++;
        atual = atual->elo;
    }

    srand(time(nullptr));
    int indiceAleatorio = rand() % cont;

    atual = lista.comeco;
    for (int i = 0; i < indiceAleatorio; i++) {
        atual = atual->elo;
    }

    return atual->info;
}

void salvarListaEmArquivo(LUE &lista, string nomeArquivo) {
    ofstream arquivo(nomeArquivo, ios::app);
    if (arquivo.is_open()) {
        No *atual = lista.comeco;
        while (atual != NULL) {
            arquivo << atual->info << endl;
            atual = atual->elo;
        }
        arquivo.close();
    } else {
        cout << "Nao foi possovel abrir o arquivo para escrita." << endl;
    }
}

void salvarListaEmArquivoRetirar(LUE lista, string nomeArquivo) {
    ofstream arquivo(nomeArquivo, ios::trunc);
    if (arquivo.is_open()) {
        No *atual = lista.comeco;
        while (atual != NULL) {
            arquivo << atual->info << endl;
            atual = atual->elo;
        }
        arquivo.close();
    } else {
        cout << "Nao foi possovel abrir o arquivo para escrita." << endl;
    }
}

bool removerPalavraLUE(LUE &lista, string valor) {
    No *atual = lista.comeco;
    No *anterior = NULL;

    while (atual != NULL && atual->info != valor) {
        anterior = atual;
        atual = atual->elo;
    }

    if (atual == NULL) {
        return false;
    }

    if (anterior == NULL) {
        lista.comeco = atual->elo;
    } else {
        anterior->elo = atual->elo;
    }

    if (atual == lista.fim) {
        lista.fim = anterior;
    }

    delete atual;
    return true;
}