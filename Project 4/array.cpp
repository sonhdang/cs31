//
//  array.cpp
//  project 4
//
//  Created by Son Dang on 11/3/18.
//  Copyright © 2018 Son Dang. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <string>

using namespace std;

int appendToAll(string a[], int n, string value)
{
    if (n < 0)                      // return -1 if n is a negative number
        return -1;
    else
    {
        for (int i = 0; i < n; i++)
            a[i] += value;
    }
    return n;
}

int lookup(const string a[], int n, string target)
{
    for (int i = 0; i < n; i++)
    {
        if (a[i] == target)
            return i;
    }
    return -1;                      // return -1 if targer is not found in the array
}

int positionOfMax(const string a[], int n)
{
    if (n <= 0)
        return -1;                  // return -1 if the array has no interesting element
    else
    {
        int max = 0;
        for (int i = 0; i < n - 1; i++)
        {
            if (a[i] > a[max])
                max = i;
        }
        return max;
    }
}

int rotateLeft(string a[], int n, int pos)
{
    if (n == 0 || pos >= n)
        return -1;      // returns -1 if the array has no interesting element or pos is greater than or equal to n
    string temp = a[pos];
    for (int i = pos; i < n - 1; i++)
        a[i] = a[i + 1];
    a[n - 1] = temp;
    return pos;
}

int countRuns(const string a[], int n)
{
    if (n < 0)
        return -1;     // returns -1 if n is negative
    else if (n == 0)
        return 0;      // returns 0 if the array has no interesting element
    int counter = 1;
    int i = 0;
    while (i < n - 1)   // stops the loop before the last element because we need to examine the element after element i
    {
        if (a[i] == a[i + 1])
            i++;
        else
        {
            counter++;
            i++;
        }
    }
    return counter;
}

int flip(string a[], int n)
{
    if (n < 0)
        return -1;      // returns -1 if n is negative
    int i = 0;
    int j = n - 1;       // last index of the array
    int middleIndex = n/2;
    while (i < middleIndex)
    {
        string temp = a[i];
        a[i] = a[j];
        a[j] = temp;
        i++;
        j--;
    }
    return n;
}

int differ(const string a1[], int n1, const string a2[], int n2)
{
    int min = 0;                //min stores the value of the lesser number of elements
    if (n1 < 0 || n2 < 0)
        return -1;              //return -1 for invalid input - either n1 or n2 is negative
    else if(n1 > n2)
        min = n2;
    else
        min = n1;
    for(int i = 0; i < min; i++)
    {
        if(a1[i] != a2[i])
            return i; //return the position where a1 is different from a2 and stops the loop
    }
    return min;
}

int subsequence(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0 || n2 > n1)
        return -1;
    else if (n2 == 0)
        return 0;
    int subPos = -1;
    int i2 = 0;
    int i1 = lookup(a1, n1, a2[i2]);
    while (i2 < n2 && i1 < n1)              //this while loop is for iterating through the whole array
    {
        subPos = i1;
        i2 = 0;
        if(a1[i1] == a2[i2])                //checks if the first element of the subsequence is equal to the current element in a1
        {
            while (i2 < n2 && i1 < n1 && a1[i1] == a2[i2])  //loop that checks the elements in the rest of the array after found the first matching element in both array
            {
                i1++;
                i2++;
            }
        }
        else
        {
            subPos = -1;                    //reset subPos when the the subsequence in a1 is not equal to a2
            i1++;
            i2 = 0;                         //reset index for a2 for the next iteration
        }
    }
    if (i2 != n2)
        return -1;                          //checks if i1 runs out of element to check before done checking with a2
    else
        return subPos;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
    if(n1 <= 0 || n2 <= 0)
        return -1;
    for(int i = 0; i < n1; i++)             //for loop iterating through a1
    {
        for(int j = 0; j < n2; j++)         //for loop iterating through a2
        {
            if (a1[i] == a2[j])             //check for quality between a1 and a2
                return i;
        }
    }
    return -1;
}

