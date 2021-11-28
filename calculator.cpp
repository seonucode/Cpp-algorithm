/* Programming methodology course assignment
 * Given expression skeleton separated by spaces & available numbers of each operator as input,
 * Prints out the expression which makes the largest result
 * ex) input 2.3 ((-3) 1) 4 (-2) 1 1 / 3 3 2 1 1
 *      output 2.3*((-3)-1)^4-(-2)+1+1, 592.8
 */

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

double CalculateExpression(const char s[], int& idx, int level = 1);
double EvaluateTerm(const char s[], int& idx);
double StringToNumber(const char s[], int& idx);
int OperatorPriority(char op);
double CalculateOperator(double left, double right, char op);
void Solve(char s[], int idx, int add, int sub, int mul, int div, int pow, bool seq_pow);
int FindSpace(const char s[], int idx);

const int MAX_EXPR_LENGTH = 100;		// Maximum number of the characters in a single expression
const int MAX_OPERATOR_LEVEL = 3;		// Maximum level of the priority of operators
double max_val = -INFINITY;				// Maximum value of mathematical expressions
char max_s[MAX_EXPR_LENGTH + 1] = "";	// Expression which returns the maximum value

int main() {
	char s[MAX_EXPR_LENGTH + 1] = "";
	int idx;

	idx = 0;
	cout << ">>";
	cin.getline(s, MAX_EXPR_LENGTH + 1);  // getline member function
	cout << s << endl;
	if (strcmp(s, "exit") == 0) {  // strcmp function
		cout << "Exiting.." << endl;
		exit(1);
	}

	int add, sub, mul, div, pow, enter;
	cout << "Number of add sub mul div pow\n>>";
	cin >> add >> sub >> mul >> div >> pow;

	Solve(s, idx, add, sub, mul, div, pow, false);

	if (isnan(max_val) || isinf(max_val)) { // isnan, isinf function, end of c-string = 0
		cout << "Error while evaluating!" << endl;
	}
	else {
		cout << "Maximum Value: " << max_val << endl;
		cout << "Expression: " << max_s << endl;
	}
	
	return 0;
}

void Solve(char s[], int idx, int add, int sub, int mul, int div, int pow, bool seq_pow){
	/*
	It fills in the blanks in the given expression and finds the maximum value and the expression corresponding to that value
	add, sub, mul, div, pow represents the remaining number of each operator
	seq_pow represents whether previous operator was pow or not
	*/

	int new_idx = FindSpace(s,idx);
	// cout << "new_idx check: " << new_idx << endl;
	if (s[new_idx] == '\0'){
		/* 
		Base Case
		- Calculate the completed formula 
		- Compare the calculated value with the (current) maximum value
		*/
		/*
		TEST purpose
		*/
		cout << s << endl;
		/*
		To-do
		*/
		return;
	}
	
	/* 
	Recursive Step
	- Recognize empty space(‘ ’) and fill in the space with the given operator to create a complete expression
	*/
	{
		if (add > 0) {
			s[new_idx] = '+';
			Solve(s, new_idx, add - 1, sub, mul, div, pow, false);
		}
	}
	{
		if (sub > 0) {
			s[new_idx] = '-';
			Solve(s, new_idx, add, sub - 1, mul, div, pow, false);
		}
	}
	{
		if (mul > 0) {
			s[new_idx] = '*';
			Solve(s, new_idx, add, sub, mul - 1, div, pow, false);
		}
	}
	{
		if (div > 0 && s[new_idx + 1] != 0) {
			s[new_idx] = '/';
			Solve(s, new_idx, add, sub, mul, div - 1, pow, false);
		}
	}
	{
		if (pow > 0 && !seq_pow) {
			s[new_idx] = '^';
			Solve(s, new_idx, add, sub, mul, div, pow - 1, true);
		}
	}
}

int FindSpace(const char s[], int idx){
	// It finds the next index of the blank ‘ ’ in string s
	while (s[idx] != ' ') {
		if (s[idx] == '\0') break;
		idx++;
	}
	return idx;
}

