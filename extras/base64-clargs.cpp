#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]){
	string plaintxt = "";
	for(int i = 1; i < argc; i++){
		plaintxt.append(argv[i]);
		if(i < argc-1) plaintxt.append(" ");
	}
	vector <bool> sinbyte;
	vector <bool> bitstring;
	vector <bool> sixbits;
	int decimal[plaintxt.size()];
	for(int i = 0; i < plaintxt.size(); i++){
		decimal[i]=int(plaintxt[i]);
	}
	int decimalsize = sizeof(decimal) / sizeof(decimal[0]);
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
		int bitcounter = i * 8;
		bitstring.insert(bitstring.begin() + bitcounter, sinbyte.begin(), sinbyte.end());
		sinbyte.clear();
	}
	if((bitstring.size() / 8) % 3 == 1){
		bitstring.push_back(false);
		bitstring.push_back(false);
		bitstring.push_back(false);
		bitstring.push_back(false);
	}
	else if((bitstring.size() / 8) % 3 == 2){
		bitstring.push_back(false);
		bitstring.push_back(false);
	}
	int sixbitsize = (bitstring.size()/6);
	int x = 0;
	int y = 6;
	int numarray[sixbitsize];
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
		numarray[i1]=num;
		sixbits.clear();
	}
	for(int i = 0; i < sixbitsize; i++){
		if(numarray[i] <= 25) numarray[i]+=65;
		else if(numarray[i] >= 26 && numarray[i] <= 51) numarray[i]+=71;
		else if(numarray[i] >= 52 && numarray[i] <= 61 ) numarray[i]-=4;
		else if(numarray[i] == 62) numarray[i]=43;
		else if(numarray[i] == 63) numarray[i]=47;
	}
	char base64[sixbitsize];
	for(int i = 0; i < sixbitsize; i++){
		base64[i]=char(numarray[i]);
	}
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