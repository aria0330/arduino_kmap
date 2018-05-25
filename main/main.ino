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
    
  
public:
  
  Kmap () 
  {
  }
 vector<char>  invokeKmap(int type_in,vector<int> ones_in,vector<int> dcares_in);


};//end kmap

/***
  The main function of the program that implement K-map by:
  1- prompting for k-map type by its variable's number
  2- prompting for one's position by getPos function
  3- prompting for don't care position by getPos function
  4- Minimizing and getting results
*/

vector<char> Kmap ::invokeKmap(int type_in,vector<int> ones_in,vector<int> dcares_in)
  {
    char tempChar;           //temprature character 
    vector<char>result;      //Saving results
    vector<vector<char>> filterResults; //results after being filtered
    
    type=type_in;
    hasEnteredType = true;
  for(int i=0;i<ones_in.size();i++){
    ones.push_back(ones_in[i]);
    }
  for(int i=0;i<dcares_in.size();i++){
    dCare.push_back(dcares_in[i]);
    }
    
    SOP=true;
    result = minimize(ones, dCare); //Solving by minimizing
    
    if( result.size() != 1 ||   //not full or empty maps
      ( result[0] != 48 && result[0] != 49 ) )
    {
      filterResults.clear();
      filterResults =  filter(result,ones); //filter result from unessential terms
      result.clear();
    for(int temp = 0; temp < filterResults.size(); temp++)
    {
      for(int temp1 = 0; temp1 < filterResults[temp].size(); temp1++) {
      //cout<<filterResults[temp][temp1];
      //Serial.print(filterResults[temp][temp1]);
      result.push_back(filterResults[temp][temp1]);
      }
    }

    }

  return result;
}//end invoke kmap





void loop() {
  // put your main code here, to run repeatedly:
  vector<char> result;
  vector<int> ones_input,dCare_input;
  int tmp;
  
      while(true) //still reading until read q
      {
      
        Serial.print("Please, enter one's position (100 for stopping) : ");
        while (Serial.available()==0)
            {
            }
                tmp=(int) Serial.parseInt();
        if(tmp != (100)) 
          {
            ones_input.push_back(tmp); //save position
            Serial.println(tmp);
            Serial.println("");
          }
        else 
        {
          Serial.println();
          break;
        }
      }//end while


  
  Kmap k1;
  result = k1.invokeKmap(4,ones_input,dCare_input);

  Serial.print("result : ");

  for(int i=0;i<result.size();i++){
      Serial.print(result[i]);
    }
    Serial.println();
  
  }
