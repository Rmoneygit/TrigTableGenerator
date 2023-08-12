// File: TrigTableGenerator.cpp
// Author: Ryan P.
// Timestamp: <Aug-12-2023> 11:26:42 PST

#include <iostream>
#include <map>
#include <cmath>
#include <iomanip>

using namespace std;

map<double, double> angleToSine;
map<double, double> angleToCosine;
const char seperator = ' ';
const int printWidth = 7;
enum trig_func { SINE, COSINE };

double cofunction_identity(int function_to_find, double angle);
double difference_identity(int function_to_find, double angle1, double angle2);
double half_angle_identity(int function_to_find, double angle);
double sum_identity(int function_to_find, double angle1, double angle2);
double linearly_interpolate(int function_to_find, double newAngle, double angle1, double angle2);

int main()
{

    // Start by manually inserting angles whose sine and cosine we can learn by geometric construction.
    // Using only this information, we will derive everything else.
    /**********************************************************************/
    // sin(0) = 0.
    // cos(0) = 1.
    angleToSine.insert(pair<double, double>(0, 0));
    angleToCosine.insert(pair<double, double>(0, 1));

    double val;

    // sin(18) = (sqrt(5) - 1)/4.
    // cos(18) = (sqrt(10 + 2 * sqrt(5))/4
    val = (sqrt(5) - 1) / 4;
    angleToSine.insert(pair<double, double>(18, val));
    val = (sqrt(10 + 2 * sqrt(5))) / 4;
    angleToCosine.insert(pair<double, double>(18, val));

    // sin(30) = 1/2
    // cos(30) = sqrt(3)/2
    angleToSine.insert(pair<double, double>(30, 0.5));
    val = sqrt(3) / 2;
    angleToCosine.insert(pair<double, double>(30, val));

    // sin(45) = sqrt(2)/2
    // cos(45) = sqrt(2)/2
    val = sqrt(2) / 2;
    angleToSine.insert(pair<double, double>(45, val));
    angleToCosine.insert(pair<double, double>(45, val));
    /**********************************************************************/

    // Next we can repeatedly use the difference identity to determine sine and cosine of 3 degrees.
    /**********************************************************************/
    val = difference_identity(SINE, 45, 30);
    angleToSine.insert(pair<double, double>(15, val));

    val = difference_identity(COSINE, 45, 30);
    angleToCosine.insert(pair<double, double>(15, val));

    val = difference_identity(SINE, 18, 15);
    angleToSine.insert(pair<double, double>(3, val));

    val = difference_identity(COSINE, 18, 15);
    angleToCosine.insert(pair<double, double>(3, val));
    /**********************************************************************/

    // Now we're able to create a table in increments of 3 degrees.
    /**********************************************************************/
    val = sum_identity(SINE, 3, 3);
    angleToSine.insert(pair<double, double>(6, val));

    val = sum_identity(COSINE, 3, 3);
    angleToCosine.insert(pair<double, double>(6, val));

    val = sum_identity(SINE, 6, 3);
    angleToSine.insert(pair<double, double>(9, val));

    val = sum_identity(COSINE, 6, 3);
    angleToCosine.insert(pair<double, double>(9, val));

    val = difference_identity(SINE, 15, 3);
    angleToSine.insert(pair<double, double>(12, val));

    val = difference_identity(COSINE, 15, 3);
    angleToCosine.insert(pair<double, double>(12, val));

    val = sum_identity(SINE, 18, 3);
    angleToSine.insert(pair<double, double>(21, val));

    val = sum_identity(COSINE, 18, 3);
    angleToCosine.insert(pair<double, double>(21, val));

    val = sum_identity(SINE, 21, 3);
    angleToSine.insert(pair<double, double>(24, val));

    val = sum_identity(COSINE, 21, 3);
    angleToCosine.insert(pair<double, double>(24, val));

    val = difference_identity(SINE, 30, 3);
    angleToSine.insert(pair<double, double>(27, val));

    val = difference_identity(COSINE, 30, 3);
    angleToCosine.insert(pair<double, double>(27, val));

    val = sum_identity(SINE, 30, 3);
    angleToSine.insert(pair<double, double>(33, val));

    val = sum_identity(COSINE, 30, 3);
    angleToCosine.insert(pair<double, double>(33, val));

    val = sum_identity(SINE, 33, 3);
    angleToSine.insert(pair<double, double>(36, val));

    val = sum_identity(COSINE, 33, 3);
    angleToCosine.insert(pair<double, double>(36, val));

    val = difference_identity(SINE, 45, 3);
    angleToSine.insert(pair<double, double>(42, val));

    val = difference_identity(COSINE, 45, 3);
    angleToCosine.insert(pair<double, double>(42, val));

    val = difference_identity(SINE, 42, 3);
    angleToSine.insert(pair<double, double>(39, val));

    val = difference_identity(COSINE, 45, 3);
    angleToCosine.insert(pair<double, double>(39, val));

    // 1 degree is not a constructible angle. But what we can do is use the half-angle identity
    // to determine sine and cosine of 1.5 and 0.75. Then, since the trig functions are approximately linear
    // for small angles, we can use linear interpolation to estimate sine and cosine of 1 degree. We can then
    // use sum and difference identities to fill out out a table in increments of 1 degree.
    /**********************************************************************/
    val = half_angle_identity(SINE, 3);
    angleToSine.insert(pair<double, double>(1.5, val));

    val = half_angle_identity(COSINE, 3);
    angleToCosine.insert(pair<double, double>(1.5, val));

    val = half_angle_identity(SINE, 1.5);
    angleToSine.insert(pair<double, double>(0.75, val));

    val = half_angle_identity(COSINE, 1.5);
    angleToCosine.insert(pair<double, double>(0.75, val));

    val = linearly_interpolate(SINE, 1, 0.75, 1.5);
    angleToSine.insert(pair<double, double>(1, val));

    val = linearly_interpolate(COSINE, 1, 0.75, 1.5);
    angleToCosine.insert(pair<double, double>(1, val));

    for (int i = 3; i <= 45; i = i + 3)
    {
        val = sum_identity(SINE, i, 1);
        angleToSine.insert(pair<double, double>(i + 1, val));

        val = sum_identity(COSINE, i, 1);
        angleToCosine.insert(pair<double, double>(i + 1, val));

        val = difference_identity(SINE, i, 1);
        angleToSine.insert(pair<double, double>(i - 1, val));

        val = difference_identity(COSINE, i, 1);
        angleToCosine.insert(pair<double, double>(i - 1, val));
    }

    angleToSine.erase(0.75);
    angleToSine.erase(1.5);

    angleToCosine.erase(0.75);
    angleToCosine.erase(1.5);

    angleToCosine.erase(46);
    angleToCosine.erase(46);

    cout << "Angle " << " Sine " << "       Cosine" << endl;
    for (auto it = angleToSine.cbegin(), it2 = angleToCosine.cbegin();
            it != angleToSine.cend() && it2 != angleToCosine.cend(); 
            ++it, ++it2)
        cout << left << setw(printWidth) << setfill(seperator) << it->first << setprecision(4) << left << setw(12) <<
            it->second << left << setw(20) << it2->second << endl;
}

