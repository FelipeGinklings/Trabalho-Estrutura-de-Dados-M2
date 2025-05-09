#include <iostream>

#include "fila.hpp"
#include "set.hpp"

// Porcentagens de distribuição de pessoas
constexpr int PORCENTAGEM_SOCIO_TORCEDOR = 5;  // 5% das pessoas procuram guichês sócio-torcedor
constexpr int PORCENTAGEM_NORMAL = 95;  // 95% das pessoas procuram guichês normal

// Tempos de atendimento para sócio-torcedor
constexpr int PORCENTAGEM_SOCIO_TEMPO_1 = 85;  // 85% são atendidas em 1 unidade de tempo
constexpr int PORCENTAGEM_SOCIO_TEMPO_2 = 15;  // 15% são atendidas em 2 unidades de tempo

// Tempos de atendimento para normal
constexpr int PORCENTAGEM_NORMAL_TEMPO_1 = 45;  // 45% são atendidas em 3 unidades de tempo
constexpr int PORCENTAGEM_NORMAL_TEMPO_2 = 30;  // 30% são atendidas em 2 unidades de tempo
constexpr int PORCENTAGEM_NORMAL_TEMPO_3 = 25;  // 25% são atendidas em 1 unidades de tempo

struct DadosDeEntrada {
    int qtdDeGuiSocTorc, qtdDeGuiNorm, cargaInicial, qtdPorTemp, tempoSimulado;

    DadosDeEntrada(const int qtdDeGuiSocTorc, const int qtdDeGuiNorm, const int cargaInicial,
                   const int qtdPorTemp, const int tempoSimulado) :
        qtdDeGuiSocTorc(qtdDeGuiSocTorc), qtdDeGuiNorm(qtdDeGuiNorm), cargaInicial(cargaInicial),
        qtdPorTemp(qtdPorTemp), tempoSimulado(tempoSimulado) {}
};

DadosDeEntrada pedirDadosDeEntrada() {
    int qtdDeGuiSocTorc = 0, qtdDeGuiNorm = 0, cargaInicial = 0, qtdPorTemp = 0, tempoSimulado = 0;

    std::cout << "Informe a quantidade de guiches socio torcedor: ";
    std::cin >> qtdDeGuiSocTorc;

    std::cout << "Informe a quantidade de guiches normais: ";
    std::cin >> qtdDeGuiNorm;

    std::cout << "Informe a quantidade da carga inicial: ";
    std::cin >> cargaInicial;

    std::cout << "Informe a quantidade de pessoas por unidade de tempo: ";
    std::cin >> qtdPorTemp;

    std::cout << "Informe a quantidade de tempo a ser simulado: ";
    std::cin >> tempoSimulado;

    return {qtdDeGuiSocTorc, qtdDeGuiNorm, cargaInicial, qtdPorTemp, tempoSimulado};
}

struct QuantidadeTorcedores {
    int socioTorcedor, normal, socioTempo1, socioTempo2, normalTempo1, normalTempo2, normalTempo3;

    QuantidadeTorcedores(const int socioTorcedor, const int normal, const int socioTempo1,
                         const int socioTempo2, const int normalTempo1, const int normalTempo2,
                         const int normalTempo3) :
        socioTorcedor(socioTorcedor), normal(normal), socioTempo1(socioTempo1),
        socioTempo2(socioTempo2), normalTempo1(normalTempo1), normalTempo2(normalTempo2),
        normalTempo3(normalTempo3) {}
};

QuantidadeTorcedores operator-(const QuantidadeTorcedores& qtd1, const QuantidadeTorcedores& qtd2) {
    QuantidadeTorcedores resultado(0, 0, 0, 0, 0, 0, 0);
    resultado.socioTorcedor = qtd1.socioTorcedor - qtd2.socioTorcedor;
    resultado.normal = qtd1.normal - qtd2.normal;
    resultado.socioTempo1 = qtd1.socioTempo1 - qtd2.socioTempo1;
    resultado.socioTempo2 = qtd1.socioTempo2 - qtd2.socioTempo2;
    resultado.normalTempo1 = qtd1.normalTempo1 - qtd2.normalTempo1;
    resultado.normalTempo2 = qtd1.normalTempo2 - qtd2.normalTempo2;
    resultado.normalTempo3 = qtd1.normalTempo3 - qtd2.normalTempo3;
    return resultado;
}

/**
 * @brief Calcula uma quantidade distribuída com base em regras de porcentagem
 *
 * Esta função aplica regras específicas de distribuição para calcular quantos
 * itens devem ser alocados com base em uma porcentagem dada. Ela trata vários
 * casos específicos com lógica especial antes de recorrer ao cálculo padrão por
 * porcentagem.
 *
 * @param quantidade Quantidade total para distribuir
 * @param porcentagem Porcentagem a ser aplicada (0-100)
 * @return int A quantidade distribuída calculada
 *
 * @note Casos especiais tratados:
 * - Se quantidade for 0, retorna 0
 * - Se quantidade for 1, retorna 1 apenas se porcentagem ≥ 45%
 * - Se quantidade for 2 e porcentagem for 95% ou 5%, retorna 1
 * - Se quantidade for 3 e porcentagem estiver entre 25% e 45%, retorna 1
 * - Para múltiplos de 20, 25%, ou ≥85%, usa cálculo exato de porcentagem
 * - Caso especial de 30% diminui do total 45% mais 1 e 25% para pegar o valor
 * mais próximo de 25%
 * - Caso padrão adiciona 1 ao cálculo inicial de porcentagem
 *
 * @warning A função assume que porcentagem está no intervalo 0-100. Valores
 * fora desta faixa podem produzir resultados inesperados.
 * @warning Esses cálculos são considerando que as porcentagens são 5 ou 15 ou
 * 25 ou 30 ou 45 ou 85 ou 95
 */
