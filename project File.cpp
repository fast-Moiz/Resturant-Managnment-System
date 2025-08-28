//============================================================================
// Name        : cpp.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include<iostream>
#include<fstream>
#include <sstream>
#include <limits>
#include<string>
#include<iomanip>
#include <ctime>
using namespace std;

string getDateTime() {
    time_t now=time(0);
    tm* ltm=localtime(&now);

    ostringstream oss;
    oss<<"["
        <<1900 + ltm->tm_year << "-"
        <<setw(2)<<setfill('0')<<ltm->tm_mon + 1 << "-"
        <<setw(2)<<setfill('0')<<ltm->tm_mday << " | "
        <<setw(2)<<setfill('0')<<ltm->tm_hour << ":"
        <<setw(2)<<setfill('0')<<ltm->tm_min << ":"
        <<setw(2)<<setfill('0')<<ltm->tm_sec
        << "]";

    return oss.str();
}
void AddLogToFile(string line1)
{
	ifstream checkFile("Logs.txt");
	bool isEmpty = checkFile.peek() == ifstream::traits_type::eof();
	checkFile.close();
	ofstream file("Logs.txt", ios::app);
	if (file.is_open())
	{
	  if (isEmpty) {
		  file << "Logs "<<endl;
		  file<<"Time || Action"<<endl;
		 file<<endl;
		 file<<endl;
			     }

	  	  file<<getDateTime()<<"||"<<line1<<"\n";
			 file.close();

			  }
}
void Sale(string line1)
{
	ifstream checkFile("sale.txt");
	bool isEmpty = checkFile.peek() == ifstream::traits_type::eof();
	checkFile.close();
	ofstream file("sale.txt", ios::app);
	if (file.is_open())
	{
	  if (isEmpty) {
		  file << "sale "<<endl;
		  file<<"Time || Action"<<endl;
		 file<<endl;
		 file<<endl;
			     }

	  	  file<<getDateTime()<<"||"<<line1<<"\n";
			 file.close();

			  }
}
bool Loginchecking(string targetusername, string targetpassword,string role)
{
	if(role=="manager")
	{
		role="Manager";
	}
	else if(role=="chef")
	{
		role="Chef";
	}
	else if(role=="seller")
	{
		role="Seller";
	}
	else if(role=="admin")
	{
		role="Admin";
	}

	string filename;
	filename=role+".txt";
	 ifstream inFile(filename);
	 string line;
	 bool check=0;
	 int lineNumber = 0;

	 while (getline(inFile, line) && check==0)
	 {
			        lineNumber++;

			        stringstream ss(line);
			        string username, password;

			        getline(ss, username, ',');
			        getline(ss, password, '\n');
			        if(targetusername==username && password==targetpassword)
			        {
			        	AddLogToFile(username+"  Login SuccessFully ");
			        	cout<<setw(50)<<"";
			        	cout<<"   Successfully Log In "<<endl;
			        	check=1;

			        }

			    }
	 inFile.close();
	 if(check==0)
	 {
		 cout<<setw(50)<<"";
		 AddLogToFile(targetusername+"  Attemped  a log-in (Failed) ");
		 cout<<"\t  Invalid Credentials"<<endl;
	 }
return check;
}

class User
{
protected:
	string UserName;
	string password;
	string Role;
public:
	User(string name,string pass, string rol)
	{
		UserName=name;
		password=pass;
		Role=rol;
	}
	virtual void ShowMenuPage() =0;
	virtual ~User()
		{
			UserName="";
			password="";
			Role="";
		}

};
class StockChanger
{
public:

