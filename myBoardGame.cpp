/* Programming Methodology course assignment
 * skeleton code specifying function definitions given
 * source code for board game displayed in console, finding combinations to make desired calculation result
 */

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <vector>
#include <algorithm>
using namespace std;
const int TILE_SIZE=16;
const int TILE_BOARD_LENGTH = 4;
const int NUM_CHANCE_TYPE = 2;
const int NUM_CHANCE_1 = 2;
const int NUM_CHANCE_2 = 2;
const int ROUNDS=5;
const char BOARD_FRONT[TILE_BOARD_LENGTH][TILE_BOARD_LENGTH] = { {'A', 'B', 'C', 'D'}, {'E','F', 'G', 'H'}, {'I', 'J', 'K', 'L'}, {'M', 'N', 'O', 'P'} };

const int NUM_POSSIBLE_NUM=12;
const int NUM_POSSIBLE_OP=4;
const string POSSIBLE_NUM[NUM_POSSIBLE_NUM] = { "1", "2","3","4","5","6","7","8","9", "10", "11", "12" };
const string POSSIBLE_OP[NUM_POSSIBLE_OP] = { "+", "-", "x", "/" };


class Simple_Calculator{
    public:
        // Function that converts the operands from string to number 
        //  and handles either input formula of length 3 or 5
        // Implement the length 3/5 formula calculation utilizing the arithmetic_op function
        // @param input[] : (string type) the player's given input
        // @param input_size : (int type) the length of the input
        // @return : The calculation outcome for either input of size 3 or 5.
        float calculate (string input[],int input_size) const;

        // Function that executes the arithmetic operation with the given inputs
        // @param operand : (float type) operand number
        // @param op : (string type) operator (+,-,*,/)
        // @return : The calculation outcome of the "operand1 op operand2 "
        float arithmetic_op (float operand1, float operand2, string op) const; 
        
        // Function that verifies if the input number is integer.
        // @param number : (float type) number to verify if it is integer
        // @return : true if the number is integer, false if it is not.
        bool is_integer (float number) const; 
    };




//Simple_Calculator class:
//member function calculate(string, int) definition
float Simple_Calculator::calculate (string input[],int input_size) const {
        float intermediate_result;
        if (input_size == 3) {
                return arithmetic_op(stof(input[0]), stof(input[2]), input[1]);
        }
        else if (input_size == 5) {
                if ((input[1] == "+" || input[1] == "-") && (input[3] == "x" || input[3] == "/")) {
                        intermediate_result = arithmetic_op(stof(input[2]), stof(input[4]), input[3]);
                        return arithmetic_op(stof(input[0]), intermediate_result, input[1]);
                }
                else {
                        intermediate_result = arithmetic_op(stof(input[0]), stof(input[2]), input[1]);
                        return arithmetic_op(intermediate_result, stof(input[4]), input[3]);
                }
        }
}

//Simple_Calculator class:
//member function arithmetic_op(float, float, string) definition
float Simple_Calculator::arithmetic_op(float operand1, float operand2, string op) const {
        if (op == "+") {
                return operand1 + operand2;
        }
        else if (op == "-") {
                return operand1 - operand2;
        }
        else if (op == "x") {
                return operand1 * operand2;
        }
        else if (op == "/") {
                return operand1 / operand2;
        }
}

