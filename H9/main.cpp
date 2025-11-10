#include <string>
#include <list>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <iomanip>

constexpr size_t C = 123;

class HashTable {
private:
    // Each slot in the hash table contains a linked list of key-value pairs
    struct HashNode {
        std::string key;
        std::string value;

        HashNode(const std::string& k, const std::string& v)
            : key(k), value(v) {
        }
    };

    std::vector<std::list<HashNode>> table;
    size_t size;
    size_t num_keys;

    size_t hash(const std::string& key) const {
        // Implement a hashing algorithm:
        // h ← 0; for i ← 0 to s − 1 do h ← (h * C + ord(ci)) mod m
        size_t h = 0;
        for (size_t i = 0; i < key.length(); i++) {
			h = (h * C + (size_t)(key[i])) % size;
		}
		return h;
    }

public:
    HashTable(size_t initial_size) : size(initial_size), num_keys(0) {
        table.resize(size);
    }

    void insert(const std::string& key, const std::string& value) {
        // Implement the insertion here
		size_t index = hash(key);
        for (HashNode node : table[index]) {
            if (node.key == key) {
                throw std::runtime_error("Key already exists");
            }
        }
		table[index].push_back(HashNode(key, value));
		num_keys++;
    }

    std::string search(const std::string& key) const {
        // Implement a search here
		size_t index = hash(key);
        for (HashNode node : table[index]) {
            if (node.key == key) {
                return node.value;
            }
		}
        // If key does not exist, throw
        throw std::runtime_error("Key not found");
    }

    void remove(const std::string& key) {
        // Implement remove here
		size_t index = hash(key);
        for (std::list<HashNode>::iterator it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->key == key) {
                table[index].erase(it);
                num_keys--;
                return;
            }
		}

        // If key does not exist, throw
        throw std::runtime_error("Key not found");
    }

    double load_factor() const {
        return static_cast<double>(num_keys) / size;
    }

    // Added method to display the hash table structure
    void display() const {
        std::cout << "\nHash Table Contents:\n";
        std::cout << "Size: " << size << ", Number of keys: " << num_keys << ", Load factor: " << load_factor() << "\n\n";

        for (size_t i = 0; i < size; i++) {
            std::cout << std::setw(2) << i << ": ";
            if (table[i].empty()) {
                std::cout << "[ ]";
            }
            else {
                std::cout << "[ ";
                for (const auto& node : table[i]) {
                    std::cout << node.key << ", ";
                }
                std::cout << "]";
            }
            std::cout << std::endl;
        }
    }
};

static std::vector<std::string> read_words() {
    std::vector<std::string> words;
    std::string word;

    while (std::cin >> word) {
        words.push_back(word);
    }

    return words;
}

int main() {
    HashTable ht(13); // Create hash table with size 13 as in the textbook example

    // Insert the words from the example
    std::vector<std::string> words = read_words();

    std::cout << "Inserting words into hash table...\n";
    for (const auto& word : words) {
        ht.insert(word, word); // Using the word as both key and value for demonstration
        std::cout << "Inserted '" << word << "' into the hash table\n";
    }

    // Display the structure of the hash table
    ht.display();

    // Demonstrate searching
    std::cout << "\nSearching for some keys:\n";
    try {
        std::cout << "Searching for 'FOOL': " << ht.search("FOOL") << std::endl;
        std::cout << "Searching for 'MONEY': " << ht.search("MONEY") << std::endl;
        std::cout << "Searching for 'KID': ";
        std::string value = ht.search("KID");
    }
    catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // Demonstrate deletion
    std::cout << "\nRemoving 'FOOL' from the hash table...\n";
    ht.remove("FOOL");
    ht.display();

    return 0;
}