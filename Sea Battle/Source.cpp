
#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <ctime>
#include <iterator>
#include <cassert>

//#define DEBUG

constexpr auto VerticalParallels = char(186); //║
constexpr auto AngleRightDown = char(201); //╔
constexpr auto AngleLeftDown = char(187); //╗
constexpr auto AngleRightUp = char(200); //╚
constexpr auto AngleLeftUp = char(188); //╝
constexpr auto VerticalParallLeft = char(185); //╣
constexpr auto VerticalParallRight = char(204); //╠
constexpr auto HorizontalParallDown = char(203); //╦
constexpr auto HorizontalParallUp = char(202); //╩
constexpr auto DoubleCross = char(206); //╬
constexpr auto HorizontalParallels = char(205); //═

std::map <std::string, int> Alphabet;

std::map <int, char> Designation = { {0,/*char(249)*/ ' '} ,{1,char(254)},{2,char(254)}, {3,char(254)}, {4,char(254)}, {5,char(177)}, {6, char(111)}, {7,char(88)} };

/*
0 - пустое поле
1 - однопалубный
2 - двупалубный
3 - трехпалубный
4 - четырехпалубный
5 - мимо
6 - подбит
7 - убит
*/

struct game {
	short X, Y;
	bool fl = false, ifGameOver = false;
	const char* ABC[26]{ "A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z" };
	int indABC = 0, indNum = 0, indABC2 = 0, indNum2 = 0;
	std::vector <std::vector <int> > Myfield;
	std::vector <std::vector <int> > Enemyfield;
	std::vector <std::vector <int> > EnemyMapOfShots;
	std::vector <std::vector <int> > MyMapOfShots;

