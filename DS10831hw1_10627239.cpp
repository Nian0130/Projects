// 10627239蔡曜年 資訊三乙
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <sstream> 
#include <fstream> 
#include <cmath> 
#include <math.h> 

using namespace std ;

typedef struct cT {
	string line ;
    string school;
    string department;  
} collegeType ;


class Manipulator {
	
void Read(vector<string> &allinput, int &numOfInput, string &filename) { // 讀input檔
    fstream read ; // 用於讀檔
    string InputaLine ; // 用來讀一整行的資料
    string title ; // 用於讀掉txt檔案的前三句

    cout << "Please enter the filename which you want to open , Ex: input101.txt,input102.txt,input103.txt : " ;
    cin >> filename ; // 讀入txt檔的名子
    if ( filename.length() == 8 ) filename = filename + ".txt" ; // 若檔名是input101,要自動加上.txt
    if ( filename.length() == 3 ) filename = "input" + filename + ".txt" ; // 若檔名是101,要自動加上input,.txt

    read.open( filename.c_str(), ios::in ) ; // 開啟txt檔案 (讀)

    while ( !read ) {  // 檢查是否能開啟(防呆)
        cout << "!!! The file does not exist !!! "<< endl ;
        cout << "Please enter the filename which you want to open , Ex: input101.txt,input102.txt,input103.txt : " ;
        cin >> filename ; // 讀入txt檔的名子
        if ( filename.length() == 8 ) filename = filename + ".txt" ;// 若檔名是input101,要自動加上.txt
        if ( filename.length() == 3 ) filename = "input" + filename + ".txt" ; // 若檔名是101,要自動加上input,.txt
        read.open( filename.c_str(), ios::in ) ; // 開啟檔案(讀檔)
    } // while()

    getline( read, title ) ; // 先把第一行(標題)讀掉
    getline( read, title ) ; // 先把第二行(年度)讀掉
    getline( read, title ) ; // 先把第三行(欄位)讀掉
    while( getline( read, InputaLine ) ) { 
      allinput.push_back(InputaLine) ;
      numOfInput++;
	} // while
    read.close(); // 關閉檔案
} // Read

void Save(vector<string> allinput, int numOfInput, string filename) {
	fstream save ;
	string num ; //filename的數字部分 
	for ( int i = 5 ; i < 8 ; i++ )  
	  num = num + filename[i] ;
	string output = "copy" + num + ".txt";
	save.open( output.c_str(), ios::out ) ; 
	for( int i = 0 ; i < allinput.size() ; i++ ) 
	  save << allinput[i] << endl ;	  
	save.close() ;  
	cout << "Number of records = "<< numOfInput << endl ;
} // Save
 
 
void ReadCopy(vector<string> &allcopy, int &numOfCopy, string &copyname) {
    fstream read ; // 用於讀檔
    string InputaLine ; // 用來讀一整行的資料
    int sMin = 0 ;
    int gMin = 0 ;
    
    cout << "Please enter the filename which you want to open , Ex: copy101.txt,copy102.txt,copy103.txt : " ;
    cin >> copyname ; // 讀入txt檔的名子
    if ( copyname.length() == 7 ) copyname = copyname + ".txt" ; // 若檔名是copy101,要自動加上.txt
    if ( copyname.length() == 3 ) copyname = "copy" + copyname + ".txt" ; // 若檔名是101,要自動加上input,.txt

    read.open( copyname.c_str(), ios::in ) ; // 開啟txt檔案 (讀)

    while ( !read ) {  // 檢查是否能開啟(防呆)
        cout << "!!! The file does not exist !!! "<< endl ;
        cout << "Please enter the filename which you want to open , Ex: copy101.txt,copy102.txt,copy103.txt : " ;
        cin >> copyname ; // 讀入txt檔的名子
        if ( copyname.length() == 7 ) copyname = copyname + ".txt" ;// 若檔名是copy101,要自動加上.txt
        if ( copyname.length() == 3 ) copyname = "copy" + copyname + ".txt" ; // 若檔名是101,要自動加上input,.txt
        read.open( copyname.c_str(), ios::in ) ; // 開啟檔案(讀檔)
    } // while()
     
    cout << "Input a lower bound on the number of student:" ;
    cin >> sMin ;
    cout << "Input a lower bound on the number of graduates:" ;
    cin >> gMin ;
    // 輸入
	 
    while( getline( read, InputaLine ) ) { 
        int student = 7 ; // 第7項是學生數的字串
        int graduate = 9 ; // 第9項是畢業生數的字串 
        int studentNum = 0 ;
        int graduateNum = 0 ;
        string str ; // 切割出來的
        int start = 0 ; // 紀錄一整個大字串開始的位置
        int ends = 0 ;
        
        for(int i = 0 ; i < student - 1 ; ++i ) {
            start = InputaLine.find( '\t', start ) ; // 從start開始尋找下一個'\t'
            ++start ; // 從當前查找的'\t'位置下一字串，開始查找('\t'之後=字串開始的位置)
        } // for 
		    
        ends = InputaLine.find( '\t', start );	// 查找第幾個小字串的結束位置(找到下一個tab之前)

        if(ends != string::npos )	{	// 找到'\t'
            str = InputaLine.substr( start, ends - start ) ;
        } // if
        
        else {
            str = InputaLine.substr( start, InputaLine.size() - start ) ; // 切割字串
        } // else
        if ( str[0] == '"' ) { // "3,559"的情況
            int i = 1 ;
            string newStr ;

            while ( str[i] != '"') {
                if ( str[i] != ',' )
                    newStr = newStr + str[i] ;
                i ++ ;
            }

            stringstream change ; // 字串轉數字
            change << newStr ; // 將num字串轉成數字
            change >> studentNum ;

        }
        else { // 正常情況
            stringstream change ; // 字串轉數字
            change << str ; // 將num字串轉成數字
            change >> studentNum ;
        }    
// 找學生數 
		start = 0 ;
        for(int i = 0 ; i < graduate - 1 ; ++i ) {
            start = InputaLine.find( '\t', start ) ; // 從start開始尋找下一個'\t'
            ++start ; // 從當前查找的'\t'位置下一字串，開始查找('\t'之後=字串開始的位置)
        } // for   
		    
        ends = InputaLine.find( '\t', start );	// 查找第幾個小字串的結束位置(找到下一個tab之前)
        if(ends != string::npos )	{	// 找到'\t'
            str = InputaLine.substr( start, ends - start ) ;
        } // if
        else {
            str = InputaLine.substr( start, InputaLine.size() - start ) ; // 切割字串
        } // else
        if ( str[0] == '"' ) { // "3,559"的情況
            int i = 1 ;
            string newStr ;

            while ( str[i] != '"') {
                if ( str[i] != ',' )
                    newStr = newStr + str[i] ;
                i ++ ;
            }

            stringstream change ; // 字串轉數字
            change << newStr ; // 將num字串轉成數字
            change >> graduateNum ;

        }
        else { // 正常情況
            stringstream change ; // 字串轉數字
            change << str ; // 將num字串轉成數字
            change >> graduateNum ;
        }
// 找畢業生數
		
		if ( studentNum >= sMin && graduateNum >= gMin ) {
		  allcopy.push_back(InputaLine)	;
		  numOfCopy++ ;
	    } // if
						   		  	  
	} // while	
    read.close(); // 關閉檔案
} // ReadCopy
 
void Remove(vector<string> &allcopy, int &numOfCopy, string &copyname) {
	fstream remove ;
	remove.open( copyname.c_str(), ios::out ) ; 
	for( int i = 0 ; i < allcopy.size() ; i++ ) 
	  remove << allcopy[i] << endl ;	  
	remove.close() ;  
	cout << "Number of records = "<< numOfCopy << endl ;	
} // Remove

void Find(string &InputaLine,vector<cT> &file ,struct cT &temp ){
    	int school = 2 ; 
    	int department = 4 ; 
        string str ; // 切割出來的
        int start = 0 ; // 紀錄一整個大字串開始的位置
        int ends = 0 ;
        
        for(int i = 0 ; i < school - 1 ; ++i ) {
            start = InputaLine.find( '\t', start ) ; // 從start開始尋找下一個'\t'
            ++start ; // 從當前查找的'\t'位置下一字串，開始查找('\t'之後=字串開始的位置)
        } // for 
		    
        ends = InputaLine.find( '\t', start );	// 查找第幾個小字串的結束位置(找到下一個tab之前)

        if(ends != string::npos )	{	// 找到'\t'
            str = InputaLine.substr( start, ends - start ) ;
        } // if
        
        else {
            str = InputaLine.substr( start, InputaLine.size() - start ) ; // 切割字串
        } // else

        temp.school = str ;

//找學校
		start = 0 ;
        for(int i = 0 ; i < department - 1 ; ++i ) {
            start = InputaLine.find( '\t', start ) ; // 從start開始尋找下一個'\t'
            ++start ; // 從當前查找的'\t'位置下一字串，開始查找('\t'之後=字串開始的位置)
        } // for   
		    
        ends = InputaLine.find( '\t', start );	// 查找第幾個小字串的結束位置(找到下一個tab之前)
        if(ends != string::npos )	{	// 找到'\t'
            str = InputaLine.substr( start, ends - start ) ;
        } // if
        else {
            str = InputaLine.substr( start, InputaLine.size() - start ) ; // 切割字串
        } // else
        temp.department = str ;
        
// 找科系
      temp.line = InputaLine ;
      file.push_back(temp) ;				   	
} // Find

void Merge(vector<cT> &all, int &numOfMerge, string &name1, string & name2){
	fstream read ; // 用於讀檔
    string InputaLine ; // 用來讀一整行的資料
    vector<cT> file1 ;
    vector<cT> file2 ;
    struct cT temp ;
      
    cout << "Please enter the filename which you want to open , Ex: copy101.txt,copy102.txt,copy103.txt : " ;
    cin >> name1 ; // 讀入txt檔的名子
    if ( name1.length() == 7 ) name1 = name1 + ".txt" ; // 若檔名是copy101,要自動加上.txt
    if ( name1.length() == 3 ) name1 = "copy" + name1 + ".txt" ; // 若檔名是101,要自動加上copy.txt

    read.open( name1.c_str(), ios::in ) ; // 開啟txt檔案 (讀)

    while ( !read ) {  // 檢查是否能開啟(防呆)
        cout << "!!! The file does not exist !!! "<< endl ;
        cout << "Please enter the filename which you want to open , Ex: copy101.txt,copy102.txt,copy103.txt : " ;
        cin >> name1 ; // 讀入txt檔的名子
        if ( name1.length() == 7 ) name1 = name1 + ".txt" ;// 若檔名是copy101,要自動加上.txt
        if ( name1.length() == 3 ) name1 = "copy" + name1 + ".txt" ; // 若檔名是101,要自動加上copy.txt
        read.open( name1.c_str(), ios::in ) ; // 開啟檔案(讀檔)
    } // while()
    while( getline( read, InputaLine ) )  {
      Find(InputaLine,file1,temp) ; //找代碼 
	  numOfMerge++ ;    
    } // while
    read.close(); // 關閉檔案
// 讀第一個檔    
    cout << "Please enter the filename which you want to open , Ex: copy101.txt,copy102.txt,copy103.txt : " ;
    cin >> name2 ; // 讀入txt檔的名子
    if ( name2.length() == 7 ) name2 = name2 + ".txt" ; // 若檔名是copy101,要自動加上.txt
    if ( name2.length() == 3 ) name2 = "copy" + name2 + ".txt" ; // 若檔名是101,要自動加上copy.txt

    read.open( name2.c_str(), ios::in ) ; // 開啟txt檔案 (讀)

    while ( !read ) {  // 檢查是否能開啟(防呆)
        cout << "!!! The file does not exist !!! "<< endl ;
        cout << "Please enter the filename which you want to open , Ex: copy101.txt,copy102.txt,copy103.txt : " ;
        cin >> name1 ; // 讀入txt檔的名子
        if ( name2.length() == 7 ) name2 = name2 + ".txt" ;// 若檔名是copy101,要自動加上.txt
        if ( name2.length() == 3 ) name2 = "copy" + name2 + ".txt" ; // 若檔名是101,要自動加上copy.txt
        read.open( name2.c_str(), ios::in ) ; // 開啟檔案(讀檔)
    } // while()
    while( getline( read, InputaLine ) ) {
      Find(InputaLine,file2,temp) ; // 找代碼 
	  numOfMerge++ ; 
    } // while
    read.close(); // 關閉檔案     
// 讀第二個檔 
     
// 開始合併放進all  
  for( int f1 = 0 ; f1 < file1.size() ; f1++ ){ 
    all.push_back(file1[f1]) ; //先放第一個檔的資料 
    
    for( int f2 = 0 ; f2 < file2.size() ; f2++ ){ 
      while( file1[f1].school == file2[f2].school && file1[f1].department == file2[f2].department )	 {//先看是否學校科系都相同 
        all.push_back(file2[f2]) ;
        file2.erase(file2.begin()+f2) ;	    
	  } // while
	} // for
	
    for( int f2 = 0 ; f2 < file2.size() ; f2++ ){
      while( file1[f1].school == file2[f2].school )	{ //再看學校是否相同 
        all.push_back(file2[f2]) ;
        file2.erase(file2.begin()+f2) ;	    
	  } // while
	} // for
  } // for	    
	
	
  for(int i = 0 ; i < file2.size() ; i++ ) { //放第二個檔案剩下的資料 
	all.push_back(file2[i]) ;
  } // for
  
} // Merge

void Print(vector<cT> &all, int &numOfMerge, string &name1, string & name2){
	fstream print ;
	string num1 ;
	string num2 ;
	for ( int i = 4 ; i < 7 ; i++ )  
	  num1 = num1 + name1[i] ;
	for ( int i = 4 ; i < 7 ; i++ )  
	  num2 = num2 + name2[i] ;	 
	   
	string output = "output" + num1 + "_" + num2 + ".txt";
	print.open( output.c_str(), ios::out ) ; 
	 
	for( int i = 0 ; i < all.size() ; i++ ) 
	  print << all[i].line << endl ;
		  
	print.close() ;  
	cout << "Number of records = "<< numOfMerge << endl ;	
} // Print

