/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Project: call_stats2
Author: Christopher M. Anzalone

Description: This program stores, processes, performs searches, adds, 
removes, and outputs data on a database of call records for cell phone
numbers. New records may be added as long as the database is not full. 
Records for a number may be removed as well. The search shows all of the 
records for one particular number. It can accept a data file as input, 
and can output a new data file after work has been done to it.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*Preprocessor Directives*/
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

/*Struct for call record types*/
class call_record
{
public:
	string cellNum;
	double rStat;	
	double lengthMin;
	double netCost;
	double taxRate;
	double callTax;
	double tCost;
};

/*Function Prototypes*/
//---------------------------------------------------------------
void initialize_DB(call_record [], int&);
//---------------------------------------------------------------
//FUNCTION NAME: initialize_DB
//DESCRIPTION: This function initializes the database by 
//allowing the user to upload a data file.
//PRECONDITIONS: A data file must exist and should be stored in 
//the same directory as this program.
//POSTCONDITIONS: Data from a text file has been read into the 
//database (aka the array of call_record structs.
//---------------------------------------------------------------
int search_DB(call_record [], int&, string);
//---------------------------------------------------------------
//FUNCTION NAME: search_DB
//DESCRIPTION: This function searches for a particular number
//in the database and prints out all instances of it, along
//with the rest of the information on record for it.
//PRECONDITIONS: There exists one or more records in the
//database.
//POSTCONDITIONS: If the user-entered number exists in the
//database, it, along with its information, has been printed to
//the screen.
//---------------------------------------------------------------
void process_data_DB(call_record[], int);
//---------------------------------------------------------------
//FUNCTION NAME: process_data_DB
//DESCRIPTION: This function processes the information for each
//number in the database based on the number of relay stations
//and the length of the phone call.
//PRECONDITIONS: One or more records must exist in the database,
//with a value for relay stations and length in minutes.
//POSTCONDITIONS: Any and all numbers in the database have had
//their net cost, tax rate, call tax, and total cost calculated.
//---------------------------------------------------------------
void process_data_Single(call_record);
//---------------------------------------------------------------
//FUNCTION NAME: process_data_Single
//DESCRIPTION: This function processes the information for a new
//record submitted within the Add_DB function.
//PRECONDITIONS: A new phone number and its relay stations and 
//length of phone call in minutes must have been entered in the 
//Add_DB function.
//POSTCONDITIONS: The new phone number has had its net cost, tax
//rate, call tax, and total cost calculated and stored.
//---------------------------------------------------------------
void call_Stats(call_record[], int, string);
//---------------------------------------------------------------
//FUNCTION NAME: call_Stats
//DESCRIPTION: This function prints to the user all of the 
//information on a particular phone number, based on the number
//they asked for.
//PRECONDITIONS: One or more records must exist in the database.
//POSTCONDITIONS: All of the records for the number entered have
//been displayed to the user.
//---------------------------------------------------------------
void Add_DB(call_record[], int&);
//---------------------------------------------------------------
//FUNCTION NAME: Add_DB
//DESCRIPTION: This function allows the user to add a new number
//with the number of relay stations and length of call in 
//minutes.
//PRECONDITIONS: The database must not be full.
//POSTCONDITIONS: The number and its information have been 
//processed and added to the database.
//---------------------------------------------------------------
void remove_DB(call_record [], int&, string);
//---------------------------------------------------------------
//FUNCTION NAME: remove_DB
//DESCRIPTION: This function allows the user to remove a number,
//along with all of the information for it, from the database.
//PRECONDITIONS: The number that is to be removed must first
//exist in the database.
//POSTCONDITIONS: All of the records for the number entered have
//been removed.
//---------------------------------------------------------------
void print_DB(call_record [], int);
//---------------------------------------------------------------
//FUNCTION NAME: print_DB
//DESCRIPTION: This function outputs all of the existing data
//into a new file, "weekly_call_info.txt"
//PRECONDITIONS: One or more records must exist in the database.
//POSTCONDITIONS: Any and all numbers in the database have been
//saved in a new file in the same directory.
//---------------------------------------------------------------
void screen_DB(call_record [], int);
//---------------------------------------------------------------
//FUNCTION NAME: screen_DB
//DESCRIPTION: This function displays the information currently
//in the database of this particular instance of the program.
//PRECONDITIONS: One or more records must exist in the database.
//POSTCONDITIONS: All of the information currently in the 
//database has been displayed on the screen for the user.
//---------------------------------------------------------------

