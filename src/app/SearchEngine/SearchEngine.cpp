//
// Created by flauta on 13/07/2024.
//

#include "SearchEngine.h"

SearchEngine::SearchEngine() {}

void SearchEngine::addDocument(const std::string &doc) {
    int docId = documents.size();
    documents.push_back(doc);

    // Parallelize indexing using std::thread
    std::thread indexThread(&SearchEngine::indexDocument, this, docId, doc);
    indexThread.join(); // Ensure indexing is complete before proceeding
}

void SearchEngine::indexDocument(int docId, const std::string &doc) {
    std::istringstream stream(doc);
    std::string word;
    while (stream >> word) {
        std::lock_guard<std::mutex> guard(indexMutex); // Protect access to index
        index[word].push_back(docId);
    }
}

std::vector<std::string> SearchEngine::search(const std::string &query) {
    std::vector<int> results = searchIndex(query);
    std::vector<std::string> foundDocs;
    std::vector<std::thread> threads;
    std::mutex foundDocsMutex;

    // Use threads to parallelize document retrieval
    for (int docId : results) {
        threads.emplace_back([&foundDocs, &foundDocsMutex, this, docId]() {
            std::lock_guard<std::mutex> guard(foundDocsMutex);
            foundDocs.push_back(this->documents[docId]);
        });
    }

    // Join all threads
    for (auto &thread : threads) {
        thread.join();
    }

    return foundDocs;
}

std::vector<int> SearchEngine::searchIndex(const std::string &query) {
    std::lock_guard<std::mutex> guard(indexMutex); // Protect access to index
    if (index.find(query) != index.end()) {
        return index[query];
    }
    return {};
}