#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 1000
#define MAX_LOGS 10000

typedef struct {
    int log_id;
    char type[10];
    int quantity;
} Log;

typedef struct {
    char id[20];
    char name[50];
    int quantity;
    double price;

    Log logs[MAX_LOGS];
    int log_count;
} Item;

Item items[MAX_ITEMS];
int item_count = 0;

int global_log_id = 1;

/* Cari index barang berdasarkan ID */
int find_item(char *id) {
    for (int i = 0; i < item_count; i++) {
        if (strcmp(items[i].id, id) == 0) {
            return i;
        }
    }
    return -1;
}

/* Tambah log */
void add_log(Item *item, char *type, int quantity) {
    Log *log = &item->logs[item->log_count++];
    log->log_id = global_log_id++;
    strcpy(log->type, type);
    log->quantity = quantity;
}

/* Handle receive */
void receive(char *id, char *name, int quantity, double price) {
    if (quantity <= 0) return;

    if (find_item(id) != -1) return;

    Item *item = &items[item_count++];
    strcpy(item->id, id);
    strcpy(item->name, name);
    item->quantity = quantity;
    item->price = price;
    item->log_count = 0;

    add_log(item, "receive", quantity);
}

/* Handle ship */
void ship(char *id, int quantity) {
    if (quantity <= 0) return;

    int idx = find_item(id);
    if (idx == -1) return;

    Item *item = &items[idx];

    if (item->quantity < quantity) return;

    item->quantity -= quantity;

    add_log(item, "ship", quantity);
}

/* Handle restock */
void restock(char *id, int quantity) {
    if (quantity <= 0) return;

    int idx = find_item(id);
    if (idx == -1) return;

    Item *item = &items[idx];
    item->quantity += quantity;

    add_log(item, "restock", quantity);
}

/* Report semua barang */
void report() {
    for (int i = 0; i < item_count; i++) {
        printf("%s|%s|%d|%.1f\n",
            items[i].id,
            items[i].name,
            items[i].quantity,
            items[i].price
        );
    }
}

/* Audit */
void audit(char *id) {
    int idx = find_item(id);
    if (idx == -1) return;

    Item *item = &items[idx];

    printf("%s|%s|%d|%.1f\n",
        item->id,
        item->name,
        item->quantity,
        item->price
    );

    for (int i = 0; i < item->log_count; i++) {
        printf("%d|%s|%d\n",
            item->logs[i].log_id,
            item->logs[i].type,
            item->logs[i].quantity
        );
    }
}

int main() {
    char line[256];

    while (fgets(line, sizeof(line), stdin)) {

        /* Stop jika --- */
        if (strncmp(line, "---", 3) == 0) break;

        /* Hapus newline */
        line[strcspn(line, "\n")] = 0;

        /* Parsing */
        char *cmd = strtok(line, "#");

        if (!cmd) continue;

        if (strcmp(cmd, "receive") == 0) {
            char *id = strtok(NULL, "#");
            char *name = strtok(NULL, "#");
            char *qty = strtok(NULL, "#");
            char *price = strtok(NULL, "#");

            if (!id || !name || !qty || !price) continue;

            receive(id, name, atoi(qty), atof(price));
        }

        else if (strcmp(cmd, "ship") == 0) {
            char *id = strtok(NULL, "#");
            char *qty = strtok(NULL, "#");

            if (!id || !qty) continue;

            ship(id, atoi(qty));
        }

        else if (strcmp(cmd, "restock") == 0) {
            char *id = strtok(NULL, "#");
            char *qty = strtok(NULL, "#");

            if (!id || !qty) continue;

            restock(id, atoi(qty));
        }

        else if (strcmp(cmd, "report") == 0) {
            report();
        }

        else if (strcmp(cmd, "audit") == 0) {
            char *id = strtok(NULL, "#");
            if (!id) continue;
            audit(id);
        }

        /* Jika command tidak valid → abaikan */
    }

    return 0;
}