#include <stdlib.h>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include <random>
#include <iostream>

class Board {
	struct Cell {
		int _value;

		Cell(int value) {
			_value = value;
		}
	};

	class SubBoard {
		std::vector<Cell*> _cells;

	public:
		SubBoard() {}

		void populate(Cell* cells[]) {
			for (int i = 0; i < 9; ++i) {
				_cells.push_back(cells[i]);
			}
		}

		bool contains(Cell* cellToFind) {
			for (Cell* cell : _cells) {
				if (cell == cellToFind)
					return true;
			}
			return false;
		}

		//validates that there are no duplicate values within a sub-board
		bool validate() {
			std::vector<int> values;
			for (Cell* cell : _cells) {
				for (int i = 0; i < values.size(); ++i) {
					if (cell->_value == 0) break;

					if (cell->_value == values[i]) {
						return false;
					}
				}
				if (cell->_value != 0)
					values.push_back(cell->_value);
			}
			return true;
		}
	};

	/*
  * Struct:     Rand
  * Author:     Aaron Rader
  * Purpose:    A simple structure containing a vector of up to 9 digits and a function to
  *             randomly generate those digits
  */
	struct Rand {
	private:
		std::vector<int> _tested;

	public:
		int next() {
			int n;
			bool okay = false;

			while (!okay) {
				n = std::rand() % 9 + 1;
				okay = true;
				for (int t : _tested) {
					if (n == t) {
						okay = false;
						break;
					}
				}
			}
			_tested.push_back(n);
			return n;
		}
	};

	//used for checking valid values
	SubBoard column1, column2, column3, column4, column5, column6, column7, column8, column9;
	SubBoard row1, row2, row3, row4, row5, row6, row7, row8, row9;
	SubBoard nwblock, nblock, neblock;
	SubBoard wblock, cblock, eblock;
	SubBoard swblock, sblock, seblock;

	std::vector<SubBoard*> _subboards = {
	  &column1, &column2, &column3, &column4, &column5, &column6, &column7, &column8, &column9,
	  &row1, &row2, &row3, &row4, &row5, &row6, &row7, &row8, &row9,
	  &nwblock, &nblock, &neblock, &wblock, &cblock, &eblock, &swblock, &sblock, &seblock
	};

	std::vector<Cell> _cells;

public:

