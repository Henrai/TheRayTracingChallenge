#include <gtest/gtest.h>
#include <Color.h>
#include <Canvas.h>

TEST(CanvasTest, initializeCanvas) {
    Canvas c(10, 20);
    EXPECT_EQ(c.getWidth(), 10);
    EXPECT_EQ(c.getHeight(), 20);
    for (size_t i = 0; i < 10; i++) {
        for (size_t j = 0; j < 20; j++) {
            EXPECT_TRUE(c[i][j] == Color::BLACK);
        }
    }
}

TEST(CanvasTest, setColor) {
    Canvas c(10, 20);
    c[2][4] = Color::RED;
    EXPECT_TRUE(c[2][4] == Color::RED);
}

TEST(CanvaseTest, writeToPPM) {
    constexpr char const* expected =
        "P3\n"
        "5 3\n"
        "255\n"
        "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n";


    Canvas c(5, 3);
    c[0][0] = Color(1.5,0,0);
    c[2][1] = Color(0,0.5,0);
    c[4][2] = Color(-0.5, 0, 1.0);
    std::ostringstream ss;
    ss << c;    
    std::string s = ss.str();
    EXPECT_STREQ(expected, s.c_str());
}

TEST(CanvasTest, splitLongLines) {
    constexpr char const* expected = "P3\n10 2\n255\n"
        "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n"
        "153 255 204 153 255 204 153 255 204 153 255 204 153\n"
        "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n"
        "153 255 204 153 255 204 153 255 204 153 255 204 153\n";
    Canvas c(10, 2);
    Color color(1.f, 0.8f, 0.6f);
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 2; j++) {
            c[i][j] = color;
        }
    std::ostringstream ss;
    ss << c;    
    std::string s = ss.str();
    EXPECT_STREQ(expected, s.c_str());
}

TEST(CanvasTest, terminateByNewLine) {
    Canvas const c(5, 3);
     std::ostringstream ss;
    ss << c;    
    std::string s = ss.str();
    EXPECT_EQ(s[s.size() - 1], '\n');
}