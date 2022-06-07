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

class BSTREE {
	
typedef struct pT {
	string line ;
	int num;
	string name;
    string type1;
    int total ;
    int hp ;
    int atk ;
    int def ;
} pokemonType ;

typedef struct BST {
	vector<pokemonType> item ;
	int level ;
	struct BST *leftNode ;
	struct BST *rightNode ;
} nodeType ;	

int visit ;
int height ;
vector<pT> pSet ;	
nodeType *root ;
					
void Find( string &temp1, int &temp,int num, string InputaLine ) {	
        string str ; // 切割出來的
        int start = 0 ; // 紀錄一整個大字串開始的位置
        int ends = 0 ;
			
        for(int i = 0 ; i < num - 1 ; ++i ) {
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
        if( num != 2 && num != 3 ){ //非字串時 
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
            change >> temp ;

          }
          else { // 正常情況
            stringstream change ; // 字串轉數字
            change << str ; // 將num字串轉成數字
            change >> temp ;
          }           
		} // if
		
		else //字串 
		  temp1 = str ;
} // Find

void Read() {
    fstream read ; // 用於讀檔
    string InputaLine ; // 用來讀一整行的資料
    int temp = 0 ;
    string temp1 ;
    string fileName ;
    pT pokemon ;
    cout << "Please enter the filename which you want to open , Ex: input101.txt,copy102.txt,copy103.txt : " ;
    cin >> fileName ; // 讀入txt檔的名子
    if ( fileName.length() == 8 ) fileName = fileName + ".txt" ; // 若檔名是input101,要自動加上.txt
    if ( fileName.length() == 3 ) fileName = "input" + fileName + ".txt" ; // 若檔名是101,要自動加上input.txt

    read.open( fileName.c_str(), ios::in ) ; // 開啟txt檔案 (讀)

    while ( !read ) {  // 檢查是否能開啟(防呆)
        cout << "!!! The file does not exist !!! "<< endl ;
        cout << "Please enter the filename which you want to open , Ex: copy101.txt,copy102.txt,copy103.txt : " ;
        cin >> fileName ; // 讀入txt檔的名子
        if ( fileName.length() == 8 ) fileName = fileName + ".txt" ;// 若檔名是copy101,要自動加上.txt
        if ( fileName.length() == 3 ) fileName = "input" + fileName + ".txt" ; // 若檔名是101,要自動加上input,.txt
        read.open( fileName.c_str(), ios::in ) ; // 開啟檔案(讀檔)
    } // while()

	getline( read, InputaLine ) ; //讀掉第一列 
    while( getline( read, InputaLine ) ) { 
	    int num = 1 ;
    	int name = 2 ; 
    	int type1 = 3 ; 
    	int total = 5 ;
    	int hp = 6 ;
    	int atk = 7 ;
    	int def = 8 ;
    	pokemon.line = InputaLine ;
        Find(temp1,temp,num,InputaLine) ;
        pokemon.num = temp ;
        Find(temp1,temp,name,InputaLine) ;
        pokemon.name = temp1 ;     
        Find(temp1,temp,type1,InputaLine) ;
        pokemon.type1 = temp1 ;
        Find(temp1,temp,total,InputaLine) ;
        pokemon.total = temp ;
        Find(temp1,temp,hp,InputaLine) ;
        pokemon.hp = temp ;
        Find(temp1,temp,atk,InputaLine) ;
        pokemon.atk = temp ;
        Find(temp1,temp,def,InputaLine) ;
        pokemon.def = temp ;
    	pSet.push_back(pokemon) ;								   		  	  
	} // while	
    read.close(); // 關閉檔案
} // Read
void Print(){	
	cout << "\t#\tName\t\tType1\tHP\tAttack\tDefense" << endl ; 
	for( int i = 0 ; i < pSet.size() ; i++ ){
		if( pSet[i].name.length() > 7 )
			cout << "[" << i+1 << "]\t" << pSet[i].num << "\t" << pSet[i].name << "\t" << pSet[i].type1 ;
		else
			cout << "[" << i+1 << "]\t" << pSet[i].num << "\t" << pSet[i].name << "\t\t" << pSet[i].type1 ;	
		cout << "\t" << pSet[i].hp << "\t" << pSet[i].atk << "\t" << pSet[i].def << endl ;
	} // for
} // Print

void Build(){
	nodeType *temp ;
	nodeType *current ;
	int i = 0 ;
	int level = 1 ;        // 樹階
	height = 1 ;       // 樹高
	bool sameData = false ; // 用來判斷資料血量是否和節點血量相同
	// 建立樹根
	root = new nodeType ; 
	root->item.push_back( pSet[i] ) ;
	root->leftNode = NULL ;
	root->rightNode = NULL ;
	root->level = 1 ;
	i++ ;

	// 把所有資料加入樹中 
	while( i < pSet.size() ) {
		current = root ;
		temp = root ;
		// 將要放進的資料和樹中節點比大小 來決定往左子樹還是右子樹走
		while( current != NULL && ! sameData ) {
			// 資料血量比節點血量小 往左子樹走 
			if( current->item[0].hp > pSet[i].hp ) {
				temp = current ;
				current = current->leftNode ;
				level ++ ;
			}
			// 資料血量比節點血量大 往右子樹走
			else if( current->item[0].hp < pSet[i].hp ) {
				temp = current ;
				current = current->rightNode ;
				level ++ ;
			}
			// 資料血量和節點血量相同 將資料放進節點中
			else if( current->item[0].hp == pSet[i].hp ) {
				current->item.push_back( pSet[i] ) ;
				sameData = true ;
			}
		}

		// 沒有子樹可以走了 建立新節點 
		if( temp->item[0].hp > pSet[i].hp && !sameData ) {
			temp->leftNode = new nodeType ;
			current = temp->leftNode ;
			current->item.push_back( pSet[i] ) ;
			current->leftNode = NULL ;
			current->rightNode = NULL ;
			current->level = level ;
		}
		else if( temp->item[0].hp < pSet[i].hp && !sameData ) {
			temp->rightNode = new nodeType ;
			current = temp->rightNode ;
			current->item.push_back( pSet[i] ) ;
			current->leftNode = NULL ;
			current->rightNode = NULL ;
			current->level = level ;
		}

		// 更新樹高 
		if( level > height ) height = level ;
			i++ ;
			level = 1 ;
			sameData = false ;
	} // while 
		cout << "HP tree height = " << height << endl ; 	
	pSet.clear() ; // 清空pSet 
} // Build

void PreOrder( int &visitedNode, int input, nodeType *root, vector<pokemonType> &Data ) {
	// 若已經沒有子樹 就結束這層遞迴 
	if( root == NULL ) return ;			
	visitedNode ++ ;
	int i = 0 ;
	// 若節點血量比門檻大 就將資料放進vector中 
	if( root->item[0].hp >= input ) {
		while( i < root->item.size() ) {
			Data.push_back( root->item[i] ) ;
			i ++ ;
		} // while
	} // if		
	if( root->item[0].hp > input ) PreOrder( visitedNode, input, root->leftNode, Data ) ;
	PreOrder( visitedNode, input, root->rightNode, Data ) ;
} // PreOrder

void SwapData( vector<pokemonType> &Data, int i, int max ) {
	pokemonType temp ;			
	temp.num = Data[i].num ;
	temp.name = Data[i].name  ;
	temp.type1 = Data[i].type1  ;
	temp.total = Data[i].total ;
	temp.hp = Data[i].hp ;
	temp.atk = Data[i].atk ;
	temp.def = Data[i].def ;
	// temp
	Data[i].num = Data[max].num ;
	Data[i].name = Data[max].name  ;
	Data[i].type1 = Data[max].type1  ;
	Data[i].total = Data[max].total ;
	Data[i].hp = Data[max].hp ;
	Data[i].atk = Data[max].atk ;
	Data[i].def = Data[max].def ;
	// i
	Data[max].num = temp.num ;
	Data[max].name = temp.name  ;
	Data[max].type1 = temp.type1  ;
	Data[max].total = temp.total ;
	Data[max].hp = temp.hp ;
	Data[max].atk = temp.atk ;
	Data[max].def = temp.def ;
	// max
} // SwapData
 
void Sort( vector<pokemonType> &Data ) {
	int max = 0 ; // 目前所有資料裡面最大的那一筆資料
	int i = 0 ;
	int j = 1 ;

	while( i < Data.size() ) {
	 	while( j < Data.size() ) {
	 		// 若 Data[j]的資料為目前最大 就將它設為max 
			if( Data[j].hp > Data[max].hp ) {
				max = j ;
			} // if
			else if( Data[j].hp == Data[max].hp ){
				if(Data[j].num < Data[max].num){
				  max = j ;	
				}				
			}
			j++ ;
		} // while	
		// 將max和最前面的資料交換位置 
		SwapData( Data, i, max ) ;			
		i++ ;
		j = i + 1 ;
		max = i ;
	} // while
} // Sort
				
void Search() {			
	vector<pokemonType> Data ;
	int input = -1 ;
	int visitedNode = 0 ;			
	// 讀取一正整數 
	cout << "Input a positive integer: "  ;
	cin >> input ;
	while( input < 0 ) {
		cout << "Error!  It's not a positive integer." << endl ;
		cout << "Input a positive integer: " ;
		cin >> input ;
	} // while
		
	PreOrder( visitedNode, input, root, Data ) ;		
	Sort( Data ) ;			
	cout << "\t#\tName\t\tType1\tTotal\tHP\tAttack\tDefense" << endl ; 
	for( int i = 0 ; i < Data.size() ; i++ ){
		if( Data[i].name.length() > 7 )
			cout << "[" << i+1 << "]\t" << Data[i].num << "\t" << Data[i].name << "\t" << Data[i].type1 ;
		else
			cout << "[" << i+1 << "]\t" << Data[i].num << "\t" << Data[i].name << "\t\t" << Data[i].type1 ;	
		cout << "\t" << Data[i].total << "\t" << Data[i].hp << "\t" << Data[i].atk << "\t" << Data[i].def << endl ;
	} // for	
	cout << "Number of visited nodes = " << visitedNode << endl ;
} // Search
	
// 重設樹階 
void Reset( nodeType *root, int level ) {
	if( root == NULL ) return ;
	Reset( root->leftNode, level+1 ) ;
	Reset( root->rightNode, level+1 ) ;
			
	root->level = level ;
} // Reset 
		 
// 計算樹高 
void FindHeight( nodeType *root ) {
	if( root == NULL ) return ;
	FindHeight( root->leftNode ) ;
	FindHeight( root->rightNode ) ;
	if( height < root->level ) height = root->level ;
} // FindHeight
	
void Delete() {			
	nodeType *current = root ;
	nodeType *temp = NULL ;
	nodeType *before = NULL ;
	// 找最大值 
	while( current->rightNode != NULL ) {
		before = current ;
		current = current->rightNode ;
	} // while
		
	cout << "#\tName\tType 1\tType 2\tTotal\tHP\tAttack\tDefense\tSp.Atk\tSp.Def\tSpeed\tGeneration\tLegendary" << endl ;
	cout << current->item[current->item.size()-1].line << endl ;
 
// 只有root 
	if( root->rightNode == NULL && root->leftNode == NULL ) {
		if( root->item.size() > 1 ) //超過一筆資料 
		    root->item.pop_back() ;
		else { //只有一筆資料 
			delete root ;
			root = NULL ;
		}
	}
//	root為最大值 
	else if( before == NULL ) {
		if( current->item.size() > 1 ) 
		    current->item.pop_back() ;
		else {
			root = root->leftNode ;
			cout << root->item[0].hp << endl ;
			delete current ;
		}
	}
// 要刪的節點沒有左節點 
	else if( current->leftNode == NULL ) {
		if( current->item.size() > 1 ) 
			current->item.pop_back() ;
		else {
			delete current ;
			before->rightNode = NULL ;
		}
	}
// 要刪的節點有左節點 
	else if( current->leftNode != NULL ) {
		if( current->item.size() > 1 ) 
			current->item.pop_back() ;
		else { 
			temp = current->leftNode ;
			delete current ;
			before->rightNode = temp ;
		} 
	}			
	Reset( root, 1 ) ;			
	height = 0 ;
	FindHeight( root ) ;
	cout << "HP Tree Hight : " << height << endl ;
}

