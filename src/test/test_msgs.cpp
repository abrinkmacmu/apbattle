#include <iostream>
#include <string>
#include <apbattle/bship_common.h>

int main() {

	std::cout << "\nTesting Guess Messages now...\n";

	std::cout << bship::createGuessMsg(0) << "\n";
	std::cout << bship::createGuessMsg(50) << "\n";
	std::cout << bship::createGuessMsg(99) << "\n";

	std::cout << "\nTesting Response Messages now...\n";


	bship::HitStatus hs = bship::Hit;
	bship::ShipName sn = bship::Carrier;

	std::cout << bship::createResponseMsg(hs, sn, false) << "\n";
	hs = bship::Miss;
	sn = bship::None;

	std::cout << bship::createResponseMsg(hs, sn, false) << "\n";
	hs = bship::Hit;
	sn = bship::Battleship;

	std::cout << bship::createResponseMsg(hs, sn, true) << "\n";


	std::cout << "\nTesting Connection Messages now...\n";

	std::cout << bship::createConnectionMsg(true, false) << "\n";
	std::cout << bship::createConnectionMsg(false, true) << "\n";

}