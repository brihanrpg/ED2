/* Pesquisa das 10 chaves */
/*{
    clock_t time_begin_ind, time_end_ind;
    dados.acessos = dados.comparacoes = 0;

    time_begin_ind = clock();
    int tam = 200;
    Registro *aux = (Registro*) malloc(tam * sizeof(Registro));
    while (fread(aux, sizeof(Registro), tam, arquivo)) {
        dados.acessos++;
        for (int i = 0; i < tam; i++) {
            insere_est(aux[i], &arvore);
        }
    }
    time_end_ind = clock();
    fclose(arquivo);

    printf("Dados da geração dos índices:\n");
    printf("Acessos:      %lld\n", dados.acessos);
    printf("Comparações:  %lld\n", dados.comparacoes);
    printf("Tempo:        %lfs\n", (double) (time_end_ind - time_begin_ind) / CLOCKS_PER_SEC);

    Analise soma_dados;
    soma_dados.acessos = soma_dados.comparacoes = 0;
    dados.acessos = dados.comparacoes = 0;

    int num[10], tam2 = 0;
    srand(time(NULL));
    while (tam2 < 10) {
        int ok = 1;
        int numero = rand() % total_registros + 1;
        for (int i = 0; i < 10; i++) {
            if (num[i] == numero) ok = 0;
        }
        if (ok) num[tam2++] = numero;
    }

    for (int i = 0; i < 10; i++) {
        clock_t time_begin, time_end;
        Registro xx;
        xx.chave = num[i];
        time_begin = clock();
        pesquisa_est(&xx, &arvore);
        time_end = clock();
        soma_dados.tempo += (double) (time_end - time_begin) / CLOCKS_PER_SEC;
        soma_dados.acessos += dados.acessos;
        soma_dados.comparacoes += dados.comparacoes;
        dados.acessos = dados.comparacoes = 0;
    }
    soma_dados.comparacoes /= 10;
    soma_dados.acessos /= 10;
    soma_dados.tempo /= 10.0;
    printf("\nDADOS DA PESQUISA:\n");
    printf("Acessos:       %lld\n", soma_dados.acessos);
    printf("Comparações:   %lld\n", soma_dados.comparacoes);
    printf("Tempo:         %lfs\n", soma_dados.tempo);
}*/
