#include <iostream>
#include <fstream>
using namespace std;

string USERNAME;

class User{
    protected:
    string username;
    string password;
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
                password = p;
                loop = false;
            }
        }
        }
    }
    bool checkUserExist(string t){
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
    bool CheckAccountInfo(string s,string t){
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
    ~User(){
        delete this;
    }
};
  
class TaskBase{
    public:
    virtual void ShowInfo() = 0;
    virtual void AddItem() = 0;
    virtual void DeleteItem() = 0;
    virtual ~TaskBase(){}
};
class TodoList : public TaskBase{
    private:
    string t;
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
            if(file){
                cout<<"Your List is Empty!\n";
            }
            while(getline(file,t)){
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
            cout<< "Task Succecfully added! \n";
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
            fstream file(USERNAME + "TodoList.txt",ios::in | ios::out);
            fstream temp("temp.txt",ios::in | ios::out);
            if((file.is_open()) && (temp.is_open())){

                while(getline(file,s)){
                    counter++;
                    if(line == counter){
                        continue;
                    }
                    temp << s << "\n";
                }
                file.seekg(0);
                while(getline(temp,s)){
                    file << s << "\n";
                }
            }
            else{
                cerr<<"Something went Wrong!\n";
                }
           file.close();
        }
    }

    ~TodoList(){
        delete this;
    }
};
class Reminder : public TaskBase{
    private:
    string name;
    int CreationDate;
    int ExpireDate;
    public:
    void ShowInfo() override{

    }
    void AddItem() override{

    }
    void DeleteItem() override{

    }
};
class ShopList : public TaskBase{
    private:
    int price;
    string name;
    public:
    void ShowInfo() override{

    }
    void AddItem() override{

    }
    void DeleteItem() override{

    }
};


int main(){
    TaskBase* Task[3];
    Task[0] = new TodoList;
    Task[1] = new Reminder;
    Task[2] = new ShopList;
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
        <<"1.Create New Account\n"
        <<"2.Log into Existing Account\n"
        <<"0.quit program\n"
        <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    bool loop = true;
    while(loop){
        int choice;
        cin>>choice;
        switch (choice){
            case (1):{
                User* uTemp = new User(0);
                loop = false;
                break;
            }
            case (2):{
                User* uTemp = new User(1);
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
                        <<"4.Back\n"
                        <<"0.quit program\n"
                        <<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n";
                    int choice1;
                    cin>>choice1;
                    switch(choice1){
                        case (1):{
                            Task[0]->ShowInfo();
                            break;
                        }
                        case (2):{
                           Task[0]->AddItem();
                           break;
                        }
                        case (3):{
                            Task[0]->DeleteItem();
                            break;
                        }
                        case (4):{
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
                        <<"2.Add a new Task to my List\n"
                        <<"3.Delete an existing Task\n"
                        <<"4.Back\n"
                        <<"0.quit program\n"
                        <<"~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n";
                    int choice1;
                    cin>>choice1;
                    switch(choice1){
                        case (1):{
                            Task[1]->ShowInfo();
                            break;
                        }
                        case (2):{
                           Task[1]->AddItem();
                           break;
                        }
                        case (3):{
                            Task[1]->DeleteItem();
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
                            Task[2]->ShowInfo();
                            break;
                        }
                        case (2):{
                           Task[2]->AddItem();
                           break;
                        }
                        case (3):{
                            Task[2]->DeleteItem();
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
                main();
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
    return 0;
}