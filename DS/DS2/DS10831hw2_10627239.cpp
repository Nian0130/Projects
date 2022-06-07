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
        string str ; // ���ΥX�Ӫ�
        int start = 0 ; // �����@��Ӥj�r��}�l����m
        int ends = 0 ;
			
        for(int i = 0 ; i < num - 1 ; ++i ) {
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
        if( num != 2 && num != 3 ){ //�D�r��� 
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
            change >> temp ;

          }
          else { // ���`���p
            stringstream change ; // �r����Ʀr
            change << str ; // �Nnum�r���ন�Ʀr
            change >> temp ;
          }           
		} // if
		
		else //�r�� 
		  temp1 = str ;
} // Find

void Read() {
    fstream read ; // �Ω�Ū��
    string InputaLine ; // �Ψ�Ū�@��檺���
    int temp = 0 ;
    string temp1 ;
    string fileName ;
    pT pokemon ;
    cout << "Please enter the filename which you want to open , Ex: input101.txt,copy102.txt,copy103.txt : " ;
    cin >> fileName ; // Ū�Jtxt�ɪ��W�l
    if ( fileName.length() == 8 ) fileName = fileName + ".txt" ; // �Y�ɦW�Oinput101,�n�۰ʥ[�W.txt
    if ( fileName.length() == 3 ) fileName = "input" + fileName + ".txt" ; // �Y�ɦW�O101,�n�۰ʥ[�Winput.txt

    read.open( fileName.c_str(), ios::in ) ; // �}��txt�ɮ� (Ū)

    while ( !read ) {  // �ˬd�O�_��}��(���b)
        cout << "!!! The file does not exist !!! "<< endl ;
        cout << "Please enter the filename which you want to open , Ex: copy101.txt,copy102.txt,copy103.txt : " ;
        cin >> fileName ; // Ū�Jtxt�ɪ��W�l
        if ( fileName.length() == 8 ) fileName = fileName + ".txt" ;// �Y�ɦW�Ocopy101,�n�۰ʥ[�W.txt
        if ( fileName.length() == 3 ) fileName = "input" + fileName + ".txt" ; // �Y�ɦW�O101,�n�۰ʥ[�Winput,.txt
        read.open( fileName.c_str(), ios::in ) ; // �}���ɮ�(Ū��)
    } // while()

	getline( read, InputaLine ) ; //Ū���Ĥ@�C 
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
    read.close(); // �����ɮ�
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
	int level = 1 ;        // ��
	height = 1 ;       // ��
	bool sameData = false ; // �ΨӧP�_��Ʀ�q�O�_�M�`�I��q�ۦP
	// �إ߾��
	root = new nodeType ; 
	root->item.push_back( pSet[i] ) ;
	root->leftNode = NULL ;
	root->rightNode = NULL ;
	root->level = 1 ;
	i++ ;

	// ��Ҧ���ƥ[�J�� 
	while( i < pSet.size() ) {
		current = root ;
		temp = root ;
		// �N�n��i����ƩM�𤤸`�I��j�p �ӨM�w�����l���٬O�k�l��
		while( current != NULL && ! sameData ) {
			// ��Ʀ�q��`�I��q�p �����l�� 
			if( current->item[0].hp > pSet[i].hp ) {
				temp = current ;
				current = current->leftNode ;
				level ++ ;
			}
			// ��Ʀ�q��`�I��q�j ���k�l��
			else if( current->item[0].hp < pSet[i].hp ) {
				temp = current ;
				current = current->rightNode ;
				level ++ ;
			}
			// ��Ʀ�q�M�`�I��q�ۦP �N��Ʃ�i�`�I��
			else if( current->item[0].hp == pSet[i].hp ) {
				current->item.push_back( pSet[i] ) ;
				sameData = true ;
			}
		}

		// �S���l��i�H���F �إ߷s�`�I 
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

		// ��s�� 
		if( level > height ) height = level ;
			i++ ;
			level = 1 ;
			sameData = false ;
	} // while 
		cout << "HP tree height = " << height << endl ; 	
	pSet.clear() ; // �M��pSet 
} // Build

