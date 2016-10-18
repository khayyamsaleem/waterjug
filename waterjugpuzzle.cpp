#include <iostream>
#include <sstream>
#include <ostream>
#include <vector>
#include <cstdlib>
#include <cassert>
#include <queue>
#include <map>

using namespace std;

// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;
    vector<string> directions;

    State(int _a, int _b, int _c) : a(_a), b(_b), c(_c) { };

    // String representation of state in tuple form.
    string to_string() const {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }


    int& operator[](char x) { // lets me access member vars like an array, v cool
    	if (x == 'a') return a;
    	if (x == 'b') return b;
    	if (x == 'c') return c;
    	exit(1);
    }

    bool operator==(const State& x){ // lets me check if two states are equal to one another
    	return (this->a == x.a && this->b == x.b && this->c == x.c);
    }
};

typedef vector<State> Path;

ostream& operator<<(ostream& o, const vector< vector<State> >& out){
	if (out.size() == 0){
		o << "{ { } }";
		return o;
	}
	o << "{" << "\n";
	for (int i=0; i < out.size(); i++){
		o << "  {";
		for(int j = 0; j < out[i].size(); j++){
			o << out[i][j].to_string() << ", ";
		}
		o << "\b \b" << "\b \b" << "}, ";
	}
	o << "\b \b" << "\b \b" << endl << "}";
	return o;
}

ostream& operator<<(ostream& o, const queue<State>& out){
	if (out.size() == 0){
		o << "{ { } }";
		return o;
	}
	o << "{ ";
	for (int i=0; i < out.size(); i++){
		o << out.front().to_string() << "->";
	}
	o << "\b \b" << "\b \b" << "}";
	return o;
}

State pour(char from, char to, State i, State caps){
	State o = i;

	if (i[from] + i[to] >= caps[to]){
		o[from] -= caps[to] - o[to];
		o[to] = caps[to];
	} else {
		o[to] += i[from];
		o[from] = 0;
	}
	for(char z = 'a'; z <= 'c'; ++z){
		assert(o[z] >= 0);
	}
	return o;
}

queue< Path >* bfs(State i, State f, State c){
	queue< Path > *sol = new queue< State >();
	Path path;
	path.push_back(i);
	sol->push(path);
	while(!(sol->empty())){

	}
	return sol;

}

bool argChecks(int argc, char *argv[]) {
	istringstream iss;
	int m;
	char jugs[3] = {'A', 'B', 'C'};

	if (argc != 7) {
		cerr << "Usage: " << argv[0] << " <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
		return true;
	}

	for (int i = 1; i < argc; i++) {
		iss.clear();
		iss.str(argv[i]);
		if (!(iss >> m)) {
			if (i <= 3) {
				cerr << "Error: Invalid capacity '" << argv[i] << "' for jug " << jugs[i-1] << "." << endl;
				return true;
			}
			else {
				cerr << "Error: Invalid goal '" << argv[i] << "' for jug " << jugs[i%4] << "." << endl;
				return true;
			}
		}
		else if (m < 1) {
			if (i <= 3) {
				cerr << "Error: Invalid capacity '" << argv[i] << "' for jug " << jugs[i-1] << "." << endl;
				return true;
			}
			else {
				if (m != 0) {
					cerr << "Error: Invalid goal '" << argv[i] << "' for jug " << jugs[i%4] << "." << endl;
					return true;
				}
			}
		}

	}
	for (int i = 1; i < argc; i++) {
		if ((i < 4) && (atoi(argv[i+3]) > atoi(argv[i]))) {
			cerr << "Error: Goal cannot exceed capacity of jug " << jugs[i-1] << "." << endl;
			return true;
		}
	}
	if (atoi(argv[4]) + atoi(argv[5]) + atoi(argv[6]) != atoi(argv[3])) {
		cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
		return true;
	}
	return false;
}

int main(int argc, char *argv[]) {
	if (argChecks(argc, argv)) {
		return 1;
	}
	State i(0, 0, atoi(argv[3]));
	State caps(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
	State f(atoi(argv[4]), atoi(argv[5]), atoi(argv[6]));

//	State s(0, 0, 8);
//	cout << s.to_string() << endl;
//	s.a += 3;
//	s.c -= 3;
//	cout << s.to_string() << endl;
//	State test1 = pour('c', 'a', i, caps);
//	cout << test1.to_string() << endl;
//	cout << (test1 == pour('c', 'a', pour('a', 'c', test1, caps), caps)) << endl;

	cout << bfs(i, f, caps) << endl;

	return 0;
}
