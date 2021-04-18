/*Rational.hpp
Nathan Damon
CS 202
4/17/2021
This is the hpp file for the Template Rational class.
*/

#ifndef RATIONAL_HPP
#define RATIONAL_HPP

#include <iostream>
#include <numeric>

// class invariant:
// _denominator is always > 0
template <typename T>
class Rational {
    template <typename U>
    friend std::ostream& operator<<(std::ostream&, const Rational<U>& rhs);
    template <typename U>
    friend Rational<U> operator+(const Rational<U>& lhs, const Rational<U>& rhs);
    template <typename U>
    friend Rational<U> operator-(const Rational<U>& lhs);
    template <typename U>
    friend bool operator==(const Rational<U>& lhs, const Rational<U>& rhs);
    template <typename U>
    friend bool operator<(const Rational<U>& lhs, const Rational<U>& rhs);

public:
    Rational(T = 0, T = 1); //NOLINT(google-explicit-constructor): Allow implicit conversion from int
    Rational& operator+=(const Rational& rhs);
    Rational& operator-=(const Rational& rhs);
    Rational& operator*=(const Rational& rhs);
    Rational& operator/=(const Rational& rhs);
    Rational& operator++();        //prefix ++
    Rational operator++(int); //postfix ++
    Rational& operator--();        //prefix --
    Rational operator--(int); //postfix --
private:
    void reduce();

    T _numerator;
    T _denominator;
};

//Rational<T> operator-(const Rational& lhs, const Rational& rhs);
//Rational<T> operator*(Rational lhs, const Rational& rhs);
//Rational<T> operator/(Rational lhs, const Rational& rhs);
//
//bool operator!=(const Rational& lhs, const Rational& rhs);
//bool operator>(const Rational& lhs, const Rational& rhs);
//bool operator<=(const Rational& lhs, const Rational& rhs);
//bool operator>=(const Rational& lhs, const Rational& rhs);


template <typename T>
Rational<T>::Rational(T num, T den) : _numerator(num), _denominator(den) {
    reduce();
}

template <typename U>
std::ostream& operator<<(std::ostream& os, const Rational<U>& rhs) {
    os << rhs._numerator;
    if (rhs._denominator != 1)
        os << "/" << rhs._denominator;
    return os;
}

template <typename U>
Rational<U> operator+(const Rational<U>& lhs, const Rational<U>& rhs) { //canonical
    auto temp{ lhs };
    temp += rhs;
    return temp;
}

template <typename U>
Rational<U>& Rational<U>::operator+=(const Rational<U>& rhs) {
    // a/b + c/d = (ad+bc)/ad
    _numerator = _numerator * rhs._denominator + rhs._numerator * _denominator;
    _denominator *= rhs._denominator;
    reduce();
    return *this;
}

template <typename U>
void Rational<U>::reduce() {
    auto gcd = std::gcd(_numerator, _denominator);
    _numerator /= gcd;
    _denominator /= gcd;
    if (_denominator < 0) {
        _numerator *= -1;
        _denominator *= -1;
    }
}

template <typename U>
Rational<U> operator-(const Rational<U>& lhs) {
    return { -lhs._numerator, lhs._denominator };
}

template <typename U>
Rational<U>& Rational<U>::operator-=(const Rational<U>& rhs) { //Canonical
    *this = *this - rhs; //uses Rational::operator- to define operator-=
    reduce();
    return *this;
}

template <typename U>
Rational<U>& Rational<U>::operator*=(const Rational<U>& rhs) {
    _numerator *= rhs._numerator;
    _denominator *= rhs._denominator;
    reduce();
    return *this;
}

template <typename U>
Rational<U>& Rational<U>::operator/=(const Rational<U>& rhs) {
    *this *= {rhs._denominator, rhs._numerator};
    reduce();
    return *this;
}

template <typename U>
Rational<U> operator-(const Rational<U>& lhs, const Rational<U>& rhs) {
    return lhs + -rhs;
}

// pass lhs by value because we were going to copy it anyway
template <typename U>
Rational<U> operator*(Rational<U> lhs, const Rational<U>& rhs) { //Canonical
    return lhs *= rhs;
}

// pass lhs by value because we were going to copy it anyway
template <typename U>
Rational<U> operator/(Rational<U> lhs, const Rational<U>& rhs) { //Canonical
    return lhs /= rhs;
}

template <typename U>
Rational<U>& Rational<U>::operator++() {//prefix ++
    return *this += 1;
}

template <typename U>
Rational<U> Rational<U>::operator++(int) {//postfix ++
    auto copy{ *this };
    ++(*this);
    return copy;
}

template <typename U>
Rational<U>& Rational<U>::operator--() {//prefix --
    return *this -= 1;
}

template <typename U>
Rational<U> Rational<U>::operator--(int) {//postfix --
    auto copy{ *this };
    --(*this);
    return copy;
}

template <typename U>
bool operator==(const Rational<U>& lhs, const Rational<U>& rhs) {
    return lhs._numerator == rhs._numerator && lhs._denominator == rhs._denominator;
}

template <typename U>
bool operator<(const Rational<U>& lhs, const Rational<U>& rhs) {
    return lhs._numerator * rhs._denominator < rhs._numerator * lhs._denominator;
}

template <typename U>
bool operator!=(const Rational<U>& lhs, const Rational<U>& rhs) {//canonical
    return !(rhs == lhs);
}

template <typename U>
bool operator>(const Rational<U>& lhs, const Rational<U>& rhs) {//canonical
    return rhs < lhs;
}

template <typename U>
bool operator<=(const Rational<U>& lhs, const Rational<U>& rhs) {//canonical
    return !(rhs > lhs);
}

template <typename U>
bool operator>=(const Rational<U>& lhs, const Rational<U>& rhs) {//canonical
    return !(rhs < lhs);
}

#endif // !RATIONAL_HPP


