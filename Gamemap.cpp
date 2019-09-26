#include "pch.h"
#include "Gamemap.h"
#include <cctype>
#include <iomanip>
#include <string>
#include <algorithm>
#include <cctype>
Gamemap::Gamemap() noexcept {
	ChooseSize();
	drawMap();
}

template <class T, class X >
constexpr bool look_for(const T & set, const X sought) {
	return std::find(std::begin(set), std::end(set), sought) != std::end(set);
}

template<typename T>
constexpr bool checkForAlpha(const T &container) {
	for (const auto &it : container) {
		if (isalpha(it))
			return true;
	}
	return false;
}

void Gamemap::ChooseSize() {
	char uChoice;
	do {
		std::cout << "Choose size of map:\n[1]Small\n[2]Medium\n[3]Big\n[4]Rules\n";
		uChoice = SafelyGetUserInput();
		switch (uChoice) {
		case '1':
			msize = MapSize::Small; break;
		case '2':
			msize = MapSize::Medium; break;
		case '3':
			msize = MapSize::Big; break;
		case '4':
			showRules(); break;
		}
	} while (uChoice == '4');
}

void Gamemap::RedrawMap() {
	std::cout << "RedrawMap()\n";
}

void Gamemap::LetPlayerPlaceShips() {
	std::cout << "Place your ships in formula: [Type][Orientation][Coordinates]\n"
		<< "Example: CVA4 ([Carrier][Vertical][Coordinates A4])\n";
	std::cout << "Type here: ";
	getUserData();
}

void Gamemap::PlaceShipsByAI() {
	std::cout << "PlaceShipsByAI();\n";
}

void writeLetters(size_t);
void printMap(size_t);

void Gamemap::drawMap() {
	switch (msize) {
	case MapSize::Small:
		mapSize = smallMapDimensions;
		std::cout << "   ";
		writeLetters(smallMapDimensions);
		printMap(smallMapDimensions);
		break;

	case MapSize::Medium:
		mapSize = mediumMapDimensions;
		std::cout << "   ";
		writeLetters(mediumMapDimensions);
		printMap(mediumMapDimensions);
		break;

	case MapSize::Big:
		mapSize = bigMapDimensions;
		std::cout << "   ";
		writeLetters(bigMapDimensions);
		printMap(bigMapDimensions);
		break;
	} 
}

void Gamemap::showRules() const {
	std::cout << "\nRules are pretty simple:\nWhen map is ready, first thing what you have to do is to\n"
		"select ship and type exact coordinates you want to put ship at using formula\n"
		"[Type][Orientation][Coordinates] like in this example:\n"
		"user input: CVA4\t([Carrier][Vertical][Coordinates A4])\n"
		"Place like that all of your ships and you're done :)\n\n";
}

size_t Gamemap::getMapSize() {
	return mapSize;
}

auto SafelyGetUserInput() -> char {
	char uInput = _getch();
	while (!look_for("1234", uInput)) {
		std::cout << "Please type 1, 2, 3 or 4.\n";
		uInput = _getch();
	}
	return uInput;
}

void writeLetters(size_t amount) {
	for (size_t character = 65; character < amount + 65; ++character)
		std::cout << static_cast<char>(character) << " ";
	std::cout << '\n';
}

void printMap(size_t amount) {
	for (size_t i = 0; i < amount; ++i) {
		std::cout << std::setw(2);
		std::cout << i + 1 << " ";
		for (size_t j = 0; j < amount; ++j)
			std::cout << ". ";
		std::cout << '\n';
	}
}

void Gamemap::getUserData() {
	std::string userInput;
	std::getline(std::cin, userInput);
	while(!checkIfInputIsCorrect(userInput)) {
		placeShipOnMap(userInput);


		std::getline(std::cin, userInput);
	}
	std::cout << "all input tests passed\n";
}

void Gamemap::placeShipOnMap(const std::string &input) {
	std::cout << "XD";
}

bool checkProperTypeOfShip(char);
bool checkOrientation(char);

bool Gamemap::checkIfInputIsCorrect(std::string & userInput) {
	std::string coords;
	if (userInput.length() < 4) {
		std::cout << "Missing data.\n";
		return false;
	}

	else if (userInput.length() == 4) {
		coords.push_back(userInput[2]);
		coords.push_back(userInput[3]);
	}

	else if (userInput.length() == 5) {
		for (size_t i = 2; i < 5; ++i)
			coords.push_back(userInput[i]);
	}

	else {
		std::cout << "Too high number.\n";
		return false;
	}

	bool shipsGood = checkProperTypeOfShip(userInput[0]);
	bool orientationGood = checkOrientation(userInput[1]);
	bool coordinatesGood = checkCoordinates(coords);

	if (shipsGood && orientationGood && coordinatesGood)
		return true;
	else
		return false;
}

bool checkProperTypeOfShip(char shipType) {
	if (!look_for("BDICbdic", shipType)) { 
		std::cout << "Wrong type of the ship (type B/D/I/C).\n";
		return false;
	}
	else
		return true;
}

bool checkOrientation(char orientation) {
	if (orientation == 'H' || orientation == 'h' || orientation == 'V' || orientation == 'v')
		return true;
	else {
		std::cout << "Wrong orientation (type V or H).\n";
		return false;
	}
}

bool Gamemap::checkCoordinates(std::string & coords) {
	std::transform(coords.begin(), coords.end(), coords.begin(), ::toupper);
	std::string digits;
	digits.push_back(coords[1]);
	if (coords.length() == 3)
		digits.push_back(coords[2]);

	bool alphaGood = checkAlpha(coords[0]);
	bool numberGood = checkNumber(digits);

	if (numberGood == true && alphaGood == true)
		return true;
	else
		return false;
}

bool Gamemap::checkAlpha(char letter) {
	for (size_t character = 65; character < mapSize + 65; ++character) { 
		if (static_cast<char>(character) == letter)
			return true;
	}
	std::cout << "You entered wrong character.\n";
	return false;
}

bool Gamemap::checkNumber(const std::string & numbers) {
	if (checkForAlpha(numbers))
		return false;

	for (size_t number = 1; number <= mapSize; ++number) {
		if (number == std::stoi(numbers))
			return true;
	}
	std::cout << "You entered wrong number.\n";
	return false;
}