	void initialization() {
		std::cout << "Enter number of cells in vertical coordinates: ";
		std::cin >> X;
		std::cout << "Enter number of cells in horizontal coordinates: ";
		std::cin >> Y;
		if (std::cin.fail()) {
			std::cerr <<"\n\n\-----------------------------------------------------------\n";
			std::cerr << char(179) << "ERROR: INCORRECT COORDINATES! The programm will close now" << char(179) << std::endl;
			std::cerr << "-----------------------------------------------------------\n\n";
			system("pause");
			exit(1);
		}
		Myfield.resize(X);
		Enemyfield.resize(X);
		MyMapOfShots.resize(X);
		EnemyMapOfShots.resize(X);
		for (int i = 0; i < X; i++) {
			Myfield[i].resize(Y);
			Enemyfield[i].resize(Y);
			EnemyMapOfShots[i].resize(Y);
			MyMapOfShots[i].resize(Y);
		}
	}
	void firstFilling(std::vector <std::vector <int> > vec) {
		for (int i = 0; i < X; i++) {
			for (int j = 0; j < Y; j++) {
				vec[i][j] = 0; 
			}
		}
	}
	void OutputMaps(std::vector <std::vector <int> > vec, std::vector <std::vector <int> > vec2) {

		std::cout << "    " << AngleRightDown;


		/*Drawing cap of left map
		==========================================*/
		for (int i = 0; i < Y; i++) {
			std::cout << HorizontalParallels << HorizontalParallels << HorizontalParallels;
			if (i != Y - 1)
				std::cout << HorizontalParallDown;
			else
				std::cout << AngleLeftDown;
		}
		//-----------------------------------------
		std::cout << "          ";
		std::cout << "    " << AngleRightDown;
		/*Drawing cap of right map
		==========================================*/
		for (int i = 0; i < Y; i++) {
			std::cout << HorizontalParallels << HorizontalParallels << HorizontalParallels;
			if (i != Y - 1)
				std::cout << HorizontalParallDown;
			else
				std::cout << AngleLeftDown;
		}
		//-----------------------------------------
		std::cout << std::endl << "    ";

		/*Drawing A,B,C... of left map
		==========================================*/
		for (int i = 0; i < Y; i++) {
			std::cout << VerticalParallels << " " << ABC[indABC] << " ";
			indABC++;
			if (i == Y - 1)
				std::cout << VerticalParallels;
		}
		//-----------------------------------------

		std::cout << "              ";

		/*Drawing A,B,C... of right map
		==========================================*/
		for (int i = 0; i < Y; i++) {
			std::cout << VerticalParallels << " " << ABC[indABC2] << " ";
			indABC2++;
			if (i == Y - 1)
				std::cout << VerticalParallels;
		}
		//-----------------------------------------

		std::cout << std::endl;

		/*Drawing bottom of caps: 
		==========================================*/
		for (int i = 0; i < X; i++) {
			if (!fl) {
				//Drawing cap of i row of left map after first cap with A,B,C..
				for (int j = 0; j <= Y + 1; j++) {
					if (j == 0) {
						std::cout << AngleRightDown;
						std::cout << HorizontalParallels << HorizontalParallels << HorizontalParallels;
					}
					else {
						if (j == Y + 1)
							std::cout << VerticalParallLeft;
						else {
							std::cout << DoubleCross;
							std::cout << HorizontalParallels << HorizontalParallels << HorizontalParallels;
						}
					}

				}
				//-----------------------------------------
				std::cout << "          ";
				
				//Drawing cap of i row of right map after first cap with A,B,C..
				for (int j = 0; j <= Y + 1; j++) {
					if (j == 0) {
						std::cout << AngleRightDown;
						std::cout << HorizontalParallels << HorizontalParallels << HorizontalParallels;
					}
					else {
						if (j == Y + 1)
							std::cout << VerticalParallLeft;
						else {
							std::cout << DoubleCross;
							std::cout << HorizontalParallels << HorizontalParallels << HorizontalParallels;
						}
					}

				}
				fl = true; // if you draw at least once cap of first row, you mustn't do it again
				std::cout << std::endl;
			}




			//Drawing middle lines of two maps
			//====================================


			std::cout << VerticalParallels;
			
			if (indNum < 10)
				std::cout << " ";
			std::cout << std::to_string(indNum) << " ";
			indNum++;

			for (int j = 0; j < Y; j++) {

				std::cout << VerticalParallels << " " << Designation.find(vec[i][j])->second << " ";
				if (j == Y - 1)
					std::cout << VerticalParallels;

			}

			std::cout << "          ";

			std::cout << VerticalParallels;
			if (indNum2 < 10)
				std::cout << " ";
			std::cout << std::to_string(indNum2) << " ";
			indNum2++;

			for (int j = 0; j < Y; j++) {

				std::cout << VerticalParallels << " " << Designation.find(vec2[i][j])->second << " ";
				if (j == Y - 1)
					std::cout << VerticalParallels;

			}

			//====================================



			std::cout << std::endl;


			/*Рисование 3-ей линии(нижней)
			======================================*/
			for (int j = 0; j <= Y; j++) {
				if (i == X - 1) {
					if (j == 0) {
						std::cout << AngleRightUp << HorizontalParallels << HorizontalParallels << HorizontalParallels;
					}
					else {
						std::cout << HorizontalParallUp << HorizontalParallels << HorizontalParallels << HorizontalParallels;
						if (j == Y) {
							std::cout << AngleLeftUp;
						}
					}
				}
				else {
					if (j == 0) {
						std::cout << VerticalParallRight << HorizontalParallels << HorizontalParallels << HorizontalParallels;
					}
					else {
						std::cout << DoubleCross << HorizontalParallels << HorizontalParallels << HorizontalParallels;
						if (j == Y)
							std::cout << VerticalParallLeft;
					}
					//std::cout << DoubleCross;
					//std::cout << HorizontalParallels << HorizontalParallels << HorizontalParallels;
				}

			}
			//=============================================
			std::cout << "          ";


			for (int j = 0; j <= Y; j++) {
				if (i == X - 1) {
					if (j == 0) {
						std::cout << AngleRightUp << HorizontalParallels << HorizontalParallels << HorizontalParallels;
					}
					else {
						std::cout << HorizontalParallUp << HorizontalParallels << HorizontalParallels << HorizontalParallels;
						if (j == Y) {
							std::cout << AngleLeftUp;
						}
					}
				}
				else {
					if (j == 0) {
						std::cout << VerticalParallRight << HorizontalParallels << HorizontalParallels << HorizontalParallels;
					}
					else {
						std::cout << DoubleCross << HorizontalParallels << HorizontalParallels << HorizontalParallels;
						if (j == Y)
							std::cout << VerticalParallLeft;
					}
					//std::cout << DoubleCross;
					//std::cout << HorizontalParallels << HorizontalParallels << HorizontalParallels;
				}

			}

			std::cout << std::endl;
		}

		indABC = 0;
		indABC2 = 0;
		fl = false;
		indNum = 0;
		indNum2 = 0;
	}
	void OutputSetShips(std::vector <std::vector <int> > vec) {

		std::cout << "    " << AngleRightDown;


		/*Рисование букв A,B..
		==========================================*/
		for (int i = 0; i < Y; i++) {
			std::cout << HorizontalParallels << HorizontalParallels << HorizontalParallels;
			if (i != Y - 1)
				std::cout << HorizontalParallDown;
			else
				std::cout << AngleLeftDown;
		}


		std::cout << std::endl << "    ";



		for (int i = 0; i < Y; i++) {
			std::cout << VerticalParallels << " " << ABC[indABC] << " ";
			indABC++;
			if (i == Y - 1)
				std::cout << VerticalParallels;
		}
		//=============================================


		std::cout << std::endl;

		for (int i = 0; i < X; i++) {
			if (!fl) {
				for (int j = 0; j <= Y + 1; j++) {
					if (j == 0) {
						std::cout << AngleRightDown;
						std::cout << HorizontalParallels << HorizontalParallels << HorizontalParallels;
					}
					else {
						if (j == Y + 1)
							std::cout << VerticalParallLeft;
						else {
							std::cout << DoubleCross;
							std::cout << HorizontalParallels << HorizontalParallels << HorizontalParallels;
						}
					}

				}
				fl = true;
				std::cout << std::endl;
			}




			//РИсование средней линии
			//====================================


			std::cout << VerticalParallels;
			if (indNum < 10)
				std::cout << " ";
			std::cout << std::to_string(indNum) << " ";
			indNum++;

			for (int j = 0; j < Y; j++) {

				std::cout << VerticalParallels << " " << Designation.find(vec[i][j])->second << " ";
				if (j == Y - 1)
					std::cout << VerticalParallels;

			}
			//====================================

			std::cout << std::endl;


			/*Рисование 3-ей линии(нижней)
			======================================*/
			for (int j = 0; j <= Y; j++) {
				if (i == X - 1) {
					if (j == 0) {
						std::cout << AngleRightUp << HorizontalParallels << HorizontalParallels << HorizontalParallels;
					}
					else {
						std::cout << HorizontalParallUp << HorizontalParallels << HorizontalParallels << HorizontalParallels;
						if (j == Y) {
							std::cout << AngleLeftUp;
						}
					}
				}
				else {
					if (j == 0) {
						std::cout << VerticalParallRight << HorizontalParallels << HorizontalParallels << HorizontalParallels;
					}
					else {
						std::cout << DoubleCross << HorizontalParallels << HorizontalParallels << HorizontalParallels;
						if (j == Y)
							std::cout << VerticalParallLeft;
					}

				}

			}
			//=============================================


			std::cout << std::endl;
		}
		indABC = 0;
		fl = false;
		indNum = 0;
	}
	bool vicinity(int verticalCoordinate, int horizotalCoordinate, std::vector <std::vector< int >> mapOfGame, bool AI) {

		for (int i = verticalCoordinate - 1; i <= verticalCoordinate + 1; i++) {
			for (int j = horizotalCoordinate - 1; j <= horizotalCoordinate + 1; j++) {
				if (i >= 0 && i <= X - 1 && j >= 0 && j <= Y - 1) {
					if (mapOfGame[i][j] != 0) {
						if (!AI) {
							std::cout << "------------------------------------------------------------------------\n";
							std::cout << char(179) << "YOU CAN'T PLACE SHIP OR PART OF IT NEAR ANOTHER SHIP! PLEASE TRY AGAIN" << char(179) << std::endl;
							std::cout << "------------------------------------------------------------------------\n\n";
						}
						return false;
					}

				}
			}
		}
		return true;
	}
	bool seachingAndCheckAllDecks(int verticalCoordinate, int horizontalCoordinate, std::vector <std::vector<int>> mapOfGame, std::vector <std::vector<int>> mapOfShots) {
		//check left side


		int ind = 1; //for how much cells check 
		bool check;
		if (horizontalCoordinate - ind >= 0) {
			check = (mapOfGame[verticalCoordinate][horizontalCoordinate - ind] != 0);
			while (check) {
				if (mapOfShots[verticalCoordinate][horizontalCoordinate - ind] == 6) {
					ind++;
					if (horizontalCoordinate - ind >= 0) 
						check = (mapOfGame[verticalCoordinate][horizontalCoordinate - ind] != 0);
					else
						check = false;
					
				}
				else {
					if (mapOfGame[verticalCoordinate][horizontalCoordinate - ind] != 5)
						return false;
					else
						check = false;
				}
			}

		}
		//check right side
		ind = 1;
		if (horizontalCoordinate + ind < Y) {
			check = (mapOfGame[verticalCoordinate][horizontalCoordinate + ind] != 0);
			while (check) {
				if (mapOfShots[verticalCoordinate][horizontalCoordinate + ind] == 6) {
					ind++;
					if (horizontalCoordinate + ind < Y)
						check = (mapOfGame[verticalCoordinate][horizontalCoordinate + ind] != 0);
					else
						check = false;
				}
					
				else {
					if (mapOfGame[verticalCoordinate][horizontalCoordinate + ind] != 5)
						return false;
					else
						check = false;
				}
			}

		}
		//check top 
		ind = 1;
		
		if (verticalCoordinate - ind >= 0) {
			check = (mapOfGame[verticalCoordinate-ind][horizontalCoordinate] != 0);
			while (check) {
				if (mapOfShots[verticalCoordinate - ind][horizontalCoordinate] == 6) {
					ind++;
					if (verticalCoordinate - ind >= 0)
						check = (mapOfGame[verticalCoordinate - ind][horizontalCoordinate] != 0);
					else
						check = false;
				}	
				else {
					if (mapOfGame[verticalCoordinate - ind][horizontalCoordinate] != 5)
						return false;
					else
						check = false;
				}
			}

		}
		//check down
		ind = 1;

		if (verticalCoordinate + ind < X) {
			check = (mapOfGame[verticalCoordinate + ind][horizontalCoordinate] != 0);
			while (check) {
				if (mapOfShots[verticalCoordinate + ind][horizontalCoordinate] == 6) {
					ind++;
					if (verticalCoordinate + ind < X) {
						check = (mapOfGame[verticalCoordinate + ind][horizontalCoordinate] != 0);
					}
					else
						check = false;
				}	
				else {
					if (mapOfGame[verticalCoordinate + ind][horizontalCoordinate] != 5)
						return false;
					else
						check = false;
				}
			}

		}

		return true; //that mean, that all decks of ship were

	}
	void killingShip(int verticalCoordinate, int horizontalCoordinate, std::vector <std::vector<int>> &mapOfGame, std::vector <std::vector<int>> &mapOfShots) {
		int ind = 1; //for how much cells check 
		//check left side
		bool check;
		if (horizontalCoordinate - ind >= 0) {
			check = (mapOfGame[verticalCoordinate][horizontalCoordinate - ind] != 0);
			while (check) {
				if (mapOfShots[verticalCoordinate][horizontalCoordinate - ind] == 6) {
					mapOfShots[verticalCoordinate][horizontalCoordinate - ind] = 7;
					mapOfGame[verticalCoordinate][horizontalCoordinate - ind] = 7;
					for (int i = verticalCoordinate - 1; i <= verticalCoordinate + 1; i++) {
						for (int j = horizontalCoordinate - ind - 1; j <= horizontalCoordinate - ind + 1; j++) {
							if (i >= 0 && i <= X - 1 && j >= 0 && j <= Y - 1) {
								if (mapOfGame[i][j] == 0) {
									mapOfShots[i][j] = 5;
									mapOfGame[i][j] = 5;
								}
							}
						}
					}

					ind++;
					if (horizontalCoordinate - ind >= 0)
						check = (mapOfGame[verticalCoordinate][horizontalCoordinate - ind] != 0);
					else
						check = false;
				}		
				else {
					check = false;
				}

			}

		}
		//check right side
		ind = 1;
		if (horizontalCoordinate + ind < Y) {
			check = (mapOfGame[verticalCoordinate][horizontalCoordinate + ind] != 0);
			while (check) {
				if (mapOfShots[verticalCoordinate][horizontalCoordinate + ind] == 6) {
					mapOfShots[verticalCoordinate][horizontalCoordinate + ind] = 7;
					mapOfGame[verticalCoordinate][horizontalCoordinate + ind] = 7;
					for (int i = verticalCoordinate - 1; i <= verticalCoordinate + 1; i++) {
						for (int j = horizontalCoordinate + ind - 1; j <= horizontalCoordinate + ind + 1; j++) {
							if (i >= 0 && i <= X - 1 && j >= 0 && j <= Y - 1) {
								if (mapOfGame[i][j] == 0) {
									mapOfShots[i][j] = 5;
									mapOfGame[i][j] = 5;
								}
							}
						}
					}
					ind++;
					if (horizontalCoordinate + ind < Y)
						check = (mapOfGame[verticalCoordinate][horizontalCoordinate + ind] != 0);
					else
						check = false;
				}
				else {
					check = false;
				}

			}

		}
		//check top 
		ind = 1;

		if (verticalCoordinate - ind >= 0) {
			check = (mapOfGame[verticalCoordinate - ind][horizontalCoordinate] != 0);
			while (check) {
				if (mapOfShots[verticalCoordinate - ind][horizontalCoordinate] == 6) {
					mapOfShots[verticalCoordinate - ind][horizontalCoordinate] = 7;
					mapOfGame[verticalCoordinate - ind][horizontalCoordinate] = 7;
					for (int i = verticalCoordinate - ind - 1; i <= verticalCoordinate - ind + 1; i++) {
						for (int j = horizontalCoordinate - 1; j <= horizontalCoordinate + 1; j++) {
							if (i >= 0 && i <= X - 1 && j >= 0 && j <= Y - 1) {
								if (mapOfGame[i][j] == 0) {
									mapOfShots[i][j] = 5;
									mapOfGame[i][j] = 5;
								}
							}
						}
					}
	
					ind++;
					if (verticalCoordinate - ind >= 0)
						check = (mapOfGame[verticalCoordinate - ind][horizontalCoordinate] != 0);
					else
						check = false;
				}
				else {
					check = false;
				}

			}

		}
		//check down 
		ind = 1;

		if (verticalCoordinate + ind < X) {
			check = (mapOfGame[verticalCoordinate + ind][horizontalCoordinate] != 0);
			while (check) {
				if (mapOfShots[verticalCoordinate + ind][horizontalCoordinate] == 6) {
					mapOfShots[verticalCoordinate + ind][horizontalCoordinate] = 7;
					mapOfGame[verticalCoordinate + ind][horizontalCoordinate] = 7;
					for (int i = verticalCoordinate + ind - 1; i <= verticalCoordinate + ind + 1; i++) {
						for (int j = horizontalCoordinate - 1; j <= horizontalCoordinate + 1; j++) {
							if (i >= 0 && i <= X - 1 && j >= 0 && j <= Y - 1) {
								if (mapOfGame[i][j] == 0) {
									mapOfShots[i][j] = 5;
									mapOfGame[i][j] = 5;
								}
							}
						}
					}
					ind++;
			
					if (verticalCoordinate + ind < X) {
						check = (mapOfGame[verticalCoordinate + ind][horizontalCoordinate] != 0);
					}
					else
						check = false;
				}
				else {
					check = false;
				}
			}

		}
		mapOfShots[verticalCoordinate][horizontalCoordinate] = 7;
		mapOfGame[verticalCoordinate][horizontalCoordinate] = 7;

		for (int i = verticalCoordinate - 1; i <= verticalCoordinate + 1; i++) {
			for (int j = horizontalCoordinate - 1; j <= horizontalCoordinate + 1; j++) {
				if (i >= 0 && i <= X - 1 && j >= 0 && j <= Y - 1) {
					if (mapOfGame[i][j] != 7) {
						mapOfShots[i][j] = 5;
						mapOfGame[i][j] = 5;
					}
				}
			}
		}
		return;

	}
	int shot(int verticalCoordinate, int horizontalCoordinate, std::vector <std::vector<int>> &mapOfGame, std::vector <std::vector<int>> &mapOfShots, std::vector<int> &leftMyCheck,
			std::vector<int> &leftBotCheck, bool AI) {

		if (mapOfGame[verticalCoordinate][horizontalCoordinate] == 0) {
			mapOfShots[verticalCoordinate][horizontalCoordinate] = 5; //milk
			mapOfGame[verticalCoordinate][horizontalCoordinate] = 5; //milk
			return mapOfShots[verticalCoordinate][horizontalCoordinate];
		}
		if (mapOfGame[verticalCoordinate][horizontalCoordinate] == 1) {
			if (!AI) {
				leftMyCheck[0]--;
			}
			else {
				leftBotCheck[0]--;
			}
			
			mapOfShots[verticalCoordinate][horizontalCoordinate] = 7; //kill
			mapOfGame[verticalCoordinate][horizontalCoordinate] = 7; //kill
			
			for (int i = verticalCoordinate - 1; i <= verticalCoordinate + 1; i++) {
				for (int j = horizontalCoordinate - 1; j <= horizontalCoordinate + 1; j++) {
					if (i >= 0 && i <= X - 1 && j >= 0 && j <= Y - 1) {
						if (i != verticalCoordinate || j != horizontalCoordinate) {
							mapOfShots[i][j] = 5;
							mapOfGame[i][j] = 5;
						}
					}
				}
			}
			return mapOfShots[verticalCoordinate][horizontalCoordinate];
		}
		if (mapOfGame[verticalCoordinate][horizontalCoordinate] == 2 || mapOfGame[verticalCoordinate][horizontalCoordinate] == 3 ||
			mapOfGame[verticalCoordinate][horizontalCoordinate] == 4 ) {
			
			if (seachingAndCheckAllDecks(verticalCoordinate, horizontalCoordinate, mapOfGame, mapOfShots)) {
				if (!AI) {
					leftMyCheck[mapOfGame[verticalCoordinate][horizontalCoordinate] - 1] --;
				}
				else {
					leftBotCheck[mapOfGame[verticalCoordinate][horizontalCoordinate] - 1] --;
				}
				killingShip(verticalCoordinate, horizontalCoordinate, mapOfGame, mapOfShots);				
				return 7;
			}
			else {
				mapOfShots[verticalCoordinate][horizontalCoordinate] = 6;
				mapOfGame[verticalCoordinate][horizontalCoordinate] = 6;
				return 6;
			}			
			
		}
			
	}
	bool checkVicinity(std::vector <std::vector< int >> mapOfGame, int verticalCoordinate, int horizontalCoordinate, int numberOfDecks, char direction, bool AI){
		if (direction == 'R') {
			for (int i = 0; i < numberOfDecks; i++) {
				if (horizontalCoordinate + i < Y) {
					if (!vicinity(verticalCoordinate, horizontalCoordinate + i, mapOfGame, AI))
						return false;
				}
				else {
					if (!AI) {
						std::cout << "--------------------------------------------------\n";
						std::cout << char(179) << "you can not go out of bounds, PLEASE, TRY AGAIN!" << char(179) << std::endl;
						std::cout << "--------------------------------------------------\n\n";
					}
					return false;
				}
			}
		}
		if (direction == 'L') {
			for (int i = 0; i < numberOfDecks; i++) {
				if (horizontalCoordinate - i >= 0) {
					if (!vicinity(verticalCoordinate, horizontalCoordinate - i, mapOfGame, AI))
						return false;
				}
				else {
					if (!AI) {
						std::cout << "--------------------------------------------------\n";
						std::cout << char(179) << "you can not go out of bounds, PLEASE, TRY AGAIN!" << char(179) << std::endl;
						std::cout << "--------------------------------------------------\n\n"; \
					}
					return false;
				}
			}
		}
		if (direction == 'T') {
			for (int i = 0; i < numberOfDecks; i++) {
				if (verticalCoordinate - i >= 0) {
					if (!vicinity(verticalCoordinate - i, horizontalCoordinate, mapOfGame, AI))
						return false;
				}
				else {
					if (!AI) {
						std::cout << "--------------------------------------------------\n";
						std::cout << char(179) << "you can not go out of bounds, PLEASE, TRY AGAIN!" << char(179) << std::endl;
						std::cout << "--------------------------------------------------\n\n"; \
					}
					return false;
				}
			}
		}
		if (direction == 'D') {
			for (int i = 0; i < numberOfDecks; i++) {
				if (verticalCoordinate + i < X) {
					if (!vicinity(verticalCoordinate + i, horizontalCoordinate, mapOfGame, AI))
						return false;
				}
				else {
					if (!AI) {
						std::cout << "--------------------------------------------------\n";
						std::cout << char(179) << "you can not go out of bounds, PLEASE, TRY AGAIN!" << char(179) << std::endl;
						std::cout << "--------------------------------------------------\n\n"; \
					}
						return false;
				}
			}
		}
		return true;
	}
	void setShip(std::vector <std::vector< int >> & mapOfGame, int verticalCoordinate, int horizontalCoordinate, int numberOfDecks, char direction) {
		if (direction == 'R') {
			for (int i = 0; i < numberOfDecks; i++) {
				mapOfGame[verticalCoordinate][horizontalCoordinate + i] = numberOfDecks;
			}
		}
		if (direction == 'L') {
			for (int i = 0; i < numberOfDecks; i++) {
				mapOfGame[verticalCoordinate][horizontalCoordinate - i] = numberOfDecks;
			}
		
		}
		if (direction == 'T') {

			for (int i = 0; i < numberOfDecks; i++) {
				mapOfGame[verticalCoordinate - i][horizontalCoordinate] = numberOfDecks;
			}

		}
		if (direction == 'D') {
			for (int i = 0; i < numberOfDecks; i++) {
				mapOfGame[verticalCoordinate + i][horizontalCoordinate] = numberOfDecks;
			}
		}
	}
	void setOneDeck(std::vector <std::vector< int >> & mapOfGame, bool AI) {
		int numberOfPlacedShips = 0, verticalCoordinate, horizontalCoordinate;
		bool OK = false;
		std::string symbolOfHorizontalCoordinate;
		std::cout << std::endl << std::endl;
		std::map<std::string, int>::iterator it ;

		while (numberOfPlacedShips != 4) {
			while (!OK) {
				if (!AI) {
					std::cout << "Please ENTER COORDINATES for " << numberOfPlacedShips + 1 << " SUNGLE-DECK SHIP by this principle :  [HORIZONTAL COORDINATE <backspace> VERTICAL COORDINATE] :\n";
					std::cout << "[horizontal | vertical] = ";
					std::cin >> symbolOfHorizontalCoordinate;
					std::cin >> verticalCoordinate;
					std::cout << std::endl;
					it = Alphabet.find(symbolOfHorizontalCoordinate);

					if (verticalCoordinate >= 0 && verticalCoordinate < X && it != Alphabet.end()) {
						if (it->second < Y) {
							horizontalCoordinate = it->second;
							//OK = true;
						}
						else { // this else needed because my symbol can Be in Alphabet, but can not be in my game map

							std::cout << "-----------------------------------------------\n";
							std::cout << char(179) << "Unknown coordinates found! PLEASE, TRY AGAIN!" << char(179) << std::endl;
							std::cout << "-----------------------------------------------\n\n";
							continue;
						}
					}
					else {	

						std::cout << "-----------------------------------------------\n";
						std::cout << char(179) << "Unknown coordinates found! PLEASE, TRY AGAIN!" << char(179) << std::endl;
						std::cout << "-----------------------------------------------\n\n";
						continue;
					}
					OK = true;
				}
				else {
					verticalCoordinate = rand() % X;
					horizontalCoordinate = rand() % Y;
					OK = true;
				}
				
				
			}
			if (vicinity(verticalCoordinate, horizontalCoordinate, mapOfGame, AI)) {
				mapOfGame[verticalCoordinate][horizontalCoordinate] = 1;
				if(!AI)
					OutputSetShips(mapOfGame);
				numberOfPlacedShips++;
			}
			OK = false; // initialization for next sircle
		}
	}
	void setTwoDeck(std::vector <std::vector< int >> & mapOfGame, bool AI = false) {
		bool OK = false, movingToRight = rand() % 2;
		char direction;
		std::string symbolOfHorizontalCoordinate;
		char directions[4] = { 'L', 'T', 'R', 'D' };
		int  verticalCoordinate, horizontalCoordinate, numberOfUsedDirections = 0, valueOfDirection = rand() % 4, numberOfPlacedShips = 0;
		std::map<std::string, int>::iterator it;

		while (numberOfPlacedShips != 3) {
			while (!OK) {
				if (!AI) {
					std::cout << "Please ENTER COORDINATES for FIRST DECK OF " << numberOfPlacedShips + 1 << " DESTROYER(TWO-DECK SHIP) by this principle :  [HORIZONTAL COORDINATE <backspace> VERTICAL COORDINATE <backspace> DIRECTION] :\n";
					std::cout << "L - left; R - right; T - top; D - down\n";
					std::cout << "[horizontal | vertical | direction] = ";
					std::cin >> symbolOfHorizontalCoordinate;
					std::cin >> verticalCoordinate;
					std::cin >> direction;
					std::cout << std::endl;

					it = Alphabet.find(symbolOfHorizontalCoordinate);

					if (verticalCoordinate >= 0 && verticalCoordinate < X && it != Alphabet.end() && (direction == 'T' || direction == 'D' || direction == 'R' || direction == 'L')) {
						if (it->second < Y) {
							horizontalCoordinate = it->second;
						}
						else { // this else needed because my symbol can Be in Alphabet, but can not be in my game map
								std::cout << "-----------------------------------------------\n";
								std::cout << char(179) << "Unknown coordinates found! PLEASE, TRY AGAIN!" << char(179) << std::endl;
								std::cout << "-----------------------------------------------\n\n";
							continue;
						}
					}
					else {
							std::cout << "-----------------------------------------------\n";
							std::cout << char(179) << "Unknown coordinates found! PLEASE, TRY AGAIN!" << char(179) << std::endl;
							std::cout << "-----------------------------------------------\n\n";
						continue;
					}

					OK = true;
				}
				else {
					if (numberOfUsedDirections == 0) {
						verticalCoordinate = rand() % X;
						horizontalCoordinate = rand() % Y;
						direction = directions[valueOfDirection];
					}
					else {
						if (numberOfUsedDirections == 4) {
							numberOfUsedDirections = 0;
							OK = false;
							valueOfDirection = rand() % 4;
							movingToRight = rand() % 2;
							continue;
						}
						else {
							if (movingToRight) {
								if (valueOfDirection == 3) {
									valueOfDirection = 0;
									direction = directions[valueOfDirection];
								}
								else
									direction = directions[valueOfDirection++];
							}
							else {
								if (valueOfDirection == 0) {
									valueOfDirection = 3;
									direction = directions[valueOfDirection];
								}
								else
									direction = directions[valueOfDirection--];
							}
						}
					}
				}

				

				if (checkVicinity(mapOfGame, verticalCoordinate, horizontalCoordinate, 2, direction, AI)) {
					setShip(mapOfGame, verticalCoordinate, horizontalCoordinate, 2, direction);
					if(!AI)
						OutputSetShips(mapOfGame);
					numberOfPlacedShips++;
					if (AI) {
						numberOfUsedDirections = 0;
						valueOfDirection = rand() % 4;
					}
					OK = true;
				}
				else {
					if (AI) {
						numberOfUsedDirections++;
					}
				}

			}
			OK = false; // initialization for next sircle

		}
		

	}
	void setThreeDeck(std::vector <std::vector< int >> & mapOfGame, bool AI = false) {
		bool OK = false, movingToRight = rand() % 2;
		char direction;
		std::string symbolOfHorizontalCoordinate;
		char directions[4] = { 'L', 'T', 'R', 'D' };
		int  verticalCoordinate, horizontalCoordinate, numberOfUsedDirections = 0, valueOfDirection = rand() % 4, numberOfPlacedShips = 0;
		std::map<std::string, int>::iterator it;

		while (numberOfPlacedShips != 2) {
			while (!OK) {
				if (!AI) {
					std::cout << "Please ENTER COORDINATES for FIRST DECK OF " << numberOfPlacedShips + 1 << " CRUISER(THREE-DECK SHIP) by this principle :  [HORIZONTAL COORDINATE <backspace> VERTICAL COORDINATE <backspace> DIRECTION] :\n";
					std::cout << "L - left; R - right; T - top; D - down\n";
					std::cout << "[horizontal | vertical | direction] = ";
					std::cin >> symbolOfHorizontalCoordinate;
					std::cin >> verticalCoordinate;
					std::cin >> direction;
					std::cout << std::endl;

					it = Alphabet.find(symbolOfHorizontalCoordinate);

					if (verticalCoordinate >= 0 && verticalCoordinate < X && it != Alphabet.end() && (direction == 'T' || direction == 'D' || direction == 'R' || direction == 'L')) {
						if (it->second < Y) {
							horizontalCoordinate = it->second;
						}
						else { // this else needed because my symbol can Be in Alphabet, but can not be in my game map
								std::cout << "-----------------------------------------------\n";
								std::cout << char(179) << "Unknown coordinates found! PLEASE, TRY AGAIN!" << char(179) << std::endl;
								std::cout << "-----------------------------------------------\n\n";
							continue;
						}
					}
					else {
							std::cout << "-----------------------------------------------\n";
							std::cout << char(179) << "Unknown coordinates found! PLEASE, TRY AGAIN!" << char(179) << std::endl;
							std::cout << "-----------------------------------------------\n\n";
						continue;
					}
					OK = true;
				
				}
				else {
					if (numberOfUsedDirections == 0) {
						verticalCoordinate = rand() % X;
						horizontalCoordinate = rand() % Y;
						direction = directions[valueOfDirection];
					}
					else {
						if (numberOfUsedDirections == 4) {
							numberOfUsedDirections = 0;
							OK = false;
							valueOfDirection = rand() % 4;
							movingToRight = rand() % 2;
							continue;
						}
						else {
							if (movingToRight) {
								if (valueOfDirection == 3) {
									valueOfDirection = 0;
									direction = directions[valueOfDirection];
								}
								else
									direction = directions[valueOfDirection++];
							}
							else {
								if (valueOfDirection == 0) {
									valueOfDirection = 3;
									direction = directions[valueOfDirection];
								}
								else
									direction = directions[valueOfDirection--];
							}
						}
					}
				}

				
				if (checkVicinity(mapOfGame, verticalCoordinate, horizontalCoordinate, 3, direction, AI)) {
					setShip(mapOfGame, verticalCoordinate, horizontalCoordinate, 3, direction);
					if(!AI)
						OutputSetShips(mapOfGame);
					numberOfPlacedShips++;
					if (AI) {
						numberOfUsedDirections = 0;
						valueOfDirection = rand() % 4;
					}
					OK = true;
				}
				else {
					if (AI) {
						numberOfUsedDirections++;
					}
				}
				
			}
			OK = false; // initialization for next sircle

		}

		
	}
	void setFourDeck(std::vector <std::vector< int >> & mapOfGame, bool AI = false) {
		bool OK = false, movingToRight = rand() % 2;
		char direction;
		std::string symbolOfHorizontalCoordinate;
		char directions[4] = { 'L', 'T', 'R', 'D' };
		int  verticalCoordinate, horizontalCoordinate, numberOfUsedDirections = 0, valueOfDirection = rand() % 4, numberOfPlacedShips = 0;
		std::map<std::string, int>::iterator it;

		while (numberOfPlacedShips != 1) {
			while (!OK) {
				if (!AI) {
					std::cout << "Please ENTER COORDINATES for FIRST DECK OF " << numberOfPlacedShips + 1 << " BATTLESHIP(FOUR-DECK SHIP) by this principle :  [HORIZONTAL COORDINATE <backspace> VERTICAL COORDINATE <backspace> DIRECTION] :\n";
					std::cout << "L - left; R - right; T - top; D - down\n";
					std::cout << "[horizontal | vertical | direction] = ";
					std::cin >> symbolOfHorizontalCoordinate;
					std::cin >> verticalCoordinate;
					std::cin >> direction;
					std::cout << std::endl;

					it = Alphabet.find(symbolOfHorizontalCoordinate);

					if (verticalCoordinate >= 0 && verticalCoordinate < X && it != Alphabet.end() && (direction == 'T' || direction == 'D' || direction == 'R' || direction == 'L')) {
						if (it->second < Y) {
							horizontalCoordinate = it->second;
						}
						else { // this else needed because my symbol can Be in Alphabet, but can not be in my game map
								std::cout << "-----------------------------------------------\n";
								std::cout << char(179) << "Unknown coordinates found! PLEASE, TRY AGAIN!" << char(179) << std::endl;
								std::cout << "-----------------------------------------------\n\n";
							continue;
						}
					}
					else {
							std::cout << "-----------------------------------------------\n";
							std::cout << char(179) << "Unknown coordinates found! PLEASE, TRY AGAIN!" << char(179) << std::endl;
							std::cout << "-----------------------------------------------\n\n";
						continue;
					}
					OK = true;				
				}
				else {
					if (numberOfUsedDirections == 0) {
						verticalCoordinate = rand() % X;
						horizontalCoordinate = rand() % Y;
						direction = directions[valueOfDirection];
					}
					else {
						if (numberOfUsedDirections == 0) {
							verticalCoordinate = rand() % X;
							horizontalCoordinate = rand() % Y;
							direction = directions[valueOfDirection];
						}
						else {
							if (numberOfUsedDirections == 4) {
								numberOfUsedDirections = 0;
								OK = false;
								valueOfDirection = rand() % 4;
								movingToRight = rand() % 2;
								continue;
							}
							else {
								if (movingToRight) {
									if (valueOfDirection == 3) {
										valueOfDirection = 0;
										direction = directions[valueOfDirection];
									}
									else
										direction = directions[valueOfDirection++];
								}
								else {
									if (valueOfDirection == 0) {
										valueOfDirection = 3;
										direction = directions[valueOfDirection];
									}
									else
										direction = directions[valueOfDirection--];
								}
							}
						}
					}
				}
				if (checkVicinity(mapOfGame, verticalCoordinate, horizontalCoordinate, 4, direction, AI)) {
					setShip(mapOfGame, verticalCoordinate, horizontalCoordinate, 4, direction);
					if(!AI)
						OutputSetShips(mapOfGame);
					numberOfPlacedShips++;
					if (AI) {
						numberOfUsedDirections = 0;
						valueOfDirection = rand() % 4;
					}
					OK = true;
				}
				else {
					if (AI) {
						numberOfUsedDirections++;
					}
				}
				
			}
			OK = false; // initialization for next sircle

		}
	}
	void setAllShips(bool AI, std::vector <std::vector< int >> &mapOfGame) {
		
		setOneDeck(mapOfGame, AI);
		if(!AI)
			std::cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::\n";
		setTwoDeck(mapOfGame, AI);
		if (!AI)
			std::cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::\n";
		setThreeDeck(mapOfGame, AI);
		if (!AI)
			std::cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::\n";
		setFourDeck(mapOfGame, AI);
		if (!AI)
			std::cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::\n";
	}
	bool fire(std::vector <std::vector<int>> &mapOfGame, std::vector <std::vector<int>> &mapOfShots,
			std::vector<int> &leftMyCheck,	std::vector<int> &leftBotCheck, bool &ifHitShip, std::vector<int> &coordinatesOfLastHit, int &indexV, int &indexH,  std::vector<char> dir, int &numOfDir, bool &toRight,
		bool &shotVertical, bool &firstShot,  bool AI) {
		int verticalCoordinate = -1, horizontalCoordinate = -1;
		char direction;
		bool ifHit = true;
		int res;
		std::string symbolOfHorizontalCoordinate;
		std::map<std::string, int>::iterator it;
		if (!AI) {
			
			std::cout << "														----------------\n";
			std::cout << "														" << char(179) << "!!!YOUR TURN!!" << char(179) << std::endl;
			std::cout << "														----------------\n\n";
		}
		else {	
			system("cls");
			std::cout << "														----------------\n";
			std::cout << "														"<< char(179) << "!!!BOTS TURN!!" << char(179) << std::endl;
			std::cout << "														----------------\n\n";
		}

		while (ifHit) {
			if (!gameOver(leftMyCheck, leftBotCheck)) {
				if (!AI) {

					for (int i = 0; i < 4; i++) {
						std::cout << "														";
						std::cout << i + 1 << "-deck ships left: " << leftMyCheck[i] << std::endl;
					} 

					std::cout << "Choose coordinates of fire: [horizontal <space> vertical]: ";
					std::cin >> symbolOfHorizontalCoordinate;
					std::cin.exceptions(std::istream::failbit | std::istream::badbit);
					try {
						std::cin >> verticalCoordinate;
					}
					catch (std::istream::failure ex) {
						std::cerr << "-----------------------------------------------\n";
						std::cerr << char(179) << "Unknown coordinates found! PLEASE, TRY AGAIN!" << char(179) << std::endl;
						std::cerr << "-----------------------------------------------\n\n";
						std::cin.clear();
						std::cin.ignore();
						continue;
					}
					it = Alphabet.find(symbolOfHorizontalCoordinate);
					if (verticalCoordinate >= 0 && verticalCoordinate < X && it != Alphabet.end()) {
						if (it->second < Y) {
							horizontalCoordinate = it->second;
						}
						else { // this else needed because my symbol can Be in Alphabet, but can not be in my game map

							std::cout << "-----------------------------------------------\n";
							std::cout << char(179) << "Unknown coordinates found! PLEASE, TRY AGAIN!" << char(179) << std::endl;
							std::cout << "-----------------------------------------------\n\n";
							std::cin.clear();
							std::cin.ignore();
							continue;
						}
					}
					else {

						std::cout << "-----------------------------------------------\n";
						std::cout << char(179) << "Unknown coordinates found! PLEASE, TRY AGAIN!" << char(179) << std::endl;
						std::cout << "-----------------------------------------------\n\n";
						std::cin.clear();
						std::cin.ignore();
						continue;
					}
					if (mapOfShots[verticalCoordinate][horizontalCoordinate] == 0) {

						res = shot(verticalCoordinate, horizontalCoordinate, mapOfGame, mapOfShots, leftMyCheck, leftBotCheck, AI);
						if (res == 6 || res == 7) {
							ifHit = true;
							std::cout << "----------------BOT FIELD--------------------          ------------------MY FIELD-------------------\n";
							OutputMaps(mapOfShots, Myfield);

							continue;
						}
						/*if (res == 7) {
							ifHit = true;
							std::cout << "----------------BOT FIELD--------------------          ------------------MY FIELD-------------------\n";
							OutputMaps(mapOfShots, Myfield);

							continue;
						}*/
						if (res == 5) {
							ifHit = false;
							std::cout << "----------------BOT FIELD--------------------          ------------------MY FIELD-------------------\n";
							OutputMaps(mapOfShots, Myfield);

							return false;
						}
					}
					else {
						std::cout << "------------------------------------------------------------------------\n";
						std::cout << char(179) << "YOU CAN'T SHOT COORDINATES, THAT ALREADY WERE SHOTED! PLEASE TRY AGAIN" << char(179) << std::endl;
						std::cout << "------------------------------------------------------------------------\n\n";

						continue;
					}


				}
				else { // AI
					if (!ifHitShip) {
						verticalCoordinate = rand() % X;
						horizontalCoordinate = rand() % Y;
					}
					else {

						if (dir[numOfDir] == 'R') {
							indexH++;
							if (coordinatesOfLastHit[1] + indexH < Y) {
								verticalCoordinate = coordinatesOfLastHit[0];
								horizontalCoordinate = coordinatesOfLastHit[1] + indexH;

							}
							else {
								if (toRight) {
									numOfDir++;
									if (!firstShot) {
										if (!shotVertical) {
											numOfDir++;
										}
									}
								}
								else {
									numOfDir--;
									if (!firstShot) {
										if (!shotVertical) {
											numOfDir--;
										}
									}
								}

								if (numOfDir == 4)
									numOfDir = 0;
								else {
									if (numOfDir == -1)
										numOfDir = 3;
									if (numOfDir == -2)
										numOfDir = 2;
									if (numOfDir == 5)
										numOfDir = 1;
									if (numOfDir == 6)
										numOfDir = 2;
								}
								indexV = 0;
								indexH = 0;
								continue;
							}
						}
						if (dir[numOfDir] == 'L') {
							indexH++;
							if (coordinatesOfLastHit[1] - indexH >= 0) {
								verticalCoordinate = coordinatesOfLastHit[0];
								horizontalCoordinate = coordinatesOfLastHit[1] - indexH;

							}
							else {
								if (toRight) {
									numOfDir++;
									if (!firstShot) {
										if (!shotVertical) {
											numOfDir++;
										}
									}
								}
								else {
									numOfDir--;
									if (!firstShot) {
										if (!shotVertical) {
											numOfDir--;
										}
									}
								}
								if (numOfDir == 4)
									numOfDir = 0;
								else {
									if (numOfDir == -1)
										numOfDir = 3;
									if (numOfDir == -2)
										numOfDir = 2;
									if (numOfDir == 5)
										numOfDir = 1;
									if (numOfDir == 6)
										numOfDir = 2;
								}
								indexV = 0;
								indexH = 0;
								continue;
							}
						}
						if (dir[numOfDir] == 'T') {
							indexV++;
							if (coordinatesOfLastHit[0] - indexV >= 0) {
								verticalCoordinate = coordinatesOfLastHit[0] - indexV;
								horizontalCoordinate = coordinatesOfLastHit[1];

							}
							else {
								if (toRight) {
									numOfDir++;
									if (!firstShot) {
										if (shotVertical) {
											numOfDir++;
										}
									}
								}
								else {
									numOfDir--;
									if (!firstShot) {
										if (shotVertical) {
											numOfDir--;
										}
									}
								}

								if (numOfDir == 4)
									numOfDir = 0;
								else {
									if (numOfDir == -1)
										numOfDir = 3;
									if (numOfDir == -2)
										numOfDir = 2;
									if (numOfDir == 5)
										numOfDir = 1;
									if (numOfDir == 6)
										numOfDir = 2;
								}
								indexV = 0;
								indexH = 0;
								continue;
							}
						}
						if (dir[numOfDir] == 'D') {
							indexV++;
							if (coordinatesOfLastHit[0] + indexV < Y) {
								verticalCoordinate = coordinatesOfLastHit[0] + indexV;
								horizontalCoordinate = coordinatesOfLastHit[1];

							}
							else {
								if (toRight) {
									numOfDir++;
									if (!firstShot) {
										if (shotVertical) {
											numOfDir++;
										}
									}
								}
								else {
									numOfDir--;
									if (!firstShot) {
										if (shotVertical) {
											numOfDir--;
										}
									}
								}

								if (numOfDir == 4)
									numOfDir = 0;
								else {
									if (numOfDir == -1)
										numOfDir = 3;
									if (numOfDir == -2)
										numOfDir = 2;
									if (numOfDir == 5)
										numOfDir = 1;
									if (numOfDir == 6)
										numOfDir = 2;
								}
								indexV = 0;
								indexH = 0;
								continue;
							}
						}


					}
					if (mapOfShots[verticalCoordinate][horizontalCoordinate] == 0) {
						res = shot(verticalCoordinate, horizontalCoordinate, mapOfGame, mapOfShots, leftMyCheck, leftBotCheck, AI);
						if (res == 6) {
							ifHit = true;
							std::cout << "----------------BOT FIELD--------------------          ------------------MY FIELD-------------------\n";
							if (!ifHitShip) {
								coordinatesOfLastHit[0] = verticalCoordinate;
								coordinatesOfLastHit[1] = horizontalCoordinate;
								numOfDir = rand() % 4;
								toRight = rand() % 2;
								indexV = 0;
								indexH = 0;
								ifHitShip = true;
								firstShot = true;
							}
							else {
								firstShot = false;
								if (dir[numOfDir] == 'L' || dir[numOfDir] == 'R') {
									shotVertical = false;
								}
								else {
									shotVertical = true;
								}
							}
							OutputMaps(EnemyMapOfShots, mapOfGame);


							continue;
						}
						if (res == 7) {
							ifHit = true;
							std::cout << "----------------BOT FIELD--------------------          ------------------MY FIELD-------------------\n";;
							OutputMaps(EnemyMapOfShots, mapOfGame);
							firstShot = true;
							ifHitShip = false;
							numOfDir = rand() % 4;
							indexH = 0;
							indexV = 0;
							continue;
						}
						if (res == 5) {
							ifHit = false;
							std::cout << "----------------BOT FIELD--------------------          ------------------MY FIELD-------------------\n";
							if (ifHitShip) {
								if (toRight) {
									numOfDir++;
									if (!firstShot) {
										if (shotVertical) {
											numOfDir++;
										}
									}
								}
								else {
									numOfDir--;
									if (!firstShot) {
										if (shotVertical) {
											numOfDir--;
										}
									}
								}

								if (numOfDir == 4)
									numOfDir = 0;
								else {
									if (numOfDir == -1)
										numOfDir = 3;
									if (numOfDir == -2)
										numOfDir = 2;
									if (numOfDir == 5)
										numOfDir = 1;
									if (numOfDir == 6)
										numOfDir = 2;
								}
							}
							indexH = 0;
							indexV = 0;
							OutputMaps(EnemyMapOfShots, mapOfGame);
							return true;
						}
					}
					else {
#ifdef DEBUG
						std::cout << "------------------------------------------------------------------------\n";
						std::cout << char(179) << "YOU CAN'T SHOT COORDINATES, THAT ALREADY WERE SHOTED! PLEASE TRY AGAIN" << char(179) << std::endl;
						std::cout << "------------------------------------------------------------------------\n\n";
#endif
						if (toRight) {
							numOfDir++;
							if (!firstShot) {
								if (shotVertical) {
									numOfDir++;
								}
							}
						}
						else {
							numOfDir--;
							if (!firstShot) {
								if (shotVertical) {
									numOfDir--;
								}
							}
						}

						if (numOfDir == 4)
							numOfDir = 0;
						else {
							if (numOfDir == -1)
								numOfDir = 3;
							if (numOfDir == -2)
								numOfDir = 2;
							if (numOfDir == 5)
								numOfDir = 1;
							if (numOfDir == 6)
								numOfDir = 2;
						}
						indexV = 0;
						indexH = 0;
						continue;
					}
				}
			}
			else
				return true;;
		}
	}

