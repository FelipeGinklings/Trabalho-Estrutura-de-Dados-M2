#ifndef GERENCIAMENTO_H
#define GERENCIAMENTO_H

#include "fila.h" 

// Estrutura para armazenar os dados de configuração e estado da simulação
struct DadosSimulacao {
    int qtd_guiche_socio;
    int qtd_guiche_normal;
    int carga_inicial;      
    int carga_por_turno;    
    int qtd_tempo_total;    
    int total_socios_procuraram; 
    int total_normais_procuraram; 

    // NOVOS CONTADORES PARA TEMPO DE ATENDIMENTO
    float socios_atend_1_ut;
    float socios_atend_2_ut;
    float normais_atend_1_ut;
    float normais_atend_2_ut;
    float normais_atend_3_ut;
};

// Estrutura para representar um torcedor
struct Torcedor {
    int tipo; 
    int UnidadeTempo; 
};

// Estrutura para representar um guichê
struct Guiche {
    Fila<Torcedor> fila;
};

void inicializa_Guiche(Guiche &g) {
    inicializaFila(g.fila);
}

int arredondar(float x) {
    int inteiro = (int)x;
    if ((x - (float)inteiro) >= 0.5f) {
        return inteiro + 1;
    }
    return inteiro;
}

// --- Funções adicionar_torcedor_socio e adicionar_torcedor_normal permanecem as mesmas ---
void adicionar_torcedor_socio(int qtd_ut1, int qtd_ut2, Guiche* guiches, int qtd_guiches_disponiveis) {
    if (qtd_guiches_disponiveis == 0) return; 
    for (int i = 0; i < qtd_ut1; i++) {
        Torcedor t; t.tipo = 1; t.UnidadeTempo = 1;
        int indice_menor_fila = 0;
        if (qtd_guiches_disponiveis > 1) { 
            int tamanho_menor_fila = guiches[0].fila.tamanho;
            for (int j = 1; j < qtd_guiches_disponiveis; j++) {
                if (guiches[j].fila.tamanho < tamanho_menor_fila) {
                    tamanho_menor_fila = guiches[j].fila.tamanho;
                    indice_menor_fila = j;
                }
            }
        }
        entrarNaFila(guiches[indice_menor_fila].fila, t);
    }
    for (int i = 0; i < qtd_ut2; i++) {
        Torcedor t; t.tipo = 1; t.UnidadeTempo = 2;
        int indice_menor_fila = 0;
        if (qtd_guiches_disponiveis > 1) {
            int tamanho_menor_fila = guiches[0].fila.tamanho;
            for (int j = 1; j < qtd_guiches_disponiveis; j++) {
                if (guiches[j].fila.tamanho < tamanho_menor_fila) {
                    tamanho_menor_fila = guiches[j].fila.tamanho;
                    indice_menor_fila = j;
                }
            }
        }
        entrarNaFila(guiches[indice_menor_fila].fila, t);
    }
}
void adicionar_torcedor_normal(int q_ut1, int q_ut2, int q_ut3, Guiche* guiches, int qtd_guiches_disponiveis) {
    if (qtd_guiches_disponiveis == 0) return;
    for (int i = 0; i < q_ut1; i++) {
        Torcedor t; t.tipo = 0; t.UnidadeTempo = 1;
        int indice_menor_fila = 0;
        if (qtd_guiches_disponiveis > 1) {
            int tamanho_menor_fila = guiches[0].fila.tamanho;
            for (int j = 1; j < qtd_guiches_disponiveis; j++) {
                if (guiches[j].fila.tamanho < tamanho_menor_fila) {
                    tamanho_menor_fila = guiches[j].fila.tamanho;
                    indice_menor_fila = j;
                }
            }
        }
        entrarNaFila(guiches[indice_menor_fila].fila, t);
    }
    for (int i = 0; i < q_ut2; i++) {
        Torcedor t; t.tipo = 0; t.UnidadeTempo = 2;
        int indice_menor_fila = 0;
        if (qtd_guiches_disponiveis > 1) {
            int tamanho_menor_fila = guiches[0].fila.tamanho;
            for (int j = 1; j < qtd_guiches_disponiveis; j++) {
                if (guiches[j].fila.tamanho < tamanho_menor_fila) {
                    tamanho_menor_fila = guiches[j].fila.tamanho;
                    indice_menor_fila = j;
                }
            }
        }
        entrarNaFila(guiches[indice_menor_fila].fila, t);
    }
    for (int i = 0; i < q_ut3; i++) {
        Torcedor t; t.tipo = 0; t.UnidadeTempo = 3;
        int indice_menor_fila = 0;
        if (qtd_guiches_disponiveis > 1) {
            int tamanho_menor_fila = guiches[0].fila.tamanho;
            for (int j = 1; j < qtd_guiches_disponiveis; j++) {
                if (guiches[j].fila.tamanho < tamanho_menor_fila) {
                    tamanho_menor_fila = guiches[j].fila.tamanho;
                    indice_menor_fila = j;
                }
            }
        }
        entrarNaFila(guiches[indice_menor_fila].fila, t);
    }
}
// --- Fim das funções de adicionar torcedor ---


