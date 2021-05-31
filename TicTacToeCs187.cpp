//
//  main.cpp
//  TicTacToe
//
//  Created by Pham Lightning on 2/20/21.
//

#include <iostream>
using namespace std;
class TicTacToe{
private:
    char **ttBoard;
    int boardSize;
    bool play= true;
    int count=0;
public :
  
    TicTacToe(int row, int column, int size)
    {
        ttBoard= new char*[row];
        for(int i=0;i<row;i++)
        {
            ttBoard[i]=new char[column];
        }
        
        for(int i=0;i<row;i++){
            for(int j=0;j<column; j++){
                ttBoard[i][j]=' ';
            }
        }
        boardSize= size;
    }
    void fillBoardatPosition(char fill,int row, int column)
    {
        ttBoard[row][column]=fill;
        checkWin(fill, row, column);
    }
    void checkWinRow(char fill, int row){
        if(play==true)
        {
        for( count=0; count<boardSize; count++)
            {
             if(ttBoard[row][count]!=fill)
              {
                break;
              }
            }
        if(count== boardSize)
         {
            cout<<"Win Row!";
            play=false;
         }
        }
    }
    void checkWinColumn(char fill,int column){
        if(play==true  )
        {
            for( count= 0; count <boardSize; count++)
           {
               
                if(ttBoard[count][column]!=fill){
                    break;
                }
             
            }
            
            if(count ==boardSize)
            {
                play=false;
                cout<<"Win Column!";
            }
        }
        }
    void checkWinLinearDown(char fill, int column, int row){
        if((row==column) && (play==true))
        {
            for( count= 0; count<boardSize; count ++){
                if(ttBoard[count][count]!=fill){
                    break;
                }
            }
            
            if(count==boardSize){
                play=false;
                cout<<"Win LinearDown!";
            }
            
        }
    }
    void checkWinLinearUp1(char fill){
        
        int cCounter=boardSize-1, rCounter=0;
        for( count=0;count<boardSize;count++){
            if(ttBoard[cCounter][rCounter]!=fill){
                break;
            }
            cCounter--;
            rCounter++;
        }
        if(count==boardSize){
            cout<<"Win LinearUP!";
            play=false;
        }
    }
    void checkWinLinearUp(char fill, int column, int row){
        if(play==true)
        {
        int cCounter1=boardSize, rCounter2=0;
        for(count=0;count<boardSize;count++){
            if(row==cCounter1 && column==rCounter2){
                checkWinLinearUp1(fill);
                break;
            }
               
            cCounter1--;
            rCounter2++;
        }
        }
    }
    
    void checkWin(char fill, int row, int column){
        //check to see if the move made by player will make game win, if so then play =false.
        checkWinRow(fill, row);
        checkWinColumn(fill, column);
        checkWinLinearUp(fill, column, row);
        checkWinLinearDown(fill, column, row);
        
        
    }
    bool getPlay(){
        return play;
    }
    void printBoard( )
    {
        count=0;
        for(int i=0; i<boardSize; i++){
            for(int j=0; j<boardSize;j++){
                cout<<ttBoard[i][j]<<" ";
                if (ttBoard[i][j] !=' '){
                    count++;
                }
            }
            if(count==boardSize*boardSize){
                play=false;
            }
            cout<<endl;
        }
        
    }

    void printBoardRecursiveColumn(int row, int column){
        if(column<boardSize){
        cout<<ttBoard[row][column]<<" ";
        printBoardRecursiveColumn(row,column+1);
        }
    }
    void printBoardRecursiveRow(int row, int column){
        if(row<boardSize){
            printBoardRecursiveColumn(row,column);
            cout<<endl;
            printBoardRecursiveRow(row+1,column);
        }
    }
    char getSquareAt(int row, int column){
        return ttBoard[row][column];
    }
    int getBoardSize(){
        return boardSize;
    }
    int getCount(){
        return count;
    }
    
    
};
class Player{
private:
    string name;
    int point;
    char fill;
   
public:
    Player(string n, char f){
        name=n;
        point=0;
        fill= f;
    }
    void makeMove(TicTacToe &tt, int row, int column){
        tt.fillBoardatPosition(fill, row, column);
        if(tt.getPlay()==false){
            cout<<name<<" wins. Add 1 point to " <<name<<"."<<endl;
            addPoint();
        }
    }
    
