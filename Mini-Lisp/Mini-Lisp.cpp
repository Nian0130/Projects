# include <iostream>    // cout, endl
# include <string>      // string
# include <stdio.h>
# include <cstdlib>     // atoi, system
# include <iomanip>     // setw
# include <vector>
# include <stdlib.h>
# include <math.h>
# include <iomanip>

using namespace std;

struct Token {
  string tokenType ;
  string tokenString ;
} ; 

class Parser {

public :
  void Init() ;
  void GetToken() ;
  void Parse() ;

private :
  char mChar ;
  int mNum ;
  int cur ;
  int l ;
  Token mToken ;
  string mString ;
  string mType ;
  bool IsDigit( char a ) ; 
  bool IsLetter( char a ) ;
  bool IsID( char a ) ;
  bool IsNUM( char a ) ; 
  void CheckID() ;
  void CheckNUM() ;
  void Check() ;
  bool PROGRAM() ;
  bool STMTS() ;
  bool STMT() ;
  bool EXP() ;
  bool PRINTSTMT() ;
  bool VARIABLE() ;
  bool NUMOP() ;
  int Cal() ;
  vector<Token> mAllToken ;
};

void Parser::Init() {
  mChar = '\0' ;
  mString = "\0" ;
  mType = "none" ;
  mToken.tokenString = "\0" ;
  mToken.tokenType = "none" ;
} // Parser::Init()

bool Parser::IsDigit( char a ) {
  if( a >= '0' && a <= '9' ) return true ;
  else return false ;
} // Parser::Init()

bool Parser::IsLetter( char a ) {
  if( a >= 'a' && a <= 'z' ) return true ;
  else return false ;	
} // Parser::IsChar

bool Parser::IsID( char a ) {
  if( IsLetter( a ) ) return true ;
  else if ( IsDigit( a ) ) return true ;
  else if ( a == '-' ) return true ;
  else return false ;	
} // Parser::IsID

bool Parser::IsNUM( char a ) {
  if ( IsDigit( a ) ) return true ;
  else if ( a == '-' ) return true ;
  else return false ;	
} // Parser::IsID

void Parser::CheckID() {
  bool error = false ;
  int max = mString.length() - 1 ;
  if( !IsLetter( mString[0] ) ) error = true ;

  if( max != 0 ) {
    for( int i = 1 ; i <= max ; i++ ) {
      if( !IsID( mString[i] ) ) error = true ;
    } // for()
  } // if

  if( error == true ) mType = "error" ;
  else mType = "id" ;	
} // Parser::CheckID

void Parser::CheckNUM() {
  bool error = false ;
  int max = mString.length() - 1 ;
  if( mString[0] == '-' && max == 0 ) error = true ; // 只有減號 
  if( !IsNUM( mString[0] ) ) error = true ;

  if( max != 0 ) {
    for( int i = 1 ; i <= max ; i++ ) {
      if( !IsDigit( mString[i] ) ) error = true ;
    } // for()
  } // if

  if( error == true ) mType = "error" ;
  else mType = "number" ;	
} // Parser::CheckID
 
void Parser::Check() {
  mToken.tokenString = mString ;
  CheckID() ;
  CheckNUM() ;
  if( mString == "print-num" ) mType = "print-num" ;
  else if( mString == "print-bool" ) mType = "print-bool" ;
  else if( mString == "mod" ) mType = "mod" ;
  else if( mString == "-" ) mType = "minus" ;
  else if( mString == "and" ) mType = "and" ;
  else if( mString == "or" ) mType = "or" ;
  else if( mString == "not" ) mType = "not" ;
  mToken.tokenType = mType ;
  mAllToken.push_back( mToken ) ; 
  Init() ;	
} // Check

