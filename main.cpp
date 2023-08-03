/*
 * Trabalho de AEDS - Editor de Imagem PGM P2
 * 
 * Aluno: Maicon Almeida Mian
 * RA: 2023.1.08.013
 * Professor: Paulo Alexandre Bressan 
 * Data: 20/07/2023
 */

#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

typedef int img[1000][1000]; // cria uma matriz 1000x1000 quando é chamada
string erro; // armazena a mensagem de erro

/*
 Abre a imagem com o nome solicitado
 @param nome contém o nome da imagem a ser aberta
 @param entrada armazena os valores da matriz da imagem
 @param linha guarda a quantidade de linhas da imagem
 @param coluna guarda a quantidade de colunas da imagem
 @param escala guarda o valor máximo do tom da imagem
 
 @return retorna 1 e 2 para erros e 0 sem erros
 */
int AbrirImagem(string nome, img entrada, int *linha, int *coluna, int *escala) {
    string tipo; //variável que guarda o tipo da imagem
    //abre a imagem com o nome solicitado
    ifstream imagem(nome);
    //confere se a imagem existe
    if (!imagem.is_open()) {
        erro = "   Erro: O nome do arquivo não corresponde a nenhuma imagem.";
        return 1;
    }
    //guarda as informações da imagem
    imagem >> tipo >> *coluna >> *linha >> *escala;
    //confere se a imagem está no formato certo
    if (tipo != "P2") {
        erro = "   Erro: A imagem escolhida não contém o formato PGM em P2";
        return 2;
    }
    //guarda a imagem em uma matriz
    for (int i = 0; i < *linha; i++) {
        for (int j = 0; j < *coluna; j++) {
            imagem >> entrada[i][j];
        }
    }
    imagem.close();
    return 0;
}

/*
 Salva a imagem de saida
 @param nome_saida contém o nome da nova imagem
 @param saida guarda a matriz da imagem
 @param linha guarda a quantidade de linhas da imagem
 @param coluna guarda a quantidade de colunas da imagem
 @param escala guarda o valor máximo do tom da imagem
 
 @return retorna 1 para erro e 0 sem erro
 */
int ImagemSaida(string nome_saida, img saida, int *linha, int *coluna, int *escala) {
    //cria imagem com o nome solicitado
    ofstream imagem_saida(nome_saida);
    //confere se não houve erros na criação
    if (!imagem_saida.is_open()) {
        erro = "Erro: Não foi possível criar ou substituir a imagem de saída.";
        return 1;
    }
    //guarda no arquivo as informações da imagem
    imagem_saida << "P2" << endl << *coluna << " " << *linha << endl << *escala << endl;
    //pega a matriz da imagem e joga no arquivo
    for (int i = 0; i < *linha; i++) {
        for (int j = 0; j < *coluna; j++) {
            imagem_saida << saida[i][j] << " ";
        }
        imagem_saida << endl;
    }
    imagem_saida.close();
    return 0;
}

/*
 Escurece a imagem 
 @param entrada contém a  matriz de entrada
 @param saida guarda a matriz alterada da imagem
 @param linha guarda a quantidade de linhas da imagem
 @param coluna guarda a quantidade de colunas da imagem
 @param guarda qual a porcentagem do escurecimento
 @param escala guarda o valor máximo do tom da imagem
 */
void Escurecer(img entrada, img saida, int *linha, int *coluna, int *opcao, int *escala) {
    //escurece cada pixel da imagem com o valor solicitado
    for (int i = 0; i < *linha; i++) {
        for (int j = 0; j < *coluna; j++) {
            saida[i][j] = entrada[i][j] - *opcao;
            if (saida[i][j] <= 0) {
                saida[i][j] = 0;
            }
        }
    }

}