int quantidadePorPorcentagem(const int quantidade, const int porcentagem) {
    const int porcentagemInicial = quantidade * porcentagem / 100;
    if (quantidade == 0) return 0;
    if (quantidade == 1) return porcentagem >= 45 ? 1 : 0;
    if (quantidade == 2 && (porcentagem == 95 || porcentagem == 5)) return 1;
    if (quantidade == 3 && porcentagem >= 25 && porcentagem <= 45) return 1;
    if (quantidade % 20 == 0 || porcentagem == 25 || porcentagem >= 85) return porcentagemInicial;
    if (porcentagem == 30)
        return quantidade - quantidade * 25 / 100 - (quantidade * 45 + 100) / 100;
    return porcentagemInicial + 1;
}

void adicionarQuantidadeTorcedores(QuantidadeTorcedores& qtdTorcedores, const int quantidade) {
    qtdTorcedores.socioTorcedor += quantidadePorPorcentagem(quantidade, PORCENTAGEM_SOCIO_TORCEDOR);
    qtdTorcedores.normal += quantidadePorPorcentagem(quantidade, PORCENTAGEM_NORMAL);
    qtdTorcedores.socioTempo1 +=
            quantidadePorPorcentagem(qtdTorcedores.socioTorcedor, PORCENTAGEM_SOCIO_TEMPO_1);
    qtdTorcedores.socioTempo2 +=
            quantidadePorPorcentagem(qtdTorcedores.socioTorcedor, PORCENTAGEM_SOCIO_TEMPO_2);
    qtdTorcedores.normalTempo1 +=
            quantidadePorPorcentagem(qtdTorcedores.normal, PORCENTAGEM_NORMAL_TEMPO_1);
    qtdTorcedores.normalTempo2 +=
            quantidadePorPorcentagem(qtdTorcedores.normal, PORCENTAGEM_NORMAL_TEMPO_2);
    qtdTorcedores.normalTempo3 +=
            quantidadePorPorcentagem(qtdTorcedores.normal, PORCENTAGEM_NORMAL_TEMPO_3);
}

struct Torcedor {
    bool tipo;  // Verdade para sócio e falso para normal
    int unidadesDeTempo;
    Torcedor(const bool tipo, const int unidadesDeTempo) :
        tipo(tipo), unidadesDeTempo(unidadesDeTempo) {}
    Torcedor() : tipo(false), unidadesDeTempo(0) {}
};

Torcedor operator+(const Torcedor& torcedor1, const Torcedor& torcedor2) {
    Torcedor resultado(false, 0);
    resultado.unidadesDeTempo = torcedor1.unidadesDeTempo + torcedor2.unidadesDeTempo;
    return resultado;
}

struct Guiche {
    Fila<Torcedor> fila;
    int tempoEspera;

    Guiche() : fila(), tempoEspera(0) {}
    Guiche(const Fila<Torcedor>& fila) : fila(fila), tempoEspera() {}
    Guiche(const Fila<Torcedor>& fila, const int& tempoEspera) :
        fila(fila), tempoEspera(tempoEspera) {}
};

Guiche* operator+(const Guiche*& guiche1, const Guiche*& guiche2) {
    const auto resultado = new Guiche();
    resultado->tempoEspera = guiche1->tempoEspera + guiche2->tempoEspera;
    return resultado;
}

bool operator>(const Guiche& guiche1, const Guiche& guiche2) {
    return guiche1.tempoEspera > guiche2.tempoEspera;
}

SetEncadeado<Guiche> criarGuichesIniciais(const DadosDeEntrada& dadosDeEntrada, const bool tipo) {
    const auto [qtdDeGuiSocTorc, qtdDeGuiNorm, _0, _1, _2] = dadosDeEntrada;

    QuantidadeTorcedores qtdTorcedores(0, 0, 0, 0, 0, 0, 0);
    adicionarQuantidadeTorcedores(qtdTorcedores, dadosDeEntrada.cargaInicial);

    const auto [socioTorcedor, normal, socioTempo1, socioTempo2, normalTempo1, normalTempo2,
                normalTempo3] = qtdTorcedores;


    SetEncadeado<Guiche> guichesIniciais;
    inicializarSet(guichesIniciais);
    for (int i = 0; i < (tipo ? qtdDeGuiSocTorc : 0) + qtdDeGuiNorm; i++) {
        Fila<Torcedor> fila;
        inicializaFila(fila);
        adicionarNoSet(guichesIniciais, Guiche(fila));
    }

    int tempo1 = tipo ? socioTempo1 : normalTempo1;
    int tempo2 = tipo ? socioTempo2 : normalTempo2;
    int tempo3 = tipo ? 0 : normalTempo3;

    int time = 1;

    for (int i = 0; i < (tipo ? socioTorcedor : normal); i++) {
        Guiche guiche = guichesIniciais.inicio->dado;
        entrarNaFila(guiche.fila, Torcedor(true, time));
        atualizarSet(guichesIniciais, guiche);
        guiche.tempoEspera += time;
        if (tempo1 > 0 && time == 1) {
            tempo1--;
            time = 2;
        } else if (tempo2 > 0 && time == 2) {
            tempo2--;
            time = tipo ? 1 : 3;
        } else if (tempo3 > 0 && time == 3) {
            tempo3--;
            time = 1;
        }
    }
    return guichesIniciais;
}

int main() {
    SetEncadeado<Guiche> guichesSocio =
            criarGuichesIniciais(DadosDeEntrada(4, 4, 20, 20, 30), false);

    return 0;
}