int divide(string a[], int n, string divider)
{
    if (n == 0)
        return 0;
    int i = 0;
    for(int counter = 0; counter < n; counter++)    //iterating through every character of the array
    {
        if (a[i] >= divider)         //move the string to the end of the array
        {
            rotateLeft(a, n, i);    //because the string a pushed to the end of the array, the one after get pushed to the left by one - therefore, no need to update the index
        }
        else
            i++;                    //skip if the string is less than or equal to the divider
    }
    int j;
    for(j = 0; j < n; j++)
    {
        if(a[j] >= divider)          //finding the position of the divider
            break;
    }
    return j;
}

void printString(string a[], int size) //tests function
{
    for (int i = 0; i < size - 1; i++)
        cerr << a[i] << ", ";
    cerr << a[size - 1] << endl;
}

int main(int argc, const char * argv[]) {
    //TEST appendToAll//
    
    //tests if it works as expected
    string people1[8] = {"John", "Kelly", "Son", "Juliano", "Eduard", "Ash", "Wes", "Richard"};
    assert(3 == appendToAll(people1, 3, " Transfer Bridge"));
    
    //tests for appending to 0 string
    string people2[8] = {"John", "Kelly", "Son", "Juliano", "Eduard", "Ash", "Wes", "Richard"};
    assert(0 == appendToAll(people2, 0, " Transfer Bridge"));
    
    //tests for negative n
    string people3[8] = {"John", "Kelly", "Son", "Juliano", "Eduard", "Ash", "Wes", "Richard"};
    assert(-1 == appendToAll(people3, -4, " Transfer Bridge"));
    
    //TEST lookup//
    
    //tests for case sensitivity
    string people4[8] = {"John", "Kelly", "Son", "Juliano", "Eduard", "Ash", "Wes", "Richard"};
    assert(-1 == lookup(people4, 8, "kelly"));
    
    //tests for looking up people beyond the interested size
    string people5[8] = {"John", "Kelly", "Son", "Juliano", "Eduard", "Ash", "Wes", "Richard"};
    assert(-1 == lookup(people5, 5, "Ash"));
    
    //tests for looking up people at the beginning of the array
    string people6[8] = {"John", "Kelly", "Son", "Juliano", "Eduard", "Ash", "Wes", "Richard"};
    assert(0 == lookup(people6, 7, "John"));
    
    //tests for looking up people at the end of the interested size
    string people7[8] = {"John", "Kelly", "Son", "Juliano", "Eduard", "Ash", "Wes", "Richard"};
    assert(4 == lookup(people7, 5, "Eduard"));
    
    //TEST positionOfMax

    //tests if it works as expected
    string people8[8] = {"John", "Kelly", "Son", "Juliano", "Eduard", "Ash", "Wes", "Richard"};
    assert(6 == positionOfMax(people8, 8));
    
    //tests for when the number of string interested is 1
    string people9[8] = {"John", "Kelly", "Son", "Juliano", "Eduard", "Ash", "Wes", "Richard"};
    assert(0 == positionOfMax(people9, 1));
    
    //tests for when the number of string interested is 0
    string people10[8] = {"John", "Kelly", "Son", "Juliano", "Eduard", "Ash", "Wes", "Richard"};
    assert(-1 == positionOfMax(people10, 0));
    
    //tests for when there are two max strings
    string people11[8] = {"John", "Kelly", "Son", "Juliano", "Eduard", "Wes", "Wes", "Richard"};
    assert(5 == positionOfMax(people11, 8));
    
    //tests for when there the max string is not in the interested number of strings
    string people12[8] = {"John", "Kelly", "Son", "Juliano", "Eduard", "Ash", "Wes", "Richard"};
    assert(2 == positionOfMax(people12, 6));
    
    //TEST rorateLeft
    
    //tests if it works as expected
    string people13[8] = {"John", "Kelly", "Son", "Juliano", "Eduard", "Ash", "Wes", "Richard"};
    assert(4 == rotateLeft(people13, 8, 4));
    printString(people13, 8);
    
    //tests for when n is less than the size of the array
    string people14[8] = {"John", "Kelly", "Son", "Juliano", "Eduard", "Ash", "Wes", "Richard"};
    assert(3 == rotateLeft(people14, 5,3));
    printString(people14, 8);
    
    //tests for when pos is at the last position of the array
    string people15[8] = {"John", "Kelly", "Son", "Juliano", "Eduard", "Ash", "Wes", "Richard"};
    assert(5 == rotateLeft(people15, 6, 5));
    printString(people15, 8);
    
    //tests for when pos = 0
    string people16[8] = {"John", "Kelly", "Son", "Juliano", "Eduard", "Ash", "Wes", "Richard"};
    assert(0 == rotateLeft(people16, 7, 0));
    printString(people16, 8);
    
    //tests for when pos >= n
    string people17[8] = {"John", "Kelly", "Son", "Juliano", "Eduard", "Ash", "Wes", "Richard"};
    assert(-1 == rotateLeft(people17, 4, 4));
    printString(people17, 8);
    
    //tests for when there is no interesting elements in the array
    string people18[8] = {"John", "Kelly", "Son", "Juliano", "Eduard", "Ash", "Wes", "Richard"};
    assert(-1 == rotateLeft(people18, 0, 0));
    
    //TEST countRuns
    
    //tests for when the array only has 1 element
    string people19[1] = {"John"};
    assert(1 == countRuns(people19, 1));
    
    //tests for when the n = 0
    string people20[8] = {"John", "Kelly", "Son", "Juliano", "Eduard", "Ash", "Wes", "Richard"};
    assert(0 == countRuns(people20, 0));
    
    //tests for when the array has 2 elements
    string people21[2] = {"John", "John"};
    assert(1 == countRuns(people21, 1));
    
    //tests for when all the elements in the array are distinct elements
    string people22[8] = {"John", "Kelly", "Son", "Juliano", "Eduard", "Ash", "Wes", "Richard"};
    assert(8 == countRuns(people22, 8));
    
    //tests for when all the elements in the array are identical
    string people23[8] = {"Kelly", "Kelly", "Kelly", "Kelly", "Kelly", "Kelly", "Kelly", "Kelly"};
    assert(1 == countRuns(people23, 8));
    
    //TEST flip//
    
    //tests for when there is no interesting element
    string people24[0] = {};
    assert(0 == flip(people24, 0));
    
    //tests for when there is only one element in the array
    string people25[1] = {"John"};
    assert(1 == flip(people25, 1));
    printString(people25, 1);
    
    //tests for when there are two element in the array
    string people26[2] = {"John", "Kelly"};
    assert(2 == flip(people26, 2));
    printString(people26, 2);
    
    //tests for when there are odd number of elements in the array
    string people27[7] = {"John", "Kelly", "Son", "Juliano", "Eduard", "Ash", "Wes"};
    assert(7 == flip(people27, 7));
    printString(people27, 7);
    
    //tests for when there are even number of elements in the array
    string people28[8] = {"John", "Kelly", "Son", "Juliano", "Eduard", "Ash", "Wes", "Richard"};
    assert(8 == flip(people28, 8));
    printString(people28, 8);
    
    //TEST differ//
    
    //tests for when either of the array's number of string interesting element is -1
    string people29[1] = {"John"};
    string people30[1] = {"John"};
    assert (-1 == differ(people29, 1, people30, -4));
    
    //tests for when either of the array's number of string interesting element is 0
    string people31[0];
    string people32[2] = {"John", "Kelly"};
    assert(0 == differ(people31, 0, people32, 2));
    
    //tests for when the number of interesting elements of both arrays are 1
    string people37[1] = {"John"};
    string people38[1] = {"Kelly"};
    assert(0 == differ(people37, 1, people38, 1));
    
    //tests for when the number of interesting elements of both arrays are 1 and the elements are equal
    string people39[1] = {"John"};
    string people40[1] = {"John"};
    assert(1 == differ(people39, 1, people40, 1));
    
    //tests for when either of the array are equal and run out of element
    string people33[7] = {"John", "Kelly", "Son", "Juliano", "Eduard", "Ash", "Wes"};
    string people34[8] = {"John", "Kelly", "Son", "Juliano", "Eduard", "Ash", "Wes", "Richard"};
    assert (7 == differ(people33, 7, people34, 8));
    
    //tests for when the number of interesting elements of both arrays are equal
    string people35[8] = {"John", "Kelly", "Son", "Juliano", "Eduard", "Ash", "Wes", "Richard"};
    string people36[8] = {"John", "Kelly", "Son", "Juliano", "Eduard", "Ash", "Wes", "Richard"};
    assert (8 == differ(people35, 8, people36, 8));
    
    //TEST subsequence//

    //tests for when n2 is an array of 0 element
    string people47[6] = {"John", "Kelly", "Kelly", "Son", "Craig", "Ash"};
    string people48[0] = {};
    assert(0 == subsequence(people47, 6, people48, 0));
    
    //tests for when n2 is a subsequence of n1
    string people45[6] = {"John", "Craig", "Kelly", "Son", "Kelly", "Ash"};
    string people46[2] = {"Kelly", "Son"};
    assert(2 == subsequence(people45, 6, people46, 2));
    
    //tests for when no subsequence is found
    string people43[6] = {"John", "Kelly", "Kelly", "Kelly", "Craig", "Ash"};
    string people44[2] = {"Kelly", "Son"};
    assert(-1 == subsequence(people43, 6, people44, 2));
    
    //tests for when 2 identical elements are right next to each other in a1
    string people41[6] = {"John", "Kelly", "Kelly", "Son", "Craig", "Ash"};
    string people42[2] = {"Kelly", "Son"};
    assert(2 == subsequence(people41, 6, people42, 2));
    
    //tests for when there are 2 subsequences in a1
    string people49[6] = {"John", "Kelly", "Kelly", "Son", "Kelly", "Son"};
    string people50[2] = {"Kelly", "Son"};
    assert(2 == subsequence(people49, 6, people50, 2));
    
    //tests for when there is only 1 element in a2
    string people51[6] = {"John", "Kelly", "Kelly", "Son", "Son", "Craig"};
    string people52[1] = {"Son"};
    assert(3 == subsequence(people51, 6, people52, 1));
    
    //TEST lookupAny//
    
    //tests for when a1 is an empty array
    string people53[6] = {"John", "Kelly", "Son", "Craig", "Jin", "Son"};
    string people54[0];
    assert(-1 == lookupAny(people54, 0, people53, 6));
    
    //tests for when a2 is an empty array
    string people55[6] = {"John", "Kelly", "Son", "Craig", "Jin", "Son"};
    string people56[0];
    assert(-1 == lookupAny(people55, 0, people56, 6));
    
    //tests if it works as expected
    string people57[6] = {"John", "Kelly", "Son", "Craig", "Jin", "Son"};
    string people58[3] = {"Tom", "Son", "Kelly"};
    assert(1 == lookupAny(people57, 6, people58, 3));
    
    //tests if it works as expected
    string people59[6] = {"John", "John", "Son", "Craig", "Jin", "Son"};
    string people60[3] = {"Craig", "Craig", "Kelly"};
    assert(3 == lookupAny(people59, 6, people60, 3));
    
    //tests if it works as expected
    string people61[2] = {"John", "Kelly"};
    string people62[4] = {"Craig", "Son", "Jin", "Kelly"};
    assert(1 == lookupAny(people61, 2, people62, 4));
    
    //TEST divide//
    
    //tests if it works as expected
    string people63[6] = {"John", "Kelly", "Son", "Craig", "Hope", "Jin"};
    assert(2 == divide(people63, 6, "Ian"));
    printString(people63, 6);
    
    //tests for when the divider is greater than all the strings in the array
    string people64[7] = {"Kelly", "Angela", "Katlyn", "Megan", "Claudia", "Kevin", "Pauline"};
    assert(7 == divide(people64, 7, "son"));
    printString(people64, 7);
    
    //tests for when the divider is less than all the strings in the array
    string people65[7] = {"Kelly", "Angela", "Katlyn", "Megan", "Claudia", "Kevin", "Pauline"};
    assert(0 == divide(people65,7 , "AA"));
    printString(people65, 7);
    
    //tests for when the string is empty
    string people66[0] = {};
    assert(0 == divide(people66, 0, "Shawn"));
    
    //tests for when the divider is an empty string
    string people67[7] = {"Kelly", "Angela", "Katlyn", "Megan", "Claudia", "Kevin", "Pauline"};
    assert(0 == divide(people67, 7, ""));
    
    cerr << "All tests passed" << endl;
}
