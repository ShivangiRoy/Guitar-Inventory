/*
GUITARSTORE DATABSE MANAGEMENT SYSTEM
A projectby Shivangi Roy Class :- XII-Sc-B
*/

#include <iostream.h>
#include <conio.h>
#include <fstream.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iomanip.h>

class guitar
{
// to read and append in the guitarinventory.bin file
  int itemno,sold, stock;
  char name[80];
  float cp, sp;
 public:
  guitar()//initialize the sold and stock
  {
   sold=0;
   stock=0;
  }
  float spr()
  { return sp; }
  float cpr()
  { return cp; }
  int stockr()
  { return stock; }
  int soldr()
  { return sold; }
  void subtract(int x)
  {
   stock-=x;
   sold=x;
  }
  int ritemno()
  {
   return itemno;
  }
  void input()
  {
   cout<<"\nItem number?\n";
   cin>>itemno;
   cout<<"\nGuitar model name?\n";
   gets(name);
   cout<<"\nCost price per piece?\n";
   cin>>cp;
   cout<<"\nSelling price per piece?\n";
   cin>>sp;
   cout<<"\nNumber of items?\n";
   cin>>stock;
  }
  void display()
  {
   cout<<setw(25)<<"Item number "<<": "<<itemno<<endl;
   cout<<setw(25)<<"Item name "<<": "<<name<<endl;
   cout<<setw(25)<<"Cost Price per unit "<<": "<<cp<<endl;
   cout<<setw(25)<<"Selling Price per unit "<<": "<<sp<<endl;
   cout<<setw(25)<<"No. of items in stock "<<": "<<stock<<endl;
  }
};
/*End of guitar class*/

/* Function to get price of guitar using its guitar ID */
float get_guitar_price(int guitar_id)
{
   fstream fil;
   fil.open("guitarinventory.bin", ios::binary|ios::in);
   guitar g;
   float price=0;

   while(fil.read((char*)&g, sizeof(g)))
   {
    if(g.ritemno()==guitar_id)
    {
     price = g.spr();
     break;
    }
   }
   fil.close();
   return price;
} // End of get_guitar_price()

class order
{
  int id;
  char name[80];
  char address[80];
  char status[20];
  int guitarid;
  int qtt;
  float price;
 public:
  order()
  {
  strcpy(status,"unprocessed");
  }
  int qttr()
  { return qtt; }
  int guitaridr()
  { return guitarid; }
  float pricer()
  { return price;}
  char* statusr()
  {
   return status;
  }
  void process()
  {
   strcpy(status,"processed");
  }
  int getid()
  {
   return id;
  }

  void input()
  {
   cout<<"\nOrder Id?\n";
   cin>>id;
   cout<<"\nCustomer name?\n";
   gets(name);
   cout<<"\nDelivery address?\n";
   gets(address);
   cout<<"\nGuitar item number bought?\n";
   cin>>guitarid;
   cout<<"\nNumber of pieces?\n";
   cin>>qtt;
   strcpy(status,"unprocessed");
  }

  void display()
  {
   cout<<setw(25)<<"Order Id "<<": "<<id<<endl;
   cout<<setw(25)<<"Customer name "<<": "<<name<<endl;
   cout<<setw(25)<<"Delivery Address "<<": "<<address<<endl;
   cout<<setw(25)<<"Guitar (Id) brought "<<": "<<guitarid<<endl;
   float price = get_guitar_price(guitarid);
   cout<<setw(25)<<"Price per unit "<<": "<<price<<endl;
   cout<<setw(25)<<"No. of pieces "<<": "<<qtt<<endl;
   cout<<setw(25)<<"Total"<<": "<<qtt*price<<endl;
  }
};

void Mainmenu();
void Inventory();
void Orders();
void Sales();

void addguitar() /* adds new guitars in guitarinventory.bin file*/
{
 clrscr();
 fstream fil;
 fil.open("guitarinventory.bin", ios::binary|ios::app);
 guitar g;
 cout<<"\nFill details of the guitar(s) :\n";
 int choice;
 do
 {
  g.input();/*gets new item number,guitar model name,cost price,selling price,no. of items from user*/
  fil.write((char*)&g, sizeof(g));
  cout<<"\nData recorded! Input more? (1=Yes, 2=No)\n";
  cin>>choice;
  getch();
  clrscr();
 }
 while(choice==1);
 clrscr();
 fil.close();
}

