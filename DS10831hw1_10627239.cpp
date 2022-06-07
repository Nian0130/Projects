// 10627239���`�~ ��T�T�A
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
	
void Read(vector<string> &allinput, int &numOfInput, string &filename) { // Ūinput��
    fstream read ; // �Ω�Ū��
    string InputaLine ; // �Ψ�Ū�@��檺���
    string title ; // �Ω�Ū��txt�ɮת��e�T�y

    cout << "Please enter the filename which you want to open , Ex: input101.txt,input102.txt,input103.txt : " ;
    cin >> filename ; // Ū�Jtxt�ɪ��W�l
    if ( filename.length() == 8 ) filename = filename + ".txt" ; // �Y�ɦW�Oinput101,�n�۰ʥ[�W.txt
    if ( filename.length() == 3 ) filename = "input" + filename + ".txt" ; // �Y�ɦW�O101,�n�۰ʥ[�Winput,.txt

    read.open( filename.c_str(), ios::in ) ; // �}��txt�ɮ� (Ū)

    while ( !read ) {  // �ˬd�O�_��}��(���b)
        cout << "!!! The file does not exist !!! "<< endl ;
        cout << "Please enter the filename which you want to open , Ex: input101.txt,input102.txt,input103.txt : " ;
        cin >> filename ; // Ū�Jtxt�ɪ��W�l
        if ( filename.length() == 8 ) filename = filename + ".txt" ;// �Y�ɦW�Oinput101,�n�۰ʥ[�W.txt
        if ( filename.length() == 3 ) filename = "input" + filename + ".txt" ; // �Y�ɦW�O101,�n�۰ʥ[�Winput,.txt
        read.open( filename.c_str(), ios::in ) ; // �}���ɮ�(Ū��)
    } // while()

    getline( read, title ) ; // ����Ĥ@��(���D)Ū��
    getline( read, title ) ; // ����ĤG��(�~��)Ū��
    getline( read, title ) ; // ����ĤT��(���)Ū��
    while( getline( read, InputaLine ) ) { 
      allinput.push_back(InputaLine) ;
      numOfInput++;
	} // while
    read.close(); // �����ɮ�
} // Read

