#include "big_int.hpp"

#include <limits.h>
#include <string.h>

void big_int::realloc(size_t new_count) {
    m_count = new_count;
    size_t* tmp = new size_t[m_count]();
    memcpy(tmp, m_data, m_count * sizeof(size_t));
    delete[] m_data;
    m_data = tmp;
}

big_int::big_int() {
    m_data = new size_t[2]();
    m_count = 2;
    sign = 0;
}

big_int::~big_int() {
    delete[] m_data;
    m_count = 0;
    sign = 0;
}

big_int::big_int(const big_int& other) {
    m_data = new size_t[other.m_count];
    m_count = other.m_count;
    memcpy(m_data, other.m_data, m_count * sizeof(size_t));
    sign = 0;
}

big_int::big_int(big_int&& other) noexcept {
    m_data = other.m_data;
    other.m_data = nullptr;
    m_count = other.m_count;
    other.m_count = 0;
    sign = 0;
}

big_int& big_int::operator=(const big_int& other) {
    if (this == &other) {
        return *this;
    }

    if (m_count != other.m_count) {
        m_count = other.m_count;
        delete[] m_data;
        m_data = new size_t[other.m_count];
    }
    memcpy(m_data, other.m_data, m_count * sizeof(size_t));
    sign = other.sign;

    return *this;
}

big_int& big_int::operator=(big_int&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    m_data = other.m_data;
    other.m_data = nullptr;
    m_count = other.m_count;
    other.m_count = 0;
    sign = other.sign;

    return *this;
}

big_int::big_int(const int x) {
    m_data = new size_t[2]();
    m_count = 2;

    sign = (x < 0);

    int abs_x = abs(x);
    memcpy(m_data, &abs_x, sizeof(int));
}

big_int::big_int(const unsigned int x) {
    m_data = new size_t[2]();
    m_count = 2;

    sign = 0;

    memcpy(m_data, &x, sizeof(unsigned int));
}

big_int::big_int(const long x) {
    m_data = new size_t[2]();
    m_count = 2;

    sign = (x < 0);

    long abs_x = abs(x);
    memcpy(m_data, &abs_x, sizeof(long));
}

big_int::big_int(const unsigned long x) {
    m_data = new size_t[2]();
    m_count = 2;

    sign = 0;

    memcpy(m_data, &x, sizeof(unsigned long));
}

big_int::big_int(const long long x) {
    m_data = new size_t[2]();
    m_count = 2;

    sign = (x < 0);

    long long abs_x = abs(x);
    memcpy(m_data, &abs_x, sizeof(long long));
}

big_int::big_int(const unsigned long long x) {
    m_data = new size_t[2]();
    m_count = 2;

    sign = 0;

    memcpy(m_data, &x, sizeof(unsigned long long));
}

big_int& big_int::operator=(const int x) {
    delete[] m_data;
    m_data = new size_t[2]();
    m_count = 2;

    sign = (x < 0);

    int abs_x = abs(x);
    memcpy(m_data, &abs_x, sizeof(int));

    return *this;
}

big_int& big_int::operator=(const unsigned int x) {
    delete[] m_data;
    m_data = new size_t[2]();
    m_count = 2;

    sign = 0;

    memcpy(m_data, &x, sizeof(unsigned int));

    return *this;
}

big_int& big_int::operator=(const long x) {
    delete[] m_data;
    m_data = new size_t[2]();
    m_count = 2;

    sign = (x < 0);

    long abs_x = abs(x);
    memcpy(m_data, &abs_x, sizeof(long));

    return *this;
}

big_int& big_int::operator=(const unsigned long x) {
    delete[] m_data;
    m_data = new size_t[2]();
    m_count = 2;

    sign = 0;

    memcpy(m_data, &x, sizeof(unsigned long));

    return *this;
}

big_int& big_int::operator=(const long long x) {
    delete[] m_data;
    m_data = new size_t[2]();
    m_count = 2;

    sign = (x < 0);

    long long abs_x = abs(x);
    memcpy(m_data, &abs_x, sizeof(long long));

    return *this;
}

big_int& big_int::operator=(const unsigned long long x) {
    delete[] m_data;
    m_data = new size_t[2]();
    m_count = 2;

    sign = 0;

    memcpy(m_data, &x, sizeof(unsigned long long));

    return *this;
}

void big_int::set_to_binary_string(std::string str) {
    if (str.front() == '-') {
        sign = 1;
        str = str.substr(1);
    } else sign = 0;

    if (str.size() % 64 != 0) return;

    m_count = str.size() / 64;
    m_data = new size_t[m_count]();

    size_t i = 0;
    while (i < str.size()) {
        m_data[m_count - 1 - i / 64] |= size_t(str[i] - '0') << size_t(63 - i % 64);
        ++i;
    }
}

