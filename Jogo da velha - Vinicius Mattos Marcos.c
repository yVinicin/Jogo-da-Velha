/*  
    ==========================================
    ||          Jogo da velha.              ||
    ||    Nome: Vinicius Mattos Marcos.     ||
    ==========================================
*/

// Bibliotecas.
#include <stdio.h>

#define CLEAR "\033[H\033[2J"

// Varaiáveis globais.
char Tabuleiro[3][3];
char jogardnv;
int linha, coluna;
int npartidas, partidaA= 1;
int jogador = 1, jogada = 9;
int modoJogo, dificuldade;
int pontuacao1 = 0, pontuacao2 = 0; // Pontuação do jogador 1 e jogador 2, respectivamente.

int ValidaOuN(int l, int c);

// Função para inicializar a matriz (tabuleiro) com espaços.
void IncializarTabuleiro() {
    for(int lin = 0; lin < 3; lin++) {
        for(int col = 0; col < 3; col++) {
            Tabuleiro[lin][col] = ' ';
        }
    }
}

// Função para limpar o console;
void LimparConsole() {
    printf(CLEAR);
    return;
}

// Função para limpar o buffer de entrada.
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para imprimir o cabeçalho do jogo.
void ImprimeCabecalho() {
    printf("\n================================================\n");
    printf("||              Jogo da Velha                 ||\n");
    printf("||    (feito por: Vinicius Mattos Marcos)     ||\n");
    printf("================================================\n\n");
}

// Função para imprimir o tabuleiro.
void ImprimeTabuleiro(char T[3][3]) {
    printf("              0     1     2\n");
    printf("           -------------------\n");
    printf("         0 |  %c  |  %c  |  %c  |\n", T[0][0], T[0][1], T[0][2]);
    printf("           ------+-----+------\n");
    printf("         1 |  %c  |  %c  |  %c  |\n", T[1][0], T[1][1], T[1][2]);
    printf("           ------+-----+------\n");
    printf("         2 |  %c  |  %c  |  %c  |\n", T[2][0], T[2][1], T[2][2]);
    printf("           -------------------\n\n");
}

// Função para imprimir a situação atual do jogo.
void ImprimirSituacao(int jogador, int jogada, int pontos1, int pontos2) {
    printf("Pontuação\n");
    printf("(Vitória = 2 pts || Derrota = 0 pts || Empate = 1 pt para cada)\n");
    printf("Jogador 1: %d\n", pontos1);
    printf("Jogador 2: %d\n\n", pontos2);
    printf("Partida atual: ( %d / %d )\n", partidaA, npartidas);
    printf("Jogadas restantes: %d\n", jogada);
    
    if(jogador == 1) {
        printf("Vez do jogador 1 ( X )\n\n");
    } else {
        printf("Vez do jogador 2 ( O )\n\n");
    }
}

// Função para dar uma pausa no jogo (ver a situação do tabuleiro ao final rodada jogada).
void Pausa() {
    limparBufferEntrada();
    LimparConsole();
    ImprimeCabecalho();
    ImprimeTabuleiro(Tabuleiro);
    ImprimirSituacao(jogador, jogada, pontuacao1, pontuacao2);
    printf("Pressione Enter para continuar!\n");
    getchar();
}

// Função para ler as coordenadas.
void LerCoordenadas(int jogador) {
    
    printf("Digite o número da linha (0 - 2): ");
    scanf("%d", &linha);
    printf("Digite o número da coluna (0 - 2): ");
    scanf("%d", &coluna);

    while(ValidaOuN(linha, coluna) != 1) {
        LimparConsole();
        ImprimeCabecalho();
        ImprimeTabuleiro(Tabuleiro);
        ImprimirSituacao(jogador, jogada, pontuacao1, pontuacao2);
        printf("Coordenada inválida! Digite novamente.\n");
        printf("Digite o número da linha (0 - 2): ");
        scanf("%d", &linha);
        printf("Digite o número da coluna (0 - 2): ");
        scanf("%d", &coluna);
    }

    if(jogador == 1) {
        Tabuleiro[linha][coluna] = 'X';
    } else {
        Tabuleiro[linha][coluna] = 'O';
    }
}

/*
    Função para verificar se as coordenadas são válidas.
    1 = válida.
    0 = inválida.
*/ 

