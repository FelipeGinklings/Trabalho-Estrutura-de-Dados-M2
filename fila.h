#ifndef FILA_H
#define FILA_H

// Removido: #include <iostream> // Não é necessário aqui, só para debug talvez

template<typename TIPO>
struct ItemFila {
    TIPO dado;
    ItemFila<TIPO> *prox;
};

template<typename TIPO>
struct Fila {
    ItemFila<TIPO> *inicio;
    ItemFila<TIPO> *fim; // Ponteiro para o último elemento para inserção O(1)
    int tamanho;
};

template<typename TIPO>
void inicializaFila(Fila<TIPO> &f) {
    f.inicio = nullptr;
    f.fim = nullptr;
    f.tamanho = 0;
}

template<typename TIPO>
void entrarNaFila(Fila<TIPO> &f, TIPO dado) {
    ItemFila<TIPO>* novoItem = new ItemFila<TIPO>;
    novoItem->dado = dado;
    novoItem->prox = nullptr;
    
    if (f.inicio == nullptr) { // Fila estava vazia
        f.inicio = novoItem;
        f.fim = novoItem;
    } else { // Fila não estava vazia
        f.fim->prox = novoItem;
        f.fim = novoItem;
    }
    f.tamanho++;
}

template<typename TIPO>
bool filaVazia(Fila<TIPO> &f) {
    return f.tamanho == 0;
}

template<typename TIPO>
TIPO atender(Fila<TIPO> &f) {
    // É responsabilidade do chamador verificar se a fila não está vazia
    // antes de chamar atender. Se f.inicio é nullptr, haverá erro.
    ItemFila<TIPO>* apagado = f.inicio;
    TIPO dadoRetorno = apagado->dado;
    f.inicio = apagado->prox;
    f.tamanho--;

    if (f.inicio == nullptr) { // Se a fila ficou vazia
        f.fim = nullptr;    // Atualizar ponteiro fim
    }
    delete apagado;
    return dadoRetorno;
}

template<typename TIPO>
TIPO primeiro(Fila<TIPO> &f) {
    // É responsabilidade do chamador verificar se a fila não está vazia.
    // Se f.inicio é nullptr, haverá erro.
    return f.inicio->dado;
}

#endif // FILA_H
