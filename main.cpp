#include <iostream>
#include <string>
#include <cmath>
using namespace std;
// Array to hold 16 keys
string round_keys[16];
// String to hold the plain text
string pt;
int abda;
string round_keys_bin[48];
bool checko = false;
bool breako = false;
int Box1[4][16] = { 14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7, 
        0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8, 
        4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0, 
        15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13  };
        
int Box2[4][16] =
 {
 15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10, 
        3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5, 
        0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15, 
        13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9};

int Box3[4][16] = {
10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8, 
        13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1, 
        13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7, 
        1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12 

};

int Box4[4][16] = {

        7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15, 
        13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9, 
        10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4, 
        3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14
};
        
int Box5[4][16] =
{
       2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9, 
        14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6, 
        4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14, 
        11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3 


};       

int Box6[4][16] =
 {
 	
 	12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11, 
        10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8, 
        9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6, 
        4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13 
 };
        
int Box7[4][16] =
{

   4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1, 
        13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6, 
        1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2, 
        6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12 
};


int Box8[4][16] =
{
	
	13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7, 
        1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2, 
        7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8, 
        2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11 


};      
// Function to convert a number in decimal to binary
string convertDecimalToBinary(int decimal)
{
	string binary;
    while(decimal != 0) {
		binary = (decimal % 2 == 0 ? "0" : "1") + binary; 
		decimal = decimal/2;
	}
	while(binary.length() < 4){
		binary = "0" + binary;
	}
    return binary;
}

// Function to convert a number in binary to decimal
int convertBinaryToDecimal(string binary)
{
    int decimal = 0;
	int counter = 0;
	int size = binary.length();
	for(int i = size-1; i >= 0; i--)
	{
    	if(binary[i] == '1'){
        	decimal += pow(2, counter);
    	}
    counter++;
	}
	return decimal;
}

string shift_left_once(string key_chunk){ 
    string shifted="";  
        for(int i = 1; i < 28; i++){ 
            shifted += key_chunk[i]; 
        } 
        shifted += key_chunk[0];   
    return shifted; 
} 
// Function to do a circular left shift by 2
string shift_left_twice(string key_chunk){ 
    string shifted=""; 
    for(int i = 0; i < 2; i++){ 
        for(int j = 1; j < 28; j++){ 
            shifted += key_chunk[j]; 
        } 
        shifted += key_chunk[0]; 
        key_chunk= shifted; 
        shifted =""; 
    } 
    return key_chunk; 
}

string Xor(string a, string b){ 
	string result = ""; 
	int size = b.size();
	for(int i = 0; i < size; i++){ 
		if(a[i] != b[i]){ 
			result += "1"; 
		}
		else{ 
			result += "0"; 
		} 
	} 
	return result; 
} 

void generate_keys(string key){
	// The PC1 table
	int pc1[56] = {
	57,49,41,33,25,17,9, 
	1,58,50,42,34,26,18, 
	10,2,59,51,43,35,27, 
	19,11,3,60,52,44,36,		 
	63,55,47,39,31,23,15, 
	7,62,54,46,38,30,22, 
	14,6,61,53,45,37,29, 
	21,13,5,28,20,12,4 
	};
	
int pc2[48] = { 
	14,17,11,24,1,5, 
	3,28,15,6,21,10, 
	23,19,12,4,26,8, 
	16,7,27,20,13,2, 
	41,52,31,37,47,55, 
	30,40,51,45,33,48, 
	44,49,39,56,34,53, 
	46,42,50,36,29,32 
	}; 
	
	
	string perm_key =""; 
	for(int i = 0; i < 56; i++){ 
		perm_key+= key[pc1[i]-1]; 
	} 
		// 2. Dividing the key into two equal halves
	string left= perm_key.substr(0, 28); 
	string right= perm_key.substr(28, 28); 
	for(int i2=0; i2<16; i2++){ 
		// 3.1. For rounds 1, 2, 9, 16 the key_chunks
		// are shifted by one.
		if(i2 == 0 || i2 == 1 || i2==8 || i2==15 ){
			left= shift_left_once(left); 
			right= shift_left_once(right);
		} 
		// 3.2. For other rounds, the key_chunks
		// are shifted by two
		else{
			left= shift_left_twice(left); 
			right= shift_left_twice(right);
		}
        string combined_key = left + right;
		string round_key = ""; 
		// Finally, using the PC2 table to transpose the key bits
		for(int i = 0; i < 48; i++){ 
			round_key += combined_key[pc2[i]-1]; 
		}   
		round_keys[i2] = round_key; 
	} 

}