void Parser::GetToken() {	

  while ( cin.peek() != EOF ) {	
    mChar = cin.get() ;
	  if( mChar == '\n' || mChar == ' ' || mChar == '\t' || mChar == '\r' ) {    
        if ( mString != "\0" ) {
          Check() ;
        } // if()
          Init() ;
      } // if()

      else if ( mChar == '(' ) { // 遇到(的時候
        if ( mString != "\0" ) {
          Check() ;
        } // if()
 
        mType = "lbr" ; 
        mToken.tokenType = mType ; 
        mToken.tokenString = "(" ;
	    mAllToken.push_back( mToken ) ;
        Init() ; 
      } // else if()

      else if ( mChar == ')' ) { // 遇到)的時候 
        if ( mString != "\0" ) {
          Check() ;
        } // if()

        mType = "rbr" ; 
        mToken.tokenType = mType ; 
        mToken.tokenString = ")" ;
	    mAllToken.push_back( mToken ) ;
        Init() ;
      } // else if()

      else if ( mChar == '#' ) { // 遇到#的時候 
        if ( mString != "\0" ) {
          Check() ;
        } // if()
        mString = mChar ;
        mChar = cin.get() ;
        if( mChar == 't' || mChar == 'f' ){
          mType = "bool-val" ; 	
          mToken.tokenType = mType ; 
          mString = mString + mChar ;
          mToken.tokenString = mString ;
	      mAllToken.push_back( mToken ) ; 
          Init() ;
        }//if
        else{
	      mType = "error" ; 
          mToken.tokenType = mType ; 
          mString = mString + mChar ;
          mToken.tokenString = mString ;
	      mAllToken.push_back( mToken ) ; 
          Init() ;	
        } // else

      } // else if()

      else if ( mChar == '+' ) { // 遇到+的時候 
        if ( mString != "\0" ) {
          Check() ;
        } // if()

        mType = "plus" ; 
        mToken.tokenType = mType ; 
        mToken.tokenString = "+" ;
	    mAllToken.push_back( mToken ) ;
        Init() ;
      } // else if()

      else if ( mChar == '*' ) { // 遇到*的時候 
        if ( mString != "\0" ) {
          Check() ;
        } // if()

        mType = "mul" ; 
        mToken.tokenType = mType ; 
        mToken.tokenString = "*" ;
	    mAllToken.push_back( mToken ) ;
        Init() ;
      } // else if()

      else if ( mChar == '/' ) { // 遇到/的時候 
        if ( mString != "\0" ) {
          Check() ;
        } // if()

        mType = "div" ; 
        mToken.tokenType = mType ; 
        mToken.tokenString = "/" ;
	    mAllToken.push_back( mToken ) ;
        Init() ;
      } // else if()

      else if ( mChar == '>' ) { // 遇到>的時候 
        if ( mString != "\0" ) {
          Check() ;
        } // if()

        mType = "grtr" ; 
        mToken.tokenType = mType ; 
        mToken.tokenString = ">" ;
	    mAllToken.push_back( mToken ) ;
        Init() ;
      } // else if()

      else if ( mChar == '<' ) { // 遇到<的時候 
        if ( mString != "\0" ) {
          Check() ;
        } // if()

        mType = "smlr" ; 
        mToken.tokenType = mType ; 
        mToken.tokenString = "<" ;
	    mAllToken.push_back( mToken ) ;
        Init() ;
      } // else if()

      else if ( mChar == '=' ) { // 遇到=的時候 
        if ( mString != "\0" ) {
          Check() ;
        } // if()

        mType = "eql" ; 
        mToken.tokenType = mType ; 
        mToken.tokenString = "equal" ;
	    mAllToken.push_back( mToken ) ;
        Init() ;
      } // else if()
          
      else {
        mString = mString + mChar ;
      } // else()

  } // while()

} // Parser::GetToken()
//=========================================== 文法部分 
bool Parser::PROGRAM() {
  if( STMTS() )
      return true ;
  else
    return false ;
} // Parser::PROGRAM()
 
bool Parser::STMTS() {
  if ( mNum >= mAllToken.size() )
    return true ;
  else if( STMT() ) {
	if( STMTS() )
      return true ;
  } // else if
  else
    return false ;
} // Parser::STMTS()

bool Parser:: STMT() { 
  if ( mNum >= mAllToken.size() )
    return true ;
  else if( PRINTSTMT() )
    return true ;
  else if( EXP() )
    return true ;
  else
    return false ;
} // Parser::STMT()

bool Parser:: EXP() {
  if ( mNum >= mAllToken.size() )
    return true ;	
  else if( mAllToken[mNum].tokenType == "bool-val" ) {
	mNum++ ;
	return true ;
  } // else if
  else if( mAllToken[mNum].tokenType == "number" ){
	mNum++ ;
	return true ;
  } // else if
  else if( VARIABLE() )
    return true ;
  else if( NUMOP() )
    return true;
  else
    return false ;	
} // Parser::EXP()

bool Parser:: PRINTSTMT() {	 
  if ( mNum >= mAllToken.size() )
    return true ;
  else if( mAllToken[mNum].tokenType == "lbr" )	{
	  mNum++ ;
      if( mAllToken[mNum].tokenType == "print-num" ) {
	    mNum++ ;
        if( EXP() ) {
          if( mAllToken[mNum].tokenType == "rbr" ) {
	        mNum++ ;
            return true ;
          } // if
          else return false ;
        } // if
        else return false ;
      } // if
      else if( mAllToken[mNum].tokenType == "print-bool" ) { 
	    mNum++ ;
        if( EXP() ) { 
          if( mAllToken[mNum].tokenType == "rbr" ) { 
	        mNum++ ;
            return true ;
          } // if
          else return false ;
        } // if
        else return false ;
      } // else if
      else {
	    mNum-- ;
        return false ;
      }
  } // else if

  else 
    return false ;

} // Parser::PRINTSTMT()

