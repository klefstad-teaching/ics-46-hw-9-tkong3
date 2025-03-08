#include "ladder.h"


void error(string word1, string word2, string msg) {
    cout << "Error: " << msg << " with " << word1 << " and " << word2 << "\n";
}


bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int str1_len = str1.size();
    int str2_len = str2.size();
    if (abs(str1_len - str2_len) > d) return false;
    vector<int> prev(str2_len + 1), curr(str2_len + 1);

    for (int i = 0; i <= str2_len; ++i) {
        prev[i] = i;
    }
    for (int j = 1; j <= str1_len; ++j) {
        curr[0] = j;

        int lower = max(1, j - d);
        int upper = min(str2_len, j + d);

        for (int n = lower; n <= upper; n++) {
            if (str1[j - 1] == str2[n - 1]) curr[n] = prev[n - 1];
            else curr[n] = 1 + min({prev[n], curr[n - 1], prev[n - 1]});
        }
        prev.swap(curr);
    }
    return prev[str2_len] <= d;
}


bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}


vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    vector<string> curr;
    if (word_list.find(end_word) == word_list.end() || begin_word == end_word) return curr;

    queue<vector<string>> ladder_queue;
    curr.push_back(begin_word);
    ladder_queue.push(curr);

    set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        curr = ladder_queue.front();
        ladder_queue.pop();
        string last_word = curr.back();

        for (string word : word_list) {
            if (is_adjacent(last_word, word)) {
                if (visited.find(word) == visited.end()) {
                    visited.insert(word);
                    vector<string> new_ladder = curr;
                    new_ladder.push_back(word);
                    if (word == end_word) {
                        return new_ladder;
                    }
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    curr.clear();
    return curr;
}
