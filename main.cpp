#include <iostream>
#include "gerenciamento.h" 

using namespace std;

const int MAX_IGNORE_CHARS = 10000; 

void simular_atendimento_guiches(Guiche* guiches, int qtd_guiches) {
    if (qtd_guiches == 0) return;
    for (int i = 0; i < qtd_guiches; i++) {
        if (!filaVazia(guiches[i].fila)) {
            Torcedor &torcedor_atendido = guiches[i].fila.inicio->dado; 
            torcedor_atendido.UnidadeTempo--;
            if (torcedor_atendido.UnidadeTempo == 0) {
                atender(guiches[i].fila); 
            }
        }
    }
}

void exibir_estado_filas(Guiche* guiches, int qtd_guiches, string tipo_guiche_label) {
    cout << "\n--- Filas " << tipo_guiche_label << " --- \n";
    if (qtd_guiches == 0) {
        cout << "Nenhum guiche deste tipo.\n";
        return;
    }
    for (int i = 0; i < qtd_guiches; i++) {
        cout << "Guiche " << (i + 1) << " (" << guiches[i].fila.tamanho << " na fila): ";
        ItemFila<Torcedor>* atual = guiches[i].fila.inicio;
        while (atual != nullptr) {
            cout << "[" << (atual->dado.tipo ? "S" : "N") << "," << atual->dado.UnidadeTempo << "] ";
            atual = atual->prox;
        }
        cout << "\n";
    }
}

// Função auxiliar para calcular e imprimir porcentagem
void imprimir_porcentagem(float parte, float total, string label) {
    if (total > 0) {
        float perc = parte / total * 100;
        cout << label << parte << " (" << perc << "%)";
    } else {
        cout << label << parte << " (N/A)";
    }
}