// Modificado para receber DadosSimulacao por referência para atualizar contadores de tempo
void dividir_tempo_socios(int total_novos_socios, Guiche* guiches_socios, DadosSimulacao &dados_sim) {
    if (dados_sim.qtd_guiche_socio == 0 || total_novos_socios == 0) return;

    int socios_1_ut = arredondar(total_novos_socios * 0.85f);
    int socios_2_ut = total_novos_socios - socios_1_ut; 
    if (socios_2_ut < 0) socios_2_ut = 0; 
    
    // Atualiza contadores globais de tempo de atendimento
    dados_sim.socios_atend_1_ut += socios_1_ut;
    dados_sim.socios_atend_2_ut += socios_2_ut;
    
    adicionar_torcedor_socio(socios_1_ut, socios_2_ut, guiches_socios, dados_sim.qtd_guiche_socio);
}

// Modificado para receber DadosSimulacao por referência para atualizar contadores de tempo
void dividir_tempo_normal(int total_novos_normais, Guiche* guiches_normais, DadosSimulacao &dados_sim) {
    if (dados_sim.qtd_guiche_normal == 0 || total_novos_normais == 0) return;

    int normais_3_ut = arredondar(total_novos_normais * 0.45f);
    int normais_2_ut = arredondar(total_novos_normais * 0.30f);
    int normais_1_ut = total_novos_normais - (normais_2_ut + normais_3_ut);

    if (normais_1_ut < 0) { // Bloco de ajuste copiado da versão anterior
        normais_1_ut = 0;
        int soma_parcial = normais_2_ut + normais_3_ut;
        if (soma_parcial > total_novos_normais) {
            normais_1_ut = arredondar(total_novos_normais * 0.25f);
            normais_2_ut = arredondar(total_novos_normais * 0.30f);
            normais_3_ut = total_novos_normais - normais_1_ut - normais_2_ut;
            if (normais_3_ut < 0) { 
                normais_3_ut = 0;
                normais_1_ut = total_novos_normais - normais_2_ut;
                if (normais_1_ut < 0) {
                    normais_1_ut = 0;
                    normais_2_ut = total_novos_normais; 
                    if (normais_2_ut < 0) normais_2_ut = 0;
                }
            }
        }
    }
    
    // Atualiza contadores globais de tempo de atendimento
    dados_sim.normais_atend_1_ut += normais_1_ut;
    dados_sim.normais_atend_2_ut += normais_2_ut;
    dados_sim.normais_atend_3_ut += normais_3_ut;
    
    adicionar_torcedor_normal(normais_1_ut, normais_2_ut, normais_3_ut, guiches_normais, dados_sim.qtd_guiche_normal);
}
// --- Fim das funções de dividir tempo ---


