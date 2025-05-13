#include <iostream>
#include <vector>

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
    int socioTempo1, socioTempo2, normalTempo1, normalTempo2, normalTempo3;

    QuantidadeTorcedores(const int socioTempo1, const int socioTempo2, const int normalTempo1, const int normalTempo2,
                         const int normalTempo3) :
        socioTempo1(socioTempo1), socioTempo2(socioTempo2), normalTempo1(normalTempo1), normalTempo2(normalTempo2),
        normalTempo3(normalTempo3) {}
};
QuantidadeTorcedores operator-(const QuantidadeTorcedores& qtd1, const QuantidadeTorcedores& qtd2) {
    QuantidadeTorcedores resultado = qtd1;
    resultado.socioTempo1 -= qtd2.socioTempo1;
    resultado.socioTempo2 -= qtd2.socioTempo2;
    resultado.normalTempo1 -= qtd2.normalTempo1;
    resultado.normalTempo2 -= qtd2.normalTempo2;
    resultado.normalTempo3 -= qtd2.normalTempo3;
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
 * mais próximo de 30%
 * - Caso padrão adiciona 1 ao cálculo inicial de porcentagem
 *
 * @warning A função assume que porcentagem está no intervalo 0-100. Valores
 * fora desta faixa podem produzir resultados inesperados.
 *
 * @warning Esses cálculos são considerando que as porcentagens são 5 ou 15 ou
 * 25 ou 30 ou 45 ou 85 ou 95 porcento
 */
int quantidadePorPorcentagem(const int quantidade, const int porcentagem) {
    const int porcentagemInicial = quantidade * porcentagem / 100;

    if (quantidade == 1) return porcentagem >= 45;
    if (quantidade == 2 && (porcentagem == 85 || porcentagem == 45)) return quantidade;
    if ((quantidade == 2 && porcentagem < 95) || quantidade == 0) return 0;
    if (quantidade == 3 && porcentagem >= 25 && porcentagem <= 45) return 1;

    if (quantidade < 20 && (porcentagem == 5 || porcentagem == 95)) return porcentagem == 95 ? quantidade : 0;

    if (quantidade % 20 == 0 || porcentagem == 25 || porcentagem >= 85) return porcentagemInicial;
    if (porcentagem == 30) return quantidade - quantidade * 25 / 100 - (quantidade * 45 + 100) / 100;
    return porcentagemInicial + 1;
}

void calcularNovasQuantidades(QuantidadeTorcedores& qtdTorcedores, const int quantidade) {
    const int socioTorcedor = quantidadePorPorcentagem(quantidade, PORCENTAGEM_SOCIO_TORCEDOR);
    const int normal = quantidadePorPorcentagem(quantidade, PORCENTAGEM_NORMAL);
    qtdTorcedores.socioTempo1 = quantidadePorPorcentagem(socioTorcedor, PORCENTAGEM_SOCIO_TEMPO_1);
    qtdTorcedores.socioTempo2 = quantidadePorPorcentagem(socioTorcedor, PORCENTAGEM_SOCIO_TEMPO_2);
    qtdTorcedores.normalTempo1 = quantidadePorPorcentagem(normal, PORCENTAGEM_NORMAL_TEMPO_1);
    qtdTorcedores.normalTempo2 = quantidadePorPorcentagem(normal, PORCENTAGEM_NORMAL_TEMPO_2);
    qtdTorcedores.normalTempo3 = quantidadePorPorcentagem(normal, PORCENTAGEM_NORMAL_TEMPO_3);
}

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

struct Guiche {
    Fila<Torcedor> fila;
    int sendoAtendido;
    int torcedoresNaFila;

    Guiche() : fila(), sendoAtendido(), torcedoresNaFila() {}
    explicit Guiche(const Fila<Torcedor> fila) : fila(fila), sendoAtendido(0), torcedoresNaFila(0) {}
};
Guiche operator+(const Guiche& guiche1, const Guiche& guiche2) {
    Guiche resultado = guiche1;
    resultado.torcedoresNaFila += guiche2.torcedoresNaFila;
    return resultado;
}
bool operator>=(const Guiche& guiche1, const Guiche& guiche2) {
    return guiche1.torcedoresNaFila >= guiche2.torcedoresNaFila;
}
bool operator>(const Guiche& guiche1, const Guiche& guiche2) {
    return guiche1.torcedoresNaFila > guiche2.torcedoresNaFila;
}
bool operator<(const Guiche& guiche1, const Guiche& guiche2) {
    return guiche1.torcedoresNaFila < guiche2.torcedoresNaFila;
}
bool operator==(const Guiche& guiche1, const Guiche& guiche2) {
    return guiche1.torcedoresNaFila == guiche2.torcedoresNaFila;
}

void distribuirNosGuiches(SetEncadeado<Guiche>& guichesNormais, SetEncadeado<Guiche>& guichesSocios,
                          QuantidadeTorcedores qtdTorcedores) {
    if (guichesNormais.inicio == NULL && guichesSocios.inicio == NULL) return;
    auto& [socioTempo1, socioTempo2, normalTempo1, normalTempo2, normalTempo3] = qtdTorcedores;


    while (normalTempo1 || normalTempo2 || normalTempo3 || socioTempo1 || socioTempo2) {
        if (guichesNormais.inicio != NULL) {
            if (normalTempo1 > 0) {
                auto& fila = guichesNormais.inicio->dado.fila;
                const auto novoTorcedor = Torcedor(false, 3);
                guichesNormais.inicio->dado.torcedoresNaFila++;
                normalTempo1--;

                entrarNaFila(fila, novoTorcedor);
                atualizarSet(guichesNormais);
            }
            if (normalTempo2 > 0) {
                auto& fila = guichesNormais.inicio->dado.fila;
                const auto novoTorcedor = Torcedor(false, 2);
                guichesNormais.inicio->dado.torcedoresNaFila++;
                normalTempo2--;

                entrarNaFila(fila, novoTorcedor);
                atualizarSet(guichesNormais);
            }
            if (normalTempo3 > 0) {
                auto& fila = guichesNormais.inicio->dado.fila;
                const auto novoTorcedor = Torcedor(false, 1);
                guichesNormais.inicio->dado.torcedoresNaFila++;
                normalTempo3--;

                entrarNaFila(fila, novoTorcedor);
                atualizarSet(guichesNormais);
            }
        } else {
            normalTempo1 = normalTempo2 = normalTempo3 = 0;
        }

        if (guichesNormais.inicio != NULL && guichesSocios.inicio != NULL && (socioTempo1 || socioTempo2)) {
            const auto tempoEsperaNormal = guichesNormais.inicio->dado.torcedoresNaFila;
            const auto tempoEsperaSocio = guichesSocios.inicio->dado.torcedoresNaFila;

            if (tempoEsperaNormal < tempoEsperaSocio) {
                if (socioTempo1 > 0) {
                    auto& fila = guichesNormais.inicio->dado.fila;
                    const auto novoTorcedor = Torcedor(true, 1);
                    guichesNormais.inicio->dado.torcedoresNaFila++;
                    normalTempo3--;

                    entrarNaFila(fila, novoTorcedor);
                    atualizarSet(guichesNormais);
                }
                if (socioTempo2 > 0) {
                    auto& fila = guichesNormais.inicio->dado.fila;
                    const auto novoTorcedor = Torcedor(true, 2);
                    guichesNormais.inicio->dado.torcedoresNaFila++;
                    normalTempo3--;

                    entrarNaFila(fila, novoTorcedor);
                    atualizarSet(guichesNormais);
                }
            }
        }
        if (guichesSocios.inicio != NULL && (socioTempo1 || socioTempo2)) {
            if (socioTempo1 > 0) {
                auto& fila = guichesSocios.inicio->dado.fila;
                const auto novoTorcedor = Torcedor(true, 1);
                guichesSocios.inicio->dado.torcedoresNaFila++;
                socioTempo1--;

                entrarNaFila(fila, novoTorcedor);
                atualizarSet(guichesSocios);
            }
            if (socioTempo2 > 0) {
                auto& fila = guichesSocios.inicio->dado.fila;
                const auto novoTorcedor = Torcedor(true, 2);
                guichesSocios.inicio->dado.torcedoresNaFila++;
                socioTempo2--;

                entrarNaFila(fila, novoTorcedor);
                atualizarSet(guichesSocios);
            }
        } else if (guichesSocios.inicio == NULL) {
            socioTempo1 = socioTempo2 = 0;
        }
    }
}
QuantidadeTorcedores criarGuichesIniciais(const DadosDeEntrada& dadosDeEntrada, SetEncadeado<Guiche>& guichesNormais,
                                          SetEncadeado<Guiche>& guichesSocios) {
    int guichesNormal = dadosDeEntrada.qtdDeGuiNorm;
    while (guichesNormal) {
        guichesNormal--;
        Fila<Torcedor> filaNormal{};
        inicializaFila(filaNormal);
        const auto guicheNormal = Guiche(filaNormal);
        adicionarNoSet(guichesNormais, guicheNormal);
    }
    int guichesSocio = dadosDeEntrada.qtdDeGuiSocTorc;
    while (guichesSocio) {
        guichesSocio--;
        Fila<Torcedor> filaSocio{};
        inicializaFila(filaSocio);
        const auto guicheSocio = Guiche(filaSocio);
        adicionarNoSet(guichesSocios, guicheSocio);
    }
    QuantidadeTorcedores torcedoresIniciais = {0, 0, 0, 0, 0};
    calcularNovasQuantidades(torcedoresIniciais, dadosDeEntrada.cargaInicial);
    return torcedoresIniciais;
}

QuantidadeTorcedores novosTorcedores(const DadosDeEntrada& dadosDeEntrada, QuantidadeTorcedores& qtdTorcedoresAtuais,
                                     const int turno) {
    QuantidadeTorcedores novosTorcedores = {0, 0, 0, 0, 0};
    const int quantidadeAtualTorcedores = dadosDeEntrada.cargaInicial + dadosDeEntrada.qtdPorTemp * turno;
    calcularNovasQuantidades(qtdTorcedoresAtuais, quantidadeAtualTorcedores);
    calcularNovasQuantidades(novosTorcedores, quantidadeAtualTorcedores - dadosDeEntrada.qtdPorTemp);
    novosTorcedores = qtdTorcedoresAtuais - novosTorcedores;
    return novosTorcedores;
}

void colocarParaSerAtendido(SetEncadeado<Guiche>& guichesNormais, SetEncadeado<Guiche>& guichesSocios) {
    auto atual = guichesNormais.inicio;
    if (atual != NULL && guichesNormais.fim->dado.torcedoresNaFila) {
        do {  // Coloca em atendimento
            auto& fila = atual->dado.fila;
            if (!atual->dado.sendoAtendido && fila.inicio != NULL) {
                const Torcedor torcedor = atender(fila);
                atual->dado.sendoAtendido = torcedor.unidadesDeTempo;
            }
            atual = atual->proximo;
        } while (atual != guichesNormais.inicio);
    }
    atual = guichesSocios.inicio;
    if (atual != NULL && guichesSocios.fim->dado.torcedoresNaFila) {
        do {  // Coloca em atendimento
            auto& fila = atual->dado.fila;
            if (!atual->dado.sendoAtendido && fila.inicio != NULL) {
                const Torcedor torcedor = atender(fila);
                atual->dado.sendoAtendido = torcedor.unidadesDeTempo;
            }
            atual = atual->proximo;
        } while (atual != guichesSocios.inicio);
    }
}

void umTurnoAtendimento(SetEncadeado<Guiche>& guichesNormais, SetEncadeado<Guiche>& guichesSocios) {
    auto atual = guichesNormais.inicio;
    if (atual != NULL) {
        do {  // Coloca em atendimento
            if (atual->dado.sendoAtendido) atual->dado.sendoAtendido--;
            if (!atual->dado.sendoAtendido && atual->dado.torcedoresNaFila) {
                atual->dado.torcedoresNaFila--;
                atualizarSet(guichesNormais, atual);
            }
            atual = atual->proximo;
        } while (atual != guichesNormais.inicio);
    }
    atual = guichesSocios.inicio;
    if (atual != NULL) {
        do {  // Coloca em atendimento
            if (atual->dado.sendoAtendido) atual->dado.sendoAtendido--;
            if (!atual->dado.sendoAtendido && atual->dado.torcedoresNaFila) {
                atual->dado.torcedoresNaFila--;
                atualizarSet(guichesSocios, atual);
            }
            atual = atual->proximo;
        } while (atual != guichesSocios.inicio);
    }
}

int adicionarAoTotal(const SetEncadeado<Guiche>& guichesNormais, const SetEncadeado<Guiche>& guichesSocios) {
    int total = 0;
    auto atual = guichesNormais.fim;
    if (atual != NULL) {
        do {
            // total += atual->dado.torcedoresNaFila + (atual->dado.sendoAtendido ? -1 : 0);
            auto torcedorAtual = atual->dado.fila.inicio;
            while (torcedorAtual != NULL) {
                total += 1;
                torcedorAtual = torcedorAtual->prox;
            }
            atual = atual->anterior;
            if (!atual->dado.torcedoresNaFila) atual = guichesNormais.fim;
        } while (atual != guichesNormais.fim);
    }
    atual = guichesSocios.fim;
    if (atual != NULL) {
        do {
            total += atual->dado.torcedoresNaFila;
            atual = atual->anterior;
            if (!atual->dado.torcedoresNaFila) atual = guichesSocios.fim;
        } while (atual != guichesSocios.fim);
    }
    return total;
}

void print(const SetEncadeado<Guiche> guiches, const bool tipo) {
    auto atual = guiches.inicio;
    if (atual == NULL) return;
    do {
        for (int i = 0; i < 4; i++) {
            auto torcedorAtual = atual->dado.fila.inicio;
            if (i == 0 || i == 2)
                std::cout << "|               " << "|               ";
            else if (i == 1)
                std::cout << (tipo ? "| Guiche Socio  " : "| Guiche Normal ") << "| Em Atendido "
                          << atual->dado.sendoAtendido << " ";
            int posicao = 0;
            while (torcedorAtual != NULL) {
                posicao++;
                if (i == 0)
                    std::cout << "|       " << posicao << (posicao > 9 ? "      " : "       ");
                else if (i == 1)
                    std::cout << "|  Socio: " << (torcedorAtual->dado.tipo ? "Sim" : "Nao") << "   ";
                else if (i == 2)
                    std::cout << "|  Tempo: " << torcedorAtual->dado.unidadesDeTempo << "     ";
                else if (i == 3)
                    if (torcedorAtual->prox == NULL) {
                        std::cout << "|---------------|---------------|";
                        std::cout << "---------------|";
                    } else
                        std::cout << "|---------------";

                torcedorAtual = torcedorAtual->prox;
            }
            std::cout << std::endl;
        }
        atual = atual->proximo;
    } while (guiches.inicio != atual);
}

int programaPrincipal(DadosDeEntrada dadosDeEntrada) {
    if (!dadosDeEntrada.qtdDeGuiNorm && !dadosDeEntrada.qtdDeGuiSocTorc) {
        return 0;
    }
    SetEncadeado<Guiche> guichesNormais{};
    SetEncadeado<Guiche> guichesSocios{};

    inicializarSet(guichesNormais);
    inicializarSet(guichesSocios);

    criarGuichesIniciais(dadosDeEntrada, guichesNormais, guichesSocios);

    QuantidadeTorcedores quantidadeDeTorcedoresAtuais = {0, 0, 0, 0, 0};
    if (dadosDeEntrada.cargaInicial) {
        calcularNovasQuantidades(quantidadeDeTorcedoresAtuais, dadosDeEntrada.cargaInicial);
        distribuirNosGuiches(guichesNormais, guichesSocios, quantidadeDeTorcedoresAtuais);
    }

    int turnos = dadosDeEntrada.tempoSimulado;
    int totalEsperando = 0;
    int totalTurnos = 0;
    while (turnos && (dadosDeEntrada.cargaInicial || dadosDeEntrada.qtdPorTemp)) {
        totalTurnos++;
        turnos--;

        // std::cout << std::string(150, '\n');
        print(guichesSocios, true);
        print(guichesNormais, false);
        std::cout << "Pressione Enter para continuar..." << std::endl;
        std::cin.get();

        const int adicionarNoTotal = adicionarAoTotal(guichesNormais, guichesSocios);
        totalEsperando += adicionarNoTotal;
        std::cout << adicionarNoTotal << std::endl;
        if (!adicionarNoTotal && totalEsperando > 0) {
            totalTurnos--;
        }

        colocarParaSerAtendido(guichesNormais, guichesSocios);

        if (turnos + 1 != dadosDeEntrada.tempoSimulado) {
            umTurnoAtendimento(guichesNormais, guichesSocios);
        }

        if (dadosDeEntrada.qtdPorTemp) {
            const auto quantidadeNovaDeTorcedores = novosTorcedores(dadosDeEntrada, quantidadeDeTorcedoresAtuais,
                                                                    dadosDeEntrada.tempoSimulado - turnos);
            distribuirNosGuiches(guichesNormais, guichesSocios, quantidadeNovaDeTorcedores);
        }

        if (dadosDeEntrada.qtdDeGuiNorm && !dadosDeEntrada.qtdPorTemp) {
            if (!guichesNormais.fim->dado.torcedoresNaFila && !guichesNormais.fim->dado.sendoAtendido) {
                turnos = 0;
            }
        } else if (dadosDeEntrada.qtdDeGuiSocTorc && !dadosDeEntrada.qtdPorTemp) {
            if (!guichesSocios.fim->dado.torcedoresNaFila && !guichesSocios.fim->dado.sendoAtendido) {
                turnos = 0;
            }
        }
    }
    totalEsperando += adicionarAoTotal(guichesNormais, guichesSocios);
    std::cout << std::string(150, '\n');
    std::cout << "Total Esperando: " << totalEsperando << "\nTotal Turnos: " << totalTurnos << std::endl;
    std::cout << "Resultado: " << static_cast<float>(totalEsperando) / totalTurnos << std::endl;
    std::cout << "Pressione Enter para continuar..." << std::endl;
    std::cin.get();

    return 0;
}

std::vector<int> numeroParaBinario(int numero) {
    std::vector binario(5, 0);  // vetor com 5 posições, todas iniciadas com 0

    for (int i = 4; i >= 0; --i) {
        binario[4 - i] = numero >> i & 1;  // extrai o bit da posição i
    }

    return binario;
}

int main() {
    // Verifca todas as possibilidades zeradas
    // for (int i = 0; i < 32; i++) {
    //     auto nParaBin = numeroParaBinario(i);
    //     const auto dadosDeEntrada = DadosDeEntrada(nParaBin[0], nParaBin[1], nParaBin[2], nParaBin[3], nParaBin[4]);
    // }
    // const auto dadosDeEntrada = DadosDeEntrada(1, 4, 10, 0, 12);
    const auto dadosDeEntrada = pedirDadosDeEntrada();
    std::cout << programaPrincipal(dadosDeEntrada) << std::endl;
    return 0;
}
