//Defines the entry point for the console application.
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <math.h>
using namespace std;

//Initialize a global boolean array marking primes
bool global_prime_flag[100000000];
long long max_n_so_far;


/*
This function reads a line of int values into a vector function and returns that
vector.
*/
vector<int> readlineofints(int count) {
    // Input values
    vector<int> linevalues(count);
    for (int j = 0; j < count; j++) {
        int val;
        cin >> val;
        linevalues[j] = val;
    }
    return linevalues; // Return line values as a vector
}

/*
This function reads a line of long values into a vector function and returns that
vector.
*/
vector<long> readlineoflongs(int count) {
    // Input values
    vector<long> linevalues(count);
    for (int j = 0; j < count; j++) {
        long val;
        cin >> val;
        linevalues[j] = val;
    }
    return linevalues; // Return line values as a vector
}



/*Program to find the GCD of two input values
*/
long gcd(long a, long b) {
    if (b == 0) { return a; }
    else {
        return gcd(b, a % b);
    }
}

/*Optimized Sieve of Eratosthenes algorithm
Returns a sorted vector of long values that contains all the primes less than the input number
Requires math import for square root function
*/
vector<long> sieve(long n) {
    vector<long> result;
    vector<bool> prime_flag(n + 1, true); //Initialized with a 0 and 1 value which are never used to keep indexes clear
    //Iterate over numbers
    for (long i = 2; i <= sqrt(n); i++) {
        if (prime_flag[i] == true) {
            for (long j = i*i; j < n; j += i) {
                prime_flag[j] = false;
            }
        }
    }
    //Record prime numbers to output vector and to global array
    for (long i = 2; i < n; i++) {
        if (prime_flag[i]) {
            result.push_back(i);
            global_prime_flag[i] = true;
        }
    }
    return result;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    // get test case count
    int t;
    std::cin >> t;

    //Initialize primes vector
    vector<long> primes;
    max_n_so_far = 0;
    

    //! loop over all the test cases
    for (int i = 1; i <= t; i++) {
        // Read in params
        vector<long> params = readlineoflongs(1);
        long n = params[0];
        

        //Get the primes less than this number
        //If we haven't search for any primes before
        if (max_n_so_far == 0) {
            primes = sieve(n); //Do full search
            max_n_so_far = n; //Set new max n
        }
        //If we've already searched for primes but n is greater than previous searches
        else if (max_n_so_far < n) {
            primes = sieve(n); //Search again
            max_n_so_far = n; //Set new max n
        }


        vector<long> answers;

        //If the number is even
        if (n % 2 == 0) {
            //For each number in the primes array
            for (long num : primes) {
                //Check to see if n minus this prime is also prime
                if (global_prime_flag[n-num]) {
                    //If it is, add num and the partner to the answers array and break
                    answers.push_back(num);
                    answers.push_back(n-num);
                    break;
                }
            }
        }
        //If the number is odd
        else {
            //For each number in the primes array
            for (long num : primes) {
                for (long sec_num : primes) {
                    if (sec_num > n) { break; } //If we're using an old vector and we've surpassed n in this loop, break back to first loop
                    //Check to see if n minus the first two numbers is prime
                    if (global_prime_flag[n - num - sec_num]) {
                        //If it is, add num and the partner to the answers array and break
                        answers.push_back(num);
                        answers.push_back(sec_num);
                        answers.push_back(n-num-sec_num);
                        break;
                    }
                }
                //If we found the answer, break out of this loop too
                if (answers.size() > 0) { break; }
            }
        }
        
        //Sort the output
        sort(answers.begin(), answers.end());

        //Print output
        std::cout << "Case #" << i << ": ";
        for (long num : answers) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}