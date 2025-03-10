#include "ladder.h"
#include <cctype>
#include <fstream>
#include <vector>
#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void error(string word1, string word2, string msg)
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
    return current[len_2] == d;
}

// finds word that has an edit_distance of 1
// calls edit_distance within to calculate distance
bool is_adjacent(const string& last_word, const string& next_word)
{
    return edit_distance_within(last_word, next_word, 1);
}

std::vector<std::string> ladderToVector(std::stack<string> ladder)
{
    std::vector<std::string> res;
    while (!ladder.empty())
    {
        res.push_back(ladder.top());
        ladder.pop();
    }
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
        for (std::string word : word_list)
        {
            if (is_adjacent(last_word, word))
            {
                // std::cout << last_word << " is adjacent to: " << word << std::endl;
                if (visited.find(word) == visited.end())
                {
                    visited.insert(word);
                    std::stack<std::string> new_ladder = ladder;
                    new_ladder.push(word);

                    if(word == end_word)
                    {
                        // std::cout << word << " was a match!" << std::endl;
                        return ladderToVector(new_ladder);
                    }
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
    // std::cout << "Size of word list is: " << word_list.size() << std::endl;
}

void print_word_ladder(const vector<string>& ladder)
{
    for (std::string word : ladder)
    {
        std::cout << word << ' ';
    }
}

void verify_word_ladder() {

    set<string> word_list;

    load_words(word_list, "/home/hjardine/ics46/ics-46-hw-9-HectorJardines/src/words.txt");

    // std::vector<std::string> path = generate_word_ladder("cat", "dog", word_list);
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    // print_word_ladder(path);
    // std::cout << path.size() << std::endl;

    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);

}