int ValidaOuN(int l, int c) {
    if(l >= 0 && l < 3 && c >= 0 && c < 3 && Tabuleiro[l][c] == ' ') {
        return 1;
    } else {
        return 0;
    }
}

/*
    Função que verifica vitória por linha.
    1 = jogador 1 ganhou.
    2 = jogador 2 ganhou.
    3 = ninguém ganhou ainda.
*/
int VitoriaLinha(int jogador) {
    for(int l = 0; l < 3; l++) {
        if(jogador == 1) {
            if(Tabuleiro[l][0] == 'X' && Tabuleiro[l][1] == 'X' && Tabuleiro[l][2] == 'X') {
                return 1;
            }
        } else {
            if(Tabuleiro[l][0] == 'O' && Tabuleiro[l][1] == 'O' && Tabuleiro[l][2] == 'O') {
                return 2;
            } 
        }
    }
    return 3;
}

/*
    Função que verifica vitória por coluna.
    1 = jogador 1 ganhou.
    2 = jogador 2 ganhou.
    3 = ninguém ganhou ainda.
*/
int VitoriaColuna(int jogador) {
    for(int c = 0; c < 3; c++) {
        if(jogador == 1) {
            if(Tabuleiro[0][c] == 'X' && Tabuleiro[1][c] == 'X' && Tabuleiro[2][c] == 'X') {
                return 1;
            }
        } else {
            if(Tabuleiro[0][c] == 'O' && Tabuleiro[1][c] == 'O' && Tabuleiro[2][c] == 'O') {
                return 2;
            } 
        }
    }
    return 3;
}

/*
    Função que verifica vitória na diagonal principal.
    1 = jogador 1 ganhou.
    2 = jogador 2 ganhou.
    3 = ninguém ganhou ainda.
*/
int VitoriaDiagP(int jogador) {
    if(jogador == 1) {
        if(Tabuleiro[0][0] == 'X' && Tabuleiro[1][1] == 'X' && Tabuleiro[2][2] == 'X') {
            return 1;
        }
    } else {
        if(Tabuleiro[0][0] == 'O' && Tabuleiro[1][1] == 'O' && Tabuleiro[2][2] == 'O') {
            return 2;
        } 
    }
    return 3;
}

/*
    Função que verifica vitória na diagonal secundária.
    1 = jogador 1 ganhou.
    2 = jogador 2 ganhou.
    3 = ninguém ganhou ainda.
*/
int VitoriaDiagS(int jogador) {
    if(jogador == 1) {
        if(Tabuleiro[0][2] == 'X' && Tabuleiro[1][1] == 'X' && Tabuleiro[2][0] == 'X') {
            return 1;
        }
    } else {
        if(Tabuleiro[0][2] == 'O' && Tabuleiro[1][1] == 'O' && Tabuleiro[2][0] == 'O') {
            return 2;
        } 
    }
    return 3;
}

/*
    Função que verifica quem ganhou o jogo.
    1 = jogador 1 ganhou.
    2 = jogador 2 ganhou.
    3 = ninguém ganhou ainda.
*/
int Vencedor(int jogador) {
    if(VitoriaLinha(jogador) == 1 || VitoriaColuna(jogador) == 1 || VitoriaDiagP(jogador) == 1 || VitoriaDiagS(jogador) == 1) {
        return 1;
    } else if(VitoriaLinha(jogador) == 2 || VitoriaColuna(jogador) == 2 || VitoriaDiagP(jogador) == 2 || VitoriaDiagS(jogador) == 2) {
        return 2;
    } else {
        return 3;
    }
}

// Função para verificar a quantidade de posições vazias (verifica se houve empate caso a váriavel retorne zerada)
int Empate() {
    int quantidade = 0;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(Tabuleiro[i][j] == ' ') {
                quantidade++;
            }
        }
    }
    return quantidade;
}

// Função que verifica o vencedor pelos pontos totais.
void VencedorPorPt(int pts1, int pts2) {
    if(pts1 > pts2) {
        printf("Jogador 1 venceu!!!\n\n");
    } else if(pts2 > pts1) {
        printf("Jogador 2 venceu!!!\n\n");
    } else {
        printf("Empate!!!\n\n");
    }
}

// Função para o Bot na dificuldade fácil (joga no primeiro espaço vazio que encontrar).
void BotFacil() {
    for(int l = 0; l < 3; l++) {
        for(int c = 0; c < 3; c++) {
            if(Tabuleiro[l][c] == ' ') {
                Tabuleiro[l][c] = 'O';
                return;
            }
        }
    }
}

