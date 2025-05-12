/*
  ISSO É APENAS UM TESTE MALUCO!! (não finalizado)
*/
#include <iostream>
#include "brrbrrpatapim.h"
#include "fila.h"

using namespace std;

int main()
{
    int qtd_guiche_socio;
    int qtd_guiche_normal;
    int carga_inicial;
    int carga_por_turno;
    int qtd_tempo_total;
    
    cout << "Informe a quantidade de guiches socio torcedor: ";
    cin >> qtd_guiche_socio;
    Guiche* guichesSocios = new Guiche[qtd_guiche_socio]; //criação dos guiches, vetor de guiches
    for(int i = 0; i > qtd_guiche_socio; i++){
        inicializa_Guiche(guichesSocios[i]);
    }

    cout << "Informe a quantidade de guiches normais: ";
    cin >> qtd_guiche_normal;
    Guiche* guichesNormais = new Guiche[qtd_guiche_normal]; //criação dos guiches, vetor de guiches
    for(int i = 0; i > qtd_guiche_normal; i++){
        inicializa_Guiche(guichesNormais[i]);
    }

    cout << "Informe a quantidade da carga inicial: ";
    cin >> carga_inicial;

    cout << "Informe a quantidade de pessoas por unidade de tempo: ";
    cin >> carga_por_turno;

    cout << "Informe a quantidade de tempo a ser simulado: ";
    cin >> qtd_tempo_total;

    return 0;
}