double StringToNumber(const char s[], int& idx) {
	//It converts the string to float number. Update the idx value to next unread index.
	// PRECONDITION: s[idx] is not an operator or parenthesis.

	// 1. Is our number negative? 	(keep in mind, that a negative number ends with ')'.)
	bool is_negative = s[idx] == '-';
	if (is_negative) idx++;

	char s_number[MAX_EXPR_LENGTH + 1] = "";
	char s_fraction[MAX_EXPR_LENGTH] = "";

	int i = 0;
	// 2. Iterate through s, while s[idx] is a digit
	while (isdigit(s[idx])) {
		s_number[i] = s[idx];
		idx++;
		i++;
	}
	// - Stopped at s[idx]...
	// 	1) If the number has fractional parts
	if (s[idx] == '.') {
		idx++;
		i = 0;
		while (isdigit(s[idx])) {
			s_fraction[i] = s[idx];
			idx++;
			i++;
		}
		if (is_negative) {
			idx++;	// additional increment to pass through final ')'
			return -1 * (atof(s_number) + atof(s_fraction) / pow(10, i));
		}
		else return atof(s_number) + atof(s_fraction) / pow(10, i);
	}
	//	2) Else: the number is a natural number. (Evaluating the last term of the expression also falls to here)
	else {
		if (is_negative) {
			idx++;	// additional increment to pass through final ')'.
			return -1 *atoi(s_number);
		}
		else return atoi(s_number);
	}
}

double EvaluateTerm(const char s[], int& idx) {
	// It calculates the expression in parenthesis or converts the string to float number. idx value is updated to the next unread index.
	// POSTCONDITION: s[idx] after return is an operator

	// 1. If s[idx] is '(', first check if the string is a negative number, or an expression in parentheses.
	if (s[idx] == '(') {
		idx++;
		// 1) If string is a negative number, call STN() at current idx.
		if (s[idx] == '-') {
			return StringToNumber(s, idx);	// idx is increased in STN().
		}
		// 2) If string is an expression in parentheses,
		// 	Put the inner expression into a new array, and pass it to CE().
		// 	Handle nested parentheses; append terms until the outermost right parenthesis is found
		else {
			char s_parenthesis[MAX_EXPR_LENGTH + 1] = "";	// new array to hold inner expression
			int i = 0;										// indexing variable used in filling s_parenthesis
			int need_match = 1;								// counts 'parenthesis match' needed, to figure out if outermost parenthesis is found 
			
			while (need_match > 0) {
				if (s[idx] == '(') need_match++;
				else if (s[idx] == ')') need_match--;

				if (need_match > 0) {						// first '(' and last ')' isn't passed into new array
					s_parenthesis[i] = s[idx];
					i++;
				}

				idx++;
			}
			// after filling s_parenthesis, current idx points right next to the last ')'
			//	 this meets POSTCONDITION of ET()
			// pass obtained array to CE()
			int start = 0;
			int& idx_start = start;
			return CalculateExpression(s_parenthesis, idx_start);
		}
	}
	// 2. If s[idx] is not '(', we call STN() right away. (STN() can evaluate negative numbers)
	// 	
	else return StringToNumber(s, idx);
}

int OperatorPriority(char op) {
	// It returns the priority of given operator ‘op’
	switch (op) {
		case '+':
		case '-': return 1;
		case '*':
		case '/': return 2;
		case '^': return 3;
		default : return 0;
	}
}

double CalculateOperator(double left, double right, char op) {
	// It returns the result calculated by left and right using the given operator ‘op’
	switch (op) {
		case '+': return left + right;
		case '-': return left - right;
		case '*': return left * right;
		case '/': return left / right;
		case '^': return pow(left, right);
	}
}


double CalculateExpression(const char s[], int& idx, int level) {
	double left, right;
	char op;

	if (level > MAX_OPERATOR_LEVEL) {
		return EvaluateTerm(s, idx);
	}
	else {
		left = CalculateExpression(s, idx, level + 1);
	}
	
	while (OperatorPriority(s[idx]) == level) {
		
		if (OperatorPriority(op) == MAX_OPERATOR_LEVEL) {
			left = CalculateOperator(left, CalculateExpression(s, ++idx, level), op);
		}

		else {
			right = CalculateExpression(s, ++idx, level + 1);

			// checking division by zero error ("/0" is excluded in Solve(), but cases like "/(2-2)" has to be checked here)
			if (op == '/' && right == 0) return -INFINITY;

			left = CalculateOperator(left, right, op);
		}
	}
	
}