/*
    Função na qual o Bot(dificil) faz sua jogada nos cantos.
    1 = válido.
    2 = inválido.
*/
int Cantos() {
    if(Tabuleiro[0][0] == ' ') {
        Tabuleiro[0][0] = 'O';
        return 1;
    } else if(Tabuleiro[2][2] == ' ') {
        Tabuleiro[2][2] = 'O';
        return 1;
    } else if(Tabuleiro[2][0] == ' ') {
        Tabuleiro[2][0] = 'O';
        return 1;
    } else if(Tabuleiro[0][2] == ' ') {
        Tabuleiro[0][2] = 'O';
        return 1;
    }
    return 2;
}

/*
    Função que mostra ao Bot se o Jogador tem alguma possibilidade de ganhar (faz com que o Bot impeça a vitória do Jogador).
    1 = Impediu a vitória do jogador.
    2 = Nada aconteceu ainda.
*/
int EmpateBotDificil() {
    
    // Verifica chance de vitória (do jogador) na primeira linha.
    if(Tabuleiro[0][0] == ' ' && Tabuleiro[0][1] == 'X' && Tabuleiro[0][2] == 'X') {
        Tabuleiro[0][0] = 'O';
        return 1;
    } else if(Tabuleiro[0][0] == 'X' && Tabuleiro[0][1] == ' ' && Tabuleiro[0][2] == 'X') {
        Tabuleiro[0][1] = 'O';
        return 1;
    } else if(Tabuleiro[0][0] == 'X' && Tabuleiro[0][1] == 'X' && Tabuleiro[0][2] == ' ') {
        Tabuleiro[0][2] = 'O';
        return 1;
    }
    
    // Verifica chance de vitória (do jogador) na segunda linha.
    else if(Tabuleiro[1][0] == ' ' && Tabuleiro[1][1] == 'X' && Tabuleiro[1][2] == 'X') {
        Tabuleiro[1][0] = 'O';
        return 1;
    } else if(Tabuleiro[1][0] == 'X' && Tabuleiro[1][1] == ' ' && Tabuleiro[1][2] == 'X') {
        Tabuleiro[1][1] = 'O';
        return 1;
    } else if(Tabuleiro[1][0] == 'X' && Tabuleiro[1][1] == 'X' && Tabuleiro[1][2] == ' ') {
        Tabuleiro[1][2] = 'O';
        return 1;
    }

    // Verifica chance de vitória (do jogador) na última linha.
    else if(Tabuleiro[2][0] == ' ' && Tabuleiro[2][1] == 'X' && Tabuleiro[2][2] == 'X') { 
        Tabuleiro[2][0] = 'O';
        return 1;
    } else if(Tabuleiro[2][0] == 'X' && Tabuleiro[2][1] == ' ' && Tabuleiro[2][2] == 'X') {
        Tabuleiro[2][1] = 'O';
        return 1;
    } else if(Tabuleiro[2][0] == 'X' && Tabuleiro[2][1] == 'X' && Tabuleiro[2][2] == ' ') {
        Tabuleiro[2][2] = 'O';
        return 1;
    }
    
    // Verifica chance de vitória (do jogador) na primeira coluna.
    else if(Tabuleiro[0][0] == ' ' && Tabuleiro[1][0] == 'X' && Tabuleiro[2][0] == 'X') { 
        Tabuleiro[0][0] = 'O';
        return 1;
    } else if(Tabuleiro[0][0] == 'X' && Tabuleiro[1][0] == ' ' && Tabuleiro[2][0] == 'X') { 
        Tabuleiro[1][0] = 'O';
        return 1;
    } else if(Tabuleiro[0][0] == 'X' && Tabuleiro[1][0] == 'X' && Tabuleiro[2][0] == ' ') { 
        Tabuleiro[2][0] = 'O';
        return 1;
    }
    
    // Verifica chance de vitória (do jogador) na segunda coluna.
    else if(Tabuleiro[0][1] == ' ' && Tabuleiro[1][1] == 'X' && Tabuleiro[2][1] == 'X') {
        Tabuleiro[0][1] = 'O';
        return 1;
    } else if(Tabuleiro[0][1] == 'X' && Tabuleiro[1][1] == ' ' && Tabuleiro[2][1] == 'X') {
        Tabuleiro[1][1] = 'O';
        return 1;
    } else if(Tabuleiro[0][1] == 'X' && Tabuleiro[1][1] == 'X' && Tabuleiro[2][1] == ' ') {
        Tabuleiro[2][1] = 'O';
        return 1;
    }
    
    // Verifica chance de vitória (do jogador) na última coluna.
    else if(Tabuleiro[0][2] == ' ' && Tabuleiro[1][2] == 'X' && Tabuleiro[2][2] == 'X') { 
        Tabuleiro[0][2] = 'O';
        return 1;
    } else if(Tabuleiro[0][2] == 'X' && Tabuleiro[1][2] == ' ' && Tabuleiro[2][2] == 'X') { 
        Tabuleiro[1][2] = 'O';
        return 1;
    } else if(Tabuleiro[0][2] == 'X' && Tabuleiro[1][2] == 'X' && Tabuleiro[2][2] == ' ') { 
        Tabuleiro[2][2] = 'O';
        return 1;
    }

    // Verifica chance de vitória (do jogador) na diagonal principal.
    else if(Tabuleiro[0][0] == ' ' && Tabuleiro[1][1] == 'X' && Tabuleiro[2][2] == 'X') {
        Tabuleiro[0][0] = 'O';
        return 1;
    } else if(Tabuleiro[0][0] == 'X' && Tabuleiro[1][1] == ' ' && Tabuleiro[2][2] == 'X') {
        Tabuleiro[1][1] = 'O';
        return 1;
    } else if(Tabuleiro[0][0] == 'X' && Tabuleiro[1][1] == 'X' && Tabuleiro[2][2] == ' ') {
        Tabuleiro[2][2] = 'O';
        return 1;
    }

    // Verifica chance de vitória (do jogador) na diagonal secundária.
    else if(Tabuleiro[0][2] == ' ' && Tabuleiro[1][1] == 'X' && Tabuleiro[2][0] == 'X') {
        Tabuleiro[0][2] = 'O';
        return 1;
    } else if(Tabuleiro[0][2] == 'X' && Tabuleiro[1][1] == ' ' && Tabuleiro[2][0] == 'X') {
        Tabuleiro[1][1] = 'O';
        return 1;
    } else if(Tabuleiro[0][2] == 'X' && Tabuleiro[1][1] == 'X' && Tabuleiro[2][0] == ' ') {
        Tabuleiro[2][0] = 'O';
        return 1;
    }
    return 2;
}