	void updateStock(int itemID, int stockChange,string username) {
	    ifstream inFile("Menu.txt");
	    string line, updatedData = "";
	    cout<<setw(43)<<"";
		cout << "+----------------------+----------------------+" << endl;
		 cout<<setw(43)<<"";
		cout << "+----------------Updating Stock---------------+" << endl;
	    bool found = false;
	    int lineNumber=0;

	    while (getline(inFile, line))
	    {
	    	lineNumber++;
	        if(lineNumber<=4)
	        {
	            updatedData+=line+"\n";
	            continue;
	        }
	        if (line.empty())
	        	continue;

	        stringstream ss(line);
	        string id, name, priceStr, stockStr, category;

	        getline(ss, id, ',');
	        getline(ss, name, ',');
	        getline(ss, priceStr, ',');
	        getline(ss, stockStr, ',');
	        getline(ss, category, ',');
	        int id1=stoi(id);
	        if (id1 == itemID)
	        {
	            int currentStock=stoi(stockStr);
	            int newStock=currentStock+stockChange;

	            if(newStock<0)
	            	newStock = 0;
	            AddLogToFile(username+" Changed the "+name+" Stock "+to_string(newStock));
	            line=id+","+name+","+priceStr+","+to_string(newStock)+","+category;
	            found = true;
	        }

	        updatedData += line + "\n";
	    }

	    inFile.close();

	    ofstream outFile("Menu.txt");
	    outFile << updatedData;
	    outFile.close();

	    if(found)
	    {
	    	cout<<setw(53)<<"";
	        cout<<"Stock updated successfully.\n";
	    } else
	    {
	    	cout<<setw(53)<<"";
	        cout<<"Item ID not found.\n";
	    }
	    cout<<setw(43)<<"";
	    cout << "+----------------------+----------------------+" << endl;
	}
	int getstock(int itemID, int stockChange,string username) {
		    ifstream inFile("Menu.txt");
		    string line, updatedData = "";
		    int lineNumber=0;

		    while (getline(inFile, line))
		    {
		    	lineNumber++;
		        if(lineNumber<=4)
		        {
		            updatedData+=line+"\n";
		            continue;
		        }
		        if (line.empty())
		        	continue;

		        stringstream ss(line);
		        string id, name, priceStr, stockStr, category;

		        getline(ss, id, ',');
		        getline(ss, name, ',');
		        getline(ss, priceStr, ',');
		        getline(ss, stockStr, ',');
		        getline(ss, category, ',');
		        int id1=stoi(id);
		        if (id1 == itemID)
		        {
		            int currentStock=stoi(stockStr);
		            int newStock=currentStock+stockChange;

		            return newStock;

		        }

		        updatedData += line + "\n";
		    }

		    inFile.close();

		    ofstream outFile("Menu.txt");
		    outFile << updatedData;
		    outFile.close();
		    return 0;

		}
};
class Admin : public User , public StockChanger
{
public:
	Admin(string username="",string pass="", string role="") : User(username,pass, role)
	{
		this->Role="Admin";
	}
	void ViewLog()
	{
		 cout<<setw(33)<<"";
		cout << "+-----------------------------+------------------------------------------+" << endl;
		 cout<<setw(33)<<"";
		cout << "+------------- --------Viewing Logs--------------------------------------+" << endl;
		 ifstream inFile("Logs.txt");
		 string line;
		 int lineNumber = 0;
		 while (getline(inFile, line))
		 {
				        lineNumber++;

				        stringstream ss(line);
				        string line1;

				        getline(ss,line1, '\n');
				        cout<<setw(43)<<"";
				        cout<<line1<<endl;

				    }
		 inFile.close();
		 cout<<endl;
		 cout<<endl;
		 cout<<setw(33)<<"";
		cout << "+-----------------------------+------------------------------------------+" << endl;
	}
	void ShowMenuPage()
	{
		 cout<<setw(43)<<"";
		cout << "+----------------------+----------------------+" << endl;
		 cout<<setw(43)<<"";
		cout << "+-------------------Menu Page-----------------+" << endl;
		AddLogToFile(UserName+" Visted the Menu page ");
		int option;
		while(option!=6)
		{

		cout<<setw(53)<<"";
		cout<<"Enter options (1 to 6) :\n"
		<<setw(53)<<""<<"1.Add new employee \n"
		<<setw(53)<<""<<"2.Remove the employee \n"
		<<setw(53)<<""<<"3.View the employee list \n"
		<<setw(53)<<""<<"4.View the activity log \n"
		<<setw(53)<<""<<"5.Stock changer\n"
		<<setw(53)<<""<<"6.Exit  ";
		cin>>option;
		cin.ignore();
		if(option==1)
		{
			AddEmploye();
		}
		else if (option==2)
		{
			RemoveEmploye();

		}
		else if(option==3)
		{
			Employlist();
			AddLogToFile(UserName+" Viewed the Employ list");
		}
		else if(option==4)
		{
			ViewLog();
			AddLogToFile(UserName+" Viewed the Logs ");
		}
		else if(option==5)
		{
			int id;
			int stock;
			cout<<setw(53)<<"";
			cout << "+----------------------+----------------------+" << endl;
			cout<<setw(53)<<"";
			cout<<"Enter the Id number : ";
			cin>>id;
			cout<<setw(53)<<"";
			cout<<"Enter the Stock Number : ";
			cin>>stock;
			updateStock(id,stock,this->Role);


		}
		}
		AddLogToFile(UserName+" Existed the Menu page ");
		 cout<<setw(43)<<"";
		cout << "+----------------------+----------------------+" << endl;

	}
	bool Login(string targetusername="",string targetpassword="",string role="")
	{
	if(role.length()<2)
	{

	cout<<setw(60);
	cout<<"\tEnter the Username ";
	cin>>targetusername;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	cout<<setw(60);
	cout<<"\tEnter the Password ";
	cin>>targetpassword;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	}
	if(Loginchecking(targetusername,targetpassword,this->Role)==1)
	{
		this->UserName=targetusername;
		this->password=targetpassword;

		 cout<<setw(43)<<"";
		cout << "+----------------------+----------------------+" << endl;

		return 1;
	}
	return 0;
	}
	void Employlist()
	{
		cout<<setw(43)<<"";
	    cout << " +----------------------+----------------------+" << endl;
	    cout<<setw(43)<<"";
	    cout << " |     Username         |      Password        |" << endl;
	    cout<<setw(43)<<"";
	    cout << " +----------------------+----------------------+" << endl;

		 ifstream inFile("Manager.txt");
		 string line;
		 int lineNumber = 0;
		 cout<<setw(43)<<"";
		 cout<<" |--Manager"<<endl;
		 while (getline(inFile, line))
		 {
				        lineNumber++;

				        stringstream ss(line);
				        string username, password;

				        getline(ss, username, ',');
				        getline(ss, password, '\n');
				        if(lineNumber>=5)
				        {
				        	cout<<setw(43)<<"";
				            cout << " | " << left << setw(20) << username
				                 << "| " << left << setw(21) << password << " |" << endl;
				        }

				    }
		 inFile.close();
		 ifstream inFile1("Chef.txt");
		 cout<<setw(43)<<"";
		 cout<<" |--Chef"<<endl;
		 string line1;
		 int lineNumber1 = 0;
		 while (getline(inFile1, line1))
		 {
				        lineNumber1++;

				        stringstream ss(line1);
				        string username, password;

				        getline(ss, username, ',');
				        getline(ss, password, '\n');
				        if(lineNumber1>=5)
				        {
				        	cout<<setw(43)<<"";
				            cout << " | " << left << setw(20) << username
				                 << "| " << left << setw(21) << password << " |" << endl;
				        }


				    }
		 inFile1.close();
		 ifstream inFile2("Seller.txt");
		 cout<<setw(43)<<"";
		 cout<<" |--Seller"<<endl;
		 string line2;
		 int lineNumber2 = 0;
		 while (getline(inFile2, line2))
		 {
				        lineNumber2++;

				        stringstream ss(line2);
				        string username, password;

				        getline(ss, username, ',');
				        getline(ss, password, '\n');
				        if(lineNumber2>=5)
				        {
				        	cout<<setw(43)<<"";
				            cout << " | " << left << setw(20) << username
				                 << "| " << left << setw(21) << password << " |" << endl;
				        }

				    }
				    inFile2.close();


				    cout<<setw(43)<<"";
				    cout << "+----------------------+----------------------+" << endl;
					 cout<<setw(43)<<"";
					cout << "+----------------------+----------------------+" << endl;

	}
	void RemoveEmploye()
	{
		string targetUsername;
		string password;
		string role;
		 cout<<setw(43)<<"";
		cout << "+----------------------+----------------------+" << endl;
		 cout<<setw(43)<<"";
		cout << "+--------------Removing Employe---------------+" << endl;
		cout<<setw(53)<<"";
		cout<<"Enter the username ";
		cin>>targetUsername;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout<<setw(53)<<"";
		cout<<"Enter the password ";
		cin>>password;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout<<setw(53)<<"";
		cout<<"Enter the role ";
		cin>>role;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if(role=="Manager" || role=="manager")
		{
		    ifstream inFile("Manager.txt");
		    ofstream outFile("temp.txt");
		    string line;
		    int lineNumber = 0;
		    bool found = false;

		    while (getline(inFile, line))
		    {
		        lineNumber++;

		        stringstream ss(line);
		        string username, password;

		        getline(ss, username, ',');
		        getline(ss, password, '\n');
		        if (lineNumber<=4) {
		            outFile<<line<<"\n";
		        }
		        else if (username !=targetUsername)
		        {
		            outFile<<username<<","<<password<<"\n";
		        } else
		        {
		            found = true;
		            AddLogToFile("SAD News "+UserName+"  Removed "+targetUsername+" as a "+"\'"+role+"\'");
		        }
		    }
		    inFile.close();
		    outFile.close();
		    remove("Manager.txt");
		    rename("temp.txt", "Manager.txt");

		    if(found)
		    {
		    	cout<<setw(50)<<"";
		        cout<<"User  "<<targetUsername <<"' removed from credentials.\n";
		    }
		    else
		    {
		    	cout<<setw(50)<<"";
		        cout<<"Username not found .\n";
		    }
		}
		else if(role=="chef" ||  role=="Chef")
		{
			 ifstream inFile("Chef.txt");
			 ofstream outFile("temp.txt");
					    string line;
					    int lineNumber = 0;
					    bool found = false;

					    while (getline(inFile, line))
					    {
					        lineNumber++;

					        stringstream ss(line);
					        string username, password;

					        getline(ss, username, ',');
					        getline(ss, password, '\n');
					        if (lineNumber<=4) {
					            outFile<<line<<"\n";
					        }
					        else if (username !=targetUsername)
					        {
					            outFile<<username<<","<<password<<"\n";
					        } else {
					            found = true;
					            AddLogToFile("SAD News "+UserName+"  Removed "+targetUsername+" as a "+"\'"+role+"\'");
					        }
					    }
					    inFile.close();
					    outFile.close();
					    remove("Chef.txt");
					    rename("temp.txt", "Chef.txt");

					    if(found)
					    {
					    	cout<<setw(50)<<"";
					        cout<<"User  "<<targetUsername <<"' removed from credentials.\n";
					    }
					    else
					    {
					    	cout<<setw(50)<<"";
					        cout<<"Username not found .\n";
					    }
		}
		else if(role=="seller" || role=="Seller")
		{
			 ifstream inFile("Seller.txt");
			ofstream outFile("temp.txt");
					    string line;
					    int lineNumber = 0;
					    bool found = false;

					    while (getline(inFile, line))
					    {
					        lineNumber++;

					        stringstream ss(line);
					        string username, password;

					        getline(ss, username, ',');
					        getline(ss, password, '\n');
					        if (lineNumber<=4) {
					            outFile<<line<<"\n";
					        }
					        else if (username !=targetUsername)
					        {
					            outFile<<username<<","<<password<<"\n";
					        } else {
					            found = true;
					        }
					    }
					    inFile.close();
					    outFile.close();
					    remove("Seller.txt");
					    rename("temp.txt", "Seller.txt");

					    if(found)
					    {
					    	cout<<setw(50)<<"";
					        cout<<"User  "<<targetUsername <<"' removed from credentials.\n";
					        AddLogToFile("SAD News "+UserName+"  Removed "+targetUsername+" as a "+"\'"+role+"\'");
					    }
					    else
					    {
					    	cout<<setw(50)<<"";
					        cout<<"Username not found after line 3.\n";

					    }
		}
		else
		{
			cout<<setw(50)<<"";
			cout<<"Username not found.\n";
		}
		 cout<<setw(43)<<"";
		cout << "+----------------------+----------------------+" << endl;

	}
	void AddEmploye()
	{
		 cout<<setw(43)<<"";
		cout << "+----------------------+----------------------+" << endl;
		 cout<<setw(43)<<"";
		cout << "+---------------Adding Employe----------------+" << endl;
		string username;
					string password;
					string role;
					cout<<setw(53)<<"";

					cout<<"Enter the username ";
					cin>>username;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');

					cout<<setw(53)<<"";
					cout<<"Enter the password ";
					cin>>password;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');

					cout<<setw(53)<<"";
					cout<<"Enter the role ";
					cin>>role;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					AddLogToFile(UserName+"  Added "+username+" as a "+"\'"+role+"\'");
					if(role=="Manager" || role=="manager")
					{
						ifstream checkFile("Manager.txt");
						    bool isEmpty = checkFile.peek() == ifstream::traits_type::eof();
						    checkFile.close();
						    ofstream file("Manager.txt", ios::app);
						    if (file.is_open())
						    {
						        if (isEmpty) {
						            file << "Manager Credentials"<<endl;
						            file<<"username,password"<<endl;
						            file<<endl;
						            file<<endl;
						        }

						        file<<username<<","<<password<<"\n";
						        file.close();
						        cout<<setw(50)<<"";
						        cout << "Credentials saved successfully.\n";
						    } else
						    {
						    	cout<<setw(50)<<"";
						        cout<<"Failed to open credentials.txt\n";
						    }
					}
					else if(role=="chef" ||  role=="Chef")
					{
						ifstream checkFile("Chef.txt");
						    bool isEmpty = checkFile.peek() == ifstream::traits_type::eof();
						    checkFile.close();
						    ofstream file("Chef.txt", ios::app);
						    if (file.is_open())
						    {
						        if (isEmpty) {
						            file << "Chef Credentials"<<endl;
						            file<<"username,password"<<endl;
						            file<<endl;
						            file<<endl;
						        }

						        file<<username<<","<<password<<"\n";
						        file.close();
						        cout<<setw(50)<<"";
						        cout << "Credentials saved successfully.\n";
						    } else
						    {
						    	cout<<setw(50)<<"";
						        cout<<"Failed to open credentials.txt\n";
						    }
					}
					else if(role=="seller" || role=="Seller")
					{
						ifstream checkFile("Seller.txt");
						    bool isEmpty = checkFile.peek() == ifstream::traits_type::eof();
						    checkFile.close();
						    ofstream file("Seller.txt", ios::app);
						    if (file.is_open())
						    {
						        if (isEmpty) {
						            file << "Seller Credentials"<<endl;
						            file<<"username,password"<<endl;
						            file<<endl;
						            file<<endl;
						        }

						        file<<username<<","<<password<<"\n";
						        file.close();
						        cout<<setw(50)<<"";
						        cout << "Credentials saved successfully.\n";
						    } else
						    {
						    	cout<<setw(50)<<"";
						        cout<<"Failed to open credentials.txt\n";
						    }
					}
					else
					{
						cout<<setw(50)<<"";
												        cout<<"Role Not Matched\n";
					}
					 cout<<setw(43)<<"";
					cout << "+----------------------+----------------------+" << endl;



	}
};
class Manager : public User , public StockChanger
{

public:
	Manager(string username="",string pass="", string role="") : User(username,pass, role)
	{
		this->Role="Manager";
	}

void ViewSale()
{
	 cout<<setw(33)<<"";
	cout << "+-----------------------------+------------------------------------------+" << endl;
	 cout<<setw(33)<<"";
	cout << "+------------- --------Viewing Sale Logs--------------------------------------+" << endl;
	 ifstream inFile("sale.txt");
	 string line;
	 int lineNumber = 0;
	 while (getline(inFile, line))
	 {
			        lineNumber++;

			        stringstream ss(line);
			        string line1;

			        getline(ss,line1, '\n');
			        cout<<setw(43)<<"";
			        cout<<line1<<endl;

			    }
	 inFile.close();
	 cout<<endl;
	 cout<<endl;
	 cout<<setw(33)<<"";
	cout << "+-----------------------------+------------------------------------------+" << endl;
}