/*Global constant for size of array of structs*/
const int SIZE=20;

int main()
{	/*variable declarations*/
	call_record call_DB[SIZE];
	char init='\0';
	string key;
	string scan;
	int num=0;
	int menu=0;

	/*initialize all variables in struct to zero*/
	for (int x=0; x<SIZE; x++)
	{
		call_DB[x].rStat=0.0;
		call_DB[x].lengthMin=0.0;
		call_DB[x].netCost=0.0;
		call_DB[x].taxRate=0.0;
		call_DB[x].callTax=0.0;
		call_DB[x].tCost=0.0;
	}
	
	/*Formula for numerical output displayed*/
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);

	/*File initialization prompt*/
	cout<<"Hello! Would you like to initialize the database with a file?\n"
		<<"(Y or N)"<<endl;

	cin>>init;

	if (init=='y' || init=='Y')
	{
		initialize_DB(call_DB, num);
	}

	/*Menu and switch statement for entire program*/
	while (menu!=7)
	{
		cout<<"\nPlease choose from the menu below"<<endl
			<<"\t(1) Add"<<endl
			<<"\t(2) Remove"<<endl
			<<"\t(3) Search for individual record"<<endl
			<<"\t(4) Output database to txt file"<<endl
			<<"\t(5) Print current database to screen"<<endl
			<<"\t(6) Process database"<<endl
			<<"\t(7) Exit program."<<endl;

		cin>>menu;
		cout<<endl;
		
		switch(menu)
		{
		case 1:
			//add info here
			Add_DB(call_DB, num);
			break;
		case 2:
			//remove info here
			cout<<"Please enter the number you would like to remove from "
				<<"the database."<<endl;
			cin>>key;
			remove_DB(call_DB, num, key);
			break;
		case 3:
			//search info here
			cout<<"Please enter the number you wish to search for."<<endl;
			cin>>scan;
			call_Stats(call_DB, num, scan);
			break;
		case 4:
			//output db info here
			print_DB(call_DB, num);
			break;
		case 5:
			//print to screen info here
			screen_DB(call_DB, num);
			break;
		case 6:
			//process info here
			process_data_DB(call_DB, num);
			break;
		case 7:
			menu=7;
			break;
		default:
			cout<<"Incorrect value entered."<<endl;
		}
		cout<<endl;
	} 
	return 0;
}

/*Function Implementations*/
void initialize_DB(call_record call_DB[], int& num)	
{
	/*Declaration of filestream object and file name string*/
	string filename;
	ifstream in;

	/*Input for name of file to input*/
	cout<<"\nPlease enter the filename\n"<<endl;
	cin>>filename;

	/*Open and read data from file, then close file*/
	in.open(filename.c_str());

	while(!in.eof())
	{
		in>>call_DB[num].cellNum
		  >>call_DB[num].rStat
		  >>call_DB[num].lengthMin;
		num++;
	}

	in.close();

	cout<<"\nInitialization complete."<<endl;
}

int search_DB(call_record call_DB[], int& num, string scan)	
{ 
	int x=0;

	/*Searches for identical string in database and returns index*/
	for (;x<num;x++)
	{
		if (call_DB[x].cellNum==scan)
			return x;	
	}
	return -1;	//returned if no similar string is found
}

