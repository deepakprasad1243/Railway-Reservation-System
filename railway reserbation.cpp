/*****************************************************************
		SOFTWARE FOR RAILWAY RESEVATION
			  CREATED BY :-
	  ARJUN SINGH,DEEPAK PRASAD AND HIMANSHU TYAGI
******************************************************************/

/*****************************************************************
		  HEADER FILES USED IN THE PROGRAM
 *****************************************************************/
#include<iostream.h>
#include<fstream.h>
#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
/***************************************************************************
		   CLASS DATABASE FOR ADMINISTRATION PURPOSE
 ***************************************************************************/
class database
{
	public:
	char tname[30]; //TO INPUT NAME OF TRAIN
	int tno;        //TO INPUT TRAIN NUMBER
	float gen,sl,ac3,ac2,ac1,f; // DIFFERENT CLASSES OF TRAIN
	char s[50],d[50];   // S FOR SOURCE STATION AND D FOR DESTINATION
/***************************************************************************
	     TO INPUT ALL THE DETAILS
 ***************************************************************************/
 void input()
 {
	cout<<"Enter train name:-   ";
	gets(tname);cout<<"\n";
	cout<<"Enter train number:-   ";
	cin>>tno; cout<<"\n";
	cout<<"Enter source station:-   ";
	gets(s);cout<<"\n";
	cout<<"Enter destination station:-   ";
	gets(d); cout<<"\n";
	cout<<"enter fare of general class:-   ";
	cin>>gen;cout<<"\n";
	cout<<"enter fare of sleeper class:-   ";
	cin>>sl;cout<<"\n";
	cout<<"enter fare of ac-1 tier:-   ";
	cin>>ac1;cout<<"\n";
	cout<<"Enter  fare of ac-2 tier:-   ";
	cin>>ac2;cout<<"\n";
	cout<<"Enter the fare of ac-3 tier:-   ";
	cin>>ac3;cout<<"\n";
  }
/******************************************************************************
	       THIS FUNCTION IS TO DISPLAY THE OUTPUT ON THE SCREEN
******************************************************************************/
  void output()
  {
	cout<<"train name = ";
	puts(tname);
	cout<<endl;
	cout<<"train no. = "<< tno<<endl;
	cout<<"Source station = ";
	puts(s);
	cout<<endl;
	cout<<" Destination station =";
	puts(d);
	cout<<"\nfare per person for gernal class= "<<gen;
	cout<<"\nfare per person for sleeper class= "<<sl;
	cout<<"\nfare per person for AC-3 tier= "<<ac3;
	cout<<"\nfare per person for AC-2 tier= "<<ac2;
	cout<<"\nfare per person for AC-1 tier= "<<ac1;
  }
};
/**************************************************************************
	    THIS FUNCTION IS TO CREATE DATABASE OF TRAINS
***************************************************************************/
void create()
{
	database dt[100];
	int n,i;
	cout<<"Enter the no. of Enteries:-   ";
	cin>>n;
	ofstream f;  //A FILE OPENED IN BINARY MODE
	f.open("Reservation.dat",ios::binary);  //FILE RESERVATION IS OPENED
		for(i=0;i<n;i++)
		{
		dt[i].input();
		f.write((char*)&dt[i],sizeof(dt[i])); //ALL INPUTED DETAILS ARE WRITTEN IN RESERVATION FILE
		}
	f.close(); //RESERVATION FILE IS CLOSED
}
/**************************************************************************
	    THIS FUNCTION IS TO ADD DETAILS OF THE TRAIN
***************************************************************************/
void add()
{
	ofstream f;
	int n,i;
	database d;
	f.open("resevation.dat",ios::binary|ios:: app);//RESEVATION FILE IS OPENED IN APPEND MODE
	cout<<"Enter the no of details to be added";
	cin>>n;
		for(i=0;i<n;i++) //TO INPUT DETAILS IF 'N' TRAINS
		{
		d.input();
		f.write((char*)&d,sizeof(d));  // RESEVATION FILE IS UPDATED
		}
	f.close(); // FILE IS CLOSED
}
/*************************************************************************
	       THIS FUNCTION IS TO DISPLAY TRAIN ENTRIES
 *************************************************************************/
void display()
{
	ifstream f;
	database d;
	f.open("Reservation.dat",ios::binary);
	while(!f.eof())
	{	f.read((char*)&d,sizeof(d));
		d.output();
	}
	f.close();
}

/********************************************************************
	     TO DELETE ENTRIES IN CASE OF EMERGENCY
 ********************************************************************/