/*
 Clareia a imagem 
 @param entrada contém a  matriz de entrada
 @param saida guarda a matriz alterada da imagem
 @param linha guarda a quantidade de linhas da imagem
 @param coluna guarda a quantidade de colunas da imagem
 @param guarda qual a porcentagem do clareamento
 @param escala guarda o valor máximo do tom da imagem
 */
void Clarear(img entrada, img saida, int *linha, int *coluna, int *opcao, int *escala) {
    //passa pela matriz imagem clareando cada pixel
    for (int i = 0; i < *linha; i++) {
        for (int j = 0; j < *coluna; j++) {
            saida[i][j] = entrada[i][j] + *opcao;

            if (saida[i][j] >= *escala) {
                saida[i][j] = *escala;
            }
        }
    }

}

/*
 Gira a imagem á direita
 @param entrada contém a  matriz de entrada
 @param saida guarda a matriz alterada da imagem
 @param linha guarda a quantidade de linhas da imagem
 @param coluna guarda a quantidade de colunas da imagem
 */
void GirarDireita(img entrada, img saida, int *linha, int *coluna) {
    //percorre a matriz girando-a a direita
    for (int i = 0; i < *coluna; i++) {
        for (int k = 0, j = *linha; k < *linha; k++, j--) {
            saida[i][k] = entrada[j][i];
        }
    }
}

/*
 Gira a imagem à esquerda
 @param entrada contém a  matriz de entrada
 @param saida guarda a matriz alterada da imagem
 @param linha guarda a quantidade de linhas da imagem
 @param coluna guarda a quantidade de colunas da imagem
 */
void GirarEsquerda(img entrada, img saida, int *linha, int *coluna) {
    //passa por toda matriz, girando-a a esquerda
    for (int i = 0, j = *coluna; j >= 0; i++, j--) {
        for (int k = 0; k < *linha; k++) {
            saida[i][k] = entrada[k][j];
        }
    }
}

/*
 Binariza a imagem por um valor solicitado
 @param entrada contém a  matriz de entrada
 @param saida guarda a matriz alterada da imagem
 @param linha guarda a quantidade de linhas da imagem
 @param coluna guarda a quantidade de colunas da imagem
 @param opcao contém o fator de binarização
 @param escala guarda o valor máximo de tom da imagem
 */
void Binarizar(img entrada, img saida, int *linha, int *coluna, int *opcao, int *escala) {
    //percorre toda imagem binarizando pelo valor solicitado
    for (int i = 0; i < *linha; i++) {
        for (int j = 0; j < *coluna; j++) {
            if (entrada[i][j] >= *opcao) {
                saida[i][j] = *escala;
            } else {
                saida[i][j] = 0;
            }
        }
    }
}

/*
 Transforma a imagem em um ícone 64x64
 @param entrada contém a  matriz de entrada
 @param saida guarda a matriz alterada da imagem
 @param linha guarda a quantidade de linhas da imagem
 @param coluna guarda a quantidade de colunas da imagem
 */
void Iconizar(img entrada, img saida, int *linha, int *coluna) {
    /*
     fator_linha guarda a quantidade de linhas que se tornarão apenas uma
     fator_coluna guarda a quantidade de colunas que se tornarão apenas uma
     media guarda o valor da soma dos pixels 
     */
    int fator_linha = (*linha) / 64, fator_coluna = (*coluna) / 64, media;
    //confere se o fator e linha não é menor que um (imagem pequena)
    if (fator_linha < 1) {
        fator_linha = 1;
    }
    if (fator_coluna < 1) {
        fator_coluna = 1;
    }
    //percorre toda imagem transformando-a em um ícone
    for (int i = 0; i < *linha; i = i + fator_linha) {
        for (int j = 0; j < *coluna; j = j + fator_coluna) {
            media = 0;
            for (int k = i; k < i + fator_linha; k++) {
                for (int l = j; l < j + fator_coluna; l++) {
                    media = media + entrada[k][l];
                }
            }
            media = media / (fator_linha * fator_coluna);
            saida[i / fator_linha][j / fator_coluna] = media;
        }
    }
}

