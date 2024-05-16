#pragma once

class MailPattern {
public:
    static std::string getPattern() {
        return "^[a-zA-Z0-9_.-]+@[a-zA-Z0-9_.-]+.[a-zA-Z]{2,}$"; // regex pattern for mail
    };
};