void Save(vector<string> allinput, int numOfInput, string filename) {
	fstream save ;
	string num ; //filename���Ʀr���� 
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
    fstream read ; // �Ω�Ū��
    string InputaLine ; // �Ψ�Ū�@��檺���
    int sMin = 0 ;
    int gMin = 0 ;
    
    cout << "Please enter the filename which you want to open , Ex: copy101.txt,copy102.txt,copy103.txt : " ;
    cin >> copyname ; // Ū�Jtxt�ɪ��W�l
    if ( copyname.length() == 7 ) copyname = copyname + ".txt" ; // �Y�ɦW�Ocopy101,�n�۰ʥ[�W.txt
    if ( copyname.length() == 3 ) copyname = "copy" + copyname + ".txt" ; // �Y�ɦW�O101,�n�۰ʥ[�Winput,.txt

    read.open( copyname.c_str(), ios::in ) ; // �}��txt�ɮ� (Ū)

    while ( !read ) {  // �ˬd�O�_��}��(���b)
        cout << "!!! The file does not exist !!! "<< endl ;
        cout << "Please enter the filename which you want to open , Ex: copy101.txt,copy102.txt,copy103.txt : " ;
        cin >> copyname ; // Ū�Jtxt�ɪ��W�l
        if ( copyname.length() == 7 ) copyname = copyname + ".txt" ;// �Y�ɦW�Ocopy101,�n�۰ʥ[�W.txt
        if ( copyname.length() == 3 ) copyname = "copy" + copyname + ".txt" ; // �Y�ɦW�O101,�n�۰ʥ[�Winput,.txt
        read.open( copyname.c_str(), ios::in ) ; // �}���ɮ�(Ū��)
    } // while()
     
    cout << "Input a lower bound on the number of student:" ;
    cin >> sMin ;
    cout << "Input a lower bound on the number of graduates:" ;
    cin >> gMin ;
    // ��J
	 
    while( getline( read, InputaLine ) ) { 
        int student = 7 ; // ��7���O�ǥͼƪ��r��
        int graduate = 9 ; // ��9���O���~�ͼƪ��r�� 
        int studentNum = 0 ;
        int graduateNum = 0 ;
        string str ; // ���ΥX�Ӫ�
        int start = 0 ; // �����@��Ӥj�r��}�l����m
        int ends = 0 ;
        
        for(int i = 0 ; i < student - 1 ; ++i ) {
            start = InputaLine.find( '\t', start ) ; // �qstart�}�l�M��U�@��'\t'
            ++start ; // �q��e�d�䪺'\t'��m�U�@�r��A�}�l�d��('\t'����=�r��}�l����m)
        } // for 
		    
        ends = InputaLine.find( '\t', start );	// �d��ĴX�Ӥp�r�ꪺ������m(���U�@��tab���e)

        if(ends != string::npos )	{	// ���'\t'
            str = InputaLine.substr( start, ends - start ) ;
        } // if
        
        else {
            str = InputaLine.substr( start, InputaLine.size() - start ) ; // ���Φr��
        } // else
        if ( str[0] == '"' ) { // "3,559"�����p
            int i = 1 ;
            string newStr ;

            while ( str[i] != '"') {
                if ( str[i] != ',' )
                    newStr = newStr + str[i] ;
                i ++ ;
            }

            stringstream change ; // �r����Ʀr
            change << newStr ; // �Nnum�r���ন�Ʀr
            change >> studentNum ;

        }
        else { // ���`���p
            stringstream change ; // �r����Ʀr
            change << str ; // �Nnum�r���ন�Ʀr
            change >> studentNum ;
        }    
// ��ǥͼ� 
		start = 0 ;
        for(int i = 0 ; i < graduate - 1 ; ++i ) {
            start = InputaLine.find( '\t', start ) ; // �qstart�}�l�M��U�@��'\t'
            ++start ; // �q��e�d�䪺'\t'��m�U�@�r��A�}�l�d��('\t'����=�r��}�l����m)
        } // for   
		    
        ends = InputaLine.find( '\t', start );	// �d��ĴX�Ӥp�r�ꪺ������m(���U�@��tab���e)
        if(ends != string::npos )	{	// ���'\t'
            str = InputaLine.substr( start, ends - start ) ;
        } // if
        else {
            str = InputaLine.substr( start, InputaLine.size() - start ) ; // ���Φr��
        } // else
        if ( str[0] == '"' ) { // "3,559"�����p
            int i = 1 ;
            string newStr ;

            while ( str[i] != '"') {
                if ( str[i] != ',' )
                    newStr = newStr + str[i] ;
                i ++ ;
            }

            stringstream change ; // �r����Ʀr
            change << newStr ; // �Nnum�r���ন�Ʀr
            change >> graduateNum ;

        }
        else { // ���`���p
            stringstream change ; // �r����Ʀr
            change << str ; // �Nnum�r���ন�Ʀr
            change >> graduateNum ;
        }
// �䲦�~�ͼ�
		
		if ( studentNum >= sMin && graduateNum >= gMin ) {
		  allcopy.push_back(InputaLine)	;
		  numOfCopy++ ;
	    } // if
						   		  	  
	} // while	
    read.close(); // �����ɮ�
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
        string str ; // ���ΥX�Ӫ�
        int start = 0 ; // �����@��Ӥj�r��}�l����m
        int ends = 0 ;
        
        for(int i = 0 ; i < school - 1 ; ++i ) {
            start = InputaLine.find( '\t', start ) ; // �qstart�}�l�M��U�@��'\t'
            ++start ; // �q��e�d�䪺'\t'��m�U�@�r��A�}�l�d��('\t'����=�r��}�l����m)
        } // for 
		    
        ends = InputaLine.find( '\t', start );	// �d��ĴX�Ӥp�r�ꪺ������m(���U�@��tab���e)

        if(ends != string::npos )	{	// ���'\t'
            str = InputaLine.substr( start, ends - start ) ;
        } // if
        
        else {
            str = InputaLine.substr( start, InputaLine.size() - start ) ; // ���Φr��
        } // else

        temp.school = str ;

//��Ǯ�
		start = 0 ;
        for(int i = 0 ; i < department - 1 ; ++i ) {
            start = InputaLine.find( '\t', start ) ; // �qstart�}�l�M��U�@��'\t'
            ++start ; // �q��e�d�䪺'\t'��m�U�@�r��A�}�l�d��('\t'����=�r��}�l����m)
        } // for   
		    
        ends = InputaLine.find( '\t', start );	// �d��ĴX�Ӥp�r�ꪺ������m(���U�@��tab���e)
        if(ends != string::npos )	{	// ���'\t'
            str = InputaLine.substr( start, ends - start ) ;
        } // if
        else {
            str = InputaLine.substr( start, InputaLine.size() - start ) ; // ���Φr��
        } // else
        temp.department = str ;
        
// ���t
      temp.line = InputaLine ;
      file.push_back(temp) ;				   	
} // Find