    public :
        void MissionOne() {
			Read() ;
			Print() ;
			Build()	;	
        }
        void MissionTwo() {
        	Search() ;
        }		    	
        void MissionThree() {
        	Delete() ;
        }
};
   
int main() {
    int command = 0 ; // 任務號碼 
    bool tree = false ;
    BSTREE pokemonList ;
    cout << endl << "**** Binary Search Tree on Pokemon ****" ;
    cout << endl << "* 0. QUIT                          *" ; 
    cout << endl << "* 1. Read one file to build BST    *" ; 
    cout << endl << "* 2. Threshold search on one column*" ; 
    cout << endl << "* 3. Delete the max on one column  *" ;    
    cout << endl << "**************************************" ;
    cout << endl << "Input a choice(0, 1, 2, 3): " ;

    cin >> command ; // 輸入任務號碼

    while( command != 0 ) {  // 只要輸入的數字不是0就可以繼續其他任務
        while ( command < 0 || command > 3 ) {  // 確保輸入的任務代號是0.1.2.3(否則重新輸入)
            cout << endl << "Command does not exist!" << endl ;

    cout << endl << "**** Binary Search Tree on Pokemon ****" ;
    cout << endl << "* 0. QUIT                          *" ; 
    cout << endl << "* 1. Read one file to build BST    *" ; 
    cout << endl << "* 2. Threshold search on one column*" ; 
    cout << endl << "* 3. Delete the max on one column  *" ;    
    cout << endl << "**************************************" ;
    cout << endl << "Input a choice(0, 1, 2, 3): " ;

            cin >> command ; // 輸入任務號碼
        } // while()

        if ( command == 0 ) return 0 ; // 結束
        if ( command == 1 ) {
		  pokemonList.MissionOne() ; // 執行任務1
		  tree = true ;
	    }
        if ( command == 2 && tree == true ) pokemonList.MissionTwo() ; // 執行任務2
        if ( command == 2 && tree == false ) cout << "Execute Mission 1 first!" << endl ; 
        if ( command == 3 && tree == true ) pokemonList.MissionThree() ; // 執行任務3       
		if ( command == 3 && tree == false ) cout << "Execute Mission 1 first!" << endl ; 
    cout << endl << "**** Binary Search Tree on Pokemon ****" ;
    cout << endl << "* 0. QUIT                          *" ; 
    cout << endl << "* 1. Read one file to build BST    *" ; 
    cout << endl << "* 2. Threshold search on one column*" ; 
    cout << endl << "* 3. Delete the max on one column  *" ;    
    cout << endl << "**************************************" ;
    cout << endl << "Input a choice(0, 1, 2, 3): " ;

        cin >> command ; // 輸入任務號碼

    } // while()
} // main()
//*********************************************************************************


