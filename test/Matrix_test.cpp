#include <Matrix.h>
#include <Tuple.h>
#include <gtest/gtest.h>
#include <iostream>

using namespace std;

TEST (MatrixTest, createMatrix) {
    Matrix2 m2 = Matrix2({{-3, 5},{1,-2}});
    
    EXPECT_FLOAT_EQ(m2[0][0], -3);
    EXPECT_FLOAT_EQ(m2[0][1], 5);
    EXPECT_FLOAT_EQ(m2[1][0], 1);
    EXPECT_FLOAT_EQ(m2[1][1], -2);

    Matrix3 m3 {{-3, 5, 0},{1,-2, -7},{0, 1, 1}};
    
    EXPECT_FLOAT_EQ(m3[0][0], -3);
    EXPECT_FLOAT_EQ(m3[1][1], -2);
    EXPECT_FLOAT_EQ(m3[2][2], 1);

    Matrix4 m4 = 
            {{ 1.0f,  2.0f,  3.0f,  4.0f},
            { 5.5f,  6.5f,  7.5f,  8.5f},
            { 9.0f, 10.0f, 11.0f, 12.0f},
            {13.5f, 14.5f, 15.5f, 16.5f}};
    
    EXPECT_FLOAT_EQ(m4[0][0], 1);
    EXPECT_FLOAT_EQ(m4[0][3], 4);
    EXPECT_FLOAT_EQ(m4[1][0], 5.5);
    EXPECT_FLOAT_EQ(m4[1][2], 7.5);
    EXPECT_FLOAT_EQ(m4[2][2], 11);
    EXPECT_FLOAT_EQ(m4[3][0], 13.5);
    EXPECT_FLOAT_EQ(m4[3][2], 15.5);
}

TEST(MatrixTest, testEqual) {
    Matrix4 a = {
            { 1.0f,  2.0f,  3.0f,  4.0f},
            { 5.0f,  6.0f,  7.0f,  8.0f},
            { 9.0f, 10.0f, 11.0f, 12.0f}, 
            {13.0f, 14.0f, 15.0f, 16.0f}};
    Matrix4   b = {
            { 1.0f,  2.0f,  3.0f,  4.0f},
            { 5.0f,  6.0f,  7.0f,  8.0f},
            { 9.0f, 10.0f, 11.0f, 12.0f},
            {13.0f, 14.0f, 15.0f, 16.0f}};

    Matrix4   c = {
            { 2.0f,  3.0f,  4.0f,  5.0f},
            { 6.0f,  7.0f,  8.0f,  9.0f},
            { 10.0f, 11.0f, 13.0f, 16.0f},
            {12.0f, 17.0f, 14.0f, 15.0f}};        
    EXPECT_TRUE(a == b);        
}

TEST(MatrixTest, mutiplication) {
    Matrix4 a= {
            {1.0f, 2.0f, 3.0f, 4.0f},
            {5.0f, 6.0f, 7.0f, 8.0f},
            {9.0f, 8.0f, 7.0f, 6.0f},
            {5.0f, 4.0f, 3.0f, 2.0f} };
    Matrix4 b = {
            {-2.0f, 1.0f, 2.0f,  3.0f},
            { 3.0f, 2.0f, 1.0f, -1.0f},
            { 4.0f, 3.0f, 6.0f,  5.0f},
            { 1.0f, 2.0f, 7.0f,  8.0f} };
    Matrix4 c = {
            { 20.0f, 22.0f,  50.0f,  48.0f},
            { 44.0f, 54.0f, 114.0f, 108.0f},
            { 40.0f, 58.0f, 110.0f, 102.0f},
            { 16.0f, 26.0f,  46.0f,  42.0f}};
    EXPECT_TRUE( a * b == c );
}

TEST(MatrixTest, multipicationByTuple)
{
   Matrix4 m ={
        {1.0f, 2.0f, 3.0f, 4.0f},
        {2.0f, 4.0f, 4.0f, 2.0f},
        {8.0f, 6.0f, 4.0f, 1.0f},
        {0.0f, 0.0f, 0.0f, 1.0f}};
    Tuple  t(1.0f, 2.0f, 3.0f, 1.0f);
    Tuple  t2(18.f, 24.f, 33.f, 1.f);
    EXPECT_TRUE( m * t == t2 );
}



TEST(MatrixTest,  submartixOfMatrix3)
{
    Matrix3 m = {
            { 1.f, 5.f,  0.f},
            {-3.f, 2.f,  7.f},
            { 0.f, 6.f, -3.f}};
    Matrix2 subM = {
            {-3.f, 2.f},
            { 0.f, 6.f} };
    EXPECT_TRUE( m.Submatrix(0,2) == subM );
}

