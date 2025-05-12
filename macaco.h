#ifndef BRRBRRPATAPIM_H
#define BRRBRRPATAPIM_H
#include "fila.h"

struct Torcedor{
    int tipo;
    int UnidadeTempo;
};

struct Guiche{
    Fila<Torcedor> fila;
    int atendimento_atual; //é a UnidadeTempo do torcedor que está sendo atendido
};

void inicializa_Guiche(Guiche &guiche){
    inicializaFila(guiche.fila);
    guiche.atendimento_atual = 0;
}

void dividir_carga(int carga, int &qtd_socios, int &qtd_normais){
    float fqtd_socios = carga * 5 / 100;   //5%
    qtd_socios = fqtd_socios; //tranforma em inteiro
    
    float fqtd_normais = carga * 95 / 100; //95%
    qtd_normais = fqtd_normais; //tranforma em inteiro
    
    if(fqtd_socios - qtd_socios >= 0.5){
        qtd_socios++;
    }else{
        qtd_normais++;
    }
}

#endif  
