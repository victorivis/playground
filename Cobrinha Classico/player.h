#pragma once

class Player{
    //Obrigatorio
    public:
        int HEIGHT;
        int WIDTH;

    //Configuracoes
	public:
		int TAM_COBRA;
		int VEL=TAM_COBRA;
        int num_segmentos;
        short int direcao;
        bool cobra_colorida;

        SDL_Rect cabeca;
        deque<SDL_Rect> segmentos_cobra;
        vector<int> controles;

    //Funcoes
    public:
        void Player(int w, int h, vector<int> z);
        void executar_controles(int tecla);
        void mover_cobra(int direcao);
        void colorir_cobra(vector<trio>& cores);
        void descolorir_cobra(vector<trio>& cores, trio cor_segmentos={0, 0, 0});
        void colisao_cobra(deque<SDL_Rect>& cobra_generica);
};