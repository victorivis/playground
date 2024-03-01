class Player{
    //Obrigatorio
    public:
        int HEIGHT;
        int WIDTH;

    //Configuracoes
	public:
		int TAM_COBRA=10;
		int VEL=TAM_COBRA;
        int num_segmentos=1;
        short int direcao = -1;
        bool cobra_colorida=false;

        SDL_Rect cabeca = {500, 500, TAM_COBRA, TAM_COBRA};
        deque<SDL_Rect> segmentos_cobra;
        vector<int> controles;

    //Funcoes
    public:
        void Player(int w, int h, vector<int> z){
            WIDTH = w;
            HEIGHT = h;
            controles=z;
        }

        void executar_controles(int tecla){
            switch(tecla){
               case controles[0]: if(direcao!=Baixo) direcao=Cima; break;
				case  controles[1]: if(direcao!=Cima) direcao=Baixo; break;
				case  controles[2]: if(direcao!=Esquerda) direcao=Direita; break;
				case  controles[3]:	if(direcao!=Direita) direcao=Esquerda; break;
            }
        }

        void mover_cobra(int direcao){
            switch(direcao){
                case Cima: cabeca.y = (cabeca.y-VEL+HEIGHT)%HEIGHT; break;
                case Baixo: cabeca.y = (cabeca.y+VEL+HEIGHT)%HEIGHT; break;
                case Direita: cabeca.x = (cabeca.x+VEL+WIDTH)%WIDTH; break;
                case Esquerda: cabeca.x = (cabeca.x-VEL+WIDTH)%WIDTH; break;
            }
        }

        void colorir_cobra(vector<trio>& cores){
            for_each(cores.begin(), cores.end(), [&](trio& cor){
                cor.r = rand()%256;
                cor.g = rand()%256;
                cor.b = rand()%256;
            });
        }

        void descolorir_cobra(vector<trio>& cores, trio cor_segmentos={0, 0, 0}){
            for_each(cores.begin(), cores.end(), [&](trio& cor){
                cor.r = cor_segmentos.r;
                cor.g = cor_segmentos.g;
                cor.b = cor_segmentos.b;
            });
        }

        void colisao_cobra(deque<SDL_Rect>& cobra_generica){
            for_each(cobra_generica.begin(), cobra_generica.end(), [&](auto& segmento){
                if(SDL_HasIntersection(&segmento, &cabeca)){
                    num_segmentos = 1;
                    //cout << "Colisao cabeca\n";
                }
            });
        }
};
