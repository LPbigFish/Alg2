#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

class State {
public:
	bool k = false;
	bool v = false;
	bool p = false;
	bool z = false;

	State(bool k, bool v, bool p, bool z) {
		this->k = k;
		this->v = v;
		this->p = p;
		this->z = z;
	}

	bool crossed() const {
		return k && v && p && z;
	}

	bool is_valid() const {
		return !((k == v && p != v) || (z == k && p != k));
	}

	vector<State> get_next_states() {
		vector<State> next_states;

		bool next_pos = !this->p;

		State s_p(k, v, next_pos, z);
		if (s_p.is_valid()) next_states.push_back(s_p);
		if (this->p == this->v) {
			State s_v(k, !v, next_pos, z);
			if (s_v.is_valid()) next_states.push_back(s_v);
		}

		if (this->p == this->k) {
			State s_k(!k, v, next_pos, z);
			if (s_k.is_valid()) next_states.push_back(s_k);
		}
		if (this->p == this->z) {
			State s_z(k, v, next_pos, !z);
			if (s_z.is_valid()) next_states.push_back(s_z);
		}

		return next_states;
	}

	string getMove(const State& to) const {
		if (this->v != to.v) return "Farmer takes Wolf";
		if (this->k != to.k) return "Farmer takes Goat";
		if (this->z != to.z) return "Farmer takes Cabbage";
		return "Farmer crosses alone";
	}
};

int main() {
	State base_state(false, false, false, false);

	queue<vector<State>> q;

	bool visited[2][2][2][2] = { false };
	visited[0][0][0][0] = true;

	q.push({ base_state });

	vector<State> path;
	bool found = false;

	while (!q.empty()) {
		vector<State> current_path = q.front();
		q.pop();

		State current_state = current_path.back();

		if (current_state.crossed()) {
			path = current_path;
			found = true;
			break;
		}

		for (State next_state : current_state.get_next_states()) {
			if (!visited[next_state.k][next_state.v][next_state.p][next_state.z]) {
				visited[next_state.k][next_state.v][next_state.p][next_state.z] = true;
				vector<State> new_path = current_path;
				new_path.push_back(next_state);
				q.push(new_path);
			}
		}
	}

	if (found) {
		for (size_t i = 0; i < path.size() - 1; i++) {
			cout << "Step " << i + 1 << ": " << path[i].getMove(path[i + 1]) << endl;
		}
	}

	return 0;
}