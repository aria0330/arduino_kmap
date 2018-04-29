#ifndef SETKMAP_H
#define SETKMAP_H


#include <iostream>
#include <vector>
#include <iomanip>
//#include <conio.h>
#include <string>

using namespace std;


//this class is using for prompting k-map details from user
//and setting k-map in order to solveing it 

class setKmap 
{
protected:

		int	type,				//k-map type 2,3, ....
			termCount,          //term's count
			saverCount;			//saving savers
		vector<int>ones;         //Saving ones position
		vector<int>dCare;        //Saving dont care position
		bool hasEnteredType,      //check entering type of not
			SOP;			      // ture for some of product
		                          // false for product of some

	void guideWin (short cursor);
	int readInt (int &count, bool negative ); 
	void getPos (vector<int> &pos, String name_pos);
	void setTerms (vector<int> ones, vector<vector<int> > &terms);  
	
	setKmap(): hasEnteredType(false) {}

};//end kmap


/***
* guide window helps user to solving K-map
* its argument curor for moving cursor during minimize
*/

void setKmap ::guideWin (short cursor)
{
//	cout<<"This program has devolped to solve Karnaugh map with any number of variables\n\n"
//		<<"Solving steps:\n";
		Serial.println("This program has devolped to solve Karnaugh map with any number of variables");
		Serial.println("");
		Serial.println("");
		Serial.println("Solving steps:");

		//if(cursor == 1) cout<<"==>    "; else cout<<"       ";
		if(cursor == 1) Serial.println("==>    ");
		else Serial.println("       ");
		//cout <<"1- Enter k-map type (Number of variables)\n";
		Serial.println("1- Enter k-map type (Number of variables)");

		// if(cursor == 2) cout<<"==>    "; else cout<<"       ";
		if(cursor == 2) Serial.println("==>    ");
		else Serial.println("       ");

		// cout<<"2- Enter one's positions (-1 for stopping)\n";
		Serial.println("2- Enter one's positions (-1 for stopping)");

		// if(cursor == 3) cout<<"==>    "; else cout<<"       ";
		if(cursor == 3) Serial.println("==>    ");
		else Serial.println("       ");
		// cout<<"3- Enter don't care positions (-1 for stopping)\n";
		Serial.println("3- Enter don't care positions (-1 for stopping)");

		// if(cursor == 4) cout<<"==>    "; else cout<<"       ";
		if(cursor == 4) Serial.println("==>    ");
		else Serial.println("       ");
		// cout<<"4- Choose result's type (SOP or POS):\n";
		Serial.println("4- Choose result's type (SOP or POS):");


		// if(cursor == 5) cout<<"==>    "; else cout<<"       ";
		if(cursor == 5) Serial.println("==>    ");
		else Serial.println("       ");		
		// cout<<"5- Solving of your k-map\n\n";
		Serial.println("5- Solving of your k-map");
		Serial.println("");


		//show type
		//if(hasEnteredType) cout<<"Type : "<<type<<endl;
		if(hasEnteredType){
			Serial.print("Type : ");
			Serial.println(type);
		}

		//show ones
		if(ones.size() > 0) 
		{
			//cout<<"Ones :";
			Serial.print("Ones : ");
			for(int temp = 0; temp < ones.size(); temp++)
			{
				//cout<<ones[temp];
				Serial.print(ones[temp]);
				if(temp < ones.size() -1 )
					//cout<<",";
					Serial.print(",");
			}
			//cout<<endl;
			Serial.println("");
		}

		//show don't care
		if(dCare.size() > 0) 
		{
			//cout<<"Don't Care :";
			Serial.print("Don't Care :");
			for(int temp = 0; temp < dCare.size(); temp++)
				{
					//cout<<dCare[temp];
					Serial.print(dCare[temp]);
					if(temp < dCare.size() -1 )
					//cout<<",";
					Serial.print(",");
				}
			Serial.println("");
		}

		//cout<<"*******************************************************************************\n";
		Serial.println("*******************************************************************************");
}//end guide windows

