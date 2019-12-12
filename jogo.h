#ifndef JOGO_H_INCLUDED
#define JOGO_H_INCLUDED

typedef struct
{
   int key[SDLK_LAST];
}
teclas;

void *gerenciamento_bomba_j1(void*arg);
void *gerenciamento_bomba_j2(void*arg);

void criacao_bomba_j1(int **mapa, SDL_Surface* ecran);
void criacao_bomba_j2(int **mapa, SDL_Surface* ecran);

void tecladoa_tualizado(teclas* estado_teclado);
void jogar(SDL_Surface* ecran);
void movimento_jogador(int **mapa, SDL_Rect *pos, int direcao);

#endif // JOGO_H_INCLUDED