//Simple_Calculator class:
//member function is_integer(float) definition
//returns true if number == n...., n.99999999..., n.00000001... (more than 6~7 consecutive 9, 0s)
//      : this condition is enough for evaluating possible cases in Game
bool Simple_Calculator::is_integer(float number) const {
        return ((int)number - number) == 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////


class Board {
public:
        //NOT FROM SKELETON CODE
        //A default constructor
        Board();

        // A Constructor of the Board class.
        // Initialze class with pair<char, string> tiles
        // @param board_front:  The front-side of the board (Use global variable BOARD_FRONT)
        // @param board_back:  The back-side of the board (2D string array, read from Tiles.txt )
	Board(const char board_front[][TILE_BOARD_LENGTH], string board_back[][TILE_BOARD_LENGTH]);
        
        // Fuction for getting number or operation corresponding the input alphabet
        // @param alphabet: Player's input alphabet
        // @return (string type) number or operation corresponding to alphabet
        string get_num_from_back(char alphabet) const;
        
        // Function for printing front-side of the board.
        void print_front() const;
        
        // Function for printing front-side of the board except one tile. 
        // @param alphabet: Player's input alphabet 
        void print_one_flipped(char alphabet) const;
	
        // Function for printing back-side of the board
        void print_back() const;     

        //NOT FROM SKELETON CODE
        // Function for checking if given number can be generated from current board.
        bool can_generate(int target_number) const;
        
        // Function for advanced version, this function changes the board corresponding to input_alphabets array
        // Using POSSIBLE_NUM / POSSIBLE_OP  array, change the board. 
        // @param input_alphabets: (char type) array which saves input alphabets [correct equation]
        // @param arr_size: (int type) size for input_alphabets array
        // Do not fix it
        void change_board(char input_alphabets[], int arr_size) ; 
    
private:
	pair<char, string> tiles[TILE_BOARD_LENGTH][TILE_BOARD_LENGTH]; 
};

//NOT FROM SKELETON CODE
//Board Class:
//Default Constructor definition
//Initialize board front as BOARD_FRONT, back as [+, -, X, /, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
Board::Board() {
        pair <char, string> tile_temp;
        string tile_back_temp;
        for (int i = 0; i < TILE_BOARD_LENGTH; i++) {
                for (int j = 0; j < TILE_BOARD_LENGTH; j++) {
                        if (i==0) {tile_back_temp = POSSIBLE_OP[j];}
                        else {tile_back_temp = POSSIBLE_NUM[4*(i-1)+j];}
                        tile_temp = make_pair(BOARD_FRONT[i][j], tile_back_temp);
                        tiles[i][j] = tile_temp;
                }
        }
}

//Board Class:
//Constructor definition
Board::Board(const char board_front[][TILE_BOARD_LENGTH], string board_back[][TILE_BOARD_LENGTH]) {
        pair <char, string> tile_temp;
        for (int i = 0; i < TILE_BOARD_LENGTH; i++) {
                for (int j = 0; j < TILE_BOARD_LENGTH; j++) {
                        tile_temp = make_pair(board_front[i][j], board_back[i][j]);
                        tiles[i][j] = tile_temp;
                }
        }
}

//Board Class:
//member function get_num_from_back(char) definition
string Board::get_num_from_back(char alphabet) const {
        for (int i = 0; i < TILE_BOARD_LENGTH; i++) {
                for (int j = 0; j < TILE_BOARD_LENGTH; j++) {
                        if (tiles[i][j].first == alphabet) 
                                return tiles[i][j].second;
                }
        }
}

//Board Class:
//member function print_front() definition
void Board::print_front() const {
        cout << "====== BOARD ======" << endl;
        cout << "____________________" << endl;
        for (int i = 0; i < TILE_BOARD_LENGTH ; i++){
                cout << "| ";
                for (int j = 0; j < TILE_BOARD_LENGTH; j++){
                        cout << tiles[i][j].first  << "  | " ;
                }
        cout << endl; 
        }
}

//Board Class:
//member function print_one_flipped() definition
void Board::print_one_flipped(char alphabet) const {
        cout << "====== BOARD: One-flipped ======" << endl;
        cout << "____________________" << endl;
        for (int i = 0; i < TILE_BOARD_LENGTH; i++){
                cout << "| ";
                for (int j = 0; j < TILE_BOARD_LENGTH; j++){
                        if (tiles[i][j].first == alphabet) {
                                if (tiles[i][j].second.size()==1){cout << tiles[i][j].second  << "  | " ;}
                                else{cout << tiles[i][j].second << " | " ;}
                        }
                        else {
                                cout << tiles[i][j].first  << "  | " ;
                        }
                }
        cout << endl; 
        }
}

//Board Class:
//member function print_back() definition
void Board::print_back() const {
        cout << "====== BACK ======" << endl;
        cout << "____________________" << endl;
        for (int i = 0; i < TILE_BOARD_LENGTH; i++){
                cout << "| ";
                for (int j = 0; j < TILE_BOARD_LENGTH; j++){
                        if (tiles[i][j].second.size()==1){cout << tiles[i][j].second  << "  | " ;}
                        else{cout << tiles[i][j].second << " | " ;}
                }
                cout << endl; 
        }
}

//NOT FROM SKELETON CODE
//Board Class:
//member function can_generate() definition
bool Board::can_generate(int target_number) const {
        Simple_Calculator calculator;
        vector<string> board_numbers, board_ops;
        float value_temp;
        for (int i = 0; i < TILE_BOARD_LENGTH; i++) {
                for (int j = 0; j < TILE_BOARD_LENGTH; j++) {
                        if ( (tiles[i][j].second =="+") || (tiles[i][j].second =="-") || (tiles[i][j].second =="x") ||  (tiles[i][j].second =="/") ){
                                board_ops.push_back(tiles[i][j].second);
                        }
                        else {
                                board_numbers.push_back(tiles[i][j].second);
                        }
                }
        }
        
        for (int i = 0; i < board_numbers.size(); i++) {
                for (int j = i + 1; j < board_numbers.size(); j++) {
                        for (int k = 0; k < board_ops.size(); k++) {
                                value_temp = calculator.arithmetic_op(stof(board_numbers[i]), stof(board_numbers[j]), board_ops[k]);
                                if (calculator.is_integer(value_temp) && value_temp == target_number) {
                                        return true;
                                }

                                value_temp = calculator.arithmetic_op(stof(board_numbers[j]), stof(board_numbers[i]), board_ops[k]);
                                if (calculator.is_integer(value_temp) && value_temp == target_number) {
                                        return true;
                                }
                        }
                }
        }
        return false;
}

//SKELETON CODE
void Board::change_board(char input_alphabets[],int input_size) {
    for (int k=0; k<input_size; k++){
        for (int i=0; i<TILE_BOARD_LENGTH ;i++ ){
             for (int j=0; j<TILE_BOARD_LENGTH ;j++ ){
                    if (input_alphabets[k]==tiles[i][j].first){
                        if ( (tiles[i][j].second =="+") || (tiles[i][j].second =="-") || (tiles[i][j].second =="x") ||  (tiles[i][j].second =="/") ){
                                tiles[i][j].second=POSSIBLE_OP[rand()% NUM_POSSIBLE_OP];  
                           }
                        else{
                                tiles[i][j].second=POSSIBLE_NUM[rand()% NUM_POSSIBLE_NUM]; 
                            }
                    }
            }        
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

class Player {
public:
        // A Constructor of the Player class.
        // Initialze chance_count array and score=0.
	Player();

        // Function for adding player's score.
        // @param chance_type: (int type) type of chance (1,2,3).
        void add_score(int chance_type);
	
        // Function for reducing the remaining number of specific chance type.
        // If chance is used, reduce the remaining chance count. 
        // @param chance_type: (int type) type of chance (1,2,3).
        void reduce_chance_count(int chance_type);
        
        // Function for getting score.
        int get_score() const;
        
        // Function for printing remaining chance list.
	void print_remaining_chance_list() const; 

        // Function for checking the specific chance is remained.
        // @param chance_type: (int type) type of chance (1,2,3).
	bool has_remaining_chance(int chance_type) const;

private:
	int chance_count[NUM_CHANCE_TYPE];
        int score;
};

//Player Class:
//Constructor definition
Player::Player() {
        chance_count[0] = NUM_CHANCE_1;
        chance_count[1] = NUM_CHANCE_2;
        score = 0;
}

//Player Class:
//member function add_score(int) definition
void Player::add_score(int chance_type) {
        if (chance_type==3) {
                score += 2;
        }
        else {
                score += 1;
        }
}

//Player Class:
//member function reduce_chance_count(int) definition
void Player::reduce_chance_count(int chance_type) {
        if (chance_type==1 || chance_type==2) {
                chance_count[chance_type-1] -= 1;
        }
}

//Player Class:
//member function get_score() definition
int Player::get_score() const {
        return score;
}

//Player Class:
//member function print_remaining_chance_list() definition
void Player::print_remaining_chance_list() const {
        cout << "Chance 1:" << chance_count[0] << ",  Chance 2:" << chance_count[1] << ",  Chance 3: unlimited" << endl;
}

//Player Class:
//member function has_remaining_chance() definition
bool Player::has_remaining_chance(int chance_type) const {
        if (chance_type == 1) {
                return chance_count[0] > 0;
        }
        else if (chance_type == 2) {
                return chance_count[1] > 0;
        }
        else {
                return true;
        }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

class Game {
public:
        // A Constructor of the Game class.
        // Initialze board class object and current_player_idx=0
        // @param board_front:  The front-side of the board (Use global variable BOARD_FRONT)
        // @param board_back:  The back-side of the board (2D string array, Read from Tiles.txt ) 
        Game(const char board_front[][TILE_BOARD_LENGTH], string board_back[][TILE_BOARD_LENGTH]); 

        // Function for running the game. 
        // 1) Choosing the game type [1,2] 
        // 2) Start round
        //   2-1) Generate target number and verify whether it is valid or not. Only valid target
        //   number can be used in the game.
        //   2-2) Print the back-side of the board for 5 seconds.
        //   2-3) Loop play_turn until round is done. 
        // 3) print final results and game is done.
	void run(); 

        // Function for playing each turn.
        // @return true if round is done. 
        // 1) Chance-selecting step [0: no use chance, 1: skip this turn, 2: show back, 3: Double chance]
        // 2) Tile-selecting step  
        // 3) Result evaluation step
        bool play_turn(); 

        // Function for printing the final results.
        void print_final_result() const;
        
        // Function for generating the target number.
        // Do not fix it
        void generate_target_num();

        // Function that finds all possible natural numbers using numbers and operators in the current board
        // and compares with the target number.
        // @param target_num: (int type) target number generated from generate_target_num()
        // @return true if target number is valid
        bool verify_target_num(int target_num)const;

private:
        int game_type;
	int current_player_idx; 
	Player players[2];
        Board board;
        Simple_Calculator calculator;
        int round;
        int target_num;
        char winning_tiles[5];
        int winning_tiles_count;
};

//Game class:
//Constructor definition
//Initialize board & current_player_idx
Game::Game(const char board_front[][TILE_BOARD_LENGTH], string board_back[][TILE_BOARD_LENGTH]) {
        board = Board(board_front, board_back);
        current_player_idx = 0;
}

//Game class:
//member function run() definition
void Game::run() {
        bool round_done;
        // 1) Choosing the game type [1,2] 
        cout << "Game Start!" << endl;
        cout << "Choose Game Type!" << endl;
        cout << "Press 1 if you want to play a basic game(fixed board)" << endl;
        cout << "Press 2 if you want to play an advanced game(changeable board)" << endl;
        do {
                cout << ">> ";
                cin >> game_type;
                if (game_type != 1 && game_type != 2) {
                        cout << "Invalid game type! Choose among 1 and 2 again" << endl;
                }
        } while (game_type != 1 && game_type != 2);
        
        round = 1;
        while (round <= ROUNDS) {
                // 2) Start round

                //   2-1) Generate target number and verify whether it is valid or not. Only valid target
                //   number can be used in the game.
                do {
                        generate_target_num();
                } while (!verify_target_num(target_num));
                //TARGET NUM VERIFIED

                //   2-2) Print the back-side of the board for 5 seconds.
                if (round == 1) {
                        board.print_back();
                        sleep(5);
                        system("clear");
                }
        
                //   2-3) Loop play_turn until round is done.
                if (round == 1 || round == 3 || round == 5) {
                        current_player_idx = 0;
                }
                else{
                        current_player_idx = 1;
                }
                do {
                        round_done = play_turn();
                        if (!round_done) {
                                current_player_idx = 1 - current_player_idx; // turn over
                        }
                } while (!round_done);  
                
                //   Round done.
                //   round increment, and change board if it is an advanced game
                round++;
                if (game_type == 2) {
                        board.change_board(winning_tiles, winning_tiles_count); // 최종 타일 전달? ex)J, M, G, 3 / A, F, D, E, I, 5
                        board.print_back();
                        sleep(5);
                        system("clear");
                }
        }
        
        // 3) print final results and game is done.
        print_final_result();
}

//Game class:
//member function print_final_result() definition
bool Game::play_turn() {
        // Function for playing each turn.
        // @return true if round is done. 
        int chance_type;
        int to_select = 3;
        int select_count;
        char choice_in;
        string choice_back;
        bool valid_in = false;
        float formula_value;
        vector<char> selected_tiles;
        string selected_tile_backs[5];

        cout << "Player " << (current_player_idx + 1) << "'s turn!" << endl << endl;

        cout << "Round " << round << " / 5" << endl;
        cout << "Current score:  [Player 1: " << players[0].get_score() << " | Player 2: " << players[1].get_score() << " ]" << endl << endl;
        
        cout << "Target Number:  " << target_num << endl << endl;

        cout << "Player " << (current_player_idx + 1) << "'s Remaining Chance List:" << endl;
        players[current_player_idx].print_remaining_chance_list();
        cout << endl;

        // 1) Chance-selecting step [0: no use chance, 1: skip this turn, 2: show back, 3: Double chance]
        cout << "Use Chance?" << endl;
        cout << "Press 0: No chance" << endl;
        cout << "Press 1: Skip this turn!" << endl;
        cout << "Press 2: Show back sides of all alphabet tiles!" << endl;
        cout << "Press 3: Double Chance!" << endl;
        do {
                cout << ">> ";
                cin >> chance_type;
                if (chance_type >= 0 && chance_type <= 3) {
                        if (players[current_player_idx].has_remaining_chance(chance_type)) {
                                valid_in = true;
                        }
                        else {
                                cout << "No remaining chance-" << chance_type << endl;
                        }
                }
                else {
                        cout << "Please enter an appropriate number" << endl;
                }                        
        } while (!valid_in);
        //POST: valid_in == true
        players[current_player_idx].reduce_chance_count(chance_type);

        if (chance_type == 1) {
                system("clear");
                return false;
        }
        else if (chance_type == 2) {
                board.print_back();
                sleep(5);
                system("clear");
        }
        else if (chance_type == 3) {
                to_select = 5;
                system("clear");
        }
        //no chance use
        else {
                system("clear");
        }
        
        // 2) Tile-selecting step
        select_count = 0;
        while (select_count < to_select) {
                //PRE: system cleared
                //display at every selection counts
                cout << "Player " << (current_player_idx + 1) << "'s turn!" << endl << endl;

                cout << "Round " << round << " / 5" << endl;
                cout << "Current score:  [Player 1: " << players[0].get_score() << " | Player 2: " << players[1].get_score() << " ]" << endl << endl;
                
                cout << "Target Number:  " << target_num << endl << endl;

                cout << "Enter alphabet for flipping tile on board" << endl;
                board.print_front();
                valid_in = false;
                do {
                        cout << "Choice-" << select_count + 1 << ": ";
                        cin >> choice_in;
                        for (int i = 0; i < TILE_BOARD_LENGTH; i++) {
                                for (int j = 0; j < TILE_BOARD_LENGTH; j++) {
                                        if (BOARD_FRONT[i][j] == choice_in){
                                                valid_in = true;
                                        }
                                }
                        }
                        if (!valid_in) {
                                cout << "Please check input type" << endl;
                        }
                } while (!valid_in);

                choice_back = board.get_num_from_back(choice_in);

                //SINCE INVALID FORMULA ERROR IS EVALUATED FIRST,
                //AND BOARD BACK IS NOT DISPLAYED AT TILE REUSE ERROR,
                //      WE POSTPONE PRINT_ONE_FLIPPED TO THE POINT WHEN ALL ERRORS ARE EVALUATED

                //error detection: invalid formula
                if (select_count == 0 || select_count == 2 || select_count == 4) {
                        if (choice_back == "+" || choice_back == "-" || choice_back == "x" || choice_back == "/") {
                                cout << "False! Invalid Formula" << endl;
                                sleep(3); // to inform the player
                                system("clear");
                                return false;
                        }
                }
                else {
                        if (choice_back != "+" && choice_back != "-" && choice_back != "x" && choice_back != "/") {
                                cout << "False! Invalid Formula" << endl;
                                sleep(3); // to inform the player
                                system("clear");
                                return false;
                        }
                }

                //error detection: tile reuse
                auto it = find(selected_tiles.begin(), selected_tiles.end(), choice_in);
                if (it != selected_tiles.end()) {
                        cout << "False: You entered an alphabet more than once!" << endl;
                        sleep(3); // to inform the player
                        system("clear");
                        return false;
                }

                //no error detected
                selected_tiles.push_back(choice_in);
                selected_tile_backs[select_count] = choice_back;

                select_count++;
                board.print_one_flipped(choice_in);
                sleep(3);
                system("clear");
        }

        // 3) Result evaluation step
        //PRE: no error so far,
        //      #to_select values are selected
        formula_value = calculator.calculate(selected_tile_backs, to_select);
        cout << "Result: " << formula_value << endl;
        if (!calculator.is_integer(formula_value) || formula_value != target_num) {
                cout << "False!: Incorrect answer :  Change turn" << endl;
                sleep(3); //to inform the player
                system("clear");
                return false;
        }
        else {
                players[current_player_idx].add_score(chance_type);
                for (int i = 0; i < to_select; i++) {
                        winning_tiles[i] = selected_tiles[i];
                }
                winning_tiles_count = to_select;
                cout << "Correct! Round Done" << endl;
                sleep(3); //to inform the player
                system("clear");
                return true;
        }
}

//Game class:
//member function print_final_result() definition
void Game::print_final_result() const {
        cout << "FINAL RESULT" << endl;
        cout << "Score of player 1: " << players[0].get_score() << endl;
        cout << "Score of player 2: " << players[1].get_score() << endl << endl;

        if (players[0].get_score() > players[1].get_score()) {
                cout << "Player 1 win!" << endl;
        }
        else if (players[1].get_score() > players[0].get_score()) {
                cout << "Player 2 win!" << endl;
        }
        else {
                cout << "It's a draw!" << endl;
        }
}

//SKELETON CODE
void Game::generate_target_num() { 
    int min=1; int max=100;
    static const double fraction = 1.0 / (RAND_MAX + 1.0); 
    target_num=min + static_cast<int>((max - min + 1) * (rand() * fraction)) ; 
}

//Game class:
//member function verify_target_num(int) definition
bool Game::verify_target_num(int target_num) const {
        return board.can_generate(target_num);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

int main(void) {  
	ifstream ifs("Tile.txt");
	if (ifs.fail()) {
		cout << "Input tile text not found! Quitting..." << endl;
		exit(1);
	}
//      IMPLEMENT FROM HERE (Read Tile.txt)
//      string TILE_NUMBERS[TILE_BOARD_LENGTH][TILE_BOARD_LENGTH];
        string TILE_NUMBERS[TILE_BOARD_LENGTH][TILE_BOARD_LENGTH];
        system("clear"); 
        char file_in_temp[3];
        for (int i=0; i<16;i++){
              //IMPLEMENT HERE
              ifs >> file_in_temp;
              TILE_NUMBERS[i / 4][i % 4] = string(file_in_temp);
        }   
        ifs.close();            
//      ifs.close();

        Game game=Game(BOARD_FRONT, TILE_NUMBERS);
        game.run();
  	cout << "Thanks for playing the game!" << endl;
//      Game game=Game(BOARD_FRONT,board_back); 
//      game.run();
//	cout << "Thanks for playing the game!" << endl;
	return 0;
}