//
//  Student.h
//  StudentScheduler
//
//  Created by Pham Lightning on 4/19/21.
//

#ifndef Student_h
#define Student_h

#include <vector>
#include "Course.h"

using namespace std;
class Student{
private:
    string name;
    int maxCourse;
    vector<Course*> preferences;
    vector<Course*> schedule;
public:
    Student(string n, int m){// maxCourse >1, preferences must be larger than
        name = n;
        maxCourse=m;
    }
    void setSchedule(vector<Course*> s){
        schedule =s;
    }
    vector<Course*> getPreferences(){
        return preferences;
    }
    vector<Course*> getSchedule(){
        return schedule;
    }
    void addSchedule(Course* course){
        if(schedule.size()<maxCourse){
            schedule.push_back(course);
        }
        else{
            cout<<"Schedule is full"<<endl;
        }
    }
    bool isDone(){
        return schedule.size()==maxCourse;
    }
    bool alreadyInSchedule(string courseName){
        for(int i=0;i<schedule.size();i++){
            if(schedule.getName()==courseName){
                return true;
            }
        }
        return false;
    }
    void dropSchedule(string name){
        if(schedule.size()>0){
            bool hasErased=false;
            for(int i=0;i<schedule.size();i++){
                if(schedule.at(i).getName()==name){
                    schedule.erase(schedule.begin()+i);
                    hasErased=true;
                    break;
                }
            }
          
        }
        else{
            cout<<"There is nothing in schedule"<<endl;
        }
    }
    void dropAll(){
        for(int i=schedule.size()-1;i>=0;i--){
            schedule.erase(schedule.begin()+i);
        }
    }
    string getName(){
        return name;
    }
    
    
};

#endif /* Student_h */
