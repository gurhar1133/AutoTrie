#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include "../trieCode/FinalProjectTrie.h"

using namespace std;

char getch() {
        char buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
                perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");
        return (buf);
}

int main(){
    
    
    // Main thus far is a demo of how the functions can perform autocomplete
    /*
    Trie myTrie;
    string freqComp;
    string comp;
    shared_ptr<trie_node> top(new trie_node);
    myTrie.FillTrie(top, "trumpSpeech.txt");
    string incomplete;
    
    cout << "Enter a incomplete word: (or enter quit to quit)" << endl;
    cin >> incomplete;
    for (int i = 0; i < incomplete.length(); i++)
    {
        incomplete[i] = tolower(incomplete[i]);
    }
    while (incomplete != "quit"){
        shared_ptr<trie_node> p1 = myTrie.Search(top, incomplete);
        freqComp = myTrie.FreqComplete(p1, incomplete);
        comp = myTrie.Complete(p1, incomplete);
        cout << incomplete << " completed with frequency traversal: " << freqComp << endl;
        cout << "   vs. " << endl;
        cout << incomplete << " completed without frequency traversal: " << comp << endl;
        cout << "Enter a incomplete word: (or enter quit to quit)" << endl;
        cin >> incomplete;
        for (int i = 0; i < incomplete.length(); i++)
        {
            incomplete[i] = tolower(incomplete[i]);
        }
    }
    */
    
    // testing out continuous input collection
    


    //cout << "Lets complete some words" << endl; 
    char charInput;
    string build = "";
    Trie myTrie;
    string freqComp;
    string comp;
    shared_ptr<trie_node> top(new trie_node);
    int corpusChoice;
    string textFile;
    
    cout << "______Welcome to auto-complete______" << endl;
    cout << "Which corpus: " << endl;
    cout << "   1) The entirety of The Hobbit by JRR Tolkien" << endl;
    cout << "   2) A Donald Trump speech" << endl;
    cout << "   3) Enter a textfile name" << endl;
    cin >> corpusChoice;
    if(corpusChoice == 1){
        textFile = "theHobbit.txt";
    }
    else if(corpusChoice == 2)
    {
        textFile = "trumpSpeech.txt";
    }
    else if(corpusChoice == 3)
    {
        cout << "Enter file name:" << endl;
        cin >> textFile;
    }
    cout << "Filling the trie" << endl;
    myTrie.FillTrie(top, textFile);
    
    cout << "Lets complete some words" << endl; 
    cout << "Here's the rules: " << endl;
    cout << "   1) You dont have to hit enter, just type the word" << endl;
    cout << "   2) If at any point you want to type a new word, type 1" << endl;
    cout << "   3) If at any point you want to exit, type 0" << endl;
    cout << "You may now type away!" << endl;
    
    while (charInput != '0')
    {
        
        if (charInput == '1'){
            build = "";
            cout << endl << "You've chosen to enter a new word!" << endl;
            cout << "Type away!" << endl;
            }
        
        // Waits for single character 
        charInput = getch(); 
        
        if (charInput == '0'){
            cout << "Goodbye" << endl;
            break;
        }
        build = build + charInput;
        shared_ptr<trie_node> srchPtr = myTrie.Search(top, build);
        freqComp = myTrie.FreqComplete(srchPtr, build);
        comp = myTrie.Complete(srchPtr, build);
        cout << endl << "Your uncompleted word: " << build << endl;
        cout << endl << "completed  with frequency traversal = " << freqComp << endl;
        cout << endl << "completed without frequency traversal = " << comp << endl;
        
        //cout << "string length: " << build.length() << endl;
    }
    
    return 0;
}