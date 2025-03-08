#include <gtest/gtest.h>

#include "../src/dijkstras.h"
#include "../src/ladder.h"

TEST(LadderTests, EditDistanceWithin) {
    string word1 = "cat";
    string word2 = "cut";
    EXPECT_TRUE(edit_distance_within(word1, word2, 1));
    EXPECT_TRUE(edit_distance_within(word1, word2, 2));
    word2 = "cast";
    EXPECT_TRUE(edit_distance_within(word1, word2, 1));
    word2 = "ct";
    EXPECT_TRUE(edit_distance_within(word1, word2, 1));
    word2 = "casts";
    EXPECT_FALSE(edit_distance_within(word1, word2, 1));
    EXPECT_TRUE(edit_distance_within(word1, word2, 2));
}

TEST(LadderTests, Adjacent) {
    string word1 = "cat";
    string word2 = "cut";
    EXPECT_TRUE(is_adjacent(word1, word2));
    word2 = "cast";
    EXPECT_TRUE(is_adjacent(word1, word2));
    word2 = "ct";
    EXPECT_TRUE(is_adjacent(word1, word2));
    word2 = "casts";
    EXPECT_FALSE(is_adjacent(word1, word2));
}


int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
