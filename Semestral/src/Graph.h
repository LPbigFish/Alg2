#pragma once
#include "Node.h"
#include <queue>
#include <set>
#include <vector>

/**
 * @class Graph
 * @brief Tøída reprezentující orientovaný graf závislostí souborù v projektu.
 * 
 * Zdroje:
 * https://en.wikipedia.org/wiki/Topological_sorting
 * ALG 1 - 2024/25 - Závìreèný test
 */
class Graph {
	std::vector<Node*> nodes;

	std::vector<Node*> transposedNodes;
public:
	Graph() = default;
	~Graph();

	/**
 * @brief Pøidá relaci (hranu) mezi dvìma soubory do grafu.
 *
 * Vytváøí dvì hrany:
 * 1. V pùvodním grafu: file -> dep (file závisí na dep)
 * 2. V transponovaném grafu: dep -> file (reverse direction)
 *
 * @param file Soubor, který závisí (zdrojový soubor).
 * @param dep Soubor, na kterém file závisí (cílový soubor).
 */
	void addRelation(int file, int dep);

	/**
 * @brief Provádí BFS na transponovaném grafu.
 *
 * Metoda najde všechny uzly dosažitelné z daného uzlu v transponovaném grafu.
 *
 * Algoritmus:
 * 1. Najde se startovací uzel podle zadaného ID v transponovaném grafu
 * 2. Provede se BFS z tohoto uzlu
 * 3. Vrátí se množina všech dosažených uzlù bez duplicit
 *
 * Èasová složitost: O(V + E), kde V je poèet vrcholù a E je poèet hran.
 * Prostorová složitost: O(V) pro frontu a výstupní množinu.
 *
 * @param node Id uzlu, ze kterého se má zaèít vyhledávání.
 * @return Množina ukazatelù na všechny uzly dosažitelné z poèáteèního uzlu
 *         v transponovaném grafu.
 */
	std::set<Node*> bfs(int node);


	/**
	 * @brief Vyhledá uzel v grafu podle jeho id.
	 *
	 * @param value Id hledaného uzlu.
	 * @return Ukazatel na nalezený uzel, nebo nullptr pokud uzel neexistuje.
	 */
	Node* getNode(int value);

	/**
	 * @brief Vyhledá uzel v transponovaném grafu podle jeho id.
	 *
	 * @param value Id hledaného uzlu.
	 * @return Ukazatel na nalezený uzel, nebo nullptr pokud uzel neexistuje.
	 */
	Node* getTNode(int value);

	/**
	 * @brief Vrátí vektor všech uzlù v grafu.
	 *
	 * @return Vektor ukazatelù na všechny uzly v grafu.
	 */
	std::vector<Node*> getNodes() { return nodes; }
};
