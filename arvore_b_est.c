#include "arvore_b_est.h"

void tree_b_star(int amount, int key) {
    int i;
    information info;
    Nodo2 tree;
    info.key = key;
    clock_t time_begin_ind, time_end_ind;
    time_begin_ind = clock();
    initialize_b_star_tree(&tree);
    FILE* arquivo;
    if ((arquivo = fopen("informations.bin", "rb")) == NULL) {
        printf("Erro na abertura do arquivo!\n");
        return;
    }
    information* aux = (information*)malloc(amount * sizeof(information));
    while (fread(aux, sizeof(information), amount, arquivo)) {
        dados.hits += amount;
        i = 0;
        while (i < amount) {
            insert_star(aux[i], &tree);
            i++;
        }
    }
    free(aux);
    time_end_ind = clock();

    printf("Numero de transferencias: %lld\n", dados.hits);
    printf("Numero de comparisons: %lld\n", dados.comparisons);
    dados.time = fabs((double)(time_end_ind - time_begin_ind) / CLOCKS_PER_SEC);
    printf("Tempo: %lf segundos\n", dados.time);
    dados.hits = 0;
    dados.comparisons = 0;
    time_begin_ind = clock();
    fclose(arquivo);
    if (b_star_tree_search(&info, &tree)) {
        printf("\nkey: %d\n dado1: %ld\n dado2: %s\n dado3: %s\n", info.key, info.dado1, info.dado2, info.dado3);
        printf("Numero de transferencias: %lld\n", dados.hits);
        printf("Numero de comparisons: %lld\n", dados.comparisons);
        dados.time = fabs((double)(clock() - time_begin_ind) / CLOCKS_PER_SEC);
        printf("Tempo: %lf segundos\n", dados.time);
    }
    else {
        printf("key nao encontrada!\n");
    }
    release_tree_b_star(&tree);
}

void release_tree_b_star(Nodo2 *no){
    if ((*no)->pt == Externa)
        return;
    for(int i = 0; i <= (*no)->UU.In.ni; i++) {
        release_tree_b_star(&(*no)->UU.In.sons[i]);
        free((*no)->UU.In.sons[i]);
    }
}

void initialize_b_star_tree(Nodo2 *tree) {
    *tree = (Nodo2) malloc(sizeof(Pag));
    (*tree)->pt = Externa;
    (*tree)->UU.Ex.ne = 0;
}


int b_star_tree_search(information *x, Nodo2 *ap) {
    int i;
    Nodo2 pag = *ap;
    if ((*ap)->pt == Interna){
        i = 1;
        // pesquisa sequencial na pagina interna
        while(i< pag->UU.In.ni && x->key > pag->UU.In.keys[i-1]){
            dados.comparisons++;
            i++;
        }
        if (i<pag->UU.In.ni && !(x->key>pag->UU.In.keys[i-1])){
            dados.comparisons++;
        }
        dados.comparisons++;
        if (x->key<= pag->UU.In.keys[i-1])
            return b_star_tree_search(x, &pag->UU.In.sons[i-1]);
        else 
            return b_star_tree_search(x, &pag->UU.In.sons[i]);
    }
    // pesquisa na pagina folha
    i= 1;
    while (i< pag->UU.Ex.ne && x->key > pag->UU.Ex.r[i-1].key) {
        dados.comparisons++;
        i++;
    }
    if(i< pag->UU.Ex.ne && !(x->key > pag->UU.Ex.r[i-1].key)){
        dados.comparisons++;
    }
    // verifica se achou a key    
    if (x->key == pag->UU.Ex.r[i-1].key) {
        dados.comparisons++;
        *x = pag->UU.Ex.r[i - 1];
        return true;
    }
    return false;
}


void insert_star(information reg, Nodo2 *ap) {
    int adds,reg_retorno;
    Pag *ap_retorno, *ap_temp;
    ins_est(reg, *ap, &adds, &reg_retorno, &ap_retorno);
    dados.comparisons++;
    if(adds) {
        ap_temp = (Pag *) malloc(sizeof(Pag));
        ap_temp->pt = Interna;
        ap_temp->UU.In.ni = 1;
        ap_temp->UU.In.keys[0] = reg_retorno;
        ap_temp->UU.In.sons[1] = ap_retorno;
        ap_temp->UU.In.sons[0] = *ap;
        *ap = ap_temp;
    }
}


void insert_external_page(Nodo2 ap, information reg) {
    int i=ap->UU.Ex.ne,didnthit= true;
    dados.comparisons++;
    while((i>0)&&(didnthit==true)){
        dados.comparisons++;
        if(reg.key>= ap->UU.Ex.r[i-1].key){
            didnthit= false;
            break;
        }
        ap->UU.Ex.r[i] = ap->UU.Ex.r[i-1];
        i--;
        dados.comparisons++;
        if (i<1) 
            didnthit= false;
    }
    ap->UU.Ex.r[i] = reg;
    ap->UU.Ex.ne++;
}