TEST(MatrixTest, submartixOfMatrix4)
{
    Matrix4 m = {
            {-6.f, 1.f, 1.f, 6.f},
            {-8.f, 5.f, 8.f, 6.f},
            {-1.f, 0.f, 8.f, 2.f},
            {-7.f, 1.f,-1.f, 1.f}};
    Matrix3 subM = {
            {-6.f, 1.f, 6.f},
            {-8.f, 8.f, 6.f},
            {-7.f,-1.f, 1.f}};
    EXPECT_TRUE( m.Submatrix(2, 1) == subM );
}

TEST(MatrixTest, minorOfMatrix3)
{
    Matrix3 m = {
            {3.f, 5.f, 0.f},
            {2.f,-1.f,-7.f},
            {6.f,-1.f, 5.f} };

    EXPECT_TRUE(m.Minor(1, 0) == 25.f );
}

TEST(MatrixTest, cofactorOfMatrix3)
{
     Matrix3 m = {
            {3.f, 5.f, 0.f},
            {2.f,-1.f,-7.f},
            {6.f,-1.f, 5.f} };

    EXPECT_FLOAT_EQ(m.Minor(0, 0) , -12.f);
    EXPECT_FLOAT_EQ(m.Cofactor(0, 0) , -12.f);
    EXPECT_FLOAT_EQ(m.Minor(1, 0) , 25.f);
    EXPECT_FLOAT_EQ(m.Cofactor(1, 0) , -25.f);
}


TEST(MatrixTest, detOfMatrix3)
{
    Matrix3 m = {
            { 1.f, 2.f, 6.f},
            {-5.f, 8.f,-4.f},
            { 2.f, 6.f, 4.f}};
    EXPECT_FLOAT_EQ(m.Cofactor(0, 0) , 56.f);
    EXPECT_FLOAT_EQ(m.Cofactor(0, 1) , 12.f);
    EXPECT_FLOAT_EQ(m.Cofactor(0, 2) , -46.f);
    EXPECT_FLOAT_EQ(m.Determinant() , -196);
}

TEST(MatrixTest, detOfMatrix4)
{
    Matrix4 m ={
            {-2.f,-8.f, 3.f, 5.f},
            {-3.f, 1.f, 7.f, 3.f},
            { 1.f, 2.f,-9.f, 6.f},
            {-6.f, 7.f, 7.f,-9.f} };
    EXPECT_FLOAT_EQ(m.Cofactor(0, 0) , 690.f);
    EXPECT_FLOAT_EQ(m.Cofactor(0, 1) , 447.f);
    EXPECT_FLOAT_EQ(m.Cofactor(0, 2) , 210.f);
    EXPECT_FLOAT_EQ(m.Cofactor(0, 3) , 51.f);
    EXPECT_FLOAT_EQ(m.Determinant() , -4071.f);
}

TEST(MatrixTest, inverseMatrix4)
{
    Matrix4 m = {
        {-5.f, 2.f, 6.f,-8.f},
        { 1.f,-5.f, 1.f, 8.f},
        { 7.f, 7.f,-6.f,-7.f},
        { 1.f,-3.f, 7.f, 4.f}};

    Matrix4 mInverted= {
            { 0.21805f, 0.45113f, 0.24060f,-0.04511f},
            {-0.80827f,-1.45677f,-0.44361f, 0.52068f},
            {-0.07895f,-0.22368f,-0.05263f, 0.19737f},
            {-0.52256f,-0.81391f,-0.30075f, 0.30639f}};

    EXPECT_TRUE(m.IsInvertible());
    
    EXPECT_TRUE(m.Inverse() == mInverted );
}

TEST(MatrixTest, inverseMatrix4Identity)
{
    Matrix4 a = {
            { 3.f,-9.f, 7.f, 3.f},
            { 3.f,-8.f, 2.f,-9.f},
            {-4.f, 4.f, 4.f, 1.f},
            { 6.f, 5.f,-1.f, 1.f} };

    Matrix4 b = {
            { 8.f, 2.f, 2.f, 2.f},
            { 3.f,-1.f, 7.f, 0.f},
            { 7.f, 0.f, 5.f, 4.f},
            { 6.f,-2.f, 0.f, 5.f} };

    Matrix4 p = a * b;
    EXPECT_TRUE( p * b.Inverse() == a );
}

TEST(MatrixTest, inverseToIdentity)
{
    Matrix4 a = {
            { 3.f,-9.f, 7.f, 3.f},
            { 3.f,-8.f, 2.f,-9.f},
            {-4.f, 4.f, 4.f, 1.f},
            { 6.f, 5.f,-1.f, 1.f} };

    EXPECT_TRUE( a * a.Inverse() == Matrix4::Identity());
}