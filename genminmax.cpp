//genminmax.cpp

//Hue Purkett
//cs470
//project 2
//minmax functions generator
//Not run as part of the connect-4-playing program.

#include<cstdio>
using namespace std;

//const int LOOKAHEAD=12;


FILE *out;

unsigned long long int pow(int i){return 1ULL<<i;}

void indent(int j){for(int i=0; i<j; i++){fprintf(out, "  ");}}

void writeCode(unsigned long long int mask, int ind, int base){
  indent(ind);
  fprintf(out, "if(total&%lluULL){//if space is filled, continue upwards, else move here\n", mask);
  if(mask>64){
    writeCode(mask>>7, ind+1, base);
  }else{
    indent(ind);
    fprintf(out, "  //column full -- do nothing\n");
  }
  indent(ind);
  fprintf(out, "}else{\n");


  indent(ind);
  fprintf(out, "  if(mm){//max\n");
  indent(ind);
  fprintf(out, "    tmp=minmax(p1|%lluULL, p2, total|%lluULL, level+1, best, false);\n", mask, mask);
  indent(ind);
  fprintf(out, "    if(tmp>=ab){return tmp;}//alpha-beta pruning\n");
  indent(ind);
  fprintf(out, "    if(tmp>best){best=tmp; bm=%i;}//new best move found\n", base);
  indent(ind);
  fprintf(out, "  }else{//min\n");
  indent(ind);
  fprintf(out, "    tmp=minmax(p1, p2|%lluULL, total|%lluULL, level+1, best, true);\n", mask, mask);
  indent(ind);
  fprintf(out, "    if(tmp<=ab){return tmp;}//alpha-beta pruning\n");
  indent(ind);
  fprintf(out, "    if(tmp<best){best=tmp; bm=%i;}//new best move found\n", base);
  indent(ind);
  fprintf(out, "  }\n");


  indent(ind);
  fprintf(out, "}\n");
}


int main(){
  out=fopen("minmax.cpp", "w");
  unsigned long long int a[]={pow(38), pow(37), pow(39), pow(36), pow(40), pow(35), pow(41)};
  int b[]={38, 37, 39, 36, 40, 35, 41};

  fprintf(out, "//minmax.cpp\n\n//Hue Purkett\n//cs470\n//project 2\n//min-max functions\n\n");
  fprintf(out, "extern bool win(unsigned long long int);\n");
  fprintf(out, "extern int eval(unsigned long long int, unsigned long long int);\n\n");
  fprintf(out, "extern int lookahead;\n");
  fprintf(out, "int bestMove;\n");

  fprintf(out, "int minmax(unsigned long long int p1, unsigned long long int p2, unsigned long long int total, int level, int ab, bool mm){\n");
  fprintf(out, "  int best;\n");
  fprintf(out, "  if(mm){//max\n");
  fprintf(out, "    if(win(p2)){return -2000000+level;}//+level to force shortest path to win\n");
  fprintf(out, "    best=-3000000;\n");
  fprintf(out, "  }else{//min\n");
  fprintf(out, "    if(win(p1)){return 2000000-level;}//-level to force shortest path to win\n");
  fprintf(out, "    best=3000000;\n");
  fprintf(out, "  }\n");
  fprintf(out, "  if(level==lookahead||total==%lluULL){return eval(p1, p2);}//evaluate immediately if lookahead reached or board full\n", pow(42)-1);
  fprintf(out, "  int tmp, bm;\n");
  for(int i=0; i<7; i++){
    writeCode(a[i], 1, b[i]-35);
  }
  fprintf(out, "  bestMove=bm;\n");
  fprintf(out, "  return best;\n");
  fprintf(out, "}\n");
}
