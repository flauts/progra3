#include <iostream>
#include <fstream>
#include <queue>
#include <string>

// Assuming Movie class is defined elsewhere
class Movie;

struct TrieNode {
    TrieNode* childNode[37];
    bool wordEnd;
    TrieNode* movieNode;

    TrieNode();
    virtual ~TrieNode() = default;

    unordered_set<Movie*> search_movies_by_key(const std::string& key);
    void insert_movies_data(const std::string &key, Movie *mov);

    // Serialization method
    void serialize(std::ofstream& out) const {
        // Write wordEnd
        out.write(reinterpret_cast<const char*>(&wordEnd), sizeof(bool));

        // Write if movieNode exists
        bool hasMovieNode = (movieNode != nullptr);
        out.write(reinterpret_cast<const char*>(&hasMovieNode), sizeof(bool));

        // If movieNode exists, serialize TrieNodeVector
        if (hasMovieNode) {
            TrieNodeVector* movieNodeVector = dynamic_cast<TrieNodeVector*>(movieNode);
            if (movieNodeVector) {
                size_t movieCount = movieNodeVector->vectorPelis.size();
                out.write(reinterpret_cast<const char*>(&movieCount), sizeof(size_t));

                // Here you would serialize each Movie* in vectorPelis
                // For this example, we'll just write the pointer addresses
                for (const Movie* movie : movieNodeVector->vectorPelis) {
                    out.write(reinterpret_cast<const char*>(&movie), sizeof(Movie*));
                }
            }
        }

        // Write child nodes
        for (int i = 0; i < 37; ++i) {
            bool hasChild = (childNode[i] != nullptr);
            out.write(reinterpret_cast<const char*>(&hasChild), sizeof(bool));
            if (hasChild) {
                childNode[i]->serialize(out);
            }
        }
    }

    // Deserialization method
    static TrieNode* deserialize(std::ifstream& in) {
        TrieNode* node = new TrieNode();

        // Read wordEnd
        in.read(reinterpret_cast<char*>(&node->wordEnd), sizeof(bool));

        // Read if movieNode exists
        bool hasMovieNode;
        in.read(reinterpret_cast<char*>(&hasMovieNode), sizeof(bool));

        // If movieNode exists, deserialize TrieNodeVector
        if (hasMovieNode) {
            TrieNodeVector* movieNodeVector = new TrieNodeVector();
            size_t movieCount;
            in.read(reinterpret_cast<char*>(&movieCount), sizeof(size_t));

            // Here you would deserialize each Movie* in vectorPelis
            // For this example, we're just reading the pointer addresses
            for (size_t i = 0; i < movieCount; ++i) {
                Movie* movie;
                in.read(reinterpret_cast<char*>(&movie), sizeof(Movie*));
                movieNodeVector->vectorPelis.insert(movie);
            }

            node->movieNode = movieNodeVector;
        }

        // Read child nodes
        for (int i = 0; i < 37; ++i) {
            bool hasChild;
            in.read(reinterpret_cast<char*>(&hasChild), sizeof(bool));
            if (hasChild) {
                node->childNode[i] = deserialize(in);
            } else {
                node->childNode[i] = nullptr;
            }
        }

        return node;
    }
};

struct TrieNodeVector : public TrieNode {
    unordered_set<Movie*> vectorPelis = unordered_set<Movie*>();
    TrieNodeVector() = default;
};

// Function to serialize the entire Trie
void serializeTrie(const TrieNode* root, const std::string& filename) {
    std::ofstream out(filename, std::ios::binary);
    if (out.is_open()) {
        root->serialize(out);
        out.close();
    } else {
        std::cerr << "Unable to open file for writing: " << filename << std::endl;
    }
}

// Function to deserialize the entire Trie
TrieNode* deserializeTrie(const std::string& filename) {
    std::ifstream in(filename, std::ios::binary);
    if (in.is_open()) {
        TrieNode* root = TrieNode::deserialize(in);
        in.close();
        return root;
    } else {
        std::cerr << "Unable to open file for reading: " << filename << std::endl;
        return nullptr;
    }
}