#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>

// Vectors which house the "rings" (ints)
std::vector<int> towerA;
std::vector<int> towerB;
std::vector<int> towerC;

// Pointers to the vectors
std::vector<int>* Aptr {&towerA};
std::vector<int>* Bptr {&towerB};
std::vector<int>* Cptr {&towerC};

std::map<std::vector<int>*, std::string> map {
	{Aptr, "Tower A"},
	{Bptr, "Tower B"},
	{Cptr, "Tower C"}
};

int get_input(){
	std::cout << "Enter number of discs to solve for : ";
	int n;
	std::cin >> n;
	std::cout << "\n\n";
	return n;
}

// Draws tower segment if there is no disc to be drawn
void draw_empty(int disc_cnt){
	std::cout << std::setw(disc_cnt) << "" << "|" 
	<< std::setw(disc_cnt) << "" << " ";
}
// Draws a single tower
void draw_tower(std::vector<int>* tower, int disc_cnt, size_t i){
	if(tower->size() < i){
		draw_empty(disc_cnt);
	} else {
		std::cout << 
		std::setw(disc_cnt - tower->at(i-1)) << "" <<
		std::setfill('|') << std::setw(tower->at(i-1)) << "" <<
		tower->at(i-1) <<
		std::setw(tower->at(i-1)) << "" << std::setfill(' ') <<
		std::setw(disc_cnt - tower->at(i-1)) << "" << " ";
	}
}
// Draws all three towers
void draw(int disc_cnt){
	for(size_t i = disc_cnt+2; i > 0; i--){
		draw_tower(Aptr, disc_cnt, i);
		draw_tower(Bptr, disc_cnt, i);
		draw_tower(Cptr, disc_cnt, i);
		std::cout << "\n";
	}
	std::cout << "\n\n";
}

// Actual TOH recursive algorithm.
void toh(int n, std::vector<int>* A, std::vector<int>* B, std::vector<int>* C, int disc_cnt){
	static int cnt {1};
	if(n > 0){
		toh(n-1, A, C, B, disc_cnt);
		
		C->push_back(A->back());
		A->pop_back();
		
		std::cout << 
		"Move " << cnt << ": " <<
		"Disc " << n << 
		" from " << map.find(A)->second << 
		" to " << map.find(C)->second << ".\n"; 

		draw(disc_cnt);
		cnt++;

		toh(n-1, B, A, C, disc_cnt);
	}
}

int main(){
	
	system("clear");

	int disc_cnt {get_input()};

	// initialize tower
	for(int i = disc_cnt; i > 0; i--){
		Aptr->push_back(i);
	}
	std::cout << "Initial state: " << "\n";
	draw(disc_cnt);

	toh(disc_cnt, Aptr, Bptr, Cptr, disc_cnt);

	return 0;
}