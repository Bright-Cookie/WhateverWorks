//
//  main.cpp
//  StudentScheduler
//
//  Created by Pham Lightning on 4/19/21.
//

#include <iostream>
#include "Course.h"
#include "Student.h"
#include <vector>

using namespace std;
/*
class Scheduler{
    vector<Student> studentList;
    vector<Course> courseList;
    
    void addStudent(Student *student){
        studentList.push_back(student);
    }
    void addCourse(Course *course){
        courseList.push_back(course);
    }
    void drop(Student *student, Course *course){
        student.dropSchedule(course.getName());
        course.dropStudent(student);
 
    }
 bool isValidCourse(Course* course){
 for(int i=0;i<courseList.size();i++){
 if(courseList[i]==course){
 return true;
 }
 }
 return false;
 }
    void assignAll(){
 bool hasChanged==true;
 int times;// the largest student number of courses in schedule
        while(hasChanged==true){
       times=0;
 hasChanged==false;
 for(int j=0;j<studentList.size();j++){
   vector<Course*> myList=studentList.at(i)->getPreferences();//This is one method
 for(int i=times;i<myList.size();i++){
 Student* student =studentList.at(j);
 Course* myCourse=student->getPreference.at(i);//One other method
 if(isValidCourse(myList[i]) && !student->isDone()){
 if(!myList[i]->isFull() &&
 !student->alreadyInSchedule(myList[i]->getName())
 studentList.at(j)->addSchedule(myList.at(i));
 myList.at(i)->addStudent(studentList.at(j));
 haschanged=true;
 break;
 }
    }
 }
 }
 times++;
 }
 }

 void unEnroll(Student* student){
        for(int i=0;i<courseList.size();i++){
 if(courseList.at(i).containStudent(student)){
              courselIst.at(i).erase(cousreList.begin()+ courseList.at(i).getStudentIndex(student));
                
            }
        }
 studentList.at(i).dropAll();
    }
    
};
*/
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    int  num1=1;
    int  num2=2;
     int num3=3;
    int &a=num1;
    int &b=num2;
    int &c=num3;
    
    vector<int&> list1{a,b,c};
    cout<< list1.at(list1.begin()+0)
    return 0;
}
