#include <cmath>
#include <iostream> // cout, endl
#include <fstream> // open, is_open, close, ignore
#include <string> // string, find_last_of, substr
#include <sstream>
#include <vector> // vector, push_back
#include <cstdlib> // system, atoi
#include <stdio.h>
#include <iomanip> // setw
#include <time.h>

using namespace std;

struct table{
	//1~4 [0]���� 
	vector<string> one ;
	vector<string> two ;
	vector<string> three ;
	vector<string> four ;
	vector<string> five ;
	vector<string> six ;
	vector<string> sev ;
};

struct tk{
	string name;
	int val=0;
	int tb=0;
};

class tablefc {
	public:
	vector<string> instr ;
	vector<tk> altk ;
	table alltb ;
	void build1to4(){ //set table 
	    string str, fname;
		//1	Table1.table 
		fname = "Table1.table";
		fstream _file1( fname.c_str()) ;
		while ( !_file1.eof() ) { //���O�̫�@�� 

   			getline(_file1, str, '\n');  
       		alltb.one.push_back(str);

  		} // while
  		
  		fname = "Table2.table";
		fstream _file2( fname.c_str()) ;
		while ( !_file2.eof() ) { //���O�̫�@�� 

   			getline(_file2, str, '\n');  
       		alltb.two.push_back(str);

  		} // while
  		
  		fname = "Table3.table";
		fstream _file3( fname.c_str()) ;
		while ( !_file3.eof() ) { //���O�̫�@�� 

   			getline(_file3, str, '\n');  
       		alltb.three.push_back(str);

  		} // while
  		
  		fname = "Table4.table";
		fstream _file4( fname.c_str()) ;
		while ( !_file4.eof() ) { //���O�̫�@�� 

   			getline(_file4, str, '\n');  
       		alltb.four.push_back(str);

  		} // while
  		
  		alltb.five.resize(100);
  		alltb.six.resize(100);
  		alltb.sev.resize(100);
	}
	
	//Ū���O 
	void read( string & fname){
		int i = 0 ;
		string str; 

		cout<<"input file name: ";
		cin>>fname;
		
		ifstream _file( fname.c_str()) ; // ��W��fname���ɮץ��} 
		if (_file.is_open()) { //�ɮצs�b 
		
	  		while ( !_file.eof() ) { //���O�̫�@�� 

        		getline(_file, str, '\n');  
        		instr.push_back(str);

      		} // while
  		} 
  		else{
  			cout<<"wrong file's name" ;
  			read(fname);
		}
  		
  		_file.close();
  		
	}
	

	
	//��token   
	void cut(){
		
		string token="\0",tmp="\0";
		int val=0;
		int type=0;
		tk temp;
		
		for(int i=0; i<instr.size(); i++){
			cout<<instr[i]<<endl;
			//��token 
			for(int j=0; j<instr[i].size(); j++){
				tmp=instr[i][j];
				token="\0";
				
				while(instr[i][j]!=' '&& instr[i][j]!='\t'&&instr[i][j]!='\n'&& issame(val, tmp)!=4 && j<instr[i].size() ){ //is not space/tab/enter
					token=token+instr[i][j];
					
		
					j++;
					tmp=instr[i][j];
				}
						
	
				if(issame(val, tmp)==4){
		
					if(tmp=="'" && (token=="C"||token=="X"||token=="c"||token=="x")){
						
						if(token=="C"||token=="c")
							type=1;
						else if(token=="X"||token=="x")
							type=2;
							
						token="\0";
					}
					else if(tmp=="'" && type==0) //'string' 
						type=1;
				}
				
				if(token!="\0"){
				
				if((issame(val, token)!=0 && type==0)){  
					temp.tb=issame(val, token);
					temp.val=val;
					temp.name=token;
					altk.push_back(temp);
					cout<<"("<<issame(val, token)<<","<<val<<") "; 
				} //in table
				else{ 					// hash, string(1)||lebal||int/real(2)
					// check int/real
					for(int k=0; k<token.size() && type==0; k++)
						if((int)token[k]>47 && (int)token[k]<58)
							type=2;
							
					int tbnum=0;
					for(int i =0; i<alltb.six.size() && type==2; i++){  //check int/real in table
		
		 				string bf = token;
						for (int j=0; j <token.size(); j++){  
							if((int)alltb.six[i][j]>=97 && (int)alltb.six[i][j]<=122) //a~z 
       							token[j] = tolower(token[j]);  //�j�g�ܤp�g  
       						else
       							token[j] = toupper(token[j]); //�p�g�ܤj�g 
						}
       			
						if(token == alltb.six[i]){
							val=i;
							tbnum=6;
						}
				
						token=bf;
					}
		
					for(int i =0; i<alltb.sev.size()&&type==1; i++){  //check string in table
						if(token == alltb.sev[i]){
							val=i;
							tbnum=7;
						}
					}

					if(tbnum==0){
						if(type==2) // is int/real
							hash( token, 6);	
						else if(type==1) // is string
							hash( token, 7);
						else
							hash( token, 5);
					}
					else{
						temp.tb=tbnum;
						temp.val=val;
						temp.name=token;
						altk.push_back(temp);						
						cout<<"("<<tbnum<<","<<val<<") ";
					} 	

					
				}
				 
				val=0;
				type=0;
				}
			
				if(issame(val, tmp)==4){  //is delimeter 
					temp.tb=4;
					temp.val=val;
					temp.name=tmp;
					altk.push_back(temp);
					cout<<"(4"<<","<<val<<") "; 				
				}
				
			}
			
			//���j 
			temp.tb=0;
			temp.val=0;
			temp.name="\0";
			altk.push_back(temp);
			cout<<endl;
		}
	}
	
