#include <stdlib.h>
#include <stdio.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <pthread.h>
#include "jogo.h"
#include "constante.h"

//VARIÁVEL GLOBAL
int gVitoria = 0;
int gContinuar = 1;
int gDerrota = 0;

//ESTRUTURAS PARA AS BOMBAS NA TELA
typedef struct
{
int **mapa_bomba_j1;
    SDL_Surface* tela_bomba_j1;
}bomba_j1;

bomba_j1 j1;

typedef struct
{
int **mapa_bomba_j2;
    SDL_Surface* tela_bomba_j2;
}bomba_j2;

bomba_j2 j2;

//BOMBA VERMELHA
SDL_Rect posicao_bomba_v1;
SDL_Rect posicao_bomba_v2;

//CRIAÇÃO EXPLOSÕES DE BOMBAS NA TELA
SDL_Rect posicao_explosao_d;
SDL_Rect posicao_explosao_e;
SDL_Rect posicao_explosao_b;
SDL_Rect posicao_explosao_c;
SDL_Rect posicao_explosao_m;

//TECLADO PARA OS 2 PLAYERS SEM CONFLITO
void teclado_atualizado(teclas* estado_teclado)
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_KEYDOWN:
            estado_teclado -> key[event.key.keysym.sym] = 1;
            break;

            case SDL_KEYUP:
            estado_teclado -> key[event.key.keysym.sym] = 0;
            break;

            default:
            break;
        }
    }
}

//CRICAÇÃO DAS POSIÇÕES DOS PLAYERS
SDL_Rect posicao, posicao_jogador_1;
SDL_Rect posicao_2, posicao_jogador_2;

//FUNÇÃO DO JOGO
void jogar(SDL_Surface* tela)
{
    teclas estado_teclado;
    memset(&estado_teclado, 0, sizeof(estado_teclado));

//CRICAÇÃO DAS IMAGENS
    SDL_Surface *jogador_1b = NULL;
    SDL_Surface *jogador_1c = NULL;
    SDL_Surface *jogador_1d = NULL;
    SDL_Surface *jogador_1e = NULL;

    SDL_Surface *jogador_2b = NULL;
    SDL_Surface *jogador_2c = NULL;
    SDL_Surface *jogador_2d = NULL;
    SDL_Surface *jogador_2e = NULL;

    SDL_Surface *jogador_1_atual = NULL;
    SDL_Surface *jogador_2_atual = NULL;

    SDL_Surface *bloco = NULL;

//CRIAÇÃO DA POSIÇÃO DO CENÁRIO E DA SUA IMAGEM
    SDL_Rect posicao_cenario;
    SDL_Surface *cenario = NULL;

//CRIAÇÃO DAS IMAGENS DE BOMBAS E EXPLOSÃO
    SDL_Surface *bomba_v1 = NULL;
    SDL_Surface *bomba_v2 = NULL;

    SDL_Surface *bomba_1 = NULL;
    SDL_Surface *bomba_2 = NULL;

    SDL_Surface *explosao_b = NULL;
    SDL_Surface *explosao_c = NULL;
    SDL_Surface *explosao_d = NULL;
    SDL_Surface *explosao_e = NULL;
    SDL_Surface *explosao_m = NULL;

//CRIAÇÃO DOS BLOCOS ANIMADOS
    SDL_Surface *bloco_1 = NULL;
    SDL_Surface *bloco_2 = NULL;
    SDL_Surface *bloco_3 = NULL;
    SDL_Surface *bloco_4 = NULL;
    SDL_Surface *bloco_5 = NULL;
    SDL_Surface *bloco_6 = NULL;

//CRIAÇÃO DO MAPA
    int i = 0, j = 0;

    int **mapa = (int**)malloc(11*sizeof(int*));

    for(i = 0; i < 11; i++)
    {
        mapa[i] = (int*)malloc((15*sizeof(int)));
    }

//PAREDE ESQUERDA
    mapa[0][0] = 1;
    mapa[1][0] = 1;
    mapa[2][0] = 1;
    mapa[3][0] = 1;
    mapa[4][0] = 1;
    mapa[5][0] = 1;
    mapa[6][0] = 1;
    mapa[7][0] = 1;
    mapa[8][0] = 1;
    mapa[9][0] = 1;
    mapa[10][0] = 1;
    mapa[11][0] = 1;
    mapa[12][0] = 1;

//PAREDE DIREITA
    mapa[0][14] = 1;
    mapa[1][14] = 1;
    mapa[2][14] = 1;
    mapa[3][14] = 1;
    mapa[4][14] = 1;
    mapa[5][14] = 1;
    mapa[6][14] = 1;
    mapa[7][14] = 1;
    mapa[8][14] = 1;
    mapa[9][14] = 1;
    mapa[10][14] = 1;
    mapa[11][14] = 1;
    mapa[12][14] = 1;

//PARADE CIMA
    mapa[0][1] = 1;
    mapa[0][2] = 1;
    mapa[0][3] = 1;
    mapa[0][4] = 1;
    mapa[0][5] = 1;
    mapa[0][6] = 1;
    mapa[0][7] = 1;
    mapa[0][8] = 1;
    mapa[0][9] = 1;
    mapa[0][10] = 1;
    mapa[0][11] = 1;
    mapa[0][12] = 1;
    mapa[0][13] = 1;
    mapa[0][14] = 1;

//PAREDE BAIXO
    mapa[12][1] = 1;
    mapa[12][2] = 1;
    mapa[12][3] = 1;
    mapa[12][4] = 1;
    mapa[12][5] = 1;
    mapa[12][6] = 1;
    mapa[12][7] = 1;
    mapa[12][8] = 1;
    mapa[12][9] = 1;
    mapa[12][10] = 1;
    mapa[12][11] = 1;
    mapa[12][12] = 1;
    mapa[12][13] = 1;
    mapa[12][14] = 1;
    mapa[2][2] = 1;

//LINHA DE PAREDE INTERNA 1
    mapa[2][4] = 1;
    mapa[2][6] = 1;
    mapa[2][8] = 1;
    mapa[2][10] = 1;
    mapa[2][12] = 1;

//LINHA DE PAREDE INTERNA 2
    mapa[4][2] = 1;
    mapa[4][4] = 1;
    mapa[4][6] = 1;
    mapa[4][8] = 1;
    mapa[4][10] = 1;
    mapa[4][12] = 1;

//LINHA DE PAREDE INTERNA 3
    mapa[6][2] = 1;
    mapa[6][4] = 1;
    mapa[6][6] = 1;
    mapa[6][8] = 1;
    mapa[6][10] = 1;
    mapa[6][12] = 1;

//LINHA DE PAREDE INTERNA 4
    mapa[8][2] = 1;
    mapa[8][4] = 1;
    mapa[8][6] = 1;
    mapa[8][8] = 1;
    mapa[8][10] = 1;
    mapa[8][12] = 1;

//LINHA DE PAREDE INTERNA 5
    mapa[10][2] = 1;
    mapa[10][4] = 1;
    mapa[10][6] = 1;
    mapa[10][8] = 1;
    mapa[10][10] = 1;
    mapa[10][12] = 1;

//BLOCOS DESTRUÍVES
    mapa[1][3] = 2;
    mapa[1][4] = 2;
    mapa[1][5] = 2;
    mapa[1][6] = 2;
    mapa[1][6] = 2;
    mapa[1][7] = 2;
    mapa[1][8] = 2;
    mapa[1][9] = 2;
    mapa[1][10] = 2;
    mapa[1][11] = 2;
    mapa[1][12] = 2;
    mapa[1][13] = 2;
    mapa[2][3] = 2;
    mapa[2][5] = 2;
    mapa[2][7] = 2;
    mapa[2][9] = 2;
    mapa[2][11] = 2;
    mapa[2][13] = 2;
    mapa[3][1] = 2;
    mapa[3][2] = 2;
    mapa[3][3] = 2;
    mapa[3][4] = 2;
    mapa[3][5] = 2;
    mapa[3][6] = 2;
    mapa[3][7] = 2;
    mapa[3][8] = 2;
    mapa[3][9] = 2;
    mapa[3][10] = 2;
    mapa[3][11] = 2;
    mapa[3][12] = 2;
    mapa[3][13] = 2;
    mapa[4][1] = 2;
    mapa[4][3] = 2;
    mapa[4][5] = 2;
    mapa[4][7] = 2;
    mapa[4][9] = 2;
    mapa[4][11] = 2;
    mapa[4][13] = 2;

    mapa[5][1] = 2;
    mapa[5][2] = 2;
    mapa[5][3] = 2;
    mapa[5][4] = 2;
    mapa[5][5] = 2;
    mapa[5][6] = 2;
    mapa[5][7] = 2;
    mapa[5][8] = 2;
    mapa[5][9] = 2;
    mapa[5][10] = 2;
    mapa[5][11] = 2;
    mapa[5][12] = 2;
    mapa[5][13] = 2;
    mapa[6][1] = 2;
    mapa[6][3] = 2;
    mapa[6][5] = 2;
    mapa[6][7] = 2;
    mapa[6][9] = 2;
    mapa[6][11] = 2;
    mapa[6][13] = 2;

    mapa[7][1] = 2;
    mapa[7][2] = 2;
    mapa[7][3] = 2;
    mapa[7][4] = 2;
    mapa[7][5] = 2;
    mapa[7][6] = 2;
    mapa[7][7] = 2;
    mapa[7][8] = 2;
    mapa[7][9] = 2;
    mapa[7][10] = 2;
    mapa[7][11] = 2;
    mapa[7][12] = 2;
    mapa[7][13] = 2;

    mapa[8][1] = 2;
    mapa[8][3] = 2;
    mapa[8][5] = 2;
    mapa[8][7] = 2;
    mapa[8][9] = 2;
    mapa[8][11] = 2;
    mapa[8][13] = 2;

    mapa[9][1] = 2;
    mapa[9][2] = 2;
    mapa[9][3] = 2;
    mapa[9][4] = 2;
    mapa[9][5] = 2;
    mapa[9][6] = 2;
    mapa[9][7] = 2;
    mapa[9][8] = 2;
    mapa[9][9] = 2;
    mapa[9][10] = 2;
    mapa[9][11] = 2;
    mapa[9][12] = 2;
    mapa[9][13] = 2;

    mapa[10][1] = 2;
    mapa[10][3] = 2;
    mapa[10][5] = 2;
    mapa[10][7] = 2;
    mapa[10][9] = 2;
    mapa[10][11] = 2;

    mapa[11][1] = 2;
    mapa[11][2] = 2;
    mapa[11][3] = 2;
    mapa[11][4] = 2;
    mapa[11][5] = 2;
    mapa[11][6] = 2;
    mapa[11][7] = 2;
    mapa[11][8] = 2;
    mapa[11][9] = 2;
    mapa[11][10] = 2;
    mapa[11][11] = 2;

//CRIAÇÃO DA MÚSICA DE BATALHA
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);

    Mix_Music *musica_batalha = NULL;
    musica_batalha = Mix_LoadMUS("stage-3-music.mp3");

    Mix_PlayMusic(musica_batalha, -1);

//CARREGAMENTO DAS IMAGENS
    bomba_v1 = IMG_Load("BombaV.bmp");
    bomba_v2 = IMG_Load("BombaV.bmp");

    bomba_1 = IMG_Load("Bomba2.bmp");
    bomba_2 = IMG_Load("Bomba2.bmp");

    explosao_b = IMG_Load("ExplosaoB.bmp");
    explosao_c = IMG_Load("ExplosaoC.bmp");
    explosao_d = IMG_Load("ExplosaoD.bmp");
    explosao_e = IMG_Load("ExplosaoE.bmp");
    explosao_m = IMG_Load("ExplosaoM.bmp");

    jogador_1b = IMG_Load("BombermanF.png");
    jogador_1e = IMG_Load("BombermanE.png");
    jogador_1d = IMG_Load("BombermanD.png");
    jogador_1c = IMG_Load("BombermanC.png");

    jogador_2b = IMG_Load("BombermanBF.png");
    jogador_2e = IMG_Load("BombermanBE.png");
    jogador_2d = IMG_Load("BombermanBD.png");
    jogador_2c = IMG_Load("BombermanBC.png");

    bloco = IMG_Load("Bloco1.png");
    cenario = IMG_Load("Back_penguim.bmp");

    bloco_1 = IMG_Load("Blocodegelo1.png");
    bloco_2 = IMG_Load("Blocodegelo2.png");
    bloco_3 = IMG_Load("Blocodegelo3.png");
    bloco_4 = IMG_Load("Blocodegelo4.png");
    bloco_5 = IMG_Load("Bloco5degelo.png");
    bloco_6 = IMG_Load("Blocodegelo6.png");

    jogador_1_atual = jogador_1b;
    jogador_2_atual = jogador_2b;