void insert_internal_page(Nodo2 ap, int key, Nodo2 apDir) {
    int i= ap->UU.In.ni,didnthit= true;
    dados.comparisons++;
    while((i>0)&&(didnthit==true)){
        dados.comparisons++;

        if(key>= ap->UU.In.keys[i-1]){
            dados.comparisons++;
            didnthit= false;
            break;
        }
        ap->UU.In.keys[i] = ap->UU.In.keys[i-1];
        ap->UU.In.sons[i+1] = ap->UU.In.sons[i];
        i--;
        dados.comparisons++;
        if(i<1) 
            didnthit= false;
    }
    ap->UU.In.keys[i]= key;
    ap->UU.In.sons[i+ 1]= apDir;
    ap->UU.In.ni++;
}

         
void ins_est(information reg, Nodo2 ap, int *adds, int *reg_retorno, Nodo2 *ap_retorno) {
    Nodo2 aux;
    int j;
    long i = 1;
    dados.comparisons++;
    if (ap->pt == Externa) {
        // verifica se h� espa�o para inserir na folha
        dados.comparisons++;
        if (ap->UU.Ex.ne < M + M) {
            insert_external_page(ap, reg);
            *adds= false;
            return;
        }
        // Pagina (folha) tem que ser dividida
        aux= (Nodo2) malloc(sizeof(Pag));
        aux->UU.Ex.ne = 0;
        aux->pt = Externa;
        // acha a posi��o onde vai ser inseridio
        while (i < ap->UU.Ex.ne && reg.key > ap->UU.Ex.r[i - 1].key) {
          dados.comparisons++;
          i++;  
        }
        if (i < ap->UU.Ex.ne && !(reg.key > ap->UU.Ex.r[i - 1].key)) {
            dados.comparisons++;
        }
        dados.comparisons++;
        if (reg.key == ap->UU.Ex.r[i - 1].key) {
            dados.comparisons++;
            printf("information ja esta presente!\n");
            *adds= false;
            return;
        }
        dados.comparisons++;
        if (reg.key < ap->UU.Ex.r[i - 1].key)
            i--;
        dados.comparisons++;
        if (i < M + 1) {
            // coloca o information mais a direita na nova p�gina
            insert_external_page(aux, ap->UU.Ex.r[M + M - 1]);
            ap->UU.Ex.ne--;
            // insere o novo information na p�gina antiga
            insert_external_page(ap, reg);
        }
        else  
            insert_external_page(aux, reg);
        j=M + 2;
        while (j <= M + M){
            dados.comparisons++;
            insert_external_page(aux, ap->UU.Ex.r[j - 1]);
            j++;
        }
        ap->UU.Ex.ne = M + 1;
        // sobe o pai
        *reg_retorno = ap->UU.Ex.r[M].key;
        *ap_retorno = aux;
        *adds= true;
        return;
    }
    // Pagina Interna
    while (i < ap->UU.In.ni && reg.key > ap->UU.In.keys[i - 1]) {
        i++;
        dados.comparisons++;
    }
    dados.comparisons++;
    if( i < ap->UU.In.ni && !(reg.key > ap->UU.In.keys[i - 1])){
        dados.comparisons++;
    }
    dados.comparisons++;
    if (reg.key <= ap->UU.In.keys[i - 1]) i--;
    ins_est(reg, ap->UU.In.sons[i],adds, reg_retorno, ap_retorno);
    dados.comparisons++;
    if (!(*adds)) return;
    dados.comparisons++;
    if (ap->UU.In.ni < M + M) {
        insert_internal_page(ap, *reg_retorno, *ap_retorno);
        *adds= 0;
        return;
    }
    // Pagina tem que ser dividida
    aux= (Nodo2) malloc(sizeof(Pag));
    aux->UU.In.ni = 0;
    aux->UU.In.sons[0] = NULL;
    aux->pt = Interna;
    dados.comparisons++;
    if (i < M + 1) {
        insert_internal_page(aux, ap->UU.In.keys[M + M - 1], ap->UU.In.sons[M + M]);
        ap->UU.In.ni--;
        insert_internal_page(ap, *reg_retorno, *ap_retorno);
    }
    else
        insert_internal_page(aux, *reg_retorno, *ap_retorno);
    j=M + 2;
    while (j <= M + M){
        insert_internal_page(aux, ap->UU.In.keys[j - 1], ap->UU.In.sons[j]);
        dados.comparisons++;
        j++;
    }
    ap->UU.In.ni = M;
    aux->UU.In.sons[0] = ap->UU.In.sons[M + 1];
    dados.comparisons++;
    *reg_retorno = ap->UU.In.keys[M];
    *ap_retorno = aux;
    *adds= true;
}