//
//  main.cpp
//  DNAASSEMBLER
//
//  Created by Pham Lightning on 3/30/21.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;
class Fragment{
private:
    string sequence;
public:
    Fragment(string s){
        sequence=s;
    }
    string getSequence(){
        return sequence;
    }
  

int checkOverlap(Fragment fragment){
   
    int index=0;
    string sequence2=fragment.getSequence();
    int iterator=sequence.length();
    
    if(sequence.length()> sequence2.length()){
        index=sequence.length()-sequence2.length();
        iterator=sequence2.length();
    }
        while(iterator>=1){
            if(
              sequence.substr(index,iterator)==sequence2.substr(0,iterator) ){
              //  cout<<fragment[f1Index].substr(index,iterator)<<endl;
             //   cout<<fragment[f2Index].substr(0,iterator)<<endl;
                
                return iterator;
            }
            iterator--;
            index++;
        }
    return 0;
}
string mergeWith(Fragment fragment){
        int toLeftOut=checkOverlap(fragment);
        string str1=sequence;
        string str2=fragment.getSequence();
    cout<<str1<<endl;
    cout<<str2<<endl;
        str1+=str2.substr(toLeftOut,str2.length()-toLeftOut);
      
       
        return str1;
    }

};
class Node{
public:
    Fragment *fragment;
    Node* next;
    Node(Fragment *f){
        fragment=f;
        next=NULL;
    }
    void setNext(Node* n){
        next=n;
    }
    Node* getNext(){
        return next;
    }
    Fragment* getFragment(){
        return fragment;
    }
    
};

class AssemblerList{
public:
    Node* head;
    int size;
    int getSize(Node *node){
        if(node==NULL){
            return 0;
        }
        else{
            return 1+ getSize(node->next);
        }
    }
    int getSize(){
        int count=0;
        Node* current=head;
        while(current!=NULL){
            current->getNext();
            count++;
        }
        return count;
    }
    void printList(Node* node){
        cout<<node->getFragment()->getSequence();
        printList(node->next);
    }
    Node* getNodeAtPos(int n){
        if(n<1){
            return NULL;
        }
        else{
        int count=1;
        Node* current=head;
        while(count<n){
            current= current->getNext();
            count++;
        }
        return current;
        }
    }
    void addNode(Fragment* fragment){
        Node *newNode= new Node(fragment);
        if(head==NULL){
           
            head=newNode;
        }
        else{
            Node* current=head;
            while(current->getNext()!=NULL){
                current=current->getNext();
            }
            current->setNext(newNode);
            
        }
    }
    void addNodeBeforeHead(Fragment *fragment){
        Node* newNode= new Node(fragment);
        newNode->setNext(head);
        head=newNode;
    }
    void removeNodeAtPos(int n){
        int count=1;
        Node* prev=head;
        Node*current=NULL;
        if(prev->getNext()!=NULL){
         current=prev->getNext();
        }
        while(count<n-1){
            prev=prev->getNext();
            current=current->getNext();
            count++;
        }
        prev->setNext(current->getNext());
        current->setNext(NULL);
        size--;
    }
};
class Assembler{
public:
    vector<Fragment> fraglist;
    void addFragment(Fragment fragment){
        fraglist.push_back(fragment);
    }



bool hasSmalllerMerge(int n1, int n2, int o1, int o2){
    
    string s1=fraglist.at(n1).getSequence();
    string s2=fraglist.at(n2).getSequence();
    int toLeftOut=fraglist.at(n1).checkOverlap(fraglist.at(n2));
    s1+=s2.substr(toLeftOut,s2.length()-toLeftOut);
    cout<<s1<<endl;
     
    string s3=fraglist.at(o1).getSequence();
    string s4=fraglist.at(o2).getSequence();
    toLeftOut=fraglist.at(o1).checkOverlap(fraglist.at(o2));

    s3+=s4.substr(toLeftOut,s4.length()-toLeftOut);;
    cout<<s3<<endl;
    if(s1<s3){
        return true;
    }
    else{
        return false;
    }
}


void printVector(){
    for(int i=0; i < fraglist.size(); i++)
        cout << fraglist.at(i).getSequence() << ' ';
}
void setToMergeWith( int &merge, int &mergeWith,int i, int j,int &lap){
    int lap1=   fraglist.at(i).checkOverlap(fraglist.at(j));
     int lap2=  fraglist.at(j).checkOverlap(fraglist.at(i));
       int newLap=getLargerOverlap(lap1, lap2);
       if(newLap>lap){
       if(lap1<lap2){
           lap=lap2;
           merge=j;
           mergeWith=i;
       }
       else {
           lap=lap1;
           merge=i;
           mergeWith=j;
       }
       }
       else if(newLap==lap){
          
               int o1=merge,n1=i;
               int o2=mergeWith,n2=j;
               if(lap1<lap2){
                    n1=j;
                    n2=i;
               }
               if(hasSmalllerMerge(n1, n2, o1, o2)==true){
                   merge=n1;
                   mergeWith=n2;
           }
       
       }
   }
       

