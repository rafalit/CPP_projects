#include <iostream>
#include <string>
#include <stdexcept> // std::out_of_range()
#include <iomanip>   // std::setw()

using namespace std;

#include "matrix.h"

#ifndef _MSC_FULL_VER // if not Visual Studio Compiler
    #warning "Klasa jest do zaimplementowania. Instrukcja w pliku naglowkowym"
#else
    #pragma message ("Klasa jest do zaimplementowania. Instrukcja w pliku naglowkowym")
#endif

TwoDimensionMatrix::TwoDimensionMatrix(){
    for(size_t i=0; i<size_; i++){
        for(size_t j=0; j<size_; j++){
            matrix_[i][j] = 0;
        }
    }
}


TwoDimensionMatrix::TwoDimensionMatrix(const TwoDimensionMatrix & matrix__){
    for(size_t i=0; i<size_; i++){
        for(size_t j=0; j<size_; j++) {
            matrix_[i][j] = matrix__.matrix_[i][j];
        }
    }
}


TwoDimensionMatrix::TwoDimensionMatrix(const MatrixElement matrix[size_][size_]){
    for(int i=0; i<size_; i++){
        for(int j=0; j<size_; j++){
            matrix_[i][j] = matrix[i][j];
        }
    }
}

TwoDimensionMatrix& TwoDimensionMatrix:: operator=(const TwoDimensionMatrix& m){
        if(this != &m){
            for(int i=0; i<size_; i++){
                for(int j=0; j<size_; j++){
                    matrix_[i][j] = m.matrix_[i][j];
                }
            }
        }
        return *this;
}

std::ostream& TwoDimensionMatrix::operator<<(std::ostream& ma) const {
    for (int i = 0; i < size_; i++) {
        for (int j = 0; j < size_; j++) {
            ma << matrix_[i][j] << " ";
        }
        ma << std::endl;
    }
    return ma;
}


std::ostream& operator<<(std::ostream& os, const TwoDimensionMatrix& mat) {
    for (int i = 0; i < mat.size_; ++i) {
        for (int j = 0; j < mat.size_; ++j) {
            os << mat.get(i, j);
            if (j < mat.size_ - 1) {
                os << ' ';
            }
        }
        if (i < mat.size_ - 1) {
            os << '\n';
        }
    }
    return os;
}


std::istream& operator>>(std::istream& is, TwoDimensionMatrix& matrix) {
    for (size_t row = 0; row < matrix.size(); ++row) {
        for (size_t col = 0; col < matrix.size(); ++col) {
            MatrixElement element;
            is >> element;
            matrix.set(row, col, element);
        }
    }

    return is;
}

TwoDimensionMatrix operator+(const TwoDimensionMatrix& matrix1, const TwoDimensionMatrix& matrix2) {
    TwoDimensionMatrix result;

    for (size_t row=0; row < TwoDimensionMatrix::size(); ++row)
        for (size_t column=0; column < TwoDimensionMatrix::size(); ++column)
            result.set(row, column, matrix1.get(row, column) + matrix2.get(row, column));

    return result;
}

TwoDimensionMatrix& TwoDimensionMatrix::operator*=(MatrixElement number) {
    for (size_t row=0; row < TwoDimensionMatrix::size(); ++row)
        for (size_t column=0; column < TwoDimensionMatrix::size(); ++column)
            matrix_[row][column] *= number;

    return *this;
}

TwoDimensionMatrix& TwoDimensionMatrix :: operator*=(double number) {
    for (int i = 0; i < size_; i++) {
        for (int j = 0; j < size_; j++) {
            matrix_[i][j] *= number;
        }
    }
    return *this;
}

TwoDimensionMatrix TwoDimensionMatrix::operator&&(const TwoDimensionMatrix matrix) const{
    TwoDimensionMatrix result;
    for (size_t i = 0; i < size_; ++i) {
        for (size_t j = 0; j < size_; ++j) {
            result[i][j] = matrix_[i][j] && matrix.matrix_[i][j];
        }
    }
    return result;
}