void process_data_DB(call_record *call_DB, int num)	
{
	double rate=0.0;

	for (int track=0;track<num; track++)
	{
		/*calculate tax rate (%)*/
		if (call_DB[track].rStat>=1 && call_DB[track].rStat<=5)
			rate=1;
		else if (call_DB[track].rStat>=6 && call_DB[track].rStat<=11)
			rate=3;
		else if (call_DB[track].rStat>=12 && call_DB[track].rStat<=20)
			rate=5;
		else if (call_DB[track].rStat>=21 && call_DB[track].rStat<=50)
			rate=8;
		else if (call_DB[track].rStat>50)
			rate=12;

		/*set rate*/
		call_DB[track].taxRate=rate/100;

		/*calculate net cost*/
		call_DB[track].netCost=((call_DB[track].rStat/50)*(0.40)*(call_DB[track].lengthMin));

		/*calculate tax on call*/
		call_DB[track].callTax=(call_DB[track].netCost*(rate/100));

		/*calculate total*/
		call_DB[track].tCost=call_DB[track].netCost+call_DB[track].callTax;
	}
	
	cout<<"\nProcessing complete."<<endl;
}

void call_Stats(call_record call_DB[], int num, string prNum)
{	
	if (num == 0)	/*Checks if database is empty*/
	{
		cout<<"The array is empty; there is nothing to print "<<endl;
	}
	else	/*Searches for all (if any) instances of the number*/
	{
		int i=search_DB(call_DB,num,prNum);

		if (i == -1)
		{
			cout <<prNum<<" is not in the database, unable to print. "<<endl;
		}
		else	/*Searches for all (if any) instances of the number
				and displays information for each record*/
		{
			cout<<setw(16)<<left<<"Cell Phone #";
			cout<<setw(8)<<left<<"Relays\t"<<"Min\t"<<"Net\t"
			<<"Rate\t"<<"Tax\t"<<"Total Cost"<<endl;

			int z=0;

			/*Totals declarations*/
			double totalRelay=0.0, totalMinutes=0.0, totalNet=0.0, 
				totalCost=0.0, totalTax=0.0;

			/*Finds every existing entry of number and calculates totals*/
			while (z<num) 
			{
				if (call_DB[z].cellNum==prNum)
				{
					/*Existing info for phone number entry displayed*/
					cout<<" "<<call_DB[z].cellNum<<"\t"<<call_DB[z].rStat
						<<"\t"<<call_DB[z].lengthMin<<"\t"<<call_DB[z].netCost
						<<"\t"<<call_DB[z].taxRate<<"\t"<<call_DB[z].callTax
						<<"\t"<<call_DB[z].tCost<<endl;
				
					/*calculate totals of the number*/
					totalRelay=((call_DB[z].rStat)+(totalRelay));
					totalMinutes=((call_DB[z].lengthMin)+(totalMinutes));
					totalNet=((call_DB[z].netCost)+(totalNet));
					totalCost=((call_DB[z].tCost)+(totalCost));
					totalTax=((call_DB[z].callTax)+(totalTax));
				}
				z++;
			}

			/*Totals output*/
			cout<<"Totals\t\t"<<totalRelay<<"\t"<<totalMinutes<<"\t"<<totalNet
			<<" \tN/A\t"<<totalTax<<"\t"<<totalCost<<endl;
		}
	}
}

void Add_DB(call_record call_DB[], int& num)
{	
	/*Declaration for new record*/
	call_record recordNew;

	/*Variables of new record initialized to zero*/
	recordNew.rStat=0.0;
	recordNew.lengthMin=0.0;
	recordNew.netCost=0.0;
	recordNew.taxRate=0.0;
	recordNew.callTax=0.0;
	recordNew.tCost=0.0;

	/*User input for new record*/
	cout<<"Please input the cell number of new record"<<endl;
	cin>>recordNew.cellNum;

	cout<<"Please input number of relay stations"<<endl;
	cin>>recordNew.rStat;

	cout<<"Please input length of call"<<endl;
	cin>>recordNew.lengthMin;

	/*New record processed*/
	process_data_Single(recordNew);	

	/*If database is not full, new record is added to database*/
	if (num==SIZE)
	{
		cout<<"Database is full. New call record not added."<<endl;
	}
	else 
	{
		call_DB[num++]=recordNew;
	} 

	cout<<"Add complete."<<endl;
}

