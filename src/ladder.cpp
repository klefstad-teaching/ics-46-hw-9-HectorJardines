#include "ladder.h"
#include <cctype>
#include <algorithm>
#include <fstream>
#include <vector>
#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void error(const string & word1, const string & word2, const string & msg)
{
    std::cerr << "ERROR - " << msg << ": FROM - " << word1 << ", TO - " << word2 << std::endl;
}

// checks whether edit can be made in certain distance
// *arks, b*rks, ba*ks, bar*s, bark*
// barks -> sharks
// sbarks
// sharks
bool edit_distance_within(const std::string& str1, const std::string& str2, int d)
{
    int len_1 = str1.length();
    int len_2 = str2.length();

    // holds all change costs curr[len_2] should hold the final number of steps, but why?
    std::vector<int> current(len_2 + 1, 0); 

    for (int j = 0; j <= len_2; ++j)
        current[j] = j;

    for (int i = 1; i <= len_1; ++i)
    {
        int prev = current[0]; // 0 on first loop
        current[0] = i; // 1 on first loop

        for (int j = 1; j <= len_2; ++j)
        {
            int temp = current[j]; // save current[j] to set to prev
            if (std::tolower(str1[i - 1]) == std::tolower(str2[j - 1]))
                current[j] = prev;
            else
                current[j] = 1 + std::min(current[j - 1], std::min(prev, current[j]));

            prev = temp;
        }
    }
    return current[len_2] == d || current[len_2] == 0;
}

// finds word that has an edit_distance of 1
// calls edit_distance within to calculate distance
bool is_adjacent(const string& last_word, const string& next_word)
{
    return edit_distance_within(last_word, next_word, 1);
}

std::vector<std::string> ladderToVector(std::stack<string> & ladder)
{
    std::vector<std::string> res;
    while (!ladder.empty())
    {
        res.push_back(ladder.top());
        ladder.pop();
    }
    // std::reverse(res.begin(), res.end());
    return res;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list)
{
    std::queue<std::stack<std::string>> ladders;
    std::stack<std::string> first;
    first.push(begin_word);
    ladders.push(first);

    std::set<std::string> visited;
    visited.insert(begin_word);

    while(!ladders.empty())
    {
        std::stack<std::string> ladder = ladders.front();
        ladders.pop();
        std::string last_word = ladder.top();
        if (last_word == end_word)
            return ladderToVector(ladder);

        for (const std::string & word : word_list)
        {
            if (is_adjacent(last_word, word))
            {
                if (visited.find(word) == visited.end())
                {
                    visited.insert(word);
                    std::stack<std::string> new_ladder = ladder;
                    new_ladder.push(word);

                    // if(word == end_word)
                    // {
                    //     return ladderToVector(new_ladder);
                    // }
                    ladders.push(new_ladder);
                }
            }
        }
    }
    return std::vector<string>();
}

void load_words(std::set<string> & word_list, const std::string& file_name)
{
    ifstream in(file_name);
    std::string word;
    while (in >> word)
        word_list.insert(word);
    in.close();
}

void print_word_ladder(const vector<string>& ladder)
{
    size_t path_len = ladder.size();
    if (path_len > 0)
        std::cout << "Word ladder found: ";
    else
        std::cout << "No word ladder found.";

    for (int i = path_len - 1; i >= 0; --i)
    {
        std::cout << ladder[i] << ' ';
    }
    std::cout << std::endl;
}

void verify_word_ladder() {

    set<string> word_list;

    load_words(word_list, "/home/hjardine/ics46/ics-46-hw-9-HectorJardines/src/words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);

}