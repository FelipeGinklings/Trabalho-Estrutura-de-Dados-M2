//
// Created by Felipe Notebook on 28/04/2025.
//

#ifndef FILA_HPP
#define FILA_HPP

template<typename TIPO>
struct ItemFila {
    TIPO dado;
    ItemFila<TIPO> *prox;
};

template<typename TIPO>
struct Fila {
    ItemFila<TIPO> *inicio;
};

template<typename TIPO>
void inicializaFila(Fila<TIPO> &f) {
    f.inicio = NULL;
}

template<typename TIPO>
void entrarNaFila(Fila<TIPO> &f, TIPO dado) {
    auto novoItem = new ItemFila<TIPO>;
    novoItem->dado = dado;
    novoItem->prox = nullptr;
    if (f.inicio == nullptr) {
        f.inicio = novoItem;
    } else {
        ItemFila<TIPO> *aux = f.inicio;
        while (aux->prox != nullptr) {
        }
        aux->prox = novoItem;
    }
}


template<typename TIPO>
TIPO atender(Fila<TIPO> &f) {
    if (f.inicio != nullptr) {
        ItemFila<TIPO> *apagado = f.inicio;
        TIPO dado = apagado->dado;
        f.inicio = apagado->prox;

        delete apagado;
        return dado;
    }
}

template<typename TIPO>
TIPO primeiro(Fila<TIPO> &f) {
    if (f.inicio != NULL) {
        return f.inicio.dado;
    }
}

#endif  // FILA_HPP
