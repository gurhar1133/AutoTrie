#include "FinalProjectTrie.h"

// JUST FOR TESTING PURPOSES
Sanity::Sanity(){
    
}

Sanity::~Sanity(){
    
}

int Sanity::EmptyFunc(){
    return 2;
}

// Trie functions
Trie::Trie(){
    
}




Trie::~Trie(){
    
}




shared_ptr<trie_node> Trie::InitNode(bool is_end)
{
    shared_ptr<trie_node> newNode(new trie_node);
    //cout << "new node 1" << endl;
    newNode->is_end_of_word = is_end;
    //cout << "about to loop" << endl;
    newNode->freq = 0;
    for (int i = 0; i < 26; i++)
    {
        if (newNode->children[i])
        {
            newNode->children[i] = NULL;
        }
        else
        {
        //    cout << "val at "<< i << " was null to begin with"<< endl;
        }
       
    }
    //cout << "new trie node initialized" << endl;
    return newNode;
}




void Trie::Insert(shared_ptr<trie_node> root, string newWord){
    shared_ptr<trie_node> cursor = root;
    // for testing
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    
    for (int i = 0; i < newWord.length(); i++)
    {
        //stuff for testing
        //cout << newWord[i] - 'a' << endl;
        //cout << alphabet[newWord[i] - 'a'] << endl;
        if(cursor->children[newWord[i] - 'a'] == NULL)
        {
            cursor->children[newWord[i] - 'a'] = InitNode(false);
            TrieSize++;
        }
        cursor = cursor->children[newWord[i] - 'a'];
        cursor->freq = cursor->freq + 1;
        // For testing purposes
        //cout << "node with letter " << alphabet[newWord[i] - 'a'] << " has frequency: " << cursor->freq << endl;
    }
    cursor->is_end_of_word = true;
}




bool Trie::Contains(shared_ptr<trie_node> root, string word){
    shared_ptr<trie_node> cursor = root;
    //int size_branch = 0;
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < word.size(); i++)
    {
        //cout << alphabet[word[i] - 'a'] << endl;
        if(cursor->children[word[i]-'a'] == NULL){ return false; }
       // size_branch++;
        cursor = cursor->children[word[i] - 'a'];
    }
    return true;
}




shared_ptr<trie_node> Trie::Search(shared_ptr<trie_node> root, string end_of_word_so_far){
    shared_ptr<trie_node> cursor(new trie_node);
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    cursor = root;
    int i;
    for (i = 0; i < end_of_word_so_far.length(); i++)
    {
        if(cursor->children[end_of_word_so_far[i] - 'a'] == NULL){
            //the trie doesnt have anything to complete for 
            // you in this case
            return NULL;
        }
        //cout << "the end of word so far is: " << alphabet[end_of_word_so_far[i] - 'a'] << endl;
        cursor = cursor->children[end_of_word_so_far[i] - 'a'];
    }
    //cout << "the end of word so far is: " << alphabet[end_of_word_so_far[i] - 'a'] << endl;
    return cursor;
}




int CheckKids(shared_ptr<trie_node> node){
    // finds the first non null child. but could include frequency checking later
    for (int i = 0; i < 26; i++)
    {
        if (node->children[i])
        {
            return i;
        }
    }
    return -1;
}




int getChildIndexByFreq(shared_ptr<trie_node> node){
    // get max indexed non null child and return it
    int maxIndex = -1;
    int maxVal = 0;
    //cout << "about to loop in get child" << endl;
    for (int i = 0; i<26; i++)
    {
        if(node->children[i]){
            if (node->children[i]->freq > maxVal)
            {
                maxVal = node->children[i]->freq;
                maxIndex = i;
            }
        }
    }
    //cout << "just looped in getCHild" << endl;
    return maxIndex;
}




string Trie::FreqComplete(shared_ptr<trie_node> subt, string toComplete){
    shared_ptr<trie_node> cursor;
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    cursor = subt;
    int index;
    //if (cursor->is_end_of_word){return toComplete;}
    if (!cursor){return toComplete;}
    while(!cursor->is_end_of_word)
    {
        if (index == -1){return toComplete;}
        index = getChildIndexByFreq(cursor);
        toComplete = toComplete + alphabet[index];
        cursor = cursor->children[index];
    }
    return toComplete;
}




string Trie::Complete(shared_ptr<trie_node> subt, string toComplete){
    shared_ptr<trie_node> cursor;
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    cursor = subt;
    int index;
    //if (cursor->is_end_of_word){return toComplete;}
    if (!cursor){return toComplete;}
    while(!cursor->is_end_of_word)
    {
        if (index == -1){return toComplete;}
        index = CheckKids(cursor);
        toComplete = toComplete + alphabet[index];
        cursor = cursor->children[index];
    }
    return toComplete;
}




void Trie::FillTrie(shared_ptr<trie_node> root, string filename){
    fstream file;
    string word;
    string line;
    file.open(filename);
    if (file.fail()){
        cout << "oops" << endl;
        return;
    }
    while(getline(file, line))
    {
        stringstream s_stream(line);
        //cout << "line as inputed from file: " << line << endl;
        while(s_stream.good())
        {
            getline(s_stream, word, ' ');
            //taking care of case and punctuation
            //by ignoring non alphabetical chars
            int i = 0;
            int len = word.length();
            while(i < len)
            {
                word[i] = tolower(word[i]);
                if (!isalpha(word[i])) 
                { 
                    word.erase(i--, 1); 
                    len = word.length(); 
                } 
                i++;
            }
            //cout << "filling trie with word: " << word << endl;
            Insert(root, word);
            
        }
    }
    cout << "This trie has " << TrieSize << " nodes" << endl;
}