	void ShowMenuPage()
	{

		 cout<<setw(43)<<"";
		cout << "+----------------------+----------------------+" << endl;
		 cout<<setw(43)<<"";
		cout << "+---------------Menu Page---------------------+" << endl;
		int option;
		while(option!=5)
		{
		cout<<setw(53)<<"";
		cout<<"Enter the following option \n"
		<<setw(53)<<""<<"1.Log in\n"
		<<setw(53)<<""<<"2.Add new Food Item\n"
		<<setw(53)<<""<<"3.Increasing the stock Value of existing Item\n";
		cout<<setw(53)<<"";
		cout<<"4.View the sale.txt\n";
		cout<<setw(53)<<"";
		cout<<"5.Exit";
		cin>>option;
		if(option==1)
		{
			Login();

		}
		else if(option==2)
		{
			AddNewFood();
		}
		else if(option==3)
		{
			 cout<<setw(43)<<"";
			cout << "+----------------------+----------------------+" << endl;
			 cout<<setw(43)<<"";
			cout << "+-----------Changin the Stock Value ----------+" << endl;
			int id;
			int stock;
			cout<<setw(53)<<"";
			cout<<"Enter the Id number ";
			cin>>id;
			cout<<setw(53)<<"";
			cout<<"Enter the Stock Number ";
			cin>>stock;
			updateStock(id,stock,this->Role);
		}
		else if(option==4)
		{
			ViewSale();
		}
		else if(option==5)
		{
			AddLogToFile("Exiting the Manager Menu ");
			cout<<setw(53)<<"";
			cout<<"Exiting Manager Menu"<<endl;
		}
		}
		 cout<<setw(43)<<"";
		cout << "+----------------------+----------------------+" << endl;

	}
	bool Login(string targetusername="",string targetpassword="",string role="")
	{
		 cout<<setw(43)<<"";
		cout << "+----------------------+----------------------+" << endl;
		 cout<<setw(43)<<"";
		cout << "+------------------Login Page ----------------+" << endl;
		if(role.length()<2)
		{
		cout<<setw(53)<<"";
		cout<<"Enter the username ";
		cin>>targetusername;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout<<setw(53)<<"";
		cout<<"Enter the password ";
		cin>>targetpassword;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		if(Loginchecking(targetusername,targetpassword,this->Role)==1)
		{
			this->UserName=targetusername;
			this->password=targetpassword;
			AddLogToFile(UserName+"  Login SuccessFully ");
			 cout<<setw(43)<<"";
			cout << "+----------------------+----------------------+" << endl;

			return 1;
		}
		 cout<<setw(43)<<"";
		 AddLogToFile(UserName+"  Invalid Password ");
		cout << "+----------------------+----------------------+" << endl;

		return 0;

	}
	int getLastID(const string& filename) {
	    ifstream file(filename);
	    string line, lastID = "0";

	    while (getline(file, line)) {
	        if (line.empty()) continue;


	        if (line[0] == ',') {
	            line = line.substr(1);
	        }

	        stringstream ss(line);
	        string id;
	        getline(ss, id, ',');


	        if (!id.empty()) {
	            lastID = id;
	        }
	    }
	    if(lastID=="idNumber")
	    {
	    	return 1;
	    }
	    return stoi(lastID);
	}
	void AddNewFood()
	{
		 cout<<setw(43)<<"";
		cout << "+----------------------+----------------------+" << endl;
		 cout<<setw(43)<<"";
		cout << "+---------------Adding A new Item ------------+" << endl;
		string ItemName,category;
		int price=-1,stock=-1;
		cout<<setw(53)<<"";
		cout<<"Enter the Item Name";
		cin>>ItemName;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		while(price<0)
		{
		cout<<setw(53)<<"";
		cout<<"Enter the Price ";
		cin>>price;
		}
		while(stock<0)
		{
			cout<<setw(53)<<"";
		cout<<"Enter the stock Value ";
		cin>>stock;
		}
		cout<<setw(53)<<"";
		cout<<"Enter the Category ";
		cin>>category;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		ifstream checkFile("Menu.txt");
		bool isEmpty = checkFile.peek() == ifstream::traits_type::eof();
		checkFile.close();
		ofstream file("Menu.txt", ios::app);
		if (file.is_open())
		{
		  if (isEmpty)
		  {
			   file << "Menu Credentials"<<endl;
			   file<<"idNumber,ItemName,Price,Stock,Category"<<endl;
			   file<<endl;
			   file<<endl;
		  }
				int id=(getLastID("Menu.txt"));

				AddLogToFile(UserName+" Added A New Item Having ID "+to_string(id)+" With Name "+ItemName+" Stock value "+to_string(stock));
		  	  file<<id<<","<<ItemName<<","<<price<<","<<stock<<","<<category<<"\n";
		  	  id++;
			  file.close();

			  cout<<setw(53)<<"";
			   cout << "Menu Credentials saved successfully.\n";

			} else
				 {
				cout<<setw(53)<<"";
		       cout<<"Failed to open credentials.txt\n";
				 }
		ofstream file1("Requests.txt", ios::app);
		if (file1.is_open())
		{

				int id1=(getLastID("Requests.txt"));
				id1++;
				if(category=="drink" || category=="Drink" || category=="Drinks")
				{
					file1<<id1<<","<<ItemName<<","<<price<<","<<stock<<","<<category<<","<<"ITem Have No recipie/n";
				}
				else
				{
					file1<<id1<<","<<ItemName<<","<<price<<","<<stock<<","<<category<<","<<"NoRecipie\n";
				}


			  file1.close();
			  cout<<setw(53)<<"";
			  AddLogToFile(UserName+" Requesta a Chef Departnment for Recipe of this Item  With Name "+ItemName+" Stock value "+to_string(stock));
			   cout << "Requests Credentials saved successfully.\n";

			} else
				 {
				cout<<setw(53)<<"";
		       cout<<"Failed to open credentials.txt\n";
		 }
		 cout<<setw(43)<<"";
		cout << "+----------------------+----------------------+" << endl;

	}


};
class Chef : public User
{
public:
	Chef(string username="",string pass="", string role="") : User(username,pass, role)
	{
		this->Role="Chef";
	}

