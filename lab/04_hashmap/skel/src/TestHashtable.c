/*
 * Testhashtable_t.c
 * Alexandru-Cosmin Mihai
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Hashtable.h"

#define MAX_STRING_SIZE		256

struct InfoPrieten {
	char nume[MAX_STRING_SIZE];
	char facultate[MAX_STRING_SIZE];
	char mancare_preferata[MAX_STRING_SIZE];
	int varsta;
};

static void
print_prieten(struct InfoPrieten *p_info)
{
	if (p_info == NULL) {
		printf("Prieten inexistent!\n");
		return;
	}
	printf("* Nume: %s | ", p_info->nume);
	printf("Varsta: %d | ", p_info->varsta);
	printf("Facultate: %s | ", p_info->facultate);
	printf("Mancare preferata: %s\n", p_info->mancare_preferata);
}

int
main()
{
	hashtable_t *ht_prieteni;
	struct InfoPrieten informatii_prieteni[4];
	struct InfoPrieten *p_infoPrieten;
	int current_key;

	/* Initializare structuri informatii prieteni. */
	strcpy(informatii_prieteni[0].nume, "Alexandra");
	informatii_prieteni[0].varsta = 20;
	strcpy(informatii_prieteni[0].facultate, "ACS");
	strcpy(informatii_prieteni[0].mancare_preferata, "tortellini");

	strcpy(informatii_prieteni[1].nume, "Alin");
	informatii_prieteni[1].varsta = 21;
	strcpy(informatii_prieteni[1].facultate, "ACS");
	strcpy(informatii_prieteni[1].mancare_preferata, "noodles");

	strcpy(informatii_prieteni[2].nume, "Alexandru");
	informatii_prieteni[2].varsta = 22;
	strcpy(informatii_prieteni[2].facultate, "ACS");
	strcpy(informatii_prieteni[2].mancare_preferata, "pizza");

	strcpy(informatii_prieteni[3].nume, "Loredana");
	informatii_prieteni[3].varsta = 21;
	strcpy(informatii_prieteni[3].facultate, "ACS");
	strcpy(informatii_prieteni[3].mancare_preferata, "pizza");

	/* Initializare hashtable_t. */
	ht_prieteni = ht_create(10, hash_function_string,
				compare_function_strings);

	/* Put si get pentru o singura cheie. */
	ht_put(ht_prieteni, "Alex", strlen("Alex") + 1, &informatii_prieteni[0],
		sizeof(informatii_prieteni[0]));
	p_infoPrieten = ht_get(ht_prieteni, "Alex");
	printf("# 1\n");
	printf("Output:\n");
	print_prieten(p_infoPrieten);
	printf("Output asteptat:\n");
	printf("* Nume: Alexandra | Varsta: 20 | Facultate: ACS | Mancare preferata: tortellini\n");


	/* Put si get pentru chei unice. */
	ht_put(ht_prieteni, "Alin", strlen("Alin") + 1, &informatii_prieteni[1],
		sizeof(informatii_prieteni[1]));
	ht_put(ht_prieteni, "Loredana", strlen("Loredana") + 1,
		&informatii_prieteni[3], sizeof(informatii_prieteni[3]));

	p_infoPrieten = ht_get(ht_prieteni, "Alex");
	printf("\n# 2\n");
	printf("Output:\n");
	print_prieten(p_infoPrieten);
	printf("Output asteptat:\n");
	printf("* Nume: Alexandra | Varsta: 20 | Facultate: ACS | Mancare preferata: tortellini\n");

	p_infoPrieten = ht_get(ht_prieteni, "Alin");
	printf("\n# 3\n");
	printf("Output:\n");
	print_prieten(p_infoPrieten);
	printf("Output asteptat:\n");
	printf("* Nume: Alin | Varsta: 21 | Facultate: ACS | Mancare preferata: noodles\n");

	p_infoPrieten = ht_get(ht_prieteni, "Loredana");
	printf("\n# 4\n");
	printf("Output:\n");
	print_prieten(p_infoPrieten);
	printf("Output asteptat:\n");
	printf("* Nume: Loredana | Varsta: 21 | Facultate: ACS | Mancare preferata: pizza\n");

	/* Has key. */
	printf("\n# 5\n");
	printf("Output: %d\n", ht_has_key(ht_prieteni, "Loredana"));
	printf("Output asteptat: 1\n");

	printf("\n# 6\n");
	printf("Output: %d\n", ht_has_key(ht_prieteni, "Cosmin"));
	printf("Output asteptat: 0\n");

	/* Put pentru actualizare intrare de la cheie deja existenta. */
	ht_put(ht_prieteni, "Alex", strlen("Alex") + 1, &informatii_prieteni[2],
		sizeof(informatii_prieteni[2]));

	p_infoPrieten = ht_get(ht_prieteni, "Alex");
	printf("\n# 7\n");
	printf("Output:\n");
	print_prieten(p_infoPrieten);
	printf("Output asteptat:\n");
	printf("* Nume: Alexandru | Varsta: 22 | Facultate: ACS | Mancare preferata: pizza\n");

	/* Remove entry din hashtable_t. */
	ht_remove_entry(ht_prieteni, "Alex");

	p_infoPrieten = ht_get(ht_prieteni, "Alex");
	printf("\n# 8\n");
	printf("Output:\n");
	print_prieten(p_infoPrieten);
	printf("Output asteptat:\n");
	printf("Prieten inexistent!\n");

	printf("\n# 9\n");
	printf("Output: %d\n", ht_has_key(ht_prieteni, "Alex"));
	printf("Output asteptat: 0\n");

	ht_free(ht_prieteni);

	/* Acum reconstruim un hashtable_t indexat prin varsta prietenilor. */
	/* Initializare hashtable_t cu key de tip int. */
	ht_prieteni = ht_create(5, hash_function_int, compare_function_ints);

	/* Put si get chei unice. */
	current_key = 20;
	ht_put(ht_prieteni, &current_key, sizeof(current_key),
		&informatii_prieteni[0], sizeof(informatii_prieteni[0]));
	current_key = 21;
	ht_put(ht_prieteni, &current_key, sizeof(current_key),
		&informatii_prieteni[1], sizeof(informatii_prieteni[1]));
	current_key = 22;
	ht_put(ht_prieteni, &current_key, sizeof(current_key),
		&informatii_prieteni[2], sizeof(informatii_prieteni[2]));

	current_key = 20;
	p_infoPrieten = ht_get(ht_prieteni, &current_key);
	printf("\n# 10\n");
	printf("Output:\n");
	print_prieten(p_infoPrieten);
	printf("Output asteptat:\n");
	printf("* Nume: Alexandra | Varsta: 20 | Facultate: ACS | Mancare preferata: tortellini\n");

	current_key = 21;
	p_infoPrieten = ht_get(ht_prieteni, &current_key);
	printf("\n# 11\n");
	printf("Output:\n");
	print_prieten(p_infoPrieten);
	printf("Output asteptat:\n");
	printf("* Nume: Alin | Varsta: 21 | Facultate: ACS | Mancare preferata: noodles\n");

	/* Put pentru actualizare intrare de la cheie deja existenta. */
	current_key = 21;
	ht_put(ht_prieteni, &current_key, sizeof(current_key),
		&informatii_prieteni[3], sizeof(informatii_prieteni[3]));
	p_infoPrieten = ht_get(ht_prieteni, &current_key);
	printf("\n# 12\n");
	printf("Output:\n");
	print_prieten(p_infoPrieten);
	printf("Output asteptat:\n");
	printf("* Nume: Loredana | Varsta: 21 | Facultate: ACS | Mancare preferata: pizza\n");

	ht_free(ht_prieteni);

	return 0;
}
