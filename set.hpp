#ifndef SET_H_INCLUDED
#define SET_H_INCLUDED

template<typename Tipo>
struct Item {
    Tipo dado;
    Item<Tipo> *proximo, *anterior;
};

template<typename Tipo>
struct SetEncadeado {
    Item<Tipo> *inicio;
    Item<Tipo> *fim;
};

template<typename Tipo>
void inicializarSet(SetEncadeado<Tipo> &setEncadeadado) {
    setEncadeadado.inicio = NULL;
    setEncadeadado.fim = NULL;
}

template<typename Tipo>
bool adicionarNoSet(SetEncadeado<Tipo> &setEncadeado, Tipo item) {
    auto *novoItem = new Item<Tipo>;
    novoItem->dado = item;

    if (setEncadeado.fim == NULL || setEncadeado.inicio == NULL) {
        novoItem->anterior = novoItem;
        novoItem->proximo = novoItem;
        setEncadeado.inicio = novoItem;
        setEncadeado.fim = novoItem;
        return true;
    }

    novoItem->proximo = setEncadeado.inicio;  // Aponta para o antigo inicio
    novoItem->anterior = setEncadeado.fim;  // O anterior aponta para o fim
    setEncadeado.inicio->anterior = novoItem;  // O início aponta para o novo ‘item’
    setEncadeado.fim->proximo = novoItem;  // O próximo do fim aponta para o início
    setEncadeado.inicio = novoItem;  // Atualiza o inicio
    return true;
}

template<typename Tipo>
bool atualizarSet(SetEncadeado<Tipo> &setEncadeado, Tipo novoDado) {
    if (setEncadeado.inicio == NULL || setEncadeado.inicio == setEncadeado.fim) {
        return false;
    }

    if (setEncadeado.fim->proximo != setEncadeado.inicio ||
        setEncadeado.inicio->anterior != setEncadeado.fim) {
        return false;
    }

    Item<Tipo> *antigoInicio = setEncadeado.inicio;
    antigoInicio->dado = antigoInicio->dado + novoDado;
    setEncadeado.inicio = antigoInicio->proximo;
    setEncadeado.inicio->anterior = setEncadeado.fim;
    setEncadeado.fim->proximo = setEncadeado.inicio;

    Item<Tipo> *aux = setEncadeado.inicio;
    Item<Tipo> *previous = NULL;

    while (aux != setEncadeado.inicio->anterior && antigoInicio->dado > aux->dado) {
        previous = aux;
        aux = aux->proximo;
    }

    if (antigoInicio->dado > aux->dado) {
        previous = aux;
        aux = aux->proximo;
    }

    antigoInicio->proximo = aux;
    antigoInicio->anterior = previous;
    previous->proximo = antigoInicio;
    aux->anterior = antigoInicio;

    if (aux == setEncadeado.inicio) {
        setEncadeado.fim = antigoInicio;
    }

    return true;
}

#endif
