#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hashtable.h"

struct account_details{
    unsigned int pin, balance;
    linked_list_t *transactions;
};

struct trans_details{
    char location[50], date[20];
    int sum;
};

int main()
{
    hashtable_t *htBank = ht_create(10, hash_function_string, compare_function_strings);

    char clients[5][10];
    strcpy(clients[0], "Josh");
    strcpy(clients[1], "Sandra");
    strcpy(clients[2], "Daniel");
    strcpy(clients[3], "Corina");
    strcpy(clients[4], "Kate");

    struct account_details details[4];
    details[0].pin = 1243;
    details[0].balance = 30;
    details[0].transactions = ll_create(sizeof(struct trans_details));
    struct trans_details trans;
    strcpy(trans.location, "Auchan");
    strcpy(trans.date, "12-05-2020");
    trans.sum = 120;
    ll_add_nth_node(details[0].transactions, 0, &trans);
    strcpy(trans.location, "Kaufland");
    strcpy(trans.date, "17-03-2020");
    trans.sum = 40;
    ll_add_nth_node(details[0].transactions, 1, &trans);

    details[1].pin = 1423;
    details[1].balance = 60;
    details[1].transactions = ll_create(sizeof(struct trans_details));
    strcpy(trans.location, "Walmart");
    strcpy(trans.date, "12-06-2019");
    trans.sum = 450;
    ll_add_nth_node(details[1].transactions, 0, &trans);
    strcpy(trans.location, "Target");
    strcpy(trans.date, "14-02-2019");
    trans.sum = 500;
    ll_add_nth_node(details[1].transactions, 1, &trans);

    details[2].pin = 3241;
    details[2].balance = 100;
    details[2].transactions = ll_create(sizeof(struct trans_details));
    strcpy(trans.location, "Lidl");
    strcpy(trans.date, "68-17-2022");
    trans.sum = 120;
    ll_add_nth_node(details[2].transactions, 0, &trans);
    strcpy(trans.location, "Auchan");
    strcpy(trans.date, "21-09-2021");
    trans.sum = 60;
    ll_add_nth_node(details[2].transactions, 1, &trans);

    details[3].pin = 1234;
    details[3].balance = 20;
    details[3].transactions = ll_create(sizeof(struct trans_details));
    strcpy(trans.location, "Carrefour");
    strcpy(trans.date, "25-12-2018");
    trans.sum = 220;
    ll_add_nth_node(details[3].transactions, 0, &trans);
    strcpy(trans.location, "KFC");
    strcpy(trans.date, "07-10-2021");
    trans.sum = 50;
    ll_add_nth_node(details[3].transactions, 1, &trans);

    details[4].pin = 3421;
    details[4].balance = 75;
    details[4].transactions = ll_create(sizeof(struct trans_details));
    strcpy(trans.location, "Walmart");
    strcpy(trans.date, "06-02-2019");
    trans.sum = 320;
    ll_add_nth_node(details[4].transactions, 0, &trans);
    strcpy(trans.location, "Lidl");
    strcpy(trans.date, "18-08-2019");
    trans.sum = 655;
    ll_add_nth_node(details[4].transactions, 1, &trans);

    for (int i = 0; i < 5; i++)
        ht_put(htBank, clients[i], strlen(clients[i]) + 1, &details[i], sizeof(details[i]));

    struct account_details acc;
    acc = *((struct account_details*)ht_get(htBank, clients[2]));
    ll_node_t *q = acc.transactions->head;
    while (q != NULL)
    {
        printf("%s spent %d on %s in %s\n", clients[2], ((struct trans_details*)q->data)->sum, ((struct trans_details*)q->data)->date, ((struct trans_details*)q->data)->location);
        q = q->next;
    }

    char name[10];
    for (int i = 0; i < htBank->hmax; i++)
    {
        ll_node_t *q = htBank->buckets[i]->head;
        while (q != NULL)
        {
            if (((struct account_details*)((struct info*)q->data)->value)->balance <= 50)
            {
                strcpy(name, (char *)((struct info*)q->data)->key);
                ll_free(&((struct account_details*)((struct info*)q->data)->value)->transactions);
                ht_remove_entry(htBank, name);
                printf("%s has been removed\n", name);
            }
            q = q->next;
        }
    }
/*
    for (int i = 0; i < htBank->hmax; i++)
    {
        ll_node_t *q = htBank->buckets[i]->head;
        while (q != NULL)
        {
            if (strcmp(((struct trans_details*)q->data)->date, "07-10-2021") == 0)
            {
                strcpy(name, (char *)((struct info*)q->data)->key);
                printf("%s spent %d on %s in %s\n", name, ((struct trans_details*)q->data)->sum, ((struct trans_details*)q->data)->date, ((struct trans_details*)q->data)->location);
            }
            q = q->next;
        }
    }
*/
    ht_free(htBank);
}
