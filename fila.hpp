//
// Created by Felipe Notebook on 28/04/2025.
//

#ifndef FILA_HPP
#define FILA_HPP

template<typename TIPO>
struct Item {
    TIPO dado;
    Item<TIPO> *prox;
};

template<typename TIPO>
struct Fila {
    Item<TIPO> *inicio;
};

template<typename TIPO>
void inicializaFila(Fila<TIPO> &f) {
    f.inicio = NULL;
}

template<typename TIPO>
void entrarNaFila(Fila<TIPO> &f, TIPO dado) {
    auto novoItem = new Item<TIPO>;
    novoItem->dado = dado;
    novoItem->prox = NULL;
    if (f.inicio == NULL) {
        f.inicio = novoItem;
    } else {
        Item<TIPO> *aux = f.inicio;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = novoItem;
    }
}

template<typename TIPO>
TIPO atender(Fila<TIPO> &f) {
    if (f.inicio != NULL) {
        Item<TIPO> *apagado = f.inicio;
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