	void ShowMenuPage()
	{
		 cout<<setw(43)<<"";
		cout << "+----------------------+----------------------+" << endl;
		 cout<<setw(43)<<"";
		cout << "+---------------Menu Page ------- ------------+" << endl;
		int option;
		while(option!=5)
		{
		cout<<setw(53)<<"";
		cout<<"Enter the following option (1 to 5) \n"
		<<setw(53)<<""<<"1.Log in\n"
		<<setw(53)<<""<<"2.Add the recipe of item\n"
		<<setw(53)<<""<<"3.Edit the Recipe\n"
		<<setw(53)<<""<<"4.View the recipies\n"
		<<setw(53)<<""<<"5.Exit";
		cin>>option;
		if(option==1)
		{
			if(Login()!=1)
			{
				cout<<setw(53)<<"";
				cout<<"Password or User name Incorrect "<<endl;
			}
		}
		else if(option==2)
		{
			AddRecipe();
		}
		else if(option==3)
		{
			string ID_ItemName;
			cout<<setw(40)<<"";
			cout<<"Enter the ID and Item Name in this format (ID.ItemaName) : ";
			cin>>ID_ItemName;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			editRecipe(ID_ItemName);
		}
		else if(option==4)
		{
			ViewAllItem();
		}
		}
		AddLogToFile(UserName+" Exit the Menu Page ");
		cout<<setw(43)<<"";
		cout << "+--------------Exiting-Menu Page--------------+" << endl;
		cout<<setw(43)<<"";
		cout << "+----------------------+----------------------+" << endl;
	}
	bool checkItemExists(const string& itemID, const string& itemName)
	{
		 ifstream inFile("Requests.txt");
			    string line, updatedData = "";
			    bool found = false;
			    int lineNumber=0;

			    while (getline(inFile, line))
			    {
			    	lineNumber++;

			        if (line.empty())
			        	continue;

			        stringstream ss(line);
			        string id, name, priceStr, stockStr, category,status;

			        getline(ss, id, ',');
			        getline(ss, name, ',');
			        getline(ss, priceStr, ',');
			        getline(ss, stockStr, ',');
			        getline(ss, category, ',');
			        getline(ss, status, '\n');
			        int id1=stoi(id);

			        if (id1 == stoi(itemID))
			        {
			        	if(status=="NoRecipie")
			        	{
			        		status="Done Recipie";
			        	}
			        	else
			        	{
			        		return 0;
			        	}

			            line=id+","+name+","+priceStr+","+stockStr+","+category+","+status;
			            found = true;
			        }

			        updatedData += line + "\n";
			    }

			    inFile.close();

			    ofstream outFile("Requests.txt");
			    outFile << updatedData;
			    outFile.close();

			    if(found)
			    {

			    	return 1;

			    } else
			    {
			    	cout<<setw(53)<<"";

			        cout<<"Item ID not found.\n";
			    }
			   return 0;

	}
	void ViewAllItem()
	{
		 cout<<setw(43)<<"";
		cout << "+----------------------+----------------------+" << endl;
		 cout<<setw(43)<<"";
		cout << "+--------------- --All Item------- ------------+" << endl;
	    ifstream file("Menu.txt");
	    string line;
	    int lineNumber = 0;
	    while (getline(file, line))
	    {
	        lineNumber++;
	        if (lineNumber <= 4)
	        	continue;

	        if (line.empty())
	        	continue;

	        stringstream ss(line);
	        string id, name, price, stock, category;

	        getline(ss, id, ',');
	        getline(ss, name, ',');
	        getline(ss, price, ',');
	        getline(ss, stock, ',');
	        getline(ss, category, '\n');
	        AllItemsWithRecipies(id,name,stock);
			 cout<<setw(43)<<"";
			cout << "+----------------------+----------------------+" << endl;
			AddLogToFile(UserName+" Viewd the Recipe List "+" #id No. ");


	    }
	    file.close();

	}
	void AddRecipe()
	{
		 cout<<setw(43)<<"";
		cout << "+----------------------+----------------------+" << endl;
		 cout<<setw(43)<<"";
		cout << "+---------------Adding the recipie------ -----+" << endl;
		string id;
		string Item_name;
		cout<<setw(53)<<"";
		cout<<"Etner the id number ";
		cin>>id;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout<<setw(53)<<"";
		cout<<"Etner the Item NAme";

		cin>>Item_name;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if(checkItemExists(id,Item_name)==1)
		{
			cout<<setw(53)<<"";
			cout<<"Match Found"<<endl;
			int steps=0;
			while(steps<=0)
			{
				cout<<setw(53)<<"";
			    cout<<"Enter the number of steps ";
			    cin>>steps;
			}

			ifstream checkFile("Recipes.txt");
			    bool isEmpty = checkFile.peek() == ifstream::traits_type::eof();
			    checkFile.close();
			    ofstream file("Recipes.txt", ios::app);
			    if (file.is_open())
			    {
			        if (isEmpty) {
			            file << "Recipes Credentials"<<endl;
			            file<<"Id Number. Item Name"<<endl;
			            file<<endl;
			            file<<endl;
			        }

			        file<<id<<"."<<Item_name;
			        file<<endl;
			        file<<endl;
			        int count;
			        string ingredients;
			        cout<<setw(53)<<"";
			        cout<<"Enter the number of Ingredients ";
			        cin>>count;
			        file<<"Ingredients."<<endl;
			        cin.ignore();
			        for(int i=1;i<=count;i++)
			        {
			        	ingredients="";
			        	cout<<setw(53)<<"";
			        	cout<<"Enter the Ingredients NO. "<<i<<" ";

			        	getline(cin,ingredients);
			        	file<<i<<"."<<ingredients<<"\n";
			        }
			        file<<".";


			 	    file<<endl;
			 	    file<<endl;
			 		file<<"Steps."<<endl;
			        for(int i=1;i<=steps;i++)
			        {
			        	string step="";
			        	cout<<setw(53)<<"";
			        	cout<<"Enter the Steps No. "<<i;
			        	getline(cin,step);
			    		file<<i<<"."<<step<<"\n";

			        }
			        file<<".";
			        file<<endl;
			        file.close();
			        AddLogToFile(UserName+" Added the Recipe of "+" #id No. "+id+" with Item Name "+Item_name);
			        cout<<setw(53)<<"";
			        cout << "Credentials saved successfully.\n";
			    } else
			    {
			    	cout<<setw(53)<<"";
			        cout<<"Failed to open credentials.txt\n";
			    }

		}
		else
		{
			cout<<setw(53)<<"";
			cout<<"Not found such item"<<endl;

		}
		 cout<<setw(43)<<"";
		cout << "+----------------------+----------------------+" << endl;



	}
	void editRecipe(const string& idAndName)
	{
		 cout<<setw(43)<<"";
		cout << "+----------------------+----------------------+" << endl;
		 cout<<setw(43)<<"";
		cout << "+--------------Editing the Recipe------------+" << endl;
	    ifstream inFile("Recipes.txt");
	    ofstream tempFile("temp.txt");

	    if (!inFile || !tempFile)
	    {
	    	cout<<setw(53)<<"";
	        cout << "Error opening file!" << endl;
	        return;
	    }

	    string line;
	    bool matchFound = false;
	    bool skippingOldContent = false;
	    bool insideTargetRecipe = false;

	    while (getline(inFile, line)) {
	        // Check if it's the matching recipe
	        if (!matchFound && line == idAndName) {
	            matchFound = true;
	            insideTargetRecipe = true;

	            tempFile<<line << endl;
	            cout<<setw(40)<<"";
	            cout<<"Enter new ingredients (type 'done' to finish):"<<endl;
	            tempFile<<"Ingredients."<<endl;
	            string input;
	            int count = 1;
	            while (true)
	            {
	            	cout<<setw(45)<<"";
	                cout<<count<<". ";
	                getline(cin, input);
	                if(input == "done")
	                	break;
	                tempFile<<count<<"."<<input<< endl;
	                count++;
	            }
	            tempFile<<"."<<endl;
	            cout<<setw(45)<<"";
	            cout << "Enter new steps (type 'done' to finish):"<<endl;
	            tempFile<<"Steps."<<endl;
	            count=1;
	            while(true)
	            {
	            	cout<<setw(45)<<"";
	                cout<<count<<". ";
	                getline(cin,input);
	                if (input == "done")
	                	break;
	                tempFile<<count<<"."<<input<<endl;
	                count++;
	            }
	            tempFile << "." << endl;

	            skippingOldContent = true;
	            continue;
	        }


	        if (skippingOldContent)
	        {
	            if (line == ".")
	            {
	                getline(inFile, line);
	                while (getline(inFile, line)) {
	                    if (line == ".") break;
	                }
	                skippingOldContent = false;
	            }
	            continue;
	        }

	        tempFile << line << endl;
	    }

	    inFile.close();
	    tempFile.close();

	    remove("Recipes.txt");
	    rename("temp.txt", "Recipes.txt");

	    if (matchFound)
	    {
	    	AddLogToFile(UserName+" Updated  the Recipe of "+" #id No.IteName "+idAndName);
	    	cout<<setw(53)<<"";
	        cout<<"Recipe updated successfully!"<<endl;
	    } else
	    {
	    	cout<<setw(53)<<"";
	        cout<<"Recipe with '"<<idAndName<< "' Do not exist."<< endl;
	    }
		 cout<<setw(43)<<"";
		cout << "+----------------------+----------------------+" << endl;

	}
	bool Login(string targetusername="",string targetpassword="",string role="")
	{
		 cout<<setw(43)<<"";
		cout << "+----------------------+----------------------+" << endl;
		 cout<<setw(43)<<"";
		cout << "+---------------Login Page------- ------------+" << endl;
	if(role.length()<2)
	{
	cout<<setw(53)<<"";
	cout<<"Enter the username ";
	cin>>targetusername;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout<<setw(53)<<"";
	cout<<"Enter the password ";
	cin>>targetpassword;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	if(Loginchecking(targetusername,targetpassword,this->Role)==1)
	{
		this->UserName=targetusername;
		this->password=targetpassword;
		AddLogToFile(UserName+"  Login SuccessFully ");
		return 1;
	}
	return 0;
	}
	void AllItemsWithRecipies(string id , string Item_Name,string stock)
	{


	    ifstream file("Recipes.txt");
	    string line;
	    int lineNumber = 0;
	    bool found=0;
	    int counter=0;
	    while (getline(file, line))
	    {

	        lineNumber++;
	        if (lineNumber <= 4)
	        	continue;

	        if (line.empty())
	        	continue;

	        stringstream ss(line);
	        string lin1, line2;

	        getline(ss, lin1, '.');
	        getline(ss, line2, '\n');
	        if(lin1==id && line2==Item_Name)
	        {
	        	found=1;

	        				cout<<setw(53)<<"";
	        	cout<<"Quatities is "<<stock<<endl;

	        }
	        if(found==1)
	        {
	        	cout<<setw(53)<<"";
	        	cout<<lin1<<"."<<line2<<endl;
	        	if(line2=="")
	        	{
	        		counter++;

	        	}
	        }
	        if(counter==2)
	        {
	        	found=0;
	        }


	    }
	    file.close();

	}



};
class Seller : public User , public StockChanger
{
public:
	Seller(string username="",string pass="", string role="") : User(username,pass, role)
	{
		this->Role="Seller";
	}

