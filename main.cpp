//
//  main.cpp
//  SimilarlityDetection
//
//

#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <sstream>

using namespace std;



//class SetUltilities{
//public:
  
      set<string> unioning(set<string> s, set<string> t){
        
         set<string> neoSet(s);
        
          set<string>:: iterator it;
          for( it=t.begin(); it!=t.end();++it){
              neoSet.emplace(*it);
                 }
               
             
           
         return neoSet;
     }
set<string> intersection(set<string> s, set<string> t){
   set<string> neoSet(s);
  
    set<string>:: iterator it;
    for( it=s.begin(); it!=s.end();++it){
        if(t.find(*it)==t.end()){
            neoSet.erase(*it);
        }
   }
   return neoSet;
}
set<string> difference(set<string> s, set<string> t){
    set<string> neoSet(s);
   
     set<string>:: iterator it;
     for( it=s.begin(); it!=s.end();++it){
         if(t.find(*it)!=t.end()){
             neoSet.erase(*it);
         }
    }
    return neoSet;
    
}
double jaccardIndex(set<string> s,set<string> t){
   if(s.empty() && t.empty()){
       return -1;
   }
   set<string> intersect=intersection(s,t);
   set<string> unitive=unioning(s,t);
   return intersect.size()/unitive.size();
}
bool isanEmptyLine(string text){
   if(text!=""){
       string sub=text.substr(1,text.size()-1);
       if(text[0]==' '&& text.size()==1){
           return true;
       }
       else if(text[0]==' '){
           return isanEmptyLine(sub);
       }
       else{
           return false;
       }
   }
   else{
       return true;
   }
}
/*
class SetUltilities{
        
    
     set<string> intersection(set<string> s, set<string> t){
        set<string> neoSet;
        for( typename set<string>::iterator it1=s.begin(); it1!=s.end();++it1){
            bool equalFound=false;
            for(typename set<string>::iterator it2=s.begin(); it2!=t.end();++it2){
                if(*it1==*it2){
                    equalFound=true;
                    break;
                }
            }
            if(equalFound){
                neoSet.insert(*it1);
            }
        }
        return neoSet;
    }
     set<string> difference(set<string> s, set<string> t){
        if(s.size()<t.size()){
        set<string> neoSet(t);
        }
       
            set<string> neoSet;
    
        for(typename set<string>::iterator it1=s.begin(); it1!=s.end();++it1){
            bool equalFound=false;
            for(typename set<string>::itertator it2=s.begin(); it2!=t.end();++it2){
                if(*it1==*it2){
                    equalFound=true;
                   
                    break;
                }
            }
            if(!equalFound){
                neoSet.insert(*it1);
            }
        }
    
        
        for( typename set<string>::iterator it1=t.begin(); it1!=t.end();++it1){
            bool equalFound=false;
            for( typename set<string>::iterator it2=s.begin(); it2!=s.end();++it2){
                if(*it1==*it2){
                    equalFound=true;
                   
                    break;
                }
            }
            if(equalFound){
                neoSet.erase(it1);
            }
        }
         return neoSet;
    }
     double jaccardIndex(set<string> s,set<string> t){
        if(s.empty() && t.empty()){
            return -1;
        }
        set<string> intersect=intersection(s,t);
        set<string> unitive=unioning(s,t);
        return intersect.size()/unitive.size();
    }
    
};
*/

class SimilarlyUltilities{
public:
     bool isEmptyLine(string text){
        string temp;
        for(int i=0;i<text.size();i++){
            temp+=" ";
        }
        if(text==temp){
            return true;
        }
        else{
            return false;
        }
    }
     bool isanEmptyLine(string text){
        if(text!=""){
            string sub=text.substr(1,text.size()-1);
            if(text[0]==' '&& text.size()==1){
                return true;
            }
            else if(text[0]==' '){
                return isanEmptyLine(sub);
            }
            else{
                return false;
            }
        }
        else{
            return true;
        }
    }
    string trim(string &s)
    {
        auto start = s.begin();
        while (start != s.end() && isspace(*start)) {
            start++;
        }
     
        auto end = s.end();
        do {
            end--;
        } while (distance(start, end) > 0 && isspace(*end));
     
        return string(start, end + 1);
    }
       set<string> trimmedLines(string text) {
          
          set <string> token;
               
             // stringstream class check1
             stringstream check1(text);
               
             string intermediate;
               
             // Tokenizing w.r.t. space ' '
             while(getline(check1, intermediate, '\n'))
             {
                 if(intermediate!="")
                     trim(intermediate);
                 token.insert(intermediate);
                 
             }
               
             // Printing the token vector
          set<string>::iterator it;
          for (it=token.begin(); it!=token.end(); ++it)
              std::cout << ' ' << *it;
          
            return token;
           
          
        }
     bool isEndWord(char a, int i){
        if(i<0){
            return true;
        }
        if((a>=32 && a<=46) ){
            return true;
        }
        return false;
    }
 
