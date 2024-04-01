#include "ia.h"

int retorna_valor(char peca){
    switch(peca){
        case BlackPawn:
        case BlackStaticPawn:
            return -peao;

        case WhiteStaticPawn:
        case WhitePawn:
            return peao;

        case BlackKnight:
            return -cavalo;

        case WhiteKnight:
            return cavalo;

        case BlackBishop:
            return -bispo;
        
        case WhiteBishop:
            return bispo;

        case BlackRook:
        case BlackStaticRook:
            return -torre;

        case WhiteStaticRook:
        case WhiteRook:
            return torre;

        case BlackQueen:
            return -rainha;

        case WhiteQueen:
            return rainha;

        case BlackKing:
        case BlackStaticKing:
            return -rei;

        case WhiteStaticKing:
        case WhiteKing:
            return rei;

        default:
            return 0;
    }
}

int avaliacao_posicao(std::vector<std::vector<char>>& pecas_tabuleiro){
    int total=0;
    for(int i=0; i<pecas_tabuleiro.size(); i++){
        for(int j=0; j<pecas_tabuleiro.size(); j++){
            total += retorna_valor(pecas_tabuleiro[i][j]);
        }
    }

    return total;
}

Lance minmax(std::vector<FEN>& controle_lances, std::vector<std::vector<char>>& pecas_tabuleiro, int& turno, bool max){
    std::vector<Lance> possibilidades = todos_possiveis_lances(pecas_tabuleiro, turno, &controle_lances);
    if(possibilidades.size()==0){
        return {-1, -1, -1, -1};
    }
    
    int resultado=0;
    int valor_resultado=0;
    int backup_turno = turno;

    for(int i=0; i<possibilidades.size(); i++){
        executar_lance(pecas_tabuleiro, possibilidades[i], &controle_lances);
        int result_iteracao = avaliacao_posicao(pecas_tabuleiro);

        if(turno==White){
            if(valor_resultado < result_iteracao){
                valor_resultado = result_iteracao;
                resultado = i;
            }
        }
        else{
            if(valor_resultado > result_iteracao){
                valor_resultado = result_iteracao;
                resultado = i;
            }
        }

        reverter_lance(controle_lances, pecas_tabuleiro, backup_turno);
    }

    return possibilidades[resultado];
}

void minmax_recusivo(Lance* escolhido, int* pontuacao, int profundidade, std::vector<FEN>& controle_lances, 
    std::vector<std::vector<char>>& pecas_tabuleiro, int& turno, bool max){
        if(profundidade>0){
            std::vector<Lance> possibilidades = todos_possiveis_lances(pecas_tabuleiro, turno, &controle_lances);
            if(possibilidades.size()!=0){
                int backup_turno=turno;
                int melhor_lance=0;

                //calcula o primeiro elemento
                executar_lance(pecas_tabuleiro, possibilidades[0], &controle_lances);
                int melhor_pontuacao=avaliacao_posicao(pecas_tabuleiro);
                reverter_lance(controle_lances, pecas_tabuleiro, backup_turno);

                for(int i=1; i<possibilidades.size(); i++){
                    executar_lance(pecas_tabuleiro, possibilidades[i], &controle_lances);
                    int pontuacao_iteracao=avaliacao_posicao(pecas_tabuleiro);
                    reverter_lance(controle_lances, pecas_tabuleiro, backup_turno);

                    if(turno==White){
                        if(melhor_pontuacao < pontuacao_iteracao){
                            melhor_pontuacao = pontuacao_iteracao;
                            melhor_lance = i;
                        }
                    }
                    else{
                        if(melhor_pontuacao > pontuacao_iteracao){
                            melhor_pontuacao = pontuacao_iteracao;
                            melhor_lance = i;
                        }
                    }
                }
            }
        }
}

void executar_lance_ia(std::vector<FEN>& controle_lances, std::vector<std::vector<char>>& pecas_tabuleiro, int& turno){
    bool eh_max = turno==White ? true : false;
    turno = turno==White ? Black : White;

    Lance lance_escolhido = minmax(controle_lances, pecas_tabuleiro, turno, eh_max);
    if(lance_escolhido.src_i!=-1){
        executar_lance(pecas_tabuleiro, lance_escolhido, &controle_lances);
    }
    else{
        ModoDeJogo=FimDeJogo;
        printf("Fim de Jogo\n");
    }
}