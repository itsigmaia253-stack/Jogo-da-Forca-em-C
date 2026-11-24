#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

void desenharForca(int erros) {
    printf("\n");
    printf("  --------\n");
    printf("  |      |\n");
    if (erros >= 1) printf("  O\n");
    else printf("  \n");
    
    if (erros >= 2) printf("  |");
    if (erros >= 3) printf("--");
    if (erros >= 4) printf("-");
    if (erros >= 2 || erros >= 3 || erros >= 4) printf("\n");
    else printf("\n");
    
    if (erros >= 5) printf("  |\n");
    else printf("\n");
    
    if (erros >= 6) printf("  |\n");
    else printf("\n");
    
    if (erros >= 7) printf(" /");
    if (erros >= 8) printf(" \\\n");
    else printf("\n");
    printf("\n");
}

int main() {
    srand(time(NULL));
    
    // Lista de palavras
    const char *palavras[] = {
        "programacao", "computador", "forca", "gato", "cachorro", 
        "python", "javascript", "biblioteca", "universidade", "desenvolvimento",
        "inteligencia", "algoritmo", "variavel", "funcao", "estrutura"
    };
    
    int numPalavras = sizeof(palavras) / sizeof(palavras[0]);
    const char *palavra = palavras[rand() % numPalavras];
    int tamanho = strlen(palavra);
    
    char *descoberta = (char *)malloc(tamanho + 1);
    strcpy(descoberta, palavra);
    for (int i = 0; i < tamanho; i++) {
        descoberta[i] = '_';
    }
    descoberta[tamanho] = '\0';
    
    char letrasUsadas[26] = {0};
    int erros = 0;
    int acertos = 0;
    int maxErros = 8;
    int jogoAcabou = 0;
    int ganhou = 0;
    
    printf("╔════════════════════════════════════════╗\n");
    printf("║        BEM-VINDO AO JOGO DA FORCA     ║\n");
    printf("╚════════════════════════════════════════╝\n\n");
    printf("Adivinhe a palavra letra por letra!\n");
    printf("Você tem %d tentativas erradas.\n\n", maxErros);
    
    while (!jogoAcabou) {
        desenharForca(erros);
        printf("Palavra: %s\n", descoberta);
        printf("Letras usadas: ");
        for (int i = 0; i < 26; i++) {
            if (letrasUsadas[i]) printf("%c ", 'a' + i);
        }
        printf("\nErros: %d/%d\n", erros, maxErros);
        printf("\nDigite uma letra: ");
        
        char letra;
        scanf(" %c", &letra);
        letra = tolower(letra);
        
        // Verificar se já foi usada
        if (letrasUsadas[letra - 'a']) {
            printf("❌ Você já usou essa letra!\n");
            system("clear || cls");
            continue;
        }
        
        letrasUsadas[letra - 'a'] = 1;
        
        // Verificar se a letra está na palavra
        int encontrou = 0;
        for (int i = 0; i < tamanho; i++) {
            if (palavra[i] == letra) {
                descoberta[i] = letra;
                encontrou = 1;
                acertos++;
            }
        }
        
        if (encontrou) {
            printf("✅ Ótimo! A letra '%c' existe na palavra!\n", letra);
        } else {
            printf("❌ A letra '%c' não existe na palavra!\n", letra);
            erros++;
        }
        
        // Verificar vitória
        if (acertos == tamanho) {
            jogoAcabou = 1;
            ganhou = 1;
        }
        
        // Verificar derrota
        if (erros >= maxErros) {
            jogoAcabou = 1;
            ganhou = 0;
        }
        
        system("clear || cls");
    }
    
    // Fim do jogo
    desenharForca(erros);
    printf("Palavra: %s\n", palavra);
    
    if (ganhou) {
        printf("\n🎉 PARABÉNS! VOCÊ GANHOU! 🎉\n");
        printf("A palavra era: %s\n", palavra);
    } else {
        printf("\n💀 GAME OVER! VOCÊ PERDEU! 💀\n");
        printf("A palavra era: %s\n", palavra);
    }
    
    free(descoberta);
    return 0;
}