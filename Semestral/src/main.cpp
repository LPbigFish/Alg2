#include "Graph.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const string DELIM = "->";

static void showOff(Graph& graph, set<int>& values) {
	for (int file_id : values) {
		set<Node*> result = graph.bfs(file_id);

		vector<Node*> result_nodes(result.begin(), result.end());
		qsort(&result_nodes[0], result_nodes.size(), sizeof(Node*),
			[](const void* a, const void* b) {
				Node* nodeA = *(Node**)a;
				Node* nodeB = *(Node**)b;
				return nodeB->getValue() - nodeA->getValue();
			});

		cout << file_id << " -> ";
		while (!result_nodes.empty()) {
			Node* node = result_nodes.back();
			result_nodes.pop_back();
			cout << node->getValue() << (!result_nodes.empty() ? ", " : "" );
		}
		
		cout << endl;
	}
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " <input_file>" << endl;
		return 1;
	}


	std::ifstream file_input(argv[1]);
	if (!file_input.is_open()) {
		cerr << "Error opening file: " << argv[1] << endl;
		return 1;
	}
	string line;

	Graph graph;
	set<int> values;

	int prev_id = -1;
	bool second_part = false;

	while (std::getline(file_input, line)) {
		int id = stoi(line.substr(0, line.find(DELIM)));
		int id2 = stoi(line.substr(line.find(DELIM) + DELIM.length()));

		values.insert(id);
		values.insert(id2);

		graph.addRelation(id, id2);
	}

	file_input.close();

	showOff(graph, values);

	return 0;
}
