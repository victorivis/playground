#include "CApp.h"

//O construtor (padrao)
CApp::CApp(){
    isRunning = true;
    pWindow = NULL;
    pRenderer = NULL;
}


bool CApp::OnInit(){
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        return false;
    }

    pWindow = SDL_CreateWindow("Uma especie de RPG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);

    if(pWindow != NULL){
        //As opcoes habilitam sincronizacao vertical e utilizar a placa de video para otimizar cpu, respectivamente
        pRenderer = SDL_CreateRenderer(pWindow, -1,  SDL_RENDERER_TARGETTEXTURE);
    }
    else{
        return false;
    }

    /*
    entidades = {
        Entity(pRenderer, "../images/grama.png", 100, 100),
        Entity(pRenderer, "../images/grama.png", 200, 100),
        Entity(pRenderer, "../images/grama.png", 300, 100),
    };

    player = {
        Player(pRenderer, "../images/player.png", 100, 200, 10)
    };
    */

    //entidades.push_back(Entity(pRenderer, "../images/grama.png", 100, 100));

    // Show the window.
    SDL_RenderPresent(pRenderer);

    

    return true;
}

void CApp::OnEvent(SDL_Event *evento){
    if(evento->type == SDL_QUIT){
        isRunning = false;
    }
    else if(evento->type == SDL_KEYDOWN){

        switch(evento->key.keysym.sym){
            case SDLK_ESCAPE:
				isRunning=false;
				break;
        }
    }
}

int CApp::OnExecute(){
    SDL_Event event;

    if (OnInit() == false){
        return -1;
    }

    Entity entidades[] = {Entity (pRenderer, "../images/grama.png", 100, 230),
    Entity (pRenderer, "../images/grama.png", 600, 230),
    Entity (pRenderer, "../images/grama.png", 164, 230),
    Entity (pRenderer, "../images/grama.png", 216, 230),
    };

    Entity parede[] = {
        Entity (pRenderer, "../images/gray-tile.png", 100, 530),
        Entity (pRenderer, "../images/gray-tile.png", 600, 530),
        Entity (pRenderer, "../images/gray-tile.png", 164, 530),
        Entity (pRenderer, "../images/gray-tile.png", 216, 530),
    };


    Player player(pRenderer, "../images/player-no-border.png", 216, 100, 10);
    
    //std::vector<Entity> entidades;
    //entidades.push_back(grama1);
    //entidades.push_back(grama2);
    //entidades.push_back(grama3);
    //entidades.push_back(grama4);

    while(isRunning){
        while(SDL_PollEvent(&event) != 0){
            OnEvent(&event);

            if(event.type == SDL_KEYDOWN){
                player.executarControles(event.key.keysym.sym);
            }
        }

        OnLoop();
        
        for(int i=0; i < sizeof(entidades) / sizeof(Entity); i++){
            entidades[i].render();
            aceleracao_aabb(player, entidades[i]);
        }

        for(int i=0; i < sizeof(parede) / sizeof(Entity); i++){
            parede[i].render();
            colisao_aabb(player, parede[i]);
        }

        player.render();

        OnRender();
    }
    OnExit();

    return 0;
}

void CApp::OnLoop(){
    //std::cout << "segundos: " << hireTimeInSeconds() << "\n";
}

void CApp::OnRender(){

    SDL_RenderPresent(pRenderer);
    SDL_Delay(4);

    // Define a cor de fundo para preto
    SDL_SetRenderDrawColor(pRenderer, 150, 150, 150, 255);
    SDL_RenderClear(pRenderer);
}

void CApp::OnExit(){
    SDL_DestroyWindow(pWindow);
    SDL_DestroyRenderer(pRenderer);
    IMG_Quit();

    pWindow = NULL;
    pRenderer = NULL;

    std::cout << "Tudo limpo. Adeus vazamentos de memoria!\n";

    SDL_Quit();
}