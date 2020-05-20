//
//  main.cpp
//  Project 3
//
//  Created by Son Dang on 10/28/18.
//  Copyright © 2018 Son Dang. All rights reserved.
//

#include <iostream>
#include <cassert>
using namespace std;
//*************************************
//  isValidUppercaseStateCode
//*************************************

// Return true if the argument is a two-uppercase-letter state code, or
// false otherwise.

bool isValidUppercaseStateCode(string stateCode)
{
    const string codes =
    "AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
    "LA.ME.MD.MA.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC.ND."
    "OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2  &&
            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(stateCode) != string::npos);  // match found
}

//*************************************
//  isValidPartyResults
//*************************************

// Return true if the argument is a sequence of party results
// false otherwise.

bool isValidPartyResults(string partyResult)
{
    if (partyResult.size() < 2)                 // if party result is less than 2 characters
        return false;                           // because a party result needs at least 2 characters
    int i = 0;
    while (i < partyResult.size())              // checks if index i has reached the end of the string
    {
        if (isdigit(partyResult[i]))            // checks for the first digit
        {
            i++;
            if (i >= partyResult.size())        // checks if the party result is incomplete (only has a digit)
                return false;
            else if(isdigit(partyResult[i]))    // checks for the second digit
                i++;
        }
        if (isalpha(partyResult[i]))            // checks for the party code
            i++;
        else
            return false;
    }
    return true;
}

//*************************************
//  hasProperSyntax
//*************************************

// Returns true if its parameter is a poll data string
// false otherwise.

bool hasProperSyntax(string pollData)
{
    if (pollData.size() == 0)                   // checks if pollData is an empty string
        return true;
    else if (pollData.size() < 2)
        return false;
    int first = 0;                              // the first character of the examining state forecast of the pollData
    int last = 0;                               // the last character of the examining state forecast of the pollData
    int stateForecastLength = 0;
    while (first < pollData.size())
    {
        while(pollData[last] != ',' && last < pollData.size())    // checks if we have reached the end of the string
        {
            last++;                              // increments until the end of the string or reaches a comma
            stateForecastLength++;               // increments the length of the examining state forecast of the pollData
        }
        last--;                                  // subtract 1 to get back to the index that points at the last character
        if (stateForecastLength < 2 || stateForecastLength == 3) //invalid length for a state code;
            return false;
        else if (stateForecastLength == 2)       // for case that only contains a state code
        {
            string stateCode = pollData.substr(first, 2);       // extracts the state code from the state forecast
            for(int i = 0; i < 2; i++)
                stateCode[i] = toupper(stateCode[i]);           // converting the state code to upper case
            if(!isValidUppercaseStateCode(stateCode))           // validates the state code
                return false;
            else
            {
                last += 2;               // +2 for the comma and get to the first character of the next party result
                first = last;
                stateForecastLength = 0;
            }
        }
        else                                    // for all the other cases that has a length of at least 4 characters
        {
            string stateCode = pollData.substr(first, 2);       // extracts the state code from the state forecast
            for(int i = 0; i < 2; i++)
                stateCode[i] = toupper(stateCode[i]);           // converting the state code to upper case
            if(!isValidUppercaseStateCode(stateCode))           // validates the state code
                return false;
            else
            {
                int partyResultsLength = stateForecastLength - 2;   // -2 for the state code
                string partyResults = pollData.substr(first + 2, partyResultsLength);   // extracts the party results
                if(!isValidPartyResults(partyResults))
                    return false;
                else
                {
                    last += 2;           // +2 for the comma
                    first = last;                               // repositioning the index
                    stateForecastLength = 0;
                }
            }
        }
    }
    first--;                            // check if the last character is a comma
    if(pollData[first] == ',')
        return false;
    else
        return true;
}

//*************************************
//  tallySeats
//*************************************

// Return 1 if the first argument pollData is not a valid poll data, seatTally left unchanged
//        2 if the second argument party is not a valid character that represents a party, seatTally left unchanged
//        1 if both the first and second arguments are invalid, seatTally left unchanged
//        0 if they are all valid arguments, seatTally is set to the number of seats counted