void search()
{
 clrscr();
 fstream fil;
 fil.open("guitarinventory.bin", ios::binary|ios::in);
 guitar g;
 cout<<"\nType the item number to be searched : ";
 int itemno;
 cin>>itemno;
 int c=0;
 while(fil.read((char*)&g, sizeof(g)))
 {
  if(g.ritemno()==itemno)
  {
   g.display();
   c++;
  }
 }
  if(c==0)
  {
   cout<<"\nItem not found!"<<endl;
   }
 fil.close();
 getch();
 clrscr();
}

void showstatus()
{
 clrscr();
 fstream fil;
 fil.open("guitarinventory.bin", ios::binary|ios::in);
 guitar g;
 int counttype=0, countnum=0;
 while(fil.read((char*)&g, sizeof(g)))
 {
  counttype++;
  countnum+=g.stockr();
 }
 cout<<"\nTotal types of guitars in inventory = "<<counttype<<"\nTotal number of all guitars in inventory = "<<countnum<<endl<<endl<<endl;
 getch();
 clrscr();
 fil.close();
}

void removeguitar()
{
 clrscr();
 fstream fil1, fil2;
 fil1.open("guitarinventory.bin", ios::binary|ios::in|ios::out);
 fil2.open("tempinventory.bin", ios::binary|ios::in|ios::out);
 int inod;
 guitar g;
 cout<<"Enter the item number of the guitar to be removed : ";
 cin>>inod;
 int del=0;
 while(fil1.read((char*)&g, sizeof(g)))
 {
  if(g.ritemno()!=inod)
   fil2.write((char*)&g, sizeof(g));
  else
   del++;
 }
 if(!del)
  cout<<"\nGuitar does not exist in inventory!";
 else
  cout<<"\nGuitar removed from inventory!";
 fil1.close();
 fil2.close();
 remove("guitarinventory.bin");
 rename("tempinventory.bin", "guitarinventory.bin");
 getch();
 clrscr();
}

void registero()
{
 clrscr();
 fstream fil;
 fil.open("order.bin", ios::binary|ios::app);
 order o;
 cout<<"\nFill details of the order(s) :\n";
 int choice;
 do
 {
  o.input();
  fil.write((char*)&o, sizeof(o));
  cout<<"\nOrder registered! Input more? (1=Yes, 2=No)\n";
  cin>>choice;
  getch();
  clrscr();
 }
 while(choice==1);
 fil.close();
 clrscr();
}

void showpending()
{
 clrscr();
 fstream fil;
 fil.open("order.bin", ios::binary|ios::in);
 order o;
 int count=0;
 while(fil.read((char*)&o, sizeof(o)))
 {
  if(strcmpi(o.statusr(),"unprocessed")==0)
  {
   o.display();
   cout<<endl<<endl;
   count++;
  }
 }
 if(count==0)
 cout<<"\nNo orders pending!\n";
 fil.close();
 getch();
 clrscr();
}

void quantityalter(order o)
{
 fstream fil;
 fil.open("guitarinventory.bin", ios::binary|ios::in|ios::out);
 guitar g;
 while(fil.read((char*)&g,sizeof(g)))
 {
  if(g.ritemno()==o.guitaridr())
  {
   int val=o.qttr();
   g.subtract(val);
   fil.seekg(fil.tellg()-sizeof(g));
   fil.write((char*)&g, sizeof(g));
  }
 }
 fil.close();
}


void processorder()
{
 clrscr();
 fstream fil1, fil2;
 fil1.open("order.bin", ios::binary|ios::in|ios::out);
 order o;
 int x;
 cout<<"Enter the id of the order to be processed - ";
 cin>>x;
 int found=0;
 while(!found && fil1.read((char*)&o, sizeof(o)))
 {
  if(o.getid()==x)
  {
   if(strcmpi(o.statusr(),"unprocessed")==0)
   {
    found=1;
    o.process();
    fil1.seekg(fil1.tellg()-sizeof(o));
    fil1.write((char*)&o, sizeof(o));
    cout<<"\nOrder Processed!"<<endl;
    quantityalter(o);
   }
  }
 }
 fil1.close();
 getch();
 clrscr();
}

void showprocessed()
{
 clrscr();
 fstream fil;
 fil.open("order.bin", ios::binary|ios::in);
 order o;
 int count=0;
 while(fil.read((char*)&o, sizeof(o)))
 {
  if(strcmpi(o.statusr(),"processed")==0)
  {
   o.display();
   cout<<endl<<endl;
   count++;
  }
 }
 if(count==0)
 cout<<"\nNo orders processed yet!\n";
 fil.close();
 getch();
 clrscr();
}

