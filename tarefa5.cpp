// TODO: implementar destrutores nas classes

#include <iostream>
#include <SDL2/SDL.h>
#include <thread>
#include "classes/headers/math/Vec3.h"
#include "classes/headers/primitives/Esfera.h"
#include "classes/headers/primitives/Cilindro.h"
#include "classes/headers/primitives/Cone.h"
#include "classes/headers/Canvas.h"
#include "classes/headers/Ray.h"
#include "classes/headers/Scene.h"
#include "classes/headers/materiais/BaseMaterial.h"
#include "classes/headers/materiais/MaterialTarefa.h"
#include "classes/headers/math/Transformations.h"
#include "classes/headers/math/Mat4.h"
#include "classes/headers/math/Vec4.h"
#include "classes/headers/Camera.h"
#include "classes/headers/primitives/Triangulo.h"
#include "classes/headers/primitives/Mesh.h"
#include "classes/headers/primitives/ObjMesh.h"
#include "classes/headers/primitives/mesh/Texture.h"
#include "classes/headers/luzes/LuzPontual.h"


using namespace std;

const int WINDOW_WIDTH = 500, WINDOW_HEIGHT = 500;

void renderizarCenario(Scene* cenario, double dJanela, Vec3 olhoPintor) {
    cenario->pintarCanvas2(dJanela, olhoPintor);
}

void colorirCenario(SDL_Renderer* renderer, Scene* cenario, int nLin, int nCol) {
    for (int l = 0; l < nLin; ++l) {
        for (int c = 0; c < nCol; ++c) {
            SDL_Color cor = cenario->canvas->cores[l][c];

            SDL_SetRenderDrawColor(renderer, cor.r, cor.g, cor.b, cor.a);
            SDL_RenderDrawPoint(renderer, c, l); // x = coluna que ta e y = linha que ta
        }
    }
}

