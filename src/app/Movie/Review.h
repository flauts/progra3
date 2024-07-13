//
// Created by Badi on 7/13/2024.
//

#ifndef PROGRA3FINALPROJECT_REVIEW_H
#define PROGRA3FINALPROJECT_REVIEW_H

#include <iostream>
#include <vector>

class Review {

private:
    std::string username;
    std::vector<std::string> comment;
    float score;
    int review_id;
public:
    Review() = default;
    Review(std::string, std::vector<std::string>, float);
    void getInfoBlock();
    std::string getUsername() {return username;};
    std::vector<std::string> getComment() {return comment;};
    float getScore() {return score;};
    int getReviewId() {return review_id;};
};


#endif //PROGRA3FINALPROJECT_REVIEW_H