int main() {
    DadosSimulacao dados; 
    // Inicializa TODOS os campos da struct, incluindo os novos contadores
    dados.total_socios_procuraram = 0;
    dados.total_normais_procuraram = 0;
    dados.socios_atend_1_ut = 0;
    dados.socios_atend_2_ut = 0;
    dados.normais_atend_1_ut = 0;
    dados.normais_atend_2_ut = 0;
    dados.normais_atend_3_ut = 0;

    /*
    cout << "--- Configuracao da Simulacao ---\n";
    cout << "Quantidade de guiches socio-torcedor: ";
    cin >> dados.qtd_guiche_socio;
    cout << "Quantidade de guiches normais: ";
    cin >> dados.qtd_guiche_normal;
    cout << "Quantidade de pessoas aguardando (carga inicial): ";
    cin >> dados.carga_inicial;
    cout << "Quantidade de pessoas que procuram guiches a cada unidade de tempo: ";
    cin >> dados.carga_por_turno;
    cout << "Quantidade de tempo (unidades) para simular: ";
    cin >> dados.qtd_tempo_total;
   */
    
    dados.qtd_guiche_socio=2;
    dados.qtd_guiche_normal=8;
    dados.carga_inicial=100;
    dados.carga_por_turno=1;
    dados.qtd_tempo_total=10;

    Guiche* guichesSocios = nullptr;
    if (dados.qtd_guiche_socio > 0) {
        guichesSocios = new Guiche[dados.qtd_guiche_socio];
        for (int i = 0; i < dados.qtd_guiche_socio; i++) {
            inicializa_Guiche(guichesSocios[i]);
        }
    }

    Guiche* guichesNormais = nullptr;
    if (dados.qtd_guiche_normal > 0) {
        guichesNormais = new Guiche[dados.qtd_guiche_normal];
        for (int i = 0; i < dados.qtd_guiche_normal; i++) {
            inicializa_Guiche(guichesNormais[i]);
        }
    }

    if (dados.carga_inicial > 0) {
        cout << "\nProcessando carga inicial de " << dados.carga_inicial << " torcedores...\n";
        distribuir_carga_turno(dados.carga_inicial, guichesSocios, guichesNormais, dados);
    }
    
    exibir_estado_filas(guichesSocios, dados.qtd_guiche_socio, "Socio-Torcedor");
    exibir_estado_filas(guichesNormais, dados.qtd_guiche_normal, "Normal");

    for (int tempo_atual = 1; tempo_atual <= dados.qtd_tempo_total; tempo_atual++) {
        if(tempo_atual==1){
            // Consome o \n deixado pelos cin >>
            // Você pode usar cin.ignore(MAX_IGNORE_CHARS, '\n'); para mais robustez
            // ou um simples cin.ignore() se só houver o \n.
            // Se o seu cin.ignore() dentro do loop já estiver funcionando, talvez não precise deste.
            // Teste para ver o que funciona melhor com sua forma de usar o Enter.
             char ch; // Para consumir um caracter do buffer, esperando o enter
             ch = cin.get(); // ou cin.ignore();
             if (ch != '\n' && ch != EOF) { // Se não foi newline, e não fim do arquivo
                 // Pode ser que algo mais estivesse no buffer, limpar até o \n
                 cin.ignore(MAX_IGNORE_CHARS, '\n');
             }
        }
        cout << "\n\n--- Tempo: " << tempo_atual << " --- (Pressione ENTER para continuar)";
         cin.ignore();


        if (dados.carga_por_turno > 0) {
            cout << "Novas chegadas (" << dados.carga_por_turno << " torcedores)...\n";
            distribuir_carga_turno(dados.carga_por_turno, guichesSocios, guichesNormais, dados);
        }

        simular_atendimento_guiches(guichesSocios, dados.qtd_guiche_socio);
        simular_atendimento_guiches(guichesNormais, dados.qtd_guiche_normal);

        cout << "\n--- Estatisticas do Turno " << tempo_atual << " ---\n";
        
        int total_direcionados_geral = dados.total_socios_procuraram + dados.total_normais_procuraram;
        if (total_direcionados_geral > 0) {
            double perc_socios_direcionados = (double)dados.total_socios_procuraram / total_direcionados_geral * 100.0;
            double perc_normais_direcionados = (double)dados.total_normais_procuraram / total_direcionados_geral * 100.0;
            
            cout << "Proporcao de Torcedores Direcionados (Acumulada): Socios " << perc_socios_direcionados << "% (" << dados.total_socios_procuraram << "), "
            << "Normais " << perc_normais_direcionados << "% (" << dados.total_normais_procuraram << ")\n";
        } else {
            cout << "Nenhum torcedor direcionado aos guiches ate o momento.\n";
        }

        // Exibir Ocupação dos Guichês (como antes)
        // ... (código de ocupação dos guichês omitido para brevidade, mas deve ser mantido) ...
        int guiches_ocupados_socios = 0;
        if (dados.qtd_guiche_socio > 0) {
            for (int i = 0; i < dados.qtd_guiche_socio; i++) {
                if (!filaVazia(guichesSocios[i].fila)) guiches_ocupados_socios++;
            }
            int perc_ocup_socios = guiches_ocupados_socios / dados.qtd_guiche_socio * 100.0;
            cout << "Ocupacao Guiches Socios: " << perc_ocup_socios << "% (" 
                 << guiches_ocupados_socios << "/" << dados.qtd_guiche_socio << ")\n";
        }
        
        int guiches_ocupados_normais = 0;
        if (dados.qtd_guiche_normal > 0) {
            for (int i = 0; i < dados.qtd_guiche_normal; i++) {
                if (!filaVazia(guichesNormais[i].fila)) guiches_ocupados_normais++;
            }
            int perc_ocup_normais = guiches_ocupados_normais / dados.qtd_guiche_normal * 100.0;
            cout << "Ocupacao Guiches Normais: " << perc_ocup_normais << "% ("<< guiches_ocupados_normais << "/" << dados.qtd_guiche_normal << ")\n";
        }

        // Exibir distribuição de tempo de atendimento A CADA TURNO (opcional, pode poluir)
        // Se preferir, mova para o final da simulação
        cout << "Distribuicao de Tempo de Atendimento (Acumulado):\n";
        float total_socios_com_tempo_definido = dados.socios_atend_1_ut + dados.socios_atend_2_ut;
        if (total_socios_com_tempo_definido > 0) {
            cout << "  Socios:\n";
            imprimir_porcentagem(dados.socios_atend_1_ut, total_socios_com_tempo_definido, "    - 1 UT: ");
            cout << " | ";
            imprimir_porcentagem(dados.socios_atend_2_ut, total_socios_com_tempo_definido, "2 UT: ");
            cout << "\n";
        }
        float total_normais_com_tempo_definido = dados.normais_atend_1_ut + dados.normais_atend_2_ut + dados.normais_atend_3_ut;
        if (total_normais_com_tempo_definido > 0) {
            cout << "  Normais:\n";
            imprimir_porcentagem(dados.normais_atend_1_ut, total_normais_com_tempo_definido, "    - 1 UT: ");
            cout << " | ";
            imprimir_porcentagem(dados.normais_atend_2_ut, total_normais_com_tempo_definido, "2 UT: ");
            cout << " | ";
            imprimir_porcentagem(dados.normais_atend_3_ut, total_normais_com_tempo_definido, "3 UT: ");
            cout << "\n";
        }
        
        exibir_estado_filas(guichesSocios, dados.qtd_guiche_socio, "Socio-Torcedor");
        exibir_estado_filas(guichesNormais, dados.qtd_guiche_normal, "Normal");
    }

    cout << "\n\n--- Fim da Simulacao ---";
    
    // Exibir Resumo Final da Distribuição de Tempos de Atendimento
    cout << "\nResumo Final da Distribuicao de Tempo de Atendimento (Total de Torcedores com Tempo Definido):\n";
    float final_total_socios_com_tempo = dados.socios_atend_1_ut + dados.socios_atend_2_ut;
    if (final_total_socios_com_tempo > 0) {
        cout << "  Socios (Total: " << final_total_socios_com_tempo << "):\n";
        imprimir_porcentagem(dados.socios_atend_1_ut, final_total_socios_com_tempo, "    - 1 UT: ");
        cout << " | ";
        imprimir_porcentagem(dados.socios_atend_2_ut, final_total_socios_com_tempo, "2 UT: ");
        cout << "\n";
    } else {
        cout << "  Nenhum socio com tempo de atendimento definido.\n";
    }

    float final_total_normais_com_tempo = dados.normais_atend_1_ut + dados.normais_atend_2_ut + dados.normais_atend_3_ut;
    if (final_total_normais_com_tempo > 0) {
        cout << "  Normais (Total: " << final_total_normais_com_tempo << "):\n";
        imprimir_porcentagem(dados.normais_atend_1_ut, final_total_normais_com_tempo, "    - 1 UT: ");
        cout << " | ";
        imprimir_porcentagem(dados.normais_atend_2_ut, final_total_normais_com_tempo, "2 UT: ");
        cout << " | ";
        imprimir_porcentagem(dados.normais_atend_3_ut, final_total_normais_com_tempo, "3 UT: ");
        cout << "\n";
    } else {
        cout << "  Nenhum torcedor normal com tempo de atendimento definido.\n";
    }
    

    float total_torcedores_restantes_nas_filas = 0; 
    int total_guiches_ativos = 0;

    if (guichesSocios) { 
        for (int i = 0; i < dados.qtd_guiche_socio; i++) {
            total_torcedores_restantes_nas_filas += guichesSocios[i].fila.tamanho;
        }
        total_guiches_ativos += dados.qtd_guiche_socio;
    }
    if (guichesNormais) { 
        for (int i = 0; i < dados.qtd_guiche_normal; i++) {
            total_torcedores_restantes_nas_filas += guichesNormais[i].fila.tamanho;
        }
        total_guiches_ativos += dados.qtd_guiche_normal;
    }

    cout << "\nTorcedores restantes nas filas: " << total_torcedores_restantes_nas_filas << endl;

    if (total_guiches_ativos > 0) {
        float media_torcedores_por_fila = total_torcedores_restantes_nas_filas / total_guiches_ativos;
        cout << "Media de torcedores por fila ao final: " << media_torcedores_por_fila << endl;
    } else {
        cout << "Nenhum guiche esteve ativo para calcular media.\n";
    }

    if (guichesSocios){
        delete[] guichesSocios;
    }
    if (guichesNormais){
        delete[] guichesNormais;
    }

    cout << "\nSimulacao concluida. Pressione ENTER para sair.";
    // Limpeza final do buffer antes de sair
    cin.ignore();
    // Se quiser uma pausa final absoluta:
    // cin.get(); 

    return 0;
}