void PreOrder( int &visitedNode, int input, nodeType *root, vector<pokemonType> &Data ) {
	// �Y�w�g�S���l�� �N�����o�h���j 
	if( root == NULL ) return ;			
	visitedNode ++ ;
	int i = 0 ;
	// �Y�`�I��q����e�j �N�N��Ʃ�ivector�� 
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
	int max = 0 ; // �ثe�Ҧ���Ƹ̭��̤j�����@�����
	int i = 0 ;
	int j = 1 ;

	while( i < Data.size() ) {
	 	while( j < Data.size() ) {
	 		// �Y Data[j]����Ƭ��ثe�̤j �N�N���]��max 
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
		// �Nmax�M�̫e������ƥ洫��m 
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
	// Ū���@����� 
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
	
// ���]�� 
void Reset( nodeType *root, int level ) {
	if( root == NULL ) return ;
	Reset( root->leftNode, level+1 ) ;
	Reset( root->rightNode, level+1 ) ;
			
	root->level = level ;
} // Reset 
		 
// �p��� 
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
	// ��̤j�� 
	while( current->rightNode != NULL ) {
		before = current ;
		current = current->rightNode ;
	} // while
		
	cout << "#\tName\tType 1\tType 2\tTotal\tHP\tAttack\tDefense\tSp.Atk\tSp.Def\tSpeed\tGeneration\tLegendary" << endl ;
	cout << current->item[current->item.size()-1].line << endl ;
 
// �u��root 
	if( root->rightNode == NULL && root->leftNode == NULL ) {
		if( root->item.size() > 1 ) //�W�L�@����� 
		    root->item.pop_back() ;
		else { //�u���@����� 
			delete root ;
			root = NULL ;
		}
	}
//	root���̤j�� 
	else if( before == NULL ) {
		if( current->item.size() > 1 ) 
		    current->item.pop_back() ;
		else {
			root = root->leftNode ;
			cout << root->item[0].hp << endl ;
			delete current ;
		}
	}
// �n�R���`�I�S�����`�I 
	else if( current->leftNode == NULL ) {
		if( current->item.size() > 1 ) 
			current->item.pop_back() ;
		else {
			delete current ;
			before->rightNode = NULL ;
		}
	}
// �n�R���`�I�����`�I 
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
    int command = 0 ; // ���ȸ��X 
    bool tree = false ;
    BSTREE pokemonList ;
    cout << endl << "**** Binary Search Tree on Pokemon ****" ;
    cout << endl << "* 0. QUIT                          *" ; 
    cout << endl << "* 1. Read one file to build BST    *" ; 
    cout << endl << "* 2. Threshold search on one column*" ; 
    cout << endl << "* 3. Delete the max on one column  *" ;    
    cout << endl << "**************************************" ;
    cout << endl << "Input a choice(0, 1, 2, 3): " ;

    cin >> command ; // ��J���ȸ��X

    while( command != 0 ) {  // �u�n��J���Ʀr���O0�N�i�H�~���L����
        while ( command < 0 || command > 3 ) {  // �T�O��J�����ȥN���O0.1.2.3(�_�h���s��J)
            cout << endl << "Command does not exist!" << endl ;

    cout << endl << "**** Binary Search Tree on Pokemon ****" ;
    cout << endl << "* 0. QUIT                          *" ; 
    cout << endl << "* 1. Read one file to build BST    *" ; 
    cout << endl << "* 2. Threshold search on one column*" ; 
    cout << endl << "* 3. Delete the max on one column  *" ;    
    cout << endl << "**************************************" ;
    cout << endl << "Input a choice(0, 1, 2, 3): " ;

            cin >> command ; // ��J���ȸ��X
        } // while()

        if ( command == 0 ) return 0 ; // ����
        if ( command == 1 ) {
		  pokemonList.MissionOne() ; // �������1
		  tree = true ;
	    }
        if ( command == 2 && tree == true ) pokemonList.MissionTwo() ; // �������2
        if ( command == 2 && tree == false ) cout << "Execute Mission 1 first!" << endl ; 
        if ( command == 3 && tree == true ) pokemonList.MissionThree() ; // �������3       
		if ( command == 3 && tree == false ) cout << "Execute Mission 1 first!" << endl ; 
    cout << endl << "**** Binary Search Tree on Pokemon ****" ;
    cout << endl << "* 0. QUIT                          *" ; 
    cout << endl << "* 1. Read one file to build BST    *" ; 
    cout << endl << "* 2. Threshold search on one column*" ; 
    cout << endl << "* 3. Delete the max on one column  *" ;    
    cout << endl << "**************************************" ;
    cout << endl << "Input a choice(0, 1, 2, 3): " ;

        cin >> command ; // ��J���ȸ��X

    } // while()
} // main()
//*********************************************************************************


