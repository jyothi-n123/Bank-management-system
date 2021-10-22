/* 
 Bank Management System 
 Author : N.Jyothi
 Date : 19-10-2021 																
*/

/*------------------------------------------------- Source Code -------------------------------------------------------------------------------------*/

#include<iostream>		//necessary header files are included 
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;
	
class account		//class account which stores variables like  name,account number, bank type, amount in the account
{
        int accountnumber;
        char name[50];
        int deposit;
        char bankType;
		public:		//operations declared here in public mode 
	        void create_account();
	        void get_report();
	        void show_account();
	        int get_accountnumber();
	        void modify_account();
	        char get_accounttype();
	        void deposit_amount(int);
	        void draw_amount(int);  	            
	        int get_amount();       	        
};       
 
void account::create_account()		//method to create a account for new customer
{
        cout<<"\nEnter the account Number: ";
        cin>>accountnumber;
        cout<<"\nEnter the Name of The account Holder : ";
        cin.ignore();
        cin.getline(name,50);
        cout<<"\nEnter account type (enter 's' for saving or 'c' for credit): ";
        cin>>bankType;
        bankType=toupper(bankType);
        cout<<"\nEnter The Initial amount\n(500 or more for Saving and 1000 or more for current ): ";
        cin>>deposit;
        cout<<"\n\n\nAccount Created Successfully...";
}
 
void account::show_account()		//display account details
{
        cout<<"\nAccount Number: "<<accountnumber;
        cout<<"\nAccount Holder Name: "<<name;
        cout<<"\nType of Account: "<<bankType;
        cout<<"\nBalance amount: "<<deposit;
}
 
void account::modify_account()		//method for account modification
{
        cout<<"\nAccount Number: "<<accountnumber;
        cout<<"\nModify Account Holder Name: ";
        cin.ignore();
        cin.getline(name,50);
        cout<<"\nModify Type of Account: ";
        cin>>bankType;
        bankType=toupper(bankType);
        cout<<"\nModify Balance amount: ";
        cin>>deposit;
}
 
void account::deposit_amount(int x)		//method for depositing amount
{
        deposit+=x;
}     
 
void account::draw_amount(int x)		//method for withdrawing amount
{
        deposit-=x;
}       
 
void account::get_report()	//method to extract the record 
{
        cout<<left<<setw(15)<<accountnumber<<left<<setw(15)<<name<<left<<setw(10)<<bankType<<left<<setw(10)<<deposit<<endl;
}
 
int account::get_accountnumber()
{
        return accountnumber;
}
 
int account::get_amount()
{
        return deposit;
}
 
char account::get_accounttype()
{
        return bankType;
}
 
void write_account();
void deposit_withdraw(int, int); 
void check_balance(int); 
void display_all();  
void delete_account(int);
void modify_account(int);           

 
 
int main()
{
        char option;
        int num;
        for(;;)		//this keeps on running until user gives exit option 
        {
 				cout<<"\n\t\t--------------------------------------------------\n";
                cout<<"\n\t\tPress 1 to Create New Account";
                cout<<"\n\t\tPress 2 to Deposit Amount";
                cout<<"\n\t\tPress 3 to Withdraw Amount";
                cout<<"\n\t\tPress 4 to Check Balance";
                cout<<"\n\t\tPress 5 to View All Account Holders";
                cout<<"\n\t\tPress 6 to Close an Account";
                cout<<"\n\t\tPress 7 to Modify an Account";
                cout<<"\n\t\tPress 8 to Exit the process";
 				cout<<"\n\t\t--------------------------------------------------\n";
                cout<<"\n\t\tEnter your Option here : ";
                cin>>option;
                system("cls");
                switch(option)
                {
                case '1':
                system("color 02");
                        write_account();
                        break;
                case '2':
                system("color 03");
                        cout<<"\n\n\tEnter The account No. : "; cin>>num;
                        deposit_withdraw(num, 1);
                        break;
                case '3':
                system("color 06");
                        cout<<"\n\n\tEnter The account No. : "; cin>>num;
                        deposit_withdraw(num, 2);
                        break;
                case '4':
                system("color 08");
                        cout<<"\n\n\tEnter The account No. : "; cin>>num;
                        check_balance(num);
                        break;
                case '5':
                system("color 9");
                        display_all();
                        break;
                case '6':
                system("color 10");
                        cout<<"\n\n\tEnter The account No. : "; cin>>num;
                        delete_account(num);
                        break;
                 case '7':
                 system("color 11");
                        cout<<"\n\n\tEnter The account No. : "; cin>>num;
                        modify_account(num);
                        break;
                 case '8':
                 system("color 04");
                        cout<<"\n\n\tThanks for using Bank Management System";
                        break;
                 default :
				    cout<<"\nInvalid Option\n";
                }
                cin.ignore();
                cin.get();             
                if(option=='8')
                break;
        }
        return 0;
}
 
