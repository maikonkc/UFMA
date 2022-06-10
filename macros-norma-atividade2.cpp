#include <stdio.h>
#include <iostream>
#include <cstring>
using namespace std;

// Máquina NORMA
// ----------------------------------------------------
// Memória: com 256 registradores
#define  INF    256
unsigned long R[INF];  //

// funções de entrada/saída:
#define ent       memset(R, 0, sizeof (R)),\
                  cout << "X = ", cin  >> R['X']
#define ent2       memset(R, 0, sizeof (R)),\
                  cout << "Z = ", cin  >> R['Z']
#define sai       cout << "Y = ", cout << R['Y'] << "\n"

// conjunto de operações:
#define inc(K)    R[K] += 1
#define dec(K)    R[K] -= R[K] > 0 ? 1 : 0
//#define set(K,n)  R[K] = n
//#define mov(A,B)  R[A] = R[B]

// conjunto de testes:
#define zero(K)   R[K] == 0

// ----------------------------------------------------
// funções auxilares:
void trace(const char* inst) {
  cout << inst << '\n';
  cout << "R[] = { ...";
  for (int i = 0; i < INF; i++)
    if ( i >= 'A' && i <= 'Z' )
      cout << ", " << char(i) << ':' << R[i];
    else if ( R[i] > 0)
      cout << ", " << i << ':' << R[i];
  cout << ", ... }\n";
}

// ----------------------------------------------------
// Sintaxe: Programa Monolítico:
// ----------------------------------------------------
// #define faca(op)     op;
// #define va_para(r)  goto r;
// #define se(t)       if(t)
// #define entao
// #define senao       else

// ----------------------------------------------------
// Sintaxe: Programa Iterativo:
// ----------------------------------------------------
#define se(t)         if(t)
#define entao
#define senao         else
#define enquanto(t)   while(t)
#define faca
#define ate(t)        while(!t)

#define falso         return false;
#define verdadeiro    return true;

// ----------------------------------------------------
// macros
// ----------------------------------------------------
#define usando

// macro: K = 0
void set0(char A) {
  ate(zero(A)) faca {
      dec(A);
  }
}

//  A = 1, ou de modo geral A = n
void set1(char A) {
    set0(A), inc(A);
}

void set2(char A) {
    set1(A), inc(A);
}

void set3(char A) {
    set2(A), inc(A);
}

void set4(char A) {
    set3(A), inc(A);
}

// ...

//#define setn(A, n)   set#n(A)
void set(char A, int n) {
    R[A] = n;
}

// macro :  A = A + B
void add(char A, char B, usando char C) {
  set0(C);
  ate ( zero(B) ) faca {
      inc(A);
      dec(B);
      inc(C);
  }
  ate ( zero(C) ) faca {
      dec(C);
      inc(B);
  }
}

// macro:  A = B
void mov(char A, char B, usando char C) {
    set0(A);
    add(A, B, usando C);
}

// macro: A = A x B
void mul(char A, char B, usando char C, char D) {
    set0(C);
    ate ( zero(A) ) faca {
      inc(C);
      dec(A);
    }
    ate ( zero(C) ) faca {
      add(A,B, usando D);
      dec(C);
    }
}

// macro: teste_primo(A)

bool teste_mod(char A, char C) {
    return R[A] % R[C] == 0;
}

bool teste_primo(char A, usando char C, char D) {
    se ( zero(A) )
    entao falso
    senao {
        mov(C, A, usando D);
        dec(C);

        se ( zero(C) )
        entao verdadeiro
        senao {
            ate ( teste_mod(A,C) )
            faca dec(C);

            dec(C);

            se ( zero(C) )
            entao verdadeiro
            senao falso
        }
    }
}

// macro:  A = primo(B)
void primo(char A, char B, usando char C, char D, char E) {
    set(A, 1);
    mov(D, B, usando C);
    ate ( zero(D) ) faca {
        dec(D);
        inc(A);
        ate ( teste_primo(A, usando C, E) )
        faca inc(A);
    }
}

// macro: A = B - C
void lessBC(char A, char B, char C, usando char D, char E, char F){
  //set(C, 5);
  add(D,B,E);
  add(E,C,F);
  
  ate ( zero(E) ) faca {
      dec(E);
      dec(D);
  }
  mov(A,D, usando F);
}

// macro: B/C
void divBC(char A, char B, char C, usando char D, char E, char F){
  set(C,3);
  set0(A);
  ate( zero(B) ) faca {
    mov(D, C, F);
    inc(A);
    ate (zero(D)) faca{
      dec(D);
      dec(B);
    }
  }
  se (teste_mod(B,C)) entao dec(A);
}

// macro: fat(A)
void fatA(char Y,char A, usando char B, char C, char D, char E){

  add(E,A,C);
  add(B,E,C);
  dec(B);
  ate( zero(B) ) faca{
    mul(A,B,C,D);
    dec(E);
    set0(B);
    add(B,E,C);
    dec(B);
  }
  mov(Y,A,C);
}

// macro: pot(X,Y)
void pot(char A, char B, usando char C, char D, char E){
  set(A,3);
  add(E,A,C);
  dec(B);
  ate(zero(B)) faca {
    trace("primo");
    set0(C);
    set0(D);
    mul(A,E,C,D);
    dec(B);
  }
}

// macro: teste(A>B)
bool maiorQue( char A, char B){
  set(A,10);
  ate( zero(A) ) faca {
    dec(A);
    dec(B);
    se( zero(B)) 
    entao se(zero(A)) 
          entao falso
          senao verdadeiro;
  }
  falso
}

// macro:  teste(A>=B)
bool maiorIgualQue( char A, char B){
  set(A,10);
  ate( zero(A) ) faca {
    dec(A);
    dec(B);
    se( zero(B)) entao verdadeiro;
  }
  falso
}

// macro: teste(A<=B)
bool menorQue( char A, char B){
  set(A,10);
  ate( zero(A) ) faca {
    dec(A);
    dec(B);
    se( zero(B)) entao falso;
  }
  verdadeiro
}

//macro: minimo divisor comun A <= MDC
void mdc(char A, char B, usando char C, usando char D){
  set0(C);   set0(D);
  se(maiorQue(A, B)) entao{
    ate(zero(A)) faca {
      restoDiv(A, B, usando C, usando D);
      mov(C, A, usando D);
      mov(A, B, usando D);
      mov(B, C, usando D);
    }
    mov(A, B, usando D);
  }
    
}


// macro:  A = A%B;
void restoDiv(char A, char B, usando char C, usando char D){
  set0(C);
  set0(D);
  ate(maiorQue(B, A)) faca{
    ate(zero(B)) faca{
      dec(B);
      dec(A);
      inc(C);
    }
    mov(B, C, usando D);
    set0(C);
  }

} 

// macro: primosEntre(A,B)
void primoEntre(char A, char B, usando char C, char D, char E, char F, char G) {
    set(A, 5);
    add(D,A,E);
    lessBC(C,B,A,E,F,G);
    dec(C);
  
    ate (zero(C)) faca{
      se( teste_primo(D,F,G)) entao trace("B = ");
      inc(D);
      dec(C);
    }
}

int main() {
  ent;
  //trace("ent : N -> R");
  // programa

  primoEntre('Y','X','A','B','C','D','E');
  trace("");

  sai;
}
