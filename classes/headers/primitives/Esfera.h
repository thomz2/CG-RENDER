#pragma once

#include <optional>
#include "../math/Vec3.h"
#include "../math/Vec4.h"
#include "../math/Transformations.h"
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
    void update(Vec3 c, double raio = -1);

    int printObj(bool printMenu = false) override;
    void handleChange(int option) override;

};