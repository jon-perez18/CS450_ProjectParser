// cs490 project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Note: this is actually a datavis project. just named the file incorrectly. oh well.
// Author: Andrew Hinton

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <functional>
#include <iomanip>
#include <string>
#include <locale>

std::string file_baseFolder_tt = "../"; // base
std::string filename = "correct_t.csv"; //file to parse

std::string fileName_article_reader_csv = file_baseFolder_tt + filename; //where the stream will search. modify based on where ur file is located.

int num_lines = 0;
bool in_quotes = false;

void io_read_from_profit_history(std::string filename);

void p2s(std::string str);
void p2sl(std::string str, int lines_at_end = 1);
void bl();
void bl(int count);

inline std::string word_at(const std::string phrase, int indexof);
inline int words_in_phrase(const std::string phrase);
void find_phrase(std::string phrase, std::string word, std::map<std::string, int>& phrase_tracker, std::function<int(std::map<std::string, int>&, std::string)> callback);
inline bool issign(char c);
inline bool iswc(char c);
std::string get_next_word(FILE* in, char c);
std::string get_next_word(FILE* in);

//converts 12345678 to 12,345,678
template<class T>
std::string FormatWithCommas(T value)
{
	std::stringstream ss;
	ss.imbue(std::locale(""));
	ss << std::fixed << value;
	return ss.str();
}

//rounds a comma-formatted number with decimals
template<class T>
std::string FormatWithCommas_rounded(T value, int decimal_places)
{
	std::stringstream ss;

	ss.imbue(std::locale(""));
	ss << std::fixed << std::setprecision(decimal_places) << value;
	return ss.str();
}

int main()
{
	io_read_from_profit_history(fileName_article_reader_csv);

	//std::cout << num_lines;
}

