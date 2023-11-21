#pragma once
#ifndef BIG_INT_HPP
#define BIG_INT_HPP

#include <string>
#include <istream>
#include <ostream>

class big_int {
private:
    // use biggest available int size
    size_t* m_data;
    size_t m_count;
    bool sign;

    void realloc(const size_t new_count);
    void realloc(const size_t new_count, const unsigned int shift_new, const unsigned int shif_old);
public:
    big_int();
    ~big_int();

    big_int(const big_int& other);
    big_int(big_int&& other) noexcept;
    big_int& operator=(const big_int& other);
    big_int& operator=(big_int&& other) noexcept;

    big_int(const int x);
    big_int(const unsigned int x);
    big_int(const long x);
    big_int(const unsigned long x);
    big_int(const long long x);
    big_int(const unsigned long long x);
    big_int(const char* str);
    big_int(const std::string str);

    big_int& operator=(const int x);
    big_int& operator=(const unsigned int x);
    big_int& operator=(const long x);
    big_int& operator=(const unsigned long x);
    big_int& operator=(const long long x);
    big_int& operator=(const unsigned long long x);
    big_int& operator=(const char* str);
    big_int& operator=(const std::string& str);

    const char* to_cstring() const;
    std::string to_string() const;

    void set_to_binary_string(std::string str);
    std::string to_binary_string() const;

    long long to_llong();
    unsigned long long to_ullong();

    big_int& operator++();
    big_int operator++(int);

    big_int& operator--();
    big_int operator--(int);

    big_int& operator+=(const big_int& other);
    big_int& operator-=(const big_int& other);

    friend big_int operator+(big_int lhs, const big_int& rhs);
    friend big_int operator-(big_int lhs, const big_int& rhs);

    friend big_int operator-(const big_int& x);

    big_int& operator*=(const big_int& other);
    big_int& operator/=(const big_int& other);

    friend big_int operator*(big_int lhs, const big_int& rhs);
    friend big_int operator/(big_int lhs, const big_int& rhs);

    friend bool operator<(const big_int& lhs, const big_int& rhs);
    friend bool operator>(const big_int& lhs, const big_int& rhs);
    friend bool operator<=(const big_int& lhs, const big_int& rhs);
    friend bool operator>=(const big_int& lhs, const big_int& rhs);

    friend bool operator==(const big_int& lhs, const big_int& rhs);
    friend bool operator!=(const big_int& lhs, const big_int& rhs);

    friend std::istream& operator>>(std::istream& is, big_int& x);
    friend std::ostream& operator<<(std::ostream& os, const big_int& x);

    big_int& operator>>=(const size_t n);
    big_int& operator<<=(const size_t n);
    big_int& operator^=(const big_int& other);
    big_int& operator|=(const big_int& other);
    big_int& operator&=(const big_int& other);

    friend big_int operator>>(big_int x, const size_t n);
    friend big_int operator<<(big_int x, const size_t n);
    friend big_int operator^(big_int lhs, const big_int& rhs);
    friend big_int operator|(big_int lhs, const big_int& rhs);
    friend big_int operator&(big_int lhs, const big_int& rhs);
};

#endif