//POSIÇÃO DOS JOGADORES NA TELA
    posicao_jogador_1.x = 1;
    posicao_jogador_1.y = 1;

    posicao_jogador_2.x = 13;
    posicao_jogador_2.y = 11;

//POSIÇÃO DOS JOGADORES NA MATRIZ
    mapa[1][1] = 0;
    mapa[1][2] = 0;
    mapa[2][1] = 0;

    mapa[11][13] = 0;
    mapa[10][13] = 0;
    mapa[11][12] = 0;

//MOVIMENTAÇÃO DOS JOGADORES
    while(gContinuar == 1)
    {
        teclado_atualizado(&estado_teclado);

        if (estado_teclado.key[SDLK_UP])
        {
            jogador_1_atual = jogador_1c;
            movimento_jogador(mapa, &posicao_jogador_1, cima);
        }
        if (estado_teclado.key[SDLK_DOWN])
        {
            jogador_1_atual = jogador_1b;
            movimento_jogador(mapa, &posicao_jogador_1, baixo);
        }
        if (estado_teclado.key[SDLK_RIGHT])
        {
            jogador_1_atual = jogador_1d;
            movimento_jogador(mapa, &posicao_jogador_1, direita);
        }
        if (estado_teclado.key[SDLK_LEFT])
        {
            jogador_1_atual = jogador_1e;
            movimento_jogador(mapa, &posicao_jogador_1, esquerda);
        }
        if (estado_teclado.key[SDLK_m])
        {
            criacao_bomba_j1 (mapa, tela);
        }

        if (estado_teclado.key[SDLK_w])
        {
            jogador_2_atual = jogador_2c;
            movimento_jogador(mapa, &posicao_jogador_2, cima);
        }
        if (estado_teclado.key[SDLK_s])
        {
            jogador_2_atual = jogador_2b;
            movimento_jogador(mapa, &posicao_jogador_2, baixo);
        }
        if (estado_teclado.key[SDLK_d])
        {
            jogador_2_atual = jogador_2d;
            movimento_jogador(mapa, &posicao_jogador_2, direita);
        }
        if (estado_teclado.key[SDLK_a])
        {
            jogador_2_atual = jogador_2e;
            movimento_jogador(mapa, &posicao_jogador_2, esquerda);
        }
        if (estado_teclado.key[SDLK_p])
        {
            criacao_bomba_j2(mapa, tela);
        }

        if (estado_teclado.key[SDLK_ESCAPE])
        {
            gContinuar = 0;
        }

        SDL_FillRect(tela,NULL,SDL_MapRGB(tela -> format,0,0,30));

//POSIÇÃO DO CENARIO NA TELA
        posicao_cenario.x = 0;
        posicao_cenario.y = 40;

        SDL_BlitSurface(cenario, NULL, tela, &posicao_cenario);

//CRIAÇÃO ANIMAÇÃO DOS BLOCOS E EFEITOS DE EXPLOSÃO
        for (i = 1; i < 11; i++)
        {
            for (j = 1; j < 15; j++)
            {
               posicao.x = j*tamanho_bloco;
               posicao.y = i*tamanho_bloco+24;

                switch(mapa[i][j])
                {
                    case 2:
                    SDL_BlitSurface(bloco, NULL, tela, &posicao);
                    break;

                    case 5:
                    SDL_BlitSurface(bomba_1, NULL, tela, &posicao);
                    break;

                    case 6:
                    SDL_BlitSurface(explosao_b, NULL, tela, &posicao);
                    break;

                    case 7:
                    SDL_BlitSurface(explosao_c, NULL, tela, &posicao);
                    break;

                    case 8:
                    SDL_BlitSurface(explosao_d, NULL, tela, &posicao);
                    break;

                    case 9:
                    SDL_BlitSurface(explosao_e, NULL, tela, &posicao);
                    break;

                    case 10:
                    SDL_BlitSurface(explosao_m, NULL, tela, &posicao);
                    break;

                    case 11:
                    SDL_BlitSurface(bomba_2, NULL, tela, &posicao);
                    break;

                    case 12:
                    SDL_BlitSurface(bloco_1, NULL, tela, &posicao);
                    break;

                    case 13:
                    SDL_BlitSurface(bloco_2, NULL, tela, &posicao);
                    break;

                    case 14:
                    SDL_BlitSurface(bloco_3, NULL, tela, &posicao);
                    break;

                    case 15:
                    SDL_BlitSurface(bloco_4, NULL, tela, &posicao);
                    break;

                    case 16:
                    SDL_BlitSurface(bloco_5, NULL, tela, &posicao);
                    break;

                    case 17:
                    SDL_BlitSurface(bloco_6, NULL, tela, &posicao);
                    break;

                    case 18:
                    SDL_BlitSurface(bomba_v1, NULL, tela, &posicao);
                    break;

                    case 19:
                    SDL_BlitSurface(bomba_v2, NULL, tela, &posicao);
                    break;
                }
            }
        }

        posicao.x = posicao_jogador_1.x*tamanho_bloco;
        posicao.y = posicao_jogador_1.y*tamanho_bloco;

        SDL_BlitSurface(jogador_1_atual,NULL,tela,&posicao);

        posicao_2.x = posicao_jogador_2.x*tamanho_bloco;
        posicao_2.y = posicao_jogador_2.y*tamanho_bloco;

        SDL_BlitSurface(jogador_2_atual,NULL,tela,&posicao_2);

//VELOCIDADE DE MOVIMENTO DOS JOGADORES
        usleep(150000);

        SDL_Flip(tela);
    }

    if(gContinuar == 5)//PLAYER 1
    {

        Mix_CloseAudio();
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
        Mix_Music *audio_vitoria = NULL;
        audio_vitoria = Mix_LoadMUS("AudioVitoria.mp3");
        Mix_PlayMusic(audio_vitoria, 0);

        SDL_Delay(10000);

        SDL_Flip(tela);

        gContinuar = 0;

    }
    else if (gContinuar == 6) //PLAYER 2
    {
        Mix_CloseAudio();
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
        Mix_Music *audio_vitoria = NULL;
        audio_vitoria = Mix_LoadMUS("AudioVitoria.mp3");
        Mix_PlayMusic(audio_vitoria, 0);

        SDL_Delay(10000);

        SDL_Flip(tela);

        gContinuar = 0;

    }
    else if (gContinuar == 7) //PLAYER 1
    {

        Mix_CloseAudio();
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
        Mix_Music *audio_vitoria = NULL;
        audio_vitoria = Mix_LoadMUS("AudioVitoria.mp3");
        Mix_PlayMusic(audio_vitoria, 0);

        SDL_Delay(10000);

        SDL_Flip(tela);

        gContinuar = 0;

    }
    else if (gContinuar == 8) //PLAYER 2
    {

        Mix_CloseAudio();
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
        Mix_Music *audio_vitoria = NULL;
        audio_vitoria = Mix_LoadMUS("AudioVitoria.mp3");
        Mix_PlayMusic(audio_vitoria, 0);

        SDL_Delay(10000);

        SDL_Flip(tela);

        gContinuar = 0;

    }

//LIBERAÇÃO DAS IMAGENS NA TELA
    SDL_FreeSurface(bloco);

    SDL_FreeSurface(jogador_1b);
    SDL_FreeSurface(jogador_1c);
    SDL_FreeSurface(jogador_1d);
    SDL_FreeSurface(jogador_1e);

    SDL_FreeSurface(jogador_2b);
    SDL_FreeSurface(jogador_2c);
    SDL_FreeSurface(jogador_2d);
    SDL_FreeSurface(jogador_2e);

    SDL_FreeSurface(bomba_v1);
    SDL_FreeSurface(bomba_v2);

    SDL_FreeSurface(bomba_1);
    SDL_FreeSurface(bomba_2);
    SDL_FreeSurface(explosao_b);
    SDL_FreeSurface(explosao_c);
    SDL_FreeSurface(explosao_d);
    SDL_FreeSurface(explosao_e);
    SDL_FreeSurface(explosao_m);

    SDL_FreeSurface(bloco_1);
    SDL_FreeSurface(bloco_2);
    SDL_FreeSurface(bloco_3);
    SDL_FreeSurface(bloco_4);
    SDL_FreeSurface(bloco_5);
    SDL_FreeSurface(bloco_6);
}

//COLISÃO DOS JOGADORES COM CENÁRIO,  BLOCOS E BOMBAS
void movimento_jogador(int **mapa, SDL_Rect *pos, int direcao)
{
    switch(direcao)
    {
        case cima:

        if (mapa[pos -> y - 1][pos -> x] == parede)
        {
            break;
        }
        if (mapa[pos -> y - 1][pos -> x] == bloco)
        {
            break;
        }
        if (mapa[pos -> y - 1][pos -> x] == bomba_1)
        {
            break;
        }
        if (mapa[pos -> y - 1][pos -> x] == bomba_2)
        {
            break;
        }
        if (mapa[pos -> y - 1][pos -> x] == bomba_v1)
        {
            break;
        }
        if (mapa[pos -> y - 1][pos -> x] == bomba_v2)
        {
            break;
        }

        pos-> y--;
        break;

        case baixo:

        if (mapa[pos -> y + 1][pos -> x] == parede)
        {
            break;
        }
        if (mapa[pos -> y + 1][pos -> x] == bloco)
        {
            break;
        }
        if (mapa[pos -> y + 1][pos -> x] == bomba_1)
        {
            break;
        }
        if (mapa[pos -> y + 1][pos -> x] == bomba_2)
        {
            break;
        }
        if (mapa[pos -> y + 1][pos -> x] == bomba_v1)
        {
            break;
        }
        if (mapa[pos -> y + 1][pos -> x] == bomba_v2)
        {
            break;
        }

        pos-> y++;
        break;

        case esquerda:

        if (mapa[pos -> y][pos -> x - 1] == parede)
        {
            break;
        }
        if (mapa[pos -> y][pos -> x - 1] == bloco)
        {
            break;
        }
        if (mapa[pos -> y][pos -> x - 1] == bomba_1)
        {
            break;
        }
        if (mapa[pos -> y][pos -> x - 1] == bomba_2)
        {
            break;
        }
        if (mapa[pos -> y][pos -> x - 1] == bomba_v1)
        {
            break;
        }
            if (mapa[pos -> y][pos -> x - 1] == bomba_v2)
        {
            break;
        }

        pos-> x--;
        break;

        case direita:

        if (mapa[pos -> y][pos -> x + 1] == parede)
        {
            break;
        }
        if (mapa[pos -> y][pos -> x + 1] == bloco)
        {
            break;
        }
        if (mapa[pos -> y][pos -> x + 1] == bomba_1)
        {
            break;
        }
        if (mapa[pos -> y][pos -> x + 1] == bomba_2)
        {
            break;
        }
        if (mapa[pos -> y][pos -> x + 1] == bomba_v1)
        {
            break;
        }
        if (mapa[pos -> y][pos -> x + 1] == bomba_v2)
        {
            break;
        }

        pos-> x++;
        break;
    }
}

//LIMITAÇÃO DAS BOMBAS DO JOGADOR 1
void criacao_bomba_j1 (int **mapa, SDL_Surface* tela)
{
    pthread_t limite_bomba_j1;

    j1.mapa_bomba_j1 = mapa;
    j1.tela_bomba_j1 = tela;

    pthread_create(&limite_bomba_j1, NULL, gerenciamento_bomba_j1, (void*)&j1);
}

