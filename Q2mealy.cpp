#include<iostream>
#include<string>
#include<fstream>
using namespace std;

#define fname "joy_mealy.txt"			//  fname is the constant variable used for my file name

/*
		INPUT FILE 
				
1/0 1/1				//     state / output
1/1 0/0

*/

/*
		INPUT FILE FORMAT DESCRIPTION:
		
										inputs
				----------------------------------------------------------------
						0										1
		
		q0:		new state = q1 (output = 0)			new state = q1 (output = 1)
							1  /  0								1	/	1
							
		q1: 	new state = q1 (output = 0)			new state = q0 (output = 0)
							1	/	0							0	/	0



//		open 	joy_mealy_machine.png  in the folder for better understanding.

// Viewer Descretion: if using windows do not view this in notepad, use Sublime, Atom or any proper text editor for best results (or better use linux :D ).

// If you are still not able to understand this, then you are hopeless, you should just copy paste. xD 

*/

void write_file(string inp, string str[], char* outname){
	ofstream fout(outname);
	
	fout << "Input for this Mealy Machine : " << inp <<'\n';
	
	fout << "Current input : \t Cur-State \t New State \t Output \n";
	for(int i=0;i<inp.size();i++) fout << str[i];
	
	fout.close();
}

char conv_char(int a){
	return a + '0';
}

string make_str(int a, int b, int c, int d){
	string tmp("\t ");
	// <<"\t " << c_in <<" \t \t   "<< c_st <<"\t  ----->\t"<< n_st <<"  \t  "<< c_out <<'\n'
	tmp.push_back(a+'0');
	tmp.append(" \t \t   ");
	tmp.push_back(b+'0');
	tmp.append("\t  ----->\t");
	tmp.push_back(c+'0');
	tmp.append("  \t  ");
	tmp.push_back(d+'0');
	tmp += "\n";
	
	return tmp;
}

int main(){
	int const n_input = 2;					// no. of inputs  (here 0 & 1)
	int st[5][5], out[5][5]; 		// state matrix & output matrix
	
	//	state matrix format ::  on state q0 if input=1  then new state = st[0][1];
	//	output matrix format::	on state q1 if input=0	then    output = out[1][0]; 
	
//	Reading file and creating state & output matrices

	ifstream fin(fname);		// opening file in read only mode.
	
	string line;
	
	int j=0;
	int i=0;
	
	while(!fin.eof()){
		fin >> line;			// line is of the format state / output
		cout<<"\nline = "<< line<<'\n';
		if(j<n_input){
			st[i][j] = line[0] -'0';	// line[0] contains state & line[] - '0' converts char to int. i.e  '1' becomes 1
			out[i][j] = line[2] - '0';
			
			//cout<<st[i][j] << " - "<< out[i][j] <<" (i,j) = "<< i<< ' '<<j <<'\n';
			j++;
		}
		if(j>=n_input)	i++,j=0;				// going to store next state
	}
	fin.close();
	
// Main program Starts here.

	string inp;
	int c_st = 0, n_st ,c_out = 0, c_in;			// Current State, New State , Current Output & Current Input variables
	
	cout << "Mealy Machine Program :- \n\n\n"
		 << "Enter input string : ";
	cin >> inp;
	cout<<'\n';
	
	string str[100];		// to store the output (to save in file later)

	cout << "Current input : \tCur-State \t  New State \t Output \n";
	for(int i=0;i<inp.size();i++){
		c_in = inp[i] - '0';
		n_st = st[c_st][c_in];
		c_out = out[c_st][c_in];
		
		cout <<"\t " << c_in <<" \t \t   "<< c_st <<"\t  ----->\t"<< n_st <<"  \t  "<< c_out <<'\n';
		str[i] = make_str(c_in,c_st,n_st,c_out);
		
		c_st = n_st;
	}
	write_file(inp,str,"mealy_output.txt");
	return 0;
}