    void mergeFragment(int merge, int mergeWith){
     string neoSequence=   fraglist.at(merge).mergeWith(fraglist.at(mergeWith));
        Fragment neoFragment{neoSequence};
        fraglist.erase(fraglist.begin()+merge);
       if(merge>mergeWith){
       fraglist.erase(fraglist.begin()+mergeWith);
        }
        else{
            fraglist.erase(fraglist.begin()+(mergeWith-1));
        }
        printVector();
        cout<<endl;
        fraglist.insert(fraglist.begin(),neoFragment);
        printVector();
    }
    int getLargerOverlap(int lap1, int lap2){
        if(lap1<lap2){
            return lap2;
        }
        else{
            return lap1;
        }
    }
    void assembleOnce(){
        int lap=0;
        int merge=0, mergeWith=0;
        for(int i=0;i<fraglist.size()-1;i++){
            for(int j=i+1;j<fraglist.size();j++){
                setToMergeWith(merge, mergeWith, i, j, lap);
            }
        }
        mergeFragment(merge,mergeWith);
    }
    void assembleAll(){
        if(fraglist.size()>1){
            assembleOnce();
            assembleAll();
        }
    }
};
class Assembler2{
public:
    AssemblerList *list;
   


    string getMergedSequence(int i, int j){
        string s1=list->getNodeAtPos(i)->getFragment()->getSequence();
        string s2=list->getNodeAtPos(j)->getFragment()->getSequence();
        int toLeftOut=(*(list->getNodeAtPos(i)->getFragment())).checkOverlap(*(list->getNodeAtPos(j)->getFragment()));
        s1+=s2.substr(toLeftOut,s2.length()-toLeftOut);
        return s1;
    }
bool hasSmalllerMerge(int n1, int n2, int o1, int o2){
    
    string s1=getMergedSequence(n1, n2);
    cout<<s1<<endl;
     
    string s2=getMergedSequence(o1, o2);
    if(s1<s2){
        return true;
    }
    else{
        return false;
    }
}
    
void setToMergeWith( int &merge, int &mergeWith,int i, int j,int &lap){
    int lap1=   (*(list->getNodeAtPos(i)->getFragment())).checkOverlap(*(list->getNodeAtPos(j)->getFragment()));
     int lap2=  (*(list->getNodeAtPos(j)->getFragment())).checkOverlap(*(list->getNodeAtPos(i)->getFragment()));
       int newLap=getLargerOverlap(lap1, lap2);
       if(newLap>lap){
       if(lap1<lap2){
           lap=lap2;
           merge=j;
           mergeWith=i;
       }
       else {
           lap=lap1;
           merge=i;
           mergeWith=j;
       }
       }
       else if(newLap==lap){
          
               int o1=merge,n1=i;
               int o2=mergeWith,n2=j;
               if(lap1<lap2){
                    n1=j;
                    n2=i;
               }
               if(hasSmalllerMerge(n1, n2, o1, o2)==true){
                   merge=n1;
                   mergeWith=n2;
           }
       
       }
   }
       

    void mergeFragment(int merge, int mergeWith){
     string neoSequence=   (*(list->getNodeAtPos(merge)->getFragment())).mergeWith(*(list->getNodeAtPos(mergeWith)->getFragment()));
        Fragment neoFragment{neoSequence};
        Fragment *neo=&neoFragment;
        list->removeNodeAtPos(merge);
       if(merge>mergeWith){
       list->removeNodeAtPos(mergeWith);
        }
        else{
            list->removeNodeAtPos(mergeWith-1);
        }
       
        cout<<endl;
        list->addNodeBeforeHead(neo);
       
    }
    int getLargerOverlap(int lap1, int lap2){
        if(lap1<lap2){
            return lap2;
        }
        else{
            return lap1;
        }
    }
    void assembleOnce(){
        int lap=0;
        int merge=0, mergeWith=0;
        for(int i=1;i<=list->getSize()-1;i++){
            for(int j=i+1;j<=list->getSize();j++){
                setToMergeWith(merge, mergeWith, i, j, lap);
            }
        }
        mergeFragment(merge,mergeWith);
    }
    void assembleAll(){
        if(list->getSize()>1){
            assembleOnce();
            assembleAll();
        }
    }
};
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
   
    Fragment f1{"CGCAT"};
    Fragment f2{"CATGAC"};
    Fragment f3{"ACATG"};
   Fragment f4{"GACTAC"};
    Assembler assemble;
 
    assemble.addFragment(f1);
    assemble.addFragment(f2);
    assemble.addFragment(f3);
    assemble.addFragment(f4);
    cout<<endl;
    assemble.assembleAll();
  
    cout<<endl;
    assemble.printVector();
    return 0;
}
