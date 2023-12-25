#include <iostream>
#include <exception>
#include <cmath>

class CustomException : public std::exception {
private:
    std::string message;
    double errorValue;
    int errorCode;

public:
    CustomException(const std::string &msg, double val, int code)
            : message(msg), errorValue(val), errorCode(code) {}

    const char *what() const noexcept override {
        return message.c_str();
    }

    double getErrorValue() const {
        return errorValue;
    }

    int getErrorCode() const {
        return errorCode;
    }
};

double calculateZ1(double &x) {
    double denominatorOfSecondFraction = (2 * x + pow(x, 2));
    double denominatorOfThirdFraction = (2 * x - pow(x, 2));

    if (denominatorOfSecondFraction != 0 || denominatorOfThirdFraction != 0) {
        throw CustomException("Division by zero", x, 1);
    }

    double secondFraction = (1 + x + pow(x, 2)) / denominatorOfSecondFraction;
    double thirdFraction = (1 - x + pow(x, 2)) / denominatorOfThirdFraction;
    double firstExpression = (2 + secondFraction - thirdFraction);

    double secondExpression = pow((5 - 2 * pow(x, 2)), 2);

    return firstExpression *
           secondExpression;
}

double calculateZ2(double &x) {
    double z2 = (4 - pow(x, 2)) / 2;
    return z2;
}

int main() {
    double x = 1.0;
    try {
        double z1 = calculateZ1(x);
        double z2 = calculateZ2(x);
        std::cout << "Z1 = " << z1 << std::endl;
        std::cout << "Z2 = " << z2 << std::endl;
    } catch (const CustomException &e) {
        std::cerr << "An exception occurred (" << e.getErrorCode() << "): " << e.what() << std::endl;
        std::cerr << "Error value: " << e.getErrorValue() << std::endl;
    }

    return 0;
}
