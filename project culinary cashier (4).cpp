#include<iostream>
#include<fstream>
#include<iomanip>
#include<stdio.h>
#include<string.h>
using namespace std;

class menu
{
public:
    int itemcode;
    char itemname[50];
    float price;
    friend void removeitem();
    friend void updateitem();
    friend void search();
    friend void searching();
public:
    void accept()
    {
        cout<<endl<<"Enter Item Code";
        cin>>itemcode;
        cout<<endl<<"Enter Itemname";
        cin>>itemname;
        cout<<endl<<"Enter Price";
        cin>>price;
    }
    void display()
    {
        cout<<endl<<setw(5)<<itemcode<<setw(45)<<itemname<<setw(15)<<price;
    }
};
menu obj;// this is a global object available to all functions not inside class
//class ends here
void search()
{
    fstream rd;
    rd.open("C:\\Users\\rohit\\Desktop\\CPP_PROJECT\\menu.txt",ios::in);//connect
    rd.seekg(0,ios::end);//take cursor to end
    char iname[50];
    cout<<endl<<"Enter item Name";
    cin>>iname;

    int n=rd.tellg();//get location of cursor which will also be size of file
    rd.seekg(0,ios::beg);//bring cursor to first position
    cout<<" itemcode    itemName                price";
    cout<<endl<<"****************************************************************"<<endl;

    for(int i=1;i<=n/sizeof(obj);i++) // apply loop to print all objects
    {
        rd.read((char *)&obj,sizeof(obj)); //read object
        if(stricmp(obj.itemname,iname)==0)
        {
        obj.display();//print object
        }
    }
    cout<<endl<<"*******************************************************";

}
void searching()
{
    fstream rd;
    rd.open("C:\\Users\\rohit\\Desktop\\CPP_PROJECT\\menu.txt",ios::in);//connect
    rd.seekg(0,ios::end);//take cursor to end
    int icode;
    cout<<endl<<"Enter item code";
    cin>>icode;

    int n=rd.tellg();//get location of cursor which will also be size of file
    rd.seekg(0,ios::beg);//bring cursor to first position
    cout<<" itemcode    itemName                price";
    cout<<endl<<"****************************************************************"<<endl;

    for(int i=1;i<=n/sizeof(obj);i++) // apply loop to print all objects
    {
        rd.read((char *)&obj,sizeof(obj)); //read object
        if(obj.itemcode==icode)
        {
        obj.display();//print object
        }
    }
    cout<<endl<<"*******************************************************";
}

class bill
{
    public:
    int billno;
    char date[10];
    char cname[50];
    int icode;
    char iname[50];
    int price;
    int qty;
    int total;
    void prebill()
    {
        /*cout<<endl<<"Enter bill number";
        cin>>billno;*/
        cout<<endl<<"Enter Date";
        cin>>date;
        cout<<endl<<"Enter Customer Name";
        cin>>cname;
    }
    void cart()
    {

        while(1)
        {
        cout<<endl<<"Enter Icode";
        cin>>icode;
        // Fetch Menu price from Menu and puts it in cart
        fstream rd;
        rd.open("C:\\Users\\rohit\\Desktop\\CPP_PROJECT\\menu.txt",ios::in);
        rd.seekg(0,ios::end);
        int s=rd.tellg();
        int count=s/sizeof(obj);
        rd.seekg(0,ios::beg); //take cursor to begining
        int flag=0;
        for(int i=1;i<=count;i++)
        {
            rd.read((char *)&obj,sizeof(obj));
            if(obj.itemcode==icode)
            {
                price=obj.price;
                strcpy(iname,obj.itemname);
                flag=1;
                break;
            }

        }
        if(flag==1)
        {
        cout<<endl<<"Enter Qty";
        cin>>qty;
        total=price*qty;
        break;
        }
        else
        {
            cout<<endl<<"invalid item code";
        }
        }
    }

};
bill obj2;

void printbill(int n)