    bool canMakeMove(TicTacToe &tt, int row, int column){
        if(tt.getSquareAt(row, column)!=' '){
            return false;
        }
        else{
            return true;
        }
    }
    void addPoint(){
        point++;
    }
    string getName(){
        return name;
    }
    int getPoint(){
        return point;
    }
    int getSquareFilledonBoard(TicTacToe &tt,int row,int column){
        return tt.getSquareAt(row, column);
    }
    int getFill(){
        return fill;
    }
    
    
};
class AiPlayer{// This comp player will not try to win but prevent player from winning and fill row by row if avalaible
private:
    string name;
    char fill;
    int point=0;
    //int *possibleMove;
    bool hasMoved=false;
    //bool almostWin=false;
    int count=0;
public:
    AiPlayer(string n, char f){
        name=n;
        fill=f;
    }
    void doMove(TicTacToe &tt, int row, int column){
        tt.fillBoardatPosition(fill, row, column);
        if(tt.getPlay()==false){
            cout<<name<<" wins. Add 1 point to " <<name<<"."<<endl;
            addPoint();
        }
    }
    void makeMove(TicTacToe &tt, Player &player, int row, int column){
       
        checkPlayerAlmostWin(tt, player, row, column);
        doPossibleMoveBoard(0, 0, tt.getBoardSize()-1, tt);
        hasMoved=false;// reset hasMoved
    }
    void doPossibleMoveRow(int row,int firstCo, int lastCo, TicTacToe &tt){
        if(firstCo<=lastCo && hasMoved ==false){//How about do possible column as well
          int middle=(firstCo+lastCo)/2;
            if(tt.getSquareAt(row, middle)==' '){
                doMove(tt, row, middle);

                
                hasMoved=true;
            }
            doPossibleMoveRow(row, firstCo, middle-1, tt);
            doPossibleMoveRow(row, middle+1,lastCo,tt);
        }
    }
    void doPossibleMoveBoard(int row,int firstCo, int lastCo, TicTacToe &tt){
        
        if(row<tt.getBoardSize() && hasMoved==false){
        doPossibleMoveRow(row,firstCo,lastCo, tt);
        doPossibleMoveBoard(row+1, firstCo, lastCo, tt);
        }
       
    }
    
    void checkAlmostWinRow(TicTacToe &tt,Player &player, int row){
        int columnToFill=-1;;
        if(hasMoved==false)
        {
            
        for( int i=0; i<tt.getBoardSize(); i++)
            {
        if(tt.getSquareAt(row, i)==player.getFill())
        {
            count++;
        }
  else if(tt.getSquareAt(row, i)==' ')
        {
            columnToFill=i;
              }
            }
        }
        if(count==tt.getBoardSize()-1 && columnToFill!=-1)//tt.getBoardSize-1
         {
             cout<<"No, ur not winning this row!"<<endl;
             //count=0;
             hasMoved=true;
             doMove(tt, row, columnToFill);
            
         }
        count=0;
        }
    
  
    void checkAlmostWinColumn(TicTacToe &tt,Player &player, int column){
        int rowToFill=-1;
        if(hasMoved==false)
        {
         
        for( int i=0; i<tt.getBoardSize(); i++)
            {
        if(tt.getSquareAt(i, column)==player.getFill())
              {
                 
                  count++;
              }
        else if(tt.getSquareAt(i, column)==' ')
              {
                 rowToFill=i;
              }
            }
        
        if(count==tt.getBoardSize()-1 && rowToFill!=-1)//tt.getBoardSize-1
         {
             cout<<"No, ur not winning this column!"<<endl;
             //count=0;
             hasMoved=true;
             doMove(tt, rowToFill, column);
             
         }
        count=0;
        }
        }
        
