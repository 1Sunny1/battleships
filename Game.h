#ifndef GAME_H_
#define GAME_H_
#include "Gamemap.h"
#include <memory>

namespace Game {
	void Prepare() {
		auto obj = std::make_unique<Gamemap>();
		obj->LetPlayerPlaceShips();
		obj->PlaceShipsByAI();
	}
	void Encounter() {
		std::cout << "encounter();\n";
		//for(;;)
			//fight until one player wins
	}
}

#endif