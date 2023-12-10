#pragma once

#include <optional>
#include "../math/Vec3.h"
#include "./Objeto.h"
#include "../Ray.h"
#include "../materiais/BaseMaterial.h"
#include "../types/LPointGetType.h"

class Esfera : public Objeto {
    public:
    Vec3 PCentro;
    double raio;

    Esfera(int id, SDL_Color cor, Vec3 Pcentro, double raio, BaseMaterial material);
    Esfera(int id, SDL_Color cor, Vec3 Pcentro, double raio);


    std::optional<LPointGetType> intersecta(Ray raycaster) override;

    // Pin = olho observador
    Vec3 getW(Vec3 Pin); 

    void printObj() override;
};