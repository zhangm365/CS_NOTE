

#include <iostream>

#include <string>
#include <vector>

using namespace std;

class Account
{

    public:
        void calculate() { amount += amount * interestRate; }
        static double rate() { return interestRate; }
        static void rate( double newRate ) { interestRate = newRate; }

    private:
        string owner;
        double amount;
        static double interestRate;
        static constexpr double todayRate = 5.26;
        static double initRate() { return todayRate; };
        static constexpr int vecSize = 20;
        double arr[vecSize];
        static vector<int> vec;
};


constexpr double Account::todayRate;
vector<int> Account::vec(Account::vecSize);

int main()
{

    Account A;

    return 0;

}