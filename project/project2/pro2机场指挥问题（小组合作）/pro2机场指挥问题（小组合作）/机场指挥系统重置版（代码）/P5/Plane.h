#ifndef PLANE
#define PLANE value
#include<iostream>
#include "Random.h"
using namespace std;

enum Plane_status {null, arriving, departing,emergency};
class Plane{
public:
    Plane();
    
    Plane(int flt, int time, Plane_status status);
    void refuse() const;
    void land(int time) const;
    void fly(int time) const;
    int started() const;
    Plane_status get_status()const;
    
private:
    int flt_num;
    int clock_start;
    Plane_status state;
    int fuel;
};

int crashes=0;
Random dice;

Plane::Plane(int flt, int time, Plane_status status)
/*Post: The Plane data members flt_num, clock_start, and state are set to the values of the parameters flt, time and status respectively.*/
{
    flt_num = flt;
    clock_start = time;
    state = status;
    cout << "Plane number " << flt << " ready to ";
    if(status==arriving){
        fuel = dice.random_integer(0, 20); 
        if (fuel <= 1) 
            status=state=emergency; 
    }
    if(status== arriving){
        cout << "land."<<endl;
    }
    else if(status==departing)
        cout <<"take off."<<endl;
    else
        cout<<"Emergency."<<endl;
}
    
Plane::Plane()
/*Post: The Plane data members flt_num, clock_start, state are set to illegal default values.*/
{
    flt_num = -1;
    clock_start = -1;
    state = null;
}

void Plane::refuse() const
/*Post: Processes a Plane wanting to use Runway, when the Queue isfull.*/
{
    cout << "Plane number " << flt_num;
    if (state == arriving||state==emergency){
        cout<<"directed to another airport"<<endl;
        if (fuel <= 3) {  
            cout << "Unfortunately it didn't have enough fuel and crashed."; 
            cout << endl;  
            cout << "plane CRASH \n\n"; 
            crashes++; 
        }
    }
    else
        cout <<"told to try to takeoff again later"<<endl;
}

void Plane::land(int time) const
/*Post: Processes a Plane that is landing at the specified time.*/
{
    int wait = time - clock_start;
    if(wait>fuel){
        cout << "\n plane CRASH \n";  
        cout << time << ": Plane number " << flt_num 
        << " ran out of fuel crashed after "  << wait 
        << " time unit" << ((wait == 1) ? "" : "s") << 
        " in the landing queue." << endl; 
        crashes++;
    }
    cout <<time<<":Plane number"<<flt_num<<"landed after"
    <<wait<<" timeunit "<<((wait == 1)?"":"s") <<" in the takeoff queue."<<endl;
}

void Plane::fly(int time) const
/*Post: Processa Plane that is taking off at the specified time.*/
{
    int wait = time - clock_start;
    cout <<time<<":Plane number"<<flt_num<<"took off after"
    <<wait<<" timeunit "<<((wait == 1)?"":"s") <<" in the takeoff queue."<<endl;
}
    
int Plane::started() const
/*Post: Return the time that the Plane entered the airportsystem.*/ {
    return clock_start;
}
  
Plane_status Plane::get_status()const
{
    return state;
}
#endif
