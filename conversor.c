/*
 * conversor.c — Converteix temperatures entre graus Celsius, Fahrenheit i Kelvin.
 *
 * Ús:
 *   ./conversor <mode> <valor>
 *
 * Modes:
 *   c2f   Celsius    -> Fahrenheit
 *   f2c   Fahrenheit -> Celsius
 *   c2k   Celsius    -> Kelvin
 *   k2c   Kelvin     -> Celsius
 *
 * Exemples:
 *   ./conversor c2f 100     ->  100.00 C = 212.00 F
 *   ./conversor k2c 0       ->  0.00 K = -273.15 C
 *
 * Codis d'eixida:
 *   0  conversió correcta
 *   1  valor impossible (per davall del zero absolut)
 *   2  error d'ús (arguments incorrectes)
 *
 * Només fa servir la biblioteca estàndard de C (C11).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ZERO_ABSOLUT_C (-273.15)

static void mostra_us(const char *programa)
{
    fprintf(stderr,
            "Ús: %s <mode> <valor>\n"
            "Modes: c2f, f2c, c2k, k2c\n",
            programa);
}

/* Converteix el text a double. Torna 0 si no és un nombre vàlid. */
static int llig_nombre(const char *text, double *resultat)
{
    char *final = NULL;
    *resultat = strtod(text, &final);
    return final != text && *final == '\0';
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        mostra_us(argv[0]);
        return 2;
    }

    const char *mode = argv[1];
    double valor;

    if (!llig_nombre(argv[2], &valor)) {
        fprintf(stderr, "Error: «%s» no és un nombre vàlid.\n", argv[2]);
        return 2;
    }

    /* Passem sempre per Celsius per a comprovar el zero absolut. */
    double celsius;
    char origen;

    if (strcmp(mode, "c2f") == 0 || strcmp(mode, "c2k") == 0) {
        celsius = valor;
        origen = 'C';
    } else if (strcmp(mode, "f2c") == 0) {
        celsius = (valor - 32.0) * 5.0 / 9.0;
        origen = 'F';
    } else if (strcmp(mode, "k2c") == 0) {
        celsius = valor + ZERO_ABSOLUT_C;
        origen = 'K';
    } else {
        fprintf(stderr, "Error: mode desconegut «%s».\n", mode);
        mostra_us(argv[0]);
        return 2;
    }

    if (celsius < ZERO_ABSOLUT_C - 1e-9) {
        fprintf(stderr, "Error: %.2f %c està per davall del zero absolut.\n",
                valor, origen);
        return 1;
    }

    double resultat;
    char desti;

    if (strcmp(mode, "c2f") == 0) {
        resultat = celsius * 9.0 / 5.0 + 32.0;
        desti = 'F';
    } else if (strcmp(mode, "c2k") == 0) {
        resultat = celsius - ZERO_ABSOLUT_C;
        desti = 'K';
    } else {
        resultat = celsius;
        desti = 'C';
    }

    printf("%.2f %c = %.2f %c\n", valor, origen, resultat, desti);
    return 0;
}
