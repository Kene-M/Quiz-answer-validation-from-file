// This program will derive a student's answers and the correct answers on a quiz from a file,
// store them in arrays, compare them, and determine if the student passed the quiz or not.

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

    // Function for reading the student/correct answers from a file.
int readAnswers(char[], string, int);

    // Function that displays questions that the student answered incorrectly, the number, and their grades.
void displayResults(char[], char[], int, int);

    // Main function.
int main()
{
        // Declare constants.
    const int SIZE = 30;  // To hold the maximum number of students in the class.

        // Declare variables.
    char stuAnswers[SIZE];  // Array that stores the student's answers.
    char corrAnswers[SIZE];  // Array that stores the correct answers.
    int numStuAns = 0;  // To hold the number of answers provided by the student.
    int numCorrAns = 0;  // To hold the number of answers to quiz questions.
    string stuFileName;  // To hold the name of the file that stores the student's answers.
    string ansFileName;  // To hold the name of the file that stores the correct answers.

        // Ask the user to enter the name of the student's answers file.
    cout << "Enter student answers file name";
    cin >> stuFileName;
    cout << endl;

        // Call the function for reading the student's answers from a file.
    numStuAns = readAnswers(stuAnswers, stuFileName, SIZE);

        // If the file does not open, display error message to the user and quit the program.
    if (numStuAns == -1)
    {
        cout << "File \"" << stuFileName << "\" could not be opened" << endl;
        exit(0);
    }

        // Ask the user to enter the name of the file that contains the correct answers to the quiz.
    cout << "Enter correct answer file name";
    cin >> ansFileName;
    cout << endl;

        // Call the function for reading the correct answers from a file.
    numCorrAns = readAnswers(corrAnswers, ansFileName,SIZE);

        // If the file does not open, display error message to the user and quit the program.
    if (numCorrAns == -1)
    {
        cout << "File \"" << ansFileName << "\" could not be opened" << endl;
        exit(0);
    }

        // If the number of the student's answers and the correct answers are not equal display error message and quit the program.
    if (numStuAns != numCorrAns)
    {
        cout << "The student answers file has " << numStuAns << " entries and the correct answers file has " << numCorrAns <<" entries" << endl
             << "Grading cannot be done if they are not the same" << endl;

        exit(0);
    }

        // If there are no provided student/correct answers, display an error message to the user and quit the program.
    else if ((numStuAns == 0) && (numCorrAns == 0))
    {
        cout << "The number of student answers and correct answers are both " << numStuAns << endl
             << "No grade can be calculated" << endl;

        exit(0);
    }

        // Call the function that displays questions that the student answered incorrectly, the number, and their grades.
    displayResults(stuAnswers, corrAnswers, numStuAns, numCorrAns);

    return 0;
}

    // Function for reading the student/correct answers from a file.
int readAnswers(char answersArr[], string FileName, int SIZE)
{
        // Declare variables.
    ifstream inputFile;  // To hold the input file object.
    int count;  // Array subscript / counter variable.

        // Open the input file.
    inputFile.open(FileName);

        // If the file does not open return to the calling function.
    if (inputFile.fail())
        return -1;

        // Store the contents of the file into the it;'s array, and keep track of the number of answers.
    for ( count = 0; (count < SIZE) && (inputFile >> answersArr[count]); count++ );

        // Close the input file.
    inputFile.close();

        // Return the number of answers contained in the file to the calling function.
    return count;
}

    // Function that displays questions that the student answered incorrectly, the number, and their grades.
void displayResults(char stuAnswers[], char corrAnswers[], int numStuAns, int numCorrAns)
{
        // Declare variables.
    int numInCorrAns = 0;  // To hold total number of questions answered incorrectly by the student.
    double correctAnsPer;// To hold the percentage of the questions answered correctly.
    int count;  // Array subscript / counter variable.

        // Access each array element.
    for (count = 0; count < numStuAns; count++)
    {
            // Check if the student answer is incorrect.
        if (stuAnswers[count] != corrAnswers[count])
        {
                // Update the total number of questions answered incorrectly by the student.
            numInCorrAns++;

                // Display what question the student failed, their answer, and the correct answer.
            cout << "Question " << count + 1 << " has incorrect answer '" << stuAnswers[count]
                 << "', the correct answer is '" << corrAnswers[count] << "'" << endl;
        }
    }

        // Calculate the percentage of the questions answered correctly (grade).
    correctAnsPer = (static_cast<double>(numCorrAns - numInCorrAns) / numStuAns) * 100.0;

        // Display the results to the user.
    cout << numInCorrAns << " questions were missed out of " << numStuAns << endl;
    cout << "The student grade is " << setprecision(1) << fixed << showpoint << correctAnsPer << "%" << endl;

        // If the student's grade is 70% or more, inform the user that the student passed.
    if (correctAnsPer >= 70)
        cout << "The student passed" << endl;

        // If the student's grade is less than 70%, inform the user that the student failed.
    else
        cout << "The student failed" << endl;
}