bool Parser:: VARIABLE()  {
  if ( mNum >= mAllToken.size() )
    return true ;
  else if( mAllToken[mNum].tokenType == "id" )
    return true ;
  else
    return false ;
} // Parser::VARIABLE()

bool Parser:: NUMOP()  {
  if( mNum >= mAllToken.size() )
    return true ;
  else if( mAllToken[mNum].tokenType == "lbr" )	{
	mNum++ ;
      if( mAllToken[mNum].tokenType == "plus" ) {
	    mNum++ ;
        if( EXP() ){
          while( EXP() ) {	
          } // while
          if( mAllToken[mNum].tokenType == "rbr" ) {
	          mNum++ ;
              return true ;
          } // if
          else return false ; 
        } // if
        else return false ;
      } // if plus

      else if( mAllToken[mNum].tokenType == "minus" ) {
	    mNum++ ;
        if( EXP() ) {
          if( EXP() ) {	     
            if( mAllToken[mNum].tokenType == "rbr" ) {
	          mNum++ ;
              return true ;
            } // if
            else return false ;
          } // if
          else return false ;
        } // if
        else return false ;
      } // else if minus
      else if( mAllToken[mNum].tokenType == "mul" ) {
	    mNum++ ;
        if( EXP() ){
          while( EXP() ) {	     
          } // while
          if( mAllToken[mNum].tokenType == "rbr" ) {
	        mNum++ ;
            return true ;
          } // if
          else return false ;
        } // if
        else return false ;
      } // else if mul
      else if( mAllToken[mNum].tokenType == "div" ) {
	    mNum++ ;
        if( EXP() ) {
          if( EXP() ) {	   
            if( mAllToken[mNum].tokenType == "rbr" ) {        
	          mNum++ ;
              return true ;
            } // if
            else return false ;
          } // if
          else return false ;
        } // if
        else return false ;
      } // else if div

      else if( mAllToken[mNum].tokenType == "mod" ) {
	    mNum++ ;
        if( EXP() ) {
          if( EXP() ) {	  
            if( mAllToken[mNum].tokenType == "rbr" ) {
	          mNum++ ;
              return true ;
            } // if
            else return false ;
          } // if
          else return false ;
        } // if
        else return false ;
      } // else if mod

      else if( mAllToken[mNum].tokenType == "grtr" ) {
	    mNum++ ;
        if( EXP() ) {	      
          if( EXP() ) {	      
            if( mAllToken[mNum].tokenType == "rbr" ) {
	          mNum++ ;
              return true ;
            } // if
            else return false ;
          } // if
          else return false ;
        } // if
        else return false ;
      } // else if grtr

      else if( mAllToken[mNum].tokenType == "smlr" ) {
	    mNum++ ;
        if( EXP() ) {	      
          if( EXP() ) {	      
            if( mAllToken[mNum].tokenType == "rbr" ) {
	          mNum++ ;
              return true ;
            } // if
            else return false ;
          } // if
          else return false ;
        } // if
        else return false ;
      } // else if smlr

      else if( mAllToken[mNum].tokenType == "eql" ) {
	    mNum++ ;
        if( EXP() ){
          while( EXP() ) {	      
          } // while
          if( mAllToken[mNum].tokenType == "rbr" ) {
	        mNum++ ;
            return true ;
          } // if
          else return false ;
        } // if
        else return false ;
      } // else if eql
      else{
	    mNum-- ;
        return false ;
      } // else
  } // else if lbr

  else
    return false ; 
	
} // Parser::NUMOP()