void del()
{
	database d;
	int ch,t;
	char train[50];
	ifstream fin;
	ofstream fout;
	fin.open("Reservation.dat",ios::binary);//RESEVATION FILE IS OPENED
	fout.open("temp.dat",ios::binary); // A NEW TEMPRARY FILE IS OPENED
	cout<<"\t\t\tmenu\n";
	cout<<"1 delete on basis of train name ";
	cout<<"2 delete on basis of train number ";
	cout<<"enter your choice as 1 or 2 ";
	cin>>ch;
	   if(ch==1)
	{
		cout<<"enter train name to be deleated ";
		gets(train);
		if(strcmp(train,d.tname)!=0)  // COMPAIRING ENTERED TRAIN NAME TO BE DELETED
		fout.write((char*)&d,sizeof(d));
	}
	else
	   if(ch==2)
	{
		cout<<"enter train number";
		cin>>t;
		if(t!=d.tno)  //COMPAIRING ON BASIS OF TRAIN NUMBER
		fout.write((char*)&d,sizeof(d));
	}
	fout.close();
	fin.close();
	remove("Resevation.dat"); //INITIAL FILE RESEVATION FILE IS REMOVED
	rename("temp.dat","Resevation.dat"); //TEMPEROARY FILE IS NAMED AS RESERVATION
}
/**************************************************************************
	    THIS FUNCTION IS TO CHECK THE AVAILABLE TRAIN
 **************************************************************************/
void available()
{
	database dt;
	char bs[50],ds[50];  //BS FOR BOARDING STATION AND DS FOR DESTINATION STATION
	int tno;
	cout<<"Enter the station of boarding train \n";
	gets(bs);
	cout<<"Enter your destinatuion ";
	gets(ds);
	cout<<"Train available in this route ";
	ifstream f;
	f.open("Resevation.dat",ios::binary);
	while(!f.eof())
	{	f.read((char*)&dt,sizeof(dt));
		if(strcmpi(bs,dt.s)==0 && strcmpi(ds,dt.d)==0)//COMPAIRING ENTERED BOARDING AND DESTINATION STATIONS
		{
			cout<<"train name =";
			puts(dt.tname);
			cout<<"\t";
			cout<<"train no. = "<<tno;
			cout<<endl;
		}
	}
}
/*************************************************************************
	    CLASS TICKET INHERITING PUBLICALLY CLASS DATABASE
 *************************************************************************/
class ticket : public database
{
	public:
	int pnrno,pno,age;
	float a;
	char type[20];
	void detail();
	void tkt();
		struct passenger
		{
		char pname[80];
		};

};
/***************************************************************************
       NON-INLINE FUNCTION OF CLASS TICKET TO GET DTAILS FROM THE USER
 ***************************************************************************/
void ticket::detail()
{
	passenger p[8];
	randomize();  //INITIALIZE RANDOM NUMBER GENERATOR
	a=random(1000)*257;
	cout<<"enter no. of passengers ";
	cin>>pno;
	    for(int i=0;i<pno;i++)
	{
		cout<<"enter name of no."<<i<<"passenger\n";
		gets(p[i].pname);
		cout<<"Enter the age of no."<<i<<"passenger\n";
		cin>>age;
	}
		cout<<"enter the type of coach as mentioned below:-\n";
		cout<<"For general:gen, For Sleeper:sl, For ac-1 tier:ac1, For ac-2 tier:ac2, For ac-3 tier:ac3\n";
		gets(type);
		if(strcmpi(type,"gen")==0) //COMPARING ENTERED TRAVEL CLASS
			f=gen;
	    else
		if(strcmpi(type,"sl")==0)
			f=sl;
	    else
		if(strcmpi(type,"ac1")==0)
			f=ac1;
	    else
		if(strcmpi(type,"ac2")==0)
			f=ac2;
	    else
		if(strcmpi(type,"ac3")==0)
			f=ac3;
	    else
		cout<<"Wrong Entry";
}
/****************************************************************
	    NON-INLINE FUNCTION FOR CLASS TICKET
	    TO DISPLAY THE DETAILS OF THE USER
 ****************************************************************/
void ticket :: tkt()
{
	int i; passenger p[8];
	cout<<"train = ";
	puts(tname);
	cout<<endl;
	cout<<"train no = "<<tno<<endl;
	cout<<"PNR no = "<<a<<endl;
	cout<<"No. of passengers = "<<pno<<endl;
	cout<<"Name of passengers are = ";
	   for(i=0;i<pno;i++)
	{	puts(p[i].pname);}
		cout<<"\ncoach type = "<<type;
		cout<<"\nFrom = ";
		puts(s);cout<<endl;
		cout<<"To = "<<
		puts(d);cout<<endl;
		cout<<"Fare = "<<f;
}
/***************************************************************************
		    THIS FUNCTION IS TO GENERATE TICKET
 ***************************************************************************/