/*
 Adiciona o Filtro Passa Baixa á imagem
 @param entrada contém a  matriz de entrada
 @param saida guarda a matriz alterada da imagem
 @param linha guarda a quantidade de linhas da imagem
 @param coluna guarda a quantidade de colunas da imagem
 */
void FiltroPassaBaixa(img entrada, img saida, int *linha, int *coluna) {
    int soma = 0; // variável que guardará a soma dos pixels
    // percorre a matriz fazendo a média do pixel e dos seus vizinhos
    for (int i = 1; i < *linha - 1; i++) {
        for (int j = 1; j < *coluna - 1; j++) {
            soma = 0;
            for (int k = i - 1; k <= i + 1; k++) {
                for (int l = j - 1; l <= j + 1; l++) {
                    soma =  soma + entrada[k][l];
                }
            }
            saida[i][j] = soma / 9;
        }
    }
    // trata as bordas da imagem
    for (int i = 0; i < *coluna; i++) {
        saida[0][i] = entrada[0][i];
        saida[*linha - 1][i] = entrada[*linha - 1][i];
    }
    for (int j = 0; j < *linha; j++) {
        saida[j][0] = entrada[j][0];
        saida[j][*coluna - 1] = entrada[j][*coluna - 1];
    }

}

int main() {

    img entrada, //matriz que guarda a imagem de entrada
            saida; // matriz que guarda a imagem de saida
    string nome, // variável que guarda o nome da imagem que será aberta
            nome_saida; // variável que guarda o nome da imagem que será criada
    int linha, // variável que guarda o número de linhas da imagem de entrada 
            coluna, //variaável que guarda o número de colunas da imagem de entrada
            escala, //variável que guarda a escala máxima de tom da imagem
            opcao, //variável que armazena a opção selecionada
            continua, // variável que armazena se o usuário vai continuar editando
            linha_saida, // variável que guarda a quant. de linhas da saída
            coluna_saida; // variável que guarda a quant. de colunas da saída

    //continua iniciando com 1 
    continua = 1;

    //imprime o cabeçalho
    cout << endl << "\e[1m" << "      Trabalho de AEDS - Editor de Imagens"
            << "\e[0m" << endl;
    cout << "   Por : Maicon Almeida Mian | RA : 2023.1.08.013 " << endl;
    cout << "   Professor: Paulo Alexandre Bressan" << endl << endl;
    //pede e guarda o nome da imagem que será editada
    cout << "   Digite o nome da imagem que deseja editar: ";
    cin >> nome;
    nome = nome + ".pgm";

    //confere se ocorreu tudo certo ao abrir a imagem
    if (AbrirImagem(nome, entrada, &linha, &coluna, &escala) != 0) {
        cout << erro << endl;
        return 1;
    }

    //imprime o menu de opções e guarda a opção solicitada
    cout << endl << "       =====================" << "\e[1m" <<
            "     Edições Disponíveis: " << "\e[0m" << endl <<
            "       ||   _       ^     || " << endl <<
            "       ||  | |    ^       || " << "    1. Escurecer Imagem" << endl <<
            "       ||   -     /\\      || " << "    2. Clarear Imagem" << endl <<
            "       ||    /\\  /  \\     || " << "    3. Rotacionar 90° à direita" << endl <<
            "       ||   /  \\/    \\    ||" << "     4. Rotacionar 90° à esquerda" << endl <<
            "       ||  /    \\     \\   || " << "    5. Binarizar imagem" << endl <<
            "       || /      \\     \\  || " << "    6. Iconizar Imagem" << endl <<
            "       ||/        \\     \\ || " << "    7. Filtro Passa Baixa" << endl <<
            "       =====================" << endl;

    //continua fazendo operações até que o programa se encerre pelo usuário
    while (continua == 1) {

        //recebe os valores padroes da imagem de entrada
        linha_saida = linha;
        coluna_saida = coluna;
        //solicita o número da opção de edição
        cout << endl << "   Digite o número da edição que deseja fazer com sua imagem: ";
        cin >> opcao;

        //confere se a opção existe
        while ((opcao <= 0) || (opcao > 7)) {
            cout << "   Não existe opção para esse valor, digite novamente:";
            cin >> opcao;
        }

        //a depender de cada opção, chama a função correspondente
        if (opcao == 1) {
            cout << "   Digite qual a porcentagem que você deseja escurecer sua imagem:";
            cin >> opcao;
            //confere se a porcentagem é um valor possível
            while (opcao < 0 || opcao > 100) {
                cout << "   O valor digitado deve estar entre 0% e 100%, digite novamente:";
                cin >> opcao;
            }
            //calcula o valor que deverá ser diminuido a cada pixel
            opcao = (escala * opcao) / 100;
            Escurecer(entrada, saida, &linha, &coluna, &opcao, &escala);
        } else {
            if (opcao == 2) {
                cout << "   Digite qual a porcentagem que você deseja clarear sua imagem: ";
                cin >> opcao;
                //confere se a porcentagem é um valor possível
                while (opcao < 0 || opcao > 100) {
                    cout << "   O valor digitado deve estar entre 0 e 100, digite novamente: ";
                    cin >> opcao;
                }
                //calcula o valor que deverá ser aumentado a cada pixel
                opcao = (escala * opcao) / 100;
                Clarear(entrada, saida, &linha, &coluna, &opcao, &escala);
            } else {
                if (opcao == 3) {
                    GirarDireita(entrada, saida, &linha, &coluna);
                    //troca linha pela coluna
                    linha_saida = coluna;
                    coluna_saida = linha;
                } else {
                    if (opcao == 4) {
                        GirarEsquerda(entrada, saida, &linha, &coluna);
                        //troca linha pela coluna
                        linha_saida = coluna;
                        coluna_saida = linha;
                    } else {
                        if (opcao == 5) {
                            cout << "   Digite qual o fator de binarização que você deseja: ";
                            cin >> opcao;
                            //confere se a binarização está dentro da escala
                            while (opcao < 0 || opcao > escala) {
                                cout << "   O valor digitado deve estar entre 0 e "
                                        << escala << ", digite novamente: ";
                                cin >> opcao;
                            }
                            Binarizar(entrada, saida, &linha, &coluna, &opcao, &escala);
                        } else {
                            if (opcao == 6) {
                                Iconizar(entrada, saida, &linha, &coluna);
                                //padroniza linha e coluna como 64
                                linha_saida = coluna_saida = 64;
                            } else {
                                FiltroPassaBaixa(entrada, saida, &linha, &coluna);
                            }
                        }
                    }
                }
            }
        }

        //solicita e guarda o nome da imagem de saída
        cout << "   Digite o nome desejado da imagem de saída: ";
        cin >> nome_saida;
        nome_saida = nome_saida + ".pgm";
        //confere se deu tudo certo ao criar a imagem
        if (ImagemSaida(nome_saida, saida, &linha_saida, &coluna_saida, &escala) != 0) {
            cout << erro << endl;
            return 1;
        }
        //mostra imagem de sucesso se tudo ocorreu bem
        cout << "   Imagem com o nome '" << "\e[1m" << nome_saida << "\e[0m"
                << "' criada com sucesso!" << endl;
        //pergunta se deseja realizar outra operação
        cout << endl <<
                "   Deseja realizar outra operação com a imagem de entrada?" <<
                endl << "   1. sim | 2. não: ";
        cin >> continua;
        //confere se o valor digitado é possível
        while ((continua < 1) || (continua > 2)) {
            cout << "   Opção inexistente! Digite novamente: ";
            cin >> continua;
        }
    }
    //mostra na tela que o programa está fechando
    cout << endl << "   Programa fechando..." << endl << endl;

    return 0;
}
