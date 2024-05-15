#pragma once

#include <iostream>

class Date {
public:
    Date() : m_year(0), m_month(0), m_day(0) {}; // Default constructor
    Date(int y, int m, int d) : m_year(y), m_month(m), m_day(d) {}; // Parameterized constructor

    // getters
    int getYear() const { return m_year; };
    int getMonth() const { return m_month; };
    int getDay() const { return m_day; };

    // setters
    void setYear(int y) { m_year = y; };
    void setMonth(int m) { m_month = m; };
    void setDay(int d) { m_day = d; };

    friend std::ostream& operator<<(std::ostream& os, const Date& date);
    friend std::istream& operator>>(std::istream& is, Date& date);

private:
    int m_year;
    int m_month;
    int m_day;
};

std::ostream& operator<<(std::ostream& os, const Date& date) {
    os << date.m_year << "-";
    if (date.m_month < 10) {
        os << "0";
    }
    os << date.m_month << "-";
    if (date.m_day < 10) {
        os << "0";
    }
    os << date.m_day;
    return os;
};

std::istream& operator>>(std::istream& is, Date& date) {
    char separator;
    is >> date.m_year >> separator >> date.m_month >> separator >> date.m_day;
    return is;
};