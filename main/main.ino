#include <StandardCplusplus.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <utility.h>

#include "filterKmapResults.h"
#include "operation.h"
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

/***Karnaugh map
* This program make a simulation to Karnaugh map with any number of variables
* and minimizing it
*/

/***
* Program algorithm
* 1- Reading inputs (ones and don't care) from user 
* 2- Starting comparing ones and don't care 
* 3- Converte comparelified result to alphabetical terms 
* 4- filter results to avoid excess terms and provde all possible slovings
*/

//this class is using for implementing k-map by
//following algorithm
class Kmap : public FilterKmapTerms, public SOPtoPOS
{
private:
    int temp, temp1, temp2, temp3; //temprature variables
    
  void invokeKmap();
  
public:
  
  Kmap () 
  {
      invokeKmap();
  }
};//end kmap

/***
  The main function of the program that implement K-map by:
  1- prompting for k-map type by its variable's number
  2- prompting for one's position by getPos function
  3- prompting for don't care position by getPos function
  4- Minimizing and getting results
*/

void Kmap ::invokeKmap()
  {
    char tempChar;           //temprature character 
    vector<char>result;      //Saving results
    vector<vector<char>> filterResults; //results after being filtered
  do
  {
    
    //first step prompting for type

    //system("cls");  //clear windows
    guideWin(1);     //invoke guide windows
    
    //prompting for type
    //cout<<"Please, enter your k-map type (Variables number, Maximum 26):";
    Serial.println("Please, enter your k-map type (Variables number, Maximum 4):");
    do
    {
    //type = readInt( temp = 0, false); //read type as an positive integer number
    //not use readInt function
    //get number from serial
    while (Serial.available()==0)
    {
    }
      type=(int)(Serial.read())-48;

    
    if(type > 4)
        Serial.println("Please, enter your k-map type (Variables number, Maximum 4):");

    }while(type > 4);
    hasEnteredType = true;

    //second step prompting for ones
//    system("cls");  //clear windows
    guideWin(2);     //reinvoke guide windows
    getPos(ones, "one");           //getOnes

    //third step prompting for don't care
//    system("cls");  //clear windows
    guideWin(3);     //reinvoke guide windows
    getPos(dCare, "don't care");   //get don't care

    //fourth step prompting for don't care
//    system("cls");  //clear windows
    guideWin(4);     //reinvoke guide windows
    //cout<<"Choose Result's type:\n"
    //  <<"1-Some of product.\n"
    //  <<"2-Product of some.\n";
    Serial.println("Choose Result's type:");
    Serial.println("1-Some of product.\n");
    Serial.println("2-Product of some.\n");
    
    do
    {
    while (Serial.available()==0)
    {
    }    
      tempChar=(Serial.read());
    
    if(tempChar == 49)
    {
      SOP = true;
    }
    else if(tempChar == 50)
    {
      SOP = false;
    }
    else
    {
      Serial.println("wrong input");
    }

    }while(tempChar != 49 && tempChar != 50);
    //fifth step: getting results
//    system("cls");  //clear windows
    guideWin(5);     //reinvoke guide windows
    result = minimize(ones, dCare); //Solving by minimizing
    
    if( result.size() != 1 ||   //not full or empty maps
      ( result[0] != 48 && result[0] != 49 ) )
    {
      filterResults.clear();
      filterResults =  filter(result,ones); //filter result from unessential terms
      //print results
    //cout<<"Minimization = ";
    Serial.print("Minimization = ");
    
    for(int temp = 0; temp < filterResults.size(); temp++)
    {
      if(filterResults.size() > 1) 
        //cout<<endl<<temp+1<<" - ";
        Serial.println();
        Serial.print(temp+1);
        Serial.print(" - ");
      if(SOP == false) convSopToPos(filterResults[temp]);

      for(int temp1 = 0; temp1 < filterResults[temp].size(); temp1++) 
      //cout<<filterResults[temp][temp1];
      Serial.print(filterResults[temp][temp1]);
    }

    }
    else
      //cout<<"Minimization = "<<result[0]<<endl;
    Serial.print("Minimization = ");
    Serial.println(result[0]);
        //cout<<endl; //going to next line
    Serial.println();
    
    //tempChar = getch ();       //reading a digit for finishing minimize
    while (Serial.available()==0)
    {
    }    
      tempChar=(Serial.read());

    if(tempChar == 27) break;  //break after esc
    else
    {
      //empty type, ones and dCare
      ones.clear();
      dCare.clear();
      hasEnteredType = false;
    }
  }while(true);
  
}//end invoke kmap





void loop() {
  // put your main code here, to run repeatedly:
  Kmap k1;
  }