void io_read_from_profit_history(std::string filename) {

	FILE* in;
	fopen_s(&in, filename.c_str(), "r");
	if (in == nullptr) {
		p2sl("File can not be read. Try again.");
		return;
	}

	std::map<std::string, int> phrase_tracker;
	std::string word = "";
	int c;

	// our decided-on list of keywords to search for
	// #Note: Never used. this document could be generic-ified 
	//		to simply foreach every keyword and weight with a dictionary.
	std::string keywords[16]{
		"line",	//0
		"bar",	//1
		"unit",	//2
		"table",//3
		"trend",//4
		"percentage",//5
		"high",//6
		"low",//7
		"mean",//8
		"differential",
		"rate",
		"time",
		"curve",
		"level",
		"ratio",
		"probability"
	};

	float line = 0, bar = 0, histo = 0, candle = 0;

	while ((c = fgetc(in)) != EOF) {

		// read each word.
		word = get_next_word(in, c);
		if (word == "EOF") break; //end the reader stream if word==EOF


		//find_phrase searches for a given phrase in the document. 
		// Once phrase is found, it enters the callback area to perform any additional calculations

		//in this case, the phrase is 'line'
		find_phrase("line", word, phrase_tracker, [&word, &in, &line, &bar, &histo, &candle](std::map<std::string, int>& phrase_tracker, std::string p)
			{
				// NOTE: all of the following find_phrase() call's comments are irrelevant. this one's phrases are up to date.
				// excuse the rest, I copy & pasted and didn't have the time/care to remove the copy&pasted comments

				word = get_next_word(in); //needed in order to not print the word twice when consol-logging the found phrase.

				line += 1;
				bar += 0.1;
				histo += 0.2;
				candle += 0.5;

				return 0; // set to 0 to keep searching for instances of this word. -- see find_phrase() function for return codes.
			}
		);


		find_phrase("bar", word, phrase_tracker, [&word, &in, &line, &bar, &histo, &candle](std::map<std::string, int>& phrase_tracker, std::string p)
			{
				word = get_next_word(in); //needed in order to move on. ignore this.

				line += 0.1;
				bar += 1;
				histo += 0.5;
				candle += 0.3;

				return 0; // set to 0 to keep searching for instances of this word.
			}
		);

		
		find_phrase("unit", word, phrase_tracker, [&word, &in, &line, &bar, &histo, &candle](std::map<std::string, int>& phrase_tracker, std::string p)
			{
				word = get_next_word(in); //needed in order to move on. ignore this.

				line += 0.1;
				bar += 0.9;
				histo += 0.9;
				candle += 0.9;

				return 0; // set to 0 to keep searching for instances of this word.
			}
		);


		find_phrase("time", word, phrase_tracker, [&word, &in, &line, &bar, &histo, &candle](std::map<std::string, int>& phrase_tracker, std::string p)
			{
				word = get_next_word(in); //needed in order to move on. ignore this.

				line += 1;
				bar += 0.2;
				histo += 0.2;
				candle += 0.5;

				return 0; // set to 0 to keep searching for instances of this word.
			}
		);


		find_phrase("trend", word, phrase_tracker, [&word, &in, &line, &bar, &histo, &candle](std::map<std::string, int>& phrase_tracker, std::string p)
			{
				word = get_next_word(in); //needed in order to move on. ignore this.

				line += 1;
				bar += 1;
				histo += 1;
				candle += 1;

				return 0; // set to 0 to keep searching for instances of this word.
			}
		);


		find_phrase("percentage", word, phrase_tracker, [&word, &in, &line, &bar, &histo, &candle](std::map<std::string, int>& phrase_tracker, std::string p)
			{
				word = get_next_word(in); //needed in order to move on. ignore this.

				line += 0.3;
				bar += 0.8;
				histo += 0.9;
				candle += 0.8;

				return 0; // set to 0 to keep searching for instances of this word.
			}
		);


		find_phrase("high", word, phrase_tracker, [&word, &in, &line, &bar, &histo, &candle](std::map<std::string, int>& phrase_tracker, std::string p)
			{
				word = get_next_word(in); //needed in order to move on. ignore this.

				line += 0.8;
				bar += 0.9;
				histo += 0.8;
				candle += 0.9;

				return 0; // set to 0 to keep searching for instances of this word.
			}
		);


		find_phrase("low", word, phrase_tracker, [&word, &in, &line, &bar, &histo, &candle](std::map<std::string, int>& phrase_tracker, std::string p)
			{
				word = get_next_word(in); //needed in order to move on. ignore this.

				line += 0.8;
				bar += 0.9;
				histo += 0.8;
				candle += 0.9;

				return 0; // set to 0 to keep searching for instances of this word.
			}
		);


		find_phrase("mean", word, phrase_tracker, [&word, &in, &line, &bar, &histo, &candle](std::map<std::string, int>& phrase_tracker, std::string p)
			{
				word = get_next_word(in); //needed in order to move on. ignore this.

				line += 0.6;
				bar += 0.8;
				histo += 0.9;
				candle += 0.89;

				return 0; // set to 0 to keep searching for instances of this word.
			}
		);


		find_phrase("differential", word, phrase_tracker, [&word, &in, &line, &bar, &histo, &candle](std::map<std::string, int>& phrase_tracker, std::string p)
			{
				word = get_next_word(in); //needed in order to move on. ignore this.

				line += 0.9;
				bar += 0.1;
				histo += 0;
				candle += 0;

				return 0; // set to 0 to keep searching for instances of this word.
			}
		);


		find_phrase("rate", word, phrase_tracker, [&word, &in, &line, &bar, &histo, &candle](std::map<std::string, int>& phrase_tracker, std::string p)
			{
				word = get_next_word(in); //needed in order to move on. ignore this.

				line += 0.8;
				bar += 0.2;
				histo += 0.8;
				candle += 0.9;

				return 0; // set to 0 to keep searching for instances of this word.
			}
		);

		find_phrase("curve", word, phrase_tracker, [&word, &in, &line, &bar, &histo, &candle](std::map<std::string, int>& phrase_tracker, std::string p)
			{
				word = get_next_word(in); //needed in order to move on. ignore this.

				line += 1;
				bar += 0.2;
				histo += 1;
				candle += 0.3;

				return 0; // set to 0 to keep searching for instances of this word.
			}
		);


		find_phrase("level", word, phrase_tracker, [&word, &in, &line, &bar, &histo, &candle](std::map<std::string, int>& phrase_tracker, std::string p)
			{
				word = get_next_word(in); //needed in order to move on. ignore this.

				line += 0.8;
				bar += 0.9;
				histo += 0.8;
				candle += 0.9;

				return 0; // set to 0 to keep searching for instances of this word.
			}
		);

		find_phrase("ratio", word, phrase_tracker, [&word, &in, &line, &bar, &histo, &candle](std::map<std::string, int>& phrase_tracker, std::string p)
			{
				word = get_next_word(in); //needed in order to move on. ignore this.

				line += 0.8;
				bar += 0.6;
				histo += 0.1;
				candle += 0.8;

				return 0; // set to 0 to keep searching for instances of this word.
			}
		);

		find_phrase("probability", word, phrase_tracker, [&word, &in, &line, &bar, &histo, &candle](std::map<std::string, int>& phrase_tracker, std::string p)
			{
				word = get_next_word(in); //needed in order to move on. ignore this.

				line += 0.5;
				bar += 0.3;
				histo += 0.8;
				candle += 0.8;

				return 0; // set to 0 to keep searching for instances of this word.
			}
		);


		find_phrase("t8t", word, phrase_tracker, [&word, &in, &line, &bar, &histo, &candle](std::map<std::string, int>& phrase_tracker, std::string p)
			{
				word = get_next_word(in); //needed in order to move on. ignore this.
				num_lines++;

				p2sl("-------------------------------------- ARTICLE " + std::to_string(num_lines));
				p2sl("line = " + FormatWithCommas_rounded(line, 2));
				p2sl("bar = " + FormatWithCommas_rounded(bar, 2));
				p2sl("histogram = " + FormatWithCommas_rounded(histo, 2));
				p2sl("candlestick = " + FormatWithCommas_rounded(candle, 2));
				//report goes here
				line = 0; bar = 0; histo = 0; candle = 0;


				return 0; // set to 0 to keep searching for instances of this word.
			}
		);

		// 


		find_phrase("t8t", word, phrase_tracker, [&word, &in](std::map<std::string, int>& phrase_tracker, std::string p)
			{
				word = get_next_word(in); //needed in order to move on. ignore this.
				/*p2sl(word);*/
				num_lines++;

				return 0; // set to 0 to keep searching for instances of this word.
			}
		);

	}

	fclose(in);

	return;
}


