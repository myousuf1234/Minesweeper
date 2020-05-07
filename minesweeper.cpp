//this program was made by Mohammed Yousuf. It simulates the famous game minesweeper using a class and structs. 

#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Tile{ //holds properties of each tile
    bool explosive = false; 
	bool showing = false;
    int counter = 0;
};
struct Tilerows{ //generates tiles
    vector<Tile> a_row;
    void createtiles(){
        for (int i = 0; i < 10; i++){
            Tile tile;
            a_row.push_back(tile);
        }
    }
};
class Minesweeper {
	public:
	    Minesweeper() {createboard(holder);} //the constructor
	    void display(bool answer){ //answer is a bool statement
	        if (answer){  //this function displays the board
	            for (int i = 1; i < 9; i++){
	                for (int j = 1; j < 9; j++){
	                    if (holder[i].a_row[j].explosive == false){
	                        cout << holder[i].a_row[j].counter << ' ';
	                    }
	                    else{
	                        cout<< "B ";  //B for bomb
	                    }
	                }
	                cout << endl;
	            }
	        }
	    }
	    bool done(){
	        if (invisible == bombno){
	            gamenotover = true;  //is the game over or not?
	        }
	        return gamenotover;
	    }
	    bool validRow(int therow){ //select a row
	        if (therow >= 1 and therow <= 8){
	            return true;
	        }
	        else{
	            return false;
	        }
	    }
	    bool validCol(int thecol){  //select a column
	        if (thecol >= 1 and thecol <= 8){
	            return true;
	        }
	        else{
	            return false;
	        }
	    }
	    bool isVisible(int arow, int acol){ //does the selected cell exist
	        return holder[arow].a_row[acol].showing;
	    }
	    bool play(int arow, int acol){  
	        if (holder[arow].a_row[acol].explosive == true){ //if theres an explosive visible, the games over
	            gamenotover = true;
	            return false;
	        }
	        else{
	            holder[arow].a_row[acol].showing = true;
	            invisible -= 1;
	            if (holder[arow].a_row[acol].counter == 0){ 
	                for (int i = -1; i < 2; i++){ 
	                    for (int j = -1; j < 2; j++){
	                        if (i != 0 or j != 0){
	                            holder[arow + i].a_row[acol + j].showing = true; //shows the given cell(s)
	                            invisible -= 1; //one less hidden cell
	                        }
	                    }
	                }
	            }
	            for (int i = 1; i < 9; i++){
	                for (int j = 1; j < 9; j++){
	                    if (holder[i].a_row[j].showing == true){
	                        cout << holder[i].a_row[j].counter << ' ';
	                    }
	                    else{
	                        cout<< "X "; //I chose X to represent unveiled squares
	                    }
	                }
	                cout << endl;
	            }
	            return true;
	        }
	    }
	private:
	    vector<Tilerows> holder; //vector for the board
	    bool gamenotover = false;
	    int invisible = 64;
	    int bombno = 10;
	    
	    void setbombs(vector<Tilerows>& rows){ //sets up bombs, randomly distributes them
	        for (int i = 0; i < bombno; i++){
	            int random = rand() % 64;
	            div_t result = div(random, 8); //div_t is needed instead of int to use div, quot, rem, etc. 
	            int arow = result.quot + 1; 
	            int acolumn = result.rem + 1; 
	            rows[arow].a_row[acolumn].explosive = true;
	        }
	    }
	    void setnum(vector<Tilerows>& rows){ //sets up numbers giving directions to bombs
	        for (int arow = 1; arow <= 8; arow++){
	            for (int acol = 1; acol <= 8; acol++){
	                if (rows[arow].a_row[acol].explosive == false){
	                    for (int i = -1; i < 2; i++){
	                        for (int j = -1; j < 2; j++){
	                            if (i != 0 or j != 0){
	                                if (rows[arow + i].a_row[acol + j].explosive == true){
	                                    rows[arow].a_row[acol].counter++;
	                                }
	                            }
	                        }
	                    }
	                }
	            }
	        }
	    }
	    void createboard(vector<Tilerows>& rows){ //a helper function with creating the board
	        for (int i = 0; i < 10; i++){
	            Tilerows arow;
	            arow.createtiles();
	            rows.push_back(arow);
	        }
	        setbombs(rows);
	        setnum(rows);
	    }
};
int main() {
    Minesweeper sweeper;
    // Continue until the only invisible cells are bombs
    while (!sweeper.done()) {
        sweeper.display(false); // display board without bombs
        int row_sel = -1, col_sel = -1;
        while (row_sel == -1) {
            // Get a valid move
            int r, c;
            cout << "row? ";
            cin >> r;
            if (!sweeper.validRow(r)) {
                cout << "Row out of bounds\n";
                continue;
            }
            cout << "col? ";
            cin >> c;
            if (!sweeper.validCol(c)) {
                cout << "Column out of bounds\n";
                continue;
            }
            if (sweeper.isVisible(r,c)) {
                cout << "Square already visible\n";
                continue;
            }
            row_sel = r;
            col_sel = c;
        }
        // Set selected square to be visible. May effect other cells.
        if (!sweeper.play(row_sel,col_sel)) {
            cout << "Sorry, you died..\n";
            sweeper.display(true); //Final board with bombs shown
            exit(0);
        }
    }
    // Ah! All invisible cells are bombs, so you won!
    cout << "You won!!!!\n";
    sweeper.display(true); // Final board with bombs shown

	}