// Distribui a nova carga de torcedores com base na disponibilidade de guichês.
void distribuir_carga_turno(int carga_do_turno, Guiche* guiches_socios, Guiche* guiches_normais,DadosSimulacao &dados_sim) {
    if (carga_do_turno <= 0) {
        return;
    }

    int socios_para_adicionar_neste_turno = 0;
    int normais_para_adicionar_neste_turno = 0;

    // CASO 1: Sem guichês de sócio, mas com guichês normais
    if (dados_sim.qtd_guiche_socio == 0 && dados_sim.qtd_guiche_normal > 0) {
        normais_para_adicionar_neste_turno = carga_do_turno;
        dados_sim.total_normais_procuraram += carga_do_turno; 
    }
    // CASO 2: Sem guichês normais, mas com guichês de sócio
    else if (dados_sim.qtd_guiche_normal == 0 && dados_sim.qtd_guiche_socio > 0) {
        socios_para_adicionar_neste_turno = carga_do_turno;
        dados_sim.total_socios_procuraram += carga_do_turno;
    }
    // CASO 3: Sem nenhum tipo de guichê
    else if (dados_sim.qtd_guiche_socio == 0 && dados_sim.qtd_guiche_normal == 0) {
        int ideal_socios_neste_turno = arredondar(carga_do_turno * 0.05f);
        int ideal_normais_neste_turno = carga_do_turno - ideal_socios_neste_turno;
        
        dados_sim.total_socios_procuraram += ideal_socios_neste_turno;
        dados_sim.total_normais_procuraram += ideal_normais_neste_turno;
        
        // Importante: Mesmo que sejam contabilizados na "procura", se não há guichês,
        // os contadores de tempo de atendimento não devem ser incrementados aqui,
        // pois eles não chegam a ter um tempo de atendimento definido para uma fila.
        // As chamadas a dividir_tempo_* abaixo cuidarão disso se houver guichês.
    }
    // CASO 4: Ambos os tipos de guichês existem
    else {
        int total_acumulado_antes_do_turno = dados_sim.total_socios_procuraram + dados_sim.total_normais_procuraram;
        int total_geral_considerando_nova_carga = total_acumulado_antes_do_turno + carga_do_turno;

        int meta_socios_acumulados = arredondar(total_geral_considerando_nova_carga * 0.05f);
        socios_para_adicionar_neste_turno = meta_socios_acumulados - dados_sim.total_socios_procuraram;

        if (socios_para_adicionar_neste_turno < 0) {
            socios_para_adicionar_neste_turno = 0;
        }
        if (socios_para_adicionar_neste_turno > carga_do_turno) {
            socios_para_adicionar_neste_turno = carga_do_turno;
        }
        normais_para_adicionar_neste_turno = carga_do_turno - socios_para_adicionar_neste_turno;

        // Atualiza os contadores globais de procura
        dados_sim.total_socios_procuraram += socios_para_adicionar_neste_turno;
        dados_sim.total_normais_procuraram += normais_para_adicionar_neste_turno;
    }

    // Efetivamente adiciona os torcedores e atualiza contadores de tempo de atendimento
    if (socios_para_adicionar_neste_turno > 0) {
        // Passa dados_sim para que os contadores de tempo sejam atualizados DENTRO de dividir_tempo_socios
        dividir_tempo_socios(socios_para_adicionar_neste_turno, guiches_socios, dados_sim);
    }
    if (normais_para_adicionar_neste_turno > 0) {
        // Passa dados_sim para que os contadores de tempo sejam atualizados DENTRO de dividir_tempo_normal
        dividir_tempo_normal(normais_para_adicionar_neste_turno, guiches_normais, dados_sim);
    }
}

#endif // GERENCIAMENTO_H
