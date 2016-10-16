#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;
    vector<string> directions;

    State(int _a, int _b, int _c) : a(_a), b(_b), c(_c) { }

    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

int atoi( const char *c ) { //converts chars from argv into ints
    int value = 0; //accumulator
    int sign = 1;
    if( *c == '+' || *c == '-' ) {
       if( *c == '-' ) sign = -1;
       c++;
    }
    while ( isdigit( *c ) ) {
        value *= 10; //adds worth of digit to value
        value += (int) (*c-'0'); // casts digit to int
        c++;
    }
    return value * sign;
}

vector<State> bfs(State state){

}

int argChecks(int argcount, char *args[]){ //argument checking
	// had to use multiple for loops over the same exact parameters bc the way the
	// test cases were set up and it's a HUGE pain and it hurts me to have done so
	// but it WORKS
	if (argcount != 7){ //incorrect number of arguments
		cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
		return 1;
	}
	istringstream iss;
	int m;
	char jugs[3] = {'A', 'B', 'C'};
	for (int i = 1; i < argcount; i++){ // arguments aren't integers
		iss.str(args[i]);
		if(!(iss >> m)){
			if (i <=3){
				cerr << "Error: Invalid capacity '" << args[i] << "' for jug " << jugs[i-1] << "." << endl;
				return 1;
			} else {
				cerr << "Error: Invalid goal '" << args[i] << "' for jug " << jugs[i%4] << "." << endl;
				return 1;
			};
		};
		iss.clear();
	};
	for(int i = 1; i < argcount; i++){ // arguments are integers, but bad user input
		if (atoi(args[i]) < 0){
			if (i <=3){
				cerr << "Error: Invalid capacity '" << args[i] << "' for jug " << jugs[i-1] << "." << endl;
				return 1;
			} else {
				cerr << "Error: Invalid goal '" << args[i] << "' for jug " << jugs[i%4] << "." << endl;
				return 1;
			};
		};
	};
	for(int i=1; i < argcount; i++){ // invalid capacity
		if ((i < 4) && (atoi(args[i+3]) > atoi(args[i]))){
			cerr << "Error: Goal cannot exceed capacity of jug " << jugs[i-1] <<"." << endl;
			return 1;
		};
	};
	if (atoi(args[4]) + atoi(args[5]) + atoi(args[6]) != atoi(args[3])){ // invalid goal state
		cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
		return 1;
	}
	return 0;
}

int main(int argc, char *argv[]) {

	argChecks(argc, argv);

	State s(0, 0, 8);
	cout << s.to_string() << endl;
	s.a += 3;
	s.c -= 3;
	cout << s.to_string() << endl;
	return 0;
}