// cos(x) = sin(90 - x)
// sin(x) = cos(90 - x)
double cofunction_identity(int function_to_find, double angle)
{
    double value = 0;

    if (function_to_find == SINE)
        value = angleToCosine[90 - angle];
    
    if (function_to_find == COSINE)
        value = angleToSine[90 - angle];

    return value;
}

// cos(x - y) = cos(x)cos(y) + sin(x)sin(y)
// sin(x - y) = sin(x)cos(y) - cos(x)sin(y)
double difference_identity(int function_to_find, double angle1, double angle2)
{
    double value = 0;

    if (function_to_find == SINE)
        value = angleToSine[angle1] * angleToCosine[angle2] - angleToCosine[angle1] * angleToSine[angle2];
    
    if (function_to_find == COSINE)
        value = angleToCosine[angle1] * angleToCosine[angle2] + angleToSine[angle1] * angleToSine[angle2];

    return value;
}

// cos(x + y) = cos(x)cos(y) - sin(x)sin(y)
// sin(x + y) = sin(x)cos(y) + cos(x)sin(y)
double sum_identity(int function_to_find, double angle1, double angle2)
{
    double value = 0;

    if (function_to_find == SINE)
        value = angleToSine[angle1] * angleToCosine[angle2] + angleToCosine[angle1] * angleToSine[angle2];

    if (function_to_find == COSINE)
        value = angleToCosine[angle1] * angleToCosine[angle2] - angleToSine[angle1] * angleToSine[angle2];

    return value;
}

// cos(x/2) = sqrt((1 + cos(x))/2)
// sin(x/2) = sqrt((1 - cos(x))/2)
double half_angle_identity(int function_to_find, double angle)
{
    double value = 0;

    if (function_to_find == SINE)
        value = sqrt((1 - angleToCosine[angle]) / 2);
    
    if (function_to_find == COSINE)
        value = sqrt((1 + angleToCosine[angle]) / 2);

    return value;
}

double linearly_interpolate(int function_to_find, double newAngle, double angle1, double angle2)
{
    double value = 0;

    if (function_to_find == SINE)
    {
        value = angleToSine[angle1] + (newAngle - angle1) * (angleToSine[angle2] - angleToSine[angle1]) / (angle2 - angle1);
    }

    if (function_to_find == COSINE)
    {
        value = angleToCosine[angle1] + (newAngle - angle1) * (angleToCosine[angle2] - angleToCosine[angle1]) / (angle2 - angle1);
    }

    return value;
}
