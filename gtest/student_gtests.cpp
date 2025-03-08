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

TEST(LadderTests, GenerateLadderSameEndBegin) {
    string word1 = "cat";
    string word2 = "cat";
    set<string> placeholder;
    vector<string> result = generate_word_ladder(word1, word2, placeholder);
    EXPECT_TRUE(result.empty());
}

TEST(LadderTests, GenerateLadderEndWordNotInList) {
    string word1 = "cat";
    string word2 = "cut";
    set<string> placeholder{"cue", "hat"};
    vector<string> result = generate_word_ladder(word1, word2, placeholder);
    EXPECT_TRUE(result.empty());
}

TEST(LadderTests, GenerateLadderShort) {
    string word1 = "cat";
    string word2 = "cheat";
    set<string> placeholder{"chat", "car", "cheat"};
    vector<string> result = generate_word_ladder(word1, word2, placeholder);
    EXPECT_TRUE(result[0] == "cat");
    EXPECT_TRUE(result[1] == "chat");
    EXPECT_TRUE(result[2] == "cheat");
    EXPECT_TRUE(result.size() == 3);
}

TEST(LadderTests, GenerateLadderNoPossibilities) {
    string word1 = "cat";
    string word2 = "cheat";
    set<string> placeholder{"car", "cheat"};
    vector<string> result = generate_word_ladder(word1, word2, placeholder);
    EXPECT_TRUE(result.empty());
}


int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