    void checkAlmostWinLinearDown(TicTacToe tt,Player &player, int row, int column){
        int toFill=-1;
        if(row==column && hasMoved==false)
        {
            for( int i= 0; i<tt.getBoardSize(); i ++){
                if(tt.getSquareAt(i, i)==player.getFill()){
                    count++;
                }
                else if(tt.getSquareAt(i, i)==' '){
                    toFill=i;
                }
            }
            
            if(count==tt.getBoardSize()-1 && toFill!=-1){
                
                cout<<"You are not winning linear down!"<<endl;
               // count=0;
                doMove(tt, toFill, toFill);
                hasMoved=true;
                
            }
            count=0;
        }
    }
    void checkAlmostWinLinearUp1(Player &player, TicTacToe &tt){
        int rowtoFill=-1, columntoFill=-1;
        int cCounter=tt.getBoardSize()-1, rCounter=0;
        for( int i=0;i<tt.getBoardSize();i++){
            if(tt.getSquareAt(cCounter,rCounter)==player.getFill()){
                count++;
            }
            else if(tt.getSquareAt(cCounter,rCounter)==' '){
                rowtoFill=cCounter;
                columntoFill=rCounter;
            }
            cCounter--;
            rCounter++;
        }
        if(count==tt.getBoardSize()-1 && rowtoFill!=-1){
            cout<<"You are not winning this linear up"<<endl;
            doMove(tt, rowtoFill, columntoFill);
            hasMoved=true;
           // count=0;
        }
        count=0;
    }
    void checkAlmostWinLinearUp(TicTacToe &tt, Player& player, int row, int column){
        if(hasMoved==false)
        {
        int cCounter1=tt.getBoardSize()-1, rCounter2=0;

            for(int i=0;i<tt.getBoardSize();i++){
            if(row==cCounter1 && column==rCounter2){
                checkAlmostWinLinearUp1( player, tt);
                break;
            }
            cCounter1--;
            rCounter2++;
        }
        }
    }
    
    void checkPlayerAlmostWin(TicTacToe &tt,Player& player, int row, int column){
        //check to see row is all the same value, if so then play =false
        checkAlmostWinRow(tt,player, row);
        checkAlmostWinColumn(tt, player, column);
        checkAlmostWinLinearUp(tt, player, row, column);
        checkAlmostWinLinearDown(tt, player, row, column);
        
        
    }
    void addPoint(){
        point++;
    }
    int getPoint(){
        return point;
    }
    string getName(){
        return name;
    }
};
void determineResult(TicTacToe &tt, Player xPlayer, Player oPlayer){
    if(xPlayer.getPoint()>oPlayer.getPoint()){
        cout<<"Congrats "<<xPlayer.getName()<<" you win!";
    }
    else if(xPlayer.getPoint()<oPlayer.getPoint()){
        cout<<"Congrats "<<oPlayer.getName()<<" you win!";
    }
    else{
        cout<<"It is a draw.";
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    TicTacToe tiktak(5,5,5);
    Player xPlayer("0", 'o');//
    AiPlayer oPlayer("X",'x');
    string xName=xPlayer.getName();
    string oName=oPlayer.getName();
    
    int row=0, column=1;
    while(tiktak.getPlay()==true && tiktak.getCount()<=16)
     {
     
         
         
         cout<<"The computer makes move"<<endl;
         oPlayer.makeMove(tiktak, xPlayer, row, column);
         //tiktak.printBoard();
         tiktak.printBoard();
         if(tiktak.getPlay()==false){
             break;
         }
         cout<<xName<<", Type in the square row and column you want to fill x in "<<endl;
         cin>> row>>column;
             while(!xPlayer.canMakeMove(tiktak,row,column)){
                 cout<<"That position is already fill! Please select another!"<<endl;
                 cin>>row>>column;
             }
         xPlayer.makeMove(tiktak, row, column);
            // tiktak.printBoard();
             tiktak.printBoard();
            
     }
    cout<<endl;
    return 0;
}

/*
 for(int i=0;i<3;i++)
 {
while(tiktak.getPlay()==true)
 {
 cout<<xName<<", Type in the square row and column you want to fill x in "<<endl;
 cin>>row>>column;
     while(!xPlayer.canMakeMove(tiktak,row,column)){
         cout<<"That position is already fill! Please select another!"<<endl;
         cin>>row>>column;
     }
 xPlayer.makeMove(tiktak, row, column);
    // tiktak.printBoard();
     tiktak.printBoardRecursiveRow(0, 0);
     if(tiktak.getPlay()==false){
         break;
     }
     
     
 cout<<oName<<", Type in the square row and column you want to fill o in "<<endl;
 cin>>row>>column;
     while(!oPlayer.canMakeMove(tiktak,row,column)){
         cout<<"That position is already fill! Please select another!"<<endl;
         cin>>row>>column;
     }
 oPlayer.makeMove(tiktak, row, column);
     //tiktak.printBoard();
     tiktak.printBoardRecursiveRow(0, 0);
 }
 }
*/
 
