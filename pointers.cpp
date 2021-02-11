// compile: g++ -o pointers pointers.cpp
#include <iostream>
#include <string.h>

typedef struct Student {
    int id;
    char *f_name;
    char *l_name;
    int n_assignments;
    double *grades;
} Student;

int promptInt(std::string message, int min, int max);
double promptDouble(std::string message, double min, double max);
void calculateStudentAverage(void *object, double *avg);

int main(int argc, char **argv)
{
    Student student;
    double *average;
    //char *inputArray[128];
    
    
    
    
    
    //assigns id number
    student.id = promptInt("Please enter the student' id number: ", 0, 999999999);

    std::cout << "Please enter the student's first name: ";
    student.f_name = new char[128];
    std::cin.getline(student.f_name, 128);
    
    std::cout << "Please enter the student's last name: ";
    student.l_name = new char[128];
    std::cin.getline(student.l_name, 128);
    
    student.n_assignments = promptInt("Please enter how many assignments were graded: ", 0, 134217728);


    student.grades = new double[student.n_assignments];

    for(int i = 0; i < student.n_assignments; i++) {
        char promptString[128] = "please enter the grade for assignment ";
        char num[9] = "";
        sprintf(num, "%d", i);
        strcat(promptString, num);
        strcat(promptString, ": ");
        student.grades[i]= promptDouble(promptString, 0.0, 1000.0);
    }
    void *void_ptr = &student;
    calculateStudentAverage(void_ptr, average);
    
    std::cout << "Student: " << student.f_name << " " << student.l_name << " [" << student.id << "]\n  Average grade : " << *average << "\n";

    return 0; 
}

/*
   message: text to output as the prompt
   min: minimum value to accept as a valid int
   max: maximum value to accept as a valid int
*/
int promptInt(std::string message, int min, int max)
{
    // Code to prompt user for an int
    //checks that every character in the string is a digit
    char inputArray[128];
    bool goodToGo = false;

    while(!goodToGo) {
        goodToGo = true;
        std::cout << message;
        std::cin.getline(inputArray, 128);

        for(int i = 0; i < sizeof(inputArray); i++) {
            if(inputArray[i] == '\0') {
                break;
            }
            //std::cout << inputArray[i];
            if(!isdigit(inputArray[i])) {
                std::cout << "Sorry, I cannot understand your answer\n";
                goodToGo = false;
                break;
            }
        }
        if(goodToGo && (atoi(inputArray) < min || atoi(inputArray) > max)) {
            std::cout << "Sorry, I cannot understand your answer\n";
            goodToGo = false;
        }

    }
    return atoi(inputArray);
}

/*
   message: text to output as the prompt
   min: minimum value to accept as a valid double
   max: maximum value to accept as a valid double
*/
double promptDouble(std::string message, double min, double max)
{
    
    // Code to prompt user for a double
    char inputArray[128];
    bool goodToGo = false;
    char *ptr;
    
    while(!goodToGo) {
        goodToGo = true;
        std::cout << message;
        std::cin.getline(inputArray, 128);
        
        int numPeriods = 0;

        for(int i = 0; i < sizeof(inputArray); i++) {
            if(inputArray[i] == '\0') {
                break;
            }
            //std::cout << inputArray[i];
            if(!isdigit(inputArray[i]) && inputArray[i] != '.') {
                std::cout << "Sorry, I cannot understand your answer\n";
                goodToGo = false;
                break;
            }
            if(inputArray[i] == '.' && numPeriods == 1) {
                std::cout << "Sorry, I cannot understand your answer\n";
                goodToGo = false;
                break;
            } else if(inputArray[i] == '.' && numPeriods == 0) {
                numPeriods = 1;
            }
        }
        if(goodToGo && (strtod(inputArray, &ptr) < min || strtod(inputArray, &ptr) > max)) {
            std::cout << "Sorry, I cannot understand your answer\n";
            goodToGo = false;
        }

    }
    
    return strtod(inputArray, &ptr);
}

/*
   object: pointer to anything - your choice! (but choose something that will be helpful)
   avg: pointer to a double (can store a value here)
*/
void calculateStudentAverage(void *object, double *avg)
{
    Student *student = (Student*) object;
    double sum = 0;
    for(int i = 0; i < student->n_assignments; i++) {
        sum += student->grades[i];
    }
    sum = sum / student->n_assignments;
    *avg = sum;
    *avg = *avg * 10 + .5;
    int avgi = (int)*avg;
    *avg = avgi;
    *avg = *avg / 10;
}
