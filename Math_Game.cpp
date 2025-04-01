#include <iostream>
#include <cstdlib>
using namespace std;

enum enLevel
{
    Easy = 1,
    Medium = 2,
    Hard = 3,
    mix = 4
};

enum enOperationType
{
    Add = 1,
    Sub = 2,
    Mul = 3,
    Div = 4,
    Mix = 5
};

struct stQuestionInfo
{
    short QuestionNumber = 0;
    int Number1;
    int Number2;
    char operation;
    int CorrectAnswer;
    int UserAnswer;
};

struct stGameResults
{
    short GameQuestions = 0;
    short UserCorrectAnswer = 0;
    short UserWrongAnswer = 0;
    bool isPass;
    enLevel Level;
    enOperationType Operation;
};

int RandomNumber(int From, int To)
{
    // Function to generate a random number
    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}

int ReadAnswer()
{
    int Answer;
    cin >> Answer;
    return Answer;
}

string LevelName(enLevel level)
{
    string arrLevelName[4] = {"Easy", "Medium", "Hard", "Mix"};
    return arrLevelName[level - 1];
}

string OperationSymbool(enOperationType Op)
{
    string arrOperationSymbool[5] = {"+", "-", "*", "/", "Mix"};
    return arrOperationSymbool[Op - 1];
}

int GetNumberByLevel(enLevel level)
{
    switch (level)
    {
    case Easy:
        return RandomNumber(0, 10);
    case Medium:
        return RandomNumber(5, 20);
    case Hard:
        return RandomNumber(20, 100);
    case mix:
        return RandomNumber(0, 100);
    }
}

char GetOperation(enOperationType Op)
{
    if (enOperationType::Mix == Op)
        Op = (enOperationType)RandomNumber(1, 4);
    char arrOperationSymbool[4] = {'+', '-', '*', '/'};
    return arrOperationSymbool[Op - 1];
}

void SetScreenColor(bool isCorrect)
{
    if (isCorrect)
        system("color 2F"); // turn screen to Green
    else
    {
        system("color 4F"); // turn screen to Red
        cout << "\a";
    }
}

enOperationType ReadPlayerOperation()
{
    short Choice = 1;
    do
    {
        cout << "\nEnter Operation Type: [1]:Add, [2]:Sub, [3]:Mul, [4]:Div , [5]:Mix ? ";
        cin >> Choice;
    } while (Choice < 1 || Choice > 5);
    return (enOperationType)Choice;
}

enLevel ReadPlayerLevel()
{
    short Choice = 1;
    do
    {
        cout << "\nEnter Questions Level: [1]:Easy, [2]:Meduim, [3]:Hard, [4]:Mix ? ";
        cin >> Choice;
    } while (Choice < 1 || Choice > 4);
    return (enLevel)Choice;
}

void ShowQuestion(int N1, int N2, char Oper)
{
    cout << "\n"
         << N1 << endl;
    cout << N2 << "  " << Oper;
    cout << "\n--------------\n";
}

int Calculator(int N1, int N2, char Oper)
{
    switch (Oper)
    {
    case '+':
        return (N1 + N2);
    case '-':
        return (N1 - N2);
    case '*':
        return (N1 * N2);
    case '/':
        return (N1 / N2);
    default:
        return 0;
    }
}

void PlayGame(short HowManyQuestions, stGameResults &GameResults)
{
    stQuestionInfo QuestionInfo;
    short UserCorrectAnswer = 0;
    GameResults.Level = ReadPlayerLevel();
    GameResults.Operation = ReadPlayerOperation();
    for (short GameRound = 1; GameRound <= HowManyQuestions; GameRound++)
    {
        cout << "\nQuestion [" << GameRound << "/" << HowManyQuestions << "]\n";
        QuestionInfo.QuestionNumber = GameRound;
        QuestionInfo.Number1 = GetNumberByLevel(GameResults.Level);
        QuestionInfo.Number2 = GetNumberByLevel(GameResults.Level);
        QuestionInfo.operation = GetOperation(GameResults.Operation);

        ShowQuestion(QuestionInfo.Number1, QuestionInfo.Number2, QuestionInfo.operation);
        QuestionInfo.CorrectAnswer = Calculator(QuestionInfo.Number1, QuestionInfo.Number2, QuestionInfo.operation);
        QuestionInfo.UserAnswer = ReadAnswer();

        bool IsCorrect = false;
        if (QuestionInfo.CorrectAnswer == QuestionInfo.UserAnswer)
        {
            UserCorrectAnswer++;
            IsCorrect = true;
            cout << "Right Answer :)" << endl;
        }
        else
        {
            cout << "Wrong Answer :(" << endl;
            cout << "The correct answer is: " << QuestionInfo.CorrectAnswer << endl;
        }
        SetScreenColor(IsCorrect);
    }
    GameResults.GameQuestions = HowManyQuestions;
    GameResults.UserCorrectAnswer = UserCorrectAnswer;
    GameResults.UserWrongAnswer = HowManyQuestions - UserCorrectAnswer;

    if (GameResults.UserCorrectAnswer > GameResults.UserWrongAnswer)
        GameResults.isPass = true;
    else
        GameResults.isPass = false;
}

string Tabs(short NumberOfTabs)
{
    string t = "";
    for (int i = 1; i < NumberOfTabs; i++)
    {
        t = t + "\t";
        cout << t;
    }
    return t;
}

void ShowFinalGameResults(stGameResults GameResults)
{
    if (GameResults.isPass)
        cout << Tabs(2) << "_____________________ [Your Pass]_____________________\n\n";
    else
        cout << Tabs(2) << "_____________________ [Your Fail]_____________________\n\n";
    cout << Tabs(2) << "Number of Questions : " << GameResults.GameQuestions << endl;
    cout << Tabs(2) << "Questions Level     : " << LevelName(GameResults.Level) << endl;
    cout << Tabs(2) << "Operation Type      : " << OperationSymbool(GameResults.Operation) << endl;
    cout << Tabs(2) << "User Correct Answer : " << GameResults.UserCorrectAnswer << endl;
    cout << Tabs(2) << "User Wrong Answer   : " << GameResults.UserWrongAnswer << endl;
    cout << Tabs(2) << "___________________________________________________________\n";
}

short ReadHowManyQuestions()
{
    short GameQuestions = 1;
    do
    {
        cout << "How Many Question do you want to answer ? ";
        cin >> GameQuestions;
    } while (GameQuestions < 1 || GameQuestions > 10);
    return GameQuestions;
}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

void StartGame()
{
    char PlayAgain = 'Y';
    do
    {
        ResetScreen();
        stGameResults GameResults;
        PlayGame(ReadHowManyQuestions(), GameResults);
        ShowFinalGameResults(GameResults);
        cout << "\n"
             << Tabs(3) << "Do you want to play again? Y/N? ";
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    // Seeds the random number generator in C++, called only once
    srand((unsigned)time(NULL));

    StartGame();
    return 0;
}