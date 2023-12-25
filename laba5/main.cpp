#include <iostream>
#include <string>
#include <cctype>

using namespace std;

class StringProcessor {
public:
    friend ostream& operator<<(ostream& os, const StringProcessor& sp);
};

ostream& operator<<(ostream& os, const StringProcessor& sp) {
    string input;
    cout << "Enter a string: ";
    getline(cin, input);

    for (char ch : input) {
        if (!isupper(ch) && !isdigit(ch)) {
            os << ch;
        }
    }

    return os;
}

int main() {
    StringProcessor sp;
    cout << sp << endl;

    return 0;
}