int tallySeats(string pollData, char party, int& seatTally)
{
    if (!hasProperSyntax(pollData))             // return 1 when the pollData is invalid
        return 1;
    else if (!isalpha(party))                   // return 2 when the party input is invalid
        return 2;
    else
    {
        int first = 0, last = 0, stateForecastLength = 0; seatTally = 0;
        while (first < pollData.size())         // this loop iterates through the entire pollData
        {
            while (last < pollData.size() && pollData[last] != ',') // this loop move the index to the last character before the comma
            {
                last++;
                stateForecastLength++;
            }
            last--;                             // subtract 1 to get back to the index of the last character of the first state forecast
            if (stateForecastLength == 2)
            {
                last += 2; // +2 for the comma and move the index by the number of stateForecastLength towards the end of the string
                first = last;
                stateForecastLength = 0;
            }
            else
            {
                int i = last;
                first += 2;                 // skips the 2 characters that compose the state code
                while (i >= first)          // this loop is to tally the seats if any
                {
                    if(toupper(pollData[i]) != toupper(party))  // checks if the tally party is the same with the checking party
                        i--;
                    else
                    {
                        i--;                // goes to the digit right in front of the party code
                        int firstDigit = pollData[i] - 48;      // subtract by 48 to get the value of the digit
                        i--;
                        if (isdigit(pollData[i]))
                        {
                            int secondDigit = pollData[i] - 48;
                            seatTally += secondDigit * 10 + firstDigit;
                            i--;            // move to left by one character
                        }
                        else
                        {
                            seatTally += firstDigit;
                        }
                        
                    }
                }
                last += 2;
                first = last;
                stateForecastLength = 0;
            }
        }
    }
    return 0;
}

int main() {
    assert(hasProperSyntax("CT5D,NY9R17D1I,VT,ne3r00D"));       // has proper syntax
    assert(!hasProperSyntax("ZT5D,NY9R17D1I,VT,ne3r00D"));      // invalid state code that does not match any of the defined state codes
    assert(!hasProperSyntax("C"));                              // invalid state code that only has one character
    assert(!hasProperSyntax("CT5D,NY9R17D1I,V"));               // invalid state code that only has one character at the end of the poll data
    assert(!hasProperSyntax("CT5D,NY9R17D1I,VT6,ne3r00D"));     // invalid party result that only has a number without a party following it
    assert(!hasProperSyntax("ZT5D,NY9R17D1I,VT12TT,ne3r00D"));  // invalid party result that has two characters following two digits for the party result
    assert(!hasProperSyntax("ZT5D,NY9R17D1I,VT123T,ne3r00D"));  // invalid party resutl that has three digits for the number of seats
    assert(hasProperSyntax(""));                                // return trues when passing in an empty string
    assert(!hasProperSyntax("CT5D,"));                          // invalid poll data with nothing after the comma
    assert(!hasProperSyntax("CT5D, "));
    
    //case 1 : valid input
    int seats1 = 0;
    assert(tallySeats("NY9R17D1I,Vt,NJ3d5r4D,KS4R", 'd', seats1) == 0);
    assert(seats1 == 24);
    
    //case 2: invalid poll data
    int seats2 = 2;
    assert(tallySeats("Y9R17D1I,Vt,NJ3d5r4D,KS4R", 'd', seats2) == 1);
    assert(seats2 == 2);
    
    //case 3: invalid party
    int seats3 = 3;
    assert(tallySeats("NY9R17D1I,Vt,NJ3d5r4D,KS4R", '-', seats3) == 2);
    assert(seats3 == 3);
    
    //case 4: invalid poll data and party
    int seats4 = 4;
    assert(tallySeats("Y9R17D1I,Vt,NJ3d5r4D,KS4R", ',', seats4) == 1);
    assert(seats4 == 4);
    
    //case 5: valid input with no seat found in the poll data
    int seats5 = 5;
    assert(tallySeats("NY9R17t1I,Vt,NJ3t5r4t,KS4R", 'd', seats5) == 0);
    assert(seats5 == 0);
    
    return 0;
}
