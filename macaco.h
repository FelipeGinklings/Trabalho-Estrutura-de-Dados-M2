#ifndef MACACO_H
#define MACACO_H
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

//ADICIONA OS SOCIOS NAS MENORES FILAS
void adicionar_torcedor_socio(int qtd_1un, int qtd_2un, Guiche* guichesSocios, int qtd_guiche_socio){
    // Adiciona sócios com 1 unidade de tempo
    for (int i = 0; i < qtd_1un; i++) {
        Torcedor t;
        t.tipo = 1; // 1 = sócio
        t.UnidadeTempo = 1;
        
        // Encontra o guichê de sócio com menor fila
        int menor_fila = 0;
        int tamanho_menor = 0;
        ItemFila<Torcedor>* aux = guichesSocios[0].fila.inicio;
        while(aux != nullptr) {
            tamanho_menor++;
            aux = aux->prox;
        }
        
        for (int g = 1; g < qtd_guiche_socio; g++) {
            int tamanho_atual = 0;
            aux = guichesSocios[g].fila.inicio;
            while(aux != nullptr) {
                tamanho_atual++;
                aux = aux->prox;
            }
            
            if (tamanho_atual < tamanho_menor) {
                menor_fila = g;
                tamanho_menor = tamanho_atual;
            }
        }
        
        entrarNaFila(guichesSocios[menor_fila].fila, t);
    }
    
    // Adiciona sócios com 2 unidades de tempo
    for (int i = 0; i < qtd_2un; i++) {
        Torcedor t;
        t.tipo = 1; // 1 = sócio
        t.UnidadeTempo = 2;
        
        // Encontra o guichê de sócio com menor fila (mesma lógica acima)
        int menor_fila = 0;
        int tamanho_menor = 0;
        ItemFila<Torcedor>* aux = guichesSocios[0].fila.inicio;
        while(aux != nullptr) {
            tamanho_menor++;
            aux = aux->prox;
        }
        
        for (int g = 1; g < qtd_guiche_socio; g++) {
            int tamanho_atual = 0;
            aux = guichesSocios[g].fila.inicio;
            while(aux != nullptr) {
                tamanho_atual++;
                aux = aux->prox;
            }
            
            if (tamanho_atual < tamanho_menor) {
                menor_fila = g;
                tamanho_menor = tamanho_atual;
            }
        }
        
        entrarNaFila(guichesSocios[menor_fila].fila, t);
    }
}

//DIVIDE O TEMPO DE ATENDIMENTO ENTRE OS SOCIOS PARA ENTÃO ADICIONA-LOS NA FILA CERTA!
void dividir_tempo_socios(int qtd_socios, Guiche* guichesSocios, int qtd_guiche_socio){
    float fqtd_1un = qtd_socios * 15 / 100;   //5%
    int qtd_1un = fqtd_1un; //tranforma em inteiro
    
    float fqtd_2un = qtd_socios * 85 / 100; //95%
    int qtd_2un = fqtd_1un; //tranforma em inteiro
    
    if(fqtd_1un - qtd_1un >= 0.5){
        qtd_1un++;
    }else{
        qtd_1un++;
    }
    
    adicionar_torcedor_socio(qtd_1un, qtd_2un, guichesSocios, qtd_guiche_socio);
}

