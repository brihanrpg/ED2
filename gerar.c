#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void create_binary_file(const char* file_path, int num_chars) {
    FILE* file = fopen(file_path, "wb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    for (int i = 0; i < num_chars; i++) {
        char ch = rand() % 26 + 'A';  // Gera um caractere maiúsculo aleatório

        fwrite(&ch, sizeof(char), 1, file);
    }

    fclose(file);
    printf("Arquivo '%s' criado com sucesso com %d caracteres.\n", file_path, num_chars);
}

int main() {
    srand(time(NULL)); // Inicializa a semente do gerador de números aleatórios

    // Criando arquivos binários com diferentes quantidades de caracteres
    create_binary_file("arquivo_100.bin", 100);
    create_binary_file("arquivo_1000.bin", 1000);
    create_binary_file("arquivo_10000.bin", 10000);
    create_binary_file("arquivo_100000.bin", 100000);
    create_binary_file("arquivo_1000000.bin", 1000000);

    return 0;
}
