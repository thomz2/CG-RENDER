#include "./Luz.h"
#include <vector>
#include "../primitives/Objeto.h"
#include "../materiais/BaseMaterial.h"
#pragma once

using namespace std;

class LuzPontual : public Luz {
public:
    LuzPontual(Vec3 posicao, Vec3 intensidade);
    Vec3 calcIntensity(vector<Objeto*> objs, LPointGetType retorno, Ray raycaster, BaseMaterial material);

};