{
    fstream rd;
    rd.open("C:\\Users\\rohit\\Desktop\\CPP_PROJECT\\bill.txt",ios::in);
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n";

    rd.seekg(0,ios::end);
    int s=rd.tellg();
    int c=s/sizeof(obj2);
    cout<<endl<<"Number of Objects"<<c;
    rd.seekg(0,ios::beg);

    for(int i=1;i<=c;i++)
    {
        rd.read((char *)&obj2,sizeof(obj2));
//        cout<<endl<<"Reading Bill Number"<<obj2.billno;
        if(obj2.billno==n)
        {
        cout<<endl<<"Dated: "<<setw(10)<<obj2.date<<"\t\t\t\t Bill Number"<<obj2.billno;
        cout<<endl<<endl<<endl<<endl;
        cout<<endl<<"********************************************************************************";
        cout<<endl<<"\t\t\t\t\tWelcome  "<<  obj2.cname<< " to My Food Place";
        cout<<endl<<"********************************************************************************";
        break;

        }
    }
    int grandtotal=0;
    rd.seekg(0,ios::beg);
    for(int j=1;j<=c;j++)
    {
        rd.read((char *)&obj2,sizeof(obj2));
        if(obj2.billno==n)
        {
            cout<<endl<<j<<"\t\t"<<setw(35)<<obj2.iname<<"\t"<<setw(4)<<obj2.price<<setw(3)<<obj2.qty<<setw(8)<<obj2.total;
            grandtotal=grandtotal+obj2.total;
        }

    }
    cout<<endl<<"******************************************************************************************";
    cout<<endl<<"\t\t\t\t\t"<<grandtotal;
    cout<<endl<<"*******************************************************************************************";



}





void raisebill()
{
    fstream rd;
    rd.open("C:\\Users\\rohit\\Desktop\\CPP_PROJECT\\number.txt",ios::in);
    char b=rd.get();
    //obj2.billno=(int)b-48;
    obj2.billno=(int)b;
    cout<<"bill number"<<obj2.billno;
    obj2.prebill(); // This Takes Basic One time info from user like billno,name, and date

    while(1)
    {
        obj2.cart(); // This takes itemcode picks data from menu file and fills object
        fstream wr2;
        wr2.open("C:\\Users\\rohit\\Desktop\\CPP_PROJECT\\bill.txt",ios::app); // Writes object to bill file
        wr2.write((char *)&obj2,sizeof(obj2));// writes object to bill file
        wr2.close();
        cout<<endl<<"Do You want to Add More items to Bill press 1 to add more item anything else to create bill";
        int choice;
        cin>>choice;
        if(choice!=1)
        {
            printbill(obj2.billno);

            break;
        }
    }
    fstream wr3;
    wr3.open("C:\\Users\\rohit\\Desktop\\CPP_PROJECT\\number.txt",ios::out);
    int m=obj2.billno+1+48;
    char c=(char)m;
    wr3.put(c);
    wr3.close();

}



void removeitem()
{

    // Input item code you want to delete

    int icode;
    cout<<endl<<"Enter item Code for Deletion";
    cin>>icode;

    //calculate number of objects in file

    fstream rd;
   // rd.open("d:\\menu.txt",ios::in);
    rd.open("C:\\Users\\rohit\\Desktop\\CPP_PROJECT\\menu.txt",ios::in);

   
    rd.seekg(0,ios::end);
    int s=rd.tellg();
    int count=s/sizeof(obj);
    rd.seekg(0,ios::beg);


    fstream wr;
    //wr.open("d:\\temp.txt",ios::out);
    wr.open("C:\\Users\\rohit\\Desktop\\CPP_PROJECT\\temp.txt",ios::out);


    //read each object from file one by one and match itemcode in object to icode that has been taken as input

    for(int i=1;i<=count;i++)
    {
        rd.read((char *)&obj,sizeof(obj));
        if(icode==obj.itemcode)
        {
            cout<<endl<<"Object Deleted";
        }
        else
        {
            wr.write((char *)&obj,sizeof(obj));

        }

    }
    //close file connections
    rd.close();
    wr.close();

    //delete menu.txt
    remove("C:\\Users\\rohit\\Desktop\\CPP_PROJECT\\menu.txt");

    //rename temp to menu
    rename("C:\\Users\\rohit\\Desktop\\CPP_PROJECT\\temp.txt","C:\\Users\\rohit\\Desktop\\CPP_PROJECT\\menu.txt");




}

