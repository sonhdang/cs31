//
//  rental.cpp
//  Project 2
//
//  Created by Son Dang on 10/18/18.
//  Copyright © 2018 Son Dang. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

const int BASE_CHARGE_NONLUXURY = 33;
const int BASE_CHARGE_LUXURY = 61;
const double COST_PER_MILE_FIRST_100 = 0.27;
const double COST_PER_MILE_NEXT_300 = 0.21;
const double COST_PER_MILE_NEXT_300_WINTER = 0.27;
const double COST_PER_MILE_BEYOND_400 = 0.19;

int main() {
    int odometerAtStart;
    int odometerAtEnd;
    int rentalDays;
    string customerName;
    char luxuryCar;
    int month;
    double rentalCharge;
    
    cout << "Odometer at start: ";
    cin >> odometerAtStart;
    
    cout << "Odometer at end: ";
    cin >> odometerAtEnd;
    
    cout << "Rental days: ";
    cin >> rentalDays;
    
    cout << "Customer name: ";
    cin.ignore(1000,'\n');
    getline (cin, customerName);

    cout << "Luxury car? (y/n): ";
    cin >> luxuryCar;
    
    cout << "Month (1=Jan, 2=Feb, etc.): ";
    cin >> month;
    
    cout << "---" << endl;
    
    if(odometerAtStart < 0)
    {
        cout << "The starting odometer reading must be nonnegative." << endl;
    }
    else if(odometerAtEnd < odometerAtStart)
    {
        cout << "The final odometer reading must be at least as large as the starting reading." << endl;
    }
    else if(rentalDays < 0)
    {
        cout << "The number of rental days must be positive." << endl;
    }
    else if(customerName == "")
    {
        cout << "You must enter a customer name." << endl;
    }
    else if(!(luxuryCar == 'y' || luxuryCar == 'n'))
    {
        cout << "You must enter y or n." << endl;
    }
    else if(month < 1 || month > 12)
    {
        cout << "The month number must be in the range 1 through 12." << endl;
    }
    else
    {
        int baseCharge;
        if(luxuryCar == 'y')
        {
            baseCharge = rentalDays * BASE_CHARGE_LUXURY;
        }
        else
        {
            baseCharge = rentalDays * BASE_CHARGE_NONLUXURY;
        }
        
        int totalMilesDriven = odometerAtEnd - odometerAtStart;
        double mileTotalCost;
        double costPerMile = COST_PER_MILE_FIRST_100;
        if(totalMilesDriven <= 100)
        {
            mileTotalCost = totalMilesDriven * costPerMile;
        }
        else
        {
            totalMilesDriven -= 100;
            mileTotalCost = 100 * costPerMile;
            
            if(month == 1 || month == 2 || month == 3 || month == 12)
            {
                costPerMile = COST_PER_MILE_NEXT_300_WINTER;
            }
            else
            {
                costPerMile = COST_PER_MILE_NEXT_300;
            }
            
            if(totalMilesDriven <= 300)
            {
                mileTotalCost += totalMilesDriven * costPerMile;
            }
            else
            {
                totalMilesDriven -= 300;
                mileTotalCost += 300 * costPerMile;
        
                costPerMile = COST_PER_MILE_BEYOND_400;
                mileTotalCost += totalMilesDriven * costPerMile;
            }
        }
        rentalCharge = mileTotalCost + baseCharge;
        cout.setf(ios::fixed);
        cout.precision(2);
        cout << "The rental charge for " << customerName <<" is $" << rentalCharge << endl;
    }
    
    return 0;
}