//LIMITAÇÃO DAS BOMBAS DO JOGADOR 2
void criacao_bomba_j2 (int **mapa, SDL_Surface* tela)
{
    pthread_t limite_bomba_j2;

    j2.mapa_bomba_j2 = mapa;
    j2.tela_bomba_j2 = tela;

    pthread_create(&limite_bomba_j2, NULL, gerenciamento_bomba_j2, (void*)&j2);
}

// INTERAÇÃO DA BOMBA, JOGADOR 1, COM O CENÁRIO
void *gerenciamento_bomba_j1(void*arg)
{
    bomba_j1 *args = (bomba_j1*)arg;
    int **mapa_bomba_j1 = args -> mapa_bomba_j1;

    int a, b, z = 0;

    for(a = 1; a < 11; a++)
    {
        for (b = 1; b < 15; b++)
        {
            if (mapa_bomba_j1[a][b] == bomba_1 || mapa_bomba_j1[a][b] == bomba_v1)
            {
                    pthread_exit(NULL);
            }
        }
    }

    Mix_Music *explosao_bj1;
    explosao_bj1 = Mix_LoadWAV("ExplosaoB1.wav");

    Mix_Music *drop_bj1;
    drop_bj1 = Mix_LoadWAV("DropB1.wav");

    int jogador_1_linha = 0, jogador_2_linha = 0, jogador_1_coluna = 0, jogador_2_coluna = 0;
    int win_right = 0, win_left = 0, win_up = 0, win_down = 0;
    int lose_right = 0, lose_left = 0, lose_up = 0, lose_down = 0;

    int bloco_up = 0, bloco_down = 0, bloco_left = 0, bloco_right = 0;
    int bloco_soma = 0, up_linha = 0, up_coluna = 0, down_linha = 0, down_coluna = 0;
    int left_linha = 0, left_coluna = 0, right_linha = 0, right_coluna = 0;

    mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x] = bomba_1;

    Mix_PlayChannel(-1, drop_bj1, 0);


    for(a = 1; a < 11; a++)
    {
        for (b = 1; b < 15; b++)
        {
            if (mapa_bomba_j1[a][b] == 5)
            {
                mapa_bomba_j1[a][b] = 18;
                SDL_Delay(500);
                mapa_bomba_j1[a][b] = 5;
                SDL_Delay(500);
                mapa_bomba_j1[a][b] = 18;
                SDL_Delay(500);
                mapa_bomba_j1[a][b] = 5;
                SDL_Delay(500);
                mapa_bomba_j1[a][b] = 18;
                SDL_Delay(500);
                mapa_bomba_j1[a][b] = 5;
                SDL_Delay(500);

                Mix_PlayChannel(-1, explosao_bj1, 0);

            }
        }
    }

    for(a = 1; a < 11; a++)
    {
        for (b = 1; b < 15; b++)
        {
            if (mapa_bomba_j1[a][b] == 5)
            {
                mapa_bomba_j1[a][b] = 10;

                if (mapa_bomba_j1[a][b] == mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x])
                {
                    gVitoria = 200;

                    mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x] = 20;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x] = 21;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x] = 22;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x] = 23;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x] = 24;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x] = 0;

                    for (a = 1; a < 11; a++)
                    {
                        for (b = 1; b < 15; b++)
                        {
                            if (mapa_bomba_j1[a][b] == mapa_bomba_j1[posicao_jogador_2.y][posicao_jogador_2.x])
                            {
                                for (z = 0; z < 3; z++)
                                {
                                    mapa_bomba_j1[posicao_jogador_2.y-1][posicao_jogador_2.x] = 29;
                                    SDL_Delay(200);
                                    mapa_bomba_j1[posicao_jogador_2.y-1][posicao_jogador_2.x] = 30;
                                    SDL_Delay(200);
                                    mapa_bomba_j1[posicao_jogador_2.y-1][posicao_jogador_2.x] = 31;
                                    SDL_Delay(200);
                                    mapa_bomba_j1[posicao_jogador_2.y-1][posicao_jogador_2.x] = 32;
                                    SDL_Delay(200);
                                }
                            }
                        }
                    }
                }

                if (mapa_bomba_j1[a][b] == mapa_bomba_j1[posicao_jogador_2.y][posicao_jogador_2.x])
                {

                    gVitoria = 100;

                    mapa_bomba_j1[posicao_jogador_2.y][posicao_jogador_2.x] = 20;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_2.y][posicao_jogador_2.x] = 21;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_2.y][posicao_jogador_2.x] = 22;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_2.y][posicao_jogador_2.x] = 23;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_2.y][posicao_jogador_2.x] = 24;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x] = 0;

                    for (a = 1; a < 11; a++)
                    {
                        for (b = 1; b < 15; b++)
                        {
                            if (mapa_bomba_j1[a][b] == mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x])
                            {
                                for (z = 0; z < 3; z++)
                                {
                                    mapa_bomba_j1[posicao_jogador_1.y-1][posicao_jogador_1.x] = 29;
                                    SDL_Delay(200);
                                    mapa_bomba_j1[posicao_jogador_1.y-1][posicao_jogador_1.x] = 30;
                                    SDL_Delay(200);
                                    mapa_bomba_j1[posicao_jogador_1.y-1][posicao_jogador_1.x] = 31;
                                    SDL_Delay(200);
                                    mapa_bomba_j1[posicao_jogador_1.y-1][posicao_jogador_1.x] = 32;
                                    SDL_Delay(200);
                                }
                            }
                        }
                    }
                }

                if (mapa_bomba_j1[a+1][b] == 0)
                {
                    mapa_bomba_j1[a+1][b] = 6;
                }
                if (mapa_bomba_j1[a+1][b] == mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x])
                {
                    mapa_bomba_j1[a+1][b] = 6;

                    gVitoria = 200;

                    mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x] = 20;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x] = 21;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x] = 22;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x] = 23;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x] = 24;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x] = 0;

                    for (a = 1; a < 11; a++)
                    {
                        for (b = 1; b < 15; b++)
                        {
                            if (mapa_bomba_j1[a][b] == mapa_bomba_j1[posicao_jogador_2.y][posicao_jogador_2.x])
                            {
                                for (z = 0; z < 3; z++)
                                {
                                    mapa_bomba_j1[posicao_jogador_2.y-1][posicao_jogador_2.x] = 29;
                                    SDL_Delay(200);
                                    mapa_bomba_j1[posicao_jogador_2.y-1][posicao_jogador_2.x] = 30;
                                    SDL_Delay(200);
                                    mapa_bomba_j1[posicao_jogador_2.y-1][posicao_jogador_2.x] = 31;
                                    SDL_Delay(200);
                                    mapa_bomba_j1[posicao_jogador_2.y-1][posicao_jogador_2.x] = 32;
                                    SDL_Delay(200);
                                }
                            }
                        }
                    }
                }
                if (mapa_bomba_j1[a+1][b] == mapa_bomba_j1[posicao_jogador_2.y][posicao_jogador_2.x])
                {
                    mapa_bomba_j1[a+1][b] = 6;

                    gVitoria = 100;

                    mapa_bomba_j1[posicao_jogador_2.y][posicao_jogador_2.x] = 20;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_2.y][posicao_jogador_2.x] = 21;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_2.y][posicao_jogador_2.x] = 22;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_2.y][posicao_jogador_2.x] = 23;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_2.y][posicao_jogador_2.x] = 24;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x] = 0;

                    for (a = 1; a < 11; a++)
                    {
                        for (b = 1; b < 15; b++)
                        {
                            if (mapa_bomba_j1[a][b] == mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x])
                            {
                                for (z = 0; z < 3; z++)
                                {
                                    mapa_bomba_j1[posicao_jogador_1.y-1][posicao_jogador_1.x] = 29;
                                    SDL_Delay(200);
                                    mapa_bomba_j1[posicao_jogador_1.y-1][posicao_jogador_1.x] = 30;
                                    SDL_Delay(200);
                                    mapa_bomba_j1[posicao_jogador_1.y-1][posicao_jogador_1.x] = 31;
                                    SDL_Delay(200);
                                    mapa_bomba_j1[posicao_jogador_1.y-1][posicao_jogador_1.x] = 32;
                                    SDL_Delay(200);
                                }
                            }
                        }
                    }
                }
                if (mapa_bomba_j1[a+1][b] == 2)
                {
                    bloco_down = 5;
                    down_linha = a+1;
                    down_coluna = b;
                }

                if (mapa_bomba_j1[a-1][b] == 0)
                {
                    mapa_bomba_j1[a-1][b] = 7;
                }
                if (mapa_bomba_j1[a-1][b] == mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x])
                {
                    mapa_bomba_j1[a-1][b] = 7;

                    gVitoria = 200;

                    mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x] = 20;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x] = 21;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x] = 22;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x] = 23;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x] = 24;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x] = 0;

                    for (a = 1; a < 11; a++)
                    {
                        for (b = 1; b < 15; b++)
                        {
                            if (mapa_bomba_j1[a][b] == mapa_bomba_j1[posicao_jogador_2.y][posicao_jogador_2.x])
                            {
                                for (z = 0; z < 3; z++)
                                {
                                    mapa_bomba_j1[posicao_jogador_2.y-1][posicao_jogador_2.x] = 29;
                                    SDL_Delay(200);
                                    mapa_bomba_j1[posicao_jogador_2.y-1][posicao_jogador_2.x] = 30;
                                    SDL_Delay(200);
                                    mapa_bomba_j1[posicao_jogador_2.y-1][posicao_jogador_2.x] = 31;
                                    SDL_Delay(200);
                                    mapa_bomba_j1[posicao_jogador_2.y-1][posicao_jogador_2.x] = 32;
                                    SDL_Delay(200);
                                }
                            }
                        }
                    }
                }
                if (mapa_bomba_j1[a-1][b] == mapa_bomba_j1[posicao_jogador_2.y][posicao_jogador_2.x])
                {
                    mapa_bomba_j1[a-1][b] = 7;

                    gVitoria = 100;

                    mapa_bomba_j1[posicao_jogador_2.y][posicao_jogador_2.x] = 20;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_2.y][posicao_jogador_2.x] = 21;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_2.y][posicao_jogador_2.x] = 22;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_2.y][posicao_jogador_2.x] = 23;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_2.y][posicao_jogador_2.x] = 24;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x] = 0;

                    for (a = 1; a < 11; a++)
                    {
                        for (b = 1; b < 15; b++)
                        {
                            if (mapa_bomba_j1[a][b] == mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x])
                            {
                                for (z = 0; z < 3; z++)
                                {
                                    mapa_bomba_j1[posicao_jogador_1.y-1][posicao_jogador_1.x] = 29;
                                    SDL_Delay(200);
                                    mapa_bomba_j1[posicao_jogador_1.y-1][posicao_jogador_1.x] = 30;
                                    SDL_Delay(200);
                                    mapa_bomba_j1[posicao_jogador_1.y-1][posicao_jogador_1.x] = 31;
                                    SDL_Delay(200);
                                    mapa_bomba_j1[posicao_jogador_1.y-1][posicao_jogador_1.x] = 32;
                                    SDL_Delay(200);
                                }
                            }
                        }
                    }
                }
                if (mapa_bomba_j1[a-1][b] == 2)
                {
                    bloco_up = 3;
                    up_linha = a-1;
                    up_coluna = b;
                }

                if (mapa_bomba_j1[a][b+1] == 0)
                {
                    mapa_bomba_j1[a][b+1] = 8;
                }
                if (mapa_bomba_j1[a][b+1] == mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x])
                {
                    mapa_bomba_j1[a][b+1] = 8;

                    gVitoria = 200;

                    mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x] = 20;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x] = 21;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x] = 22;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x] = 23;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x] = 24;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x] = 0;

                    for (a = 1; a < 11; a++)
                    {
                        for (b = 1; b < 15; b++)
                        {
                            if (mapa_bomba_j1[a][b] == mapa_bomba_j1[posicao_jogador_2.y][posicao_jogador_2.x])
                            {
                                for (z = 0; z < 3; z++)
                                {
                                    mapa_bomba_j1[posicao_jogador_2.y-1][posicao_jogador_2.x] = 29;
                                    SDL_Delay(200);
                                    mapa_bomba_j1[posicao_jogador_2.y-1][posicao_jogador_2.x] = 30;
                                    SDL_Delay(200);
                                    mapa_bomba_j1[posicao_jogador_2.y-1][posicao_jogador_2.x] = 31;
                                    SDL_Delay(200);
                                    mapa_bomba_j1[posicao_jogador_2.y-1][posicao_jogador_2.x] = 32;
                                    SDL_Delay(200);
                                }
                            }
                        }
                    }
                }
                if (mapa_bomba_j1[a][b+1] == mapa_bomba_j1[posicao_jogador_2.y][posicao_jogador_2.x])
                {
                    mapa_bomba_j1[a][b+1] = 8;

                    gVitoria = 100;

                    mapa_bomba_j1[posicao_jogador_2.y][posicao_jogador_2.x] = 20;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_2.y][posicao_jogador_2.x] = 21;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_2.y][posicao_jogador_2.x] = 22;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_2.y][posicao_jogador_2.x] = 23;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_2.y][posicao_jogador_2.x] = 24;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x] = 0;

                    for (a = 1; a < 11; a++)
                    {
                        for (b = 1; b < 15; b++)
                        {
                            if (mapa_bomba_j1[a][b] == mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x])
                            {
                                for (z = 0; z < 3; z++)
                                {
                                    mapa_bomba_j1[posicao_jogador_1.y-1][posicao_jogador_1.x] = 29;
                                    SDL_Delay(200);
                                    mapa_bomba_j1[posicao_jogador_1.y-1][posicao_jogador_1.x] = 30;
                                    SDL_Delay(200);
                                    mapa_bomba_j1[posicao_jogador_1.y-1][posicao_jogador_1.x] = 31;
                                    SDL_Delay(200);
                                    mapa_bomba_j1[posicao_jogador_1.y-1][posicao_jogador_1.x] = 32;
                                    SDL_Delay(200);
                                }
                            }
                        }
                    }
                }
                if (mapa_bomba_j1[a][b+1] == 2)
                {
                    bloco_right = 11;
                    right_linha = a;
                    right_coluna = b+1;
                }

                if (mapa_bomba_j1[a][b-1] == 0)
                {
                    mapa_bomba_j1[a][b-1] = 9;
                }
                if (mapa_bomba_j1[a][b-1] == mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x])
                {
                    mapa_bomba_j1[a][b-1] = 9;

                    gVitoria = 200;

                    mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x] = 20;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x] = 21;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x] = 22;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x] = 23;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x] = 24;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x] = 0;

                    for (a = 1; a < 11; a++)
                    {
                        for (b = 1; b < 15; b++)
                        {
                            if (mapa_bomba_j1[a][b] == mapa_bomba_j1[posicao_jogador_2.y][posicao_jogador_2.x])
                            {
                                for (z = 0; z < 3; z++)
                                {
                                    mapa_bomba_j1[posicao_jogador_2.y-1][posicao_jogador_2.x] = 29;
                                    SDL_Delay(200);
                                    mapa_bomba_j1[posicao_jogador_2.y-1][posicao_jogador_2.x] = 30;
                                    SDL_Delay(200);
                                    mapa_bomba_j1[posicao_jogador_2.y-1][posicao_jogador_2.x] = 31;
                                    SDL_Delay(200);
                                    mapa_bomba_j1[posicao_jogador_2.y-1][posicao_jogador_2.x] = 32;
                                    SDL_Delay(200);
                                }
                            }
                        }
                    }
                }
                if (mapa_bomba_j1[a][b-1] == mapa_bomba_j1[posicao_jogador_2.y][posicao_jogador_2.x])
                {
                    mapa_bomba_j1[a][b-1] = 9;

                    gVitoria = 100;

                    mapa_bomba_j1[posicao_jogador_2.y][posicao_jogador_2.x] = 20;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_2.y][posicao_jogador_2.x] = 21;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_2.y][posicao_jogador_2.x] = 22;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_2.y][posicao_jogador_2.x] = 23;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_2.y][posicao_jogador_2.x] = 24;
                    SDL_Delay(100);
                    mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x] = 0;

                    for (a = 1; a < 11; a++)
                    {
                        for (b = 1; b < 15; b++)
                        {
                            if (mapa_bomba_j1[a][b] == mapa_bomba_j1[posicao_jogador_1.y][posicao_jogador_1.x])
                            {
                                for (z = 0; z < 3; z++)
                                {
                                    mapa_bomba_j1[posicao_jogador_1.y-1][posicao_jogador_1.x] = 29;
                                    SDL_Delay(200);
                                    mapa_bomba_j1[posicao_jogador_1.y-1][posicao_jogador_1.x] = 30;
                                    SDL_Delay(200);
                                    mapa_bomba_j1[posicao_jogador_1.y-1][posicao_jogador_1.x] = 31;
                                    SDL_Delay(200);
                                    mapa_bomba_j1[posicao_jogador_1.y-1][posicao_jogador_1.x] = 32;
                                    SDL_Delay(200);
                                }
                            }
                        }
                    }
                }
                if (mapa_bomba_j1[a][b-1] == 2)
                {
                    bloco_left = 7;
                    left_linha = a;
                    left_coluna = b-1;
                }
            }
        }
    }

