/*
 * TestHashtable.c
 * Alexandru-Cosmin Mihai
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Hashtable.h"

struct InfoPrieten {
    char *nume;
    int varsta;
    char *facultate;
    char *mancare_preferata;
};

void print_prieten(struct InfoPrieten *p_info) {
    if (p_info == NULL) {
        printf("Prieten inexistent!\n");
        return;
    }
    printf("* Nume: %s | ", p_info->nume);
    printf("Varsta: %d | ", p_info->varsta);
    printf("Facultate: %s | ", p_info->facultate);
    printf("Mancare preferata: %s\n", p_info->mancare_preferata);
}

int main() {
    struct Hashtable *ht_prieteni;
    struct InfoPrieten informatii_prieteni[4];
    struct InfoPrieten *p_infoPrieten;
    int current_key;

    /* Initializare structuri informatii prieteni. */
    informatii_prieteni[0].nume = "Alexandra";
    informatii_prieteni[0].varsta = 20;
    informatii_prieteni[0].facultate = "ACS";
    informatii_prieteni[0].mancare_preferata = "tortellini";

    informatii_prieteni[1].nume = "Alin";
    informatii_prieteni[1].varsta = 21;
    informatii_prieteni[1].facultate = "ACS";
    informatii_prieteni[1].mancare_preferata = "noodles";

    informatii_prieteni[2].nume = "Alexandru";
    informatii_prieteni[2].varsta = 22;
    informatii_prieteni[2].facultate = "ACS";
    informatii_prieteni[2].mancare_preferata = "pizza";

    informatii_prieteni[3].nume = "Loredana";
    informatii_prieteni[3].varsta = 21;
    informatii_prieteni[3].facultate = "ACS";
    informatii_prieteni[3].mancare_preferata = "pizza";

    /* Initializare hashtable. */
    ht_prieteni = malloc(sizeof(struct Hashtable));
    init_ht(ht_prieteni, 10, hash_function_string, compare_function_strings);

    /* Put si get pentru o singura cheie. */
    put(ht_prieteni, "Alex", strlen("Alex") + 1, &informatii_prieteni[0]);
    p_infoPrieten = get(ht_prieteni, "Alex");
    printf("# 1\n");
    printf("Output:\n");
    print_prieten(p_infoPrieten);
    printf("Output asteptat:\n");
    printf("* Nume: Alexandra | Varsta: 20 | Facultate: ACS | Mancare preferata: tortellini\n");


    /* Put si get pentru chei unice. */
    put(ht_prieteni, "Alin", strlen("Alin") + 1, &informatii_prieteni[1]);
    put(ht_prieteni, "Loredana", strlen("Loredana") + 1, &informatii_prieteni[3]);

    p_infoPrieten = get(ht_prieteni, "Alex");
    printf("\n# 2\n");
    printf("Output:\n");
    print_prieten(p_infoPrieten);
    printf("Output asteptat:\n");
    printf("* Nume: Alexandra | Varsta: 20 | Facultate: ACS | Mancare preferata: tortellini\n");

    p_infoPrieten = get(ht_prieteni, "Alin");
    printf("\n# 3\n");
    printf("Output:\n");
    print_prieten(p_infoPrieten);
    printf("Output asteptat:\n");
    printf("* Nume: Alin | Varsta: 21 | Facultate: ACS | Mancare preferata: noodles\n");

    p_infoPrieten = get(ht_prieteni, "Loredana");
    printf("\n# 4\n");
    printf("Output:\n");
    print_prieten(p_infoPrieten);
    printf("Output asteptat:\n");
    printf("* Nume: Loredana | Varsta: 21 | Facultate: ACS | Mancare preferata: pizza\n");

    /* Has key. */
    printf("\n# 5\n");
    printf("Output: %d\n", has_key(ht_prieteni, "Loredana"));
    printf("Output asteptat: 1\n");

    printf("\n# 6\n");
    printf("Output: %d\n", has_key(ht_prieteni, "Cosmin"));
    printf("Output asteptat: 0\n");

    /* Put pentru actualizare intrare de la cheie deja existenta. */
    put(ht_prieteni, "Alex", strlen("Alex") + 1, &informatii_prieteni[2]);

    p_infoPrieten = get(ht_prieteni, "Alex");
    printf("\n# 7\n");
    printf("Output:\n");
    print_prieten(p_infoPrieten);
    printf("Output asteptat:\n");
    printf("* Nume: Alexandru | Varsta: 22 | Facultate: ACS | Mancare preferata: pizza\n");

    /* Remove entry din hashtable. */
    remove_ht_entry(ht_prieteni, "Alex");

    p_infoPrieten = get(ht_prieteni, "Alex");
    printf("\n# 8\n");
    printf("Output:\n");
    print_prieten(p_infoPrieten);
    printf("Output asteptat:\n");
    printf("Prieten inexistent!\n");

    printf("\n# 9\n");
    printf("Output: %d\n", has_key(ht_prieteni, "Alex"));
    printf("Output asteptat: 0\n");

    free_ht(ht_prieteni);

    /* Acum reconstruim un hashtable indexat prin varsta prietenilor. */
    /* Initializare hashtable cu key de tip int. */
    ht_prieteni = malloc(sizeof(struct Hashtable));
    init_ht(ht_prieteni, 5, hash_function_int, compare_function_ints);

    /* Put si get chei unice. */
    current_key = 20;
    put(ht_prieteni, &current_key, sizeof(current_key), &informatii_prieteni[0]);
    current_key = 21;
    put(ht_prieteni, &current_key, sizeof(current_key), &informatii_prieteni[1]);
    current_key = 22;
    put(ht_prieteni, &current_key, sizeof(current_key), &informatii_prieteni[2]);

    current_key = 20;
    p_infoPrieten = get(ht_prieteni, &current_key);
    printf("\n# 10\n");
    printf("Output:\n");
    print_prieten(p_infoPrieten);
    printf("Output asteptat:\n");
    printf("* Nume: Alexandra | Varsta: 20 | Facultate: ACS | Mancare preferata: tortellini\n");

    current_key = 21;
    p_infoPrieten = get(ht_prieteni, &current_key);
    printf("\n# 11\n");
    printf("Output:\n");
    print_prieten(p_infoPrieten);
    printf("Output asteptat:\n");
    printf("* Nume: Alin | Varsta: 21 | Facultate: ACS | Mancare preferata: noodles\n");

    /* Put pentru actualizare intrare de la cheie deja existenta. */
    current_key = 21;
    put(ht_prieteni, &current_key, sizeof(current_key), &informatii_prieteni[3]);
    p_infoPrieten = get(ht_prieteni, &current_key);
    printf("\n# 12\n");
    printf("Output:\n");
    print_prieten(p_infoPrieten);
    printf("Output asteptat:\n");
    printf("* Nume: Loredana | Varsta: 21 | Facultate: ACS | Mancare preferata: pizza\n");

    free_ht(ht_prieteni);

    return 0;
}