int main ( int argc, char *argv[] ) {

    MaterialTarefa material = MaterialTarefa();
    cout << material.getRefletividade() << endl;


    SDL_Window *window; // = SDL_CreateWindow("Hello SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, wJanela, hJanela, SDL_WINDOW_ALLOW_HIGHDPI );
    SDL_Renderer *renderer;


    // initializeSDLAndWindow(&window, &renderer, WINDOW_WIDTH, WINDOW_HEIGHT);

    const double dJanela = 30;

    Vec3 lookat(0, 0, -dJanela);
    Vec3 lookfrom(0, 0, 100);

    Camera *camera = new Camera(lookfrom, lookat, Vec3(0, 1, 0), 90, WINDOW_WIDTH, WINDOW_HEIGHT);
    Scene *cenario = new Scene(&window, &renderer, WINDOW_WIDTH, WINDOW_HEIGHT, Vec3(0.3, 0.3, 0.3), camera);
    const double wJanela = camera->wJanela, hJanela = camera->hJanela;
    camera->cenario = cenario;
    camera->changeCamera();
    camera->isParalel = true;

    SDL_Color corVermelha = {255, 0, 0, 255};
    SDL_Color corVerde = {0, 255, 0, 255};
    SDL_Color corAzul = {0, 0, 255, 255};

    // Mesh* mesh = new Mesh(1);
    // mesh->vertices.push_back(Vec3(0, 0, -dJanela));
    // mesh->vertices.push_back(Vec3(30, 0, -dJanela));
    // mesh->vertices.push_back(Vec3(30, 30, -dJanela));
    // mesh->faces.push_back({ 0,1,2 });
    // mesh->vertices.push_back({ 0,30,-dJanela });
    // mesh->faces.push_back({ 0,2,3 });
    // mesh->renderizar();

    Texture* textura = new Texture("assets/wood.png");
    Plano* chao = new Plano(1, corAzul, BaseMaterial(Vec3(0.2, 0.7, 0.2), Vec3(0, 0, 0), Vec3(0.2, 0.7, 0.2), 1), Vec3(0, -150, 0), Vec3(0, 1, 0), textura);
    Plano* paredeLateralDireita = new Plano(2, corAzul, BaseMaterial(Vec3(0.686, 0.933, 0.933), Vec3(0.686, 0.933, 0.933), Vec3(0.686, 0.933, 0.933), 1), Vec3(200, -150, 0), Vec3(-1, 0, 0));
    Plano* paredeFrontal = new Plano(3, corAzul, BaseMaterial(Vec3(0.686, 0.933, 0.933), Vec3(0.686, 0.933, 0.933), Vec3(0.686, 0.933, 0.933), 1), Vec3(200, -150, -400), Vec3(0, 0, 1));
    Plano* paredeLateralEsquerda = new Plano(4, corAzul, BaseMaterial(Vec3(0.686, 0.933, 0.933), Vec3(0.686, 0.933, 0.933), Vec3(0.686, 0.933, 0.933), 1), Vec3(-200, -150, 0), Vec3(1, 0, 0));
    Plano* teto = new Plano(5, corAzul, BaseMaterial(Vec3(0.933, 0.933, 0.933), Vec3(0.933, 0.933, 0.933), Vec3(0.933, 0.933, 0.933), 1), Vec3(0, 150, 0), Vec3(0, -1, 0));
    
    Cilindro* cilindro = new Cilindro(6, corAzul, Vec3(0, -150, -200), Vec3(0, 1, 0), 90, 5, BaseMaterial(Vec3(0.824, 0.706, 0.549), Vec3(0.824, 0.706, 0.549), Vec3(0.824, 0.706, 0.549), 1)); 
    Cone* cone = new Cone(7, corAzul, Vec3(0, -60, -200), Vec3(0, 1, 0), 150, 90, BaseMaterial(Vec3(0.824, 0.706, 0.549), Vec3(0.824, 0.706, 0.549), Vec3(0.824, 0.706, 0.549), 1));
    ObjMesh* cubo = new ObjMesh(8, "assets/cube/cube.obj", BaseMaterial(Vec3(1, 0.078, 0.576), Vec3(1, 0.078, 0.576), Vec3(1, 0.078, 0.576), 1));
    cubo->applyMatrix(Transformations::scale(20, 20, 20));
    cubo->applyMatrix((Transformations::translate(0, -150, -200)));

    Esfera* esfera = new Esfera(9, corAzul, Vec3(0, 95, -200), 5, BaseMaterial(Vec3(0.854, 0.647, 0.125), Vec3(0.854, 0.647, 0.125), Vec3(0.854, 0.647, 0.125), 1));

    LuzPontual* luzPontual = new LuzPontual(Vec3(-100, 140, -20), Vec3(0.3, 0.3, 0.3));
    LuzPontual* luzTeste = new LuzPontual(Vec3(-100, -100, -20), Vec3(0.7, 0.7, 0.7));

    Esfera* esfera2 = new Esfera(0, corVermelha, Vec3(0, 0, -100), 40, MaterialTarefa());
    Plano* chao2 = new Plano(5, corAzul, BaseMaterial(Vec3(0.2, 0.7, 0.2), Vec3(0, 0, 0), Vec3(0.2, 0.7, 0.2), 1), Vec3(0, -55, 0), Vec3(0, 1, 0));
    Plano* planoDeFundo2 = new Plano(6, corVerde, BaseMaterial(Vec3(0.3, 0.3, 0.7), Vec3(0, 0, 0), Vec3(0.3, 0.3, 0.7), 1), Vec3(0, 0, -200), Vec3(0, 0, 1));
    
    Cilindro* cilindro2 = new Cilindro(1, corVerde, Vec3(0, 0, -100), Vec3(-1/sqrt(3), 1/sqrt(3), -1/sqrt(3)), 3 * 40, 40/3, BaseMaterial(Vec3(0.2, 0.3, 0.8), Vec3(0.2, 0.3, 0.8), Vec3(0.2, 0.3, 0.8), 10));
    Cone* cone2 = new Cone(1, corAzul, cilindro->Ct, Vec3(-1/sqrt(3), 1/sqrt(3), -1/sqrt(3)), 1.5 * 40 / 3, (1.5)*40, BaseMaterial(Vec3(0.8, 0.3, 0.2), Vec3(0.8, 0.3, 0.2), Vec3(0.8, 0.3, 0.2), 10));

    Cone* coneTeste = new Cone(100, corAzul, Vec3(-50, 20, -200), Vec3(-50, 90, -200), 45);
    Cilindro* cilindroTeste = new Cilindro(101, corAzul, Vec3(50, 20, -200), Vec3(50, 90, -200), 45);

    cenario->objetos.push_back(chao);
    cenario->objetos.push_back(paredeLateralDireita);
    cenario->objetos.push_back(paredeFrontal);
    cenario->objetos.push_back(paredeLateralEsquerda);
    cenario->objetos.push_back(teto);

    cenario->objetos.push_back(cilindro);
    cenario->objetos.push_back(cone);
    cenario->objetos.push_back(cubo);
    cenario->objetos.push_back(esfera);

    cenario->luzes.push_back(luzPontual);

    const int nCol = 500;
    const int nLin = 500;
    const double Dx = (double)wJanela / (double)nCol;
    const double Dy = (double)hJanela / (double)nLin;
    cenario->setCanvas(nLin, nCol, Dx, Dy);

    bool rodando = true;
    double i = 0;
    while (rodando) {
        // cout << i << endl;
    //     // for (int i = -100; i <= 0 ; i+=5) {

        SDL_Event windowEvent;
        while ( SDL_PollEvent(&windowEvent) ) {
            if (SDL_QUIT == windowEvent.type) { 
                rodando = false;
                break; 
            }
        }

        // mesh2->applyMatrix(Transformations::rotateZAroundPointDegrees(1, Vec3(0, 0, 0)).apply(Transformations::rotateXAroundPointDegrees(1, Vec3(0, 0, 0))));
        // mesh2->applyMatrix(Transformations::translate(0, -i, 0));
        // mesh2->applyMatrix(Transformations::scale(i, i, i));    

        // camera->initialize2(Vec3(i, 0, 50), Vec3(0, 10, -dJanela), Vec3(0, 1, 0), 90, WINDOW_WIDTH, WINDOW_HEIGHT);
        if (i == 0) {
            camera->renderAndPaintCanvasThread(4, 1);
            // cenario->pintarCanvas(dJanela, lookfrom);
            colorirCenario(renderer, cenario, nLin, nCol);
        }
        i += 1;
        
        SDL_RenderPresent(renderer); // usar para pintar
        if ( window = nullptr ) {
            cout << "ERRO:" << SDL_GetError() << "\n";
            return 1;
        }
    }
    
    // while (rodando) {
        // for (int i = -100; i <= 0 ; i+=5) {

            // SDL_Event windowEvent;
            // while ( SDL_PollEvent(&windowEvent) ) {
            //     if (SDL_QUIT == windowEvent.type) { 
            //         rodando = false;
            //         break;  
            //     }
            // }
    


    SDL_DestroyWindow( window );
    SDL_Quit();

    return EXIT_SUCCESS;
}