void process_data_Single(call_record recordNew)
{
	double rate=0.0;
	/*calculate tax rate (%)*/
	if (recordNew.rStat>=1 && recordNew.rStat<=5)
		rate=1;
	else if (recordNew.rStat>=6 && recordNew.rStat<=11)
		rate=3;
	else if (recordNew.rStat>=12 && recordNew.rStat<=20)
		rate=5;
	else if (recordNew.rStat>=21 && recordNew.rStat<=50)
		rate=8;
	else if (recordNew.rStat>50)
		rate=12;
	
	/*set rate*/
		recordNew.taxRate=rate/100;	
	/*calculate net cost*/
		recordNew.netCost=((recordNew.rStat/50)*(0.40)*(recordNew.lengthMin));
	/*calculate tax on call*/
		recordNew.callTax=(recordNew.netCost*(rate/100));
	/*calculate total*/
		recordNew.tCost=recordNew.netCost+recordNew.callTax;
}	

void remove_DB(call_record call_DB[], int& num, string key)
{	
	if (num == 0)	/*Checks if database is empty*/
	{
		cout<<"The array is empty; cannot remove "<<key<<endl;
	}
	else
	{
		/*Checks if the number to be removed exists*/
		int i=search_DB(call_DB,num,key);

		if (i == -1)
		{
			cout <<key<<" is not in the database, unable to remove it. "<<endl;
		}
		else
		{
			int x=0;
			
			/*Searches for all instances of the number and removes it*/
			while(x!=-1)
			{
				/*Index of number returned to x*/
				x=search_DB(call_DB,num,key);

				/*When there are no more instances of the number, loop breaks*/
				if (x==-1)
					break;

				/*After index of number is found, it is removed here*/
				for(int j=x; j<num-1; j++)
				{
					call_DB[j]=call_DB[j+1];
				}
				num--;
			}

		}
	}
	cout<<"\nRemoval complete."<<endl;
}

void print_DB(call_record call_DB[], int num)
{			
	/*Declaration of filestream object and counter*/
	ofstream out;
	int step=0; 
	
	/*New file created and opened in program*/
	out.open("weekly_call_info.txt");
	
	/*Format output for file*/
	out.setf(ios::fixed);
	out.setf(ios::showpoint);
	out.precision(2);

	/*All records in database are copied into the file*/
	while(step<num)	
	{
		out<<call_DB[step].cellNum<<"\t"
		<<call_DB[step].rStat<<"\t"
		<<call_DB[step].lengthMin<<"\t"
		<<call_DB[step].netCost<<"\t"
		<<call_DB[step].taxRate<<"\t"
		<<call_DB[step].callTax<<"\t"
		<<call_DB[step].tCost<<"\t"
		<<endl;
		step++;
	}

	/*File closed*/
	out.close();
	
	cout<<"The database has been saved to weekly_call_info.txt"<<endl;
}

void screen_DB(call_record call_DB[], int num)
{
	/*Header for output*/
	cout<<setw(16)<<left<<"Cell Phone #";
	cout<<setw(8)<<left<<"Relays\t"<<"Min\t"<<"Net\t"
		<<"Rate\t"<<"Tax\t"<<"Total Cost"<<endl;

	/*All records currently in database are displayed*/
	for (int x=0; x<num; x++)
	{
		cout<<call_DB[x].cellNum<<"\t"
		<<call_DB[x].rStat<<"\t"
		<<call_DB[x].lengthMin<<"\t"
		<<call_DB[x].netCost<<"\t"
		<<call_DB[x].taxRate<<"\t"
		<<call_DB[x].callTax<<"\t"
		<<call_DB[x].tCost<<"\t"
		<<endl;
	}
}