void netrevenue()
{
 clrscr();
 fstream fil1, fil2;
 fil1.open("order.bin", ios::binary|ios::in);
 fil2.open("guitarinventory.bin", ios::binary|ios::in);
 float rev=0;
 order o;
 guitar g;
 while(fil1.read((char*)&o, sizeof(o)))
 {
  if(strcmpi(o.statusr(),"processed")==0)
  {
   while(fil2.read((char*)&g, sizeof(g)))
   {
   if(g.ritemno()==o.guitaridr())
   rev+=(o.qttr()*g.spr());
   }
  }
 }
 cout<<"\nNet sales revenue till date is "<<rev<<endl;
 fil1.close();
 fil2.close();
 getch();
 clrscr();
}

void profit()
{
 clrscr();
 fstream fil1, fil2;
 fil1.open("order.bin", ios::binary|ios::in);
 fil2.open("guitarinventory.bin", ios::binary|ios::in);
 order o;
 guitar g;
 float profit=0;
 while(fil1.read((char*)&o, sizeof(o)))
 {
  if(strcmpi(o.statusr(),"processed")==0)
  {
   while(fil2.read((char*)&g, sizeof(g)))
   {
    if(g.ritemno()==o.guitaridr())
    profit+=o.qttr()*(g.spr()-g.cpr());
   }
  }
 }
 cout<<"\nNet sales profit till date is "<<profit<<endl;
 fil1.close();
 fil2.close();
 getch();
 clrscr();
}

void main()
{
 randomize();
 int x,y;
 x=random(10);
 y=random(10);
 while(
 x!=y)
 {
  textcolor(x);
  textbackground(y);
  x=random(10);
  y=random(10);
 }
 clrscr();
 gotoxy(25,5);
 cout<<"WELCOME TO THE GUITARSTORE DATABASE!\n";
 gotoxy(25,6);
 fstream fil;
 fil.open("password.txt", ios::binary|ios::in|ios::out);
 struct p
 {
  char a[4];
 };
 p pw;   /*pw will be used to read password from file password.txt*/
 cout<<"Type the 4 digit password : ";
 char pass[4];/* pass takes password from user*/
 for(int i=0; i<4; i++)
 {
  pass[i]=getch();
  cout<<"*";
 }
 fil.read((char*)&pw, sizeof(pw));
 int count=0;
 for(int j=0; j<4; j++)
 if(pass[j]!=pw.a[j]) /*comparing password typed by user with password in file password.txt*/
  count++;
 if(count==0)
  Mainmenu();
 else
  { clrscr(); gotoxy(27,5); cout<<"WRONG PASSWORD!!!"; }
 fil.close();
 getch();
}

void Deletedata()
{
 clrscr();
 cout<<"Are you sure? (1=Yes/2=No)\n";
 int n;
 cin>>n;
 if(n==1)
 {
  remove("guitarinventory.bin");
  remove("order.bin");
  remove("sales.bin");
 }
 else
 Mainmenu();
}

void Changepword()
{
 clrscr();
 cout<<"Enter new password : ";
 char pass[4];
 cin>>pass;
 fstream fil;
 fil.open("password.txt", ios::out);
 fil<<pass;
 fil.close();
 Mainmenu();
}

