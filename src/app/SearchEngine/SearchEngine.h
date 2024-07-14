#ifndef PROGRA3_SEARCHENGINE_H
#define PROGRA3_SEARCHENGINE_H
#include <string>
#include <unordered_set>
#include <vector>

class SearchEngine {
public:
    SearchEngine();
    void addDocument(const std::string &doc);
    std::vector<std::string> search(const std::string &query);

private:
    std::vector<std::string> documents;
    std::map<std::string, std::vector<int>> index;
    std::mutex indexMutex; // Mutex to protect the index

    void indexDocument(int docId, const std::string &doc);
    std::vector<int> searchIndex(const std::string &query);
};

#endif //PROGRA3_SEARCHENGINE_H
