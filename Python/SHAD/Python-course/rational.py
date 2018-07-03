from __future__ import print_function
import sys


def gcd(b, a):
    if b > a:
        a, b = b, a
    while b != 0:
        a = a % b
        a, b = b, a
    return a


class Rational:
    def __init__(self, numerator=0, denominator=1):
        """

        :type numerator: integer
        :type denominator: positive nonzero integer
        """
        if denominator < 0:
            self.numerator = -numerator
            self.denominator = -denominator
        else:
            self.numerator = numerator
            self.denominator = denominator

    def __add__(self, other):
        return Rational(self.numerator * other.denominator +
                        self.denominator * other.numerator,
                        self.denominator * other.denominator)

    def __mul__(self, other):
        return Rational(self.numerator * other.numerator,
                        self.denominator * other.denominator)

    def __truediv__(self, other):
        if other.numerator != 0:
            return Rational(self.numerator * other.denominator,
                            self.denominator * other.numerator)
        else:
            raise ValueError("Divisor is equal to zero!!!")

    def __neg__(self):
        return Rational(-self.numerator, self.denominator)

    def __sub__(self, other):
        return self.__add__(other.__neg__())

    def __eq__(self, other):
        return self.__sub__(other).numerator == 0

    def __ne__(self, other):
        return self.__sub__(other).numerator != 0

    def __str__(self):
        gcd_ = gcd(abs(self.denominator), abs(self.numerator))
        return str(int(self.numerator / gcd_)) + '/' + str(int(self.denominator / gcd_))

exec(sys.stdin.read())