std::string big_int::to_binary_string() {
    std::string str = (sign ? "-" : "");
    for (size_t i = m_count; i >= 1; --i) {
        for (size_t j = 64; j >= 1; --j) {
            str += char(bool(m_data[i - 1] & (1ULL << (j - 1ULL)))) + '0';
        }
        str += " ";
    }
    return str;
}

long long big_int::to_llong() {
    return (sign ? -1 : 1) * m_data[0];
}

unsigned long long big_int::to_ullong() {
    return m_data[0];
}

big_int& big_int::operator++() {
    *this += 1;
    return *this;
}

big_int big_int::operator++(int) {
    big_int old = *this;
    operator++();
    return old;
}

big_int& big_int::operator--() {
    *this -= 1;
    return *this;
}

big_int big_int::operator--(int) {
    big_int old = *this;
    operator--();
    return old;
}

// make sure dst[count] is valid or else the program will segfault
static void add_to(size_t* dst, const size_t* src, size_t count) {
    size_t carry = 0;
    for (size_t i = 0; i < count; ++i) {
        size_t tmp = src[i] + carry;
        dst[i] += tmp;
        carry = (tmp < carry) + (dst[i] < tmp);
    }
    if (carry) dst[count] += carry;
}

// dst needs to be larger than src
static void subtract_from(size_t* dst, const size_t* src, size_t count) {
    size_t borrow = 0;
    for (size_t i = 0; i < count; ++i) {
        size_t tmp = src[i] + borrow;
        borrow = (tmp < borrow) + (dst[i] < tmp);
        dst[i] -= tmp;
    }
}

// x < y
static bool compare(const size_t* x, const size_t* y, const size_t count_x, const size_t count_y) {
    if (count_x == count_y) {
        // check from most significant byte to the least significant
        for (size_t i = count_x - 1; i >= 0; --i) {
            if (x[i] == y[i]) continue;
            return x[i] < y[i];
        }
    }
    return count_x < count_y;
}

big_int& big_int::operator+=(const big_int& other) {
    if (sign == 0 && other.sign == 1) {
        // x + -y = x - y
        if (compare(m_data, other.m_data, m_count, other.m_count)) {
            // x - y = -(-x + y) = -(y - x)
            big_int tmp(std::move(*this));
            *this = other;
            subtract_from(m_data, tmp.m_data, m_count);
            sign = 1;

            return *this;
        }

        subtract_from(m_data, other.m_data, m_count);

        return *this;
    } else if (sign == 1 && other.sign == 0) {
        // -x + y = -(x - y)
        if (compare(m_data, other.m_data, m_count, other.m_count)) {
            // -x - -y = -(x - y) = -(-(y - x)) = y - x
            big_int tmp(std::move(*this));
            *this = other;
            subtract_from(m_data, tmp.m_data, m_count);
            sign = 0;
            return *this;
        }

        subtract_from(m_data, other.m_data, m_count);

        return *this;
    }

    if (m_count <= other.m_count) {
        // alloc +1 in case of overflow
        realloc(other.m_count + 1);
    }

    add_to(m_data, other.m_data, m_count);

    return *this;
}

big_int& big_int::operator-=(const big_int& other) {
    if (sign == 1 && other.sign == 1) {
        // -x - -y = -(x - y)

        if (compare(m_data, other.m_data, m_count, other.m_count)) {
            // -x - -y = -(x - y) = -(-(y - x)) = y - x
            big_int tmp(std::move(*this));
            *this = other;
            subtract_from(m_data, tmp.m_data, m_count);
            sign = 0;
            return *this;
        }

        subtract_from(m_data, other.m_data, m_count);

        return *this;
    } else if (sign != other.sign) {
        // -x - y = -(x + y)
        // or
        // x - -y = x + y
        if (m_count <= other.m_count) {
            // alloc +1 in case of overflow
            realloc(other.m_count + 1);
        }

        add_to(m_data, other.m_data, m_count);

        return *this;
    }

    if (compare(m_data, other.m_data, m_count, other.m_count)) {
        // x - y = -(-x + y) = -(y - x)
        big_int tmp(std::move(*this));
        *this = other;
        subtract_from(m_data, tmp.m_data, m_count);
        sign = 1;

        return *this;
    }

    subtract_from(m_data, other.m_data, m_count);

    return *this;
}