void write_account()
{
        account ac; 		//object for class 'account' is created
        ofstream outFile;
        outFile.open("account.dat",ios::binary|ios::app);
        ac.create_account();
        outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
        outFile.close();
}
 
void check_balance(int n)
{
        account ac;
        bool flag=false;
        ifstream inFile;
        inFile.open("account.dat",ios::binary);
        if(!inFile)
        {
                cout<<"File could not be open !! Press any Key...";
                return;
        }
        cout<<"\nBALANCE DETAILS\n";
 
        while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
        {
                if(ac.get_accountnumber()==n)
                {
                       ac.show_account();
                        flag=true;
                }
        }
        inFile.close();
        if(flag==false)
                cout<<"\n\nAccount number does not exist";
}
 
void modify_account(int n)
{
        bool found=false;
        account ac;
        fstream File;
        File.open("account.dat",ios::binary|ios::in|ios::out);
        if(!File)
        {
                cout<<"File could not be open !! Press any Key...";
                return;
        }
        while(!File.eof() && found==false)
        {
                File.read(reinterpret_cast<char *> (&ac), sizeof(account));
                if(ac.get_accountnumber()==n)
                {
                        ac.show_account();
                        cout<<"\n\nEnter The New Details of account: "<<endl;
                        ac.modify_account();
                        int pos=(-1)*static_cast<int>(sizeof(account));
                        File.seekp(pos,ios::cur);
                        File.write(reinterpret_cast<char *> (&ac), sizeof(account));
                        cout<<"\n\n\t Record Updated...";
                        found=true;
                  }
        }
        File.close();
        if(found==false)
                cout<<"\n\n Record Not Found ";
}
 
void delete_account(int n)
{
        account ac;
        ifstream inFile;
        ofstream outFile;
        inFile.open("account.dat",ios::binary);
        if(!inFile)
        {
                cout<<"File could not be open !! Press any Key...";
                return;
        }
        outFile.open("Temp.dat",ios::binary);
        inFile.seekg(0,ios::beg);
        while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
        {
                if(ac.get_accountnumber()!=n)
                {
                        outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
                }
        }
 
        inFile.close();
        outFile.close();
        remove("account.dat");
        rename("Temp.dat","account.dat");
        cout<<"\n\n\tAccount Deleted...";
}
 
void display_all()
{
        account ac;
        ifstream inFile;
        inFile.open("account.dat",ios::binary);
        if(!inFile)
        {
                cout<<"File could not be open !! Press any Key...";
                return;
        }
 
        cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
        cout.setf(ios::right,ios::adjustfield);
        cout<<"====================================================\n";
        cout<<left<<setw(15)<<"Account No."<<left<<setw(15)<<"Name"<<left<<setw(10)<<"Type"<<left<<setw(10)<<"Balance"<<endl;
        cout<<"====================================================\n";
        while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
        {
            ac.get_report();
        }
        inFile.close();
}
 
void deposit_withdraw(int n, int option)
{
        int amt;
        bool found=false;
        account ac;
        fstream File;
        File.open("account.dat", ios::binary|ios::in|ios::out);
        if(!File)
        {
                cout<<"File could not be open !! Press any Key...";
                return;
        }
        while(!File.eof() && found==false)
        {
                File.read(reinterpret_cast<char *> (&ac), sizeof(account));
                if(ac.get_accountnumber()==n)
                {
                       ac.show_account();
                        if(option==1)
                        {
                                cout<<"\n\nEnter The amount to be deposited: ";
                                cin>>amt;
                                ac.deposit_amount(amt);
                        }
                        if(option==2)
                        {
                                cout<<"\n\nEnter The amount to be withdraw: ";
                                cin>>amt;
                                int bal=ac.get_amount()-amt;
                                if((bal<500 && ac.get_accounttype()=='S') || (bal<1000 && ac.get_accounttype()=='C'))
                                        cout<<"Insufficience balance";
                                else
                                        ac.draw_amount(amt);
                        }
                        int pos=(-1)*static_cast<int>(sizeof(ac));
                        File.seekp(pos,ios::cur);
                        File.write(reinterpret_cast<char *> (&ac), sizeof(account));
                        cout<<"\n\n\t Record Updated";
                        found=true;
               }
         }
        File.close();
        if(found==false)
                cout<<"\n\n Record Not Found ";
}
