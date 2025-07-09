#include "Filter.hpp"

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
int NumberOfPassangers();
class UnderAgeDriver{};

class Car{
private:
    string Owner;
    string Model;
    string color;
    string pelak;
public:
    Car(){}
    void GetName(string FirstName,string LastName){
        Owner = FirstName+" "+LastName;
    }
    void SetCarInfo(){
        cout<<"Enter your Car Name :  ";
        cin>>Model;
        cin.ignore();
        cout<<"Enter your Car Color :  ";
        cin>>color;
        cin.ignore();
        cout<<"Enter your Car pelak like(33B88877):  ";
        cin>>pelak;
        cin.ignore();
        ofstream file("CarList.txt",ios::app);
        if(file.is_open()){
            file << Owner << " "<< Model <<" "<< color <<" "<< pelak <<"\n";
            file.close();
        }else{
            cerr<<"Cant save data!\n";
        }
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
        car.GetName(FirstName,LastName);
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
class Payment{
private:
    time_t now = time(0);
    tm* hour = localtime(&now);
    float price;
public:
    Payment(){}
    float GetPassengerPrice(int distance){
        if(hour->tm_hour > 0 && hour->tm_hour<6){
            price = distance*2.5;
            cout<<"you travel beteew 12 - 6 and your price is doubled!\n";
        }
        else{
            price = distance*1.5;
        }
        if(Disscount){
            price-= price*0.2;
            cout<<"you got (20%) disscount!\n";
            Disscount = false;
        }
        return price;
    }
    float DriverPay(int distance){
        return distance*1.5;
    }
};
class CarRequest{
private:
    Account passanger;
    Payment pay;
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
                    system("cls");
                    GetCar();
                    break;
                }
                case(2):{
                    system("cls");
                    cout<<"your balance is : "<<passanger.GetBalance()<<"$\n";
                    break;
                }
                case(3):{
                    system("cls");
                    cout<<"how much you want to increase?  ";
                    float increase;
                    cin>>increase;
                    passanger.IncreaseBalance(increase);
                    break;
                }
                case(4):{
                    system("cls");
                    cout<<"your point is : "<<passanger.GetPoints()<<"\n";
                    break;
                }
                case(0):{
                    system("cls");
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
            float price = pay.GetPassengerPrice(distance(inCord,fiCord));
            if(passanger.GetBalance() < price && !passanger.FirstTrip){
                cout<<"you need to increament your balance!!\n"
                    <<"This travel cost you : "<<price<<"$\n"
                    <<"but you only have : "<< passanger.GetBalance()<<"$\n";
                return; 
            }
            else{
                if(!passanger.FirstTrip){
                    passanger.DecreaseBalance(price);
                    cout<<"This trip cost you : "<<price<<"$\n";
                }
                else{cout<<"This trip cost you : "<<price<<"$\n"
                    <<"But you payed 0$ because it was your first trip!\n";
                }
            }
            cout<<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n"
                <<"Ok.Searching for a Car Now!\n";
                passanger.IncreasePoint();
                passanger.FirstTrip = false;
                ShowCars();
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
    void ShowCars(){
        int counter = 1;
        string FirstName,LastName,model,color,pelak;
        ifstream file("CarList.txt");
        cout<<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n\n";
        if(file.is_open()){
            file.seekg(0,ios::end);
            if(file.tellg() == 0){
                cout<<"No Car has signed up yet!\n";
            }
            file.seekg(0);
            while(file >> FirstName >> LastName >> model >> color >> pelak){
                cout<<counter<<"."<<FirstName<<" "<<LastName<<" | "<<"car model : "<<model
                <<" | " << "color : "<< color <<" | "<<"pelak : "<<pelak<<"\n\n";
                counter++;
            }
            file.close();
            cout<<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n";
        }else{
            cerr<<"cant open file!\n";
        }
    }
};
class Ride{
private:
    Account driver;
    string name,inCord,fiCord;
    time_t now = time(0);
    tm* ridetime = localtime(&now);
    Payment pay;
public:
    Ride(Driver& d):driver(d){}
    Ride(SignIn& d):driver(d){}
    void RideMenu(){
        bool loop = true;
            while(loop){
                cout<<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n"
                    <<"1.Show All Requests\n"
                    <<"2.Choose a passanger\n"
                    <<"3.Show balance\n"
                    <<"4.Show my points\n"
                    <<"0.EXIT\n"
                    <<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n";
                int choice;
                cin>>choice;
                switch(choice){
                    case(1):{
                        system("cls");
                        ShowList();
                        break;
                    }
                    case(2):{
                        system("cls");
                        cout<<"Which one based on numbers('-1' to go back '0' to see list)?  ";
                        while(1){
                            int n;
                            cin>>n;
                            if(n == -1){
                                break;
                            }
                            if(n == 0){
                                system("cls");
                                ShowList();
                                cout<<"Which one based on numbers('-1' to go back '0' to see list)?  ";
                                continue;
                            }
                            if(n>NumberOfPassangers() || n<-1){
                                cout<<"invalid input!\n";
                                break;
                            }else{
                                system("cls");
                                ChoosePassnger(n);
                                DeleteCarRequest(n);
                                break;
                            }
                        }
                        break;
                    }
                    case(3):{
                        system("cls");
                        cout<<"your balance is : "<<driver.GetBalance()<<"$\n";
                        break;
                    }
                    case(4):{
                        system("cls");
                         cout<<"your point is : "<<driver.GetPoints()<<"\n";
                        break;
                    }
                    case(0):{
                        system("cls");
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
    void ChoosePassnger(int a){
        int counter = 1;
        ifstream file("CarRequest.txt");
        if(file.is_open()){
            string user,pass;
            while( file >> name >> inCord >> fiCord){
                    if(a == counter){
                        break;
                    }
                counter++;
                }
            file.close();
        }else{
            cerr<<"cant open file!\n";
        }
        ShowRecord();
    }
    void ShowRecord(){
        int length = distance(inCord,fiCord);
        time_t StartTime = time(nullptr);
        time_t EndTime = StartTime + length*60;
        cout<<"~ - ~ - ~ - ~ - ~ Travel Record - ~ - ~ - ~ - ~ - ~\n"
            <<"Passanger name :    "<<name<<"\n\n"
            <<"Starting time :     "<<ctime(&StartTime)<<"\n"
            <<"Ending time :    "<<ctime(&EndTime)<<"\n"
            <<"distance traveled :     "<<length<<"km\n\n"
            <<"you earned : "<<pay.DriverPay(length)<<"$ from this trip\n\n"
            <<"yor points increased by : 1\n\n"
            <<"you are now an active driver!\n\n"
            <<"thank you for your service\n\n"
            "~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~\n";
            driver.IncreaseBalance(pay.DriverPay(length));
            driver.IncreasePoint();
    }
    void DeleteCarRequest(int line){
        string s;
        int counter = 0;
        ifstream fileIn("CarRequest.txt");
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
            ofstream fileOut("CarRequest.txt");
            while(getline(tempIn,s)){
                fileOut << s << "\n";
            }
            tempIn.close();
            fileOut.close();
        }
        else{
             cerr<<"Something went Wrong!\n";
        }
        ofstream clearTemp("temp.txt",ios::trunc);
        clearTemp.close();
    }
    void ShowList(){
        int counter = 1;
        string name,inCord,fiCord;
        ifstream file("CarRequest.txt");
        if(file.is_open()){
            cout<<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n";
            file.seekg(0,ios::end);
            if(file.tellg() == 0){
                cout<<"No passanger has signed up yet!\n";
                file.close();
            }
            file.seekg(0);
            while(file >> name >> inCord >> fiCord){
                cout<<counter<<"."<<name<<" is wating in :"
                <<inCord<<" and wants to go :"<<fiCord<<" ---> its a "
                <<distance(inCord,fiCord)<<"km ride \n";
                counter++;
            }
            cout<<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n";
            file.close();
        }else{
            cerr<<"Cant open file and show list!\n";
        }
    }
};
class MainMenu{
public:
    MainMenu(){}
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
                    system("cls");
                    Passanger account;
                    account.CreateAccount("PassangerAccounts.txt");
                    cout<<"~ ~ ~ ~ Account Successfully Created ~ ~ ~ ~";
                    account.SaveData();
                    CarRequest _CarRequest(account);
                    _CarRequest.CarRequestMenu();
                    break;
                }
                case(2):{
                    system("cls");
                    SignIn account("PassangerAccounts.txt");
                    CarRequest _CarRequest(account);
                    _CarRequest.CarRequestMenu();
                    break;
                }
                case(0):{
                    system("cls");
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
                    system("cls");
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
                    Ride _Ride(account);
                    _Ride.RideMenu();
                    break;
                }
                case(2):{
                    system("cls");
                    SignIn account("DriverAccounts.txt");
                    Ride _Ride(account);
                    _Ride.RideMenu();
                    break;
                }
                case(0):{
                    system("cls");
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
                    system("cls");
                    admin.ShowPassangers();
                    break;
                }
                case(2):{
                    system("cls");
                    admin.ShowDrivers();
                    break;
                }
                case(3):{
                    system("cls");
                    admin.ShowDisscountList();
                    break;
                }
                case(4):{
                    system("cls");
                    admin.AddDisscount();
                    break;
                }
                case(5):{
                    system("cls");
                    admin.DeleteDisscount();
                    break;
                }
                case(0):{
                    system("cls");
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
                system("cls");
                start.PassangerMenu();
                break;
            }
            case(2):{
                system("cls");
                start.DriverMenu();
                break;
            }
            case(3):{
                system("cls");
                start.AdminMenu();
                break;
            }
            case(0):{
                system("cls");
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