     vector<string> asLowercaseWords(string text) {
    
             
           // Vector of string to save tokens
           vector <string> tokens;
             
             
           // Printing the token vector
         int endLine=text.length()-1;
        int wordStart=0;
         while(isEndWord(text[wordStart], wordStart) && wordStart<text.length()){
             wordStart++;
         
         }
        for(int i=1;i<text.length();i++){
           
            
            
            if((isEndWord(text[i],i) && !isEndWord(text[i-1],i-1) )){
                string sub=text.substr(wordStart,i-wordStart);
                
               transform(sub.begin(), sub.end(), sub.begin(), ::tolower);
                tokens.push_back(sub);
                int check;
         
                    wordStart=i+1;
                                   check=i+1;
                 
                                   while(isEndWord(text[check], check)&& i<text.length()){
                                      wordStart++;
                                  check++;
                                
                                 }
                    
               

                
            }
           
           
        }
            return tokens;
        }

     double lineSimilarlity(string text1, string text2)
    {
        set<string> set1=trimmedLines(text1);
        set<string> set2=trimmedLines(text2);
       return jaccardIndex(set1, set2);
    }
     double lineSimilarlity(string text1, string text2, string templateText)
    {
        set<string> templateSet=trimmedLines(templateText);
        set<string> set1=trimmedLines(text1);
        set<string> neoset1= difference(set1, templateSet);
        set<string> set2=trimmedLines(text1);
        set<string> neoset2=difference(set2, templateSet);
        return  jaccardIndex(neoset1, neoset2);
    }
      set<string> shingle(vector<string> words, int shingleLength) {
         set<string> shingle;
         for(int i=0;i<=words.size()-shingleLength;i++){
             string sum="";
             for(int j=i;j<i+shingleLength;j++){
                 sum.append(words[j]);
             }
             shingle.emplace(sum);
         }
         return shingle;
        }
    void printSet(set<string> myset){
        set<string>:: iterator it;
        for( it = myset.begin(); it!=myset.end(); it++)
        
           cout << *it<< endl;
    }
    double shingleSimilarlity(string text1, string text2,string templateText, int shingleLength){
        cout<<"ss"<<endl;
        vector<string> temp=asLowercaseWords(templateText);
        cout<<"ss"<<endl;
       set<string> shingleTemplate=shingle(temp,shingleLength);
        vector<string> t1=asLowercaseWords(text1);
        set<string> shingle1=shingle(t1, shingleLength);
        printSet(shingle1);
        vector<string> t2=asLowercaseWords(text2);
        set<string> shingle2=shingle(t2, shingleLength);
        cout<<"2nd"<<endl;
        printSet(shingle1);
        set<string> neoShingle1=difference(shingle1, shingleTemplate);
        set<string> neoShingle2=difference(shingle2, shingleTemplate);
        cout<<"3rd part"<<endl;
        printSet(neoShingle1);
        printSet(neoShingle1);
        return  jaccardIndex(shingle1, shingle2);
    }
     
};


int main(int argc, const char * argv[]) {
    // insert code here...
    string text="  Hello, World!\n  Riven is for redemption.\n   No player likes playing yas";
    string myLine="Almost all of Shakespeare’s Hamlet can be understood as a play about\nacting and the theater. For example, in Act 1, Hamlet adopts a pretense of\nmadness that he uses to protect himself and prevent his antagonists from discovering\nhis mission to revenge his father’s murder. He also presents truth by means of a show when he\ncompares the portraits of Gertrude’s two husbands in order to describe for her the true\nnature of the choice she has made. And when he leaps in Ophelia’s open grave ranting in\nhigh heroic terms, Hamlet is acting out the folly of excessive, melodramatic expressions\nof grief.";
    string meLine="Almost all of Shakespeare’s Hamlet can be understood as a play about\nacting and the theater. For example, in Act 1, Hamlet adopts a pretense of\nmadness that he uses to protect himself and prevent his antagonists from discovering\nhis mission to revenge his father’s murder. He also presents truth by means of a show when he\ncompares the portraits of Gertrude’s two husbands in order to describe for her the true\nnature of the choice she has made. And when he leaps in Ophelia’s open grave ranting in\nhigh heroic terms, Hamlet is acting out the folly of excessive, melodramatic expressions\nof grief.";
    string arr[]={"i","op","iii"};
    set<string> s1={"io","poi","oooo"};
    s1.insert(arr,arr+3);
    vector <string> tokens;
    string t1="I luve u i luve.";
    string t2="I luve u i luve.";
      

    string intermediate1;

    // Tokenizing w.r.t. space ' '

    SimilarlyUltilities sm;
  //  cout<<"The jaccard index of shingle is "<<sm.shingleSimilarlity(t1, t2, "", 2);
    tokens=sm.asLowercaseWords(meLine);
    char a=text[5];
    
    set<string> s={"a","c","d"};
    set<string> t={"a","b"};
    set<string> neo;
    vector<string> myStr={"i","luve","u","i","luve"};
   // neo=difference(t,s);
    /*
    for( it = neo.begin(); it!=neo.end(); it++)
    
       cout << *it<< endl;
   */
    //set<string> myset=sm.shingle(myStr, 2);
   
    /*
    for( it = myset.begin(); it!=myset.end(); it++)
    
       cout << *it<< endl;
     */
    for(int i = 0; i<tokens.size(); i++)
    
       cout << tokens[i]<< endl;
     
    //cout<<isanEmptyLine(noLine);
    return 0;
}
