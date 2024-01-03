#include "Board.cpp"
#include <iostream>
#include <string>

int main() {
	Board main_board;
	std::string input;

	std::cout << "Aaron's Sudoku board generator - 2023\n" << std::endl;

	do {
		std::cout << "Type \"generate\" to generate a board, or \"exit\" to exit: ";
		std::cin >> input;
		if (input == "exit")
			return EXIT_SUCCESS;

		std::cout << "\nGenerating...\n";
		main_board.generate();
		std::cout << main_board.tostring() << std::endl;
		if (main_board.validate()) {
			std::cout << "Board is valid!" << std::endl;
		}
		else {
			std::cout << "Board is not valid!" << std::endl;
		}
		std::cout << std::endl;
	}
	while (true);
}