// Khayyam Saleem and Matthew Rota
// CS385 -- WaterJug
// We pledge our honor that we have abided by the Stevens Honor System.
// Please enjoy the advanced af code

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
//    vector<string> directions; ??????? wat is dis

    State(int _a, int _b, int _c) : a(_a), b(_b), c(_c) { };

    // String representation of state in tuple form.
    string to_string() const {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }

    //overloading operators is SO NICE
    int& operator[](char x) { // lets me access member variables like an array, v cool
    	if (x == 'a') return a;
    	if (x == 'b') return b;
    	if (x == 'c') return c;
    	exit(1);
    }

    //u've got a friend in me
    friend bool operator<(const State& s, const State& t) { // required for checking if it exists in the map, huge pain
    	return s.a < t.a
    			|| (s.a == t.a && s.b < t.b)
    			|| (s.a == t.a && s.b == t.b && s.c < t.c);
    }

    //friend lets them not be member methods, bc u can't overload operators when they're member methods
    friend bool operator==(const State& x, const State& y){ // lets me check if two states are equal to one another
    	return (x.a == y.a && x.b == y.b && x.c == y.c);
    }
};

typedef vector<State> Path; //typedef is nice

State pour(char from, char to, State i, State caps){ //pours from one jug to another, returns the result of the pour
	State o = i;

	if (i[from] + i[to] >= caps[to]){
		o[from] -= caps[to] - o[to];
		o[to] = caps[to];
	} else {
		o[to] += i[from];
		o[from] = 0;
	}
	for(char z = 'a'; z <= 'c'; ++z){
		assert(o[z] >= 0); //make sure it's never negative bc that just doesn't make sense
	}
	return o;
}

Path copyAndPour(Path& p, char from, char to, State cap) { //makes a copy of the pour so that we can add a path to the queue
	Path copy(p); // make a copy of the path
	copy.push_back(pour(from, to, p.back(), cap)); // add new state to path
//	cout << "\tPouring -> " << copy << "\n";
	return copy;
}


Path bfs(State i, State f, State c){ //bfs implementation
	map<State, bool> seen;

	queue<Path> sol; //holds potential solution paths
	Path path; // potential solution path
	path.push_back(i); //pushes initial state to path
	sol.push(path); //pushes path containing just initial state to queue
	while(!(sol.empty())){ //while the queue is not empty
		Path cur = sol.front(); // cur = the front of the queue
		sol.pop(); // pop

		if (cur.back() == f) {
			return cur; //if the back of the path vector is equal to the goal state, return that path
		}

		if (seen[cur.back()]) //check if we've seen the state already to cut off any potential loops, skip all pours
			continue;

		seen[cur.back()] = true; //we've seen the state

		//perform all pour combinations, add them to the queue
		sol.push(copyAndPour(cur, 'c', 'a', c));
		sol.push(copyAndPour(cur, 'b', 'a', c));
		sol.push(copyAndPour(cur, 'c', 'b', c));
		sol.push(copyAndPour(cur, 'a', 'b', c));
		sol.push(copyAndPour(cur, 'b', 'c', c));
		sol.push(copyAndPour(cur, 'a', 'c', c));
	}
	return Path(); //return an empty path if no solution was found
}

bool argChecks(int argc, char *argv[]) {
	istringstream iss;
	int m;
	char jugs[3] = {'A', 'B', 'C'}; //jugs

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

void printSol(Path solution){
	if (solution.size() == 0){ //If you received an empty path, then there was no solution
		cout << "No solution." << endl;
	}
	else{
		cout << "Initial state. " << solution[0].to_string() << endl;
		for (unsigned i=1; i < solution.size(); i++){
			int diffa = solution[i-1].a - solution[i].a;
			int diffb = solution[i-1].b - solution[i].b;
			int diffc = solution[i-1].c - solution[i].c;

			cout << "Pour ";
			char from = '?';
			int fromAmount = 0;
			if (diffa > 0) {
				fromAmount = diffa;
				from = 'A';
			} else if (diffb > 0) {
				fromAmount = diffb;
				from = 'B';
			} else if (diffc > 0) {
				fromAmount = diffc;
				from = 'C';
			}

			string gallons = fromAmount == 1 ? "gallon" : "gallons"; //r u kidding me?!?!?!? grammar, dr. b????
			cout << fromAmount << " " << gallons << " from " << from << " to ";

			if (diffa < 0) {
				cout << 'A';
			} else if (diffb < 0) {
				cout << 'B';
			} else if (diffc < 0) {
				cout << 'C';
			}

			cout << ". " << solution[i].to_string() << endl;
		}
	}
}

int main(int argc, char *argv[]) {
	if (argChecks(argc, argv)) {
		return 1;
	}
	State i(0, 0, atoi(argv[3]));
	State caps(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
	State f(atoi(argv[4]), atoi(argv[5]), atoi(argv[6]));

	printSol(bfs(i, f, caps));

//	State s(0, 0, 8);
//	cout << s.to_string() << endl;
//	s.a += 3;
//	s.c -= 3;
//	cout << s.to_string() << endl;
//	State test1 = pour('c', 'a', i, caps);
//	cout << test1.to_string() << endl;
//	cout << (test1 == pour('c', 'a', pour('a', 'c', test1, caps), caps)) << endl;
	return 0;
}
