//
//  main.cpp
//  Hangman
//
//  Created by Pham Lightning on 2/27/21.
//

#include <iostream>

#include <string>

using namespace std;

class HangDrawer{
private:
    string myWord;
    char* represent;
    string hanging;
    int badGuessCount;
    public :
    HangDrawer(string word){
        myWord=word;
        hanging="#######";
         badGuessCount=0;
        represent= new char[word.length()];
        for(int i=0;i <myWord.length();i++){
            represent[i]='-';
        }
    }
    void drawHang(int n){
        if(badGuessCount<hanging.length()){
        if(n<badGuessCount){
            
           cout<<hanging[n]<<endl;
            drawHang(n+1);
        }
        }
    }
    bool rightGuess(char guess){
        bool correctGuess=false;
        for(int i=0;i<myWord.length();i++){
            if(myWord[i]==guess){
             
                revealCharacter(i, guess);
                correctGuess=true;
            }
    }
        return correctGuess;
    }
    void revealCharacter(int indexToReveal, char guess){
        
        represent[indexToReveal]=guess;
       
    }
    void doHangman(char guess){
            if(rightGuess(guess)==true){
                cout<<"Good guess"<<endl;
                cout<<"The character is "<<guess<<"!"<<endl;
                cout<<represent<<endl;
    
            }
            else{
                cout<<"Bad guess"<<endl;
                badGuessCount++;
                drawHang(0);
                            }
        
    }
    string getHanging(){
        return hanging;
    }
    int getBadGuessCount(){
        return badGuessCount;
    }
    string getRepresent(){
        return represent;
    }
    string getWord(){
        return myWord;
    }
    
                              };
class Player{
private:
    char myGuess;
    string myPrevious;
    int guessCounter;
public:
    Player(){
         myPrevious="************";
        guessCounter=0;
    }
    void makeGuess(char guess){
        myGuess=guess;
        guessCounter++;
        drawPreviousGuess(guess);
    }
    char getGuess(char guess){
        return myGuess;
    }
    void drawPreviousGuess(char guess){
        myPrevious[guessCounter-1]=guess;
    }
    bool canMakeGuess(char guess){
        bool canGuess=true;
        int index=0;
        while(myPrevious[index]!='*'){
            if(myPrevious[index]==guess){
                canGuess=false;
                
                break;
               
            }
            index++;
        }
        return canGuess;
    }
    string getPreviouGuess(){
        return myPrevious;
    }
};
class GamePLay{

public:
    static void startGame(Player& player, HangDrawer& drawer){
        char guess;
        cout<<"The word is made, now start playing!"<<endl;
        while(!(endGame(drawer))){
        cout<<"Player guess a character ";
        cin>>guess;
            while(!(player.canMakeGuess(guess))){
                cout<<"No u have guessed this before, guess again. ";
                cin>>guess;
                cout<<"Here goes nothing"<<endl;
            }
        player.makeGuess(guess);
            cout<<"The former characters are: "<<player.getPreviouGuess()<<endl;
        drawer.doHangman(guess);
        }
        
    }
    static bool endGame(HangDrawer& drawer){
            if(drawer.getRepresent()==drawer.getWord()){
                cout<<"Player wins. Successfully guessed all the words! "<<endl;
                return true;
            }
            else if(drawer.getBadGuessCount()== drawer.getHanging().length()){
                cout<<"Hangman! Player loses. You did well though."<<endl;
            return true;
            }
            else{
                return false;
            }
        }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    cout << "Hello, World!\n";
    string word="Fancy";
    HangDrawer drawer(word);
    Player player;
    //cout<<"These are the characters "<<player.getPreviouGuess()<<endl;
   // cout<<"These are the characters "<<drawer.getRepresent();
   GamePLay :: startGame(player, drawer);
    
    return 0;
}
