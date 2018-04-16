#ifndef RANDOM
#define RANDOM value

#include <cmath>
#include <iostream>
#include <time.h>
#include <limits.h>

using namespace std;

#define max_int 32214


class Random{
public:
    Random(bool pseudo = true);
    
    double random_real();
    
    int random_integer(int low, int high);
    
    int poisson(double mean);
    
private:
    int reseed()// Re-randomize the seed. int seed,
    {
        seed=seed*multiplier+add_on;
        return seed;
    }
    int seed,multiplier,add_on; // constants for use in arithmetic operations
    
};


Random::Random(bool pseudo)
{
    if(pseudo) seed = 1;
    else seed = time(NULL) % max_int ;
    multiplier = 2743;
    add_on = 5923;
}

double Random::random_real()
/*Post: A random real number between 0 and 1 isreturned.*/
{
    double max = max_int + 1.0;
    double temp = reseed();
    if (temp < 0) temp = temp + max;
    return temp/max;
}

int Random::random_integer(int low, int high)
/*Post: A random integer between low and high (inclusive) isreturned.*/
{
    if (low > high)
        return random_integer(high, low);
    else
        return ((int)((high-low+1)*random_real())) + low;
}


int Random::poisson(double mean)
{
    double limit = exp(-mean);
    double product = random_real( );
    int count = 0;
    while (product > limit)
    {
        count++;
        product *= random_real( );
    }
    return count;
}

#endif
