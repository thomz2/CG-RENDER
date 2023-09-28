// Interface.h
#pragma once

#include "../math/Vec3.h"

class BaseMaterial {
 
private:
    Vec3 RUGOSIDADE;
    Vec3 REFLETIVIDADE;
    Vec3 KAMBIENTE;
    double M;

public:
    BaseMaterial();
    BaseMaterial(Vec3 RUGOSIDADE, Vec3 REFLETIVIDADE, Vec3 KAMBIENTE, double M);
    BaseMaterial(Vec3 RUGOSIDADE, Vec3 REFLETIVIDADE, double M);
    

    Vec3 getRugosidade();
    Vec3 getRefletividade();
    Vec3 getKAmbiente();
    double getM();

};

