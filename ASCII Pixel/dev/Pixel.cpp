#include "Pixel.h"

void GetPixelRGB(SDL_Surface *superficie, int posx, int posy, Uint8 *r, Uint8 *g, Uint8 *b){
    Uint32 pixel = ((Uint32 *)superficie->pixels)[(posy * superficie->w) + posx];
    SDL_GetRGB(pixel, superficie->format, r, g, b);
}

char ColorToAscii(Uint8 r, Uint8 g, Uint8 b){
    const char color_density[] = "Ñ@#W$9876543210?!abc;:+=-,._ ";
    const int tamanho = strlen(color_density);
    int grey = r * 0.3 + g * 0.59 + b * 0.11;
    
    return color_density[tamanho - grey/tamanho];
}

void MostrarPixelsImagem(const char caminho_imagem[]){
    SDL_Surface* superficie = IMG_Load(caminho_imagem);

    if(!superficie){
        printf("IMG_Load Error: %s\n", IMG_GetError());
        return;
    }
    else{
        for (int y = 0; y < superficie->h; y++) {
            for (int x = 0; x < superficie->w; x++) {
                Uint8 r, g, b;
                GetPixelRGB(superficie, x, y, &r, &g, &b);
                std::cout << ColorToAscii(r, g, b);
            }
            std::cout << "\n";
        }
    }

    SDL_FreeSurface(superficie);
}

std::vector<std::string> PixelsImagemParaVetor(const char caminho_imagem[]){
    SDL_Surface* superficie = IMG_Load(caminho_imagem);

    if(!superficie){
        printf("IMG_Load Error: %s\n", IMG_GetError());
        return std::vector<std::string>();
    }
    else{
        std::vector<std::string> matriz;
        for (int y = 0; y < superficie->h; y++) {
            std::string linha = "";
            for (int x = 0; x < superficie->w; x++) {
                Uint8 r, g, b;
                GetPixelRGB(superficie, x, y, &r, &g, &b);
                linha.push_back(ColorToAscii(r, g, b));
            }
            matriz.push_back(linha);
        }
        SDL_FreeSurface(superficie);

        return matriz;
    }    
}

void VetorParaArquivo(const std::vector<std::string>& vec, const std::string& filename) {
    // Cria um objeto de saída de arquivo em modo de escrita
    std::ofstream outFile(filename, std::ios::out);

    // Verifica se o arquivo foi aberto com sucesso
    if (!outFile.is_open()) {
        std::cerr << "Não foi possível abrir o arquivo: " << filename << std::endl;
        return;
    }

    // Escreve cada string do vetor no arquivo, uma por linha
    for (const auto& str : vec) {
        outFile << str << std::endl;
    }

    // Fecha o arquivo
    outFile.close();
}