void updateitem()
{

    // Input item code you want to delete

    int icode;
    cout<<endl<<"Enter item Code for Deletion";
    cin>>icode;

    //calculate number of objects in file

    fstream rd;
    rd.open("d:\\menu.txt",ios::in);
    rd.seekg(0,ios::end);
    int s=rd.tellg();
    int count=s/sizeof(obj);
    rd.seekg(0,ios::beg);


    fstream wr;
    wr.open("d:\\temp.txt",ios::out);


    //read each object from file one by one and match itemcode in object to icode that has been taken as input

    for(int i=1;i<=count;i++)
    {
        rd.read((char *)&obj,sizeof(obj));
        if(icode==obj.itemcode)
        {
            obj.accept();
            wr.write((char *)&obj,sizeof(obj));
            cout<<endl<<"Object Deleted";
        }
        else
        {
            wr.write((char *)&obj,sizeof(obj));

        }

    }
    //close file connections
    rd.close();
    wr.close();

    //delete menu.txt
    remove("d:\\menu.txt");

    //rename temp to menu
    rename("d:\\temp.txt","d:\\menu.txt");




}


void addmenu() // This function is not part of class but a normal function that we used to make in C
{
    obj.accept();
    fstream wr;
   // wr.open("d:\\menu.txt",ios::app);
   wr.open("C:\\Users\\rohit\\Desktop\\CPP_PROJECT\\menu.txt",ios::app);
    wr.write((char *) &obj,sizeof(obj)); //writing Object to file
    wr.close();
    cout<<endl<<"Menu Written Successfully";
}

void readmenu()
{
    fstream rd;
    //rd.open("d:\\menu.txt",ios::in);
    rd.open("C:\\Users\\rohit\\Desktop\\CPP_PROJECT\\menu.txt",ios::in);
    int s;
    rd.seekg(0,ios::end); // i have taken cursor to last of file
    s=rd.tellg();  // this will get me number of characters

//    cout<<"Size of file"<<s<<endl;
    rd.seekg(0,ios::beg);

    int c=s/sizeof(obj);
    cout<<"Number of objects are "<<c<<endl;

    for(int i=1;i<=c;i++)
    {

    rd.read((char *)&obj,sizeof(obj));
    obj.display();
    }
}
main()
{
    int e=0;
    while(e!=1)
    {
        cout<<endl<<"************************************************";
        cout<<endl<<"Press 1 to Add New Menu Item";
        cout<<endl<<"Press 2 to View Menu List";
        cout<<endl<<"Press 3 to remove Item from Menu";
        cout<<endl<<"press 4 to search an itemname from menu";
        // cout<<endl<<"Press 5 to update Item from Menu";
        cout<<endl<<"Press 5 to Raise New Invoice";
        cout<<endl<<"press 6 to search an itemcode from menu";
        cout<<endl<<"Press 7 to exit";
        int choice;
        cin>>choice;
        switch(choice)
        {
        case 1:
            {
            addmenu();
            break;
            }
        case 2:
            {
                readmenu();
                break;
            }
        case 3:
            {

                removeitem();
                break;
            }
        //case 4:
          //  {
            //    search();
              //  break;
          //  }
        case 4:
            {
                updateitem();
                break;
            }
        case 5:
            {
                raisebill();
                break;

            }
              case 6:
            {
                searching();
                break;
            }

        case 7
		:
            {
                e=1;
                break;

            }
      

        }

    }





}
