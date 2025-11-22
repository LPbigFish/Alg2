#pragma once
#include <vector>

/**
 * @class Node
 * @brief Tøída reprezentující vrchol (soubor) v grafu závislostí.
 *
 * Tøída Node reprezentuje jeden soubor v projektu. Pole neighbors obsahuje seznam souborù,
 * na kterých daný soubor závisí.
 */
class Node {
	int value;
	std::vector<Node*> neighbors;
public:
	Node(int id) : value(id) {}
	
	int getValue() const { return value; }

	std::vector<Node*>& getNeighbors() { return neighbors; }
};