int Parser::Cal(){	
  int ans = 0 ;
  if( mAllToken[cur].tokenType == "lbr" ) {
	cur++ ;
    if( mAllToken[cur].tokenType == "mod" ){
	  cur++ ;
	  if( mAllToken[cur].tokenType == "number" ) {
        ans = atoi( mAllToken[cur].tokenString.c_str() ) ;
        cur++ ;
      } // if	
	  else if( mAllToken[cur].tokenType == "lbr" ) 
        ans = Cal() ;
	  if( mAllToken[cur].tokenType == "number" ) {
        ans = ans % atoi( mAllToken[cur].tokenString.c_str() ) ;
        cur++ ;
      } // if	
	  else if( mAllToken[cur].tokenType == "lbr" ) 
        ans = ans % Cal() ; 
      cur++ ;
      return ans ;	    
    } // if %

    else if( mAllToken[cur].tokenType == "minus" ){
	  cur++ ;	
	  if( mAllToken[cur].tokenType == "number" ) {
        ans = atoi( mAllToken[cur].tokenString.c_str() ) ;
        cur++ ;
      }  // if	
	  else if( mAllToken[cur].tokenType == "lbr" ) 
        ans = Cal() ;
	  if( mAllToken[cur].tokenType == "number" ) {
        ans = ans - atoi( mAllToken[cur].tokenString.c_str() ) ;
        cur++ ;
      } // if	
	  else if( mAllToken[cur].tokenType == "lbr" ) 
        ans = ans - Cal() ;
      cur++ ;
      return ans ;	    
    } // if -

    else if( mAllToken[cur].tokenType == "div" ){
	  cur++ ;	
	  if( mAllToken[cur].tokenType == "number" ) {
        ans = atoi( mAllToken[cur].tokenString.c_str() ) ;
        cur++ ;
      } // if 	
	  else if( mAllToken[cur].tokenType == "lbr" ) 
        ans = Cal() ;
	  if( mAllToken[cur].tokenType == "number" ) {
        ans = ans / atoi( mAllToken[cur].tokenString.c_str() ) ;
        cur++ ;
      } // if	
	    else if( mAllToken[cur].tokenType == "lbr" ) 
          ans = ans / Cal() ;
        cur++ ;
      return ans ;	    
    } // if /
//******************
    else if( mAllToken[cur].tokenType == "plus" ){	
	  cur++ ;   
	  if( mAllToken[cur].tokenType == "number" ) {
        ans = atoi( mAllToken[cur].tokenString.c_str() ) ;
        cur++ ;
      }  		
	  else if( mAllToken[cur].tokenType == "lbr" ) 
        ans = Cal() ;
      while( mAllToken[cur].tokenType != "rbr" ) {
	    if( mAllToken[cur].tokenType == "number" ) {
          ans = ans + atoi( mAllToken[cur].tokenString.c_str() ) ;
          cur++ ;
        } 	
	    else if( mAllToken[cur].tokenType == "lbr" ) 
          ans = ans + Cal() ;	
      } // while
      cur++ ; 
      return ans ;
    } // else if +

    else if( mAllToken[cur].tokenType == "mul" ){	
	  cur++ ; 
	  if( mAllToken[cur].tokenType == "number" ) {
        ans = atoi( mAllToken[cur].tokenString.c_str() ) ;
        cur++ ;
      }  		
	  else if( mAllToken[cur].tokenType == "lbr" ) 
        ans = Cal() ;
      while( mAllToken[cur].tokenType != "rbr" ) {
	    if( mAllToken[cur].tokenType == "number" ) {
          ans = ans * atoi( mAllToken[cur].tokenString.c_str() ) ;
          cur++ ; 		
        }
	    else if( mAllToken[cur].tokenType == "lbr" ) 
          ans = ans * Cal() ;	
      } // while
      cur++ ;
      return ans ;
    } // else if *

//******************
  } // if lbr

} // Parser::Cal()

void Parser::Parse() {
  mNum = 0 ;
/*
  for( int i = 0 ; i < mAllToken.size() ; i++ ) 
	cout << mAllToken[i].tokenType << "---" << mAllToken[i].tokenString << endl ;
*/
  if( PROGRAM() ) {
    for( int i = 0 ; i < mAllToken.size() ; i++ ) {
	  if( mAllToken[i].tokenType == "print-num" ) {
	    if( mAllToken[i+1].tokenType == "number" ) {
	      cout << mAllToken[i+1].tokenString << endl ;
        } // if
        else if( mAllToken[i+1].tokenType == "lbr" ){
	      cur = i + 1 ;
          l = 0 ;
	      int output = Cal() ;
          cout << output << endl ;	
        } // else if

      } // if num

	  if( mAllToken[i].tokenType == "print-bool" ) {
	    if( mAllToken[i+1].tokenType == "bool-val" ) {
	      cout << mAllToken[i+1].tokenString << endl ;
        } // if
        else if( mAllToken[i+1].tokenType == "lbr" ){
		  cur = i+1;
	      // Cal() ;
        } // else if
      } // if num

    } // for
      
  } // if program
  else cout << "syntax error" << endl ;
  mNum = 0 ;
  mAllToken.clear() ;
} // Parser::Parse()

int main() {
  Parser parser ;
  parser.Init() ;	
  parser.GetToken() ;
  parser.Parse() ;
} // main()