	bool gameOver(std::vector<int> leftMyShips, std::vector<int> leftEnemyShips) {
		if (!ifGameOver) {
			for (int i = 0; i < 4; i++) {
				if (i == 3) {
					if (leftMyShips[i] == 0) {
						std::cout << "---------------\n";
						std::cout << char(179) << "!!!YOU WIN!!!" << char(179) << std::endl;
						std::cout << "---------------\n\n";
						ifGameOver = true;
						return true;
					}
				}
				if (leftMyShips[i] == 0)
					continue;
				else {
					break;
				}
			}
		}
		if (!ifGameOver) {
			for (int i = 0; i < 4; i++) {
				if (i == 3) {
					if (leftEnemyShips[i] == 0) {
						std::cout << "---------------\n";
						std::cout << char(179) << "!!!BOT WIN!!!" << char(179) << std::endl;
						std::cout << "---------------\n\n";
						ifGameOver = true;
						return true;
					}
				}
				if (leftEnemyShips[i] == 0)
					continue;
				else {
					break;
				}
			}
		}
		return false;
	}
		
	void mainMenu() {
		bool ifHitShip = false, toRight = rand() % 2, shotVertical = rand() % 2, firstShot = true, modeOK = false;
		int me = rand() % 2, mode;
		std::vector< int > leftMyShips = { 4,3,2,1 }, leftEnemyShips = { 4,3,2,1 };
		std::vector <int> coordinatesOfLastHit;
		coordinatesOfLastHit.resize(2);
		int indexV = 0, indexH = 0;
		std::vector<char> dir = {'L','T','R','D'};
		int numOfDir = rand() % 4;
		
		
		initialization();
		firstFilling(Myfield);
		firstFilling(Enemyfield);
		firstFilling(MyMapOfShots);
		firstFilling(EnemyMapOfShots);

		while (!modeOK) {
			std::cout << "If you want to fill the field by yourself, write \'1\', else, write \'0\':";
			std::cin.exceptions(std::istream::failbit | std::istream::badbit);
			try {
				std::cin >> mode;
				if (mode != 1 && mode != 0) {
					throw std::exception("error");
				}
			}
			catch (std::istream::failure ex) {
				std::cerr << "-------------------------------------------\n";
				std::cerr << char(179) << "Unknown command found! PLEASE, TRY AGAIN!" << char(179) << std::endl;
				std::cerr << "-------------------------------------------\n\n";
				std::cin.clear();
				std::cin.ignore();
				continue;
			}
			catch (std::exception exep) {
				std::cout << exep.what();
					std::cerr << "-------------------------------------------\n";
					std::cerr << char(179) << "Unknown command found! PLEASE, TRY AGAIN!" << char(179) << std::endl;
					std::cerr << "-------------------------------------------\n\n";
					continue;
			}
			modeOK = true;
		}
		if (mode == 1) {
			setAllShips(true, Enemyfield);
			OutputSetShips(Myfield);
			setAllShips(false, Myfield);
		}
		else {
			setAllShips(true, Enemyfield);
			setAllShips(true, Myfield);
		}
		std::cout << "----------------BOT FIELD--------------------          ------------------MY FIELD-------------------\n";
		OutputMaps(EnemyMapOfShots,Myfield);
		std::cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::\n";

		while (!gameOver(leftMyShips, leftEnemyShips)) {
			if (me) {
				me = fire(Enemyfield, EnemyMapOfShots, leftMyShips , leftEnemyShips, 
					ifHitShip,coordinatesOfLastHit, indexV, indexH, dir, numOfDir, toRight, shotVertical, firstShot, false);
				system("pause");
			}
			else {
				me = fire(Myfield, MyMapOfShots, leftMyShips, leftEnemyShips, ifHitShip,
					coordinatesOfLastHit, indexV, indexH, dir, numOfDir, toRight , shotVertical, firstShot, true);
				system("pause");

			}

		}

	}
};




void initABCD(game BS) {
	for (int i = 0; i < 26; i++) {
		Alphabet.emplace(BS.ABC[i], i);
	}
}
int main(){

	std::srand(time(NULL));
	SetConsoleCP(437);
	SetConsoleOutputCP(437);
	game BS; // BS = BattleShip
	initABCD(BS);
	BS.mainMenu();
	system("pause");
	return 0;
}
