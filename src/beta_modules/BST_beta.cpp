//
// Created by Badi on 7/13/2024.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

// Define a structure for the BST node
struct BSTNode {
    std::string key; // Change this to the appropriate data type for your key
    std::vector<std::string> data; // Store the rest of the CSV data in a vector
    BSTNode* left;
    BSTNode* right;

    BSTNode(std::string  k, const std::vector<std::string>& d) : key(std::move(k)), data(d), left(nullptr), right(nullptr) {}
};

// Function to insert a new node into the BST
BSTNode* insert(BSTNode* root, const std::string& key, const std::vector<std::string>& data) {
    if (root == nullptr) {
        return new BSTNode(key, data);
    }
    if (key < root->key) {
        root->left = insert(root->left, key, data);
    } else {
        root->right = insert(root->right, key, data);
    }
    return root;
}

// Function to search for a key in the BST
BSTNode* search(BSTNode* root, const std::string& key) {
    if (root == nullptr || root->key == key) {
        return root;
    }
    if (key < root->key) {
        return search(root->left, key);
    }
    return search(root->right, key);
}

// Function to read the CSV file and populate the BST
BSTNode* readCSVAndPopulateBST(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    BSTNode* root = nullptr;

    if (file.is_open()) {
        // Read the header line
        std::getline(file, line);

        // Read the rest of the lines
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string item;
            std::vector<std::string> data;

            while (std::getline(ss, item, ',')) {
                data.push_back(item);
            }

            // Assuming the key is the first column in the CSV
            std::string key = data[0];
            root = insert(root, key, data);
        }
        file.close();
    } else {
        std::cerr << "Unable to open file";
    }

    return root;
}

int main() {
    // Path to the CSV file
    std::string filename = "mpst_full_data.csv";

    // Populate the BST
    BSTNode* root = readCSVAndPopulateBST(filename);

    // Search for a specific key (example)
    std::string searchKey = "example_key"; // Replace with an actual key from your CSV
    BSTNode* result = search(root, searchKey);

    if (result != nullptr) {
        std::cout << "Found key: " << result->key << std::endl;
        // Print the associated data
        for (const auto& item : result->data) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Key not found" << std::endl;
    }

    return 0;
}