//ANIMAÇÃO BLOCOS SENDO DESTRUIDOS

    bloco_soma = bloco_down + bloco_left + bloco_right + bloco_up;

    switch (bloco_soma)
    {
        case 3:
        mapa_bomba_j1[up_linha][up_coluna] = 12;
        SDL_Delay(50);

        mapa_bomba_j1[up_linha][up_coluna] = 13;
        SDL_Delay(50);

        mapa_bomba_j1[up_linha][up_coluna] = 14;
        SDL_Delay(50);

        mapa_bomba_j1[up_linha][up_coluna] = 15;
        SDL_Delay(50);

        mapa_bomba_j1[up_linha][up_coluna] = 16;
        SDL_Delay(50);

        mapa_bomba_j1[up_linha][up_coluna] = 17;
        SDL_Delay(50);

        mapa_bomba_j1[up_linha][up_coluna] = 0;

        bloco_soma = 0, bloco_down = 0, bloco_left = 0;
        bloco_right = 0, bloco_up = 0, up_linha = 0, up_coluna = 0;
        right_coluna = 0, right_linha = 0, down_coluna = 0, down_linha = 0;
        left_linha = 0, left_coluna = 0;
        break;

        case 5:
        mapa_bomba_j1[down_linha][down_coluna] = 12;
        SDL_Delay(50);

        mapa_bomba_j1[down_linha][down_coluna] = 13;
        SDL_Delay(50);

        mapa_bomba_j1[down_linha][down_coluna] = 14;
        SDL_Delay(50);

        mapa_bomba_j1[down_linha][down_coluna] = 15;
        SDL_Delay(50);

        mapa_bomba_j1[down_linha][down_coluna] = 16;
        SDL_Delay(50);

        mapa_bomba_j1[down_linha][down_coluna] = 17;
        SDL_Delay(50);

        mapa_bomba_j1[down_linha][down_coluna] = 0;

        bloco_soma = 0, bloco_down = 0, bloco_left = 0;
        bloco_right = 0, bloco_up = 0, up_linha = 0, up_coluna = 0;
        right_coluna = 0, right_linha = 0, down_coluna = 0, down_linha = 0;
        left_linha = 0, left_coluna = 0;
        break;

        case 7:
        mapa_bomba_j1[left_linha][left_coluna] = 12;
        SDL_Delay(50);

        mapa_bomba_j1[left_linha][left_coluna]= 13;
        SDL_Delay(50);

        mapa_bomba_j1[left_linha][left_coluna] = 14;
        SDL_Delay(50);

        mapa_bomba_j1[left_linha][left_coluna] = 15;
        SDL_Delay(50);

        mapa_bomba_j1[left_linha][left_coluna] = 16;
        SDL_Delay(50);

        mapa_bomba_j1[left_linha][left_coluna] = 17;
        SDL_Delay(50);

        mapa_bomba_j1[left_linha][left_coluna] = 0;

        bloco_soma = 0, bloco_down = 0, bloco_left = 0;
        bloco_right = 0, bloco_up = 0, up_linha = 0, up_coluna = 0;
        right_coluna = 0, right_linha = 0, down_coluna = 0, down_linha = 0;
        left_linha = 0, left_coluna = 0;
        break;

        case 8:
        mapa_bomba_j1[up_linha][up_coluna] = 12;
        mapa_bomba_j1[down_linha][down_coluna] = 12;
        SDL_Delay(50);

        mapa_bomba_j1[up_linha][up_coluna] = 13;
        mapa_bomba_j1[down_linha][down_coluna] = 13;
        SDL_Delay(50);

        mapa_bomba_j1[up_linha][up_coluna] = 14;
        mapa_bomba_j1[down_linha][down_coluna] = 14;
        SDL_Delay(50);

        mapa_bomba_j1[up_linha][up_coluna] = 15;
        mapa_bomba_j1[down_linha][down_coluna] = 15;
        SDL_Delay(50);

        mapa_bomba_j1[up_linha][up_coluna] = 16;
        mapa_bomba_j1[down_linha][down_coluna] = 16;
        SDL_Delay(50);

        mapa_bomba_j1[up_linha][up_coluna] = 17;
        mapa_bomba_j1[down_linha][down_coluna] = 17;
        SDL_Delay(50);

        mapa_bomba_j1[up_linha][up_coluna] = 0;
        mapa_bomba_j1[down_linha][down_coluna] = 0;

        bloco_soma = 0, bloco_down = 0, bloco_left = 0;
        bloco_right = 0, bloco_up = 0, up_linha = 0, up_coluna = 0;
        right_coluna = 0, right_linha = 0, down_coluna = 0, down_linha = 0;
        left_linha = 0, left_coluna = 0;
        break;

        case 10:
        mapa_bomba_j1[up_linha][up_coluna] = 12;
        mapa_bomba_j1[left_linha][left_coluna] = 12;
        SDL_Delay(50);

        mapa_bomba_j1[up_linha][up_coluna] = 13;
        mapa_bomba_j1[left_linha][left_coluna] = 13;
        SDL_Delay(50);

        mapa_bomba_j1[up_linha][up_coluna] = 14;
        mapa_bomba_j1[left_linha][left_coluna] = 14;
        SDL_Delay(50);

        mapa_bomba_j1[up_linha][up_coluna] = 15;
        mapa_bomba_j1[left_linha][left_coluna] = 15;
        SDL_Delay(50);

        mapa_bomba_j1[up_linha][up_coluna] = 16;
        mapa_bomba_j1[left_linha][left_coluna] = 16;
        SDL_Delay(50);

        mapa_bomba_j1[up_linha][up_coluna] = 17;
        mapa_bomba_j1[left_linha][left_coluna] = 17;
        SDL_Delay(50);

        mapa_bomba_j1[up_linha][up_coluna] = 0;
        mapa_bomba_j1[left_linha][left_coluna] = 0;

        bloco_soma = 0, bloco_down = 0, bloco_left = 0;
        bloco_right = 0, bloco_up = 0, up_linha = 0, up_coluna = 0;
        right_coluna = 0, right_linha = 0, down_coluna = 0, down_linha = 0;
        left_linha = 0, left_coluna = 0;
        break;

        case 11:
        mapa_bomba_j1[right_linha][right_coluna] = 12;
        SDL_Delay(50);

        mapa_bomba_j1[right_linha][right_coluna] = 13;
        SDL_Delay(50);

        mapa_bomba_j1[right_linha][right_coluna] = 14;
        SDL_Delay(50);

        mapa_bomba_j1[right_linha][right_coluna] = 15;
        SDL_Delay(50);

        mapa_bomba_j1[right_linha][right_coluna] = 16;
        SDL_Delay(50);

        mapa_bomba_j1[right_linha][right_coluna] = 17;
        SDL_Delay(50);

        mapa_bomba_j1[right_linha][right_coluna] = 0;

        bloco_soma = 0, bloco_down = 0, bloco_left = 0;
        bloco_right = 0, bloco_up = 0, up_linha = 0, up_coluna = 0;
        right_coluna = 0, right_linha = 0, down_coluna = 0, down_linha = 0;
        left_linha = 0, left_coluna = 0;
        break;

        case 12:
        mapa_bomba_j1[down_linha][down_coluna] = 12;
        mapa_bomba_j1[left_linha][left_coluna] = 12;
        SDL_Delay(50);

        mapa_bomba_j1[down_linha][down_coluna] = 13;
        mapa_bomba_j1[left_linha][left_coluna] = 13;
        SDL_Delay(50);

        mapa_bomba_j1[down_linha][down_coluna] = 14;
        mapa_bomba_j1[left_linha][left_coluna] = 14;
        SDL_Delay(50);

        mapa_bomba_j1[down_linha][down_coluna] = 15;
        mapa_bomba_j1[left_linha][left_coluna] = 15;
        SDL_Delay(50);

        mapa_bomba_j1[down_linha][down_coluna] = 16;
        mapa_bomba_j1[left_linha][left_coluna] = 16;
        SDL_Delay(50);

        mapa_bomba_j1[down_linha][down_coluna] = 17;
        mapa_bomba_j1[left_linha][left_coluna] = 17;
        SDL_Delay(50);

        mapa_bomba_j1[down_linha][down_coluna] = 0;
        mapa_bomba_j1[left_linha][left_coluna] = 0;

        bloco_soma = 0, bloco_down = 0, bloco_left = 0;
        bloco_right = 0, bloco_up = 0, up_linha = 0, up_coluna = 0;
        right_coluna = 0, right_linha = 0, down_coluna = 0, down_linha = 0;
        left_linha = 0, left_coluna = 0;
        break;

        case 14:
        mapa_bomba_j1[right_linha][right_coluna] = 12;
        mapa_bomba_j1[up_linha][up_coluna] = 12;
        SDL_Delay(50);

        mapa_bomba_j1[right_linha][right_coluna] = 13;
        mapa_bomba_j1[up_linha][up_coluna] = 13;
        SDL_Delay(50);

        mapa_bomba_j1[right_linha][right_coluna] = 14;
        mapa_bomba_j1[up_linha][up_coluna] = 14;
        SDL_Delay(50);

        mapa_bomba_j1[right_linha][right_coluna] = 15;
        mapa_bomba_j1[up_linha][up_coluna] = 15;
        SDL_Delay(50);

        mapa_bomba_j1[right_linha][right_coluna] = 16;
        mapa_bomba_j1[up_linha][up_coluna] = 16;
        SDL_Delay(50);

        mapa_bomba_j1[right_linha][right_coluna] = 17;
        mapa_bomba_j1[up_linha][up_coluna] = 17;
        SDL_Delay(50);

        mapa_bomba_j1[right_linha][right_coluna] = 0;
        mapa_bomba_j1[up_linha][up_coluna] = 0;

        bloco_soma = 0, bloco_down = 0, bloco_left = 0;
        bloco_right = 0, bloco_up = 0, up_linha = 0, up_coluna = 0;
        right_coluna = 0, right_linha = 0, down_coluna = 0, down_linha = 0;
        left_linha = 0, left_coluna = 0;
        break;

        case 15:
        mapa_bomba_j1[up_linha][up_coluna] = 12;
        mapa_bomba_j1[down_linha][down_coluna] = 12;
        mapa_bomba_j1[left_linha][left_coluna] = 12;
        SDL_Delay(50);

        mapa_bomba_j1[up_linha][up_coluna] = 13;
        mapa_bomba_j1[down_linha][down_coluna] = 13;
        mapa_bomba_j1[left_linha][left_coluna] = 13;
        SDL_Delay(50);

        mapa_bomba_j1[up_linha][up_coluna] = 14;
        mapa_bomba_j1[down_linha][down_coluna] = 14;
        mapa_bomba_j1[left_linha][left_coluna] = 14;
        SDL_Delay(50);

        mapa_bomba_j1[up_linha][up_coluna] = 15;
        mapa_bomba_j1[down_linha][down_coluna] = 15;
        mapa_bomba_j1[left_linha][left_coluna] = 15;
        SDL_Delay(50);

        mapa_bomba_j1[up_linha][up_coluna] = 16;
        mapa_bomba_j1[down_linha][down_coluna] = 16;
        mapa_bomba_j1[left_linha][left_coluna] = 16;
        SDL_Delay(50);

        mapa_bomba_j1[up_linha][up_coluna] = 17;
        mapa_bomba_j1[down_linha][down_coluna] = 17;
        mapa_bomba_j1[left_linha][left_coluna] = 17;
        SDL_Delay(50);

        mapa_bomba_j1[up_linha][up_coluna] = 0;
        mapa_bomba_j1[down_linha][down_coluna] = 0;
        mapa_bomba_j1[left_linha][left_coluna] = 0;

        bloco_soma = 0, bloco_down = 0, bloco_left = 0;
        bloco_right = 0, bloco_up = 0, up_linha = 0, up_coluna = 0;
        right_coluna = 0, right_linha = 0, down_coluna = 0, down_linha = 0;
        left_linha = 0, left_coluna = 0;
        break;

        case 16:
        mapa_bomba_j1[right_linha][right_coluna] = 12;
        mapa_bomba_j1[down_linha][down_coluna] = 12;
        SDL_Delay(50);

        mapa_bomba_j1[right_linha][right_coluna] = 13;
        mapa_bomba_j1[down_linha][down_coluna] = 13;
        SDL_Delay(50);

        mapa_bomba_j1[right_linha][right_coluna] = 14;
        mapa_bomba_j1[down_linha][down_coluna] = 14;
        SDL_Delay(50);

        mapa_bomba_j1[right_linha][right_coluna] = 15;
        mapa_bomba_j1[down_linha][down_coluna] = 15;
        SDL_Delay(50);

        mapa_bomba_j1[right_linha][right_coluna] = 16;
        mapa_bomba_j1[down_linha][down_coluna] = 16;
        SDL_Delay(50);

        mapa_bomba_j1[right_linha][right_coluna] = 17;
        mapa_bomba_j1[down_linha][down_coluna] = 17;
        SDL_Delay(50);

        mapa_bomba_j1[right_linha][right_coluna] = 0;
        mapa_bomba_j1[down_linha][down_coluna] = 0;

        bloco_soma = 0, bloco_down = 0, bloco_left = 0;
        bloco_right = 0, bloco_up = 0, up_linha = 0, up_coluna = 0;
        right_coluna = 0, right_linha = 0, down_coluna = 0, down_linha = 0;
        left_linha = 0, left_coluna = 0;
        break;

        case 18:
        mapa_bomba_j1[right_linha][right_coluna] = 12;
        mapa_bomba_j1[left_linha][left_coluna] = 12;
        SDL_Delay(50);

        mapa_bomba_j1[right_linha][right_coluna] = 13;
        mapa_bomba_j1[left_linha][left_coluna] = 13;
        SDL_Delay(50);

        mapa_bomba_j1[right_linha][right_coluna] = 14;
        mapa_bomba_j1[left_linha][left_coluna] = 14;
        SDL_Delay(50);

        mapa_bomba_j1[right_linha][right_coluna] = 15;
        mapa_bomba_j1[left_linha][left_coluna] = 15;
        SDL_Delay(50);

        mapa_bomba_j1[right_linha][right_coluna] = 16;
        mapa_bomba_j1[left_linha][left_coluna] = 16;
        SDL_Delay(50);

        mapa_bomba_j1[right_linha][right_coluna] = 17;
        mapa_bomba_j1[left_linha][left_coluna] = 17;
        SDL_Delay(50);

        mapa_bomba_j1[right_linha][right_coluna] = 0;
        mapa_bomba_j1[left_linha][left_coluna] = 0;

        bloco_soma = 0, bloco_down = 0, bloco_left = 0;
        bloco_right = 0, bloco_up = 0, up_linha = 0, up_coluna = 0;
        right_coluna = 0, right_linha = 0, down_coluna = 0, down_linha = 0;
        left_linha = 0, left_coluna = 0;
        break;

        case 19:
        mapa_bomba_j1[up_linha][up_coluna] = 12;
        mapa_bomba_j1[down_linha][down_coluna] = 12;
        mapa_bomba_j1[right_linha][right_coluna] = 12;
        SDL_Delay(50);

        mapa_bomba_j1[up_linha][up_coluna] = 13;
        mapa_bomba_j1[down_linha][down_coluna] = 13;
        mapa_bomba_j1[right_linha][right_coluna] = 13;
        SDL_Delay(50);

        mapa_bomba_j1[up_linha][up_coluna] = 14;
        mapa_bomba_j1[down_linha][down_coluna] = 14;
        mapa_bomba_j1[right_linha][right_coluna] = 14;
        SDL_Delay(50);

        mapa_bomba_j1[up_linha][up_coluna] = 15;
        mapa_bomba_j1[down_linha][down_coluna] = 15;
        mapa_bomba_j1[right_linha][right_coluna] = 15;
        SDL_Delay(50);

        mapa_bomba_j1[up_linha][up_coluna] = 16;
        mapa_bomba_j1[down_linha][down_coluna] = 16;
        mapa_bomba_j1[right_linha][right_coluna] = 16;
        SDL_Delay(50);

        mapa_bomba_j1[up_linha][up_coluna] = 17;
        mapa_bomba_j1[down_linha][down_coluna] = 17;
        mapa_bomba_j1[right_linha][right_coluna] = 17;
        SDL_Delay(50);

        mapa_bomba_j1[up_linha][up_coluna] = 0;
        mapa_bomba_j1[down_linha][down_coluna] = 0;
        mapa_bomba_j1[right_linha][right_coluna] = 0;

        bloco_soma = 0, bloco_down = 0, bloco_left = 0;
        bloco_right = 0, bloco_up = 0, up_linha = 0, up_coluna = 0;
        right_coluna = 0, right_linha = 0, down_coluna = 0, down_linha = 0;
        left_linha = 0, left_coluna = 0;
        break;

        case 21:
        mapa_bomba_j1[up_linha][up_coluna] = 12;
        mapa_bomba_j1[left_linha][left_coluna] = 12;
        mapa_bomba_j1[right_linha][right_coluna] = 12;
        SDL_Delay(50);

        mapa_bomba_j1[up_linha][up_coluna] = 13;
        mapa_bomba_j1[left_linha][left_coluna] = 13;
        mapa_bomba_j1[right_linha][right_coluna] = 13;
        SDL_Delay(50);

        mapa_bomba_j1[up_linha][up_coluna] = 14;
        mapa_bomba_j1[left_linha][left_coluna] = 14;
        mapa_bomba_j1[right_linha][right_coluna] = 14;
        SDL_Delay(50);

        mapa_bomba_j1[up_linha][up_coluna] = 15;
        mapa_bomba_j1[left_linha][left_coluna] = 15;
        mapa_bomba_j1[right_linha][right_coluna] = 15;
        SDL_Delay(50);

        mapa_bomba_j1[up_linha][up_coluna] = 16;
        mapa_bomba_j1[left_linha][left_coluna] = 16;
        mapa_bomba_j1[right_linha][right_coluna] = 16;
        SDL_Delay(50);

        mapa_bomba_j1[up_linha][up_coluna] = 17;
        mapa_bomba_j1[left_linha][left_coluna] = 17;
        mapa_bomba_j1[right_linha][right_coluna] = 17;
        SDL_Delay(50);

        mapa_bomba_j1[up_linha][up_coluna] = 0;
        mapa_bomba_j1[left_linha][left_coluna] = 0;
        mapa_bomba_j1[right_linha][right_coluna] = 0;

        bloco_soma = 0, bloco_down = 0, bloco_left = 0;
        bloco_right = 0, bloco_up = 0, up_linha = 0, up_coluna = 0;
        right_coluna = 0, right_linha = 0, down_coluna = 0, down_linha = 0;
        left_linha = 0, left_coluna = 0;
        break;

        case 23:
        mapa_bomba_j1[down_linha][down_coluna] = 12;
        mapa_bomba_j1[left_linha][left_coluna] = 12;
        mapa_bomba_j1[right_linha][right_coluna] = 12;
        SDL_Delay(50);

        mapa_bomba_j1[down_linha][down_coluna] = 13;
        mapa_bomba_j1[left_linha][left_coluna] = 13;
        mapa_bomba_j1[right_linha][right_coluna] = 13;
        SDL_Delay(50);

        mapa_bomba_j1[down_linha][down_coluna] = 14;
        mapa_bomba_j1[left_linha][left_coluna] = 14;
        mapa_bomba_j1[right_linha][right_coluna] = 14;
        SDL_Delay(50);

        mapa_bomba_j1[down_linha][down_coluna] = 15;
        mapa_bomba_j1[left_linha][left_coluna] = 15;
        mapa_bomba_j1[right_linha][right_coluna] = 15;
        SDL_Delay(50);

        mapa_bomba_j1[down_linha][down_coluna] = 16;
        mapa_bomba_j1[left_linha][left_coluna] = 16;
        mapa_bomba_j1[right_linha][right_coluna] = 16;
        SDL_Delay(50);

        mapa_bomba_j1[down_linha][down_coluna] = 17;
        mapa_bomba_j1[left_linha][left_coluna] = 17;
        mapa_bomba_j1[right_linha][right_coluna] = 17;
        SDL_Delay(50);

        mapa_bomba_j1[down_linha][down_coluna] = 0;
        mapa_bomba_j1[left_linha][left_coluna] = 0;
        mapa_bomba_j1[right_linha][right_coluna] = 0;

        bloco_soma = 0, bloco_down = 0, bloco_left = 0;
        bloco_right = 0, bloco_up = 0, up_linha = 0, up_coluna = 0;
        right_coluna = 0, right_linha = 0, down_coluna = 0, down_linha = 0;
        left_linha = 0, left_coluna = 0;
        break;

        case 26:
        mapa_bomba_j1[up_linha][up_coluna] = 12;
        mapa_bomba_j1[down_linha][down_coluna] = 12;
        mapa_bomba_j1[left_linha][left_coluna] = 12;
        mapa_bomba_j1[right_linha][right_coluna] = 12;
        SDL_Delay(50);

        mapa_bomba_j1[up_linha][up_coluna] = 13;
        mapa_bomba_j1[down_linha][down_coluna] = 13;
        mapa_bomba_j1[left_linha][left_coluna] = 13;
        mapa_bomba_j1[right_linha][right_coluna] = 13;
        SDL_Delay(50);

        mapa_bomba_j1[up_linha][up_coluna] = 14;
        mapa_bomba_j1[down_linha][down_coluna] = 14;
        mapa_bomba_j1[left_linha][left_coluna] = 14;
        mapa_bomba_j1[right_linha][right_coluna] = 14;
        SDL_Delay(50);

        mapa_bomba_j1[up_linha][up_coluna] = 15;
        mapa_bomba_j1[down_linha][down_coluna] = 15;
        mapa_bomba_j1[left_linha][left_coluna] = 15;
        mapa_bomba_j1[right_linha][right_coluna] = 15;
        SDL_Delay(50);

        mapa_bomba_j1[up_linha][up_coluna] = 16;
        mapa_bomba_j1[down_linha][down_coluna] = 16;
        mapa_bomba_j1[left_linha][left_coluna] = 16;
        mapa_bomba_j1[right_linha][right_coluna] = 16;
        SDL_Delay(50);

        mapa_bomba_j1[up_linha][up_coluna] = 17;
        mapa_bomba_j1[down_linha][down_coluna] = 17;
        mapa_bomba_j1[left_linha][left_coluna] = 17;
        mapa_bomba_j1[right_linha][right_coluna] = 17;
        SDL_Delay(50);

        mapa_bomba_j1[up_linha][up_coluna] = 0;
        mapa_bomba_j1[down_linha][down_coluna] = 0;
        mapa_bomba_j1[left_linha][left_coluna] = 0;
        mapa_bomba_j1[right_linha][right_coluna] = 0;

        bloco_soma = 0, bloco_down = 0, bloco_left = 0;
        bloco_right = 0, bloco_up = 0, up_linha = 0, up_coluna = 0;
        right_coluna = 0, right_linha = 0, down_coluna = 0, down_linha = 0;
        left_linha = 0, left_coluna = 0;
        break;
    }

    SDL_Delay(150);

