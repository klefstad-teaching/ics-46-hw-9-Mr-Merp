#include "ladder.h"

void error(string word1, string word2, string msg) {
    cout << word1 << ' ' << word2 << ' ' << msg << endl;
}

bool lev_distance(const string& str1, const string& str2, int d) {
    int len1 = str1.length(), len2 = str2.length();
    vector<vector<int> > lev(len1 + 1, vector<int>(len2 + 1, 0));
    for (int i = 0; i <= len1; i++) {
        lev[i][0] = i;
    }
 
    for (int j = 0; j <= len2; j++) {
        lev[0][j] = j;
    }
 
    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                lev[i][j] = lev[i - 1][j - 1];
            }
            else {
                lev[i][j] = 1 + min(lev[i][j - 1], min(lev[i - 1][j], lev[i - 1][j - 1]));
            }
        }
    }
    return lev[len1][len2] <= d;
}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    int len1 = str1.length(), len2 = str2.length();
    if (abs(len1 - len2) > d) return false;
    if (d == 1) {
        if (len1 == len2) {
            int count = 0;
            // if string length is the same then characters will be compared side by side
            for (int i = 0; i < len1; ++i) {
                if (str1[i] != str2[i]) {
                    ++count;
                    if (count > d) return false;
                }
            }
            return true;
        }
        else {
            const string& shrt = (len1 < len2) ? str1 : str2;
            const string& lng = (len1 < len2) ? str2 : str1;
            int Llen = lng.length(), Slen = shrt.length();

            int count = 0;
            // loop for checking deletions and insertions
            for (int l = 0, s = 0; s < Slen; ++l, ++s) {
                if (lng[l] != shrt[s]) {
                    ++count;
                    if (count > d)  return false;
                    --s;
                }
            }
            return true;
        }
    }
    else {
        return lev_distance(str1, str2, d);
    }
}

bool is_adjacent(const string& word1, const string& word2) {
    // return the edit distance within function with a set int of 1;
    return edit_distance_within(word1, word2, 1);
}

void load_words(set<string> & word_list, const string& file_name) {
    fstream in(file_name);
    for (string i; in >> i;) 
        word_list.insert(i);
    in.close();
}

void print_word_ladder(const vector<string> & ladder) {
    for (const string& word : ladder)
        cout << word << ' ';
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word,
                                    const set<string>& word_list) {
    queue<vector<string>> lq;
    lq.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);
    while (!lq.empty()) {
        vector<string> ladder = lq.front();
        lq.pop();
        string last = ladder[ladder.size() - 1];
        for (const string& word : word_list) {
            if (is_adjacent(last, word)) {
                if (!(visited.find(word) != visited.end())) {
                    visited.insert(word);
                    vector<string> new_ladder;
                    for (const string& i : ladder) new_ladder.push_back(i);
                    new_ladder.push_back(word);
                    if (word == end_word) return new_ladder;
                    lq.push(new_ladder);
                }
            }
        }
    }
    cout << "bruh" << endl;
    return vector<string>();
}

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