#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>

using namespace std;

// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;
    vector<string> directions;

    State(int _a, int _b, int _c) : a(_a), b(_b), c(_c) { };

    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    };
};


State pour(char x, char y, State i, State caps){
	State o = i;
	if (x == 'c' && y == 'a'){
		if (i.c + i.a >= caps.a){
			o.a = caps.a;
			o.c -= caps.a;
		} else {
			o.a += i.c;
			o.c = 0;
		}
	}
	return o;
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
		if (atoi(args[i]) < 1){
			if (i <=3){
				cerr << "Error: Invalid capacity '" << args[i] << "' for jug " << jugs[i-1] << "." << endl;
				return 1;
			} else if (i > 3 && (atoi(args[i]) != 0)){
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
	State i(0, 0, atoi(argv[3]));
	State caps(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
	State f(atoi(argv[4]), atoi(argv[5]), atoi(argv[6]));

//	cout << pour('c', 'a', State(0, 0, 2), caps).to_string() << endl;
//	State s(0, 0, 8);
//	cout << s.to_string() << endl;
//	s.a += 3;
//	s.c -= 3;
//	cout << s.to_string() << endl;
//	return 0;
}
