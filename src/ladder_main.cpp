
#include "ladder.h"
#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;

int main(){
    /*
    Main function for the word ladder program.
    Prompts the user for a start and end word, loads the dictionary, generates the word ladder, and prints the result.

    Parameters:
        None.

    Returns:
        int: Exit status (0 if successful, non-zero otherwise).
    */

    std::string start;
    std::string end;

    // Prompt the user for the starting word.
    std::cout << "Enter start word: ";
    std::cin >> start;

    // Prompt the user for the ending word.
    std::cout << "Enter end word: ";
    std::cin >> end;
    
    // Check if the start and end words are the same.
    // If they are the same, display an error and exit.
    if(start == end) {
        error(start, end, "Start and end words must be different.");
        return 1;
    }
    
    // Convert start word to lowercase.
    for(auto & c : start){
         c = tolower(c);
    }

    // Convert end word to lowercase.
    for(auto & c : end) {
        c = tolower(c);
    }
    
    set<std::string> word_list;
    load_words(word_list, "words.txt");

    // Ensure that the end word is in the dictionary.
    if (word_list.find(end) == word_list.end()){
        std::cout << "End word \"" << end << "\" is not in the dictionary." << std::endl;
        return 1;
    }
    
    vector<std::string> ladder = generate_word_ladder(start, end, word_list);
    print_word_ladder(ladder);
    
    // verify_word_ladder();
    
    return 0;
}