    public :
        void MissionOne() {
			int numOfInput = 0 ; 
			vector <string> allinput ;
			string filename ;
			Read(allinput,numOfInput,filename) ;
			Save(allinput,numOfInput,filename) ;			
        }
        void MissionTwo() {
        	int numOfCopy = 0 ;
        	vector <string> allcopy ;
        	string copyname ;
        	ReadCopy(allcopy,numOfCopy,copyname) ;
            Remove(allcopy,numOfCopy,copyname) ;
        }		    	
        void MissionThree() {
        	int numOfMerge = 0 ;
        	vector <cT> all ;
        	string name1 ;
        	string name2 ;
        	Merge(all,numOfMerge,name1,name2) ;
        	Print(all,numOfMerge,name1,name2) ;
        }
};
   
int main() {
    int command = 0 ; // 任務號碼
    Manipulator Manipulator ;
    cout << endl << "**** File Object Manipulator ****" ;
    cout << endl << "* 0. QUIT                          *" ; 
    cout << endl << "* 1. COPY (Read & Save a file)     *" ; 
    cout << endl << "* 2. FILTER (Reduce a file)        *" ; 
    cout << endl << "* 3. MERGE (Join two files)        *" ;    
    cout << endl << "**************************************" ;
    cout << endl << "Input a choice(0, 1, 2, 3): " ;

    cin >> command ; // 輸入任務號碼

    while( command != 0 ) {  // 只要輸入的數字不是0就可以繼續其他任務
        while ( command < 0 || command > 3 ) {  // 確保輸入的任務代號是0.1.2.3(否則重新輸入)
            cout << endl << "Command does not exist!" << endl ;

    	cout << endl << "**** File Object Manipulator ****" ;
    	cout << endl << "* 0. QUIT                          *" ; 
    	cout << endl << "* 1. COPY (Read & Save a file)     *" ; 
    	cout << endl << "* 2. FILTER (Reduce a file)        *" ; 
    	cout << endl << "* 3. MERGE (Join two files)        *" ;    
    	cout << endl << "**************************************" ;
    	cout << endl << "Input a choice(0, 1, 2, 3): " ;

            cin >> command ; // 輸入任務號碼
        } // while()

        if ( command == 0 ) return 0 ; // 結束
        if ( command == 1 ) Manipulator.MissionOne() ; // 執行任務1
        if ( command == 2 ) Manipulator.MissionTwo() ; // 執行任務2
        if ( command == 3 ) Manipulator.MissionThree() ; // 執行任務3       

    	cout << endl << "**** File Object Manipulator ****" ;
    	cout << endl << "* 0. QUIT                          *" ; 
    	cout << endl << "* 1. COPY (Read & Save a file)     *" ; 
   		cout << endl << "* 2. FILTER (Reduce a file)        *" ; 
    	cout << endl << "* 3. MERGE (Join two files)        *" ;    
    	cout << endl << "**************************************" ;
    	cout << endl << "Input a choice(0, 1, 2, 3): " ;

        cin >> command ; // 輸入任務號碼

    } // while()
} // main()
//*********************************************************************************


