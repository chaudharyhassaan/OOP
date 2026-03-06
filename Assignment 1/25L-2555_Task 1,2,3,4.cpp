#include <iostream>
using namespace std;

int stringLength(const char* str);
void copyString(char* dest, const char* src);
bool compareString(const char* a, const char* b);
void toLowerCase(char* str);

void inputText(char*& text);
char** tokenizeUnique(char* text, int& uniqueCount);
void printDictionary(char** dict, int count);
void deleteDictionary(char** dict, int count);

char*** createSynonyms(int wordCount);
void inputSynonyms(char*** synonyms, char** dict, int wordCount);
void deleteSynonyms(char*** synonyms, int wordCount);

void searchWords(char** dict, int dictCount);
void replaceWithSynonyms(char*** synonyms, char** dict, int dictCount);


    
int main()
{
    char* text = nullptr;
    int uniqueCount = 0;

    inputText(text);                                      // Task 1 
    char** dataDictionary = tokenizeUnique(text, uniqueCount); 
    printDictionary(dataDictionary, uniqueCount);


    char*** synonyms = createSynonyms(uniqueCount);      // Task 2
    inputSynonyms(synonyms, dataDictionary, uniqueCount);


    searchWords(dataDictionary, uniqueCount);            // Task 3

    replaceWithSynonyms(synonyms, dataDictionary, uniqueCount); // Task 4


    deleteSynonyms(synonyms, uniqueCount);
    deleteDictionary(dataDictionary, uniqueCount);
    delete[] text;

    return 0;
}


int stringLength(const char* str)
{
    int len = 0;
    while (*(str + len) != '\0')
        len++;
    return len;
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

void toLowerCase(char* str)
{
    int i = 0;
    while (*(str + i) != '\0')
    {
        if (*(str + i) >= 'A' && *(str + i) <= 'Z')
            *(str + i) += 32;
        i++;
    }
}

// TASK 1 

void inputText(char*& text)
{
    text = new char[3000];
    cout << "Task - 1 Enter 4-5 sentences (end each sentence with dot):\n";
    cin.getline(text, 3000);
    toLowerCase(text);
}

char** tokenizeUnique(char* text, int& uniqueCount)
{
    char** dictionary = nullptr;
    uniqueCount = 0;

    char temp[100];
    int i = 0,       k = 0;

    while (*(text + i) != '\0')
    {
        if (*(text + i) != ' ' && *(text + i) != '.')
        {
            *(temp + k) = *(text + i);
            k++;
        }
        else
        {
            if (k > 0)
            {
                *(temp + k) = '\0';

                bool exists = false;
                for (int j = 0; j < uniqueCount; j++)
                {
                    if (compareString(*(dictionary + j), temp))
                    {
                        exists = true;
                        break;
                    }
                }

                if (!exists)
                {
                    char** newDict = new char* [uniqueCount + 1];

                    for (int j = 0; j < uniqueCount; j++)
                        *(newDict + j) = *(dictionary + j);

                    int len = stringLength(temp);
                    *(newDict + uniqueCount) = new char[len + 1];
                    copyString(*(newDict + uniqueCount), temp);

                    delete[] dictionary;
                    dictionary = newDict;
                    uniqueCount++;
                }
                k = 0;
            }
        }
        i++;
    }
    return dictionary;
}

void printDictionary(char** dict, int count)
{
    cout << "\nData Dictionary words stored after completion of Task 1 :\n";
    for (int i = 0; i < count; i++)
        cout << *(dict + i) << endl;
}

void deleteDictionary(char** dict, int count)
{
    for (int i = 0; i < count; i++)
        delete[] * (dict + i);
    delete[] dict;
}

// TASK 2 

char*** createSynonyms(int wordCount)         
{
    char*** synonyms = new char** [wordCount];
    for (int i = 0; i < wordCount; i++)
        *(synonyms + i) = nullptr;
    return synonyms;
}

void inputSynonyms(char*** synonyms, char** dict, int wordCount)
{
    for (int i = 0; i < wordCount; i++)
    {
        char choice;
        cout << "\nDo you want synonyms for \""
            << *(dict + i) << "\"? ( 1 for yes ): ";
        cin >> choice;
        cin.ignore();

        if (choice == '1')
        {
            int count;
            cout << "\nHow many synonyms do you want to store for this word ? : ";
            cin >> count;
            cin.ignore();

            if (count > 0)
            {
                *(synonyms + i) = new char* [count + 1];

                for (int j = 0; j < count; j++)
                {
                    char temp[100];
                    cout << "\nEnter synonym " << j + 1 << " to store : ";
                    cin.getline(temp, 100);
                    toLowerCase(temp);

                    int len = stringLength(temp);
                    *(*(synonyms + i) + j) = new char[len + 1];

                    for (int k = 0; k < len; k++)
                        *(*(*(synonyms + i) + j) + k) = *(temp + k);

                    *(*(*(synonyms + i) + j) + len) = '\0';
                }

                *(*(synonyms + i) + count) = nullptr;
            }
        }
    }
}

void deleteSynonyms(char*** synonyms, int wordCount)
{
    for (int i = 0; i < wordCount; i++)
    {
        if (*(synonyms + i) != nullptr)
        {
            int j = 0;
            while (*(*(synonyms + i) + j) != nullptr)
            {
                delete[] * (*(synonyms + i) + j);
                j++;
            }
            delete[] * (synonyms + i);
        }
    }
    delete[] synonyms;
}

// TASK 3

void searchWords(char** dict, int dictCount)
{
    char* useCase1 = new char[3000];

    cout << "\nTask - 3 Enter new 3-4 sentences:\n";
    cin.getline(useCase1, 3000);
    toLowerCase(useCase1);

    char temp[100];
    int i = 0, k = 0, matchCount = 0;

    cout << "\nMatched Words for doing task 3 are :\n";

    while (*(useCase1 + i) != '\0')
    {
        if (*(useCase1 + i) != ' ' && *(useCase1 + i) != '.')
        {
            *(temp + k) = *(useCase1 + i);
            k++;
        }
        else
        {
            if (k > 0)
            {
                *(temp + k) = '\0';

                for (int j = 0; j < dictCount; j++)
                {
                    if (compareString(*(dict + j), temp))
                    {
                        cout << temp << endl;
                        matchCount++;
                        break;
                    }
                }
                k = 0;
            }
        }
        i++;
    }

    cout << "Total matched words: " << matchCount << endl;

    delete[] useCase1;
}

// TASK 4

void replaceWithSynonyms(char*** synonyms, char** dict, int dictCount)
{
    char* sentence = new char[3000];

    cout << "\nEnter sentence for synonym replacement:\n";
    cin.getline(sentence, 3000);
    toLowerCase(sentence);

    char temp[100];
    int i = 0, k = 0;

    cout << "\nAfter Replacement :\n";

    while (*(sentence + i) != '\0')
    {
        if (*(sentence + i) != ' ' && *(sentence + i) != '.')
        {
            *(temp + k) = *(sentence + i);
            k++;
        }
        else
        {
            if (k > 0)
            {
                *(temp + k) = '\0';
                bool replaced = false;

                for (int j = 0; j < dictCount; j++)
                {
                    if (compareString(*(dict + j), temp))
                    {
                        if (*(synonyms + j) != nullptr)
                        {
                            cout << *(*(synonyms + j)) << " ";
                            replaced = true;
                        }
                        break;
                    }
                }

                if (!replaced)
                    cout << temp << " ";

                k = 0;
            }
        }
        i++;
    }

    cout << endl;
    delete[] sentence;
}