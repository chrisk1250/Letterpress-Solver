// Chris Kam
// Letterpress solver using Loren Brichter's word list

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
	// letters from game to be used
	// can be entered manually or through command line
	// use lowercase letters
	string key_letters = "";
	// letters required to be in the words found
	string req_letters = "";
	
	// get any command line arguments
	// ex: ./a.out --letters=______ --req=______
	// ex: main.exe --letters=______ --req=______
	for (int i = 1; i < argc; ++i)
		if (!::strncmp(argv[i], "--letters=", 10))
			key_letters = argv[i] + 10;
		else if (!::strncmp(argv[i], "--req=", 6))
		  req_letters = argv[i] + 6;

	// stores all words found
	vector<string> all_words;
	// stores list of longest words found
	vector<string> longest_words;
	// size of longest_word
	int longest_word = 0;
	
	// open master file of words
	ifstream file("en.txt");

	string word = "";
	while (file >> word) {
		int word_length = word.length();

		// if length of dictionary word is > length of letters, go to next
		if (word_length > key_letters.length())
			continue;

		string key_letters_copy = key_letters;
		int num_letters_found = 0;
		// iterate through dictionary word
		for (int x = 0; x < word_length; x++) {
			// find position of letter in key word
			int pos = key_letters_copy.find(word[x]);
			// if that letter is found
			if (pos != -1) {
				key_letters_copy[pos] = '0';
				num_letters_found++;
			}
			if (num_letters_found == word_length)
				break;
		}
		// if dictionary word is a subset of key word
		if (num_letters_found == word_length) {
			all_words.push_back(word);
			if (word_length > longest_word) {
				// a new longest word is found
				longest_words.clear();
				longest_words.push_back(word);
				longest_word = word_length;
			}
			else if (word_length == longest_word) {
				longest_words.push_back(word);
			}
		}
	}
	
	file.close();
	// path to output file
	ofstream answer("answer.txt");

	answer << "letters: " << key_letters << "\n";
	// if no words found
	if (all_words.size() == 0)
		answer << "\nno words can be made.\n";
	else {
		// print words that contain required letters
		if (req_letters.length() > 0) {
			answer << "\nwords with required letters (" << req_letters << "):\n";
			for (int x = 0; x < all_words.size(); x++) {
				string key_letters_copy = all_words[x];
				bool flag = true;

				for (int y = 0; y < req_letters.length(); y++) {
					// find position of letter in word
					int pos = key_letters_copy.find(req_letters[y]);
					// if that letter is not found, fail
					if (pos == -1) {
						flag = false;
						break;
					}
					else
						key_letters_copy[pos] = '0';
				}

				if (flag == true)
					answer << all_words[x] << "\n";
			}
		}
		
		// print longest words
		answer << "\nlongest word (" << longest_word << "):\n";
		for (int x = 0; x < longest_words.size(); x++)
			answer << longest_words[x] << "\n";

		// print all words
		answer << "\nall words (" << all_words.size() << "):\n";
		for (int x = 0; x < all_words.size(); x++)
			answer << all_words[x] << "\n";
	}

	return 0;
}