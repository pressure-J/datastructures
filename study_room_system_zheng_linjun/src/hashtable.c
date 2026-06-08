#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "linkedlist.h"

static int isBlank(const char *text) {
    return text == NULL || text[0] == '\0';
}

static void copyString(char *dest, size_t destSize, const char *src) {
    if (dest == NULL || destSize == 0) return;
    if (src == NULL) {
        dest[0] = '\0';
        return;
    }
    strncpy(dest, src, destSize - 1);
    dest[destSize - 1] = '\0';
}

unsigned int hashString(const char *key) {
    unsigned int seed = 131;
    unsigned int hash = 0;
    if (key == NULL) return 0;
    while (*key) {
        hash = hash * seed + (unsigned char)(*key++);
    }
    return (hash & 0x7FFFFFFF) % HASH_TABLE_SIZE;
}

int initStudentHashTable(StudentHashTable *table) {
    if (table == NULL) return 0;
    memset(table, 0, sizeof(StudentHashTable));
    return 1;
}

int initSeatHashTable(SeatHashTable *table) {
    if (table == NULL) return 0;
    memset(table, 0, sizeof(SeatHashTable));
    return 1;
}

int initReservationHashTable(ReservationHashTable *table) {
    if (table == NULL) return 0;
    memset(table, 0, sizeof(ReservationHashTable));
    return 1;
}

Student *findStudentInHash(StudentHashTable *table, const char *studentId) {
    StudentHashNode *node;
    if (table == NULL || isBlank(studentId)) return NULL;
    node = table->buckets[hashString(studentId)];
    while (node != NULL) {
        if (strcmp(node->key, studentId) == 0) return node->value;
        node = node->next;
    }
    return NULL;
}

Seat *findSeatInHash(SeatHashTable *table, const char *seatId) {
    SeatHashNode *node;
    if (table == NULL || isBlank(seatId)) return NULL;
    node = table->buckets[hashString(seatId)];
    while (node != NULL) {
        if (strcmp(node->key, seatId) == 0) return node->value;
        node = node->next;
    }
    return NULL;
}

Reservation *findReservationInHash(ReservationHashTable *table, const char *resId) {
    ReservationHashNode *node;
    if (table == NULL || isBlank(resId)) return NULL;
    node = table->buckets[hashString(resId)];
    while (node != NULL) {
        if (strcmp(node->key, resId) == 0) return node->value;
        node = node->next;
    }
    return NULL;
}

int insertStudentToHash(StudentHashTable *table, const Student *student) {
    unsigned int index;
    StudentHashNode *node;
    if (table == NULL || student == NULL || isBlank(student->studentId)) return 0;
    if (findStudentInHash(table, student->studentId) != NULL) return 0;
    node = (StudentHashNode *)calloc(1, sizeof(StudentHashNode));
    if (node == NULL) return 0;
    node->value = createStudentNode(student);
    if (node->value == NULL) {
        free(node);
        return 0;
    }
    copyString(node->key, sizeof(node->key), student->studentId);
    index = hashString(node->key);
    node->next = table->buckets[index];
    table->buckets[index] = node;
    table->count++;
    return 1;
}

int insertSeatToHash(SeatHashTable *table, const Seat *seat) {
    unsigned int index;
    SeatHashNode *node;
    if (table == NULL || seat == NULL || isBlank(seat->seatId)) return 0;
    if (findSeatInHash(table, seat->seatId) != NULL) return 0;
    node = (SeatHashNode *)calloc(1, sizeof(SeatHashNode));
    if (node == NULL) return 0;
    node->value = createSeatNode(seat);
    if (node->value == NULL) {
        free(node);
        return 0;
    }
    copyString(node->key, sizeof(node->key), seat->seatId);
    index = hashString(node->key);
    node->next = table->buckets[index];
    table->buckets[index] = node;
    table->count++;
    return 1;
}

