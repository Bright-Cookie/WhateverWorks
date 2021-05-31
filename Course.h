//
//  Course.h
//  StudentScheduler
//
//  Created by Pham Lightning on 4/19/21.
//

#ifndef Course_h
#define Course_h
#include "Student.h"
#include <vector>

using namespace std;

class Course{
    string name;
    int maxCap;
    vector<Student*>  roster;
    Course(string n, int cap){
        name = n;
        maxCap= cap;
    
    }
    string getName(){
        return name;
    }
    int getMaxCap(){
        return maxCap;
    }
    vector<Student*> getRoster(){
        return roster;
    }
    void addStudent(Student& student){
        if(roster.size()<maxCap){
        roster.push_back(student);
        }
        else{
            cout<<"Course is full"<<endl;
        }
        
    }
    bool containStudent(Student* student){
      
        for(int i=0;i<roster.size();i++){
            if(roster.at(i)==student){
                return true;
            }
        }
        return false;
    }
    int getStudentIndex(Student* student){
        for(int i=0;i<roster.size();i++){
            if(roster.at(i)==student){
                return i;
            }
        }
        return 0;
    }
    void dropStudent(string name){
        if(roster.size()>0){
            bool hasRemoved=false;
            for(int i=0;i<roster.size();i++){
                if(roster.at(i).getName()== name){
                    roster.erase(roster.begin()+i);
                    hasRemoved=true;
                    break;
                }
            }
            if(hasRemoved==false){
                cout<<"Throw something"<<endl;;
            }
        
        }
        else{
            cout<<"There is no student currently enrolling this course"<<endl;
        }
    }
    bool isFull(){
        return roster.size()==maxCap;
    }
   
    
};

#endif /* Course_h */
