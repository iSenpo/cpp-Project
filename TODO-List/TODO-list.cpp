#include <iostream>
#include <fstream>
using namespace std;

class User{
    private:
    string username;
    string password;
    public:
    User(string a,string b): username(a), password(b){
        fstream file("UserInfo.txt", ios::in | ios::out | ios::app);
        if(file.is_open()){
            file<<"\n"<<username<<" "<<password;
        }
        else{
            cerr<<"could not open file!";
        }
        file.close();
    };
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
    string t = "";
    bool checked;
    public:
    void ShowInfo() override{

    }
    void AddItem() override{

    }
    void DeleteItem() override{

    }
};
class Reminder : public TaskBase{
    private:
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
    public:
    void ShowInfo() override{

    }
    void AddItem() override{

    }
    void DeleteItem() override{

    }
};
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
void CreateAccount(){
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
    new User(u,p);
}
void Login(){
    string u,p;
    cout<<"Enter your USERNAME :    ";
    cin>>u;
}
bool CheckAccountInfo(){
    fstream file("UserInfo.txt", ios::in);
    string t = "";
    if(!file.is_open()){
        cerr<<"Something Went wrong!";
    }
    else{
        getline(file,t);
    }
    return true;
}
void MainMenu(){
     cout<<"~~~~~~~~~~~~~ Main Menu ~~~~~~~~~~~~~~~\n"
        <<"1.Go to my TODO-List Menu\n"
        <<"2.Go to my Reminder Menu\n"
        <<"3.Go to my Shoping List Menu\n"
        <<"0.quit program\n"
        <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}
int main(){
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
        <<"1.Create New Account\n"
        <<"2.Log into Existing Account\n"
        <<"0.quit program\n"
        <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        bool Stopit = true;
    while(Stopit){
        int choice;
        cin>>choice;
        switch (choice){
            case (1):{
               CreateAccount();
               Stopit = false;
               break;
            }
            case (2):{
                Login();
                Stopit = false;
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
    
    return 0;
}