string DES(){ 
	// The initial permutation table 
	int initial_permutation[64] = { 
	58,50,42,34,26,18,10,2, 
	60,52,44,36,28,20,12,4, 
	62,54,46,38,30,22,14,6, 
	64,56,48,40,32,24,16,8, 
	57,49,41,33,25,17,9,1, 
	59,51,43,35,27,19,11,3, 
	61,53,45,37,29,21,13,5, 
	63,55,47,39,31,23,15,7 
	}; 
	// The expansion table
	int expansion_table[48] = { 
	32,1,2,3,4,5,4,5, 
	6,7,8,9,8,9,10,11, 
	12,13,12,13,14,15,16,17, 
	16,17,18,19,20,21,20,21, 
	22,23,24,25,24,25,26,27, 
	28,29,28,29,30,31,32,1 
	}; 

int substition_boxes[8][4][16]=  
	{{ 
        14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7, 
        0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8, 
        4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0, 
        15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13 
    }, 
    { 
        15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10, 
        3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5, 
        0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15, 
        13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9 
    }, 
    { 
        10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8, 
        13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1, 
        13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7, 
        1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12 
    }, 
    { 
        7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15, 
        13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9, 
        10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4, 
        3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14 
    }, 
    { 
        2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9, 
        14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6, 
        4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14, 
        11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3 
    }, 
    { 
        12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11, 
        10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8, 
        9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6, 
        4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13 
    }, 
    { 
        4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1, 
        13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6, 
        1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2, 
        6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12 
    }, 
    { 
        13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7, 
        1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2, 
        7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8, 
        2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11 
    }};
    
    

int permutation_tab[32] = { 
	16,7,20,21,29,12,28,17, 
	1,15,23,26,5,18,31,10, 
	2,8,24,14,32,27,3,9,
	19,13,30,6,22,11,4,25 
	}; 
	// The inverse permutation table
	int inverse_permutation[64]= { 
	40,8,48,16,56,24,64,32, 
	39,7,47,15,55,23,63,31, 
	38,6,46,14,54,22,62,30, 
	37,5,45,13,53,21,61,29, 
	36,4,44,12,52,20,60,28, 
	35,3,43,11,51,19,59,27, 
	34,2,42,10,50,18,58,26, 
	33,1,41,9,49,17,57,25 
	};
	//1. Applying the initial permutation
  	string perm = ""; 
	for(int i = 0; i < 64; i++){ 
		perm += pt[initial_permutation[i]-1]; 
	}
	if(checko==true)
{
cout << "Plaintext wird permutiert.." << endl;
cout << endl;
system("Pause");	
cout << "            " << perm << endl;
system("pause");
}
int merker=0;	
int k = 1;	

//initial_permutation[64];

if(checko == false)
{
cout << "Plaintext wird zuerst permutiert..." << endl;
system("Pause");
cout << "<<< Eingangspermutation >>>" <<endl;
for (int ipp = 0; ipp < 64; ipp++)
{
	
	if(initial_permutation[ipp] < 10)
	cout << initial_permutation[ipp] << "  ";
	else
	cout << initial_permutation[ipp] << " ";
	if((ipp+1) % 8 == 0)
	{
	
	  cout << endl;
	}
	  
	
}
}


if(checko == false)
{

bool seto = true; 
cout << endl;
	for(int pp = 1; pp <= 64; pp++)
	{  
	   
	   
	   
	   if(merker == 0)   
	  
	  {
	  
	   for(int bez = 1; bez <= 8; bez++)
	   {     
	   		 if(bez==1 && seto ==false)
	   		 	cout << k << ".Byte" << " ";
	        if(seto)
			 {
			 	if(bez == 1)
			 	cout << "       ";
			    cout << bez << " "	;
			 
	         }
	         if(bez ==8 && seto == true)
	        {
			  cout << endl;
			  cout << k << ".Byte" << " ";  
		    }
			 if(bez == 8)
	        {
	         k++;	
			// cout << "\n";
			 cout << "\n";
			  //if(seto)
			 // cout << "\n";
	         merker = 1;
			cout << "       ";
			seto = false;
			}
	   }    
		}//cout << endl;
		 
		cout << pt[pp-1] << " ";
		if(pp % 8==0 &&  pp !=0)
		{
		  cout << endl;
	      merker = 0;
	    }
	}
}
	cout << endl;
	if(checko == false)
	cout << "Schreiben Sie die ersten drei Bits nach der Eingangspermutationsfunktion" << endl;
	
   string aa,bb,cc,dd,ee,ff,gg,hh;
   
   //bb = perm[0] + perm[1] + perm[2];
    
	bb = perm[0];
	bb+= perm[1];
	bb+= perm[2];
//	cout << bb << endl;
   
  // cout << bb << endl;
   bool loopi = true;
   
   if(checko==false)
   while(loopi)
   {
	 cin >> aa;
    if(bb==aa)	
	{
		cout << "RICHTIG" << endl;
	    loopi = false;
	}
	else
	  cout << "FALSCH: Geben Sie es nochmal." << endl;
   }
	//cout << endl;
	
	if(checko==false)
	cout << "Schreiben Sie die letzten drei Bits nach der Eingangspermutationsfunktion" << endl;
	
	
	bool loopi2 = true;
   
     bb = perm[61];
     bb += perm[62];
     bb += perm[63];
    //cout << bb << endl;
   if(checko==false)
   while(loopi2)
   {
	 cin >> cc;
    if(bb==cc)	
	{
		cout << "RICHTIG" << endl;
	    cout << endl;
	    cout << endl;
        cout << "So sieht die Permutation des Plaintextes aus" << endl;
        cout << perm << endl;
        system("pause");
		loopi2 = false;
	}
	else
	  cout << "FALSCH: Geben Sie es nochmal." << endl;
   }
	
	cout << endl;
	
	
	//cout << "Initial Permutation " << perm << endl;  
	// 2. Dividing the result into two equal halves 
	string left = perm.substr(0, 32); 
	string right = perm.substr(32, 32);
	// The plain text is encrypted 16 times  
	system("cls");
	
	cout << "Bits werden in 2 Haelften geteilt" << endl;
	
	cout << "     linker Block                    " << "     rechter Block      " << endl;
	cout << left << " "  << right << endl;;
	system("PAUSE");
	cout << "32 Bits von der rechten Haelfte werden jetzt auf 48 Bits aufgepumpt" << endl;
	system("Pause");
	system("cls");	
	//cout << right << endl;
	//cin >>  test;


    if(checko==false)
{
	 	 cout << "<<< Expansionsfunktion >>>" << endl;
   for(int expr = 0; expr < 48; expr++)
	{
		if(expansion_table[expr] < 10)
		{cout << expansion_table[expr] << "  ";}
		else
		  cout << expansion_table[expr] << " ";
		if((expr+1) % 6 == 0)
		   cout << endl;
	 } 
	
	//cout << "RIGHT: " << right << endl;
	 for(int re = 0; re < 32; re ++)
	 {
	 	if(re < 10)
	 	cout << re+1 << "  ";
	 	else
	 	cout << re+1 << " ";
	 }
	cout << endl;
	for(int ri = 0; ri < 32; ri++)
	 {
	 	if(ri < 9)
	 cout << right[ri] << "  ";
      else if (ri == 10 || ri == 9)
      cout << right[ri] << "   ";
	 
	 if(ri >= 11)
	 cout << right[ri] << "  ";
	 }
	 cout << endl;
}
	int kii,zii;
	
//	if(checko == false)
	
	for(int i=0; i<16; i++) { 
    	string right_expanded = ""; 
		// 3.1. The right half of the plain text is expanded
    	
		kii = i;
		zii = i;
		for(int i = 0; i < 48; i++) { 
      		right_expanded += right[expansion_table[i]-1];      			
    };  
       int rr1;
       string rrr3;
	 //  cout << right_expanded << endl;
	  
	  if(kii == 0 && checko == false)
	  {
	  
	   for(int rr = 1; rr <=48; rr++)
	    {
	    	if(rr==1 || rr == 7 || rr == 13 || rr == 19 || rr == 25 || rr == 31 || rr == 37 || rr == 43 )
	    	  {
	    	  	rr1 = rr;
			  
			  continue;
	          }
			//if(rr==6 || rr == 12 || rr == 18 || rr == 24 || rr == 30 || rr == 36 || rr == 42)
		    // continue;
		    if(rr % 6 != 0)
		    {
			cout << right_expanded[rr-1];
		    rrr3 += right_expanded[rr-1];
			}
			else if ( rr % 6 == 0)
		      {
	                        		    
			    cout << endl;
			   
			   cout << "Geben Sie für das Halbbyte die neu zugekommen zwei Bits anhand der Expansionsfunktion\n" 
			   << "Folgende Halbytereihenfolge gibt es: "<< "x" << rrr3 <<"y\n" << 
			    "x = ist das erste erweiterte Bit\n" 
			   << "y = ist das zweite erweiterte Bit\n"; 
			   rrr3 = "";
			   char x,y;
			   bool xy = true;
			   while(xy)
			   {
			   cout << "x = "; cin >> x;
			   cout << "y = "; cin >> y;
			    if(x == right_expanded[rr1-1] && y == right_expanded[rr-1])
			       {
				   xy = false;
			        cout << "RICHTIG" << endl;
			        string check;
					cin >> check;
				
			        system("cls");
				        if(rr!=48)
				       cout << "<<< Expansionsfunktion  >>>" << endl;
	if(rr!=48)
	for(int expr = 0; expr < 48; expr++)
	{
		if(expansion_table[expr] < 10)
		{cout << expansion_table[expr] << "  ";}
		else
		  cout << expansion_table[expr] << " ";
		if((expr+1) % 6 == 0)
		   cout << endl;
	 } 
      if(rr!=48)	 
	  for(int re = 0; re < 32; re ++)
	 {
	 	if(re < 10)
	 	cout << re+1 << "  ";
	 	else
	 	cout << re+1 << " ";
	 }
	cout << endl;
	if(rr!=48)
	for(int ri = 0; ri < 32; ri++)
	 {
	 	if(ri < 9)
	 cout << right[ri] << "  ";
      else if (ri == 10 || ri == 9)
      cout << right[ri] << "   ";
	 
	 if(ri >= 11)
	 cout << right[ri] << "  ";
	 }
	 cout << endl;
				   
				   }
				   else
				   {
				    cout << "FALSCH" << endl;
				   }
			   }
			   //cout << right_expanded[rr1-1]  << endl;
			   //cout << right_expanded[rr-1] << endl;
			  } 
		    
		}
	   cout << endl;
	//string test2;
//	cout << right_expanded[0] << endl;
	 // cin >> test2;
}
	// 3.3. The result is xored with a key
		string xored = Xor(round_keys[i], right_expanded);  
		string res = ""; 
		if((kii==0  && abda == 0) || checko == true && abda <= (kii+1) && breako==false)
		{
		cout << "Runde: "	<< kii+1 << endl;
		cout << "rechter Block mit 48 Bits: " << right_expanded << endl;
		//cout << "                           " << "XOR" << endl;
		cout << "Rundschluessel:            " << round_keys[i] << endl;
		cout << "                           " << "XOR" << endl;
		cout << "                           " << "------------------------------------------------" << endl;
		cout << "                           " << xored;
		system("PAUSE");
		if(checko==false)
		system("cls");
	    }
		// 3.4. The result is divided into 8 equal parts and passed 
		// through 8 substitution boxes. After passing through a 
		// substituion box, each box is reduces from 6 to 4 bit



	
//}
		//cout << "XOR " << xored << endl;
		for(int i=0;i<8; i++){ 
			// Finding row and column indices to lookup the
			// substituition box
      		if(kii==0 && checko == false) 
			switch(i)
{

	case 0:	
	cout << "<<< S-Box 1 >>>" << endl;
	for(int cs = 0; cs < 6; cs++)
	{
		cout << xored[cs];
	}
	cout << endl;
	for (int zzz = 0; zzz < 49; zzz++)
    cout <<"_";
	cout << "\n";		
	
		for(int xxx = 0; xxx < 4; xxx++)
		 {
		 for(int yyy = 0; yyy < 16; yyy++)
		 {
		 	if(yyy==0)
			  {
			  cout <<  "|";
		      cout << Box1[xxx][yyy];
		     if(Box1[xxx][yyy] < 10) 
		      cout << " |";
		      else
		    cout << "|";
		   }
		  else{
		  
			 if(Box1[xxx][yyy] < 10  )
		 	{
		 	 // if(yyy==0)
			 // cout <<  "qqq"; 
			  
			  cout << Box1[xxx][yyy] << " |"; 
		    }
		 	else 
		 	{
			 cout  << Box1[xxx][yyy] << "|";
		    }
		 }
	   	
	}
	cout << "\n";
	for (int zzz = 0; zzz < 49; zzz++)
cout <<"_";

cout << endl;
}
break;





case 1:
	cout << "<<< S-Box 2 >>>" << endl;
	for(int cs = 6; cs < 12; cs++)
	{
		cout << xored[cs];
	}
	cout << endl;
	for (int zzz = 0; zzz < 49; zzz++)
    cout <<"_";
	cout << "\n";		
	
		for(int xxx = 0; xxx < 4; xxx++)
		 {
		 for(int yyy = 0; yyy < 16; yyy++)
		 {
		 	if(yyy==0)
			  {
			  cout <<  "|";
		      cout << Box2[xxx][yyy];
		     if(Box2[xxx][yyy] < 10) 
		      cout << " |";
		      else
		    cout << "|";
		   }
		  else{
		  
			 if(Box2[xxx][yyy] < 10  )
		 	{
		 	 // if(yyy==0)
			 // cout <<  "qqq"; 
			  
			  cout << Box2[xxx][yyy] << " |"; 
		    }
		 	else 
		 	{
			 cout  << Box2[xxx][yyy] << "|";
		    }
		 }
	   	
	}
	cout << "\n";
	for (int zzz = 0; zzz < 49; zzz++)
cout <<"_";

cout << endl;
	
}	break;


case 2:
    cout << "<<< S-Box 3 >>>" << endl;	
	for(int cs = 12; cs < 18; cs++)
	{
		cout << xored[cs];
	}
	cout << endl;
	for (int zzz = 0; zzz < 49; zzz++)
    cout <<"_";
	cout << "\n";		
	
		for(int xxx = 0; xxx < 4; xxx++)
		 {
		 for(int yyy = 0; yyy < 16; yyy++)
		 {
		 	if(yyy==0)
			  {
			  cout <<  "|";
		      cout << Box3[xxx][yyy];
		     if(Box3[xxx][yyy] < 10) 
		      cout << " |";
		      else
		    cout << "|";
		   }
		  else{
		  
			 if(Box3[xxx][yyy] < 10  )
		 	{
		 	 // if(yyy==0)
			 // cout <<  "qqq"; 
			  
			  cout << Box3[xxx][yyy] << " |"; 
		    }
		 	else 
		 	{
			 cout  << Box3[xxx][yyy] << "|";
		    }
		 }
	   	
	}
	cout << "\n";
	for (int zzz = 0; zzz < 49; zzz++)
cout <<"_";

cout << endl;
	

}
break;

case 3:
	cout << "<<< S-Box 4 >>>" << endl;
	for(int cs = 18; cs < 24; cs++)
	{
		cout << xored[cs];
	}
	cout << endl;
	for (int zzz = 0; zzz < 49; zzz++)
    cout <<"_";
	cout << "\n";		
	
		for(int xxx = 0; xxx < 4; xxx++)
		 {
		 for(int yyy = 0; yyy < 16; yyy++)
		 {
		 	if(yyy==0)
			  {
			  cout <<  "|";
		      cout << Box4[xxx][yyy];
		     if(Box4[xxx][yyy] < 10) 
		      cout << " |";
		      else
		    cout << "|";
		   }
		  else{
		  
			 if(Box4[xxx][yyy] < 10  )
		 	{
		 	 // if(yyy==0)
			 // cout <<  "qqq"; 
			  
			  cout << Box4[xxx][yyy] << " |"; 
		    }
		 	else 
		 	{
			 cout  << Box4[xxx][yyy] << "|";
		    }
		 }
	   	
	}
	cout << "\n";
	for (int zzz = 0; zzz < 49; zzz++)
cout <<"_";	
cout << endl;
}
	break;





case 4:
	cout << "<<< S-Box 5 >>>" << endl;
	for(int cs = 24; cs < 30; cs++)
	{
		cout << xored[cs];
	}
	cout << endl;
  for (int zzz = 0; zzz < 49; zzz++)
    cout <<"_";
	cout << "\n";		
	
		for(int xxx = 0; xxx < 4; xxx++)
		 {
		 for(int yyy = 0; yyy < 16; yyy++)
		 {
		 	if(yyy==0)
			  {
			  cout <<  "|";
		      cout << Box5[xxx][yyy];
		     if(Box5[xxx][yyy] < 10) 
		      cout << " |";
		      else
		    cout << "|";
		   }
		  else{
		  
			 if(Box5[xxx][yyy] < 10  )
		 	{
		 	 // if(yyy==0)
			 // cout <<  "qqq"; 
			  
			  cout << Box5[xxx][yyy] << " |"; 
		    }
		 	else 
		 	{
			 cout  << Box5[xxx][yyy] << "|";
		    }
		 }
	   	
	}
	cout << "\n";
	for (int zzz = 0; zzz < 49; zzz++)
cout <<"_";	
cout << endl;
}	
	
break;	
	
case 5:
	   cout << "<<< S-Box 6 >>>" << endl;
		for(int cs = 30; cs < 36; cs++)
	{
		cout << xored[cs];
	}
	cout << endl;
	
	for (int zzz = 0; zzz < 49; zzz++)
    cout <<"_";
	cout << "\n";		
	
		for(int xxx = 0; xxx < 4; xxx++)
		 {
		 for(int yyy = 0; yyy < 16; yyy++)
		 {
		 	if(yyy==0)
			  {
			  cout <<  "|";
		      cout << Box6[xxx][yyy];
		     if(Box6[xxx][yyy] < 10) 
		      cout << " |";
		      else
		    cout << "|";
		   }
		  else{
		  
			 if(Box6[xxx][yyy] < 10  )
		 	{
		 	 // if(yyy==0)
			 // cout <<  "qqq"; 
			  
			  cout << Box6[xxx][yyy] << " |"; 
		    }
		 	else 
		 	{
			 cout  << Box6[xxx][yyy] << "|";
		    }
		 }
	   	
	}
	cout << "\n";
	for (int zzz = 0; zzz < 49; zzz++)
cout <<"_";	
cout << endl;
}
	break;  
			  
		case 6:
			cout << "<<< S-Box 7 >>>" << endl;
	for(int cs = 36; cs < 42; cs++)
	{
		cout << xored[cs];
	}
	cout << endl;
		for (int zzz = 0; zzz < 49; zzz++)
    cout <<"_";
	cout << "\n";		
	
		for(int xxx = 0; xxx < 4; xxx++)
		 {
		 for(int yyy = 0; yyy < 16; yyy++)
		 {
		 	if(yyy==0)
			  {
			  cout <<  "|";
		      cout << Box7[xxx][yyy];
		     if(Box7[xxx][yyy] < 10) 
		      cout << " |";
		      else
		    cout << "|";
		   }
		  else{
		  
			 if(Box7[xxx][yyy] < 10  )
		 	{
		 	 // if(yyy==0)
			 // cout <<  "qqq"; 
			  
			  cout << Box7[xxx][yyy] << " |"; 
		    }
		 	else 
		 	{
			 cout  << Box7[xxx][yyy] << "|";
		    }
		 }
	   	
	}
	cout << "\n";
	for (int zzz = 0; zzz < 49; zzz++)
cout <<"_";	
cout << endl;
}
		
		
		
		    break;	  
		
		case 7:
			cout << "<<< S-Box 8 >>>" << endl;
	for(int cs = 42; cs < 48; cs++)
	{
		cout << xored[cs];
	}
	cout << endl;
		for (int zzz = 0; zzz < 49; zzz++)
    cout <<"_";
	cout << "\n";		
	
		for(int xxx = 0; xxx < 4; xxx++)
		 {
		 for(int yyy = 0; yyy < 16; yyy++)
		 {
		 	if(yyy==0)
			  {
			  cout <<  "|";
		      cout << Box8[xxx][yyy];
		     if(Box8[xxx][yyy] < 10) 
		      cout << " |";
		      else
		    cout << "|";
		   }
		  else{
		  
			 if(Box8[xxx][yyy] < 10  )
		 	{
		 	 // if(yyy==0)
			 // cout <<  "qqq"; 
			  
			  cout << Box8[xxx][yyy] << " |"; 
		    }
		 	else 
		 	{
			 cout  << Box8[xxx][yyy] << "|";
		    }
		 }
//	cout << "\n";
//	for (int zzz = 0; zzz < 49; zzz++)
//cout <<"_";	
	   	
	}

cout << "\n";
for (int zzz = 0; zzz < 49; zzz++)
cout <<"_";
cout << endl;

}
			  
			  break;
			  
			  
	}
			  
			string row1= xored.substr(i*6,1) + xored.substr(i*6 + 5,1);
      		//cout << "row1 " << row1 << endl;
			int row = convertBinaryToDecimal(row1);
      		string col1 = xored.substr(i*6 + 1,1) + xored.substr(i*6 + 2,1) + xored.substr(i*6 + 3,1) + xored.substr(i*6 + 4,1);;
      		
      		//cout << "col1 " << col1 << endl;
			int col = convertBinaryToDecimal(col1);
			
		
		//for(int rw = 0; rw < 9; rw++)
			//cout << "-";
			//cout << endl;
		//	system("cls");
			
			int val = substition_boxes[i][row][col];
			
		
			
				string xrow,ycol;
				int zval;
			  //cin >> x;
			  //cin >> y;
			//  cin >> z;
	//		cout << "-";
	//	    cout << "row1 " << row1 << endl;
	//		cout << "col1 "	<< col1 << endl;
			
			bool answ = true;
	//		cout << "val " << val << endl;
			
			if(kii==0 && checko == false)
			while(answ)
			{
			
			cout << "Schreiben Sie die Binaerzahl, die die Zeile der S-Box ermittelt" << endl;
			cin >> xrow;
			cout << "Schreiben Sie die Binaerzahl, die die Spalte der S-Box ermittelt" << endl;
			cin >> ycol;
			
			cout << "Schreiben Sie die ermittelte Zahl in der S-Box in dezimaler Schreibweise" << endl;
			cin >> zval;
			
			if(xrow == row1 && ycol == col1 && val == zval )
			 answ = false;
		   }  
			
			system("cls");			
			
			res += convertDecimalToBinary(val);  
		    
		 //   cout << "valbits " << res << endl;
		   
	}
	   // if(checko==true)
        // {
		//  cout << " Bits nach den S-Boxen: " << res << endl;
		  
	     //}
	
		     if(checko==true && abda <= (kii+1) && breako==false)
			 {
			 	cout << "Bits werden  mittels S-Boxen substitutiert und wieder auf 32 Bits reduziert..." << endl;
			 	cout << res << endl;
			 	system("Pause");
			 	//system("cls");
			 }
		
		
		
		     if( kii == 0 && checko == false)
		     {
		     	cout << "Bits wurden  mittels S-Boxen substitutiert" << endl;
		     	cout << res << endl;
		     	system("pause");
			 }
		
		
		// 3.5. Another permutation is applied
		string perm2 =""; 
		for(int i = 0; i < 32; i++){ 
			perm2 += res[permutation_tab[i]-1]; 
		}
		xored = Xor(perm2, left);
		
		if(checko==true && abda <= (kii+1) && breako==false)
			 {  //cout << "Runde: "	<< kii+1 << endl;
			 	cout << "Jetzt wird noch mal permutiert ..." << endl;
			 	cout << "...." << endl;
			 	cout << perm2 << endl;
			 	system("Pause");
			 	system("cls");
		cout << "Runde:               "	<< kii+1 << endl;
		cout << "Linker Block:        " << left << endl;
		cout << "Permutation 32 Bits  " << perm2 << endl;
		cout << "                     " << "XOR" << endl;
		cout << "                     " << "------------------------------------------------" << endl;
		cout << "Neuer rechter Block: " << xored << endl;
		cout << endl;
		cout << endl;	 
			 }
		
		
		if(kii==0 && checko == false)
		{
		cout << "Jetzt wird noch mal permutiert" << endl;
		cout << "...." << endl;
		cout << perm2 << endl;
		system("Pause");
		system("cls");
		cout << "Linker Block:                  " << left << endl;
		cout << "Permutation aus der f Funktion " << perm2 << endl;
		cout << "                            " << "XOR" << endl;
		cout << "                            " << "------------------------------------------------" << endl;
		cout << "Neuer rechter Block:        " << xored << endl;
		system("pause");
		system("cls");
	    }
		// 3.6. The result is xored with the left half
		xored = Xor(perm2, left);
		if((kii==0 && abda == 0 )|| (checko == true && (abda <= kii+1) && breako == false))
		{
		cout << "Runde:                      "	<< kii+1 << endl;	
		cout << "Alter linker Block:         "	<< left << endl;
		cout << "Alter rechter Block:        "   << right << endl;
		cout << "Neuer rechter Block:        "   << xored << endl;
		cout << "Neuer linker Block:         "  << right << endl;
		system("Pause");
		cout << endl;
		cout << endl;
		cout << endl;
		cout << "Willst du den Ciphertext sehen ?" << endl;
		string breaki;
		if(checko==true)
		{
		cout << "Bitte schreibe dann            'b'"  << endl;
		cout << "Wenn du naechste Runde sehen willst, druecke irgendeinen Zeichen auser 'b' " << endl;
	//	string breaki;
		cin >> breaki;
	    }
		if(breaki == "b")
		  breako = true;
		
		system("cls");
	/*	cout << "Permutation der 32 Bits:  " << perm2 << endl;
		//cout << "                           " << "XOR" << endl;
		cout << "Linker Block:             " << left << endl;
		cout << "                          " << "XOR" << endl;
		cout << "                          " << "------------------------------------------------" << endl;
		cout << "Neuer rechter Block:      " << xored << endl;
		cout << "Neuer linker Block:       " << right << endl;
		system("PAUSE");
        system("cls");	*/
	    }
		// 3.7. The left and the right parts of the plain text are swapped 
		left = xored; 
		if(i < 15){ 
			string temp = right;
			right = xored;
			left = temp;
		} 
	//}
}
	// 4. The halves of the plain text are applied
	string combined_text = left + right;   
	string ciphertext =""; 
	// The inverse of the initial permuttaion is applied
	for(int i = 0; i < 64; i++){ 
		ciphertext+= combined_text[inverse_permutation[i]-1]; 
	}
	//And we finally get the cipher text
	return ciphertext; 
}
int main(){ 
	// A 64 bit key
	string key= "1010101010111011000010010001100000100111001101101100110011011101";
	// A block of plain text of 64 bits
//	pt= "010000010100001001000011010001000100010101000110010001110100100"   1111000110001110001110100101010100010101100110000110000101010110;
	// Calling the function to generate 16 keys
  	pt = "0100000101110011011011000110000101101110011000100110010101111001";
	  //1111000110001110001110100101010100010101100110000110000101010110
	  
	  bool checki = true;
	  cout << "1. Quiz" << endl;
	  cout << "2. Presentation" << endl;
	  int agg;
	  cin >> agg;
	  while(checki)
	  {
	  
	  if(agg == 2)
	   {
		 checko = true;
	     cout << "Ab welcher Runde moechten Sie es gezeigt haben ?" << endl;
		 cin >> abda;
		 checki = true;
		 checki = false;
       }
       else if(agg ==1)
       {
       	checki = false;
	   }
	   else
	   {
	   	cout << "Bitte geben Sie 1 oder 2 ein" << endl;
	   	system("cls");
	    cout << "1. Quiz" << endl;
	    cout << "2. Presentation" << endl;
	    cin >> agg;
	   }
}
	generate_keys(key); 
    cout<<"Plain text: "<<pt<<endl; 
    string ct= DES(); 
    cout<<"Ciphertext: "<<ct<<endl;
} 
	
	
	
		
	