	void ShowMenuPage()
	{
		int option;
		while(option!=4)
		{
		 cout<<setw(43)<<"";
		cout << "+----------------------+----------------------+" << endl;
		 cout<<setw(43)<<"";
		cout << "+----------------Menu Page -------------------+" << endl;

		cout<<setw(53)<<"";
		cout<<"Enter the following option \n"
		<<setw(53)<<""<<"1.Log in\n";
		cout<<setw(53)<<""<<"2.View the Menu\n";
		cout<<setw(53)<<""<<"3.Generte the Invoices ";
		cout<<setw(53)<<""<<"4.Exit";
		cin>>option;
		if(option==1)
		{
			Login();
		}
		else if(option==2)
		{

			ShowMenuFromFile();
		}
		else if(option==3)
		{
			//GenerateInvoices();
		}
		 cout<<setw(43)<<"";
		cout << "+----------------------+----------------------+" << endl;
		}

	}
void ShowMenuFromFile()
{

string Customer_name;
	 cout<<setw(5)<<"";
	cout << "+-----------------------------------------------------------------+--------------------------------------------------+" << endl;
	 cout<<setw(5)<<"";
	cout << "+------------------------------------------------------------Menu Loading -------------------------------------------+" << endl;
    fstream file("Menu.txt");
    if (!file) {
        cout << "File not found!" << endl;
        return;
    }

    string line;

    // Header
    cout << left

         << setw(5)<<"|" <<setw(15) << "ID"
         << setw(15)<<""<<setw(15)  << "Item Name"
         << setw(10)<<"" <<setw(15) << "Price"
         << setw(10)<<"" <<setw(15) << "Stock"
         << setw(12)<<"" <<setw(15) << "Category"
		 <<"|"<<endl;


    for (int i = 0; i < 1 && getline(file, line); ++i);

    while (getline(file, line))
    {


        stringstream ss(line);
        string id, item, price, stock, category;

        getline(ss, id, ',');
        getline(ss, item, ',');
        getline(ss, price, ',');
        getline(ss, stock, ',');
        getline(ss, category, '\n');

        cout << left

             << setw(5)<<"|"  <<setw(15) << id
             << setw(15)<<"" <<setw(15) << item
             << setw(10)<<"" <<setw(15) << price
             << setw(10)<<"" <<setw(15) << stock
             << setw(12)<<"" <<setw(15) << category;
			 cout<<"|"<<endl;
    }
    int Option;
    cout<<setw(50)<<"";
	cout<<"Enter the Customer Name ";
	cin>>Customer_name;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
    ofstream file1("Invoices.txt", ios::app);
    if(file.is_open())
    {
	 file1<<Customer_name<<"."<<endl;
    }
    while(Option!=2)
    {
    	cout<<setw(45)<<""<<" Enter the 1 to order \n";
    	cout<<setw(45)<<""<<"Enter the 2 to Go back to Menu ";
    	cin>>Option;
    	if(Option==1)
    	{
    		 int id,stock=0;
    		 cout<<setw(45)<<""<<"Enter the Id to Ordered ";
    		 cin>>id;
    		  while(stock<=0)
    		  {
    		    cout<<setw(45)<<""<<"Enter the Number of Quantities ";
    		    cin>>stock;
    		    }
    		        stock=-1*stock;
    		        if(getstock(id,stock,UserName)<0)
    		        {
    		            cout<<setw(35)<<""<<" Stock Do have such Quantities "<<endl;
    		        }
    		        else
    		        {
    		            Sale(UserName+" orderd ID No "+to_string(id)+" Qnatites "+to_string(-1*stock));
    		            updateStock(id,stock,UserName);


						    if (file.is_open())
						    {
						    	file1<<id<<"."<<stock<<endl;


						        cout<<setw(50)<<"";
						        cout << "Credentials saved successfully.\n";
						    } else
						    {
						    	cout<<setw(50)<<"";
						        cout<<"Failed to open credentials.txt\n";
						    }

    		        }
        }


    	}
    file1.close();



cout<<endl;
cout<<endl;
    cout<<setw(5)<<"";

   	cout << "+-----------------------------------------------------------------+--------------------------------------------------+" << endl;
    file.close();
}

