#pragma once

class NamePattern {
public:
    static std::string getPattern() {
        return "^[^0-9]*$"; // regex pattern for anything but numbers.
    };
};