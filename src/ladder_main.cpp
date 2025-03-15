#include "ladder.h"
#include <cassert>
void verify_edit_dist()
{
    assert(edit_distance_within("wallow", "swallow", 1));
    assert(!edit_distance_within("wallow", "shallow", 1));
    assert(edit_distance_within("wallow", "wallow", 1));
}

void verify_is_adjacent()
{
    assert(is_adjacent("wallow", "wallow"));
    assert(!is_adjacent("happy", "quintillion"));
}

void verify_ladder()
{
    verify_word_ladder();
}

int main()
{
    verify_edit_dist();
    verify_is_adjacent();
    verify_ladder();
}