/*
    Função que verifica possibilidades de vitória para o Bot(Dificil).
    1 = Bot gahou.
    2 = Bot não ganhou ainda.
*/
int VitoriaBotDificil() {
    
    // Verifica chance de vitória (do bot) na primeira linha.
    if(Tabuleiro[0][0] == ' ' && Tabuleiro[0][1] == 'O' && Tabuleiro[0][2] == 'O') {
        Tabuleiro[0][0] = 'O';
        return 1;
    } else if(Tabuleiro[0][0] == 'O' && Tabuleiro[0][1] == ' ' && Tabuleiro[0][2] == 'O') {
        Tabuleiro[0][1] = 'O';
        return 1;
    } else if(Tabuleiro[0][0] == 'O' && Tabuleiro[0][1] == 'O' && Tabuleiro[0][2] == ' ') {
        Tabuleiro[0][2] = 'O';
        return 1;
    }
    
    // Verifica chance de vitória (do bot) na segunda linha.
    else if(Tabuleiro[1][0] == ' ' && Tabuleiro[1][1] == 'O' && Tabuleiro[1][2] == 'O') {
        Tabuleiro[1][0] = 'O';
        return 1;
    } else if(Tabuleiro[1][0] == 'O' && Tabuleiro[1][1] == ' ' && Tabuleiro[1][2] == 'O') {
        Tabuleiro[1][1] = 'O';
        return 1;
    } else if(Tabuleiro[1][0] == 'O' && Tabuleiro[1][1] == 'O' && Tabuleiro[1][2] == ' ') {
        Tabuleiro[1][2] = 'O';
        return 1;
    }

    // Verifica chance de vitória (do bot) na última linha.
    else if(Tabuleiro[2][0] == ' ' && Tabuleiro[2][1] == 'O' && Tabuleiro[2][2] == 'O') { 
        Tabuleiro[2][0] = 'O';
        return 1;
    } else if(Tabuleiro[2][0] == 'O' && Tabuleiro[2][1] == ' ' && Tabuleiro[2][2] == 'O') {
        Tabuleiro[2][1] = 'O';
        return 1;
    } else if(Tabuleiro[2][0] == 'O' && Tabuleiro[2][1] == 'O' && Tabuleiro[2][2] == ' ') {
        Tabuleiro[2][2] = 'O';
        return 1;
    }
    
    // Verifica chance de vitória (do bot) na primeira coluna.
    else if(Tabuleiro[0][0] == ' ' && Tabuleiro[1][0] == 'O' && Tabuleiro[2][0] == 'O') { 
        Tabuleiro[0][0] = 'O';
        return 1;
    } else if(Tabuleiro[0][0] == 'O' && Tabuleiro[1][0] == ' ' && Tabuleiro[2][0] == 'O') { 
        Tabuleiro[1][0] = 'O';
        return 1;
    } else if(Tabuleiro[0][0] == 'O' && Tabuleiro[1][0] == 'O' && Tabuleiro[2][0] == ' ') { 
        Tabuleiro[2][0] = 'O';
        return 1;
    }
    
    // Verifica chance de vitória (do bot) na segunda coluna.
    else if(Tabuleiro[0][1] == ' ' && Tabuleiro[1][1] == 'O' && Tabuleiro[2][1] == 'O') {
        Tabuleiro[0][1] = 'O';
        return 1;
    } else if(Tabuleiro[0][1] == 'O' && Tabuleiro[1][1] == ' ' && Tabuleiro[2][1] == 'O') {
        Tabuleiro[1][1] = 'O';
        return 1;
    } else if(Tabuleiro[0][1] == 'O' && Tabuleiro[1][1] == 'O' && Tabuleiro[2][1] == ' ') {
        Tabuleiro[2][1] = 'O';
        return 1;
    }
    
    // Verifica chance de vitória (do bot) na última coluna.
    else if(Tabuleiro[0][2] == ' ' && Tabuleiro[1][2] == 'O' && Tabuleiro[2][2] == 'O') { 
        Tabuleiro[0][2] = 'O';
        return 1;
    } else if(Tabuleiro[0][2] == 'O' && Tabuleiro[1][2] == ' ' && Tabuleiro[2][2] == 'O') { 
        Tabuleiro[1][2] = 'O';
        return 1;
    } else if(Tabuleiro[0][2] == 'O' && Tabuleiro[1][2] == 'O' && Tabuleiro[2][2] == ' ') { 
        Tabuleiro[2][2] = 'O';
        return 1;
    }

    // Verifica chance de vitória (do bot) na diagonal principal.
    else if(Tabuleiro[0][0] == ' ' && Tabuleiro[1][1] == 'O' && Tabuleiro[2][2] == 'O') {
        Tabuleiro[0][0] = 'O';
        return 1;
    } else if(Tabuleiro[0][0] == 'O' && Tabuleiro[1][1] == ' ' && Tabuleiro[2][2] == 'O') {
        Tabuleiro[1][1] = 'O';
        return 1;
    } else if(Tabuleiro[0][0] == 'O' && Tabuleiro[1][1] == 'O' && Tabuleiro[2][2] == ' ') {
        Tabuleiro[2][2] = 'O';
        return 1;
    }

    // Verifica chance de vitória (do bot) na diagonal secundária.
    else if(Tabuleiro[0][2] == ' ' && Tabuleiro[1][1] == 'O' && Tabuleiro[2][0] == 'O') {
        Tabuleiro[0][2] = 'O';
        return 1;
    } else if(Tabuleiro[0][2] == 'O' && Tabuleiro[1][1] == ' ' && Tabuleiro[2][0] == 'O') {
        Tabuleiro[1][1] = 'O';
        return 1;
    } else if(Tabuleiro[0][2] == 'O' && Tabuleiro[1][1] == 'O' && Tabuleiro[2][0] == ' ') {
        Tabuleiro[2][0] = 'O';
        return 1;
    }
    return 2;
}

