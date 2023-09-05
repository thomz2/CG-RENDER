#include <SDL2/SDL.h>
#include <optional>
#include "../../headers/primitives/Objeto.h"
#include "../../headers/Ray.h"

using namespace std;

Objeto::Objeto(int id, SDL_Color cor) : id(id), cor(cor) {}

Objeto::Objeto(int id) : id(id), cor(std::nullopt) {};

// bool Objeto::intersecta(Ray raycaster) const {};