#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#define NUM_TERRITORIOS 5
#define MAX_NOME 30
#define MAX_COR 15

/* Símbolos em texto */
#define ALVO "ALVO"
#define ALIADO "ALIADO"

typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
} Territorio;

/* ================= UTIL ================= */

void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int lerInteiro(const char *msg, int min, int max) {
    int valor;
    while (1) {
        printf("%s", msg);
        if (scanf("%d", &valor) != 1) {
            limparBuffer();
            continue;
        }
        limparBuffer();
        if (valor < min || valor > max)
            continue;
        return valor;
    }
}

/* ================= INICIALIZAÇÃO ================= */

Territorio* criarTerritorios(void) {
    const char *coresUnicas[3] = {
        "Azul", "Verde", "Vermelho"
    };
    const char *nomes[NUM_TERRITORIOS] = {
        "Brasil", "Argentina", "Chile", "Peru", "Colombia"
    };

    Territorio *t = calloc(NUM_TERRITORIOS, sizeof(Territorio));
    if (!t) exit(EXIT_FAILURE);

    /* Atribuir cores em ciclo */
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        strcpy(t[i].nome, nomes[i]);
        strcpy(t[i].cor, coresUnicas[i % 3]);  // Ciclo: Azul, Verde, Vermelho
        t[i].tropas = rand() % 5 + 3;
    }

    return t;
}

/* ================= MAPA ================= */

void exibirMapa(const Territorio *t, int atacante, int defensor) {
    printf("\n=========== MAPA ==========\n");
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        if (i == defensor)
            printf("%d - %s [%s] | Tropas: %d\n", i + 1, t[i].nome, ALVO, t[i].tropas);
        else if (atacante != -1 && strcmp(t[i].cor, t[atacante].cor) == 0)
            printf("%d - %s [%s] | Tropas: %d\n", i + 1, t[i].nome, ALIADO, t[i].tropas);
        else
            printf("%d - %s | Tropas: %d | Cor: %s\n", i + 1, t[i].nome, t[i].tropas, t[i].cor);
    }
    printf("===========================\n");
}

/* ================= MISSÃO ================= */

int verificarMissao(const Territorio *t) {
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        int cont = 0;
        for (int j = 0; j < NUM_TERRITORIOS; j++)
            if (strcmp(t[i].cor, t[j].cor) == 0)
                cont++;
        if (cont >= 3) return 1;
    }
    return 0;
}

/* ================= BATALHA ================= */

void atacar(Territorio *t) {
    int a = lerInteiro("Atacante (1-5): ", 1, 5) - 1;
    int d = lerInteiro("Defensor (1-5): ", 1, 5) - 1;

    if (a == d) {
        printf("Não pode atacar o mesmo território!\n");
        return;
    }
    if (t[a].tropas <= 1) {
        printf("Tropas insuficientes para atacar.\n");
        return;
    }

    exibirMapa(t, a, d);

    printf("\nBATALHA: %s VS %s\n", t[a].nome, t[d].nome);
    int dadoA = rand() % 6 + 1;
    int dadoD = rand() % 6 + 1;

    printf("Ataque: %d | Defesa: %d\n", dadoA, dadoD);

    if (dadoA >= dadoD) {
        t[d].tropas--;
        printf("Defensor perdeu 1 tropa!\n");
        if (t[d].tropas <= 0) {
            printf("Território conquistado!\n");
            strcpy(t[d].cor, t[a].cor);
            t[d].tropas = 1;
            t[a].tropas--;
        }
    } else {
        t[a].tropas--;
        printf("Ataque falhou! Atacante perdeu 1 tropa.\n");
    }

    printf("Fim da rodada.\n");

    if (verificarMissao(t))
        printf("OBJETIVO CONQUISTADO!\n");
    else
        printf("Objetivo ainda não alcançado.\n");
}

/* ================= MAIN ================= */

int main(void) {
    setlocale(LC_ALL, "");
    srand((unsigned)time(NULL));

    Territorio *territorios = criarTerritorios();

    int opcao;
    do {
        printf("\n=========== WAR ===========\n");
        printf("Objetivo: Conquistar 3 territórios da mesma cor\n");
        printf("1 - Atacar\n");
        printf("2 - Ver Mapa\n");
        printf("0 - Sair\n");

        opcao = lerInteiro("Escolha: ", 0, 2);

        switch (opcao) {
            case 1:
                atacar(territorios);
                break;
            case 2:
                exibirMapa(territorios, -1, -1);
                break;
        }

        if (verificarMissao(territorios)) {
            printf("\nPARABÉNS! VOCÊ COMPLETOU A MISSÃO!\n");
            break;
        }

    } while (opcao != 0);

    /* Pausa dupla antes de sair */
    printf("\nPressione ENTER para continuar...");
    getchar();
    printf("Pressione ENTER novamente para sair...");
    getchar();

    free(territorios);
    return 0;
}