int insertReservationToHash(ReservationHashTable *table, const Reservation *res) {
    unsigned int index;
    ReservationHashNode *node;
    if (table == NULL || res == NULL || isBlank(res->reservationId)) return 0;
    if (findReservationInHash(table, res->reservationId) != NULL) return 0;
    node = (ReservationHashNode *)calloc(1, sizeof(ReservationHashNode));
    if (node == NULL) return 0;
    node->value = createReservationNode(res);
    if (node->value == NULL) {
        free(node);
        return 0;
    }
    copyString(node->key, sizeof(node->key), res->reservationId);
    index = hashString(node->key);
    node->next = table->buckets[index];
    table->buckets[index] = node;
    table->count++;
    return 1;
}

int deleteStudentFromHash(StudentHashTable *table, const char *studentId) {
    unsigned int index;
    StudentHashNode *cur;
    StudentHashNode *prev = NULL;
    if (table == NULL || isBlank(studentId)) return 0;
    index = hashString(studentId);
    cur = table->buckets[index];
    while (cur != NULL) {
        if (strcmp(cur->key, studentId) == 0) {
            if (prev == NULL) table->buckets[index] = cur->next;
            else prev->next = cur->next;
            free(cur->value);
            free(cur);
            table->count--;
            return 1;
        }
        prev = cur;
        cur = cur->next;
    }
    return 0;
}

int deleteSeatFromHash(SeatHashTable *table, const char *seatId) {
    unsigned int index;
    SeatHashNode *cur;
    SeatHashNode *prev = NULL;
    if (table == NULL || isBlank(seatId)) return 0;
    index = hashString(seatId);
    cur = table->buckets[index];
    while (cur != NULL) {
        if (strcmp(cur->key, seatId) == 0) {
            if (prev == NULL) table->buckets[index] = cur->next;
            else prev->next = cur->next;
            free(cur->value);
            free(cur);
            table->count--;
            return 1;
        }
        prev = cur;
        cur = cur->next;
    }
    return 0;
}

int deleteReservationFromHash(ReservationHashTable *table, const char *resId) {
    unsigned int index;
    ReservationHashNode *cur;
    ReservationHashNode *prev = NULL;
    if (table == NULL || isBlank(resId)) return 0;
    index = hashString(resId);
    cur = table->buckets[index];
    while (cur != NULL) {
        if (strcmp(cur->key, resId) == 0) {
            if (prev == NULL) table->buckets[index] = cur->next;
            else prev->next = cur->next;
            free(cur->value);
            free(cur);
            table->count--;
            return 1;
        }
        prev = cur;
        cur = cur->next;
    }
    return 0;
}

void destroyStudentHashTable(StudentHashTable *table) {
    int i;
    StudentHashNode *cur;
    StudentHashNode *next;
    if (table == NULL) return;
    for (i = 0; i < HASH_TABLE_SIZE; i++) {
        cur = table->buckets[i];
        while (cur != NULL) {
            next = cur->next;
            free(cur->value);
            free(cur);
            cur = next;
        }
        table->buckets[i] = NULL;
    }
    table->count = 0;
}

void destroySeatHashTable(SeatHashTable *table) {
    int i;
    SeatHashNode *cur;
    SeatHashNode *next;
    if (table == NULL) return;
    for (i = 0; i < HASH_TABLE_SIZE; i++) {
        cur = table->buckets[i];
        while (cur != NULL) {
            next = cur->next;
            free(cur->value);
            free(cur);
            cur = next;
        }
        table->buckets[i] = NULL;
    }
    table->count = 0;
}

void destroyReservationHashTable(ReservationHashTable *table) {
    int i;
    ReservationHashNode *cur;
    ReservationHashNode *next;
    if (table == NULL) return;
    for (i = 0; i < HASH_TABLE_SIZE; i++) {
        cur = table->buckets[i];
        while (cur != NULL) {
            next = cur->next;
            free(cur->value);
            free(cur);
            cur = next;
        }
        table->buckets[i] = NULL;
    }
    table->count = 0;
}
