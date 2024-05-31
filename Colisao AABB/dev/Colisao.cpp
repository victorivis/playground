#include "Colisao.h"

void colisao_aabb(Player& player, Entity& entidade){
    if(SDL_TRUE == SDL_HasIntersection(&player.destRect, &entidade.destRect)){
        std::cout << "Colisao " << player.last_move << "\n";

        switch(player.last_move){
            case DOWN:
                player.destRect.y -= player.player_speed;
                break;
            case UP:
                player.destRect.y += player.player_speed;
                break;
            case RIGHT:
                player.destRect.x -= player.player_speed;
                break;
            case LEFT:
                player.destRect.x += player.player_speed;
                break;
        }
    }
}

void aceleracao_aabb(Player& player, Entity& entidade){
    if(SDL_TRUE == SDL_HasIntersection(&player.destRect, &entidade.destRect)){
        std::cout << "Colisao " << player.last_move << "\n";

        switch(player.last_move){
            case UP:
                player.destRect.y -= player.player_speed;
                break;
            case DOWN:
                player.destRect.y += player.player_speed;
                break;
            case LEFT:
                player.destRect.x -= player.player_speed;
                break;
            case RIGHT:
                player.destRect.x += player.player_speed;
                break;
        }
    }
}