//LIMPAR ANIMAÇÃO DE EXPLOSÃO DA BOMBA
    for (a = 1; a < 11; a++)
    {
        for (b = 1; b < 15; b++)
        {
            if (mapa_bomba_j1[a][b] == 10)
            {
                mapa_bomba_j1[a][b] = 0;
            }
            if (mapa_bomba_j1[a][b] == 6)
            {
                mapa_bomba_j1[a][b] = 0;
            }
            if (mapa_bomba_j1[a][b] == 7)
            {
                mapa_bomba_j1[a][b] = 0;
            }
            if (mapa_bomba_j1[a][b] == 8)
            {
                mapa_bomba_j1[a][b] = 0;
            }
            if (mapa_bomba_j1[a][b] == 9)
            {
                mapa_bomba_j1[a][b] = 0;
            }
        }
    }

    if(gVitoria == 100)
    {
        gContinuar = 5;
    }
    if(gVitoria == 200)
    {
        gContinuar = 6;
    }

    pthread_exit(NULL);
}

// INTERAÇÃO DA BOMBA, JOGADOR 2, COM O CENÁRIO
void *gerenciamento_bomba_j2(void*arg)
{
    bomba_j2 *args = (bomba_j2*)arg;
    int **mapa_bomba_j2 = args -> mapa_bomba_j2;

    int a, b = 0;

    for(a = 1; a < 11; a++)
    {
        for (b = 1; b < 15; b++)
        {
            if (mapa_bomba_j2[a][b] == bomba_2)
            {
                pthread_exit(NULL);
            }
            if (mapa_bomba_j2[a][b] == bomba_v2)
            {
                pthread_exit(NULL);
            }
        }
    }

    Mix_Music *explosao_bj2;
    explosao_bj2 = Mix_LoadWAV("ExplosaoB1.wav");

    Mix_Music *drop_bj2;
    drop_bj2 = Mix_LoadWAV("DropB1.wav");

    int bloco_up_2 = 0, bloco_down_2 = 0, bloco_left_2 = 0, bloco_right_2 = 0;
    int bloco_soma_2 = 0, up_linha_2 = 0, up_coluna_2 = 0, down_linha_2 = 0, down_coluna_2 = 0;
    int left_linha_2 = 0, left_coluna_2 = 0, right_linha_2 = 0, right_coluna_2 = 0;

    mapa_bomba_j2[posicao_jogador_2.y][posicao_jogador_2.x] = bomba_2;

    Mix_PlayChannel(-1, drop_bj2, 0);

    for(a = 1; a < 11; a++)
    {
        for (b = 1; b < 15; b++)
        {
            if (mapa_bomba_j2[a][b] == 11)
            {
                mapa_bomba_j2[a][b] = 19;
                SDL_Delay(500);
                mapa_bomba_j2[a][b] = 11;
                SDL_Delay(500);
                mapa_bomba_j2[a][b] = 19;
                SDL_Delay(500);
                mapa_bomba_j2[a][b] = 11;
                SDL_Delay(500);
                mapa_bomba_j2[a][b] = 19;
                SDL_Delay(500);
                mapa_bomba_j2[a][b] = 11;
                SDL_Delay(500);

                Mix_PlayChannel(-1, explosao_bj2, 0);
            }
        }
    }

    for(a = 1; a < 11; a++)
    {
        for (b = 1; b < 15; b++)
        {
            if (mapa_bomba_j2[a][b] == 11)
            {
                mapa_bomba_j2[a][b] = 10;

                if (mapa_bomba_j2[a][b] == mapa_bomba_j2[posicao_jogador_1.y][posicao_jogador_1.x])
                {
                    gDerrota = 100;
                }
                if (mapa_bomba_j2[a][b] == mapa_bomba_j2[posicao_jogador_2.y][posicao_jogador_2.x])
                {
                    gDerrota = 200;
                }

                if (mapa_bomba_j2[a+1][b] == 0)
                {
                    mapa_bomba_j2[a+1][b] = 6;
                }
                if (mapa_bomba_j2[a+1][b] == mapa_bomba_j2[posicao_jogador_1.y][posicao_jogador_1.x])
                {
                    mapa_bomba_j2[a+1][b] = 6;

                    gDerrota = 100;
                }
                if (mapa_bomba_j2[a+1][b] == mapa_bomba_j2[posicao_jogador_2.y][posicao_jogador_2.x])
                {
                    mapa_bomba_j2[a+1][b] = 6;

                    gDerrota = 200;
                }
                if (mapa_bomba_j2[a+1][b] == 2)
                {
                    bloco_down_2 = 5;
                    down_linha_2 = a+1;
                    down_coluna_2 = b;
                }

                if (mapa_bomba_j2[a-1][b] == 0)
                {
                    mapa_bomba_j2[a-1][b] = 7;
                }
                if (mapa_bomba_j2[a-1][b] == mapa_bomba_j2[posicao_jogador_1.y][posicao_jogador_1.x])
                {
                    mapa_bomba_j2[a-1][b] = 7;

                    gDerrota = 100;
                }
                if (mapa_bomba_j2[a-1][b] == mapa_bomba_j2[posicao_jogador_2.y][posicao_jogador_2.x])
                {
                    mapa_bomba_j2[a-1][b] = 7;

                    gDerrota = 200;
                }
                if (mapa_bomba_j2[a-1][b] == 2)
                {
                    bloco_up_2 = 3;
                    up_linha_2 = a-1;
                    up_coluna_2 = b;
                }

                if (mapa_bomba_j2[a][b+1] == 0)
                {
                    mapa_bomba_j2[a][b+1] = 8;
                }
                if (mapa_bomba_j2[a][b+1] == mapa_bomba_j2[posicao_jogador_1.y][posicao_jogador_1.x])
                {
                    mapa_bomba_j2[a][b+1] = 8;

                    gDerrota = 100;
                }
                if (mapa_bomba_j2[a][b+1] == mapa_bomba_j2[posicao_jogador_2.y][posicao_jogador_2.x])
                {
                    mapa_bomba_j2[a][b+1] = 8;

                    gDerrota = 200;
                }
                if (mapa_bomba_j2[a][b+1] == 2)
                {
                    bloco_right_2 = 11;
                    right_linha_2 = a;
                    right_coluna_2 = b+1;
                }

                if (mapa_bomba_j2[a][b-1] == 0)
                {
                    mapa_bomba_j2[a][b-1] = 9;
                }
                if (mapa_bomba_j2[a][b-1] == mapa_bomba_j2[posicao_jogador_1.y][posicao_jogador_1.x])
                {
                    mapa_bomba_j2[a][b-1] = 9;

                    gDerrota = 100;
                }
                if (mapa_bomba_j2[a][b-1] == mapa_bomba_j2[posicao_jogador_2.y][posicao_jogador_2.x])
                {
                    mapa_bomba_j2[a][b-1] = 9;

                    gDerrota = 200;
                }
                if (mapa_bomba_j2[a][b-1] == 2)
                {
                    mapa_bomba_j2[a][b-1] = 9;

                    bloco_left_2 = 7;
                    left_linha_2 = a;
                    left_coluna_2 = b-1;
                }
            }
        }
    }
    SDL_Delay(150);

//ANIMAÇÃO BLOCOS SENDO DESTRUIDOS JOGADOR 2

    bloco_soma_2 = bloco_down_2 + bloco_left_2 + bloco_right_2 + bloco_up_2;

    switch (bloco_soma_2)
    {
        case 3:
        mapa_bomba_j2[up_linha_2][up_coluna_2] = 12; //12
        SDL_Delay(50);

        mapa_bomba_j2[up_linha_2][up_coluna_2] = 13; //13
        SDL_Delay(50);

        mapa_bomba_j2[up_linha_2][up_coluna_2] = 14; //14
        SDL_Delay(50);

        mapa_bomba_j2[up_linha_2][up_coluna_2] = 15; //15
        SDL_Delay(50);

        mapa_bomba_j2[up_linha_2][up_coluna_2] = 16; //16
        SDL_Delay(50);

        mapa_bomba_j2[up_linha_2][up_coluna_2] = 17; //17
        SDL_Delay(50);

        mapa_bomba_j2[up_linha_2][up_coluna_2] = 0;

        bloco_soma_2 = 0, bloco_down_2 = 0, bloco_left_2 = 0;
        bloco_right_2 = 0, bloco_up_2 = 0, up_linha_2 = 0, up_coluna_2 = 0;
        right_coluna_2 = 0, right_linha_2 = 0, down_coluna_2 = 0, down_linha_2 = 0;
        left_coluna_2 = 0, left_linha_2 = 0;
        break;

        case 5:
        mapa_bomba_j2[down_linha_2][down_coluna_2] = 12; //12
        SDL_Delay(50);

        mapa_bomba_j2[down_linha_2][down_coluna_2] = 13; //13
        SDL_Delay(50);

        mapa_bomba_j2[down_linha_2][down_coluna_2] = 14; //14
        SDL_Delay(50);

        mapa_bomba_j2[down_linha_2][down_coluna_2] = 15; //15
        SDL_Delay(50);

        mapa_bomba_j2[down_linha_2][down_coluna_2] = 16; //16
        SDL_Delay(50);

        mapa_bomba_j2[down_linha_2][down_coluna_2] = 17; //17
        SDL_Delay(50);

        mapa_bomba_j2[down_linha_2][down_coluna_2] = 0;

        bloco_soma_2 = 0, bloco_down_2 = 0, bloco_left_2 = 0;
        bloco_right_2 = 0, bloco_up_2 = 0, up_linha_2 = 0, up_coluna_2 = 0;
        right_coluna_2 = 0, right_linha_2 = 0, down_coluna_2 = 0, down_linha_2 = 0;
        left_coluna_2 = 0, left_linha_2 = 0;
        break;

        case 7:
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 12; //12
        SDL_Delay(50);

        mapa_bomba_j2[left_linha_2][left_coluna_2] = 13; //13
        SDL_Delay(50);

        mapa_bomba_j2[left_linha_2][left_coluna_2] = 14; //14
        SDL_Delay(50);

        mapa_bomba_j2[left_linha_2][left_coluna_2] = 15; //15
        SDL_Delay(50);

        mapa_bomba_j2[left_linha_2][left_coluna_2] = 16; //16
        SDL_Delay(50);

        mapa_bomba_j2[left_linha_2][left_coluna_2] = 17; //17
        SDL_Delay(50);

        mapa_bomba_j2[left_linha_2][left_coluna_2] = 0;

        bloco_soma_2 = 0, bloco_down_2 = 0, bloco_left_2 = 0;
        bloco_right_2 = 0, bloco_up_2 = 0, up_linha_2 = 0, up_coluna_2 = 0;
        right_coluna_2 = 0, right_linha_2 = 0, down_coluna_2 = 0, down_linha_2 = 0;
        left_coluna_2 = 0, left_linha_2 = 0;
        break;

        case 8:
        mapa_bomba_j2[up_linha_2][up_coluna_2] = 12; //12
        mapa_bomba_j2[down_linha_2][down_coluna_2] = 12; //12
        SDL_Delay(50);

        mapa_bomba_j2[up_linha_2][up_coluna_2] = 13; //13
        mapa_bomba_j2[down_linha_2][down_coluna_2] = 13; //13
        SDL_Delay(50);

        mapa_bomba_j2[up_linha_2][up_coluna_2] = 14; //14
        mapa_bomba_j2[down_linha_2][down_coluna_2] = 14; //14
        SDL_Delay(50);

        mapa_bomba_j2[up_linha_2][up_coluna_2] = 15; //15
        mapa_bomba_j2[down_linha_2][down_coluna_2] = 15; //15
        SDL_Delay(50);

        mapa_bomba_j2[up_linha_2][up_coluna_2] = 16; //16
        mapa_bomba_j2[down_linha_2][down_coluna_2] = 16; //16
        SDL_Delay(50);

        mapa_bomba_j2[up_linha_2][up_coluna_2] = 17; //17
        mapa_bomba_j2[down_linha_2][down_coluna_2] = 17; //17
        SDL_Delay(50);

        mapa_bomba_j2[up_linha_2][up_coluna_2] = 0;
        mapa_bomba_j2[down_linha_2][down_coluna_2] = 0;

        bloco_soma_2 = 0, bloco_down_2 = 0, bloco_left_2 = 0;
        bloco_right_2 = 0, bloco_up_2 = 0, up_linha_2 = 0, up_coluna_2 = 0;
        right_coluna_2 = 0, right_linha_2 = 0, down_coluna_2 = 0, down_linha_2 = 0;
        left_coluna_2 = 0, left_linha_2 = 0;
        break;

        case 10:
        mapa_bomba_j2[up_linha_2][up_coluna_2] = 12; //12
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 12; //12
        SDL_Delay(50);

        mapa_bomba_j2[up_linha_2][up_coluna_2] = 13; //13
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 13; //13
        SDL_Delay(50);

        mapa_bomba_j2[up_linha_2][up_coluna_2] = 14; //14
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 14; //14
        SDL_Delay(50);

        mapa_bomba_j2[up_linha_2][up_coluna_2] = 15; //15
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 15; //15
        SDL_Delay(50);

        mapa_bomba_j2[up_linha_2][up_coluna_2] = 16; //16
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 16; //16
        SDL_Delay(50);

        mapa_bomba_j2[up_linha_2][up_coluna_2] = 17; //17
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 17; //17
        SDL_Delay(50);

        mapa_bomba_j2[up_linha_2][up_coluna_2] = 0;
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 0;

        bloco_soma_2 = 0, bloco_down_2 = 0, bloco_left_2 = 0;
        bloco_right_2 = 0, bloco_up_2 = 0, up_linha_2 = 0, up_coluna_2 = 0;
        right_coluna_2 = 0, right_linha_2 = 0, down_coluna_2 = 0, down_linha_2 = 0;
        left_coluna_2 = 0, left_linha_2 = 0;
        break;

        case 11:
        mapa_bomba_j2[right_linha_2][right_coluna_2] = 12; //12
        SDL_Delay(50);

        mapa_bomba_j2[right_linha_2][right_coluna_2] = 13; //13
        SDL_Delay(50);

        mapa_bomba_j2[right_linha_2][right_coluna_2] = 14; //14
        SDL_Delay(50);

        mapa_bomba_j2[right_linha_2][right_coluna_2] = 15; //15
        SDL_Delay(50);

        mapa_bomba_j2[right_linha_2][right_coluna_2] = 16; //16
        SDL_Delay(50);

        mapa_bomba_j2[right_linha_2][right_coluna_2] = 17; //17
        SDL_Delay(50);

        mapa_bomba_j2[right_linha_2][right_coluna_2] = 0;

        bloco_soma_2 = 0, bloco_down_2 = 0, bloco_left_2 = 0;
        bloco_right_2 = 0, bloco_up_2 = 0, up_linha_2 = 0, up_coluna_2 = 0;
        right_coluna_2 = 0, right_linha_2 = 0, down_coluna_2 = 0, down_linha_2 = 0;
        left_coluna_2 = 0, left_linha_2 = 0;
        break;

        case 12:
        mapa_bomba_j2[down_linha_2][down_coluna_2] = 12; //12
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 12; //12
        SDL_Delay(50);

        mapa_bomba_j2[down_linha_2][down_coluna_2] = 13; //13
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 13; //13
        SDL_Delay(50);

        mapa_bomba_j2[down_linha_2][down_coluna_2] = 14; //14
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 14; //14
        SDL_Delay(50);

        mapa_bomba_j2[down_linha_2][down_coluna_2] = 15; //15
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 15; //15
        SDL_Delay(50);

        mapa_bomba_j2[down_linha_2][down_coluna_2] = 16; //16
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 16; //16
        SDL_Delay(50);

        mapa_bomba_j2[down_linha_2][down_coluna_2] = 17; //17
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 17; //17
        SDL_Delay(50);

        mapa_bomba_j2[down_linha_2][down_coluna_2] = 0;
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 0;

        bloco_soma_2 = 0, bloco_down_2 = 0, bloco_left_2 = 0;
        bloco_right_2 = 0, bloco_up_2 = 0, up_linha_2 = 0, up_coluna_2 = 0;
        right_coluna_2 = 0, right_linha_2 = 0, down_coluna_2 = 0, down_linha_2 = 0;
        left_coluna_2 = 0, left_linha_2 = 0;
        break;

        case 14:
        mapa_bomba_j2[right_linha_2][right_coluna_2] = 12; //12
        mapa_bomba_j2[up_linha_2][up_coluna_2] = 12; //12
        SDL_Delay(50);

        mapa_bomba_j2[right_linha_2][right_coluna_2] = 13; //13
        mapa_bomba_j2[up_linha_2][up_coluna_2] = 13; //13
        SDL_Delay(50);

        mapa_bomba_j2[right_linha_2][right_coluna_2] = 14; //14
        mapa_bomba_j2[up_linha_2][up_coluna_2] = 14; //14
        SDL_Delay(50);

        mapa_bomba_j2[right_linha_2][right_coluna_2] = 15; //15
        mapa_bomba_j2[up_linha_2][up_coluna_2] = 15; //15
        SDL_Delay(50);

        mapa_bomba_j2[right_linha_2][right_coluna_2] = 16; //16
        mapa_bomba_j2[up_linha_2][up_coluna_2] = 16; //16
        SDL_Delay(50);

        mapa_bomba_j2[right_linha_2][right_coluna_2] = 17; //17
        mapa_bomba_j2[up_linha_2][up_coluna_2] = 17; //17
        SDL_Delay(50);

        mapa_bomba_j2[right_linha_2][right_coluna_2] = 0;
        mapa_bomba_j2[up_linha_2][up_coluna_2] = 0;

        bloco_soma_2 = 0, bloco_down_2 = 0, bloco_left_2 = 0;
        bloco_right_2 = 0, bloco_up_2 = 0, up_linha_2 = 0, up_coluna_2 = 0;
        right_coluna_2 = 0, right_linha_2 = 0, down_coluna_2 = 0, down_linha_2 = 0;
        left_coluna_2 = 0, left_linha_2 = 0;
        break;

        case 15:
        mapa_bomba_j2[up_linha_2][up_coluna_2] = 12; //12
        mapa_bomba_j2[down_linha_2][down_coluna_2] = 12; //12
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 12; //12
        SDL_Delay(50);

        mapa_bomba_j2[up_linha_2][up_coluna_2] = 13; //13
        mapa_bomba_j2[down_linha_2][down_coluna_2] = 13; //13
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 13; //13
        SDL_Delay(50);

        mapa_bomba_j2[up_linha_2][up_coluna_2] = 14; //14
        mapa_bomba_j2[down_linha_2][down_coluna_2] = 14; //14
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 14; //14
        SDL_Delay(50);

        mapa_bomba_j2[up_linha_2][up_coluna_2] = 15; //15
        mapa_bomba_j2[down_linha_2][down_coluna_2] = 15; //15
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 15; //15
        SDL_Delay(50);

        mapa_bomba_j2[up_linha_2][up_coluna_2] = 16; //16
        mapa_bomba_j2[down_linha_2][down_coluna_2] = 16; //16
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 16; //16
        SDL_Delay(50);

        mapa_bomba_j2[up_linha_2][up_coluna_2] = 17; //17
        mapa_bomba_j2[down_linha_2][down_coluna_2] = 17; //17
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 17; //17
        SDL_Delay(50);

        mapa_bomba_j2[up_linha_2][up_coluna_2] = 0;
        mapa_bomba_j2[down_linha_2][down_coluna_2] = 0;
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 0;

        bloco_soma_2 = 0, bloco_down_2 = 0, bloco_left_2 = 0;
        bloco_right_2 = 0, bloco_up_2 = 0, up_linha_2 = 0, up_coluna_2 = 0;
        right_coluna_2 = 0, right_linha_2 = 0, down_coluna_2 = 0, down_linha_2 = 0;
        left_coluna_2 = 0, left_linha_2 = 0;
        break;

        case 16:
        mapa_bomba_j2[right_linha_2][right_coluna_2] = 12; //12
        mapa_bomba_j2[down_linha_2][down_coluna_2] = 12; //12
        SDL_Delay(50);

        mapa_bomba_j2[right_linha_2][right_coluna_2] = 13; //13
        mapa_bomba_j2[down_linha_2][down_coluna_2] = 13; //13
        SDL_Delay(50);

        mapa_bomba_j2[right_linha_2][right_coluna_2] = 14; //14
        mapa_bomba_j2[down_linha_2][down_coluna_2] = 14; //14
        SDL_Delay(50);

        mapa_bomba_j2[right_linha_2][right_coluna_2] = 15; //15
        mapa_bomba_j2[down_linha_2][down_coluna_2] = 15; //15
        SDL_Delay(50);

        mapa_bomba_j2[right_linha_2][right_coluna_2] = 16; //16
        mapa_bomba_j2[down_linha_2][down_coluna_2] = 16; //16
        SDL_Delay(50);

        mapa_bomba_j2[right_linha_2][right_coluna_2] = 17; //17
        mapa_bomba_j2[down_linha_2][down_coluna_2] = 17; //17
        SDL_Delay(50);

        mapa_bomba_j2[right_linha_2][right_coluna_2] = 0;
        mapa_bomba_j2[down_linha_2][down_coluna_2] = 0;

        bloco_soma_2 = 0, bloco_down_2 = 0, bloco_left_2 = 0;
        bloco_right_2 = 0, bloco_up_2 = 0, up_linha_2 = 0, up_coluna_2 = 0;
        right_coluna_2 = 0, right_linha_2 = 0, down_coluna_2 = 0, down_linha_2 = 0;
        left_coluna_2 = 0, left_linha_2 = 0;
        break;

        case 18:
        mapa_bomba_j2[right_linha_2][right_coluna_2] = 12; //12
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 12; //12
        SDL_Delay(50);

        mapa_bomba_j2[right_linha_2][right_coluna_2] = 13; //13
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 13; //13
        SDL_Delay(50);

        mapa_bomba_j2[right_linha_2][right_coluna_2] = 14; //14
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 14; //14
        SDL_Delay(50);

        mapa_bomba_j2[right_linha_2][right_coluna_2] = 15; //15
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 15; //15
        SDL_Delay(50);

        mapa_bomba_j2[right_linha_2][right_coluna_2] = 16; //16
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 16; //16
        SDL_Delay(50);

        mapa_bomba_j2[right_linha_2][right_coluna_2] = 17; //17
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 17; //17
        SDL_Delay(50);

        mapa_bomba_j2[right_linha_2][right_coluna_2] = 0;
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 0;

        bloco_soma_2 = 0, bloco_down_2 = 0, bloco_left_2 = 0;
        bloco_right_2 = 0, bloco_up_2 = 0, up_linha_2 = 0, up_coluna_2 = 0;
        right_coluna_2 = 0, right_linha_2 = 0, down_coluna_2 = 0, down_linha_2 = 0;
        left_coluna_2 = 0, left_linha_2 = 0;
        break;

        case 19:
        mapa_bomba_j2[up_linha_2][up_coluna_2] = 12; //12
        mapa_bomba_j2[down_linha_2][down_coluna_2] = 12; //12
        mapa_bomba_j2[right_linha_2][right_coluna_2] = 12; //12
        SDL_Delay(50);

        mapa_bomba_j2[up_linha_2][up_coluna_2] = 13; //13
        mapa_bomba_j2[down_linha_2][down_coluna_2] = 13; //13
        mapa_bomba_j2[right_linha_2][right_coluna_2] = 13; //13
        SDL_Delay(50);

        mapa_bomba_j2[up_linha_2][up_coluna_2] = 14; //14
        mapa_bomba_j2[down_linha_2][down_coluna_2] = 14; //14
        mapa_bomba_j2[right_linha_2][right_coluna_2] = 14; //14
        SDL_Delay(50);

        mapa_bomba_j2[up_linha_2][up_coluna_2] = 15; //15
        mapa_bomba_j2[down_linha_2][down_coluna_2] = 15; //15
        mapa_bomba_j2[right_linha_2][right_coluna_2] = 15; //15
        SDL_Delay(50);

        mapa_bomba_j2[up_linha_2][up_coluna_2] = 16; //16
        mapa_bomba_j2[down_linha_2][down_coluna_2] = 16; //16
        mapa_bomba_j2[right_linha_2][right_coluna_2] = 16; //16
        SDL_Delay(50);

        mapa_bomba_j2[up_linha_2][up_coluna_2] = 17; //17
        mapa_bomba_j2[down_linha_2][down_coluna_2] = 17; //17
        mapa_bomba_j2[right_linha_2][right_coluna_2] = 17; //17
        SDL_Delay(50);

        mapa_bomba_j2[up_linha_2][up_coluna_2] = 0;
        mapa_bomba_j2[down_linha_2][down_coluna_2] = 0;
        mapa_bomba_j2[right_linha_2][right_coluna_2] = 0;

        bloco_soma_2 = 0, bloco_down_2 = 0, bloco_left_2 = 0;
        bloco_right_2 = 0, bloco_up_2 = 0, up_linha_2 = 0, up_coluna_2 = 0;
        right_coluna_2 = 0, right_linha_2 = 0, down_coluna_2 = 0, down_linha_2 = 0;
        left_coluna_2 = 0, left_linha_2 = 0;
        break;

        case 21:
        mapa_bomba_j2[up_linha_2][up_coluna_2] = 12; //12
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 12; //12
        mapa_bomba_j2[right_linha_2][right_coluna_2] = 12; //12
        SDL_Delay(50);

        mapa_bomba_j2[up_linha_2][up_coluna_2] = 13; //13
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 13; //13
        mapa_bomba_j2[right_linha_2][right_coluna_2] = 13; //13
        SDL_Delay(50);

        mapa_bomba_j2[up_linha_2][up_coluna_2] = 14; //14
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 14; //14
        mapa_bomba_j2[right_linha_2][right_coluna_2] = 14; //14
        SDL_Delay(50);

        mapa_bomba_j2[up_linha_2][up_coluna_2] = 15; //15
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 15; //15
        mapa_bomba_j2[right_linha_2][right_coluna_2] = 15; //15
        SDL_Delay(50);

        mapa_bomba_j2[up_linha_2][up_coluna_2] = 16; //16
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 16; //16
        mapa_bomba_j2[right_linha_2][right_coluna_2] = 16; //16
        SDL_Delay(50);

        mapa_bomba_j2[up_linha_2][up_coluna_2] = 17; //17
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 17; //17
        mapa_bomba_j2[right_linha_2][right_coluna_2] = 17; //17
        SDL_Delay(50);

        mapa_bomba_j2[up_linha_2][up_coluna_2] = 0;
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 0;
        mapa_bomba_j2[right_linha_2][right_coluna_2] = 0;

        bloco_soma_2 = 0, bloco_down_2 = 0, bloco_left_2 = 0;
        bloco_right_2 = 0, bloco_up_2 = 0, up_linha_2 = 0, up_coluna_2 = 0;
        right_coluna_2 = 0, right_linha_2 = 0, down_coluna_2 = 0, down_linha_2 = 0;
        left_coluna_2 = 0, left_linha_2 = 0;
        break;

        case 23:
        mapa_bomba_j2[down_linha_2][down_coluna_2] = 12; //12
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 12; //12
        mapa_bomba_j2[right_linha_2][right_coluna_2] = 12; //12
        SDL_Delay(50);

        mapa_bomba_j2[down_linha_2][down_coluna_2] = 13; //13
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 13; //13
        mapa_bomba_j2[right_linha_2][right_coluna_2] = 13; //13
        SDL_Delay(50);

        mapa_bomba_j2[down_linha_2][down_coluna_2] = 14; //14
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 14; //14
        mapa_bomba_j2[right_linha_2][right_coluna_2] = 14; //14
        SDL_Delay(50);

        mapa_bomba_j2[down_linha_2][down_coluna_2] = 15; //15
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 15; //15
        mapa_bomba_j2[right_linha_2][right_coluna_2] = 15; //15
        SDL_Delay(50);

        mapa_bomba_j2[down_linha_2][down_coluna_2] = 16; //16
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 16; //16
        mapa_bomba_j2[right_linha_2][right_coluna_2] = 16; //16
        SDL_Delay(50);

        mapa_bomba_j2[down_linha_2][down_coluna_2] = 17; //17
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 17; //17
        mapa_bomba_j2[right_linha_2][right_coluna_2] = 17; //17
        SDL_Delay(50);

        mapa_bomba_j2[down_linha_2][down_coluna_2] = 0;
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 0;
        mapa_bomba_j2[right_linha_2][right_coluna_2] = 0;

        bloco_soma_2 = 0, bloco_down_2 = 0, bloco_left_2 = 0;
        bloco_right_2 = 0, bloco_up_2 = 0, up_linha_2 = 0, up_coluna_2 = 0;
        right_coluna_2 = 0, right_linha_2 = 0, down_coluna_2 = 0, down_linha_2 = 0;
        left_coluna_2 = 0, left_linha_2 = 0;
        break;

        case 26:
        mapa_bomba_j2[up_linha_2][up_coluna_2] = 12; //12
        mapa_bomba_j2[down_linha_2][down_coluna_2] = 12; //12
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 12; //12
        mapa_bomba_j2[right_linha_2][right_coluna_2] = 12; //12
        SDL_Delay(50);

        mapa_bomba_j2[up_linha_2][up_coluna_2] = 13; //13
        mapa_bomba_j2[down_linha_2][down_coluna_2] = 13; //13
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 13; //13
        mapa_bomba_j2[right_linha_2][right_coluna_2] = 13; //13
        SDL_Delay(50);

        mapa_bomba_j2[up_linha_2][up_coluna_2] = 14; //14
        mapa_bomba_j2[down_linha_2][down_coluna_2] = 14; //14
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 14; //14
        mapa_bomba_j2[right_linha_2][right_coluna_2] = 14; //14
        SDL_Delay(50);

        mapa_bomba_j2[up_linha_2][up_coluna_2] = 15; //15
        mapa_bomba_j2[down_linha_2][down_coluna_2] = 15; //15
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 15; //15
        mapa_bomba_j2[right_linha_2][right_coluna_2] = 15; //15
        SDL_Delay(50);

        mapa_bomba_j2[up_linha_2][up_coluna_2] = 16; //16
        mapa_bomba_j2[down_linha_2][down_coluna_2] = 16; //12
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 16; //16
        mapa_bomba_j2[right_linha_2][right_coluna_2] = 16; //16
        SDL_Delay(50);

        mapa_bomba_j2[up_linha_2][up_coluna_2] = 17; //17
        mapa_bomba_j2[down_linha_2][down_coluna_2] = 17; //12
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 17; //17
        mapa_bomba_j2[right_linha_2][right_coluna_2] = 17; //17
        SDL_Delay(50);

        mapa_bomba_j2[up_linha_2][up_coluna_2] = 0;
        mapa_bomba_j2[down_linha_2][down_coluna_2] = 0;
        mapa_bomba_j2[left_linha_2][left_coluna_2] = 0;
        mapa_bomba_j2[right_linha_2][right_coluna_2] = 0;

        bloco_soma_2 = 0, bloco_down_2 = 0, bloco_left_2 = 0;
        bloco_right_2 = 0, bloco_up_2 = 0, up_linha_2 = 0, up_coluna_2 = 0;
        right_coluna_2 = 0, right_linha_2 = 0, down_coluna_2 = 0, down_linha_2 = 0;
        left_coluna_2 = 0, left_linha_2 = 0;
        break;
    }

    SDL_Delay(150);

//ANIMAÇÃO DE EXPLOSÃO DA BOMBA
    for (a = 1; a < 11; a++)
    {
        for (b = 1; b < 15; b++)
        {
            if (mapa_bomba_j2[a][b] == 10)
            {
                mapa_bomba_j2[a][b] = 0;
            }
            if (mapa_bomba_j2[a][b] == 6)
            {
                mapa_bomba_j2[a][b] = 0;
            }
            if (mapa_bomba_j2[a][b] == 7)
            {
                mapa_bomba_j2[a][b] = 0;
            }
            if (mapa_bomba_j2[a][b] == 8)
            {
                mapa_bomba_j2[a][b] = 0;
            }
            if (mapa_bomba_j2[a][b] == 9)
            {
                mapa_bomba_j2[a][b] = 0;
            }
        }
    }

    if (gDerrota == 200)
    {
        gContinuar = 7;
    }
    if (gDerrota == 100)
    {
        gContinuar = 8;
    }

    pthread_exit(NULL);
}
