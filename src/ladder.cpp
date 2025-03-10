#include "ladder.h"
#include <fstream>
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

    std::vector<int> current(len_2 + 1, 0); // holds all change costs

    for (int j = 0; j <= len_2; ++j)
        current[j] = j;

    for (int i = 1; i <= len_1; ++i)
    {
        int prev = current[0]; // 0 on first loop
        current[0] = i;

        for (int j = 1; j <= len_2; ++j)
        {
            int temp = current[j];
            if (str1[i - 1] == str2[j - 1])
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

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list);

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
    for (std::string word : ladder)
    {
        std::cout << word << ' ';
    }
}

void verify_word_ladder() {

    set<string> word_list;

    load_words(word_list, "words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);

}