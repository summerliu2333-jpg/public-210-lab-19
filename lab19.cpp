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

public:
    Movie(string movieTitle) : title(movieTitle), reviewHead(nullptr) {}

    ~Movie() {}

    string getTitle() const {
        return title;
    }
};

int main() {
    return 0;
}