#include "convert.hpp"
#include <string>
#include <sstream>
#include <unordered_map>
#include <string>
#include "MyPriorityQueue.hpp"

// You should not need to change this function.
void loadWordsIntoTable(std::unordered_set<std::string> & words, std::istream & in)
{
	std::string line, word;
	std::stringstream ss;

	while(getline(in, line))
	{
		ss.clear();
		ss << line;
		while(ss >> word)
		{
			words.insert(word);
		}
	}

}

struct Node {
    std::string word;
    std::string parent;
    int lcDistance;
    int sum;
      
    Node() {
        
    }
    
    Node(std::string word, std::string parent, int lcDistance, int sum) {
        this->word = word;
        this->parent = parent;
        this->lcDistance = lcDistance;
        this->sum = sum;
    }
    
    const bool operator<(const Node& other) {
        return lcDistance + sum < other.lcDistance + other.sum;
    }
    
    const bool operator>(const Node& other) {
        return lcDistance + sum > other.lcDistance + other.sum;
    }
    
};

int letterDiff(std::string s1, std::string s2) {
    int diff = 0;
    for (int i = 0; i < s1.length(); i++) {
        if (s1[i] != s2[i]) {
            diff++;
        }
    }
    return diff;
}

std::vector< std::string > convert(const std::string & s1, const std::string & s2, const std::unordered_set<std::string> & words)
{
    std::vector<std::string> ret;

    if(s1 == s2)
        return ret;
    
    std::unordered_map<std::string, std::pair<int, std::string>> visited;
    MyPriorityQueue<Node> pq;

    pq.insert({s1, "", 0, letterDiff(s1, s2)});
    
    while(!pq.isEmpty()) {
        Node currentNode = pq.min();
        pq.extractMin();
        int sum = currentNode.lcDistance + currentNode.lcDistance;
        visited.insert({currentNode.word, {sum + 1, ""}});

        for(std::string elem : words) {
            if(elem.size() == s1.size()) {
                if(letterDiff(elem, currentNode.word) == 1 && visited.find(elem) == visited.end()) {
                    pq.insert({elem, currentNode.word, currentNode.lcDistance + 1, letterDiff(elem, s2)});
                    visited.insert({elem, {(currentNode.lcDistance + 1) + letterDiff(elem, s2), currentNode.word}});
                }
                else if(letterDiff(elem, currentNode.word) == 1 && visited.find(elem) != visited.end()) {
                    if(visited.find(elem)->second.first > ((currentNode.lcDistance + 1) + letterDiff(elem, s2))) {
                        pq.insert({elem, currentNode.word, currentNode.lcDistance + 1, letterDiff(elem, s2)});
                        visited.find(elem)->second = {(currentNode.lcDistance + 1) + letterDiff(elem, s2), currentNode.word};
                    }
                }

            }
        }
    }
    
    if(visited.find(s2) == visited.end()) {
        return ret;
    }
    
    else {
        ret.push_back(s2);
        std::string next = visited.find(s2)->second.second;
        
        while(next != "") {
            ret.push_back(next);
            next = visited.find(next)->second.second;
        }
        
        reverse(ret.begin(), ret.end());
        return ret;
    }
}