#if SIZE_WIDTH > 32
#ifdef _MSC_VER
#include "intrin.h"
#pragma intrinsic(_mul128)
static void multiply_with_overflow(const size_t x, const size_t y, size_t* result_overflow, size_t* result) {
    *result = _mul128(x, y, (__int64*)result_overflow);
}
#else
static void multiply_with_overflow(const size_t x, const size_t y, size_t* result_overflow, size_t* result) {
    __uint128_t prod = (__uint128_t)x * (__uint128_t)y;
    *result_overflow = (size_t)(prod >> 64);
    *result = (size_t)prod;
}
#endif
#else
static void multiply_with_overflow(const size_t x, const size_t y, size_t* result_overflow, size_t* result) {
    uint64_t prod = (uint64_t)x * (uint64_t)y;
    *result_overflow = (size_t)(prod >> 32);
    *result = (size_t)prod;
}
#endif

big_int& big_int::operator*=(const big_int& other) {
    size_t result_count = m_count + other.m_count;
    size_t* result_data = new size_t[result_count]();

    size_t product[2];
    for (size_t i = 0; i < m_count; ++i) {
        for (size_t j = 0; j < other.m_count; ++j) {
            multiply_with_overflow(m_data[i], other.m_data[j], product + 1, product);

            // add the product to the result
            // use add_to function in case of overflow
            add_to(result_data + i + j, product, 2);
        }
    }

    delete[] m_data;
    m_count = result_count;
    m_data = result_data;

    return *this;
}

big_int& big_int::operator/=(const big_int& other) {
    return *this;
}

big_int operator+(big_int lhs, const big_int& rhs) {
    lhs += rhs;
    return lhs;
}

big_int operator-(big_int lhs, const big_int& rhs) {
    lhs -= rhs;
    return lhs;
}

big_int operator*(big_int lhs, const big_int& rhs) {
    lhs *= rhs;
    return lhs;
}

big_int operator/(big_int lhs, const big_int& rhs) {
    lhs /= rhs;
    return lhs;
}

bool operator<(const big_int& lhs, const big_int& rhs) {
    if (lhs.sign == rhs.sign) {
        return lhs.sign ^ compare(lhs.m_data, rhs.m_data, lhs.m_count, rhs.m_count);
    }
    return lhs.sign < rhs.sign;
}

bool operator>(const big_int& lhs, const big_int& rhs) {
    return rhs < lhs;
}

bool operator<=(const big_int& lhs, const big_int& rhs) {
    return !(lhs > rhs);
}

bool operator>=(const big_int& lhs, const big_int& rhs) {
    return !(lhs < rhs);
}

bool operator==(const big_int& lhs, const big_int& rhs) {
    if ((lhs.sign == rhs.sign) && (lhs.m_count == rhs.m_count)) {
        for (size_t i = 0; i < lhs.m_count; ++i) {
            if (lhs.m_data[i] != rhs.m_data[i]) return false;
        }
        return true;
    }
    return false;
}

bool operator!=(const big_int& lhs, const big_int& rhs) {
    return !(lhs == rhs);
}

std::istream& operator>>(std::istream& is, big_int& x) {
    if (false) {
        is.setstate(std::ios::failbit);
    }

    return is;
}

std::ostream& operator<<(std::ostream& os, const big_int& x) {
    return os;
}

big_int& big_int::operator>>=(const size_t n) {
    return *this;
}

big_int& big_int::operator<<=(const size_t n) {
    return *this;
}

big_int& big_int::operator^=(const big_int& other) {
    if (m_count < other.m_count) {
        realloc(other.m_count);
    }

    for (size_t i = 0; i < m_count; ++i) {
        m_data[i] ^= other.m_data[i];
    }

    return *this;
}

big_int& big_int::operator|=(const big_int& other) {
    if (m_count < other.m_count) {
        realloc(other.m_count);
    }

    for (size_t i = 0; i < m_count; ++i) {
        m_data[i] |= other.m_data[i];
    }

    return *this;
}

big_int& big_int::operator&=(const big_int& other) {
    if (m_count < other.m_count) {
        realloc(other.m_count);
    }

    for (size_t i = 0; i < m_count; ++i) {
        m_data[i] &= other.m_data[i];
    }

    return *this;
}

big_int operator>>(big_int x, const size_t n) {
    x >>= n;
    return x;
}

big_int operator<<(big_int x, const size_t n) {
    x <<= n;
    return x;
}

big_int operator^(big_int lhs, const big_int& rhs) {
    lhs ^= rhs;
    return lhs;
}

big_int operator|(big_int lhs, const big_int& rhs) {
    lhs &= rhs;
    return lhs;
}

big_int operator&(big_int lhs, const big_int& rhs) {
    lhs &= rhs;
    return lhs;
}
