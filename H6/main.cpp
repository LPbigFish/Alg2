#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class State {
public:
	bool k = true;
	bool v = true;
	bool p = true;
	bool z = true;

	vector<State*> next_states;

	State(bool k, bool v, bool p, bool z) {
		this->k = k;
		this->v = v;
		this->p = p;
		this->z = z;
	}

	State(bool k, bool v, bool p, bool z, State* next_k, State* next_v, State* next_p, State* next_z) {
		this->k = k;
		this->v = v;
		this->p = p;
		this->z = z;
	}

	bool crossed() const {
		return !(k || v || p || z);
	}

	bool is_wrong() const {
		return (k && v && !p && z) ||
				(!k && !v && p && !z) ||
				(k && v && !p && !z) ||
				(!k && !v && p && z) ||
				(k && !v && z && !p) ||
				(!k && v && !z && p);
	}

	void build() {
		vector<State*> visited;
		queue<State*> queue;

		queue.push(this);
		while (!queue.empty()) {
			State* current = queue.front();
			queue.pop();
			if (current->crossed()) {
				continue;
			}
			visited.push_back(current);
			vector<State*> children;
			
			if (current->k && current->p) {
			}
		}
	}
};

int main() {	
	State* base_state = new State(true, true, true, true);
	base_state->build();



	return 0;
}