/*
 * File: WordLadder.cpp
 * --------------------
 * Name: Yijun Fang 
 * ID: z5061743
 * Tutor: Peter
 * This file is the starter project for the word ladder problem on Assignment #1.
 */

#include "genlib.h"
#include "lexicon.h"
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

//turn vaaector into string and store then into a answerVector
void findVector(std::vector<std::string> v, std::vector<std::string> &answerVector ){

	if(v.size()==0) return;
	
	std::string str = v.at(0);
	for ( unsigned int i = 1; i < v.size(); i++) {
		str += " " + v.at(i);
	}
	answerVector.push_back(str);
}

//print the ladder 
void printVector(std::vector<std::string> v){
	unsigned int i = 0;
	if(v.size()==0) return;
	std::cout << "Found ladder: ";
	for ( i = 0; i < v.size(); i++) {
		std::cout << v.at(i) << std:: endl;
	}
}

bool notInMap(std::map<std::string, unsigned int> & myMap, std::string word, unsigned int levelLength){

  	if (myMap.find(word) == myMap.end())
		return true;
	else if (myMap[word] == levelLength+1)
		return true;
	return false;
}

std::vector<std::string> copyVector(std::vector<std::string> curr, std::vector<std::string> & prev){
	std::vector<std::string> v;

	for (unsigned int i = 0; i < curr.size(); i++) {
		std::string str = curr.at(i);
		prev.push_back(str);
	}
	return v;
}

int main(int argc, char * argv[]) {

	char c;
	bool firstExist = true;
	unsigned int minLength = 0;
	unsigned int levelLength = 0;

	std::string start ;
	std::string desn ;
	std::string currWord;
	std::string tmpWords;

	std::vector<std::string> currVec;
	std::vector<std::string> answerVector;
	std::map<std::string, unsigned int> myMap;
	std::queue<std::vector<std::string>> myQueue;

	Lexicon lex("EnglishWords.dat");

	std::cout << "Enter start word (RETURN to quit): "; 
	getline (std::cin, start);
	if(start == "") return 0;
	std::transform(start.begin(), start.end(), start.begin(), ::tolower);

	std::cout << "Enter destination word: "; 
	getline (std::cin, desn);
	if(desn == "") return 0;
	std::transform(desn.begin(), desn.end(), desn.begin(), ::tolower);

	if(start.size()!= desn.size()) {
		std::cout <<"No ladder found."<<std::endl; 
		return 0;
	}

	if(desn.compare(start) == 0) {
		std::cout <<"Found ladder:"<< start<<" " << desn << std::endl;
		return 0;
	}

	levelLength = 1;
	myMap[start] = levelLength;

	//form first vector
	currVec.push_back(start);
	myQueue.push(currVec);

	//loop in the queue
	while(true){

		if( myQueue.empty() && (levelLength !=1)){ 
			std::cout <<"No ladder found."<< std::endl; 
			return 0;
		}
		
		//pop one path out of the queue and exam it 
		currVec = myQueue.front();
		myQueue.pop();
		currWord = currVec.back();

		//the path is longer than the shortest path found -> print all path and exit
		if(currVec.size() == minLength && minLength != 0) {
			std::sort (answerVector.begin(), answerVector.end());
			printVector(answerVector);
			return 0; 
		}	

		//start a deeper level /longer path
		if(currVec.size() > levelLength){
			levelLength = currVec.size();
		}

		//for every word, find all its neighbour word
		for(unsigned int i = 0 ; i < start.size() ; i++){
			tmpWords = currWord;

			for(c = 'a'; c <='z'; c++){
				tmpWords[i] = c;
				if(tmpWords.compare(currWord)== 0) continue;

				//found a path and put it into the answer collection. ie answerVector
				if(tmpWords.compare(desn) == 0 ) {
					if(firstExist){
						firstExist = false;
						minLength = currVec.size()+1;
					}
		  	 		currVec.push_back(tmpWords);
		  	 		findVector(currVec, answerVector);
		  	 		break;
				}

				//for every valid word, check if it is already in the map (can be reached by shorter path)
				else if(lex.containsWord(tmpWords)  && notInMap(myMap,tmpWords, levelLength)){
					myMap[tmpWords] = levelLength+1;
					std::vector<std::string> newVector = currVec;
					newVector.push_back(tmpWords);
					myQueue.push(newVector);
				}
			}
		}		
	}
	return 0;
}