	Board() {
		//Generate a board
		//_cells = {
		//	Cell(4), Cell(1), Cell(5), Cell(9), Cell(6), Cell(2), Cell(3), Cell(7), Cell(8),
		//	Cell(7), Cell(6), Cell(3), Cell(1), Cell(8), Cell(5), Cell(4), Cell(2), Cell(9),
		//	Cell(9), Cell(2), Cell(8), Cell(3), Cell(7), Cell(4), Cell(5), Cell(6), Cell(1),
		//	Cell(1), Cell(5), Cell(7), Cell(4), Cell(9), Cell(6), Cell(8), Cell(3), Cell(2),
		//	Cell(2), Cell(8), Cell(4), Cell(7), Cell(5), Cell(3), Cell(1), Cell(9), Cell(6),
		//	Cell(3), Cell(9), Cell(6), Cell(2), Cell(1), Cell(8), Cell(7), Cell(4), Cell(5),
		//	Cell(6), Cell(7), Cell(2), Cell(5), Cell(3), Cell(1), Cell(9), Cell(8), Cell(4),
		//	Cell(8), Cell(3), Cell(1), Cell(6), Cell(4), Cell(9), Cell(2), Cell(5), Cell(7),
		//	Cell(5), Cell(4), Cell(9), Cell(8), Cell(2), Cell(7), Cell(6), Cell(1), Cell(3)
		//};

		//Zero initialize all cells - validator skips cells with a value of 0
		for (int i = 0; i < 81; ++i) {
			_cells.push_back(Cell(0));
		}

		std::srand(time(nullptr));

		//Assign memory locations of cells to sub-boards
		//Columns
		_subboards[0]->populate(new Cell * [] { &_cells[0], & _cells[9], & _cells[18], & _cells[27], & _cells[36], & _cells[45], & _cells[54], & _cells[63], & _cells[72] });
		_subboards[1]->populate(new Cell * [] { &_cells[1], & _cells[10], & _cells[19], & _cells[28], & _cells[37], & _cells[46], & _cells[55], & _cells[64], & _cells[73] });
		_subboards[2]->populate(new Cell * [] { &_cells[2], & _cells[11], & _cells[20], & _cells[29], & _cells[38], & _cells[47], & _cells[56], & _cells[65], & _cells[74] });
		_subboards[3]->populate(new Cell * [] { &_cells[3], & _cells[12], & _cells[21], & _cells[30], & _cells[39], & _cells[48], & _cells[57], & _cells[66], & _cells[75] });
		_subboards[4]->populate(new Cell * [] { &_cells[4], & _cells[13], & _cells[22], & _cells[31], & _cells[40], & _cells[49], & _cells[58], & _cells[67], & _cells[76] });
		_subboards[5]->populate(new Cell * [] { &_cells[5], & _cells[14], & _cells[23], & _cells[32], & _cells[41], & _cells[50], & _cells[59], & _cells[68], & _cells[77] });
		_subboards[6]->populate(new Cell * [] { &_cells[6], & _cells[15], & _cells[24], & _cells[33], & _cells[42], & _cells[51], & _cells[60], & _cells[69], & _cells[78] });
		_subboards[7]->populate(new Cell * [] { &_cells[7], & _cells[16], & _cells[25], & _cells[34], & _cells[43], & _cells[52], & _cells[61], & _cells[70], & _cells[79] });
		_subboards[8]->populate(new Cell * [] { &_cells[8], & _cells[17], & _cells[26], & _cells[35], & _cells[44], & _cells[53], & _cells[62], & _cells[71], & _cells[80] });

		//Rows
		_subboards[9]->populate(new Cell * [] { &_cells[0], & _cells[1], & _cells[2], & _cells[3], & _cells[4], & _cells[5], & _cells[6], & _cells[7], & _cells[8] });
		_subboards[10]->populate(new Cell * [] { &_cells[9], & _cells[10], & _cells[11], & _cells[12], & _cells[13], & _cells[14], & _cells[15], & _cells[16], & _cells[17] });
		_subboards[11]->populate(new Cell * [] { &_cells[18], & _cells[19], & _cells[20], & _cells[21], & _cells[22], & _cells[23], & _cells[24], & _cells[25], & _cells[26] });
		_subboards[12]->populate(new Cell * [] { &_cells[27], & _cells[28], & _cells[29], & _cells[30], & _cells[31], & _cells[32], & _cells[33], & _cells[34], & _cells[35] });
		_subboards[13]->populate(new Cell * [] { &_cells[36], & _cells[37], & _cells[38], & _cells[39], & _cells[40], & _cells[41], & _cells[42], & _cells[43], & _cells[44] });
		_subboards[14]->populate(new Cell * [] { &_cells[45], & _cells[46], & _cells[47], & _cells[48], & _cells[49], & _cells[50], & _cells[51], & _cells[52], & _cells[53] });
		_subboards[15]->populate(new Cell * [] { &_cells[54], & _cells[55], & _cells[56], & _cells[57], & _cells[58], & _cells[59], & _cells[60], & _cells[61], & _cells[62] });
		_subboards[16]->populate(new Cell * [] { &_cells[63], & _cells[64], & _cells[65], & _cells[66], & _cells[67], & _cells[68], & _cells[69], & _cells[70], & _cells[71] });
		_subboards[17]->populate(new Cell * [] { &_cells[72], & _cells[73], & _cells[74], & _cells[75], & _cells[76], & _cells[77], & _cells[78], & _cells[79], & _cells[80] });

		// Northwest Section
		_subboards[18]->populate(new Cell * [] {&_cells[0], & _cells[1], & _cells[2], & _cells[9], & _cells[10], & _cells[11], & _cells[18], & _cells[19], & _cells[20] });

		// North Section
		_subboards[19]->populate(new Cell * [] { &_cells[3], & _cells[4], & _cells[5], & _cells[12], & _cells[13], & _cells[14], & _cells[21], & _cells[22], & _cells[23] });

		// Northeast Section
		_subboards[20]->populate(new Cell * [] { &_cells[6], & _cells[7], & _cells[8], & _cells[15], & _cells[16], & _cells[17], & _cells[24], & _cells[25], & _cells[26] });

		// West Section
		_subboards[21]->populate(new Cell * [] { &_cells[27], & _cells[28], & _cells[29], & _cells[36], & _cells[37], & _cells[38], & _cells[45], & _cells[46], & _cells[47] });

		// Center Section
		_subboards[22]->populate(new Cell * [] { &_cells[30], & _cells[31], & _cells[32], & _cells[39], & _cells[40], & _cells[41], & _cells[48], & _cells[49], & _cells[50] });

		// East Section
		_subboards[23]->populate(new Cell * [] { &_cells[33], & _cells[34], & _cells[35], & _cells[42], & _cells[43], & _cells[44], & _cells[51], & _cells[52], & _cells[53] });

		// Southwest Section
		_subboards[24]->populate(new Cell * [] { &_cells[54], & _cells[55], & _cells[56], & _cells[63], & _cells[64], & _cells[65], & _cells[72], & _cells[73], & _cells[74] });

		// South Section
		_subboards[25]->populate(new Cell * [] { &_cells[57], & _cells[58], & _cells[59], & _cells[66], & _cells[67], & _cells[68], & _cells[75], & _cells[76], & _cells[77] });

		// Southeast Section
		_subboards[26]->populate(new Cell * [] { &_cells[60], & _cells[61], & _cells[62], & _cells[69], & _cells[70], & _cells[71], & _cells[78], & _cells[79], & _cells[80] });
	}

