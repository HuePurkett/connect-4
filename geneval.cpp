//geneval.cpp

//Hue Purkett
//cs470
//project 2
//evaluation function generator
//Not run as part of the connect-4-playing program.

#include<cstdio>
using namespace std;


void writeCode(FILE *out, unsigned long long int m1, unsigned long long int m2, unsigned long long int m3, unsigned long long int m4){
  fprintf(out, "    if(!(p2&%lluULL)){//only count this location if the enemy is not here\n", m1+m2+m3+m4);
  fprintf(out, "      tmp=(bool)(p1&%lluULL)+(bool)(p1&%lluULL)+(bool)(p1&%lluULL)+(bool)(p1&%lluULL);\n", m1, m2, m3, m4);
  fprintf(out, "      ret+=tmp*tmp*tmp;\n");
  fprintf(out, "    }\n");
}


void writeCode2(FILE *out, unsigned long long int m1, unsigned long long int m2, unsigned long long int m3, unsigned long long int m4){
  fprintf(out, "    if(!(p1&%lluULL)){//only count this location for the enemy if you are not here\n", m1+m2+m3+m4);
  fprintf(out, "      tmp=(bool)(p2&%lluULL)+(bool)(p2&%lluULL)+(bool)(p2&%lluULL)+(bool)(p2&%lluULL);\n", m1, m2, m3, m4);
  fprintf(out, "      ret-=tmp*tmp*tmp*tmp;\n");
  fprintf(out, "    }\n");
}


unsigned long long int pow(int i){
  return 1ULL<<i;
}


int main(){
  FILE *out=fopen("eval.cpp", "w");
  fprintf(out, "//eval.cpp\n\n//Hue Purkett\n//cs470\n//project 2\n//evaluation function\n\n");
  fprintf(out, "int eval(unsigned long long int p1, unsigned long long int p2){\n  int ret=0, tmp;\n");

  for(int i=38; i>0; i-=7){//check up central column first
    fprintf(out, "  if(!(p2&%lluULL)){\n", 1ULL<<i);
    for(int j=i-3; j<=i; j++){//row case
      writeCode(out, pow(j), pow(j+1), pow(j+2), pow(j+3));
    }
    for(int j=i; j<42; j+=8){//main diag
      writeCode(out, pow(j), pow(j-8), pow(j-16), pow(j-24));
    }
    for(int j=i; j<42; j+=6){//other diag
      writeCode(out, pow(j), pow(j-6), pow(j-12), pow(j-18));
    }
    if(i>20){//vert central
      writeCode(out, pow(i), pow(i-7), pow(i-14), pow(i-21));
    }
    fprintf(out, "  }\n");
  }

  for(int i=21; i<28; i++){//other verticals
    if(i==24){continue;}
    fprintf(out, "  if(!(p2&%lluULL)){\n", pow(i)+pow(i-7));
    for(int j=i-21; j<i; j+=7){
      writeCode(out, pow(j), pow(j+7), pow(j+14), pow(j+21));
    }
    fprintf(out, "  }\n");
  }


  for(int i=38; i>0; i-=7){//check up central column first
    fprintf(out, "  if(!(p1&%lluULL)){\n", 1ULL<<i);
    for(int j=i-3; j<=i; j++){//rows
      writeCode2(out, pow(j), pow(j+1), pow(j+2), pow(j+3));
    }
    for(int j=i; j<42; j+=8){//main diag
      writeCode2(out, pow(j), pow(j-8), pow(j-16), pow(j-24));
    }
    for(int j=i; j<42; j+=6){//other diag
      writeCode2(out, pow(j), pow(j-6), pow(j-12), pow(j-18));
    }
    if(i>20){//vert central
      writeCode2(out, pow(i), pow(i-7), pow(i-14), pow(i-21));
    }
    fprintf(out, "  }\n");
  }

  for(int i=21; i<28; i++){//other verticals
    if(i==24){continue;}
    fprintf(out, "  if(!(p1&%lluULL)){\n", pow(i)+pow(i-7));
    for(int j=i-21; j<i; j+=7){
      writeCode2(out, pow(j), pow(j+7), pow(j+14), pow(j+21));
    }
    fprintf(out, "  }\n");
  }

  fprintf(out, "  return ret;\n}");
}
