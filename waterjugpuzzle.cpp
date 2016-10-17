#include <iostream>
#include <sstream>
#include <ostream>
#include <vector>
#include <cstdlib>
#include <cassert>

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

ostream& operator<<(ostream& o, const vector< vector<State> >& out){
	o << "{" << endl;
	for (int i=0; i < out.size(); i++){
		o << "  {";
		for(int j = 0; j < out[i].size(); j++){
			o << out[i][j].to_string() << ", ";
		}
		o << "\b \b" << "\b \b" << "}, " << endl;
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

vector< vector<State> >* bfs(State i, State f, State c){
	vector<State> path, path2;
	vector< vector<State> > *sol = new vector< vector<State> >();
//	path.push_back(i);
//	path.push_back(f);
//	path.push_back(c);
//	path2.push_back(c);
//	path2.push_back(f);
//	path2.push_back(i);
//	sol->push_back(path);
//	sol->push_back(path2);

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
	State test1 = pour('c', 'a', i, caps);
	cout << test1.to_string() << endl;
	cout << (test1 == pour('c', 'a', pour('a', 'c', test1, caps), caps)) << endl;

	vector< vector<State> >* psoln = bfs(i, f, caps);
	vector< vector<State> >& soln = *psoln;
	cout << soln << endl;
	delete psoln;

	return 0;
}
