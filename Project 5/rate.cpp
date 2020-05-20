//
//  rate.cpp
//  Project 5
//
//  Created by Son Dang on 11/17/18.
//  Copyright © 2018 Son Dang. All rights reserved.
//

#include <iostream>
#include <cstring>
using namespace std;

const int IMPROPER_FLAG = -1;
const char LONG_WORD[] = "@";     //mark long words in documents
const int MAX_WORD_LENGTH = 20;
const int MAX_DOCUMENT_LENGTH = 250;
const int MAX_NUMBER_OF_CSTRING_IN_DOCUMENT = MAX_DOCUMENT_LENGTH / 2; //125
//max number of cstring -> least letter possible word(1 character), separated by a space -> 1 letter + 1 space = 2 characters


int makeProper(char word1[][MAX_WORD_LENGTH + 1],
               char word2[][MAX_WORD_LENGTH + 1],
               int separation[],
               int nPatterns)
{
    if (nPatterns <= 0)             //return 0 when there is no pattern to operate on
        return 0;
    else
    {
        int nProper = nPatterns;            //variable keeping track of the proper patterns of the collection
        for(int i = 0; i < nPatterns; i++)  //iterate through all the patterns
        {
            if (separation[i] < 0)          //if separation is 0 then the pattern is not proper, remove
            {
                separation[i] = IMPROPER_FLAG;  //separation becomes IMPROPER_FLAG
                nProper--;
                continue;
            }
            else if (strlen(word1[i]) == 0 || strlen(word2[i]) == 0)
            {
                separation[i] = IMPROPER_FLAG;
                nProper--;
                continue;
            }
            
            int j = 0;              //index for looping through word1
            while (word1[i][j])      //looping through word1
            {
                if(!isalpha(word1[i][j]))
                {
                    separation[i] = IMPROPER_FLAG;
                    nProper--;
                    break;
                }
                else
                {
                    tolower(word1[i][j]);
                    j++;
                }
            }
            
            if(separation[i] == IMPROPER_FLAG)   //check if word1 is proper
                continue;
            else
            {
                j = 0;                  //reset j to 0 to loop through word2;
                while(word2[i][j])
                {
                    if(!isalpha(word2[i][j]))
                    {
                        separation[i] = IMPROPER_FLAG;
                        nProper--;
                        break;
                    }
                    else
                    {
                        tolower(word1[i][j]);   //convert the letter to lowercase if the letter is alphabetic
                        j++;
                    }
                }
            }
            
            j = 0;      //reset j to iterate from the beginning of the collection to the current pattern
            while(j <= i)
            {
                if(separation[j] == IMPROPER_FLAG)  //skip improper patterns
                    j++;
                else if((strcmp(word1[i], word1[j]) == 0 && strcmp(word2[i], word2[j]) == 0) || //compare current word1(i) with existing word1(j) and compare current word2(i) with existing word2(j)
                        (strcmp(word1[i], word2[j]) == 0 && strcmp(word1[j], word2[i]) == 0))   //compare current word1(i) with existing word2(j) and compare current word2(i) with existing word1(j)
                {
                    if(separation[i] < separation[j])   //removing the one with the lesser separation
                    {
                        separation[i] = IMPROPER_FLAG;
                        nProper--;
                        j++;
                    }
                    else
                    {
                        separation[j] = IMPROPER_FLAG;
                        nProper--;
                        j++;
                    }
                }
                else
                    j++;    //leave it alone otherwise
            }
        }
        return nProper;
    }
}

int rate(const char document[],
         const char word1[][MAX_WORD_LENGTH + 1],
         const char word2[][MAX_WORD_LENGTH + 1],
         const int separation[],
         int nPatterns)
{
    if (nPatterns <= 0) //there is nothing to look for in the document so return the rating as 0
        return 0;
    else
    {
        char test[MAX_NUMBER_OF_CSTRING_IN_DOCUMENT][MAX_WORD_LENGTH + 1];  //an array of cstring's to hold all the words to compare with a collection of patterns
        int nWordInTest = 0;            //keep track of the number of words in test
        int rating = 0;                 //keep track of the rating
        int count = 0;                  //keep track of the number of characters of the current word in the document
        int i = 0;                      //index to loop through the whole document
        while (document[i])
        {
            if(document[i] == ' ')
                i++;
            else
            {
                count = 0;
                char temp[MAX_WORD_LENGTH + 1] = ""; //a temporary cstring to store the current word before being pushed to test
                while (document[i] != '\0' && document[i] != ' ')   //stops when reaches the end of the string or ' '
                {
                    if (!isalpha(document[i]) && document[i])  //if the character is not a letter -> skip
                        i++;
                    else
                    {
                        if (count < MAX_WORD_LENGTH)   //if it is a letter then push that letter to cstring temp
                        {
                            temp[count] = document[i];
                            temp[count] = tolower(temp[count]);
                            count++;
                            i++;
                        }
                        else                            //when the number of letters exceed the MAX_WORD_LENGTH then skip through until the next word in the document
                        {
                            count++;
                            i++;
                        }
                    }
                }
                if (count == 0 && document[i])
                    i++;
                else if (count > MAX_WORD_LENGTH)  //words in patterns have less than or equal to 20 characters so a word with more than 20 characters cannot be compared with a word in the patterns
                {
                    strcpy(test[nWordInTest], LONG_WORD);
                    nWordInTest++;
                    i++;
                }
                else if (count > 0 && count <= MAX_WORD_LENGTH)
                {
                    strcpy(test[nWordInTest], temp);
                    nWordInTest++;
                    i++;
                }
            }
        }
        if (nWordInTest < 2)
            return rating;
        else
        {
            for (int j = 0; j < nPatterns; j++)     //index j to iterate through all the patterns
            {
                int overhead = separation[j] + 2;
                if (overhead > nWordInTest)
                    continue;
                else
                {
                    int k = 0;
                    while(k <= nWordInTest - overhead)
                    {
                        for(int l = 1; l <= separation[j] + 1; l++)
                        {
                            if((strcmp(word1[j], test[k]) == 0 && strcmp(word2[j], test[k + l])) ||
                               (strcmp(word1[j], test[k + l]) == 0 && strcmp(word2[j], test[k])))
                            {
                                rating++;
                                k = nWordInTest - overhead;
                                break;
                            }
                        }
                        k++;
                    }
                }
            }
        }
        return rating;
    }
}
int main()
{
    const int TEST1_NRULES = 4;
    char test1w1[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
        "mad",       "deranged", "nefarious", "have"
    };
    char test1w2[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
        "scientist", "robot",    "plot",      "mad"
    };
    int test1dist[TEST1_NRULES] = {
        1,           3,          0,           12
    };
    assert(rate("The mad UCLA scientist unleashed a deranged evil giant robot.",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 2);
    assert(rate("The mad UCLA scientist unleashed    a deranged robot.",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 2);
    assert(rate("**** 2018 ****",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 0);
    assert(rate("  That plot: NEFARIOUS!",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
    assert(rate("deranged deranged robot deranged robot robot",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
    assert(rate("That scientist said two mad scientists suffer from deranged-robot fever.",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 0);
    cout << "All tests succeeded" << endl;
}
