#include <stdlib.h>
#include <stdio.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

//INICIALIZAÇÃO DE TELA E MENU
int main(int argc, char *argv[])
{
    SDL_Surface *tela = NULL;
    SDL_Surface *menu = NULL;
    SDL_Surface *novo_jogo = NULL;
    SDL_Surface *msg_sair = NULL;

    SDL_Rect posicao_menu;
    SDL_Rect posicao_novo_jogo;
    SDL_Rect posicao_msg_sair;

    TTF_Font *fonte = NULL;
    SDL_Color cor_texto = {0, 0, 0}, cor = {255, 255, 255};

    SDL_Event evento;

    int continuar = 3;
    char texto_novo_jogo[30] = "";
    char texto_msg_sair[30] = "";

    SDL_Init(SDL_INIT_VIDEO);

    SDL_WM_SetIcon(IMG_Load("Bomberman.bmp"), NULL);

    tela = SDL_SetVideoMode(520,470,32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    SDL_WM_SetCaption("Bomberman", NULL);

    menu = IMG_Load("menu.png");

    TTF_Init();
    fonte = TTF_OpenFont("fonte.ttf", 36);

    sprintf(texto_novo_jogo, "(1) Novo Jogo");
    novo_jogo = TTF_RenderText_Blended(fonte, texto_novo_jogo, cor);

    sprintf(texto_msg_sair, "(2) Sair");
    msg_sair = TTF_RenderText_Blended(fonte, texto_msg_sair, cor);

//MUSICA DO MENU
    SDL_Delay(100);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
    Mix_Music *musica_menu;
    musica_menu = Mix_LoadMUS("Menu.mp3");

//POSIÇÃO DO MENU NA TELA
    posicao_menu.x=0;
    posicao_menu.y=0;

    posicao_novo_jogo.x = 6;
    posicao_novo_jogo.y = 0;

    posicao_msg_sair.x = 5;
    posicao_msg_sair.y = 30;

//EVENTO PARA ENTRAR OU NÃO NO JOGO
    while(continuar)
    {
        Mix_PlayMusic(musica_menu, 5);

        SDL_WaitEvent(&evento);
        switch(evento.type)
        {
            case SDL_QUIT:
            continuar = 0;
            break;

            case SDL_KEYDOWN:

            switch(evento.key.keysym.sym)
            {
                case SDLK_2:
                continuar = 0;
                break;

                case SDLK_1:
                jogar(tela);
                break;
            }

            break;
        }

        SDL_BlitSurface(menu, NULL, tela, &posicao_menu);
        SDL_BlitSurface(novo_jogo, NULL, tela, &posicao_novo_jogo);
        SDL_BlitSurface(msg_sair, NULL, tela, &posicao_msg_sair);
        SDL_Flip(tela);
    }

//   Mix_CloseAudio();
    SDL_FreeSurface(menu);
    SDL_FreeSurface(novo_jogo);
    SDL_FreeSurface(msg_sair);
    SDL_Quit();

    return EXIT_SUCCESS;
}