	int sum(string str){  //��ascii�`�M 
		int num =0;
		for(int i =0; i<str.size(); i++)
			num = (int)str[i] + num;	
		return num;		
	}
	
	void hash( string str, int tb){

		int ip =sum(str)%100; //���m 
		
		if(tb==5){
		
				while(alltb.five[ip]!="\0"){  //�I�� 
					ip++;
					if(ip>=100)
						ip=ip%100;
				}

			alltb.five[ip] = str;

		}
		else if(tb==6){
			
				for(int i =0; i<str.size(); i++){
					if((int)str[i]>=97 && (int)str[i]<=122) //a~z
						ip=sum(str)-32;
						
				}
				
				ip=ip%100;
				while(alltb.six[ip]!="\0"){
					ip++;
					if(ip>=100)
						ip=ip%100;
				}

				
			alltb.six[ip] = str;
		}
		else {
				while(alltb.sev[ip]!="\0"){
					ip++;
					if(ip>=100)
						ip=ip%100;
				}
				
			alltb.sev[ip] = str;
		}
		
		tk tmp;
		tmp.tb=tb;
		tmp.val=ip;
		tmp.name=str;
		altk.push_back(tmp);
		cout<<"("<<tb<<","<<ip<<") "; 

	}
	
	int issame(int & val, string key){ //return tbnum & value
		int tbnum =0;
		bool out=false;

		for(int i =0; i<alltb.one.size() && !out; i++){ 
		 	
		 	string bf = key;
			for (int j=0; j <key.size(); j++){  
				if((int)alltb.one[i][j]>=97 && (int)alltb.one[i][j]<=122)  //a~z 
       				key[j] = tolower(key[j]);  //�j�g�ܤp�g  
       			else
       				key[j] = toupper(key[j]); //�p�g�ܤj�g 
			}
			 
			if(key == alltb.one[i]){
				
				out=true;
				val=i+1;
				tbnum=1;
			}
			
			key=bf;
			
		}

		
		for(int i =0; i<alltb.two.size() && !out; i++){
			string bf = key;
			for (int j=0; j <key.size(); j++){  
				if((int)alltb.two[i][j]>=97 && (int)alltb.two[i][j]<=122) //a~z 
       				key[j] = tolower(key[j]);  //�j�g�ܤp�g  
       			else
       				key[j] = toupper(key[j]); //�p�g�ܤj�g 
			}
       			
       		
			if(key == alltb.two[i]){
				out=true;
				val=i+1;
				tbnum=2;
			}
			
			key=bf;
		}	
		

		for(int i =0; i<alltb.three.size() && !out; i++){ 
		 	string bf = key;
			for (int j=0; j <key.size(); j++){  
				if((int)alltb.three[i][j]>=97 && (int)alltb.three[i][j]<=122) //a~z 
       				key[j] = tolower(key[j]);  //�j�g�ܤp�g  
       			else
       				key[j] = toupper(key[j]); //�p�g�ܤj�g 
			}
       			
			if(key == alltb.three[i]){
				out=true;
				val=i+1;
				tbnum=3;
			}
			
			key=bf;
		}
		
		for(int i =0; i<alltb.four.size() && !out; i++){ 
			if(key == alltb.four[i]){
				out=true;
				val=i+1;
				tbnum=4;
			}
		}
		
		for(int i =0; i<alltb.five.size() && !out; i++){ 
			if(key == alltb.five[i]){
				out=true;
				val=i;
				tbnum=5;
			}
		}
		
		for(int i =0; i<alltb.six.size() && !out; i++){ 
		
		 	string bf = key;
			for (int j=0; j <key.size(); j++){  
				if((int)alltb.six[i][j]>=97 && (int)alltb.six[i][j]<=122) //a~z 
       				key[j] = tolower(key[j]);  //�j�g�ܤp�g  
       			else
       				key[j] = toupper(key[j]); //�p�g�ܤj�g 
			}
       			
			if(key == alltb.six[i]){
				out=true;
				val=i;
				tbnum=6;
			}
			
			key=bf;
		}
		
		for(int i =0; i<alltb.sev.size() && !out; i++){ 
			if(key == alltb.sev[i]){
				out=true;
				val=i;
				tbnum=7;
			}
		}
		
		return tbnum;
	}
};


int main() {
	int val=0;
	bool exit=false;
	string fname, str;
	tablefc tb ;
	tb.build1to4();
	tb.read(fname);
	tb.cut();
	
	int j =0;
			str=fname+"_out.txt";
            ofstream out(str.c_str());  //��X�� 
            for(int i=0; i < tb.altk.size(); i++){
                out << tb.instr[i]<<endl;
                
                for(; tb.altk[j].name != "\0"; j++)
					out<<"("<<tb.altk[j].tb<<","<<tb.altk[j].val<<") ";
				out<<endl;	
				j++;
            } // for
			      
            out.close();
}
