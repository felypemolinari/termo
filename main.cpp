/*
    ##################################
    #                                #
    #      AUTORES DO PROJETO:       #
    #                                #
    #      FELYPE CESAR MOLINARI     #
    #     VINICIUS ANDRIANI MAZERA   #
    #                                #
    ##################################
*/

#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <limits>
#include <fstream>
#include <cctype>
#include "LUE.h"

using namespace std;

bool gameLoop = true;

// Função para verificar entrada do usúario
void verificaCin()
{
    system("cls");
    cout << "Erro! Opcao invalida!\n\n";
    cout << endl;
    cout << "Pressione qualquer tecla para continuar...";
    _getch();
    system("cls");

    cin.clear();

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Função caso precise criar arquivo
bool criarArquivo(string nomeArquivo) 
{
    ofstream arquivo(nomeArquivo);
    if(!arquivo) {
        cout << "Erro ao criar o arquivo: " << nomeArquivo << endl;
        return false;
    }
    arquivo.close();
    return true;
}

// Primeiro modo de jogo
void modoDeJogo1(LUE lista)
{
    // Inicializa lista do historico de tentativas
    LUE listaHistorico;
    inicializarLUE(listaHistorico);

    int tentativa = 1;
    const int maxTentativa = 6;
    string respUsuario;
    bool palavraEncontrada = false;
    
    // Le o arquivo e seleciona uma palavra aleatória
    lerArquivoParaLista(lista, "listaPalavras.txt");
    
    string palavraAleatoria = selecionarPalavraAleatoria(lista);

    if(palavraAleatoria == "") 
    {
        cout << "A lista esta vazia, nao e possivel selecionar uma palavra aleatoria." << endl;
    }

    // While onde as tentativas irão rodar
    while (tentativa <= maxTentativa) 
    {
        bool verif = false;
        while (verif == false) 
        {
            cout << "Tentativa: " << tentativa << " de "<< maxTentativa << "\r\n";
            cout << "Digite uma palavra: ";
            cin >> respUsuario;

            // Transforma para letra maiúscula
            for (char &c : respUsuario) {
                c = toupper(static_cast<unsigned char>(c)); 
            }

            // Verifica o tamanho da entrada de dados do usuário
            if(respUsuario.size() > 5 || respUsuario.size() < 5) 
            {
                cout << "A palavra deve ter no minimo/maximo 5 caracteres. Tente novamente." << endl;
            } 
            else 
            {
                verif = true;
                inserirFinalLUE(listaHistorico, respUsuario);
            }
        }

        cout << "Letras encontradas: ";

        // Verifica se a entrada é igual a sorteada
        if(palavraEncontrada == false) 
        {
            for (int i = 0; i < respUsuario.size(); i++) 
            {
                if(i < palavraAleatoria.size() && respUsuario[i] == palavraAleatoria[i]) 
                {
                    cout << "\033[32m" << respUsuario[i] << "\033[0m";
                }
                else if(palavraAleatoria.find(respUsuario[i]) != string::npos) 
                {
                    cout << "\033[33m" << respUsuario[i] << "\033[0m";
                } 
                else 
                {
                    cout << respUsuario[i];
                }
            }
        }
        
        // Se a entrada for igual ele sai do while
        if(respUsuario == palavraAleatoria) palavraEncontrada = true;

        if(palavraEncontrada == true) break;

        cout << endl;
        tentativa++;     
    }

    // Histórico final
    cout << endl;
    if (palavraEncontrada == true)
    {
        cout << "\033[32m" << "\r\nParabens voce acertou!" << "\033[0m" << endl;
        cout << "Palavra: " << "\033[32m" << palavraAleatoria << "\033[0m" << endl;
    }
    else
    {
        cout << "\033[31m" << "\r\nVoce perdeu!" << "\033[0m" << endl;
        cout << "Palavra: " << "\033[32m" << palavraAleatoria << "\033[0m" << endl;
    }

    cout << endl;
    cout << "Historico de tentativas: ";
    mostrarLUE(listaHistorico);

    _getch();
}

// Segundo modo de jogo
void modoDeJogo2(LUE lista)
{
    // Inicializa lista do historico de tentativas
    LUE listaHistorico;
    inicializarLUE(listaHistorico);

    int tentativa = 1;
    const int maxTentativa = 8;
    string respUsuario;
    bool palavraEncontrada1 = false;
    bool palavraEncontrada2 = false;

    // Le o arquivo e seleciona duas palavras aleatórias
    lerArquivoParaLista(lista, "listaPalavras.txt");
    string palavraAleatoria1 = selecionarPalavraAleatoria(lista);
    string palavraAleatoria2 = selecionarPalavraAleatoria(lista);

    // Faz as palavras sorteadas serem diferentes
    do 
    {
        palavraAleatoria2 = selecionarPalavraAleatoria(lista);
    } while (palavraAleatoria2 == palavraAleatoria1);
    
    if (palavraAleatoria1 == "") 
    {
        cout << "A lista esta vazia, nao e possivel selecionar uma palavra aleatoria." << endl;
    } 

    // While onde as tentativas irão rodar
    while (tentativa <= maxTentativa) 
    {
        bool verif = false;
        while (verif == false) 
        {
            cout << "Tentativa: " << tentativa << " de "<< maxTentativa << "\r\n";
            cout << "Digite uma palavra: ";
            cin >> respUsuario;

            // Transforma para letra maiúscula
            for (char &c : respUsuario) {
                c = toupper(static_cast<unsigned char>(c)); // Convertendo cada caractere
            }

            // Verifica o tamanho da entrada de dados do usuário
            if(respUsuario.size() > 5 || respUsuario.size() < 5) 
            {
                cout << "A palavra deve ter no minimo/maximo 5 caracteres. Tente novamente." << endl;
            } 
            else 
            {
                verif = true;
                inserirFinalLUE(listaHistorico, respUsuario);
            }
        }

        cout << "Letras encontradas: ";
        
        // Verifica se a entrada é igual a sorteada
        if(palavraEncontrada1 == false) 
        {
            for(int i = 0; i < respUsuario.size(); i++) 
            {
                if(i < palavraAleatoria1.size() && respUsuario[i] == palavraAleatoria1[i]) 
                {
                    cout << "\033[32m" << respUsuario[i] << "\033[0m";
                } 
                else if(palavraAleatoria1.find(respUsuario[i]) != string::npos) {
                    cout << "\033[33m" << respUsuario[i] << "\033[0m";
                } 
                else
                {
                    cout << respUsuario[i];
                }
            }

            cout << "  ";
        }

        if(palavraEncontrada2 == false) 
        {
            for (int i = 0; i < respUsuario.size(); i++) 
            {
                if (i < palavraAleatoria2.size() && respUsuario[i] == palavraAleatoria2[i]) 
                {
                    cout << "\033[32m" << respUsuario[i] << "\033[0m";
                } 
                else if(palavraAleatoria2.find(respUsuario[i]) != string::npos) 
                {
                    cout << "\033[33m" << respUsuario[i] << "\033[0m";
                } 
                else 
                {
                    cout << respUsuario[i];
                }
            }
        }

        // Se a entrada for igual ele sai do while
        if(respUsuario == palavraAleatoria1) palavraEncontrada1 = true;

        if(respUsuario == palavraAleatoria2) palavraEncontrada2 = true;

        if(palavraEncontrada1 == true && palavraEncontrada2 == true) break;
         
        cout << endl;
        tentativa++;
    }

    // Histórico final
    cout << endl;
    if(palavraEncontrada1 == true && palavraEncontrada2 == true)
    {
        cout << "\033[32m" << "\r\nParabens voce acertou!" << "\033[0m" << endl;
        cout << "Palavra: " << "\033[32m" << palavraAleatoria1 << "\033[0m" << endl;
        cout << "Palavra: " << "\033[32m" << palavraAleatoria2 << "\033[0m" << endl;
    }
    else
    {
        cout << "\033[31m" << "\r\nVoce perdeu!" << "\033[0m" << endl;
        cout << "Palavra: " << "\033[32m" << palavraAleatoria1 << "\033[0m" << endl;
        cout << "Palavra: " << "\033[32m" << palavraAleatoria2 << "\033[0m" << endl;
        
    }

    cout << endl;
    cout << "Historico de tentativas: ";
    mostrarLUE(listaHistorico);

    _getch();
}

// Terceiro modo de jogo
void modoDeJogo3(LUE lista)
{
    // Inicializa lista do historico de tentativas
    LUE listaHistorico;
    inicializarLUE(listaHistorico);

    int tentativa = 1;
    const int maxTentativa = 10;
    string respUsuario;
    bool palavraEncontrada1 = false;
    bool palavraEncontrada2 = false;
    bool palavraEncontrada3 = false;

    // Le o arquivo e seleciona duas palavras aleatórias
    lerArquivoParaLista(lista, "listaPalavras.txt");
    string palavraAleatoria1, palavraAleatoria2, palavraAleatoria3;

    // Faz as palavras sorteadas serem diferentes
    do {
        palavraAleatoria1 = selecionarPalavraAleatoria(lista);
        palavraAleatoria2 = selecionarPalavraAleatoria(lista);
    } while (palavraAleatoria1 == palavraAleatoria2);

    do {
        palavraAleatoria3 = selecionarPalavraAleatoria(lista);
    } while (palavraAleatoria3 == palavraAleatoria1 || palavraAleatoria3 == palavraAleatoria2);
    
    if (palavraAleatoria1 == "") 
    {
        cout << "A lista esta vazia, nao e possivel selecionar uma palavra aleatoria." << endl;
    }

    // While onde as tentativas irão rodar
    while (tentativa <= maxTentativa) 
    {
        bool verif = false;
        while (verif == false) 
        {
            cout << "Tentativa: " << tentativa << " de "<< maxTentativa << "\r\n";
            cout << "Digite uma palavra: ";
            cin >> respUsuario;

            // Transforma para letra maiúscula
            for (char &c : respUsuario) {
                c = toupper(static_cast<unsigned char>(c)); // Convertendo cada caractere
            }

            // Verifica o tamanho da entrada de dados do usuário
            if(respUsuario.size() > 5 || respUsuario.size() < 5) 
            {
                cout << "A palavra deve ter no minimo/maximo 5 caracteres. Tente novamente." << endl;
            }
            else 
            {
                verif = true;
                inserirFinalLUE(listaHistorico, respUsuario);
            }
        }

        cout << "Letras encontradas: ";

        // Verifica se a entrada é igual a sorteada
        if (palavraEncontrada1 == false) 
        {
            for (int i = 0; i < respUsuario.size(); i++) 
            {
                if(i < palavraAleatoria1.size() && respUsuario[i] == palavraAleatoria1[i]) 
                {
                    cout << "\033[32m" << respUsuario[i] << "\033[0m";   
                } 
                else if(palavraAleatoria1.find(respUsuario[i]) != string::npos) 
                {
                    cout << "\033[33m" << respUsuario[i] << "\033[0m";
                } 
                else 
                {
                    cout << respUsuario[i];
                }
            }

            cout << "  ";
        }

        if (palavraEncontrada2 == false) 
        {
            for (int i = 0; i < respUsuario.size(); i++) 
            {
                if(i < palavraAleatoria2.size() && respUsuario[i] == palavraAleatoria2[i]) 
                {
                    cout << "\033[32m" << respUsuario[i] << "\033[0m";
                } 
                else if(palavraAleatoria2.find(respUsuario[i]) != string::npos) 
                {
                    cout << "\033[33m" << respUsuario[i] << "\033[0m";
                } else 
                {
                    cout << respUsuario[i];
                }
            }

            cout << "  ";
        }

        if (palavraEncontrada3 == false) 
        {
            for(int i = 0; i < respUsuario.size(); i++) 
            {
                if(i < palavraAleatoria3.size() && respUsuario[i] == palavraAleatoria3[i]) 
                {
                    cout << "\033[32m" << respUsuario[i] << "\033[0m";
                } 
                else if(palavraAleatoria3.find(respUsuario[i]) != string::npos) 
                {
                    cout << "\033[33m" << respUsuario[i] << "\033[0m";
                } else 
                {
                    cout << respUsuario[i];
                }
            }
        }

        // Se a entrada for igual ele sai do while
        if (respUsuario == palavraAleatoria1) palavraEncontrada1 = true;

        if (respUsuario == palavraAleatoria2) palavraEncontrada2 = true;

        if (respUsuario == palavraAleatoria3) palavraEncontrada3 = true;

        if(palavraEncontrada1 == true && palavraEncontrada2 == true && palavraEncontrada3 == true) break;
         
        cout << endl;
        tentativa++;
    }

    // Histórico final
    cout << endl;
    if(palavraEncontrada1 == true && palavraEncontrada2 == true && palavraEncontrada3 == true )
    {
        cout << "\033[32m" << "\r\nParabens voce acertou!" << "\033[0m" << endl;
        cout << "Palavra 1: " << "\033[32m" << palavraAleatoria1 << "\033[0m" << endl;
        cout << "Palavra 2: " << "\033[32m" << palavraAleatoria2 << "\033[0m" << endl;
        cout << "Palavra 3: " << "\033[32m" << palavraAleatoria3 << "\033[0m" << endl;
    }
    else
    {
        cout << "\033[31m" << "\r\nVoce perdeu!" << "\033[0m" << endl;
        cout << "Palavra 1: " << "\033[32m" << palavraAleatoria1 << "\033[0m" << endl;
        cout << "Palavra 2: " << "\033[32m" << palavraAleatoria2 << "\033[0m" << endl;
        cout << "Palavra 3: " << "\033[32m" << palavraAleatoria3 << "\033[0m" << endl;
    }

    cout << endl;
    cout << "Historico de tentativas: ";
    mostrarLUE(listaHistorico);

    _getch();
}

// Quarto modo de jogo
void modoDeJogo4(LUE lista)
{
    // Inicializa lista do historico de tentativas
    LUE listaHistorico;
    inicializarLUE(listaHistorico);

    int tentativa = 1;
    const int maxTentativa = 12;
    string respUsuario;
    bool palavraEncontrada1 = false;
    bool palavraEncontrada2 = false;
    bool palavraEncontrada3 = false;
    bool palavraEncontrada4 = false;

    // Le o arquivo e seleciona uma palavra aleatória
    lerArquivoParaLista(lista, "listaPalavras.txt");
    string palavraAleatoria1, palavraAleatoria2, palavraAleatoria3, palavraAleatoria4;

    // Faz as palavras sorteadas serem diferentes
    do {
        palavraAleatoria1 = selecionarPalavraAleatoria(lista);
        palavraAleatoria2 = selecionarPalavraAleatoria(lista);
    } while (palavraAleatoria1 == palavraAleatoria2);

    do {
        palavraAleatoria3 = selecionarPalavraAleatoria(lista);
        palavraAleatoria4 = selecionarPalavraAleatoria(lista);
    } while (palavraAleatoria3 == palavraAleatoria1 || palavraAleatoria3 == palavraAleatoria2 || 
                palavraAleatoria4 == palavraAleatoria1 || palavraAleatoria4 == palavraAleatoria2 || 
                palavraAleatoria4 == palavraAleatoria3);
    
    if(palavraAleatoria1 == "") 
    {
        cout << "A lista esta vazia, nao e possivel selecionar uma palavra aleatoria." << endl;
    }

    // While onde as tentativas irão rodar
    while (tentativa <= maxTentativa) 
    {
        bool verif = false;
        while (verif == false) 
        {
            cout << "Tentativa: " << tentativa << " de "<< maxTentativa << "\r\n";
            cout << "Digite uma palavra: ";
            cin >> respUsuario;

            // Transforma para letra maiúscula
            for (char &c : respUsuario) {
                c = toupper(static_cast<unsigned char>(c)); // Convertendo cada caractere
            }

            // Verifica o tamanho da entrada de dados do usuário
            if(respUsuario.size() > 5 || respUsuario.size() < 5) 
            {
                cout << "A palavra deve ter no minimo/maximo 5 caracteres. Tente novamente." << endl;
                verificaCin();
            } 
            else 
            {
                verif = true;
                inserirFinalLUE(listaHistorico, respUsuario);
            }
        }

        cout << "Letras encontradas: ";

        // Verifica se a entrada é igual a sorteada
        if(palavraEncontrada1 == false) 
        {
            for(int i = 0; i < respUsuario.size(); i++) 
            {
                if (i < palavraAleatoria1.size() && respUsuario[i] == palavraAleatoria1[i]) 
                {
                    cout << "\033[32m" << respUsuario[i] << "\033[0m";
                    
                } 
                else if(palavraAleatoria1.find(respUsuario[i]) != string::npos) 
                {
                    cout << "\033[33m" << respUsuario[i] << "\033[0m";
                } 
                else
                {
                    cout << respUsuario[i];
                }
            }

            cout << "  ";
        }

        if(palavraEncontrada2 == false)
        {
            for(int i = 0; i < respUsuario.size(); i++) 
            {
                if (i < palavraAleatoria2.size() && respUsuario[i] == palavraAleatoria2[i]) 
                {
                    cout << "\033[32m" << respUsuario[i] << "\033[0m";
                } 
                else if(palavraAleatoria2.find(respUsuario[i]) != string::npos) 
                {
                    cout << "\033[33m" << respUsuario[i] << "\033[0m";
                } 
                else 
                {
                    cout << respUsuario[i];
                }
            }

            cout << "  ";
        }

        if (palavraEncontrada3 == false) 
        {
            for (int i = 0; i < respUsuario.size(); i++) 
            {
                if(i < palavraAleatoria3.size() && respUsuario[i] == palavraAleatoria3[i])
                {
                    cout << "\033[32m" << respUsuario[i] << "\033[0m";
                } 
                else if(palavraAleatoria3.find(respUsuario[i]) != string::npos) 
                {
                    cout << "\033[33m" << respUsuario[i] << "\033[0m";
                } 
                else 
                {
                    cout << respUsuario[i];
                }
            }

            cout << "  ";
        }

        if (palavraEncontrada4 == false) 
        {
            for(int i = 0; i < respUsuario.size(); i++) 
            {
                if(i < palavraAleatoria4.size() && respUsuario[i] == palavraAleatoria4[i]) 
                {
                    cout << "\033[32m" << respUsuario[i] << "\033[0m";
                } 
                else if(palavraAleatoria4.find(respUsuario[i]) != string::npos) 
                {
                    cout << "\033[33m" << respUsuario[i] << "\033[0m";
                } 
                else 
                {
                    cout << respUsuario[i];
                }
            }
        }

        // Se a entrada for igual ele sai do while
        if(respUsuario == palavraAleatoria1) palavraEncontrada1 = true;

        if(respUsuario == palavraAleatoria2) palavraEncontrada2 = true;

        if(respUsuario == palavraAleatoria3) palavraEncontrada3 = true;

        if(respUsuario == palavraAleatoria4) palavraEncontrada4 = true;

        if(palavraEncontrada1 == true && palavraEncontrada2 == true && palavraEncontrada3 == true && palavraEncontrada4 == true) break;
         
        cout << endl;
        tentativa++;
    }

    // Histórico final
    cout << endl;
    if(palavraEncontrada1 == true && palavraEncontrada2 == true && palavraEncontrada3 == true && palavraEncontrada4 == true)
    {
        cout << "\033[32m" << "\r\nParabens voce acertou!" << "\033[0m" << endl;
        cout << "Palavra 1: " << "\033[32m" << palavraAleatoria1 << "\033[0m" << endl;
        cout << "Palavra 2: " << "\033[32m" << palavraAleatoria2 << "\033[0m" << endl;
        cout << "Palavra 3: " << "\033[32m" << palavraAleatoria3 << "\033[0m" << endl;
        cout << "Palavra 3: " << "\033[32m" << palavraAleatoria4 << "\033[0m" << endl;
    }
    else
    {
        cout << "\033[31m" << "\r\nVoce perdeu!" << "\033[0m" << endl;
        cout << "Palavra 1: " << "\033[32m" << palavraAleatoria1 << "\033[0m" << endl;
        cout << "Palavra 2: " << "\033[32m" << palavraAleatoria2 << "\033[0m" << endl;
        cout << "Palavra 3: " << "\033[32m" << palavraAleatoria3 << "\033[0m" << endl;
        cout << "Palavra 3: " << "\033[32m" << palavraAleatoria4 << "\033[0m" << endl;
    }

    cout << endl;
    cout << "Historico de tentativas: ";
    mostrarLUE(listaHistorico);

    _getch();
}

// Função que roda o jogo
void jogo()
{
    LUE lista;

    int opcao;
    bool opcaoValida;
    bool terminal = true;

    do
    {
        do {
            cout << "Escolha o modo de jogo: " << endl;
            cout << endl;
            cout << endl;

            cout << "1) 1 palavra de forma simultanea: " << endl;
            cout << "2) 2 palavras de forma simultanea: " << endl;
            cout << "3) 3 palavras de forma simultanea: " << endl;
            cout << "4) 4 palavras de forma simultanea: " << endl;
            cout << "5) Sair:  " << endl;
            cout << "Opcao escolhida: ";

            if (!(cin >> opcao) || cin.peek() != '\n' || (opcao != 1 && opcao != 2 && opcao != 3 && opcao != 4 && opcao != 5)) {
                verificaCin();
                opcaoValida = false;
            } else{
                opcaoValida = true;
                system("cls");
            }
        } while (!opcaoValida);
        
        // Escolhe modo de jogo
        if (opcao == 1) modoDeJogo1(lista);
        else if (opcao == 2) modoDeJogo2(lista); 
        else if (opcao == 3) modoDeJogo3(lista);
        else if (opcao == 4) modoDeJogo4(lista);
        else terminal = false;

        system("cls");
    } while (terminal == true);
}

// Função para inserir item na lista
void inserirLista(LUE lista)
{
    string respUsuario;
    bool opcaoValida;
    bool verif = false;
    
    while (verif == false) {
        cout << "Digite a palavra que deseja inserir: (lembre-se que tem que ter no minimo/maximo 5 caracteres) " << endl;
        cin >> respUsuario;

        // Transforma para letra maiúscula
        for (char &c : respUsuario) {
            c = toupper(static_cast<unsigned char>(c)); 
        }

        // Verifica o tamanho da entrada de dados do usuário
        if(respUsuario.size() > 5 || respUsuario.size() < 5) 
        {
            cout << "A palavra deve ter no minimo/maximo 5 caracteres. Tente novamente." << endl;
            verificaCin();
        } 
        else 
        {
            opcaoValida = true;
            verif = true;
            system("cls");
        }
    }

    inserirFinalLUE(lista, respUsuario);
    salvarListaEmArquivo(lista, "listaPalavras.txt");
    cout << "Palavra inserida com sucesso: " << respUsuario << endl;

    _getch();
    system("cls");
}

// Função para retirar item na lista
void retirarLista(LUE lista)
{
    string respUsuario;
    bool opcaoValida;
    bool verif = false;
    while (verif == false) 
    {
        cout << "Digite a palavra que deseja retirar: (lembre-se que tem que ter no minimo/maximo 5 caracteres) " << endl;
        cin >> respUsuario;

        // Transforma para letra maiúscula
        for (char &c : respUsuario) {
            c = toupper(static_cast<unsigned char>(c)); 
        }

        // Verifica o tamanho da entrada de dados do usuário
        if (respUsuario.size() > 5 || respUsuario.size() < 5) 
        {
            cout << "A palavra deve ter no minimo/maximo 5 caracteres. Tente novamente." << endl;
            verificaCin();
        } 
        else 
        {
            opcaoValida = true;
            verif = true;
            system("cls");
        }
    }

    if (lerArquivoParaLista(lista, "listaPalavras.txt")) 
    {
        cout << "Arquivo lido e lista preenchida com sucesso!" << endl;
    } else {
        cout << "Falha ao ler o arquivo ou inserir valores na lista." << endl;
    }

    if (removerPalavraLUE(lista, respUsuario)) {
        cout << "Palavra removida e lista atualizada com sucesso!" << endl;
    } else {
        cout << "Falha ao remover a palavra." << endl;
    }

    salvarListaEmArquivoRetirar(lista, "listaPalavras.txt");

    _getch();
    system("cls");
}

// Função que roda o inserir e retirar
void inserirERetirarPalavras()
{
    LUE lista;

    int opcao;
    bool opcaoValida;
    bool terminal = true;

    do
    {
        do {
            cout << "1) Inserir: " << endl;
            cout << "2) Retirar: " << endl;
            cout << "3) Sair: " << endl << endl;
            cout << "Opcao escolhida: ";

            if (!(cin >> opcao) || cin.peek() != '\n' || (opcao != 1 && opcao != 2 && opcao != 3)) {
                verificaCin();
                opcaoValida = false;
            } else{
                opcaoValida = true;
                system("cls");
            }
        } while (!opcaoValida);

        if (opcao == 1) inserirLista(lista);
        else if(opcao == 2) retirarLista(lista);
        else terminal = false;

    } while (terminal == true);
}

void comoJogar()
{
    system("cls");
    int opcao;  
    bool opcaoValida;
    bool terminal = true;

    do {
        do {
            cout << "O termo consiste em um jogo onde voce tem que achar a palavra correta de 5 letras que foi sorteada, a partir disso voce vai ter uma quantidade de chances para acertar." << endl;
            cout << "A cor" << "\033[32m" << " verde " << "\033[0m" << "significa que voce acertou a letra e o lugar onde ela esta, a cor" << "\033[33m" << " amarela " << "\033[0m" << "significa que exite essa letra na palavra mas nao e neste local, e se nao aparecer nenhuma dessas cores, significa que a letra nao existe na palavra." << endl;
            cout << endl;
            cout << "1) Sair: ";
            if (!(cin >> opcao) || cin.peek() != '\n' || (opcao != 1)) {
                verificaCin();
                opcaoValida = false;
            } else{
                opcaoValida = true;
                system("cls");
            }
        } while (!opcaoValida);

        if (opcao == 1) terminal = false;
             
    } while (terminal == true);
}

// Função que roda o jogo
void run()
{
    system("cls");
    int opcao;
    bool opcaoValida;

    do {
        do {
            cout << "Seja bem-vindo(a) ao: " << endl;
            cout << "\033[33m" << " _                              " << "\033[0m" << endl;
            cout << "\033[33m" << "| |_    ___   _ __   _ __ ___     ___" << "\033[0m" << endl;
            cout << "\033[33m" << "| __|  / _ \\ | '__| | '_ ` _ \\   / _ \\" << "\033[0m" << endl;
            cout << "\033[33m" << "| |_  |  __/ | |    | | | | | | | (_) |" << "\033[0m" << endl;
            cout << "\033[33m" << " \\__|  \\___| |_|    |_| |_| |_|  \\___/ " << "\033[0m" << endl;

            cout << endl;
            cout << endl;
            cout << "1) Jogar: " << endl;
            cout << "2) Incluir/Remover palavras: " << endl;
            cout << "3) Como jogar: " << endl;
            cout << "4) Sair: " << endl << endl;
            cout << "Opcao escolhida: ";

            if (!(cin >> opcao) || cin.peek() != '\n' || (opcao != 1 && opcao != 2 && opcao != 3 && opcao != 4)) {
                verificaCin();
                opcaoValida = false;
            } else{
                opcaoValida = true;
                system("cls");
            }
        } while (!opcaoValida);

        if (opcao == 1) jogo();
        else if(opcao == 2) inserirERetirarPalavras();
        else if(opcao == 3) comoJogar();
        else if(opcao == 4) gameLoop = false;
             
    } while (gameLoop != false);
}

int main()
{   
    run();
    return 0;
}