	void generate() {
		time_t starttime;
		int start;
		bool succeeded;

		do {
			//reset all cells
			for (int i = 0; i < 81; ++i) {
				_cells[i]._value = 0;
			}

			starttime = time(nullptr);
			start = std::rand() % 81;
			succeeded = generate(starttime, start);
			if (!succeeded) {
				std::cout << "Generation failed - trying again..." << std::endl;
			}
		} while (!succeeded);
	}

	/*
	* Function:		validate
	* Author:		Aaron Rader
	* Purpose:		Validates the board
	*				Optional argument to validate only sub boards containing the given cell
	* Args:			cell - optional to dictate which sub boards to validate
	* Returns:		a boolean value indicating if the board is valid
	*/
	bool validate(Cell* cell = nullptr) {
		for (SubBoard* sub : _subboards) {
			if (cell && !sub->contains(cell)) //skip validating if cell is not contained in this sub board
				continue;
			if (!sub->validate())
				return false;
		}
		return true;
	}

	std::string tostring() {
		std::string boardstring;
		for (int i = 0; i < 9; ++i) {
			if (i % 3 == 0)
				boardstring += "-------------------------\n";
			for (int j = 0; j < 9; ++j) {
				if (j % 3 == 0)
					boardstring += "| ";
				boardstring += std::to_string(_cells[(i * 9) + j]._value) += ' ';
			}
			boardstring += "|\n";
		}
		boardstring += "-------------------------";
		return boardstring;
	}

private:

	/*
	* Function:		generate
	* Author:		Aaron Rader
	* Purpose:		Recursively generates one cell at a time, validating the board as it goes
	*				If the cell generated is not valid with any digit, go back to the last cell and try the next digit
	* Args:			i - the cell to generate
	*				t - a starting time to compare the algorithm's running time against
	*				count - a value to keep track of how many total cells have been generated
	* Returns:		a boolean value indicating if the generated cell contains a value that keeps the board valid
	*/
	bool generate(time_t t, int i, int count = 0) {
		/*
		* False Exit Statements:
		* 1 - if i is equal to the starting index, the generation is complete
		* 2 - if time elapsed is greater than 1 second, stop the generation
		*/
		if (isfilled())
			return true;
		if (time(nullptr) - t > 1 || count > 80)
			return false;

		Rand num_generator;

		if (i > 80)
			i = 0;

		//repeat testing random numbers up to 9 times
		for (int j = 0; j < 9; ++j) {
			_cells[i]._value = num_generator.next();
			if (validate(&_cells[i]) && generate(t, i + 1, count + 1)) {
				return true;
			}
		}

		_cells[i]._value = 0; //If no values work for this cell, reset the value to 0 so the validation works
		return false;
	}

	bool isfilled() {
		for (int i = 0; i < 81; ++i) {
			if (_cells[i]._value == 0)
				return false;
		}
		return true;
	}
};