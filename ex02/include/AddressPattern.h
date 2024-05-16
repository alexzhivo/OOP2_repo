#pragma once

class AddressPattern {
public:
    static std::string getPattern() {
        return "^[a-zA-Z]+-[0-9]+-[a-zA-Z]+$"; // regex pattern for address
    };
};