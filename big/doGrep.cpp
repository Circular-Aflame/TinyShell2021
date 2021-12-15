#include"Declarations.h"

int cnt=0;					//符合查找条件的行数 
string all_lines[200];		//记录全部行的内容 
string file_name;			//记录正在进行查找的文件的文件名
int start_num;				//从该项起为文件名
string word;
int length_word;
int st[100];
int endd[100];
int k;

struct info{
	string content;			//存储该行内容 
	int line_number;		//存储行号 
};
info output_line[200];						//记录符合要求的行的内容、行号

bool find_h=false;
bool find_H=false;
bool find_n=false;
bool find_i;
int A_num=0;									//记录A后面的数字 
int B_num=0;									//记录B后面的数字 

//函数strCMP：用于比较两个char数组是否完全相同 
bool strCMP ( char *x, char *y)
{	
	while(*x!='\0'||*y!='\0'){
		if( *x != *y)
			return false;
		x++;
		y++;
	}
	return *x==*y;
}



//函数string2strout：用于将string存入strout 
char *outt;
void string2strout(string str){
	outt=&str[0];
	strcat(gTerm.strout,outt);
}

//函数int2strout：用于将int存入strout 
void int2strout(int n){
	sprintf(gTerm.strout,"%s%d",gTerm.strout,n);
}

//函数this_line:将目标行的目标词标红 
void this_line(int i){
	int l=strlen(gTerm.strout);
	for(int m=0;m<st[i]-1;m++){
		gTerm.strout[l++]=output_line[i].content[m];
 	}
 	gTerm.strout[l]='\0';
 	strcat(gTerm.strout,"\e[91;1m");
 	l=strlen(gTerm.strout);
	for(int m=st[i]-1;m<endd[i];m++){
		gTerm.strout[l++]=output_line[i].content[m];
 	}
	gTerm.strout[l]='\0';
 	strcat(gTerm.strout,"\e[0m");
 	l=strlen(gTerm.strout);
 	for(int m=endd[i];m<output_line[i].content.size();m++){
  		gTerm.strout[l++]=output_line[i].content[m];
 	}
 	gTerm.strout[l]='\0';
 	return;
}

//函数output： 将内容存入strout，以供输出

void output(int argc, char * argv[]){	
	output_line[0].line_number=-1;
	output_line[cnt+1].line_number = output_line[cnt].line_number + B_num + A_num + 1;
	for(int i=1;i<=cnt;i++){
		for(int j=output_line[i].line_number-B_num;j<=output_line[i].line_number+A_num;j++){
			if(j>output_line[i-1].line_number && (j<output_line[i+1].line_number-B_num || j<=output_line[i].line_number) && j!=output_line[i].line_number && j>0 && j<k){		//非目标行 
				if(find_n){
					if(find_H){
						string2strout(file_name);
						strcat(gTerm.strout," ");
						strcat(gTerm.strout,"\e[92;1m");
						int2strout(j);
						strcat(gTerm.strout,"\e[94;1m-\e[0m");
						string2strout(all_lines[j]);
						strcat(gTerm.strout,"\n");
					}else{
						strcat(gTerm.strout,"\e[92;1m");
						int2strout(j);
						strcat(gTerm.strout,"\e[94;1m-\e[0m");
						string2strout(all_lines[j]);
						strcat(gTerm.strout,"\n");
					}	
				}else{
					string2strout(all_lines[j]);
					strcat(gTerm.strout,"\n");
				}
			}else if(j==output_line[i].line_number){	//目标行 
			
				if(find_n){
					if(find_H){		//-n -H 
						string2strout(file_name);
						strcat(gTerm.strout," ");
						strcat(gTerm.strout,"\e[92;1m");
						int2strout(j);
						strcat(gTerm.strout,"\e[94;1m:\e[0m");
						this_line(i);
						strcat(gTerm.strout,"\n");
						
					}else{			//-n 无-H 
						strcat(gTerm.strout,"\e[92;1m");
						int2strout(j);
						strcat(gTerm.strout,"\e[94;1m:\e[0m");
						this_line(i); 
						strcat(gTerm.strout,"\n");						
					}
				}else{
					if(find_H){		//-H 无-n
						string2strout(file_name);
						strcat(gTerm.strout," ");
						this_line(i);
						strcat(gTerm.strout,"\n");
						
					}else{			//无-n 无-H 
						this_line(i);
						strcat(gTerm.strout,"\n");
						
					}
				}
			}
		}
	}
	
	return;
}




