// ladder.cpp
#include "ladder.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;


void error(string word1, string word2, string msg) {
    /*
    Prints an error message for the provided words with an accompanying message.

    Parameters:
        word1 (string): The first word.
        word2 (string): The second word.
        msg (string): The error message to be printed.

    Returns:
        None.
    */

    std::cerr << "Error with words \"" << word1 << "\" and \"" << word2 << "\": " << msg << std::endl;
}


bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    /*
    Determines if the edit distance between two strings is within a given threshold.

    Parameters:
        str1 (const string&): The first string.
        str2 (const string&): The second string.
        d (int): The maximum allowed edit distance.

    Returns:
        bool: True if the edit distance between str1 and str2 is less than or equal to d; false otherwise.
    */

    if (abs((int)str1.size() - (int)str2.size()) > d){
        return false;
    }
    
    // Get the lengths of both strings.

    int m = str1.size();
    int n = str2.size();
    
    // Handling for the case when we only allow one edit (d == 1).
    if (d == 1) {

        // If both strings are identical, then the edit distance is 0.
        if(str1 == str2){
            return true;
        } 

        // If the strings have the same length, then check if exactly one character differs.
        if(m == n) {
            int diffCount = 0;

             // Iterate over each character position.
            for (int i = 0; i < m; i++) {
                if (tolower(str1[i]) != tolower(str2[i])) {
                    diffCount++;

                    // More than one difference means they are not adjacent.
                    if(diffCount > 1){
                        return false;
                    } 
                }
            }

            return diffCount == 1;
        } 
        else {     

            // For strings with length differing by exactly one, try to match by skipping a character.
            // Determine which string is shorter (s) and which is longer (t).
            const std::string &s = (m < n) ? str1 : str2;
            const std::string &t = (m < n) ? str2 : str1;

            size_t i = 0;
            size_t j = 0;
            bool foundDifference = false;

            // Traverse both strings while there are characters left in both.
            while(i < s.size() && j < t.size()){

                // Compare corresponding characters after converting to lowercase.
                if(tolower(s[i]) == tolower(t[j])){
                    i++; 
                    j++;
                } 
                else{
                    if(foundDifference){
                        return false;
                    }    

                    // Mark that a difference has been found.
                    foundDifference = true;

                    // Skip the extra character in the longer string and continue comparison.
                    j++; 
                }
            }
            return true;
        }
    }

    // For cases where d > 1, compute the edit distance 
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Initialize the first column: converting a string of length i to an empty string requires i deletions.
    for (int i = 0; i <= m; i++) {
        dp[i][0] = i;
    }

    // Initialize the first row: converting an empty string to a string of length j requires j insertions.
    for (int j = 0; j <= n; j++) {
        dp[0][j] = j;
    }

    // Fill in the rest of the table.
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {

            // If the characters at the current positions are the same (ignoring case), no new edit is needed.
            if (tolower(str1[i - 1]) == tolower(str2[j - 1]))
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]}) + 1;
        }
    }

    return dp[m][n] <= d;
}

bool is_adjacent(const string& word1, const string& word2) {

    /*
    Checks if two words are adjacent, meaning they differ by exactly one edit operation (replacement, insertion, or deletion).

    Parameters:
        word1 (const string&): The first word.
        word2 (const string&): The second word.

    Returns:
        bool: True if word1 and word2 are adjacent; false otherwise.
    */

    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    /*
    Generates the shortest word ladder from a begin word to an end word using breadth-first search.

    Parameters:
        begin_word (const string&): The starting word for the ladder.
        end_word (const string&): The ending word for the ladder.
        word_list (const set<string>&): The set of valid words (dictionary).

    Returns:
        vector<string>: A vector representing the word ladder. Returns an empty vector if no ladder is found.
    */

    queue<vector<string>> ladder_queue;
    set<string> visited;
    ladder_queue.push({begin_word});
    visited.insert(begin_word);  

    if (begin_word == end_word) {
        return {begin_word};
    }
    
    while (!ladder_queue.empty()) {
        // Take the front ladder from the queue
        vector<string> current_ladder = ladder_queue.front();
        ladder_queue.pop();

        // The last word in this ladder
        string last_word = current_ladder.back();

        // If we've reached end_word, return the ladder immediately
        if (last_word == end_word) {
            return current_ladder;
        }

        // Try to expand the ladder by adding valid neighbors
        for (const auto &word : word_list) {

            // If last_word and word are adjacent and word hasn't been visited yet:
            if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
                
                vector<string> new_ladder = current_ladder;
                new_ladder.push_back(word);

                // Mark this word as visited, so we don't reuse it in another path
                visited.insert(word);

                // If it's the end_word, return the new ladder right away
                if (word == end_word) {
                    return new_ladder;
                }
                ladder_queue.push(new_ladder);
            }
        }
    }

    return {}; 
}

void load_words(set<string> & word_list, const string& file_name) {
    /*
    Loads words from a file into a set.

    Parameters:
        word_list (set<string>&): A reference to a set where the words will be stored.
        file_name (const string&): The name of the file to load words from.

    Returns:
        None.
    */

    ifstream in(file_name);

    // Check if the file was successfully opened.
    if (!in) {
        std::cerr << "Cannot open " << file_name << std::endl;
        return;
    }
    std::string word;

    // Read each word from the file.
    while (in >> word) {
        for (auto & c : word) {
            c = tolower(c);
        }
        word_list.insert(word);
    }

    in.close();
}


void print_word_ladder(const vector<string>& ladder) {
    /*
    Prints the word ladder in a formatted way.

    Parameters:
        ladder (const vector<string>&): The word ladder to print.

    Returns:
        None.
    */

    // Check if the ladder is empty.
    if (ladder.empty()){
        std::cout << "No word ladder found." << std::endl;
        return;
    }

    // Print each word in the ladder separated by an arrow.
    std::cout << "Word ladder found: ";
    for (size_t i = 0; i < ladder.size(); i++){
        std::cout << ladder[i] << " ";
    }

    std::cout << endl;
}

void verify_word_ladder() {
    /*
    Verifies the word ladder implementation by running predefined test cases and printing the results.

    Parameters:
        None.

    Returns:
        None.
    */

    #define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
    set<std::string> word_list;
    load_words(word_list, "words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
    #undef my_assert
}
