#include "Graph.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const string DELIM = "->";

/**
 * @brief Zobrazí výsledky analýzy závislostí pro všechny soubory.
 *
 * Pro každý soubor v grafu vypíše seznam všech souborù, které musí být
 * znovu zkompilovány pøi zmìnì daného souboru. Výstup je ve formátu:
 * "file_id -> soubor1, soubor2, ..."
 * 
 * Soubory se vypisují v sestupném poøadí podle jejich identifikátorù.
 *
 * Algoritmus:
 * 1. Pro každý soubor se zavolá BFS na transponovaném grafu
 * 2. Výsledky se seøadí v sestupném poøadí pomocí qsort
 * 3. Výsledky se vypíšou v požadovaném formátu
 *
 * @param graph Referenèní graf závislostí souborù v projektu.
 * @param values Množina ID souborù, které byly naèteny ze vstupního souboru.
 */
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

/**
 * @brief Hlavní program pro analýzu závislostí zdrojových kódù projektu.
 *
 * Program ète ze textového souboru graf závislostí souborù v projektì.
 * Každý øádek vstupu obsahuje jednu hranu grafu ve tvaru "u -> v",
 * kde soubor u závisí na souboru v (obsahuje #include souboru v).
 * 
 * Pøíklad vstupu:
 * \code
 * 0 -> 1
 * 0 -> 2
 * 1 -> 3
 * \endcode
 *
 * Program:
 * 1. Ète graf ze souboru uvedeného v argumentu pøíkazové øádky
 * 2. Vytváøí interní reprezentaci orientovaného grafu
 * 3. Pro každý soubor urèí všechny soubory, které jsou jím ovlivnìny
 *    (tj. které na nìm závisí pøímì nebo nepøímo)
 * 4. Vypíše výsledky ve formátu: "soubor -> závislý1, závislý2, ..."
 *
 * Výstup:
 * Podle poznámky 10 v zadání je každý soubor zahrnut i sám v sobì (samozávislost).
 * Soubory se vypisují v sestupném poøadí podle jejich identifikátorù.
 *
 * @param argc Poèet argumentù pøíkazové øádky.
 * @param argv Pole argumentù pøíkazové øádky. argv[1] musí obsahovat 
 *             cestu ke vstupnímu souboru s grafem závislostí.
 * 
 * @return EXIT_SUCCESS (0) pøi úspìšném provedení, EXIT_FAILURE (1) pøi chybì
 *         (špatný poèet argumentù nebo nemohu otevøít soubor).
 * 
 * @example
 * \code
 * program.exe input.txt
 * \endcode
 */
int main(int argc, char* argv[]) {
	// Kontrola poètu argumentù
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " <input_file>" << endl;
		return 1;
	}

	// Otevøení vstupního souboru
	std::ifstream file_input(argv[1]);
	if (!file_input.is_open()) {
		cerr << "Error opening file: " << argv[1] << endl;
		return 1;
	}
	string line;

	Graph graph;
	set<int> values;

	// Ètení grafu ze souboru a vytvoøení interní reprezentace
	while (std::getline(file_input, line)) {
		// Parsování øádku: "u -> v"
		int id = stoi(line.substr(0, line.find(DELIM)));
		int id2 = stoi(line.substr(line.find(DELIM) + DELIM.length()));

		values.insert(id);
		values.insert(id2);

		// Pøidání hrany do grafu
		graph.addRelation(id, id2);
	}

	file_input.close();

	// Výstup výsledkù analýzy
	showOff(graph, values);

	return 0;
}
