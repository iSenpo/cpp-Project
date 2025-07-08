#include "Filter.hpp"
#include <ctime>

bool EXIT = false;
bool Disscount = false;

bool isName(string s);
bool isUsername(string s);
bool isPassword(string s);
bool isEmail(string s);
bool isPhoneNumber(string s);
bool CheckUserExist(string username,string FileName);
bool CheckInfo(string username,string password,string FileName);
bool CheckCord(string s);
int distance(string cord1,string cord2);
class UnderAgeDriver{};

class Car{
private:
    string Owner;
    string Model;
    string color;
    string pelak;
public:
    Car(){}
    Car(string FirstName,string LastName){
        Owner = FirstName+" "+LastName;
    }
    void SetCarInfo(){
        cout<<"Enter your Car Name and Model :  ";
        getline(cin,Model);
        cout<<"Enter your Car Color :  ";
        getline(cin,color);
        cout<<"Enter your Car pelak :  ";
        getline(cin,pelak);
    }
};

class Account{
protected:
    string FirstName;
    string LastName;
    string username;
    string password;
    string Email;
    string PhoneNumber;
    int point = 0;
    float balance = 0;
    int x = 0,y = 0;
public:
    bool FirstTrip = true;
 void CreateAccount(string FileName){
        bool exists;
        string pass2;
        cin.ignore();
        while(1){
            cout<<"Enter your First Name :  ";
            getline(cin,FirstName);
            if(!isName(FirstName)){
                cout<<"invalid Name! try again\n";
                continue;
            }
            cout<<"Name :<"<<FirstName<<"> Accepted\n\n";
            break;
        }
        while(1){
            cout<<"Enter your Last Name :  ";
            getline(cin,LastName);
            if(!isName(LastName)){
                cout<<"invalid Last Name! try again\n";
                continue;
            }
            cout<<"Last Name :<"<<LastName<<"> Accepted\n\n";
            break;
        }
        while(1){
            cout<<"Enter your USERNAME :  ";
            getline(cin,username);
            if(CheckUserExist(username,FileName)){
                cout<<"This USERNAME already Exist! try another:\n";
                continue;
            }
            if(!isUsername(username)){
                cout<<"invalid USERNAME! try again\n";
                continue;
            }
            cout<<"USERNAME :<"<<username<<"> Accepted\n\n";
            break;
        }
        while(1){
            cout<<"Enter your PASSWORD :  ";
            getline(cin,password);
            if(password.size() < 8){
                cout<<"PASSWORD is weak.it must be atleast 8 characters Long\n";
                continue;
            }
            if(!isPassword(password)){
                cout<<"invalid PASSWORD! try again\n";
                continue;
            }
            exists = (password.find(username) != string::npos); 
            if((password.size() >= 8 && password.size() <= 10)){
                if(exists){
                    cout<<"PASSWORD is weak! Don't put your username into your password!\n";
                    continue;
                }
                else{
                    cout<<"Password is GOOD!\n";
                }
            }
            if(password.size() >= 11){
                cout<<"Password is Good and Strong!\n";
            }
            cout<<"re-Enter you'r PASSWORD :  ";
            getline(cin,pass2);
            if(pass2 != password){
                cout<<"PASSWORDs Don't match! try again\n";
                continue;
            }
            cout<<"PASSWORD :<"<<password<<"> Accepted\n\n";
            break;
        }
        while(1){
            cout<<"Enter your Email :  ";
            getline(cin,Email);
            if(!isEmail(Email)){
                cout<<"invalid Email! try again\n";
                continue;
            }
            cout<<"Email :<"<<Email<<"> Accepted\n\n";
            break;
        }
         while(1){
            cout<<"Enter your phone Number in a format like (09*********) :  ";
            getline(cin,PhoneNumber);
            if(PhoneNumber.size() != 11){
                cout<<"Invalid Format! try again:\n";
                continue;
            }
            if(!isPhoneNumber(PhoneNumber)){
                cout<<"invalid Number! try again\n";
                continue;
            }
            cout<<"PhoneNumber :<"<<PhoneNumber<<"> Accepted\n\n";
            break;
        }
    }
    float GetBalance() const{
        return balance;
    }
    void IncreaseBalance(float a){
        balance += a;
    }
    void IncreasePoint(){
        point ++;
    }
    int GetPoints() const{
        return point;
    }
    string GetUsername() const{
        return username;
    }
    void DecreaseBalance(float a){
        balance -= a;
    }
};
class Passanger:public Account{
private:
    bool FirstTrip;
public:
    Passanger(){
        balance = 0;
        point = 0;
    }
    void SaveData(){
        ofstream file("PassangerAccounts.txt",ios::app);
        if(file.is_open()){
            file<< username << " " << password <<"\n";
            file.close();
        }else{
            cerr<<"something went wrong! cant save data!\n";
        }
    }
};
class Driver:public Account{
private:
    bool isActive = false;
public:
    Car car;
    Driver(){}
    void DriverRegister(){
        int age;
        car.SetCarInfo();
        cout<<"Enter your age :  ";
        cin>>age;
        if(age < 19){
            UnderAgeDriver Ex;
            throw Ex;
        }
    }
    void SaveData(){
        ofstream file("DriverAccounts.txt",ios::app);
        if(file.is_open()){
            file<< username << " " << password <<"\n";
            file.close();
        }else{
            cerr<<"something went wrong! cant save data!\n";
        }
    }
    
};
class SignIn:public Account{
public:
    SignIn(string FileName){
        while(1){
            cout<<"Enter your USERNAME :  ";
            cin>>username;
            if(!CheckUserExist(username,FileName)){
                cout<<"This USERNAME does not Exist! try again:\n";
                continue;
            }
            cout<<"Enter your PASSWORD :  ";
            cin>>password;
            if(!CheckInfo(username,password,FileName)){
                cout<<"USERNAME and PASSWORD dont match! try again:\n";
                continue;
            }
            break;
        }
        cout<<"~ ~ ~ Successfully LogedIn ~ ~ ~\n";
    }
};
class Admin{
private:
    const string AdminPassword = "AP41148";
public:
    Admin(){
        while(1){
            cout<<"Enter Admin's PASSWORD :  ";
            string input;
            cin>>input;
            if(input != AdminPassword){
                cout<<"password is incorrect pls try again:  ";
                continue;
            }
            else{
                cout<<"~ ~ ~ Successfully LogedIn as Admin ~ ~ ~\n";
                break;
            }
        }
    }
 void ShowPassangers(){
        string user,pass;
        int counter = 1;
        ifstream file("PassangerAccounts.txt");
        if(file.is_open()){
            file.seekg(0,ios::end);
            if(file.tellg() == 0){
                cout<<"No passanger has signed up yet!\n";
                file.close();
            }
            file.seekg(0);
            cout<<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n"
                <<"USERNAME  |  PASSWORD\n";
            while(file >> user >> pass){
                cout<<counter<<"."<<user << " "<< pass<<"\n";
                counter++;
            }
            cout<<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n";
            file.close();
        }else{
            cerr<<"can't open file!!\n";
        }
    }
    void ShowDrivers(){
        int counter = 1;
        string user,pass;
        ifstream file("DriverAccounts.txt");
        if(file.is_open()){
            file.seekg(0,ios::end);
            if(file.tellg() == 0){
                cout<<"No Driver has signed up yet!\n";
                file.close();
            }
            file.seekg(0);
            cout<<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n"
                <<"USERNAME  |  PASSWORD\n";
            while(file >> user >> pass){
                cout<<counter<<"."<<user << " "<< pass<<"\n";
                counter++;
            }
            cout<<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n";
            file.close();
        }else{
            cerr<<"can't open file!!\n";
        }
    }
    void ShowDisscountList(){
        int counter = 1;
        string codes;
        ifstream file("DisscountCodes.txt");
        if(file.is_open()){
            file.seekg(0,ios::end);
            if(file.tellg() == 0){
                cout<<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n"
                    <<"Your List is Empty!\n";
                file.close();
            }
            file.seekg(0);
            cout<<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n";
            while(file >> codes){
                cout<<counter<<"."<<codes<<"\n";
                counter++;
            }
            cout<<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n";
            file.close();
        }else{
            cerr<<"can't open file!!\n";
        }
    }
    void AddDisscount(){
        int counter = 1;
        string codes;
        ofstream file("DisscountCodes.txt",ios::app);
        if(file.is_open()){
            cout<<"Enter your Disscount Code in 1 word :  ";
            cin>>codes;
            file << codes<< "\n";
            cout<<"~ ~ ~ Disscount Code successfully Added ~ ~ ~\n";
            file.close();
        }else{
            cerr<<"can't open the file!!\n";
        }
    }
    void DeleteDisscount(){
        string s;
        int line,counter = 0;
        cout<<"Which TASK you want to DELETE?('0' to see list / '-1' to go back)\n";
        cin >> line;
        if(line == 0){
            this->ShowDisscountList();
            cout<<"Which TASK you want to DELETE?('0' to see list / '-1' to go back)\n";
            cin >> line;
        }
        if(line == -1){

        }
        else{
            ifstream fileIn("DisscountCodes.txt");
            ofstream tempOut("temp.txt");
            if(fileIn.is_open() && tempOut.is_open()){
                while(getline(fileIn,s)){
                    counter++;
                    if(line != counter){
                        tempOut << s << "\n";
                    }
                }
                fileIn.close();
                tempOut.close();
            ifstream tempIn("temp.txt");
            ofstream fileOut("DisscountCodes.txt");
            while(getline(tempIn,s)){
                fileOut << s << "\n";
            }
            cout<<"# # # Task succecfully deleted! # # #\n";
            tempIn.close();
            fileOut.close();
            }
            else{
                cerr<<"Something went Wrong!\n";
            }
        ofstream clearTemp("temp.txt",ios::trunc);
        clearTemp.close();
        }
    }
};
class CarRequest{
private:
    string CarModel;
    Account passanger;
public:
    CarRequest(){}
    CarRequest(Passanger& b):passanger(b){}
    CarRequest(SignIn& b):passanger(b){}
    void CarRequestMenu(){
        bool loop = true;
        while(loop){
            cout<<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n"
                <<"1.Request a Car\n"
                <<"2.Show Balance\n"
                <<"3.increase Balance\n"
                <<"4.Show my points\n"
                <<"0.EXIT\n"
                <<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n";
            int choice;
            cin>>choice;
            switch(choice){
                case(1):{
                    GetCar();
                    break;
                }
                case(2):{
                    cout<<"your balance is : "<<passanger.GetBalance()<<"$\n";
                    break;
                }
                case(3):{
                    cout<<"how much you want to increase?  ";
                    float increase;
                    cin>>increase;
                    passanger.IncreaseBalance(increase);
                    break;
                }
                case(4):{
                    cout<<"your point is : "<<passanger.GetPoints()<<"\n";
                    break;
                }
                case(0):{
                    loop = false;
                    EXIT = true;
                    break;
                }
                default:{
                    cout<<"WTF\n";
                    break;
                }
            }
        }
    }
    void GetCar(){
        string inCord,fiCord,code,s;
        if(passanger.FirstTrip){
            cout<<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n"
                <<"your travel will be free becasue of First Travel!\n";
        }
        else{
            cout<<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n"
            <<"Enter your DisscountCode if you have (type -1 if u dont) :  ";
            cin>>code;
            if(code == "-1"){
            }
            else{
                ifstream file("DisscountCodes.txt");
                if(file.is_open()){
                    while(file >> s){
                        if(s == code){
                            cout<<"Disscount Code Submited!\n";
                            Disscount = true;
                            break;
                        }
                    }
                    if(!Disscount){
                        cout<<"Not a valid Code!\n";
                    }
                    file.close();
                }else{
                    cerr<<"cant open file~!\n";
                }
            }
        }
        cin.ignore();
        while(1){
            cout<<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n"
                <<"Enter your 'starting' Cordination like (x,y) :  ";
            getline(cin,inCord);
            if(!CheckCord(inCord)){
                cout<<"not a valid format!\n";
                continue;
            }
            cout<<"Enter your 'Final' Cordination like (x,y) :  ";
            getline(cin,fiCord);
            cout<<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n";
            if(!CheckCord(fiCord)){
                cout<<"not a valid format!\n";
                continue;
            }
            if(passanger.GetBalance() < distance(inCord,fiCord) && !passanger.FirstTrip){
                cout<<"you need to increament your balance!!\n"
                    <<"This travel cost you : "<<distance(inCord,fiCord)<<"$\n"
                    <<"but you only have : "<< passanger.GetBalance()<<"$\n";
                return; 
            }
            else{
                if(!passanger.FirstTrip){
                    passanger.DecreaseBalance(distance(inCord,fiCord));
                    cout<<"This trip cost you : "<<distance(inCord,fiCord)<<"$\n";
                }
                else{cout<<"This trip cost you : "<<distance(inCord,fiCord)<<"$\n"
                    <<"But you payed 0$ because it was your first trip!\n";
                }
            }
            cout<<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n"
                <<"Ok.Searching for a Car Now!\n";
                passanger.IncreasePoint();
                passanger.FirstTrip = false;
            break;
        }
        ofstream file("CarRequest.txt",ios::app);
        if(file.is_open()){
            file<<passanger.GetUsername()<<" "<<inCord<<" "<<fiCord<<"\n";
            file.close();
        }else{
            cerr<<"cant open file!\n";
        }
    }
};
class Ride{
private:
public:
};
class Payment{
private:
    CarRequest travel;
public:
    Payment(){}
    void Passanger(){
    }
    void Driver(){
    }
};
class MainMenu{
public:
    Payment Record;
    MainMenu(){
    }
    void PassangerMenu(){
        cout<<"~ ~ ~ ~ ~ Passanger ~ ~ ~ ~ ~\n"
            <<"1.signUp (create new account)\n"
            <<"2.signIn (log into existing account)\n"
            <<"0.EXIT\n"
            <<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n";
        bool loop = true;
        while(loop){
            if(EXIT){
                break;
            }
            int choice;
            cin>>choice;
            switch(choice){
                case(1):{
                    Passanger account;
                    account.CreateAccount("PassangerAccounts.txt");
                    cout<<"~ ~ ~ ~ Account Successfully Created ~ ~ ~ ~";
                    account.SaveData();
                    CarRequest _CarRequest(account);
                    _CarRequest.CarRequestMenu();
                    break;
                }
                case(2):{
                    SignIn account("PassangerAccounts.txt");
                    CarRequest _CarRequest(account);
                    _CarRequest.CarRequestMenu();
                    break;
                }
                case(0):{
                    loop = false;
                    EXIT = true;
                    break;
                }
                default:{
                    cout<<"invalid Option! try again:  \n";
                    break;
                }
            }
        }
    }
    void DriverMenu(){
        cout<<"~ ~ ~ ~ ~ Driver ~ ~ ~ ~ ~\n"
            <<"1.signUp (create new account)\n"
            <<"2.signIn (log into existing account)\n"
            <<"0.EXIT\n"
            <<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n";
        bool loop = true;
        while(loop){
            if(EXIT){
                break;
            }
            int choice;
            cin>>choice;
            switch(choice){
                case(1):{
                    Driver account;
                    account.CreateAccount("DriverAccounts.txt");
                    try{
                    account.DriverRegister();
                    }catch(UnderAgeDriver ex){
                        cout<<"You must be 19 years old or above to register!\n"
                            <<"get out of here\n";
                        loop = false;
                        EXIT = true;
                        break;
                    }
                    cout<<"~ ~ ~ ~ Account Successfully Created ~ ~ ~ ~";
                    account.SaveData();

                    break;
                }
                case(2):{
                    SignIn account("DriverAccounts.txt");

                    break;
                }
                case(0):{
                    EXIT = true;
                    loop = false;
                    break;
                }
                default:{
                    cout<<"invalid Option! try again:  \n";
                    break;
                }
            }
        }
    }
    void AdminMenu(){
        Admin admin;
        bool loop = true;
        while(loop){
            if(EXIT){
                break;
            }
            cout<<"~ ~ ~ ~ Admin ~ ~ ~ ~\n"
                <<"1.see all Passangers\n"
                <<"2.see all Drivers\n"
                <<"3.Show disscount list\n"
                <<"4.add new disscount code\n"
                <<"5.delete a disscount code\n"
                <<"0.EXIT\n"
                <<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n";
            int choice;
            cin>>choice;
            switch(choice){
                case(1):{
                    admin.ShowPassangers();
                    break;
                }
                case(2):{
                    admin.ShowDrivers();
                    break;
                }
                case(3):{
                    admin.ShowDisscountList();
                    break;
                }
                case(4):{
                    admin.AddDisscount();
                    break;
                }
                case(5):{
                    admin.DeleteDisscount();
                    break;
                }
                case(0):{
                    loop = false;
                    EXIT = true;
                    break;
                }
                default:{
                    cout<<"invalid Option! try again:  \n";
                    break;
                }
            }
        }
    }
};
int main(){
    MainMenu start;
    cout<<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n"
        <<"1.Passanger\n"
        <<"2.Driver\n"
        <<"3.Admin\n"
        <<"0.EXIT\n"
        <<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n";
    while(!EXIT){
        int choice;
        cin>>choice;
        switch(choice){
            case(1):{
                start.PassangerMenu();
                break;
            }
            case(2):{
                start.DriverMenu();
                break;
            }
            case(3):{
                start.AdminMenu();
                break;
            }
            case(0):{
                EXIT = true;
                cout<<"closing program!  bYe bYe";
                break;
            }
            default:{
                cout<<"Invalid option! try again now: ";
                break;
            }
        }
    }
    return 0;
}