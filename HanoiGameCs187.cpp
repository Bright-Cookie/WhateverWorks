//
//  main.cpp
//  HanoiGame
//
//  Created by Pham Lightning on 4/17/21.
//

#include <iostream>
using namespace std;

class StackArray{
public:
    int loading;
    int nextIndex;
    int *arr;
    StackArray(){
        loading=3;
        arr=new int[3];
        nextIndex=0;
    }
    StackArray(int cap){
        arr=new int[cap];
        nextIndex=0;
    }
    int size(){
        return nextIndex;
    }
    void push(int number){
        if(nextIndex==loading){
            return;
        }
        arr[nextIndex]=number;
        nextIndex++;
    }
    void pop(){
        if(nextIndex<=0){
            return;
        }
        else{
        nextIndex--;
        }
    }
    bool isEmpty(){
        if(nextIndex==0){
            return true;
        }
        else{
            return false;
        }
    }
    int peek(){
        return arr[nextIndex-1];
    }
    void printStack(){
        if(isEmpty()){
            cout<<" "<<endl;
            return;
        }
        for(int i=0;i<nextIndex;i++){
            cout<<arr[i]<<" ";
        }
        cout<<endl;
    }
    
};
class Move{
public:
    int fromPeg;
    int toPeg;
    Move(int f, int t){
        fromPeg=f;
        toPeg=t;
    }
    void setFrom(int f){
        fromPeg=f;
    }
    void setTo(int t){
        toPeg=t;
    }
    int getFrom(){
        return fromPeg;
    }
    int getTo(){
        return toPeg;
    }
   
};
class HanoiBoard{
public:
    StackArray peg1;
    StackArray peg2;
    StackArray peg3;
    StackArray board[3]={peg1, peg2 , peg3};
    int winPeg=3;
    
    void setRings(int pegChoice){
        for(int i=3;i>0;i--){
            board[pegChoice -1].push(i);
                                 }
    }
    void moveRing(int fromPeg, int toPeg){//Assuming the player know what to move from
        int disk=board[fromPeg-1].peek();
        board[toPeg-1].push(disk);
        board[fromPeg-1].pop();
    }
    bool hasWon(){
        if(board[winPeg-1].size()==3){
            return true;
        }
        return false;
    }
    void printBoard(){
     
            for(int j=0;j<3;j++){
                board[j].printStack();
            }
       cout<<endl;
        }
};


    
int main(int argc, const char * argv[]) {
    // insert code here...
    HanoiBoard hanoi;
    hanoi.setRings(2);
    Move move(0,0);
    int f;
    int t;
    hanoi.printBoard();
    while(!hanoi.hasWon()){
    cout<<"Type in the peg to move from"<<endl;
    cin>>f;
    move.setFrom(f);
    cout<<"Type in the peg to move to"<<endl;

        cin>>t;
    move.setTo(t);
    hanoi.moveRing(move.getFrom(), move.getTo());
        hanoi.printBoard();
    }
    
    return 0;
}
