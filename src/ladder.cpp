#include "ladder.h"
void error(string word1, string word2, string msg)
{
    std::cerr << "ERROR - " << msg << ": FROM - " << word1 << ", TO - " << word2 << std::endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d)
{

}

bool is_adjacent(const string& word1, const string& word2);
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list);
void load_words(set<string> & word_list, const string& file_name);
void print_word_ladder(const vector<string>& ladder)
{
    for (std::string word : ladder)
    {
        std::cout << word << ' ';
    }
}
void verify_word_ladder();