bool compare(string s1, string s2, int p) {
    int countXing = 0;
    for(int i=0;i<=s2.length()-1;i++){
        if(s2[i]=='*'){
        	countXing=i+1;
		}
	}
	bool dp[50][20];

    //动态规划设置初值
	st[cnt+1]=-1;
    for(int i=p;i<=s1.length();i++){
       	if(s1[i-1]==s2[0] ||  (find_i && s1[i-1]-s2[0]==32 && s1[i-1]<=122) ||(find_i && s2[0]-s1[i-1]==32 && s2[0]<=122)){
        	dp[0][i-1]=1;
        	st[cnt+1]=i;
        	break;
		}
	}

	if(st[cnt+1]==-1)//找不到起始第一位 
		return false;
			
	if(s2.length() - countXing > s1.length()-st[cnt+1]+1 ){ //说明s2去掉通配符，长度也长于s1
		return false;
    }	
		
	//设置初值
    dp[0][st[cnt+1]-1] = true;
 	for(int m=st[cnt+1];m<=s1.length();m++){
		dp[0][m]=false; 
	}
	for(int m=1;m<=s2.length();m++){
		dp[m][st[cnt+1]-1]=false;
	}
	
	for(int i=1; i<=s2.length(); i++) {
        char s2_char = s2[i-1];			
        for(int j=st[cnt+1]; j<=s1.length(); j++) {
			char s1_char = s1[j-1];
            if(s2_char == '*'){
            	dp[i][j] = dp[i-1][j] || dp[i][j-1]; //动态规划递推式（星号） 表示星号可以匹配0个（决定于上次外循环的结果）或者多个（决定于刚才内循环的结果）
			}else{
				 dp[i][j] = dp[i-1][j-1] && (s2_char=='.' || s1_char == s2_char || (find_i && s1_char-s2_char==32 && s1_char<=122) ||(find_i && s2_char-s1_char==32 && s2_char<=122)); //动态规划递推式（非星号） 表示dp值取决于上次的状态和当前状态
			} 
        }
	}
 
    bool check=false;
    for(int i=1;i<=s1.length();i++){
        if(dp[s2.length()][i]){
        	endd[cnt+1]=i;
        	check=true;
		}
	}
	//cout<<end[cnt+1]<<endl;
	if(check){
		return true;
	}else{
		return compare(s1,s2,st[cnt+1]+1);
	}   
}


int length_line;

void doGrep(int argc , char * argv[]){
	cnt=0;
	find_h=false;
	find_H=false;
	find_n=false;
	find_i=false;
	A_num=0;
	B_num=0;

	

	
	if(strCMP(argv[1],(char*)"--help")){
		ifstream fin1("help.txt");
		string help;
		while( !fin1.eof() ){
			getline(fin1,help);
			string2strout(help);
			strcat(gTerm.strout,"\n");
		}
	
		fin1.close();
				
	}else{
		start_num=argc-1;
		for(int i=1;i<=argc-2;i++){

			if(argv[i][0]!='-'){ 
				start_num=i+1; 
				break;
			}
			
		}
		
		for(int i=1 ; i<start_num-1 ; i++){ 
			if(strCMP(argv[i],(char*)"-h")){
				find_h=true;
			}
			if(strCMP(argv[i],(char*)"-H")){
				find_H=true;
			}
			if(strCMP(argv[i],(char*)"-n")){ 
				find_n=true;
			}
			if(argv[i][1]=='A'&&argv[i][2]-'0'>A_num){ 
				A_num=argv[i][2]-'0';
			}
			if(argv[i][1]=='B'&&argv[i][2]-'0'>B_num){ 
				
				B_num=argv[i][2]-'0';
			}
		}
		
		if(find_H && find_h){
			cerr<<"grep: There is contradiction between -H & -h"<<endl;
			return;
		} 
		
		for(int i=1;i<=start_num-2;i++){

			if(argv[i][1]!='A' && argv[i][1]!='B' && !strCMP(argv[i],(char*)"-c") && !strCMP(argv[i],(char*)"-I") && !strCMP(argv[i],(char*)"-n") && !strCMP(argv[i],(char*)"-H") && !strCMP(argv[i],(char*)"-h") ){
				cerr<<"grep: command '";
				for(int j=0;j<strlen(argv[i]);j++){
					cerr<<argv[i][j];
				}
				cerr<<"' not found"<<endl;
				return;
			}
		}
		
		word=argv[start_num-1];
		length_word=word.size();
		
		ifstream fin;

		string line;
		
		bool find_c=false;
		for(int i=1 ; i<start_num ; i++){//-c:只输出符合条件的总行数
			if(strCMP(argv[i],(char*)"-c")){								 
				find_c=true;
			}
		}
		int count=0;
		
		find_i=false;									//判断是否有i 
		for(int i=1 ; i<start_num ; i++){ 
			if(strCMP(argv[i],(char*)"-I")){ 
				find_i=true;
				break;
			}
		}

		ofstream fout;
		for(int i=0;i<=argc-start_num-1;i++){		//处理第i个文件 
			char f[50];
			f[0]='\0';
			if(argv[start_num+i][0]=='-'){//从strin读取 
				fout.open("strin.txt");
				for(int j=0;j<strlen(gTerm.strin);j++){
					fout<<gTerm.strin[i];
				}
				strcat(f,"strin.txt");
				file_name="strin.txt";
			}else{ 
				//strcat(f,gTerm.root);
				//strcat(f,'/');
				//strcat(f,gTerm.wdir);
				//strcat(f,'/');
				strcat(f,argv[start_num+i]);
				file_name=argv[start_num+i];
			}
			
			fin.open(f);			//打开文件 
			if(!fin){
				cerr<<"grep: "<<file_name<<" : No such file or directory"<<endl;
				continue;
			}

			
			k=1;	//行号 （文件中的第k行） 
			cnt=0;	//记录符合要求的行的数量 
			while(!fin.eof()){
				
				
				getline(fin,line);							//读取一行
				all_lines[k]=line;							//将第k行内容记录至 all_lines[k]
				//cout<<"k"<<k<<"line"<<line<<endl;
				if(compare(line,word,1)){				//若 line中有目标词 
					//cout<<"find! "<<line<<endl;
					cnt++;									//计数 
					output_line[cnt].content=line;			//记录该行内容 
					output_line[cnt].line_number=k;			//记录该行行号		
				}
				k++;		//next line 
			}
			if(find_c){
				count+=cnt;
			}else{
				
				output(argc,argv);		//用output函数进行输出 
			}
		
			fin.close();			//关闭文件 
		}
		if(find_c){
			int2strout(count);
			strcat(gTerm.strout,"\n");
		} 
	}	
	return;	
}
