#include <stdlib.h>
#include <stdio.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <pthread.h>
#include "jogo.h"
#include "constante.h"


SDL_Rect posicao_mensagem_mapa_1;
SDL_Rect posicao_mensagem_mapa_2;

SDL_Rect posicao_tela_menu;

void menu(SDL_Surface* menu_principal)
{

//INICIALIZAÇÃO DE TELA E MENU
    SDL_Surface *tela_menu = NULL;
    SDL_Surface *mensagem_mapa_1 = NULL;
    SDL_Surface *mensagem_mapa_2 = NULL;

    TTF_Font *fonte2 = NULL;
    SDL_Color cor_texto = {0, 0, 0}, cor = {0, 0, 0};

    SDL_Event evento2;

    int escolha = 1;
    char texto_mapa_1 [30] = "";
    char texto_mapa_2 [30] = "";

    tela_menu = IMG_Load("menu.png");

    TTF_Init();
    fonte2 = TTF_OpenFont("fonte.ttf",26);

    sprintf(mensagem_mapa_1,"(1) MAPA 1");
    mensagem_mapa_1 = TTF_RenderText_Blended(fonte2, texto_mapa_1, cor);

    sprintf(mensagem_mapa_2,"(2) MAPA 2");
    mensagem_mapa_2 = TTF_RenderText_Blended(fonte2, texto_mapa_2, cor);

    posicao_mensagem_mapa_1.x = 130;
    posicao_mensagem_mapa_1.y = 130;

    posicao_mensagem_mapa_2.x = 150;
    posicao_mensagem_mapa_2.y = 150;

//POSIÇÃO DO MENU NA TELA
    posicao_tela_menu.x = 0;
    posicao_tela_menu.y = 0;

//EVENTO PARA ENTRAR OU NÃO NO JOGO
    while(escolha == 1)
    {
        SDL_WaitEvent(&evento2);

        switch(evento2.type)
        {
            case SDL_KEYDOWN:

            switch(evento2.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                escolha = 1;
                break;

                case SDLK_1:
                jogar(tela);
                break;

                case SDLK_2:
                Jogar(tela);
                break;
            }

            break;
        }

        SDL_BlitSurface(tela_menu, NULL, menu_principal, &posicao_tela_menu);
        SDL_BlitSurface(mensagem_mapa_1, NULL, menu_principal, &posicao_mensagem_mapa_1);
        SDL_BlitSurface(mensagem_mapa_2, NULL, menu_principal, &posicao_mensagem_mapa_2);
        SDL_Flip(tela_menu);
    }

//  Mix_CloseAudio();
    SDL_FreeSurface(tela_menu);
}