// Print to console
void p2s(std::string str) {
	std::cout << str;
}

//print to consol with # of lines
void p2sl(std::string str, int lines) {
	p2s(str);
	bl(1);
	if (lines > 1)bl(lines);
}

// break line -- adds a line-break to the console.
void bl() {
	bl(1);
}

void bl(int count) {
	for (int i = 0; i < count; i++)
		std::cout << std::endl;
}


// gets the word starting at given index in given phrase.
inline std::string word_at(const std::string phrase, int indexof) {
	std::string word;
	int len = phrase.length(), curIndex = 0;

	for (int i = 0; i < len; i++) {
		char c = phrase[i];
		if (isalnum(c)) { //start on word
			while ((!isspace((c = phrase[i])) && isalnum(c)) && i < len) {
				word += c;
				i++;
			}
			if (curIndex == indexof) break; // at the word we want.
			else curIndex++;
			word = "";
		}
	}
	return word;
}

//gets # of words in a string. e.g. "a cat in the hat" is 5 words.
inline int words_in_phrase(const std::string phrase) {
	std::string word;
	int len = phrase.length(), word_count = 0;

	for (int i = 0; i < len; i++) {
		char c = phrase[i];
		if (isalnum(c)) { //start on word
			while ((!isspace((c = phrase[i])) && isalnum(c)) && i < len) {
				i++;
			}
			word_count++;
		}
	}
	return word_count;
}