	bool Login(string targetusername="",string targetpassword="",string role="")
	{
		 cout<<setw(43)<<"";
		cout << "+----------------------+----------------------+" << endl;
		 cout<<setw(43)<<"";
		cout << "+----------------Login Page-------------------+" << endl;
	if(role.length()<2)
	{
		cout<<setw(53)<<"";
	cout<<"Enter the username ";
	cin>>targetusername;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout<<setw(53)<<"";
	cout<<"Enter the password ";
	cin>>targetpassword;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	if(Loginchecking(targetusername,targetpassword,this->Role)==1)
	{
		this->UserName=targetusername;
		this->password=targetpassword;
		AddLogToFile(UserName+"  Login SuccessFully ");
		 cout<<setw(43)<<"";
		cout << "+----------------------+----------------------+" << endl;
		return 1;
	}
	 cout<<setw(43)<<"";
	cout << "+----------------------+----------------------+" << endl;
	return 0;
	}

};
void LowerShape()
{
    cout<<"|";
    cout<<setw(137)<<""<<"|"<<endl;
    cout<<"|";
    cout<<setw(137)<<""<<"|"<<endl;

    cout<<"|";
    cout<<setw(137)<<""<<"|"<<endl;
    cout<<"|";
    cout<<setw(137)<<""<<"|"<<endl;

    cout<<"|";
    cout<<setw(137)<<""<<"|"<<endl;
    cout<<"|";
    cout<<setw(137)<<""<<"|"<<endl;

    cout<<"|";
    cout<<setw(137)<<""<<"|"<<endl;
    cout<<"|";
    cout<<setw(137)<<""<<"|"<<endl;
    cout<<" _________________________________________________________________________________________________________________________________________"<<endl;
    cout<<" *****************************************************************************************************************************************"<<endl;
    cout<<"\n\n\n\n\n\n";
}
void UpperShape()
{
	cout<<" _________________________________________________________________________________________________________________________________________"<<endl;
    cout<<"|";
    cout<<setw(137)<<""<<"|"<<endl;
    cout<<"|";
    cout<<setw(137)<<""<<"|"<<endl;

    cout<<"|";
    cout<<setw(137)<<""<<"|"<<endl;
    cout<<"|";
    cout<<setw(137)<<""<<"|"<<endl;

    cout<<"|";
    cout<<setw(137)<<""<<"|"<<endl;
    cout<<"|";
    cout<<setw(137)<<""<<"|"<<endl;

    cout<<"|";
    cout<<setw(137)<<""<<"|"<<endl;
    cout<<"|";
    cout<<setw(137)<<""<<"|"<<endl;
}
int main()
{
	Admin admin;
	Manager Manage;
	Chef chef;
	Seller sell;
	int Option;
	while(Option!=5)
	{
	 cout << "    ***     "<< "\t\t\t\t\t\t ______ "<< " __  __ "<< "  _____ \t\t\t\t\t\t    ***     \n";
	    cout << "  *     *   "<< "\t\t\t\t\t\t|  ____|"<< "|  \\/  |"<< " / ____|\t\t\t\t\t\t  *     *   \n";
	    cout << " *       *  "<< "\t\t\t\t\t\t| |__   "<< "| \\  / |"<< "| (___  \t\t\t\t\t\t *       *  \n";
	    cout << " *       *  "<< "\t\t\t\t\t\t|  __|  "<< "| |\\/| |"<< " \\___ \\ \t\t\t\t\t\t *       *  \n";
	    cout << "  *     *   "<< "\t\t\t\t\t\t| |     "<< "| |  | |"<< " ____) |\t\t\t\t\t\t  *     *   \n";
	    cout << "    ***     "<< "\t\t\t\t\t\t|_|     "<< "|_|  |_|"<< "|_____/ \t\t\t\t\t\t    ***     \n";
	    int Option;
	    cout<<" _________________________________________________________________________________________________________________________________________"<<endl;
	    cout<<"|";
	    cout<<setw(137)<<""<<"|"<<endl;
	    cout<<"|";
	    cout<<setw(137)<<""<<"|"<<endl;
	    cout<<"|";
	    cout<<setw(137)<<""<<"|"<<endl;
	    cout<<"|";
	    cout<<setw(60)<<""<<"HOME PAGE";
	    cout<<setw(68)<<""<<"|"<<endl;
	    cout<<"|";
	    cout<<setw(137)<<""<<"|"<<endl;
	    cout<<"|";
	    cout<<setw(137)<<""<<"|"<<endl;
	    cout<<"|";
	    cout<<setw(137)<<""<<"|"<<endl;
	    cout<<"|";
	    cout<<setw(59)<<"";
	    cout<<"Press (1 to 5) : ";
	    cout<<setw(61)<<""<<"|"<<endl;
	    cout<<"|";
	    cout<<setw(137)<<""<<"|"<<endl;
	    cout<<"|";
	    cout<<setw(59)<<""<<"1 . Admin";
	    cout<<setw(69)<<""<<"|"<<endl;
	    cout<<"|";
	    cout<<setw(59)<<""<<"2 . Manager";
	    cout<<setw(67)<<""<<"|"<<endl;
	    cout<<"|";
	    cout<<setw(59)<<""<<"3 . Chef";
	    cout<<setw(70)<<""<<"|"<<endl;
	    cout<<"|";
	    cout<<setw(59)<<""<<"4 . Seller";
	    cout<<setw(68)<<""<<"|"<<endl;
	    cout<<"|";
	    cout<<setw(59)<<""<<"5 . Exit    ";
	    cin>>Option;
	    LowerShape();
	    if(Option==1)
	    {
		    cout << "\t\t\t\t\t\t*****   ****   *   *   ***   *      * \n";
		    cout << "\t\t\t\t\t\t*   *   *   *  ** **    *    **    ** \n";
		    cout << "\t\t\t\t\t\t*****   *   *  * * *    *    * *  * *\n";
		    cout << "\t\t\t\t\t\t*   *   *   *  *   *    *    *  **  *\n";
		    cout << "\t\t\t\t\t\t*   *   ****   *   *   ***   *      *\n";
		    cout<<"\n";
		    UpperShape();
		    int opt1=0;
		    cout<<setw(63)<<""<<"Login "<<endl;
		    while(opt1==0 && admin.Login()==0 )
		    {
		    	cout<<setw(53)<<"";
		    	cout<<"Press 1 to Back & 0 to continue ";
		    	cin>>opt1;
		    }
		    LowerShape();
		    if(opt1==0)
		    {
		    cout << "\t\t\t\t\t\t*****   ****   *   *   ***   *      * \n";
		    cout << "\t\t\t\t\t\t*   *   *   *  ** **    *    **    ** \n";
		    cout << "\t\t\t\t\t\t*****   *   *  * * *    *    * *  * *\n";
		    cout << "\t\t\t\t\t\t*   *   *   *  *   *    *    *  **  *\n";
		    cout << "\t\t\t\t\t\t*   *   ****   *   *   ***   *      *\n";
		    cout<<"\n";
		    UpperShape();
		    cout<<setw(62)<<""<<"Login "<<endl;
		    admin.ShowMenuPage();
		    LowerShape();
		    }
	    }
	    else if(Option==2)
	    {
	        cout << "\t\t\t\t\t*   *   ***   *   *    ***    ******   *****   *****\n";
	        cout << "\t\t\t\t\t** **  *   *  **  *   *   *  *         *       *   * \n";
	        cout << "\t\t\t\t\t* * *  *****  * * *   *****  *  ****   *****   *  *  \n";
	        cout << "\t\t\t\t\t*   *  *   *  *  **   *   *   *    *   *       *   * \n";
	        cout << "\t\t\t\t\t*   *  *   *  *   *   *   *    *****   *****   *     * \n";
	        cout<<"\n";
	        UpperShape();
	        int opt1=0;
	        cout<<setw(62)<<""<<"Login "<<endl;
	        while(opt1==0 && Manage.Login()==0 )
	         {
	        	cout<<setw(53)<<"";
	        	cout<<"Press 1 to Back & 0 to continue ";
	        		cin>>opt1;
	        		    }
	        	 LowerShape();
	 		    if(opt1==0)
	 		    {
	 		        cout << "\t\t\t\t\t*   *   ***   *   *    ***    ******   *****   *****\n";
	 		        cout << "\t\t\t\t\t** **  *   *  **  *   *   *  *         *       *   * \n";
	 		        cout << "\t\t\t\t\t* * *  *****  * * *   *****  *  ****   *****   *  *  \n";
	 		        cout << "\t\t\t\t\t*   *  *   *  *  **   *   *   *    *   *       *   * \n";
	 		        cout << "\t\t\t\t\t*   *  *   *  *   *   *   *    *****   *****   *     * \n";
	 		        cout<<"\n";

	 		    UpperShape();

	 		  Manage.ShowMenuPage();
	 		    LowerShape();
	 		    }
	    }
	    else if(Option==3)
	    {
	        cout << "\t\t\t\t\t\t\t  ****  *   * **** ****  "<<endl;
	        cout << "\t\t\t\t\t\t\t *      *   * *    *    "<<endl;
	        cout << "\t\t\t\t\t\t\t*       ***** **** ****  "<<endl;
	        cout << "\t\t\t\t\t\t\t *      *   * *    *      "<<endl;
	        cout << "\t\t\t\t\t\t\t  ****  *   * **** *      "<<endl;
	        cout<<"\n";
	        UpperShape();
	        int opt1=0;
	        cout<<setw(62)<<""<<"Login "<<endl;
	        while(opt1==0 && chef.Login()==0 )
	         {
	        	cout<<setw(53)<<"";
	        	cout<<"Press 1 to Back & 0 to continue ";
	        		cin>>opt1;
	        		    }
	        	 LowerShape();
	    		    if(opt1==0)
		    {
		        cout << "\t\t\t\t\t\t\t  ****  *   * **** ****  "<<endl;
		        cout << "\t\t\t\t\t\t\t *      *   * *    *    "<<endl;
		        cout << "\t\t\t\t\t\t\t*       ***** **** ****  "<<endl;
		        cout << "\t\t\t\t\t\t\t *      *   * *    *      "<<endl;
		        cout << "\t\t\t\t\t\t\t  ****  *   * **** *      "<<endl;
		        cout<<"\n";

		    UpperShape();

		  chef.ShowMenuPage();
		    LowerShape();
		    }
	    }
	    else if(Option==4)
	    {
	        cout << "\t\t\t\t\t\t\t *****  **** *    *       "<<endl;
	        cout << "\t\t\t\t\t\t\t *      *    *    *     "<<endl;
	        cout << "\t\t\t\t\t\t\t *****  **** *    *      "<<endl;
	        cout << "\t\t\t\t\t\t\t     *  *    *    *     "<<endl;
	        cout << "\t\t\t\t\t\t\t *****  **** **** ****       "<<endl;
	        cout<<endl;
	        UpperShape();
	        int opt1=0;
	        cout<<setw(62)<<""<<"Login "<<endl;
	        while(opt1==0 && sell.Login()==0 )
	         {
	        	cout<<setw(53)<<"";
	        	cout<<"Press 1 to Back & 0 to continue ";
	        		cin>>opt1;
	        		    }
	        	 LowerShape();
	    		    if(opt1==0)
		    {
	    		        cout << "\t\t\t\t\t\t\t *****  **** *    *       "<<endl;
	    		        cout << "\t\t\t\t\t\t\t *      *    *    *     "<<endl;
	    		        cout << "\t\t\t\t\t\t\t *****  **** *    *      "<<endl;
	    		        cout << "\t\t\t\t\t\t\t     *  *    *    *     "<<endl;
	    		        cout << "\t\t\t\t\t\t\t *****  **** **** ****       "<<endl;
		        cout<<"\n";

		    UpperShape();

		  sell.ShowMenuPage();
		    LowerShape();
		    }

	    }
	}
	LowerShape();




	return 0;
}
