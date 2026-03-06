// COMSC-210-5068, Lab 19, Yang Liu
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

struct ReviewNode {
    double rating;
    char comment[300];
    ReviewNode* next;
};

class Movie {
private:
    string title;
    ReviewNode* reviewHead;

    void freeReviewList(ReviewNode*& head) {
        ReviewNode* current = head;
        while (current != nullptr) {
            ReviewNode* temp = current;
            current = current->next;
            delete temp;
        }
        head = nullptr;
    }

public:
    Movie(string movieTitle) : title(movieTitle), reviewHead(nullptr) {}

    ~Movie() {
        freeReviewList(reviewHead);
    }

    void addReview(const char* comment) {
        double tempRating = 3.0;
        ReviewNode* newNode = new ReviewNode();
        newNode->rating = tempRating;
        strcpy(newNode->comment, comment);
        newNode->next = reviewHead;
        reviewHead = newNode;
    }

    string getTitle() const {
        return title;
    }
};

int main() {
    Movie testMovie("Test movie 1");
    testMovie.addReview("Test comment 1");
    cout << "Added review to: " << testMovie.getTitle() << endl;
    
    return 0;
}