void generateticket()
{
	char train[50],bs[50],ds[50];
	database dt;
	ticket t;
	ifstream fin;
	ofstream fout;
	fin.open("Reservation.dat",ios::binary);
	fout.open("Ticket.dat",ios::binary|ios::app);
	cout<<"Enter train name "<<endl;
	gets(train);
	cout<<"Journey from ";
	gets(bs);
	cout<<"journey to ";
	gets(ds);
	   while(!fin.eof())
	{
		fin.read((char*)&dt,sizeof(dt));
		if(strcmp(train,dt.tname)==0 && strcmp(ds,dt.d)==0)
		   {
			strcpy(t.tname,dt.tname);
			t.tno=dt.tno;
			strcpy(t.s,dt.s);
			strcpy(t.d,dt.d);
			t.f=dt.f;
		   }
		t.detail();
		t.f=t.pno*t.f;
		fout.write((char*)&t,sizeof(t));
		t.tkt();
		fin.close();
		fout.close();
	 }
}
/******************************************************************
		THIS FUNCTION CANCELS THE TICKET
 ******************************************************************/
void cancel()
{
	int pnr;
	ticket t;
	char ch[3];
	cout<<"enter the PNR no of the ticket to be canceled ";
	cin>>pnr;
	ifstream fin;
	fin.open("ticket.dat",ios::binary);
	   while(!fin.eof())
	{
		fin.read((char*)&t,sizeof(t));
		   if(pnr==t.pnrno)
			t.tkt();
		cout<<"if you wnt to cancel your ticket type 'YES'";
		gets(ch);
		   if(strcmpi(ch,"YES")==0)
			cout<<"Your ticket has been cancelled, you can collect RS. "<<t.f;
	}
	fin.close();
}
/****************************************************************************************
     THIS FUNCTION COMPILES DIFFERENT FUNCTIONS RELATED TO ADMINISTRATION MENU
*****************************************************************************************/
void administrator()
{
	char pass[10], ch;
	cout<<"\t\t\tEnter login passward\n";cout<<"\t\t\t";
	gets(pass);
	    if(strcmpi(pass,"COMPUTER")!=0)
		cout<<"wrong password. You are not permitted to login in this mode";
	else
	    do
	{
		cout<<endl;
		cout<<"*******************************************************************\n";
		cout<<"\t\t\tADMINISTATOR MENU\n";
		cout<<"*******************************************************************\n";
		cout<<"          1.create database\n";
		cout<<"          2.Add data\n";
		cout<<"          3.Display data\n";
		cout<<"          4.delete data\n";
		cout<<"          5.Exit\n";
		cout<<"Enter your choice:-   ";
		cin>>ch;cout<<"\n\n";
	    switch(ch)
	{
		case'1':{ create();
			break;}
		case'2':{ add();
			break;}
		case'3':{ display();
			break;}
		case'4':{ del();
			break;}
		case'5' :break;
		default : cout<<" Invalid choice";
	}
	}	while(ch!='5');
}
void user()
{
	char ch;
	    do{ cout<<"***************************************************************\n";
		cout<<"\t\t\t WELCOME TO INDIAN RAILWAYS \n";
		cout<<"***************************************************************\n";
		cout<<"\t\t\t\tMENU \n";
		cout<<"       1. Availablity of trains \n";
		cout<<"       2. Reservation \n";
		cout<<"       3. Cancellation \n";
		cout<<"       4. Exit \n";
		cout<<" enter your choice :-   ";
		cin>>ch; cout<<"\n\n";
	    switch(ch)
	{
		case '1' :{ available();
				break;}
		case '2' : {  generateticket();
				break;}
		case '3' : { cancel();
				break;}
		case '4' : break;
		default  : cout<<" Invalid choice";
	}
	}    while(ch!='4');
}
void main()
{
	clrscr();
	char ch;
	cout<<"-----------------------------------------------------\n";
	cout<<"	--------WELCOME TO RAILWAY RESERVATION SYSTEM--------\n";
	cout<<"-----------------------------------------------------\n";
	    do
	{ 	clrscr();
		cout<< "\t\t\t--------- Main Menu--------\n";
		cout<<"\t\t\t1.Administer mode\n";
		cout<<"\t\t\t2.User mode\n";
		cout<<"\t\t\t3.Exit\n";
		cout<<"\t\tEnter your choice:-  ";
		cin>>ch; cout<<"\n\n";
	    switch(ch)
	{
		case '1' :{  administrator();
				 break;}
		case '2' : {  user();
				 break;}
		case '3' :  break;
		default  : cout<<" Invalid choice";
	}
	}    while(ch!='3');
}
/****************************************************************
		   ENDING OF PROGRAM
*****************************************************************/