//ADICIONA OS SOCIOS NAS MENORES FILAS
void adicionar_torcedor_normal(int qtd_1un, int qtd_2un, int qtd_3un, Guiche* guichesNormais, int qtd_guiche_normal) {
    // Adiciona normais com 1 unidade de tempo
    for (int i = 0; i < qtd_1un; i++) {
        Torcedor t;
        t.tipo = 0; // 0 = normal
        t.UnidadeTempo = 1;
        
        // Encontra o guichê normal com menor fila
        int menor_fila = 0;
        int tamanho_menor = 0;
        ItemFila<Torcedor>* aux = guichesNormais[0].fila.inicio;
        while(aux != nullptr) {
            tamanho_menor++;
            aux = aux->prox;
        }
        
        for (int g = 1; g < qtd_guiche_normal; g++) {
            int tamanho_atual = 0;
            aux = guichesNormais[g].fila.inicio;
            while(aux != nullptr) {
                tamanho_atual++;
                aux = aux->prox;
            }
            
            if (tamanho_atual < tamanho_menor) {
                menor_fila = g;
                tamanho_menor = tamanho_atual;
            }
        }
        
        entrarNaFila(guichesNormais[menor_fila].fila, t);
    }
    
    // Adiciona normais com 2 unidades de tempo
    for (int i = 0; i < qtd_2un; i++) {
        Torcedor t;
        t.tipo = 0;
        t.UnidadeTempo = 2;
        
        // Mesma lógica para encontrar guichê com menor fila
        int menor_fila = 0;
        int tamanho_menor = 0;
        ItemFila<Torcedor>* aux = guichesNormais[0].fila.inicio;
        while(aux != nullptr) {
            tamanho_menor++;
            aux = aux->prox;
        }
        
        for (int g = 1; g < qtd_guiche_normal; g++) {
            int tamanho_atual = 0;
            aux = guichesNormais[g].fila.inicio;
            while(aux != nullptr) {
                tamanho_atual++;
                aux = aux->prox;
            }
            
            if (tamanho_atual < tamanho_menor) {
                menor_fila = g;
                tamanho_menor = tamanho_atual;
            }
        }
        
        entrarNaFila(guichesNormais[menor_fila].fila, t);
    }
    
    // Adiciona normais com 3 unidades de tempo
    for (int i = 0; i < qtd_3un; i++) {
        Torcedor t;
        t.tipo = 0;
        t.UnidadeTempo = 3;
        
        // Mesma lógica para encontrar guichê com menor fila
        int menor_fila = 0;
        int tamanho_menor = 0;
        ItemFila<Torcedor>* aux = guichesNormais[0].fila.inicio;
        while(aux != nullptr) {
            tamanho_menor++;
            aux = aux->prox;
        }
        
        for (int g = 1; g < qtd_guiche_normal; g++) {
            int tamanho_atual = 0;
            aux = guichesNormais[g].fila.inicio;
            while(aux != nullptr) {
                tamanho_atual++;
                aux = aux->prox;
            }
            
            if (tamanho_atual < tamanho_menor) {
                menor_fila = g;
                tamanho_menor = tamanho_atual;
            }
        }
        
        entrarNaFila(guichesNormais[menor_fila].fila, t);
    }
}

//DIVIDE O TEMPO DE ATENDIMENTO ENTRE OS NORMAIS PARA ENTÃO ADICIONA-LOS NA FILA CERTA!
void dividir_tempo_normal(int qtd_normais, Guiche* guichesNormais, int qtd_guiche_normal){
    float fqtd_3un = qtd_normais * 45 / 100;   //45%
    int qtd_3un = fqtd_3un; //tranforma em inteiro
    
    float fqtd_2un = qtd_normais * 30 / 100; //30%
    int qtd_2un = fqtd_2un; //tranforma em inteiro
    
    if(fqtd_2un - qtd_2un >= 0.5){
        qtd_2un++;
    }else{
        qtd_3un++;
    }
    
    int qtd_1un = qtd_normais - (qtd_3un + qtd_2un); //o resto da carga de torcedores
    
    adicionar_torcedor_normal(qtd_1un, qtd_2un, qtd_3un, guichesNormais, qtd_guiche_normal);
}

//PEGA A CARGA POR TURNO E DIVIDE ENTRE SOCIO E NORMAL
void dividir_carga(int carga, Guiche* guichesSocios, Guiche* guichesNormais, int qtd_guiche_socio, int qtd_guiche_normal){ 
    float fqtd_socios = carga * 5 / 100;   //5%
    int qtd_socios = fqtd_socios; //tranforma em inteiro
    
    float fqtd_normais = carga * 95 / 100; //95%
    int qtd_normais = fqtd_normais; //tranforma em inteiro
    
    if(fqtd_socios - qtd_socios >= 0.5){
        qtd_socios++;
    }else{
        qtd_normais++;
    }
    
    dividir_tempo_socios(qtd_socios, guichesSocios, qtd_guiche_socio);
    //dividir_tempo_normal(qtd_normais);
}

#endif  
