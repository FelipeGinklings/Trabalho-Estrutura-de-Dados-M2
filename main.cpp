#include <iostream>
#include <vector>

// Porcentagens de distribuição de pessoas
constexpr double PORCENTAGEM_SOCIO_TORCEDOR = 0.05;  // 5% das pessoas procuram guichês sócio-torcedor
constexpr double PORCENTAGEM_NORMAL = 0.95;  // 95% das pessoas procuram guichês normal

// Tempos de atendimento para sócio-torcedor
constexpr double PORCENTAGEM_SOCIO_TEMPO_1 = 0.85;  // 85% são atendidas em 1 unidade de tempo
constexpr double PORCENTAGEM_SOCIO_TEMPO_2 = 0.15;  // 15% são atendidas em 2 unidades de tempo

// Tempos de atendimento para normal
constexpr double PORCENTAGEM_NORMAL_TEMPO_1 = 0.25;  // 25% são atendidas em 1 unidades de tempo
constexpr double PORCENTAGEM_NORMAL_TEMPO_2 = 0.30;  // 30% são atendidas em 2 unidades de tempo
constexpr double PORCENTAGEM_NORMAL_TEMPO_3 = 0.45;  // 45% são atendidas em 3 unidades de tempo

struct DadosDeEntrada {
    int qtdDeGuiSocTorc, qtdDeGuiNorm, cargaInicial, qtdPorTemp, tempoSimulado;

    DadosDeEntrada(const int qtdDeGuiSocTorc, const int qtdDeGuiNorm, const int cargaInicial, const int qtdPorTemp,
                   const int tempoSimulado) :
        qtdDeGuiSocTorc(qtdDeGuiSocTorc), qtdDeGuiNorm(qtdDeGuiNorm), cargaInicial(cargaInicial),
        qtdPorTemp(qtdPorTemp), tempoSimulado(tempoSimulado) {}
};

struct Porcentagens {
    double socioTorcedorAtual;
    double normalAtual;
    double socioTempo1;
    double socioTempo2;
    double normalTempo1;
    double normalTempo2;
    double normalTempo3;

    Porcentagens() :
        socioTorcedorAtual(0), normalAtual(0), socioTempo1(0), socioTempo2(0), normalTempo1(0), normalTempo2(0),
        normalTempo3(0) {}
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

struct Torcedor {
    bool tipo;  // Verdade para sócio e falso para normal
    int unidadesDeTempo;

    Torcedor(const bool tipo, const int unidadesDeTempo) : tipo(tipo), unidadesDeTempo(unidadesDeTempo) {}
};

int criarTorcedoresIniciais(const int qtdTorc) {
    int qtdSociosInt = qtdTorc * PORCENTAGEM_SOCIO_TORCEDOR;
    int qtdTorcNor = qtdTorc * PORCENTAGEM_NORMAL;
    float qtdSociosFloat = qtdTorc * PORCENTAGEM_SOCIO_TORCEDOR;
    if (qtdSociosFloat - qtdSociosInt <= 0.5) qtdTorcNor++;

    return qtdTorcNor;
}

int main() {
    std::cout << criarTorcedoresIniciais(58) << "  " << 58 - criarTorcedoresIniciais(58);
    return 0;
}
