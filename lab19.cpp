// COMSC-210-5068, Lab 19, Yang Liu
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
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

    double generateRandomRating() {
        int randomInt = 10 + (rand() % 41);
        return static_cast<double>(randomInt) / 10.0;
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

    void printReviews() const {
        cout << " --- Movie: " << title << " ---" << endl;
        if (reviewHead == nullptr) {
            cout << "  No reviews available." << endl;
            return;
        }

        ReviewNode* current = reviewHead;
        int count = 0;
        double total = 0.0;

        cout << "  Reviews:" << endl;
        while (current != nullptr) {
            count++;
            total += current->rating;
            cout << "    > Review #" << count << ": " << fixed << setprecision(1) 
                 << current->rating << ": " << current->comment << endl;
            current = current->next;
        }

        double average = total / count;
        cout << "  Average Rating: " << fixed << setprecision(1) << average << endl;
    }

    string getTitle() const {
        return title;
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0)));

    Movie testMovie("Test movie 1");
    testMovie.addReview("Test comment 1");
    testMovie.printReviews();

    return 0;
}