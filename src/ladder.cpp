#include "ladder.h"
#include <fstream>
#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void error(string word1, string word2, string msg)
{
    std::cerr << "ERROR - " << msg << ": FROM - " << word1 << ", TO - " << word2 << std::endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d)
{

}

bool is_adjacent(const string& word1, const string& word2);

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