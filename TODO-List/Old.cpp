#include <iostream>
#include <fstream>
using namespace std;

string USERNAME;

class Account{
    protected:
    string username;
    string password;
    public:
    virtual bool checkUserExist(string t) = 0;
    virtual bool CheckAccountInfo(string s,string t) = 0;
    virtual ~Account(){}
};
class Admin : public Account{
    private:
    const int id = 41148;
    public:
    Admin(){
        while(1){
        cout<<"~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~\n"
            <<"Enter Admin ID :('0' to go back)\n";
        int n;
        cin>>n;
        if(n == -1){
            break;
        }
        if(n == id){
            cout<<"Succecfully Loged in as Admin\n";
            break;
        }
        else{
            cout<<"Invaild input, try again now :\n";
        }
        }
    }
    void ShowUers(){
        string s,t;
        int counter = 0;
        ifstream file("Accounts.txt",ios::in);
        if(!file.is_open()){
            cerr<<"Something Wrong!\n";
        }else{
            cout << "Username | password\n\n";
            while(file >> s >> t){
                counter++;
                cout<<counter<<"."<<s<<" : "<<t<<"\n";
            }
            cout<<"choose one to see thier info :('0' to go back)\n";
            int n;
            cin>>n;
            if(n<0 || n>counter){
                cout<<"out of range! going back\n";
            }
            else if(n == 0){
            }
            else{
                this->UserInfo(n);
            }
        }
        file.close();
    }
    void UserInfo(int a){
        int counter = 0;
        string s,t;
        ifstream file("Accounts.txt",ios::in);
        if(!file.is_open()){
            cerr<<"Smt wrong!\n";
        }
        else{
            while(file >> s >> t){
                counter++;
                if(counter == a){
                    USERNAME = s;
                }
            }
        }
        file.close();
    }
    bool checkUserExist(string t) override{
    return true;
    }
    bool CheckAccountInfo(string s,string t) override{
   return true;
    }  
};
class User:public Account{
    public:
    User(){}
    User(bool Account){
        if(!Account){
    string u;
    string p;
    string p2;
    bool loop = true;
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
        <<"Enter Your USERNAME:    ";
        while(loop){
        cin>>u;
        if(u.size() < 3){
            cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
                <<"USERNAME at least must be 3 letters!!\n"
                <<"try again now :    ";
        }
        else if(!isName(u)){
                cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
                <<"Invalid USERNAME!your USERNAME must strat with a letter (A-Z or a-z)\n"
                <<"and you can use Numbers(0-9) or (.) in the middle if you want\n"
                <<"try again now :    ";
        }
        else if(!checkUserExist(u)){
             cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
                <<"USERNAME already taken!\n"
                <<"try again now :    ";
        }
        else{
            cout<<"USERNAME Accepted !\n";
            loop = false;
        }
        }
        cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
            <<"Enter Your PASSWORD:    ";
        loop = true;
        while(loop){
            cin>>p;
            cout<<"re-Enter Your PASSWORD: ";
            cin>>p2;
            if(p.size() < 6){
                cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
                <<"PASSWORD at least must be 6 letters!!\n"
                <<"try again now :    ";
            }
            else if(!isPassword(p)){
                    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
                    <<"Invalid PASSWORD! you can use letters(A-Z or a-z) and \n"
                    <<"Numbers(0-9) and Symbols(! / @ / # / . / & / *)\n"
                    <<"try again now :    ";
            }
            else if(p != p2){
                    cout<<"PASSWORDs Don't match ! \n"
                        <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
                        <<"Enter Your PASSWORD:    ";
            }
            else{
                cout<<"PASSWORD Accepted !\n"
                    <<"~ ~ ~ Account Succecfully Created ~ ~ ~\n";
                loop = false;
            }
            }
            CreateAccount(u,p); 
        }
        else{
        bool loop = true;
        while(loop){
            string u,p;
            cout<<"Enter your USERNAME :    ";
            cin>>u;
            cout<<"Enter your PASSWORD :    ";
            cin>>p;
            if(!CheckAccountInfo(u,p)){
                cout<<"Wrong USERNAME or PASSWORD! try again:\n";
            }
            else{
                cout<<"~ ~ ~ Succecfully Loged in ~ ~ ~\n";
                username = u;
                USERNAME = u;
                fstream file1(USERNAME + "_TodoList.txt",ios::app);
                file1.close();
                fstream file2(USERNAME + "_Reminders.txt",ios::app);
                file2.close();
                fstream file3(USERNAME + "_ShopList.txt",ios::app);
                file3.close();
                password = p;
                loop = false;
            }
        }
        }
    }
    bool checkUserExist(string t) override{
        string s1,s2;
        ifstream file("Accounts.txt");
        if(!file.is_open()){
        cerr<<"Something Went wrong!\n";
        }
        else{
            while(file >> s1 >> s2){
                if(s1 == t){
                    return false;
                }
            }
        }
        file.close();
    return true;
    }
    void CreateAccount(string a,string b){
        username = a;
        USERNAME = a;
        fstream file1(USERNAME + "_TodoList.txt",ios::app);
        file1.close();
        fstream file2(USERNAME + "_Reminders.txt",ios::app);
        file2.close();
        fstream file3(USERNAME + "_ShopList.txt",ios::app);
        file3.close();
        password = b;
        fstream file("Accounts.txt",ios::app);
        if(file.is_open()){
            file<<username<<" "<<password<<"\n";
        }
        else{
            cerr<<"could not open file!\n";
        }
        file.close();
    } 
    bool CheckAccountInfo(string s,string t) override{
        ifstream file("Accounts.txt");
        string fileUser,filePass;
        if(!file.is_open()){
            cerr<<"Something Went wrong!\n";
        }
        else{
            while(file >> fileUser >> filePass){
                if(fileUser == s && filePass == t){
                    return true;
                }
            }
        }
    file.close();
    return false;
}  
bool isName(string s){
    if((s[0] >= '0' && s[0] <= '9') || (s[0] == '.')){
        return false;
    }
    for(int i =0; i < s.size();i++){    
        if(!((s[i] >= 'A' && s[i] <= 'Z') 
        || (s[i] >= 'a' && s[i] <= 'z')
        || (s[i] >= '0' && s[i] <= '9')
        || (s[i] == '.'))){
            return false;
        }
    }
    return true;
}
bool isPassword(string s){
     for(int i =0; i < s.size();i++){    
        if(!((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z')
        || (s[i] >= '0' && s[i] <= '9') || (s[i] == '.')
        || (s[i] == '!') || (s[i] == '@') || (s[i] == '#')
        || (s[i] == '&') || (s[i] == '*') )){
            return false;
        }
    }
    return true;
}
};
  
class TaskBase{
    public:
    virtual void ShowInfo() = 0;
    virtual void AddItem() = 0;
    virtual void DeleteItem() = 0;
    virtual void Completed(int n) = 0;
    virtual ~TaskBase(){}
};
class TodoList : public TaskBase{
    private:
    string t;
    bool completed = false;
    public:
    TodoList(){}
    void ShowInfo() override{
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
    void DeleteItem() override{
        int line,counter = 0;
        string s;
        cout<<"Which TASK you want to DELETE?('0' to see list / '-1' to go back)\n";
        cin >> line;
        if(line == 0){
            this->ShowInfo();
            cout<<"Which TASK you want to DELETE?('0' to see list / '-1' to go back)\n";
            cin >> line;
        }
        if(line == -1){

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
    void Completed(int n) override{
        string s;
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
                if(counter == n){
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
class Reminder : public TaskBase{
    private:
    string t;
    int CreationDate;
    int ExpireDate;
    public:
    void ShowInfo() override{
        int ul = 1;
        ifstream file ( USERNAME + "_Reminders.txt",ios::in);
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
                cout<<ul<<"."<<t<<"\n";
                ul++;  
            }
            cout<<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n";
        }
        file.close();
    }
    void AddItem() override{
        fstream file( USERNAME + "_Reminders.txt",ios::app);
        if(!file.is_open()){
            cerr<<"Something went wrong!\n";
        }
        else{
            cout<<"Enter your new Reminder : \n";
            cin.ignore();
            getline(cin,t);
            file << t << "\n";
            cout<< "~ ~ Reminder Succecfully added ~ ~\n";
        }
        file.close();   
    }
    void DeleteItem() override{
    
        int line,counter = 0;
        string s;
        cout<<"Which REMINDER you want to DELETE?('0' to see list / '-1' to go back)\n";
        cin >> line;
        if(line == 0){
            this->ShowInfo();
            cout<<"Which REMINDER you want to DELETE?('0' to see list / '-1' to go back)\n";
            cin >> line;
        }
        if(line == -1){
            
        }
        else{
            ifstream fileIn(USERNAME + "_Reminders.txt");
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
            ofstream fileOut(USERNAME + "_Reminders.txt");
            while(getline(tempIn,s)){
                fileOut << s << "\n";
            }
            cout<<"# # # Reminder succecfully deleted! # # #\n";
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
    void Completed(int n) override{}
};
class ShopList : public TaskBase{
    private:
    float price;
    string t;
    public:
    void ShowInfo() override{
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
                cout<<ul<<"."<<t<<"\n";
                ul++;  
            }
            cout<<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n";
        }
        file.close();
    }
    void AddItem() override{
        fstream file( USERNAME + "_ShopList.txt",ios::app);
        if(!file.is_open()){
            cerr<<"Something went wrong!\n";
        }
        else{
            cout<<"Enter your new Item : \n";
            cin.ignore();
            getline(cin,t);
            cout<<"What's it's Price ? \n";
            cin >> price;
            file << t <<" "<<price<< "$\n";
            cout<< "~ ~ Item Succecfully added ~ ~\n";
        }
        file.close();      
    }
    void DeleteItem() override{
        int line,counter = 0;
        string s;
        cout<<"Which ITEM you want to DELETE?('0' to see list / '-1' to go back)\n";
        cin >> line;
        if(line == 0){
            this->ShowInfo();
            cout<<"Which ITEM you want to DELETE?('0' to see list / '-1' to go back)\n";
            cin >> line;
        }
        if(line == -1){

        }
        else{
            ifstream fileIn(USERNAME + "_ShopList.txt");
            ofstream tempOut("temp.txt");
            if((fileIn.is_open()) && (tempOut.is_open())){
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
            cout<<"# # # ITEM succecfully deleted! # # #\n";
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
    void Completed(int n) override{}
};
int main(){
    TaskBase* List[3];
    List[0] = new TodoList;
    List[1] = new Reminder;
    List[2] = new ShopList;
    while(1){
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
        <<"1.Create New Account\n"
        <<"2.Log into Existing Account\n"
        <<"3.Administrator Login\n"
        <<"0.quit program\n"
        <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    bool loop = true;
    while(loop){
        int choice;
        cin>>choice;
        switch (choice){
            case (1):{
                Account* uTemp = new User(0);
                delete uTemp;
                loop = false;
                break;
            }
            case (2):{
                Account* uTemp = new User(1);
                delete uTemp;
                loop = false;
                break;
            }
            case (3):{
                bool adLoop = true;
                Admin* adminstrator = new Admin();
                while(adLoop){
                    cout<<"~ - ~ - ~ - ~ - ~ - ~\n"
                        <<"1.See All Users\n"
                        <<"2.Log out\n"
                        <<"0.quit program\n"
                        <<"~ - ~ - ~ - ~ - ~ - ~\n";
                    int choice;
                    cin>>choice;
                    switch(choice){
                        case(1):{

                            bool adminLoop = true;
                            adminstrator->ShowUers();
                            while(adminLoop){
                                 cout<<"~ - ~ - ~ - ~ - ~ - ~\n"
                                    <<"1.Show User Todo-List\n"
                                    <<"2.Show User Reminders\n"
                                    <<"3.Show User Shop List\n"
                                    <<"4.Go Back\n"
                                    <<"0.quit program\n"
                                    <<"~ - ~ - ~ - ~ - ~ - ~\n";
                                    int choice;
                                    cin>>choice;
                                    switch(choice){
                                        case(1):{
                                            string t;
                                            int ul = 0;
                                            cout<<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n";
                                            cout<<USERNAME<<" Todo-List:\n";
                                            ifstream file(USERNAME + "_TodoList.txt",ios::in);
                                            if(!file.is_open()){
                                                cerr<<"something went wrong!\n";
                                            }
                                            else{
                                                while(getline(file,t)){
                                                    ul++;
                                                    cout<<ul<<"."<<t<<"\n";
                                                }
                                                cout<<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n";
                                            }
                                            file.close();
                                            break;
                                        }
                                        case(2):{
                                            string t;
                                            int ul = 0;
                                            cout<<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n";
                                            cout<<USERNAME<<" Reminder List:\n";
                                            ifstream file(USERNAME + "_Reminders.txt",ios::in);
                                            if(!file.is_open()){
                                                cerr<<"something went wrong!\n";
                                            }
                                            else{
                                                while(getline(file,t)){
                                                    ul++;
                                                    cout<<ul<<"."<<t<<"\n";
                                                }
                                                cout<<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n";
                                            }
                                            file.close();
                                            break;
                                        }
                                        case(3):{
                                            string t;
                                            int ul = 0;
                                            cout<<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n";
                                            cout<<USERNAME<<" Shopping List:\n";
                                            ifstream file(USERNAME + "_ShopList.txt",ios::in);
                                            if(!file.is_open()){
                                                cerr<<"something went wrong!\n";
                                            }
                                            else{
                                                while(getline(file,t)){
                                                    ul++;
                                                    cout<<ul<<"."<<t<<"\n";
                                                }
                                                cout<<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n";
                                            }
                                            file.close();
                                            break;
                                        }
                                        case(4):{
                                            adminLoop= false;
                                            break;
                                        }
                                        case(0):{
                                            cout<<"\nClosing Program... bye bye!";
                                            return 0;
                                        }
                                        default:{
                                            cout<<"Invalid Input! try again now :\n";
                                            break;
                                        }
                                    }
                                }
                            break;
                        }
                        case(2):{
                            adLoop = false;
                            break;
                        }
                        case(0):{
                            cout<<"\nClosing Program... bye bye!";
                            return 0;
                        }
                    }
                }
                loop = false;
                break;
            }
            case (0):{
                cout<<"\nClosing Program... bye bye!";
                return 0;
            }
            default:{
                cout<<"Invalid Option! choose between (1 / 2 / 0) :\n";
                break;
            }

        }
    }
    loop = true;
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
                bool loop1 = true;
                while(loop1){
                    cout<<"~ ~ ~ ~ ~ ~ TODO-LIST ~ ~ ~ ~ ~ ~\n"
                        <<"1.Show My TODO-LIST\n"
                        <<"2.Add a new Task to my List\n"
                        <<"3.Delete an existing Task\n"
                        <<"4.Mark a Task as Completed\n"
                        <<"5.Back\n"
                        <<"0.quit program\n"
                        <<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n";
                    int choice1;
                    cin>>choice1;
                    switch(choice1){
                        case (1):{
                            List[0]->ShowInfo();
                            break;
                        }
                        case (2):{
                           List[0]->AddItem();
                           break;
                        }
                        case (3):{
                            List[0]->DeleteItem();
                            break;
                        }
                        case (4):{
                            cout << "Which task have you Completed ?  ";
                            int n;
                            cin >> n;
                            List[0]->Completed(n);
                            break;
                        }
                        case (5):{
                            loop1 = false;
                            break;
                        }
                        case (0):{
                            cout<<"\nClosing Program... bye bye!";
                            return 0;
                        }
                    }
                }
                break;
            }
            case (2):{
                bool loop2 = true;
                while(loop2){
                    cout<<"~ ~ ~ ~ ~ ~ REMINDER ~ ~ ~ ~ ~ ~\n"
                        <<"1.Show My Reminder LIST\n"
                        <<"2.Add a new Reminder to my List\n"
                        <<"3.Delete an existing Reminder\n"
                        <<"4.Back\n"
                        <<"0.quit program\n"
                        <<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n";
                    int choice1;
                    cin>>choice1;
                    switch(choice1){
                        case (1):{
                            List[1]->ShowInfo();
                            break;
                        }
                        case (2):{
                           List[1]->AddItem();
                           break;
                        }
                        case (3):{
                            List[1]->DeleteItem();
                            break;
                        }
                        case (4):{
                            loop2 = false;
                            break;
                        }
                        case (0):{
                            cout<<"\nClosing Program... bye bye!";
                            return 0;
                        }
                    }
                }
                break;
            }
            case (3):{
                bool loop3 = true;
                while(loop3){
                    cout<<"~ ~ ~ ~ ~ ~ Shopping-LIST ~ ~ ~ ~ ~ ~\n"
                        <<"1.Show My Shopping List\n"
                        <<"2.Add a new Item to my List\n"
                        <<"3.Delete an existing Item\n"
                        <<"4.Back\n"
                        <<"0.quit program\n"
                        <<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n";
                    int choice1;
                    cin>>choice1;
                    switch(choice1){
                        case (1):{
                            List[2]->ShowInfo();
                            break;
                        }
                        case (2):{
                           List[2]->AddItem();
                           break;
                        }
                        case (3):{
                            List[2]->DeleteItem();
                            break;
                        }
                        case (4):{
                            loop3 = false;
                            break;
                        }
                        case (0):{
                            cout<<"\nClosing Program... bye bye!";
                            return 0;
                        }
                    }
                }
                break;
            }
            case (4):{
                loop = false;
                break;
            }
            case (0):{
                cout<<"\nClosing Program... bye bye!";
                return 0;
            }
            default:{
                cout<<"Invalid choice! try again: \n";
                break;
            }
        }
    }
}   
    delete List[0];
    delete List[1];
    delete List[2];
    return 0;
}