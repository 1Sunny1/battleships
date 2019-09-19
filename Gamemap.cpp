#include "pch.h"
#include "Gamemap.h"
#include <cctype>
#include <iomanip>
#include <string>
#include <algorithm>
Gamemap::Gamemap() noexcept {
	ChooseSize();
	drawMap();
}

void Gamemap::ChooseSize() {
	std::cout << "Choose size of map:\n[1]Small\n[2]Medium\n[3]Big\n[4]Rules\n";
	char uChoice = SafelyGetUserInput();
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
}

void Gamemap::RedrawMap() {
	std::cout << "RedrawMap()\n";
}

void getUserData();

void Gamemap::LetPlayerPlaceShips() {
	std::cout << "Place your ships in formula: [Type][Orientation][Coordinates]\n"
		<< "Example: CVA4 ([Carrier][Vertical][Coordinates A4])\n";
	std::cout << "Type here: ";
	getUserData();
}

void Gamemap::PlaceShipsByAI() {
	std::cout << "PlaceShipsByAI()\n";
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
	std::cout << "\nRules are pretty simple:\nWhen map is ready, firstly what you have to do is to\n"
		<< "select ship and type exact coordinates you want to put ship at.\n"
		<< "Then say if you want place ship horizontally or vertically.\n"
		<< "Place like that all of your ships and you're done :)\n";
}

size_t Gamemap::getMapSize() {
	return mapSize;
}

auto SafelyGetUserInput() -> char {
	char uInput = _getch();
	while (std::strchr("1234", uInput) == nullptr) {
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

bool checkIfInputIsCorrect(std::string &);

void getUserData() {
	std::string userInput;
	std::getline(std::cin, userInput);
	while(!checkIfInputIsCorrect(userInput)) {
		std::getline(std::cin, userInput);
	}
	std::cout << "all input tests passed\n";
}

bool checkProperTypeOfShip(char);
bool checkOrientation(char);
bool checkCoordinates(std::string &);

bool checkIfInputIsCorrect(std::string & userInput) {
	if (userInput.length() < 4) {
		std::cout << "Missing data.\n";
		return false;
	}
	bool shipsGood = checkProperTypeOfShip(userInput[0]);
	bool orientationGood = checkOrientation(userInput[1]);
	std::string coords;
	if (userInput.length() == 4) {
		coords.push_back(userInput[2]);
		coords.push_back(userInput[3]);
	}

	if (userInput.length() == 5) {
		for (size_t i = 2; i < 5; ++i)
			coords.push_back(userInput[i]);
	}

	if (userInput.length() > 5) {
		std::cout << "Too high number.\n";
		return false;
	}
	bool coordinatesGood = checkCoordinates(coords);
	if (shipsGood && orientationGood && coordinatesGood)
		return true;
	else
		return false;
}

bool checkProperTypeOfShip(char shipType) {
	if (std::strchr("BDICbdic", shipType) == nullptr) {
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

bool checkAlpha(char);
bool checkNumber(std::string);

bool checkCoordinates(std::string & coords) {
	std::transform(coords.begin(), coords.end(), coords.begin(), ::toupper);
	std::string digits;
	digits.push_back(coords[1]);
	if (coords.length() == 3)
		digits.push_back(coords[2]);

	bool alphaGood = checkAlpha(coords[0]);
	bool numberGood = checkNumber(digits);
	
	if (!alphaGood)
		std::cout << "You entered wrong character.\n";
	if (!numberGood)
		std::cout << "You entered wrong number.\n";

	if (numberGood == true && alphaGood == true)
		return true;
	else
		return false;
}

bool checkAlpha(char letter) {
	for (size_t character = 65; character < 20 + 65; ++character) { //!!ACTUALLY WORKS ONLY AT MEDIUM MAP!! because static mapsize isn't init, program won't compile
		if (static_cast<char>(character) == letter)
			return true;
	}
	return false;
}

bool checkNumber(std::string numbers) {
	for (size_t number = 1; number <= 20; ++number) { //later get rid of these 20's in loops
		if (number == std::stoi(numbers))
			return true;
	}
	return false;
}