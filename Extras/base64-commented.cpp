#include <bits/stdc++.h>
using namespace std;
	
int main(){
	vector <bool> sinbyte; // for converting ascii integers into a binary byte
	vector <bool> bitstring; // for concatenating all bytes into a single array of bits
	vector <bool> sixbits; // for dividing the 8bit array into 6 bits
	string plaintxt;
	cout << "Plaintext: ";
	// using getline so that spaces are supported
	getline(cin, plaintxt, '\n');
	int decimal[plaintxt.size()];
	// turning plaintext into ascii integers
	for(int i = 0; i < plaintxt.size(); i++){
		decimal[i]=int(plaintxt[i]);
	}
	int decimalsize = sizeof(decimal) / sizeof(decimal[0]); // putting the size of the array into a variable
	// turn ascii ints into binary and concatenate each byte into a single array array of bits
	for(int i = 0; i < decimalsize; i++){
		int n = decimal[i];
		//converting to binary
		while(n != 0){
			if(n%2==0){ // if the number is evenly divided by 2, convert to 0 in binary
				sinbyte.insert(sinbyte.begin(), false);
			}
			else if(n%2==1){ // if the number when divided by 2 has a remainder of 1, convert to 1 in binary
				sinbyte.insert(sinbyte.begin(), true);
			}
			n/=2; // divide the number by 2 untill it reaches 0
		}
		// pad with zeros to get to 8 bits
		for(int addzero = 8 - sinbyte.size(); addzero > 0; addzero--){
			sinbyte.insert(sinbyte.begin(), false);
		}
		int bitcounter = i * 8; // concatenating to the correct bitstring location
		bitstring.insert(bitstring.begin() + bitcounter, sinbyte.begin(), sinbyte.end()); // adding the single byte to the bitstring
		sinbyte.clear(); // clearing the single byte vector for repeated use
	}
	//pad with zeros to make the number of binary digits divisible by 3
	if((bitstring.size() / 8) % 3 == 1){
		bitstring.push_back(false);
		bitstring.push_back(false);
		bitstring.push_back(false);
		bitstring.push_back(false); // did it like this instead of using a for for the sake of code brevity
	}
	else if((bitstring.size() / 8) % 3 == 2){
		bitstring.push_back(false);
		bitstring.push_back(false); // same here
	}
	int sixbitsize = (bitstring.size()/6); // initializing the size of the six bit array
	int x = 0; // x and y are used for correct placement of the six bits into 
	int y = 6; // the sixbits vector array, from which they are converted to decimal
	int numarray[sixbitsize]; // converted numbers are stored here
	// segregate into 6 bits and convert from binary to decimal
	for(int i1 = 0; i1 < sixbitsize; i1++){
		// segregate the 8 bit string into 6 bits 
		sixbits.insert(sixbits.begin(), bitstring.begin()+x, bitstring.begin()+y);
		x+=6; y+=6; // increment x and y for the next position where 6 bits are taken from bitstring
		//convert from binary to decimal
		int num=0;
		int i3=0;
		for(int i2 = 5; i2 >= 0; i2--){
			if(sixbits[i2]){ // if sixbits is true add 2 to the power of the incrementor variable
				num+=pow(2, i3);
			}
			i3++;
		}
		numarray[i1]=num; // numarray is given the converted value
		sixbits.clear(); // clear sixbits for repeated use
	}
	// use substitution to make conversion to char easier and more direct
	for(int i = 0; i < sixbitsize; i++){
		if(numarray[i] <= 25) numarray[i]+=65; // capital letters go from 65 to 90
		else if(numarray[i] >= 26 && numarray[i] <= 51) numarray[i]+=71; // lowercase letters go from 97 to 122
		else if(numarray[i] >= 52 && numarray[i] <= 61 ) numarray[i]-=4; // numbers go from 48 to 57
		else if(numarray[i] == 62) numarray[i]=43; // special case for +
		else if(numarray[i] == 63) numarray[i]=47; // special case for /
	}
	// convert integers to characters
	char base64[sixbitsize]; // character array for the final Base64 encoding
	for(int i = 0; i < sixbitsize; i++){
		base64[i]=char(numarray[i]); // char function translates integers to characters through the ascii standard
	}
	for(int i = 0; i < (sixbitsize); i++){
		cout << base64[i]; // output the final result
	}
	//pad with = to make final string divisible by 4 (necessary if several base64 strings are concatenated)
    if(4-(sixbitsize%4) == 2){
        cout << "==";
    }
    else if(4-(sixbitsize%4) == 1){
        cout << "=";
    }
	cout << endl;
}
