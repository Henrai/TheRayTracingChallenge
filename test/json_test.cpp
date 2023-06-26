#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <string>
#include <utils/json.h>
#include <string_view>

class JsonTest : public ::testing::Test {

protected:
    const std::string test_data = 
        R"JSON({
    "aa": "BB",
    "cc": {
        "a": 10,
        "B": [1,2],
        "c": null,
        "d": true,
        "e": false,
   }, 
   'ff': {'aa': 12}})JSON";
    void SetUp() override {
        // Create a temporary test.txt file
        std::ofstream testfile("test.txt");
        testfile << test_data;
        testfile.close();
    }

    void TearDown() override {
        // Delete the temporary test.txt file
        std::remove("test.txt");
    }
};

TEST_F(JsonTest, fromJsonFile) {
    // Call readfile() and get the result
    Json::JSONObject contents = Json::JSONObject::fromFile("test.txt");
    std::cout << contents << std::endl;
    EXPECT_EQ(contents["aa"].asString(), "BB"); 
}

