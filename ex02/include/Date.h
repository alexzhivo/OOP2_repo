#pragma once

#include <iostream>

class Date {
public:
    Date() : m_year(0), m_month(0), m_day(0) {};
    Date(int y) : m_year(y), m_month(0), m_day(0) {};
    Date(int y, int m, int d) : m_year(y), m_month(m), m_day(d) {};

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
    friend Date operator-(const Date& date, int age);
    friend bool operator<=(const Date& leftSide, const Date& rightSide);

private:
    int m_year;
    int m_month;
    int m_day;
};

bool operator<=(const Date& leftSide, const Date& rightSide) {

    if (leftSide.m_year < rightSide.m_year)
        return true;
    if (leftSide.m_year > rightSide.m_year)
        return false;
    if (leftSide.m_month < rightSide.m_month)
        return true;
    if (leftSide.m_month > rightSide.m_month)
        return false;
    return leftSide.m_day <= rightSide.m_day;
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

Date operator-(const Date& date, int age) {
    return Date(date.m_year - age, date.m_month, date.m_day);
};