/***
* This function is reading positive integer numbers and 
* only negative 1 (-1) and avoid receiving any other 
* inputs to the program its argument gives the abilty 
*of reading -1 by true, or don't read by false, 
*but default case is reading both 
*count read digit's count
*/
/*
int setKmap :: readInt (int &count, bool negative = true) 
{
	char tempChar;  //for reading characters
	int intNum =  0;//for getting numers
	bool sign = true,        //saving sign, true for pos, false for neg
	     hasValue = false;  //check    
	
	while(intNum < pow(2.0,30))  //reading until breaking
	{ 
		
		tempChar = getch();   //read character by character

		//searching for negative sign in first character for negative number
		if(negative && count == 0 && tempChar == '-')
		{
			sign= false; //the sign of the number is negative
			cout<<tempChar; //print -
			count++;
		}
		
		else if( ( !sign && tempChar == 49 && intNum == 0)                 //-1 condition
		       || (sign && tempChar>47 && tempChar < 58)   )  //positive condition
		{
			if(intNum < pow (2.0 , 31))
			{
			intNum = intNum * 10 + (tempChar - 48); //add the value to intNum
			cout<<tempChar; //print char
			
			//checking intNum status
			if( !hasValue)       //if intNum doesn't has any value
				hasValue = true; //assign it has a value
			count++;
			}
		}//end Numerical characters
		
		//exit function after spaces if intNum has a value
		else if ( hasValue  && (tempChar == 13 || tempChar == ' ' || tempChar == '\t' ))
		{
			break;          //exit function
		}//end spaces condition

		// backslach condition
		else if(tempChar == '\b' && count > 0)
		{
			cout<<"\b \b"; //remove number from screen
			intNum /= 10;  //remove Character value
			count--;       //decrease count

			if(sign == false && count == 0) //removing negative sign after writing it
				sign = true;                //return it to positive

			if( count == 0 || (count == 1 && sign == false) )
				hasValue = false;
		}//end backslach condition

		//other characters (wrong inputs)
		else 
			cout<<"\a";

		
	}//end while
	
	return (sign)?intNum:-1*intNum; //return integer num

}//end readInt

*/
/***
*	getpos (get positions)
*   is prompting for positions of name sending as  
*	argument and saving them in pos's argument
*   if positions are locating in the k-map field
*   it will save it, else it will warn you
*   It is stilling reading until read -1
*/

void setKmap :: getPos (vector<int> &pos, String name_pos)
{
			int position_pos; //for reading positions
			int count ;    //position count digits

			while(true) //still reading until read -1
			{
			
				count = 0;
				//prompting for one's positions
			//cout<<"Please, enter " << name << "'s position (-1 for stopping) : ";
				Serial.print("Please, enter ");
				Serial.print(name_pos);
				Serial.print("'s position (q for stopping) : ");

				//reading one by one
				//position = readInt ( count ) ;
				while (Serial.available()==0)
  					{
    				}
                position_pos=(int)(Serial.read())-48;

				//check position locations
				//as it is locating in this type of k-map
				if(position_pos != (113-48) && position_pos < pow(2.0,type)) 
					{
						pos.push_back(position_pos); //save position
						//cout<<endl;              //going to next line
						Serial.println("");
					}
				
				//breaking number
				//else if(position == -1)
				else if(position_pos == (113-48))//ascii q ==113	
						break;

				//other wrong cases
				else 
				{
					//remove inputs and prompting sentense 
					//for(int temp = 0; temp < count+55; temp++)
					//	cout<<"\b \b"; //remove a digit
					Serial.println("wrong inputs");

				}
			}//end while
}//end getPos

/***
*  This function is :
*  1- saving k-maps (ones and don't care) position with its 
*     coordinatesin in (vector) terms
*  2- Assuming term's count
*/

	void setKmap :: setTerms (vector<int> pos, vector<vector<int> > &terms)
	
	{
		//covering ones
		for(int temp =0; temp < pos.size(); temp++)
		{
		
			//prepare a new term for a new position
			terms.push_back( vector <int> () );
	
			//covering coordinate
		for(int temp1 = 0; temp1 < type; temp1++)
		{
			/*save a one's coordinate*/
			
			//save one coordinate
			terms[termCount].insert(terms[termCount].begin(), (pos[temp] % 2)); 
			//remove the coordintae from its one
			pos[temp] /= 2;                                                          
		}//end covering coordinate loop

				termCount++; //increase terms
		}//end covering coordinate loop 

	}//end setTerms

#endif
