#ifndef TRIE_H__
#define TRIE_H__

#include <string>
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// A class just for making sure that the unit testing and make 
// files are up and running
class Sanity{
public:
  Sanity();
  ~Sanity();
  int EmptyFunc();
    
private:
  int empty_count;
};


// Trie node struct

struct trie_node {
    
    // children. Just doing lower case characters for efficiency sake
    shared_ptr<trie_node> children[26]; 
    
    // if it is the end of a word
    bool is_end_of_word;
    
    // maybe to come will be a frequency value
    int freq;
    
};

class Trie{
    public:
        // Constructor destructor
        Trie();
        ~Trie();
        // node initializer
        shared_ptr<trie_node> InitNode(bool is_end);
        
        // takes a file name and the root of the trie and fills it with the text 
        // contents of the file.
        void FillTrie(shared_ptr<trie_node> root, string filename);
    
       
    
        // takes a word and inserts it into the trie this will assist with 
        // FillTrie THIS FUNCTION WILL/MAY CARRY OUT FREQUENCY ASSIGNMENT
        // IF I CHOOSE TO DO FREQUENCY ASSIGNMENT 
        void Insert(shared_ptr<trie_node> root, string newWord);
        
        // for auto complete purposes. Essentially, search and complete will work in tandem
        // search returns pointer to the end of the word so far. eg. user types "sma"
        // if sma is in the trie, it will return a pointer to the "a" node. Otherwise it would
        // return a pointer to null.
        shared_ptr<trie_node> Search(shared_ptr<trie_node> root, string end_of_word_so_far);
        
        //complete will take the node of the end of a semi completed word 
        //if it occurs in the trie and return the nearest complete word
        //this function may be edited later to account for frequences of words
        //which may alter which path down the trie is taken.
        // an example: user types in "sma", search returns the pointer to a
        // since "small" is in the trie, the trie will traverse untill it reaches 
        // an end of word node and in this case return "small".
        string Complete(shared_ptr<trie_node> subt, string toComplete);
    
        // same as complete just uses a different helper function
        // for frequency based child indexing
        string FreqComplete(shared_ptr<trie_node> subt, string toComplete);
    
        // Traverses the trie to see if the word argument is contained in the trie
        // returns true if word is in the trie. This function is useful for testing
        // NOTE TO SELF, maybe this can be used to add new words to the trie that arent
        // allready in it in the auto complete functionality
        bool Contains(shared_ptr<trie_node> root, string word);
    
        int TrieSize = 0;
};

// a helper function for checking children nodes
// will be updated/another function written for frequency
// checking
int CheckKids(shared_ptr<trie_node> node);

//helper function for frequency based auto-completion
int getChildIndexByFreq(shared_ptr<trie_node> node);

#endif // EMPTY_H__