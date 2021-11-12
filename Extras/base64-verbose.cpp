#include <bits/stdc++.h>
using namespace std;
	
int main(){
	vector <bool> sinbyte;
	vector <bool> bitstring;
	vector <bool> sixbits;
	string plaintxt;
	cout << "Plaintext: ";
	getline(cin, plaintxt, '\n');
	int decimal[plaintxt.size()];
	cout << "ASCII to integers: ";
	for(int i = 0; i < plaintxt.size(); i++){
		decimal[i]=int(plaintxt[i]);
		cout << int(plaintxt[i]) << " ";
	} cout <<endl;
	int decimalsize = sizeof(decimal) / sizeof(decimal[0]);
	cout << "Length of input: " << decimalsize <<endl;
	cout << "Binary: ";
	for(int i = 0; i < decimalsize; i++){
		int n = decimal[i];
		while(n != 0){
			if(n%2==0){
				sinbyte.insert(sinbyte.begin(), false);
			}
			else if(n%2==1){
				sinbyte.insert(sinbyte.begin(), true);
			}
			n/=2;
		}
		for(int addzero = 8 - sinbyte.size(); addzero > 0; addzero--){
			sinbyte.insert(sinbyte.begin(), false);
		}
		//--------------------------|
		for(bool binary: sinbyte){
			if(binary) cout << "1";
			else cout << "0";
		} cout <<" ";
		//------------|
		int bitcounter = i * 8;
		bitstring.insert(bitstring.begin() + bitcounter, sinbyte.begin(), sinbyte.end());
		sinbyte.clear();
	} cout <<endl;
	if((bitstring.size() / 8) % 3 == 1){
		bitstring.push_back(false);
		bitstring.push_back(false);
		bitstring.push_back(false);
		bitstring.push_back(false);
		cout << "Padded with 4 zeros." <<endl;
	}
	else if((bitstring.size() / 8) % 3 == 2){
		bitstring.push_back(false);
		bitstring.push_back(false);
		cout << "Padded with 2 zeros." <<endl;
	}
	int sixbitsize = (bitstring.size()/6);
	int x = 0;
	int y = 6;
	int numarray[sixbitsize];
	cout <<endl;
	cout << "Segregating into 6 bits and converting to integers" <<endl;
	cout << "--------------------------------------------------" <<endl;
	for(int i1 = 0; i1 < sixbitsize; i1++){
		sixbits.insert(sixbits.begin(), bitstring.begin()+x, bitstring.begin()+y);
		x+=6; y+=6;
		int num=0;
		int i3=0;
		for(int i2 = 5; i2 >= 0; i2--){
			if(sixbits[i2]){
				num+=pow(2, i3);
			}
			i3++;
		}
		//-------------------------|
		for(bool binary: sixbits){
			if(binary) cout << "1";
			else cout << "0";
		}
		cout << " = " << num <<endl;
		//--------------------------|
		numarray[i1]=num;
		sixbits.clear();
	}
	cout << "------------" <<endl;
	cout <<endl;
	cout << "Converting integers to ASCII compatible integers" <<endl;
	for(int i = 0; i < sixbitsize; i++){
		if(numarray[i] <= 25) numarray[i]+=65;
		else if(numarray[i] >= 26 && numarray[i] <= 51) numarray[i]+=71;
		else if(numarray[i] >= 52 && numarray[i] <= 61 ) numarray[i]-=4;
		else if(numarray[i] == 62) numarray[i]=43;
		else if(numarray[i] == 63) numarray[i]=47;
	}
	char base64[sixbitsize];
	cout <<endl;
	cout << "Converting integers to ASCII" <<endl;
	cout << "----------------------------" <<endl;
	for(int i = 0; i < sixbitsize; i++){
		base64[i]=char(numarray[i]);
		cout << numarray[i] << " = " << base64[i] <<endl;
	}
	cout << "-------" <<endl;
	if(4-(sixbitsize%4) == 2){
        cout << "Padding with 2 equal signs." <<endl;
    }
    else if(4-(sixbitsize%4) == 1){
        cout << "Padding with 1 equal sign." <<endl;
    }
	cout <<endl;
	cout << "Base64: ";
	for(int i = 0; i < (sixbitsize); i++){
		cout << base64[i];
	}
    if(4-(sixbitsize%4) == 2){
        cout << "==";
    }
    else if(4-(sixbitsize%4) == 1){
        cout << "=";
    }
	cout << endl;
}