void Merge(vector<cT> &all, int &numOfMerge, string &name1, string & name2){
	fstream read ; // �Ω�Ū��
    string InputaLine ; // �Ψ�Ū�@��檺���
    vector<cT> file1 ;
    vector<cT> file2 ;
    struct cT temp ;
      
    cout << "Please enter the filename which you want to open , Ex: copy101.txt,copy102.txt,copy103.txt : " ;
    cin >> name1 ; // Ū�Jtxt�ɪ��W�l
    if ( name1.length() == 7 ) name1 = name1 + ".txt" ; // �Y�ɦW�Ocopy101,�n�۰ʥ[�W.txt
    if ( name1.length() == 3 ) name1 = "copy" + name1 + ".txt" ; // �Y�ɦW�O101,�n�۰ʥ[�Wcopy.txt

    read.open( name1.c_str(), ios::in ) ; // �}��txt�ɮ� (Ū)

    while ( !read ) {  // �ˬd�O�_��}��(���b)
        cout << "!!! The file does not exist !!! "<< endl ;
        cout << "Please enter the filename which you want to open , Ex: copy101.txt,copy102.txt,copy103.txt : " ;
        cin >> name1 ; // Ū�Jtxt�ɪ��W�l
        if ( name1.length() == 7 ) name1 = name1 + ".txt" ;// �Y�ɦW�Ocopy101,�n�۰ʥ[�W.txt
        if ( name1.length() == 3 ) name1 = "copy" + name1 + ".txt" ; // �Y�ɦW�O101,�n�۰ʥ[�Wcopy.txt
        read.open( name1.c_str(), ios::in ) ; // �}���ɮ�(Ū��)
    } // while()
    while( getline( read, InputaLine ) )  {
      Find(InputaLine,file1,temp) ; //��N�X 
	  numOfMerge++ ;    
    } // while
    read.close(); // �����ɮ�
// Ū�Ĥ@����    
    cout << "Please enter the filename which you want to open , Ex: copy101.txt,copy102.txt,copy103.txt : " ;
    cin >> name2 ; // Ū�Jtxt�ɪ��W�l
    if ( name2.length() == 7 ) name2 = name2 + ".txt" ; // �Y�ɦW�Ocopy101,�n�۰ʥ[�W.txt
    if ( name2.length() == 3 ) name2 = "copy" + name2 + ".txt" ; // �Y�ɦW�O101,�n�۰ʥ[�Wcopy.txt

    read.open( name2.c_str(), ios::in ) ; // �}��txt�ɮ� (Ū)

    while ( !read ) {  // �ˬd�O�_��}��(���b)
        cout << "!!! The file does not exist !!! "<< endl ;
        cout << "Please enter the filename which you want to open , Ex: copy101.txt,copy102.txt,copy103.txt : " ;
        cin >> name1 ; // Ū�Jtxt�ɪ��W�l
        if ( name2.length() == 7 ) name2 = name2 + ".txt" ;// �Y�ɦW�Ocopy101,�n�۰ʥ[�W.txt
        if ( name2.length() == 3 ) name2 = "copy" + name2 + ".txt" ; // �Y�ɦW�O101,�n�۰ʥ[�Wcopy.txt
        read.open( name2.c_str(), ios::in ) ; // �}���ɮ�(Ū��)
    } // while()
    while( getline( read, InputaLine ) ) {
      Find(InputaLine,file2,temp) ; // ��N�X 
	  numOfMerge++ ; 
    } // while
    read.close(); // �����ɮ�     
// Ū�ĤG���� 
     
// �}�l�X�֩�iall  
  for( int f1 = 0 ; f1 < file1.size() ; f1++ ){ 
    all.push_back(file1[f1]) ; //����Ĥ@���ɪ���� 
    
    for( int f2 = 0 ; f2 < file2.size() ; f2++ ){ 
      while( file1[f1].school == file2[f2].school && file1[f1].department == file2[f2].department )	 {//���ݬO�_�Ǯլ�t���ۦP 
        all.push_back(file2[f2]) ;
        file2.erase(file2.begin()+f2) ;	    
	  } // while
	} // for
	
    for( int f2 = 0 ; f2 < file2.size() ; f2++ ){
      while( file1[f1].school == file2[f2].school )	{ //�A�ݾǮլO�_�ۦP 
        all.push_back(file2[f2]) ;
        file2.erase(file2.begin()+f2) ;	    
	  } // while
	} // for
  } // for	    
	
	
  for(int i = 0 ; i < file2.size() ; i++ ) { //��ĤG���ɮ׳ѤU����� 
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
    int command = 0 ; // ���ȸ��X
    Manipulator Manipulator ;
    cout << endl << "**** File Object Manipulator ****" ;
    cout << endl << "* 0. QUIT                          *" ; 
    cout << endl << "* 1. COPY (Read & Save a file)     *" ; 
    cout << endl << "* 2. FILTER (Reduce a file)        *" ; 
    cout << endl << "* 3. MERGE (Join two files)        *" ;    
    cout << endl << "**************************************" ;
    cout << endl << "Input a choice(0, 1, 2, 3): " ;

    cin >> command ; // ��J���ȸ��X

    while( command != 0 ) {  // �u�n��J���Ʀr���O0�N�i�H�~���L����
        while ( command < 0 || command > 3 ) {  // �T�O��J�����ȥN���O0.1.2.3(�_�h���s��J)
            cout << endl << "Command does not exist!" << endl ;

    	cout << endl << "**** File Object Manipulator ****" ;
    	cout << endl << "* 0. QUIT                          *" ; 
    	cout << endl << "* 1. COPY (Read & Save a file)     *" ; 
    	cout << endl << "* 2. FILTER (Reduce a file)        *" ; 
    	cout << endl << "* 3. MERGE (Join two files)        *" ;    
    	cout << endl << "**************************************" ;
    	cout << endl << "Input a choice(0, 1, 2, 3): " ;

            cin >> command ; // ��J���ȸ��X
        } // while()

        if ( command == 0 ) return 0 ; // ����
        if ( command == 1 ) Manipulator.MissionOne() ; // �������1
        if ( command == 2 ) Manipulator.MissionTwo() ; // �������2
        if ( command == 3 ) Manipulator.MissionThree() ; // �������3       

    	cout << endl << "**** File Object Manipulator ****" ;
    	cout << endl << "* 0. QUIT                          *" ; 
    	cout << endl << "* 1. COPY (Read & Save a file)     *" ; 
   		cout << endl << "* 2. FILTER (Reduce a file)        *" ; 
    	cout << endl << "* 3. MERGE (Join two files)        *" ;    
    	cout << endl << "**************************************" ;
    	cout << endl << "Input a choice(0, 1, 2, 3): " ;

        cin >> command ; // ��J���ȸ��X

    } // while()
} // main()
//*********************************************************************************


