// COMSC-210-5068, Lab 19, Yang Liu
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <fstream>
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
        double randomRating = generateRandomRating();
        ReviewNode* newNode = new ReviewNode();
        newNode->rating = randomRating;
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

vector<string> readCommentsFromFile(const string& filename) {
    vector<string> comments;
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Could not open file " << filename << "!" << endl;
        return comments;
    }

    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            comments.push_back(line);
        }
    }
    file.close();
    cout << "Read " << comments.size() << " comments from input.txt." << endl;
    return comments;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    vector<string> allComments = readCommentsFromFile("input.txt");
    if (allComments.empty()) {
        cout << "Error: No comments available!" << endl;
        return 1;
    }

    vector<Movie> movieContainer;
    movieContainer.emplace_back("Test movie 1");
    movieContainer.emplace_back("Test movie 2");
    movieContainer.emplace_back("Test movie 3");
    movieContainer.emplace_back("Test movie 4");

    int commentIndex = 0;
    for (auto& movie : movieContainer) {
        for (int i = 0; i < 3; i++) {
            if (commentIndex >= allComments.size()) commentIndex = 0;
            movie.addReview(allComments[commentIndex].c_str());
            commentIndex++;
        }
    }

    cout << " ----- All Movie Reviews ----- " << endl;
    for (const auto& movie : movieContainer) {
        movie.printReviews();
    }


    return 0;
}