#include "ladder.h"


void error(string word1, string word2, string msg) {
    cout << "Error: " << msg << " with " << word1 << " and " << word2 << "\n";
}


bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int str1_len = str1.size();
    int str2_len = str2.size();
    if (abs(str1_len - str2_len) > d) return false;
    if (str1_len > str2_len) return edit_distance_within(str2, str1, d);

    vector<int> dp(str2_len + 1);

    for (int i = 0; i <= str2_len; ++i) {
        dp[i] = i;
    }
    for (int i = 1; i <= str1_len; ++i) {
        int prev_diag = dp[0];
        dp[0] = i;

        int lower = max(1, i - d);
        int upper = min(str2_len, i + d);

        for (int j = lower; j <= upper; ++j) {
            int temp = dp[j];
            if (str1[i - 1] == str2[j - 1]) dp[j] = prev_diag;
            else dp[j] = 1 + min({dp[j], dp[j - 1], prev_diag});
            prev_diag = temp;
        }
        bool within_limit = false;
        for (int j = lower; j <= upper; ++j) {
            if (dp[j] <= d) {
                within_limit = true;
                break;
            }
        }
        if (!within_limit) return within_limit;
    }
    return dp[str2_len] <= d;
}


bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
    
    // int len1 = word1.length(), len2 = word2.length();
    // if (len1 - len2 != 0 && abs(len1 - len2) != 1) return false;
    
    // if (len1 == len2) {
    //     int diff_count = 0;
    //     for (int i = 0; i < len1; i++) {
    //         if (word1[i] != word2[i]) {
    //             diff_count++;
    //             if (diff_count > 1) return false;
    //         }
    //     }
    //     return diff_count == 1;
    // }

    // if (len1 > len2) return is_adjacent(word2, word1);

    // int i = 0, j = 0;
    // while (i < len1 && j < len2) {
    //     if (word1[i] != word2[j]) {
    //         if (i != j) return false;
    //         j++;
    //     } else {
    //         i++;
    //         j++;
    //     }
    // }
    // return true;
}


vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    vector<string> curr;
    if (word_list.find(end_word) == word_list.end() || begin_word == end_word) {
        error(begin_word, end_word, "infinite loop (same word)");
        return curr;
    }
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
            if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
                vector<string> new_ladder = curr;
                new_ladder.push_back(word);
                if (word == end_word) {
                    return new_ladder;
                }
                visited.insert(word);
                ladder_queue.push(new_ladder);
            }
        }
    }
    curr.clear();
    return curr;
}



void load_words(set<string> & word_list, const string& file_name) {
    ifstream infile(file_name);
    string word;
    if (infile.is_open())
        while (infile >> word) 
            word_list.insert(word);
}

void print_word_ladder(const vector<string>& ladder) {
    if (!ladder.empty()) {
        cout << "Word laddder found: ";
        for (string e: ladder) {
            cout << e << " ";
        }
    } else {cout << "No word ladder found.";}
    cout << "\n";
}

void my_assert(bool e) {cout << e << ((e) ? " passed": " failed") << "\n";}

void verify_word_ladder() {
    set<string> word_list;

    load_words(word_list, "src/words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}