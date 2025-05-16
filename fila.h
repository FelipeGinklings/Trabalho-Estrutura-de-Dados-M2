#ifndef FILA_H
#define FILA_H

template<typename TIPO>
struct ItemFila {
    TIPO dado;
    ItemFila<TIPO> *prox;
};

template<typename TIPO>
struct Fila {
    ItemFila<TIPO> *inicio;
    ItemFila<TIPO> *fim; 
    int tamanho;
};

template<typename TIPO>
void inicializaFila(Fila<TIPO> &f){
    f.inicio = nullptr;
    f.fim = nullptr;
    f.tamanho = 0;
}

template<typename TIPO>
void entrarNaFila(Fila<TIPO> &f, TIPO dado){
    ItemFila<TIPO>* novoItem = new ItemFila<TIPO>;
    novoItem->dado = dado;
    novoItem->prox = nullptr;
    
    if (f.inicio == nullptr){ // Fila estava vazia
        f.inicio = novoItem;
        f.fim = novoItem;
    } else { // Fila não estava vazia
        f.fim->prox = novoItem;
        f.fim = novoItem;
    }
    f.tamanho++;
}

template<typename TIPO>
TIPO atender(Fila<TIPO> &f){
    if(f.inicio!=nullptr){
        ItemFila<TIPO>* apagado = f.inicio;
        TIPO dadoRetorno = apagado->dado;
        f.inicio = apagado->prox;
        f.tamanho--;

        if (f.inicio == nullptr){ // Se a fila ficou vazia
            f.fim = nullptr;    // Atualizar ponteiro fim
        }
        delete apagado;
        return dadoRetorno;
    }
}

template<typename TIPO>
TIPO primeiro(Fila<TIPO> &f){
    if(f.inicio!=nullptr){
        return f.inicio->dado;
    }
}

#endif // FILA_H