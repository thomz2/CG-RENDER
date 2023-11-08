#include <SDL.h>
#include <iostream>

using namespace std;

int m4(int argc, char* argv[]) {

    // Inicializar a biblioteca para poder usar suas fun��es
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("N�o foi poss�vel inicializar o SDL! SDL_Error: %s", SDL_GetError());
        return 1;
    }

    // Criar uma janela
    SDL_Window* window = SDL_CreateWindow(
        "CG I - Raycaster",       // T�tulo da Janela
        SDL_WINDOWPOS_UNDEFINED,        // Posi��o inicial X
        SDL_WINDOWPOS_UNDEFINED,        // Posi��o inicial Y
        1280,                           // Largura da janela em pixels
        720,                            // Altura da janela em pixels
        SDL_WINDOW_SHOWN                // Flags
    );

    // Verificar se a janela foi criada corretamente
    if (!window) {
        SDL_Log("Cria��o da janela falhou! SDL_Error: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Criar o objeto renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("Cria��o do renderer falhou! SDL_Error: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // m loop - � dentro do m while loop que fazemos todas as intera��es com a janela
    bool isRunning = true; //vari�vel de controle do loop
    SDL_Event event; //vari�vel para checar os eventos da janela

    while (isRunning) {
        // � poss�vel interagir com a janela, com clicks, apertando teclas ou clicando para fechar a janela
        // essas intera��es s�o chamadas de "eventos", abaixo, verificamos se o evento de fechar janela ocorre
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        // � uma boa pr�tica limpar o renderer antes de desenhar novos pixeis, no caso de existir "lixo" no renderer
        SDL_RenderClear(renderer);

        // Aqui temos a estrutura para pintar um pixel, no caso, um loop para pintar todos os pixeis da janela

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // <---- Aqui escolhemos a cor que desejamos pintar
        // DETALHE: essa fun��o utiliza o padr�o RGBA, para 
        // o nosso prop�sito, podemos ignorar o �ltimo par�metro
        for (int x = 0; x < 1280; x++) {
            for (int y = 0; y < 720; y++) {
                SDL_RenderDrawPoint(renderer, x, y);  //<---- Aqui escolhemos qual pixel vamos pintar
            }
        }

        // Por fim, atualizamos a janela com o renderer que acabamos de pintar e tudo deve funcionar corretamente
        SDL_RenderPresent(renderer);
    }

    // Destruir os objetos criados para limpar a mem�ria
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}