/*
    Função que verifica se há X em volta do meio.
    1 = verdadeiro.
    0 = falso.
*/
int VerificaXEmVolta() {
    if(Tabuleiro[0][1] == 'X' && Tabuleiro[1][0] == 'X') {
        if(Tabuleiro[0][2] == ' ') {    
            Tabuleiro[0][2] = 'O';
            return 1;
        }
    } else if(Tabuleiro[1][0] == 'X' && Tabuleiro[2][1] == 'X') {
        if(Tabuleiro[2][0] == ' ') {    
            Tabuleiro[2][0] = 'O';
            return 1;
        }
    } else if(Tabuleiro[2][1] == 'X' && Tabuleiro[1][2] == 'X') {
        if(Tabuleiro[2][2] == ' ') {
            Tabuleiro[2][2] = 'O';
            return 1;
        }
    } else if(Tabuleiro[1][2] == 'X' && Tabuleiro[0][1] == 'X') {
        if(Tabuleiro[0][2] == ' ') {
            Tabuleiro[0][2] = 'O';
            return 1;
        }
    }
    return 0;
}

// Função para o Bot na dificuldade difícil.
void BotDificil() {
    if(VitoriaBotDificil() == 1) {
        return;
    }

    if(EmpateBotDificil() == 1) {
        return;
    }

    if(jogada == 8 && Tabuleiro[1][1] == ' ') { // Se o Bot for o segundo a jogar, ele deve iniciar pelo meio, se a posição estiver vazia.
        Tabuleiro[1][1] = 'O';
        return;
    } else if(Tabuleiro[0][1] == 'X' && Tabuleiro[1][0] == 'X' && jogada == 5) {
        Tabuleiro[2][2] = 'O';
        return;
    } else if(VerificaXEmVolta() == 1) {
        return;
    } else if(jogada == 6) { // Na segunda jogada do Bot, caso o Jogador não tenha armado nenhuma vitória, ele deve jogar em alguma destas posições.
        if(Tabuleiro[0][1] == ' ') {
            Tabuleiro[0][1] = 'O';
            return;
        } else if(Tabuleiro[1][0] == ' ') {
            Tabuleiro[1][0] = 'O';
            return;
        } else if(Tabuleiro[1][2] == ' ') {
            Tabuleiro[1][2] = 'O';
            return;
        } else if(Tabuleiro[2][1] == ' ') {
            Tabuleiro[2][1] = 'O';
            return;
        }
    }
    
    if(Tabuleiro[1][1] == 'X') {
        if(Cantos() == 1) {
            return;
        } else {
            BotFacil();
        }
    } else if(Tabuleiro[0][1] == 'X') {
        if(jogada == 5 && Tabuleiro[2][2] == ' ') {
            Tabuleiro[2][2] = 'O';
            return;
        } else if(Tabuleiro[2][0] == ' ') {    
            Tabuleiro[2][0] = 'O';
            return;
        } else {
            BotFacil();
        }
    } else if(Tabuleiro[1][0] == 'X') {
        if(Tabuleiro[0][2] == ' ') {
            Tabuleiro[0][2] = 'O';
            return;
        } else {
            BotFacil();
        }
    } else if(Cantos() == 1) {
        return;
    } else {
        BotFacil();
    }
}

