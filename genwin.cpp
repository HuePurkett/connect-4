//genwin.cpp

//Hue Purkett
//cs470
//project 2
//win-checking function generator
//Not run as part of the connect-4-playing program.

#include<cstdio>
using namespace std;

void writeCode(FILE *out, unsigned long long int mask){
  fprintf(out, "    if((board&%lluULL)==%lluULL){winMask=%lluULL; return 1;}\n", mask, mask, mask);
}

unsigned long long int pow(int i){
  return 1ULL<<i;
}

int main(){
  FILE *out=fopen("win.cpp", "w");
  fprintf(out, "//win.cpp\n\n//Hue Purkett\n//cs470\n//project 2\n//win-checking function\n\n");
  fprintf(out, "unsigned long long int winMask;\n\nbool win(unsigned long long int board){\n");

  for(int i=38; i>0; i-=7){//check up central column first
    fprintf(out, "  if(board&%lluULL){//only bother looking in the wins containing this locaion if you are here\n", 1ULL<<i);
    for(int j=i-3; j<=i; j++){//row case
      writeCode(out, pow(j)+pow(j+1)+pow(j+2)+pow(j+3));
    }
    for(int j=i; j<42; j+=8){//main diag
      writeCode(out, pow(j)+pow(j-8)+pow(j-16)+pow(j-24));
    }
    for(int j=i; j<42; j+=6){//other diag
      writeCode(out, pow(j)+pow(j-6)+pow(j-12)+pow(j-18));
    }
    if(i>20){//vert central
      writeCode(out, pow(i)+pow(i-7)+pow(i-14)+pow(i-21));
    }
    fprintf(out, "  }\n");
  }

  for(int i=21; i<28; i++){//other verticals
    if(i==24){continue;}
    fprintf(out, "  if(board&%lluULL){//only bother looking in the wins containing this location if you are here\n", pow(i)+pow(i-7));
    for(int j=i-21; j<i; j+=7){
      writeCode(out, pow(j)+pow(j+7)+pow(j+14)+pow(j+21));
    }
    fprintf(out, "  }\n");
  }

  fprintf(out, "  return false;\n}");
}
