//main.cpp

//Hue Purkett
//cs470
//project 2
//connect-4-playing program

#include<iostream>

using namespace std;

extern bool win(unsigned long long int);
extern unsigned long long int winMask;
extern int eval(unsigned long long int, unsigned long long int);
extern int minmax(unsigned long long int p1, unsigned long long int p2, unsigned long long int total, int level, int ab, bool mm);
//mm is true for max level
extern int bestMove;


bool hasWon=false;
int lookahead=11;

void print(unsigned long long int p1, unsigned long long int p2){
  unsigned long long int mask=1;
  cout<<"|0123456|\n";
  cout<<"|-------|\n";
  for(int i=0; i<6; i++){
    cout<<"|";
    for(int j=0; j<7; j++){
      if(p1&mask){
        if(hasWon&&(mask&winMask)){
          cout<<"X";
        }else{
          cout<<"x";
        }
      }else{
        if(p2&mask){
          if(hasWon&&(mask&winMask)){
            cout<<"O";
          }else{
            cout<<"o";
          }
        }else{
          cout<<" ";
        }
      }
      mask<<=1;
    }
    cout<<"|\n";
  }
  cout<<"|-------|\n";
  cout<<"|0123456|\n";
}


void makeMove(unsigned long long int &p, unsigned long long int &total, int move){
  for(int i=move+35; i>-1; i-=7){
    if(!(total&(1ULL<<i))){
      total|=1ULL<<i;
      p|=1ULL<<i;
      return;
    }
  }
}

int main(int argc, char *argv[]){
  unsigned long long int comp=0, hume=0, total=0;
  int move;

  cout<<"Welcome to connect-4.\n";
  cout<<"Coded by Hue Purkett as part of cs470 at the University of Idaho.\n";
  cout<<"The computer's pieces are 'x's and yours are 'o's.\n";
  cout<<"Enter the number above the column in which you want to move to make that move.\n";
  cout<<"-1 exits.\n\n";

  if(argc%2){//computer goes first
    cout<<"My move: 3"<<endl;
    makeMove(comp, total, 3);
    print(comp, hume);
  }

  for(int i=0; i<21&&!hasWon; i++){
    cout<<"\nYour move: ";
    cin>>move;
    while(move<0||move>6||total&(1ULL<<move)){
      if(move==-1){
        cout<<"Goodbye.\n";
        return 0;
      }
      cout<<"Invalid move. Try again: ";
      cin>>move;
    }
    makeMove(hume, total, move);
    if(i==20&&argc%2){ print(comp, hume); break;}
    if(hasWon=win(hume)){
      print(comp, hume);
      cout<<"Congratulations! You have won!\n";
      return 0;
    }

    print(comp, hume);
    cout<<"\nMy move: "<<flush;
    minmax(comp, hume, total, 0, 4000000, true);
    makeMove(comp, total, bestMove);
    cout<<bestMove<<endl;
    if(hasWon=win(comp)){
      print(comp, hume);
      cout<<"You have lost.\n";
      return 0;
    }
    print(comp, hume);
    if(i==3){lookahead++;}
    if(i-(argc%2)>6){lookahead++;}
    if(argc%2&&i==8){lookahead++;}
    if(i==9){lookahead+=3;}
  }

  cout<<"Draw!\n";
  return 0;
}

