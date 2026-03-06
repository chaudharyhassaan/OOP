#include <iostream>
using namespace std;

const int N = 20;
const int M = 100;


int stringLength(const char* str);
bool isAlphaNumeric(char ch);
bool compareString(const char* a, const char* b);
void copyString(char* dest, const char* src);

void extractHashtags(char tweets[][M], char**& hashtags, int& count);
bool exists(char** hashtags, int count, const char* tag);
void deleteHashtags(char** hashtags, int count);
void printHashtags(char** hashtags, int count);


int main()
{
    char Tweets[N][M] = {
        "I love programming! #coding #developer #tech",
        "Just read a great book about AI! #reading #AI #books",
        "The weather today is fantastic! #sunny #beautiful",
        "Had an amazing workout session! #fitness #health #motivation",
        "Finally, coffee time! #coffee #morning #energy",
        "Learning C programming! #coding #learning",
        "Can't wait for the weekend! #weekendvibes #excited",
        "Enjoying a relaxing day at the beach! #vacation #beach #relax",
        "New project starting today! #work #project #goals",
        "Running in the park! #fitness #nature",
        "Loving this tech conference! #tech #developer #AI",
        "Weekend vibes and relaxation time! #weekendvibes #vacation #relax",
        "Fitness goals achieved today! #fitness #health #motivation",
        "Finally got my first coffee today! #coffee #morning #energy",
        "Building a new app with C! #coding #developer",
        "Taking a walk at the beach. #beach #vacation #nature",
        "Just finished an AI course! #AI #learning #tech",
        "Work is so rewarding today! #work #project #goals",
        "A morning walk to clear my mind! #morning #fitness #nature",
        "Amazing sunny day! #sunny #beautiful #weekendvibes"
    };

    char** hashtags = nullptr;
    int count = 0;

    extractHashtags(Tweets, hashtags, count);
    printHashtags(hashtags, count);
    deleteHashtags(hashtags, count);

    return 0;
}


int stringLength(const char* str)
{
    int len = 0;
    while (*(str + len) != '\0')
        len++;
    return len;
}

bool isAlphaNumeric(char ch)
{
    if (ch >= 'a' && ch <= 'z') return true;
    if (ch >= 'A' && ch <= 'Z') return true;
    if (ch >= '0' && ch <= '9') return true;
    if (ch == '_') return true;
    return false;
}

bool compareString(const char* a, const char* b)
{
    int i = 0;
    while (*(a + i) != '\0' && *(b + i) != '\0')
    {
        if (*(a + i) != *(b + i))
            return false;
        i++;
    }
    return (*(a + i) == '\0' && *(b + i) == '\0');
}

void copyString(char* dest, const char* src)
{
    int i = 0;
    while (*(src + i) != '\0')
    {
        *(dest + i) = *(src + i);
        i++;
    }
    *(dest + i) = '\0';
}



bool exists(char** hashtags, int count, const char* tag)
{
    for (int i = 0; i < count; i++)
    {
        if (compareString(*(hashtags + i), tag))
            return true;
    }
    return false;
}

void extractHashtags(char tweets[][M], char**& hashtags, int& count)
{
    char temp[100];

    for (int i = 0; i < N; i++)
    {
        int j = 0;

        while (*(*(tweets + i) + j) != '\0')
        {
            if (*(*(tweets + i) + j) == '#')
            {
                int k = 0;
                j++;

                while (isAlphaNumeric(*(*(tweets + i) + j)))
                {
                    *(temp + k) = *(*(tweets + i) + j);
                    k++;
                    j++;
                }
                *(temp + k) = '\0';

                if (!exists(hashtags, count, temp))
                {
                    char** newArray = new char* [count + 1];

                    for (int x = 0; x < count; x++)
                        *(newArray + x) = *(hashtags + x);

                    int len = stringLength(temp);
                    *(newArray + count) = new char[len + 1];
                    copyString(*(newArray + count), temp);

                    delete[] hashtags;
                    hashtags = newArray;
                    count++;
                }
            }
            else
                j++;
        }
    }
}

void printHashtags(char** hashtags, int count)
{
    cout << "\nDistinct Hashtags:\n\n";

    for (int i = 0; i < count; i++)
        cout << *(hashtags + i) << endl;
}

void deleteHashtags(char** hashtags, int count)
{
    for (int i = 0; i < count; i++)
        delete[] * (hashtags + i);

    delete[] hashtags;
}