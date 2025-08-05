#include "functions.hpp"

string USERNAME;
bool EXIT = false;

bool isName(string s);
bool isPassword(string s);

class Account{
protected:
    string username;
    string password;
public:
    bool checkUserExist(string username){
        bool exist = false;
        fstream file("Accounts.txt");
        if(file.is_open()){
            string u,p;
            while(file >> u >> p){
                if(u == username){
                    exist = true;
                    break;
                }
            }
            file.close();
        }else{
            cerr<<"Could not open file!\n";
        }
        if(exist)
            return true;
        return false;
    }
    void CreateFiles() const{
        fstream file1(USERNAME+"_TodoList.txt",ios::app);
        file1.close();
        fstream file2(USERNAME+"_Reminder.txt",ios::app);
        file2.close();
        fstream file3(USERNAME+"_ShopList.txt",ios::app);
        file3.close();
    }
    ~Account(){
        USERNAME = "";
    }
};
class Admin:public Account{
private:
    const string AdminPass = "AP41148";
public:
    Admin(){
        cout << "Enter Admin's PASSWORD :  ";
        while(true){
            cin>>password;
            if(!CheckAdminPass(password)){
                cout<<"password is wrong!\n"
                    <<"try again now :  ";
                continue;
            }
            break;
        }
        cout<<"~ ~ ~ ~ Successful login as Admin ~ ~ ~ ~\n";
        AdminMenu();
    }
    void AdminMenu(){
         bool loop = true;
        while(loop){
            cout<<"~ - ~ - ~ - ~ - ~ - ~\n"
                <<"1.See All Users\n"
                <<"2.Choose user to see their info\n"
                <<"3.Log out\n"
                <<"0.quit program\n"
                <<"~ - ~ - ~ - ~ - ~ - ~\n";
            int choice;
            cin >> choice;
            switch(choice){
                case (1):{
                    system("cls");
                    ShowUsers();
                    break;
                }
                case (2):{
                    system("cls");
                    cout<<"Enter an USERNAME :  ";
                    while(true){
                        string input;
                        cin >> input;
                        if(!checkUserExist(input)){
                            cout<<"USER does not Exist!\n"
                                <<"try again now :  ";
                        }
                        else{
                            USERNAME = input;
                            CreateFiles();
                            loop = false;
                            break;
                        }
                    }
                    break;
                }
                case (3):{
                    system("cls");
                    loop = false;
                    break;
                }
                case (0):{
                    system("cls");
                    EXIT = true;
                    loop = false;
                    break;
                }
                default :{break;}
            }
        }
    }
    void ShowUsers(){
        ifstream file("Accounts.txt");
        if(file.is_open()){
            int i = 1;
            cout<<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n"
                <<"USERNAME | PASSWORD\n";
            while(file >> username >> password){
                cout<<i<<"."<<username<<" "<<password<<"\n";
                i++;
            }
            cout<<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n";
            file.close();
        }else{
            cerr<<"Something went wrong!\n";
        }
    }
    bool CheckAdminPass(string pass) const{
        if(pass == AdminPass){
            return true;
        }
        return false;
    }
};
class SignUp:public Account{
public:
    SignUp(){
        string pass2;
        cout << "Enter your USERNAME :  ";
        cin.ignore();
        while(true){
            getline(cin,username);
            if(username.size() < 3){
                cout<<"USERNAME must atleast be 3 charachters long!\n"
                    <<"try again now :  ";
                continue;
            }
            if(!isName(username)){
                cout<<"Invalid Name!\n"
                    <<"first charachter must be a letter ('a'->'z' or 'A'->'Z')\n"
                    <<"you can use numbers ('0'->'9' and '.') in the middle\n"
                    <<"try again now :  ";
                continue;
            }
            if(checkUserExist(username)){
                cout<<"username : "<<username<<" is taken!\n"
                    <<"try again now :  ";
                continue;
            }
            cout<<"~ ~ ~ username : < "<<username<<" > Accepted ~ ~ ~\n";
            break;
        }
        cout << "Enter your PASSWORD :  ";
        cin.ignore();
        while(true){
            getline(cin,password);
            if(password.size() < 6){
                cout<<"PASSWORD must atleast be 6 charachters long!\n"
                    <<"try again now :  ";
                continue;
            }
            if(!isPassword(password)){
                cout<<"Invalid Password!\n"
                    <<"you can use letters ('a'->'z' or 'A'->'Z')\n"
                    <<"you can use symbols ('!' / '@' / '#' / '$' / '&' / '*')\n"
                    <<"and you can use numbers ('0'->'9' and '.')\n"
                    <<"try again now :  ";
                continue;
            }
            cout<<"reEnter your PASSWORD :  ";
            getline(cin,pass2);
            if(password != pass2){
                cout<<"PASSWORDs Don't match!\n"
                    <<"try again now :  ";
                continue;
            }
            cout<<"~ ~ ~ ~ PASSWORD Accepted ~ ~ ~ ~\n";
            break;
        }
        USERNAME = username;
        CreateFiles();
        ofstream file("Accounts.txt",ios::out | ios::app);
        if(file.is_open()){
            file << username << " " << password << "\n";
            file.close();
        }else{
            cerr<<"trouble saving data!\n";
        }
    }
};
class LogIn:public Account{
public:
    LogIn(){
        cout<<"Enter your USERNAME :  ";
        cin.ignore();
        while(true){
            getline(cin,username);
            if(!checkUserExist(username)){
                cout<<"This username does not exist!\n"
                    <<"try again now :  ";
                continue;
            }
            cout<<"Enter your PASSWORD :  ";
            getline(cin,password);
            if(!CheckAccountInfo(username,password)){
                cout<<"wrong username or password !\n"
                    <<"try again now :  ";
                continue;
            }
            break;
        }
        USERNAME = username;
        CreateFiles();
    }
    bool CheckAccountInfo(string user,string pass){
        bool exist = false;
        ifstream file("Accounts.txt");
        if(file.is_open()){
            while(file >> user >> pass){
                if(user == username && pass == password){
                    exist = true;
                    break;
                }
            }
            file.close();
        }else{
            cerr<<"Something went wrong!\n";
        }
        if(exist)
            return true;
        return false;
    }
};
class TaskBase{
public:
    virtual void ListMenu() = 0;
    virtual void AddItem() = 0;
    virtual void ShowItems() = 0;
    virtual void DeleteItem() = 0;
    virtual void MarkCompleted(int a) = 0;
    virtual ~TaskBase(){}
};
class TodoList:public TaskBase{
public:
    string t,s;
    TodoList(){}
    void ListMenu() override{
        bool loop = true;
        while(loop){
            cout<<"~ ~ ~ ~ ~ ~ TODO-LIST ~ ~ ~ ~ ~ ~\n"
                <<"1.Show My TODO-LIST\n"
                <<"2.Add a new Task to my List\n"
                <<"3.Delete an existing Task\n"
                <<"4.Mark a Task as Completed\n"
                <<"5.Back\n"
                <<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n";
            int choice;
            cin>>choice;
            switch(choice){
                case (1):{
                    system("cls");
                    this->ShowItems();
                    break;
                }
                case (2):{
                    system("cls");
                    this->AddItem();
                    break;
                }
                case (3):{
                    system("cls");
                    this->DeleteItem();
                    break;
                }
                case (4):{
                    system("cls");
                    cout << "Which task have you Completed ?  ";
                    int n;
                    cin >> n;
                    this->MarkCompleted(n);
                    break;
                }
                case (5):{
                    system("cls");
                    loop = false;
                    break;
                }
                default :{
                    cout <<"invalid option! try again :\n";
                    break;
                }
            }
        }
    }
    void AddItem() override{
        fstream file( USERNAME + "_TodoList.txt",ios::app);
        if(!file.is_open()){
            cerr<<"Something went wrong!\n";
        }
        else{
            cout<<"Enter your task : \n";
            cin.ignore();
            getline(cin,t);
            file << t << "\n";
            cout<< "~ ~ Task Succecfully added ~ ~\n";
        }
        file.close();
    }
    void ShowItems() override{
        int ul = 1;
        ifstream file ( USERNAME + "_TodoList.txt",ios::in);
        if(!file.is_open()){
            cerr<<"Semething went wrong!\n";
        }
        else{
            cout<<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n";
            file.seekg(0,ios::end);
            if(file.tellg() == 0){
                cout<<"Your List is Empty!\n";
            }
            file.seekg(0);
            while(getline(file,t)){
                if(t[t.size()-1] == '1'){
                    cout<<ul<<".[";
                    for(int i = 0; i < t.size()-2 ;i++){
                       cout<<t[i];
                    }
                    cout<<"] Done.\n";
                    ul++;
                    continue;
                }
                cout<<ul<<"."<<t<<"\n";
                ul++;  
            }
            cout<<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n";
        }
        file.close();
    }
    void DeleteItem() override{
        int line,counter = 0;
        cout<<"Which TASK you want to DELETE?('0' to see list / '-1' to go back)\n";
        cin >> line;
        if(line == 0){
            this->ShowItems();
            cout<<"Which TASK you want to DELETE?('0' to see list / '-1' to go back)\n";
            cin >> line;
        }
        if(line == -1){
            system("cls");
        }
        else{
            ifstream fileIn(USERNAME + "_TodoList.txt");
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
            ofstream fileOut(USERNAME + "_TodoList.txt");
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
    void MarkCompleted(int a) override{
        int counter = 1;
        ifstream fileIn(USERNAME + "_TodoList.txt");
        ofstream tempOut("temp.txt");
            if(fileIn.is_open() && tempOut.is_open()){
                while(getline(fileIn,s)){
                        tempOut << s << "\n";
                }
            fileIn.close();
            tempOut.close();
            ifstream tempIn("temp.txt");
            ofstream fileOut(USERNAME + "_TodoList.txt");
            while(getline(tempIn,s)){
                if(counter == a){
                    fileOut << s << " 1\n";
                    counter++;
                    continue;
                }
            fileOut << s << "\n";
            counter++;
            }
            tempIn.close();
            fileOut.close();
            }
            else{
                cerr<<"Something went Wrong!\n";
            }
        ofstream clearTemp("temp.txt",ios::trunc);
        clearTemp.close();
        cout << "~ ~ Succecfuly marked as Completed ~ ~\n";
    }
};
class Reminder:public TaskBase{
private:
    time_t now = time(nullptr);
    int day;
    int hour;
    int minute;
    void RemainingTime(int a){
        day = 0;
        hour = 0;
        minute = 0;
        now = time(nullptr);
        a = now - a;
        while(a >= 88400){
            a-= 88400;
            day++;
        }
        while(a >= 3600){
            a-=3600;
            hour++;
        }
        while(a >= 60){
            a -= 60;
            minute++;
        }
        cout << " | Days : "<<day << " Hours : "<<hour << " Minutes : "<< minute << " Seconds : " << a << endl;
    }
public:
    string t,s;
    Reminder(){}
    void ListMenu() override{
        bool loop = true;
        while(loop){
            cout<<"~ ~ ~ ~ ~ ~ REMINDER ~ ~ ~ ~ ~ ~\n"
                <<"1.Show My Reminder LIST\n"
                <<"2.Add a new Reminder to my List\n"
                <<"3.Delete an existing Reminder\n"
                <<"4.Mark a Task as Completed\n"
                <<"5.Back\n"
                <<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n";
            int choice;
            cin>>choice;
            switch(choice){
                case (1):{
                    system("cls");
                    this->ShowItems();
                    break;
                }
                case (2):{
                    system("cls");
                    this->AddItem();
                    break;
                }
                case (3):{
                    system("cls");
                    this->DeleteItem();
                    break;
                }
                case (4):{
                    system("cls");
                    cout << "Which task have you Completed ?  ";
                    int n;
                    cin >> n;
                    this->MarkCompleted(n);
                    break;
                }
                case (5):{
                    system("cls");
                    loop = false;
                    break;
                }
                default :{
                    cout <<"invalid option! try again :\n";
                    break;
                }
            }
        }
    }
    void AddItem() override{
        fstream file( USERNAME + "_Reminder.txt",ios::app);
        if(!file.is_open()){
            cerr<<"Something went wrong!\n";
        }
        else{
            cout<<"Enter your task : \n";
            cin.ignore();
            getline(cin,t);
            file << now << "|" << t << "\n";
            cout<< "~ ~ Reminder Succecfully added ~ ~\n";
        }
        file.close();
    }
    void ShowItems() override{
        int ul = 1;
        ifstream file ( USERNAME + "_Reminder.txt",ios::in);
        if(!file.is_open()){
            cerr<<"Semething went wrong!\n";
        }
        else{
            cout<<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n";
            file.seekg(0,ios::end);
            if(file.tellg() == 0){
                cout<<"Your List is Empty!\n";
            }
            file.seekg(0);
            while(getline(file,t)){
                bool swich = false;
                string n;
                for(int i = 0 ; i < t.size() ; i++){
                    if(t[i] == '|'){
                        swich = true;
                        continue;
                    }
                    if(!swich){
                        n+=t[i];
                    }
                    else{
                        cout << t[i];
                    }
                }
                RemainingTime(stoi(n));                
            }
            cout<<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n";
        }
        file.close();
    }
    void DeleteItem() override{
        int line,counter = 0;
        cout<<"Which TASK you want to DELETE?('0' to see list / '-1' to go back)\n";
        cin >> line;
        if(line == 0){
            this->ShowItems();
            cout<<"Which TASK you want to DELETE?('0' to see list / '-1' to go back)\n";
            cin >> line;
        }
        if(line == -1){
            system("cls");
        }
        else{
            ifstream fileIn(USERNAME + "_Reminder.txt");
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
            ofstream fileOut(USERNAME + "_Reminder.txt");
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
    void MarkCompleted(int a) override{
    }
};
class ShopList:public TaskBase{
private:
    int price;
public:
    string t,s;
    ShopList(){}
    void ListMenu() override{
        bool loop = true;
        while(loop){
            cout<<"~ ~ ~ ~ ~ ~ Shopping-LIST ~ ~ ~ ~ ~ ~\n"
                <<"1.Show My Shopping List\n"
                <<"2.Add a new Item to my List\n"
                <<"3.Delete an existing Item\n"
                <<"4.All Price Sum\n"
                <<"5.Back\n"
                <<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n";
            int choice;
            cin>>choice;
            switch(choice){
                case (1):{
                    system("cls");
                    this->ShowItems();
                    break;
                }
                case (2):{
                    system("cls");
                    this->AddItem();
                    break;
                }
                case (3):{
                    system("cls");
                    this->DeleteItem();
                    break;
                }
                case (4):{
                    system("cls");
                    this->AllCosts();
                    break;
                }
                case (5):{
                    system("cls");
                    loop = false;
                    break;
                }
                default :{
                    cout <<"invalid option! try again :\n";
                    break;
                }
            }
        }
    }
    void AddItem() override{
        fstream file( USERNAME + "_ShopList.txt",ios::app);
        if(!file.is_open()){
            cerr<<"Something went wrong!\n";
        }
        else{
            cout<<"What you want to buy Next ?\n";
            cin.ignore();
            getline(cin,t);
            cout<<"What's it's Price ?\n";
            cin >> price ;
            file << price << "|" << t << '\n';
            cout<< "~ ~ ShopList Succecfully Updated ~ ~\n";
        }
        file.close();
    }
    void ShowItems() override{
        int ul = 1;
        ifstream file ( USERNAME + "_ShopList.txt",ios::in);
        if(!file.is_open()){
            cerr<<"Semething went wrong!\n";
        }
        else{
            cout<<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n";
            file.seekg(0,ios::end);
            if(file.tellg() == 0){
                cout<<"Your List is Empty!\n";
            }
            file.seekg(0);
            while(getline(file,t)){
                cout<<ul++<<".";
                string n;
                int cost;
                bool start = false;
                for(int i = 0 ; i < t.size() ; i++){
                    if(t[i] == '|'){
                        start = true;
                        continue;
                    }
                    if(start){
                        cout<<t[i];
                    }
                    else{
                        n += t[i];
                    }
                }
                cost = stoi(n);
                cout << " : " << cost <<"$\n";
            }
            cout<<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n";
        }
        file.close();
    }
    void DeleteItem() override{
        int line,counter = 0;
        cout<<"Which TASK you want to DELETE?('0' to see list / '-1' to go back)\n";
        cin >> line;
        if(line == 0){
            this->ShowItems();
            cout<<"Which TASK you want to DELETE?('0' to see list / '-1' to go back)\n";
            cin >> line;
        }
        if(line == -1){
            system("cls");
        }
        else{
            ifstream fileIn(USERNAME + "_ShopList.txt");
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
            ofstream fileOut(USERNAME + "_ShopList.txt");
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
    void MarkCompleted(int a) override{
    }
    void AllCosts(){
        int cost = 0;
        ifstream file ( USERNAME + "_ShopList.txt",ios::in);
        if(file.is_open()){
            while(getline(file , s)){
                string n;
                for(int i = 0 ; i < s.size() ; i++){
                    if(s[i] == '|')
                        break;
                    n += s[i];
                }
                cost += stoi(n);
            }
            cout << "Your total COST is : "<<cost<<"$\n";
            file.close();
        }
        else{
            cerr<< "Cant Open File!\n";
        }
    }
};
class MainMenu{
public:
TaskBase* List[3];
MainMenu(){
        List[0] = new TodoList;
        List[1] = new Reminder;
        List[2] = new ShopList;
    }
void ClientMenu(){
    bool loop = true;
    while(loop){
        cout<<"~~~~~~~~~~~~~ Main Menu ~~~~~~~~~~~~~\n"
            <<"1.Go to my TODO-List Menu\n"
            <<"2.Go to my Reminder Menu\n"
            <<"3.Go to my Shopping List Menu\n"
            <<"4.Log Out\n"
            <<"0.quit program\n"
            <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        int choice;
        cin>>choice;
        switch(choice){
            case (1):{
                system("cls");
                List[0]->ListMenu();
                break;
            }
            case (2):{
                system("cls");
                List[1]->ListMenu();
                break;
            }
            case (3):{
                system("cls");
                List[2]->ListMenu();
                break;
            }
            case (4):{
                system("cls");
                loop = false;
                break;
            }
            case (0):{
                system("cls");
                EXIT = true;
                loop = false;
                break;
            }
            default :{
                cout <<"Invalid choice! try again :";
                break;
            }
        }
    }
}
void AdminMenu(){
    bool loop = true;
    while(loop){
            cout<<"~~~~~~~~~~~~~ Main Menu ~~~~~~~~~~~~~\n"
                <<"1.see user TODO-List Menu\n"
                <<"2.see user Reminder Menu\n"
                <<"3.see user Shopping List Menu\n"
                <<"4.Log Out\n"
                <<"0.quit program\n"
                <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            int choice;
            cin>>choice;
            switch(choice){
                case (1):{
                    system("cls");
                    List[0]->ShowItems();
                    break;
                }
                case (2):{
                    system("cls");
                    List[1]->ShowItems();
                    break;
                }
                case (3):{
                    system("cls");
                    List[2]->ShowItems();
                    break;
                }
                case (4):{
                    system("cls");
                    loop = false;
                    break;
                }
                case (0):{
                    system("cls");
                    EXIT = true;
                    loop = false;
                    break;
                }
                default :{
                    cout <<"Invalid choice! try again :";
                    break;
                }
            }
        }   
}
~MainMenu(){
    delete List[0];
    delete List[1];
    delete List[2];
}
};
int main(){
    Account* account;
    MainMenu start;
    while(!EXIT){
        cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
            <<"1.Create New Account\n"
            <<"2.Log into Existing Account\n"
            <<"3.Administrator Login\n"
            <<"0.quit program\n"
            <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        int choice;
        cin>>choice;
        switch (choice){
            case (1):{ 
                account = new SignUp;
                system("cls");
                start.ClientMenu();
                delete account;     
                break;
            }
            case (2):{
                account = new LogIn;
                system("cls");
                start.ClientMenu();
                delete account;     
                break;
            }
            case (3):{
                account = new Admin;
                system("cls");
                if(USERNAME != ""){
                    start.AdminMenu();
                }
                delete account;
                break;
            }
            case (0):{
                system("cls");
                cout << "Closing Program!";
                return 0;
                break;
            }
            default:{
                cout << "Invalid Choice, try again now :\n";
                break;
            }
        }
    }
    cout <<"closing program!";
    return 0;
}