// designed around reading data streams.
// does not recognize symbols, just alpha-numeric phrases. 
void find_phrase(std::string phrase, std::string word, std::map<std::string, int>& phrase_tracker, std::function<int(std::map<std::string, int>&, std::string)> callback) {
	//phrase tracker will store this functions state.

	// phrase tracker has certain codes. 
	//		0 = reset - look for more of this phrase.
	//		-1 = phrase found, stop searching (saves time)
	//		-2 = phase found, track following characters.
	if (phrase_tracker[phrase] == -1) return; // -1 = phrase located. stop searching.
	else if (phrase_tracker[phrase] == -2) { // -2 = phrase located, see what's after it.
		phrase_tracker[phrase] = callback(phrase_tracker, phrase);
		return;
	}

	if (!phrase_tracker.count(phrase)) //init
		phrase_tracker[phrase] = 0;

	int curState = phrase_tracker[phrase];

	//# put testers here

	//let's say ur in state 0, u only look at word indexof(0) of the phrase. if not the word, then set to 0.
	if (word == word_at(phrase, curState)) { // word found

		// if final word found,
		if (words_in_phrase(phrase) == curState + 1) {
			phrase_tracker[phrase] = -2;
			find_phrase(phrase, word, phrase_tracker, callback);
			return;
		}

		// else, update the words tagged
		phrase_tracker[phrase]++;
	}
	else {//where the word found was not in phrase, then you hit the wrong phrase.
		phrase_tracker[phrase] = 0;
	}

	// if phrase + data found, set state to -1

	//testers -- move them to the line @ 'put testers here' when needed.
	/*
		p2sl("f:word: " + word);
		p2sl("f:state: " + std::to_string(curState));
		p2sl("f:w==waI: " + std::to_string(word == word_at(phrase, curState))); //word == word at index
	*/
}


inline bool issign(char c) {
	return (c == '+' || c == '-');
}

// is word connector --> '.' and '/' should only work for numbers
inline bool iswc(char c) {
	return (c == '-' || c == '_' || c == '.' || c == '/');
}

// assumes that this-word and this_word are connected as one word.
std::string get_next_word(FILE* in, char c) {
	std::string word = "";

	if (c == EOF) return "EOF";

	if (c > 255 || c < 0) return get_next_word(in, fgetc(in));
	if (isalnum(c) || issign(c)) { //start word

		word += tolower(c);
		while ((c = fgetc(in)) != EOF) { //while: read through word

			int g = (int)c;
			if (g < 0 || g > 255) continue; // ignore unicode chars.

			if (c == '\n') {

				break;
			}
			else if (isalnum(c) || iswc(c)) {
				word += tolower(c);
			}
			else { //end word on anything that isnt alphanumb, '_', or '-'
				//print (word + " ");
				break;
			}
		}
		return word;
	}

	// if no words found, check if non-alphaNum. if EOF, return EOF warning.
	return c == EOF ? "EOF" : get_next_word(in, fgetc(in));
}

std::string get_next_word(FILE* in) {
	return get_next_word(in, fgetc(in));
}





void throwError(std::string msg) {
	std::cout << "\n:: ERROR :: " << msg << std::endl;
}



inline std::string to_lower(std::string s) {
	for (char& c : s)
		c = tolower(c);
	return s;
}

inline std::string trim(std::string s) {
	std::string trimmed = "";
	for (char& c : s)
		if (!isspace(c))
			trimmed += c;
	return trimmed;
}


