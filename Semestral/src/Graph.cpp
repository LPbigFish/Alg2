#include "Graph.h"
#include <iostream>


void Graph::addRelation(int file, int dep)
{
	Node* first_node = this->getNode(file);
	Node* first_t_node = this->getTNode(file);
	if (first_node == nullptr) {
		first_node = new Node(file);
		this->nodes.push_back(first_node);
		first_t_node = new Node(file);
		this->transposedNodes.push_back(first_t_node);
	}

	Node* second_node = this->getNode(dep);
	Node* second_t_node = this->getTNode(dep);
	if (second_node == nullptr) {
		second_node = new Node(dep);
		this->nodes.push_back(second_node);
		second_t_node = new Node(dep);
		this->transposedNodes.push_back(second_t_node);
	}
	first_node->getNeighbors().push_back(second_node);
	second_t_node->getNeighbors().push_back(first_t_node);
}

Node* Graph::getTNode(int value) {
	for (Node* node : transposedNodes) {
		if (node->getValue() == value) {
			return node;
		}
	}
	return nullptr;
}

Node* Graph::getNode(int value)
{
	for (Node* node : nodes) {
		if (node->getValue() == value) {
			return node;
		}
	}
	return nullptr;
}


std::set<Node*> Graph::bfs(int node)
{
	std::set<Node*> sorted;
	std::queue<Node*> toVisit;

	Node* startNode = this->getTNode(node);

	if (startNode == nullptr) {
		return sorted;
	}

	toVisit.push(startNode);

	while (!toVisit.empty()) {
		Node* current = toVisit.front();
		toVisit.pop();
		sorted.insert(current);
		for (Node* n : current->getNeighbors()) {
				toVisit.push(n);
			}
		}

	return sorted;
}

Graph::~Graph()
{
	for (Node* node : nodes) {
		delete node;
	}
	for (Node* node : transposedNodes) {
		delete node;
	}
}
