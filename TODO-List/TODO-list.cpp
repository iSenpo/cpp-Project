#include <iostream>
#include <fstream>
using namespace std;

class User{
    private:
    string username;
    string password;
    public:
    User(string a,string b): username(a), password(b){};
};
class TaskBase{};
class TimedTask : public TaskBase{};
class NormalTask : public TaskBase{
    
};

int main(){

    return 0;
}