// converts my minimize functions into numbers
inline long long parseValue(std::string value) {

	value = to_lower(value);
	value = trim(value);

	if (value == "") {
		throwError("Empty String Given");
		return -1;
	}

	double d_number;
	long long number, suffix;
	std::string numb_string = "";
	bool isDbl = false, isError = false, hasSuffix = false, isSigned = false, isNeg = false;

	std::map<std::string, long long> suffixes = {
		{"k",	1000 },
		{"m",	1000000 },
		{"mil", 1000000 },
		{"b",	1000000000},
		{"bil",	1000000000},
		{"t",	1000000000000},
		{"tril",1000000000000}
	};

	// algo: read thru each character until you hit a letter. substring the number part and parse that
	// validate the letter/word part. trim all whitespace.
	// 54.321m is once the value hits '.', convert to double, yes, use a double. double is 15-18 sig digits. trillion is 10 digits.
	// convert final value to long long.
	for (int i = 0; i < std::size(value); i++) {
		if (issign(value[i])) {
			//only allow sign at front and nowhere else
			if (i != 0) {
				throwError("improper input - sign must be in front");
				return -1;
			}
			if (isSigned) {
				throwError("improper input - more than one sign operator found.");
				return -1;
			}
			isSigned = true;
			if (value[i] == '-') isNeg = true;
		}
		else if (value[i] == '.') {
			if (isDbl) { // don't let there be 2 decimals.
				throwError("improper input - more than one decimal point found");
				return -1;
			}
			isDbl = true;
			numb_string += value[i];
		}
		else if (value[i] == ',' || value[i] == '\'') {//if the number has delimiters, recognize them.

			for (int j = 1; j <= 3; j++) {
				if (!isdigit(value[i + j])) {
					throwError("improper input: " + value);
					return -1;
				}
				numb_string += value[i + j];
			}
			i += 3; // push the iterator up the validated spaces.
			continue;
		}
		else if (isdigit(value[i])) { // if digit, add it.
			numb_string += value[i];
		}
		else if (isalpha(value[i])) { // if alphabet char, 
			//see if the rest of the string is a key in our map.
			//if so, pull the suffix value. if not, throw error.

			hasSuffix = true;
			std::string _suffix = value.substr(i);

			if (suffixes.find(_suffix) != suffixes.end()) {
				//found and therefore the value is complete.
				suffix = suffixes[_suffix];
				break;
			}
			else {
				throwError("suffix not found: '" + _suffix + "'");
				return -1;
			}
		}
		else if (isspace(value[i])) { // if space, trim it.
			continue;
		}
		else { // if character not recognized

			std::string s = value.substr(i, 1);
			throwError("invalid character: '" + s + "\'");
			return -1;
		}
	}

	// okay. for loop complete. now lets see what values we have.

	std::string::size_type sz;

	if (!hasSuffix) {
		suffix = 1;
	}
	if (isDbl) {

		d_number = std::stod(numb_string, &sz);
		number = d_number * suffix;
	}
	else {
		number = std::stoll(numb_string, &sz) * suffix;
	}

	return (isNeg ? -1 * number : number);
}



// 1 digit minimze. e.g. 100.2m instead of 100.22mil
std::string minimize_1d(long long val_signed) {
	double new_val;

	long long val = abs(val_signed);

	std::string sign = val_signed < 0 ? "-" : "";

	std::string suffix;

	if (val >= parseValue("1t")) {
		new_val = (double)val / parseValue("1t");
		suffix = "t";
	}
	else if (val >= parseValue("1b")) {
		new_val = (double)val / parseValue("1b");
		suffix = "b";
	}
	else if (val >= parseValue("1m")) {
		new_val = (double)val / parseValue("1m");
		suffix = "m";
	}
	else if (val >= parseValue("1k")) {
		new_val = (double)val / parseValue("1k");
		suffix = "k";
	}
	else {
		return std::to_string(val);
	}

	return sign + FormatWithCommas_rounded(new_val, 1) + suffix;
}