void Mainmenu()
{
 clrscr();
 gotoxy(20,3); cout<<"GGG U U III TTT AAA RRRR  SSS TTT OOO RRRR EEE   ";
 gotoxy(20,4); cout<<"G   U U  I   T  A A R  R  S    T  O O R  R E     ";
 gotoxy(20,5); cout<<"G G U U  I   T  AAA RRR   SSS  T  O O RRR  EEE   ";
 gotoxy(20,6); cout<<"G G U U  I   T  A A R  R    S  T  O O R  R E     ";
 gotoxy(20,7); cout<<"GGG UUU III  T  A A R  R  SSS  T  OOO R  R EEE   ";
 gotoxy(26,11); cout<<"*^*^*^*^*^*^*^*^*^*^*^*^*^*";
 gotoxy(26,12);	cout<<"<#########################>";
 gotoxy(26,13);	cout<<"*#                       #*";
 gotoxy(26,14);	cout<<"<#                       #>";
 gotoxy(26,15);	cout<<"*#                       #*";
 gotoxy(26,16);	cout<<"<#                       #>";
 gotoxy(26,17);	cout<<"*#                       #*";
 gotoxy(26,18);	cout<<"<#                       #>";
 gotoxy(26,19);	cout<<"*#                       #*";
 gotoxy(26,20);	cout<<"<#                       #>";
 gotoxy(26,21);	cout<<"*#                       #*";
 gotoxy(26,22);	cout<<"<#########################>";
 gotoxy(26,23);	cout<<"*v*v*v*v*v*v*v*v*v*v*v*v*v*";
 gotoxy(5,2);   cout<<"      xxx";
 gotoxy(5,3);	cout<<"     OxXxO";
 gotoxy(5,4);	cout<<"      xXx";
 gotoxy(5,5);	cout<<"     OxXxO";
 gotoxy(5,6);	cout<<"      HHH";
 gotoxy(5,7);	cout<<"      HHH";
 gotoxy(5,8);	cout<<"      HHH";
 gotoxy(5,9);	cout<<"      HHH";
 gotoxy(5,10);	cout<<"      HHH";
 gotoxy(5,11);	cout<<"      HHH";
 gotoxy(5,12);	cout<<"      HHH";
 gotoxy(5,13);	cout<<"    __HHH";
 gotoxy(5,14);	cout<<"   TxxHHH  _";
 gotoxy(5,15);  cout<<"  TxxxHHH_/xT";
 gotoxy(5,16);	cout<<" Txxx*|||*xxxT";
 gotoxy(5,17);	cout<<" Txxx*|||*xxxT";
 gotoxy(5,18);	cout<<"  Txxx|||xxxT";
 gotoxy(5,19);	cout<<"  Txxx|||xxxT";
 gotoxy(5,20);	cout<<" Txxx|ooo|xxxT";
 gotoxy(5,21);	cout<<"Txxxx+++++xxxxT";
 gotoxy(5,22);	cout<<"TxxxxxxxxxxxxxT";
 gotoxy(5,23);	cout<<" TxxxxxxxxxxxxT";
 gotoxy(5,24);	cout<<"  TxxxxxxxxxxT";
 gotoxy(5,25);	cout<<"   \xxxxxxxx/";
 gotoxy(29,14);
 cout<<"1.INVENTORY";
 gotoxy(29,15);
 cout<<"2.ORDERS";
 gotoxy(29,16);
 cout<<"3.SALES";
 gotoxy(29,17);
 cout<<"4.CHANGE PASSWORD";
 gotoxy(29,18);
 cout<<"5.DELETE ALL DATA";
 gotoxy(29,19);
 cout<<"6.EXIT";
 gotoxy(29,14);
 int pos;
 char mover='0';
 int y=14;
  do
  {
   mover=getch();

   if(mover==80)/*ascii value of down arrow*/
    {
     if(y<19)
      gotoxy(29,++y);
    }
   else if(mover==72)/*ascii value of up arrow*/
    {
     if(y>14)
      gotoxy(29,--y);
    }
   }
   while(mover!=13);/*ascii value of enter=13*/
   pos=wherey();
  if(mover==13)
  {
   switch(pos)
   {
    case 14: Inventory(); break;
    case 15: Orders(); break;
    case 16: Sales(); break;
    case 17: Changepword(); break;
    case 18: Deletedata(); break;
    case 19: break;
   }
  }
}



void Inventory()/* for adding,searching,removing and showing status of guitar*/
{
 clrscr();
 int choice;
 do
 {
  cout<<"\nChoose the required operation by typing in it's number -"
      <<"\n1.Add new guitar to inventory"
      <<"\n2.Search for a guitar in inventory"
      <<"\n3.Remove a guitar from the inventory"
      <<"\n4.Show inventory status"
      <<"\n5.Return to main menu"<<endl;
  cin>>choice;
  switch(choice)
  {
   case 1: addguitar(); break;
   case 2: search(); break;
   case 3: removeguitar(); break;
   case 4: showstatus(); break;
   case 5: Mainmenu();
  }
 }
 while(choice!=5);
}

void Orders()
{
 clrscr();
 int choice;
 do
 {
  cout<<"\nChoose the required operation by typing in it's number -"
      <<"\n1.Register an order"
      <<"\n2.Show pending orders"
      <<"\n3.Process an order"
      <<"\n4.Show processed orders"
      <<"\n5.Return to main menu"<<endl;
  cin>>choice;
  switch(choice)
  {
   case 1: registero(); break;
   case 2: showpending(); break;
   case 3: processorder(); break;
   case 4: showprocessed(); break;
   case 5: Mainmenu();
  }
 }
 while(choice!=5);
 }

void Sales()
{
 clrscr();
 int choice;
 do
 {
    cout<<"\nChoose the required operation by typing in it's number -"
      <<"\n1.Net profit till date"
      <<"\n2.Net revenue till date"
      <<"\n3.Return to main menu"<<endl;
  cin>>choice;
  switch(choice)
  {
   case 1: profit(); break;
   case 2: netrevenue(); break;
   case 3: Mainmenu();
  }
 }
 while(choice!=3);
}
