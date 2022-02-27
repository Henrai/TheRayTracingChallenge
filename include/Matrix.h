#pragma once

#include <initializer_list>
#include <stdint.h>
#include <assert.h>
#include <iostream>
#include <iomanip> 

#include "MathUtil.h"
#include "Tuple.h"

using namespace math;

template<uint8_t DIM>
class Matrix {
private:
float m_data[DIM][DIM];


public:

constexpr uint8_t getDimension() const {return DIM;}

static Matrix Identity();

Matrix() {}
Matrix(const Matrix& m) {
    
    for(size_t i = 0; i < DIM; i++) {
        for (size_t j = 0; j < DIM; j++) {
            m_data[i][j] = m[i][j];
        }
    }
}
Matrix(std::initializer_list<std::initializer_list<float> > data);

float* operator[](size_t row) {
    return m_data[row];
}
float*  operator[](size_t row) const {
    return const_cast<float*>(m_data[row]);
}
bool operator==(const Matrix<DIM>& matrix) const;
bool operator!=(const Matrix<DIM>& matrix) const {
    return !(*this == matrix);
}

Matrix operator=(const Matrix& matrix) {
    for(size_t i = 0; i < DIM; i++) {
        for (size_t j = 0; j < DIM; j++) {
            m_data[i][j] = matrix[i][j];
        }
    }
    return *this;
}

bool IsInvertible() const {
    return !equal(this->Determinant(),0.0f);
}
float Determinant() const;



Matrix<DIM> Inverse() const;
Matrix<DIM - 1> Submatrix(uint8_t row, uint8_t col) const;
Matrix operator*(Matrix const& other) const; 



template<uint8_t D = DIM>
typename std::enable_if<D == 4, Tuple>::type
operator*(Tuple const& v) const {
   Tuple t;
   for (size_t i = 0; i < 4; i++) {
       float temp = 0;
       for (size_t j = 0; j < 4; j++) {
           temp += m_data[i][j] * v[j];
       }
       t[i] = temp;
   }
   return t;
}

template<uint8_t D = DIM>
typename std::enable_if<(D > 2) ,float>::type
Cofactor(uint8_t row, uint8_t col) const {
    float sign = !((row+col) & 1) ? 1 : -1;
    return sign * this->Minor(row,col);
}

template<uint8_t D = DIM>
typename std::enable_if<(D > 2) ,float>::type
Minor(uint8_t row, uint8_t col) const {
    return this->Submatrix(row,col).Determinant();
}
};


using Matrix4 = Matrix<4>;
using Matrix3 = Matrix<3>;
using Matrix2 = Matrix<2>;


template<uint8_t DIM>
Matrix<DIM>::Matrix(std::initializer_list<std::initializer_list<float> > data) {
    assert(data.size() == DIM);
    assert(data.begin()->size() == DIM);
    uint8_t row = 0;
    uint8_t col = 0;
    for ( auto i :  data) {
        col = 0;
        for (auto j : i) {
            m_data[row][col] = j;
            col++;
        }
        row++;
    }
}

template<uint8_t DIM>
bool Matrix<DIM>::operator==(const Matrix& matrix) const {
    if(DIM != matrix.getDimension()) {
        return false;
    }
    for (uint8_t i = 0; i < DIM; i++) {
        for (uint8_t j = 0; j < DIM; j++) {
            if (!equal(m_data[i][j], matrix.m_data[i][j])) {
                return false;
            }
        }
    }
    return true;
}


template<uint8_t DIM>
std::ostream& operator<<(std::ostream& os, const Matrix<DIM> & m) {
    for (int i = 0; i < DIM; i++) {
        os << "| ";
        for (int j = 0; j < DIM; j++)
        {
            os << std::setw(5)<< m[i][j];
            if (j < (DIM - 1)) os << ", ";
        }
        os << " |" << std::endl;
    }
    return os;
}

template<>
inline float Matrix2::Determinant () const{
    return m_data[0][0] * m_data[1][1] - m_data[0][1] * m_data[1][0];
}

template<>
inline Matrix4 Matrix4::operator*(Matrix4 const& other) const {
    Matrix4 ans;
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j< 4; j++)
        {
            ans[i][j] =
                m_data[i][0] * other.m_data[0][j] +
                m_data[i][1] * other.m_data[1][j] +
                m_data[i][2] * other.m_data[2][j] +
                m_data[i][3] * other.m_data[3][j];
        }
    }
    return ans;
}

template<uint8_t DIM>
inline float Matrix<DIM>::Determinant () const {
    float det = 0.f;
    for (int j = 0; j < DIM; j++)
    {
        det +=  m_data[0][j] * Cofactor(0, j);
    }
    return det;
}


template<uint8_t DIM>
Matrix<DIM - 1> Matrix<DIM>::Submatrix(uint8_t row, uint8_t col) const  {
    Matrix<DIM-1> ans;
    for(int i = 0; i < DIM; i++) {
        for (int j =0; j < DIM; j++) {
            if (i == row || j == col)
                continue;
            int r = i > row ? i - 1 : i;
            int c = j > col ? j - 1 : j;
            ans[r][c] = m_data[i][j];
        }
    }
    return ans;
}

template<uint8_t DIM>
Matrix<DIM> Matrix<DIM>::Inverse() const {
    Matrix<DIM> mat;
    float det = this->Determinant();
    for(size_t i = 0; i < DIM; i++) {
        for(size_t j = 0; j < DIM; j++) {
            mat[j][i] = this->Cofactor(i,j)/det;
        }
    }
    return mat;
}

template<>
inline Matrix2 Matrix2::Identity(){
    return Matrix({
        {1,0},
        {0,1}
    });
}

template<>
inline Matrix3 Matrix3::Identity(){
    return Matrix({
        {1,0,0},
        {0,1,0},
        {0,0,1}
    });
}

template<>
inline Matrix4 Matrix4::Identity(){
    return Matrix({
        {1,0,0,0},
        {0,1,0,0},
        {0,0,1,0},
        {0,0,0,1}
    });
}