// Função principal.
int main() {

    do {
        partidaA = 1;
        jogador = 1;
        jogada = 9;
        pontuacao1 = 0;
        pontuacao2 = 0;
        
        LimparConsole();
        ImprimeCabecalho();
        IncializarTabuleiro();
        ImprimeTabuleiro(Tabuleiro);

        printf("Selecione o modo de jogo:\n");
        printf("1 - PvP (Jogador vs Jogador)\n");
        printf("2 - PvE (Jogador vs Computador)\n");
        printf("--> ");
        scanf("%d", &modoJogo);

        if(modoJogo == 1) { // Modo PvP (Player vs Player)
            printf("Digite o número de partidas que deseja jogar: ");
            scanf("%d", &npartidas);

            for(int i = 0; i < npartidas; i++) { // Laço de repetição para o número de rodadas.

                IncializarTabuleiro();

                while(Empate() > 0) { // Laço de repetição para a rodada atual.
                    LimparConsole();
                    ImprimeCabecalho();
                    ImprimeTabuleiro(Tabuleiro);
                    ImprimirSituacao(jogador, jogada, pontuacao1, pontuacao2);
                    LerCoordenadas(jogador);
                        
                    if(Vencedor(jogador) == 1) {
                        pontuacao1 += 2;
                        Pausa();
                        break;
                    } else if(Vencedor(jogador) == 2) {
                        pontuacao2 += 2;
                        Pausa();
                        break;
                    } else if(Empate() == 0) {
                        pontuacao1++;
                        pontuacao2++;
                        if(jogador == 1) {
                            jogador++;
                        } else {
                            jogador = 1;
                        }
                        Pausa();
                        break;
                    }

                    if(jogador == 1) {
                        jogador++;
                    } else {
                        jogador = 1;
                    }
                    jogada--;
                }
                
                LimparConsole();
                ImprimeCabecalho();
                ImprimeTabuleiro(Tabuleiro);
                ImprimirSituacao(jogador, jogada, pontuacao1, pontuacao2);
                
                jogada = 9;
                partidaA++;
            }

            VencedorPorPt(pontuacao1, pontuacao2);

        } else { // Modo PvC (Player vs Computador)
            printf("Selecione a dificuldade:\n");
            printf("1 - Fácil\n");
            printf("2 - Difícil\n");
            printf("--> ");
            scanf("%d", &dificuldade);
            jogador = 2; // Bot começa jogando.

            if(dificuldade == 1) { // Dificuldade fácil.
                printf("Digite o número de partidas que deseja jogar: ");
                scanf("%d", &npartidas);

                for(int i = 0; i < npartidas; i++) { // Laço de repetição para o número de rodadas.
                    
                    IncializarTabuleiro();

                    while(Empate() > 0) { // Laço de repetição para a rodada atual.
                        LimparConsole();
                        ImprimeCabecalho();
                        ImprimeTabuleiro(Tabuleiro);
                        ImprimirSituacao(jogador, jogada, pontuacao1, pontuacao2);
                        
                        if(jogador == 1) { // Jogador.
                            LerCoordenadas(jogador);
                        } else { // Bot.
                            BotFacil();
                        }

                        if(Vencedor(jogador) == 1) {
                            pontuacao1 += 2;
                            Pausa();
                            break;
                        } else if(Vencedor(jogador) == 2) {
                            pontuacao2 += 2;
                            Pausa();
                            break;
                        } else if(Empate() == 0) {
                            pontuacao1++;
                            pontuacao2++;
                            if(jogador == 1) {
                                jogador++;
                            } else {
                                jogador = 1;
                            }
                            Pausa();
                            break;
                        }
                        
                        if(jogador == 1) {
                            jogador++;
                        } else {
                            jogador = 1;
                        }
                        jogada--;
                    }

                    LimparConsole();
                    ImprimeCabecalho();
                    ImprimeTabuleiro(Tabuleiro);
                    ImprimirSituacao(jogador, jogada, pontuacao1, pontuacao2);

                    jogada = 9;
                    partidaA++;
                }

                VencedorPorPt(pontuacao1, pontuacao2);

            } else { // Dificuldade difícil.
                printf("Digite o número de partidas que deseja jogar: ");
                scanf("%d", &npartidas);

                for(int i = 0; i < npartidas; i++) { // Laço de repetição para o número de rodadas.
                    
                    IncializarTabuleiro();

                    while(Empate() > 0) { // Laço de repetição para a rodada atual.
                        LimparConsole();
                        ImprimeCabecalho();
                        ImprimeTabuleiro(Tabuleiro);
                        ImprimirSituacao(jogador, jogada, pontuacao1, pontuacao2);
                        
                        if(jogador == 1) { // Jogador.
                            LerCoordenadas(jogador);
                        } else { // Bot.
                            BotDificil();
                        }

                        if(Vencedor(jogador) == 1) {
                            pontuacao1 += 2;
                            Pausa();
                            break;
                        } else if(Vencedor(jogador) == 2) {
                            pontuacao2 += 2;
                            Pausa();
                            break;
                        } else if(Empate() == 0) {
                            pontuacao1++;
                            pontuacao2++;
                            if(jogador == 1) {
                                jogador++;
                            } else {
                                jogador = 1;
                            }
                            Pausa();
                            break;
                        }
                        
                        if(jogador == 1) {
                            jogador++;
                        } else {
                            jogador = 1;
                        }
                        jogada--;
                    }

                    LimparConsole();
                    ImprimeCabecalho();
                    ImprimeTabuleiro(Tabuleiro);
                    ImprimirSituacao(jogador, jogada, pontuacao1, pontuacao2);

                    jogada = 9;
                    partidaA++;
                }

                VencedorPorPt(pontuacao1, pontuacao2);
            }
        }
        printf("Deseja jogar novamente? ( S / N ): ");
        scanf(" %c", &jogardnv);
    } while(jogardnv == 'S' || jogardnv == 's');

    return 0;
}
