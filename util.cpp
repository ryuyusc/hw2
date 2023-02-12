#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    string temp = convToLower(trim(rawWords));  //removes the whitespace before and after words
    set<string> ans;  //initializes the answer set
    int indexOfSpace = 0;  //this is the tracker for the index of the letter after space   


    int length = temp.length();
    for (int i = 0; i < length; i++) {
        if ((temp[i] == ' ') && (i - indexOfSpace >= 2)) {
            //this is the word separated
            string word = temp.substr(indexOfSpace, i - indexOfSpace);

            //this goes through each char of individual word
            int individualWordLength = word.length();
            for (int j = 0; j < individualWordLength; j++) {
                //checks for punctuation
                if (ispunct(word[j])) {
                    //checks if the part before the punctuation is valid
                    if (individualWordLength - (individualWordLength - j) >= 2) {
                        word = word.substr(0, j);
                        break;
                    }
                    //else checks if the part after the punctuation is valid
                    else if (individualWordLength - j - 1 >= 2) {
                        word = word.substr(j + 1, individualWordLength - j - 1);
                        break;
                    }
                }
            }
            ans.insert(word);
            indexOfSpace = i + 1;
        }
        else if ((i == length - 1) && (i - indexOfSpace + 1 >= 2)) {
            //this is the word separated
            string word = temp.substr(indexOfSpace, i - indexOfSpace + 1);

            int individualWordLength = word.length();
            for (int j = 0; j < individualWordLength; j++) {
                //checks for punctuation
                if (ispunct(word[j])) {
                    if (ispunct(word[j])) {
                        //checks if the part before the punctuation is valid
                        if (individualWordLength - (individualWordLength - j) >= 2) {
                            word = word.substr(0, j);
                            break;
                        }
                        //else checks if the part after the punctuation is valid
                        else if (individualWordLength - j - 1 >= 2) {
                            word = word.substr(j + 1, individualWordLength - j - 1);
                            break;
                        }
                    }
                }
            }
            ans.insert(word);
            //the loop would end
        }
    }

    return ans;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
