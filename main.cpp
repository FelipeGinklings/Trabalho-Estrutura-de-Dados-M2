#include <cmath>
#include <iostream>
#include <vector>

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

    DadosDeEntrada(const int qtdDeGuiSocTorc, const int qtdDeGuiNorm, const int cargaInicial, const int qtdPorTemp,
                   const int tempoSimulado) :
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
    int socioTorcedor;
    int normal;

    QuantidadeTorcedores(const int socioTorcedor, const int normal) : socioTorcedor(socioTorcedor), normal(normal) {}
};
struct QuantidadeSocioTempo {
    int socioTempo1;
    int socioTempo2;

    QuantidadeSocioTempo(const int socioTempo1, const int socioTempo2) :
        socioTempo1(socioTempo1), socioTempo2(socioTempo2) {}
};
struct QuantidadeNormalTempo {
    int normalTempo1;
    int normalTempo2;
    int normalTempo3;

    QuantidadeNormalTempo(const int normalTempo1, const int normalTempo2, const int normalTempo3) :
        normalTempo1(normalTempo1), normalTempo2(normalTempo2), normalTempo3(normalTempo3) {}
};

struct Torcedor {
    bool tipo;  // Verdade para sócio e falso para normal
    int unidadesDeTempo;
    Torcedor(const bool tipo, const int unidadesDeTempo) : tipo(tipo), unidadesDeTempo(unidadesDeTempo) {}
    Torcedor() : tipo(false), unidadesDeTempo(0) {}
};

Torcedor operator+(const Torcedor& torcedor1, const Torcedor& torcedor2) {
    Torcedor resultado(false, 0);
    resultado.unidadesDeTempo = torcedor1.unidadesDeTempo + torcedor2.unidadesDeTempo;
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
    if (porcentagem == 30) return quantidade - quantidade * 25 / 100 - (quantidade * 45 + 100) / 100;
    return porcentagemInicial + 1;
}

int main() { return 0; }
