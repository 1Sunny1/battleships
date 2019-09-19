#ifndef GAMEMAP_H_
#define GAMEMAP_H_
#include <conio.h>
#include <iostream>
class Gamemap {
public:
	explicit Gamemap() noexcept;
	void ChooseSize();
	enum class MapSize { Small, Medium, Big };
	void RedrawMap();
	void LetPlayerPlaceShips();
	void PlaceShipsByAI();
	void drawMap();
	void showRules() const;
	size_t getMapSize();
private:
	MapSize msize;
	const size_t smallMapDimensions{10};
	const size_t mediumMapDimensions{20};
	const size_t bigMapDimensions{30};
	size_t mapSize;
};

inline auto SafelyGetUserInput() -> char;
#endif // !GAMEMAP_H_