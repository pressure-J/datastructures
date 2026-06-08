#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "seat.h"

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

static int isReservationBlocking(ReservationStatus status) {
    return status == RES_PENDING || status == RES_CHECKED_IN;
}

int hasTimeConflict(ReservationHashTable *table, const char *seatId,
                    time_t startTime, time_t endTime) {
    int i;
    ReservationHashNode *node;
    if (table == NULL || isBlank(seatId) || startTime >= endTime) {
        return 1;
    }
    for (i = 0; i < HASH_TABLE_SIZE; i++) {
        node = table->buckets[i];
        while (node != NULL) {
            Reservation *res = node->value;
            if (res != NULL &&
                strcmp(res->seatId, seatId) == 0 &&
                isReservationBlocking(res->status) &&
                startTime < res->endTime &&
                endTime > res->startTime) {
                return 1;
            }
            node = node->next;
        }
    }
    return 0;
}

ErrorCode getAvailableSeats(SeatHashTable *seatTable,
                            ReservationHashTable *resTable,
                            const char *roomId,
                            time_t startTime, time_t endTime,
                            Seat **resultList, int *count) {
    int i;
    int total = 0;
    Seat *list = NULL;
    SeatHashNode *node;

    if (seatTable == NULL || resTable == NULL || isBlank(roomId) ||
        startTime >= endTime || resultList == NULL || count == NULL) {
        return ERR_INVALID_TIME;
    }

    for (i = 0; i < HASH_TABLE_SIZE; i++) {
        node = seatTable->buckets[i];
        while (node != NULL) {
            Seat *seat = node->value;
            if (seat != NULL &&
                strcmp(seat->roomId, roomId) == 0 &&
                seat->status == SEAT_AVAILABLE &&
                !hasTimeConflict(resTable, seat->seatId, startTime, endTime)) {
                if (!insertSeat(&list, seat)) {
                    destroySeatList(&list);
                    *resultList = NULL;
                    *count = 0;
                    return ERR_MEMORY_ALLOC;
                }
                total++;
            }
            node = node->next;
        }
    }

    *resultList = list;
    *count = total;
    return SUCCESS;
}

ErrorCode getSeatInfo(SeatHashTable *table, const char *seatId,
                      Seat *result) {
    Seat *seat = findSeatInHash(table, seatId);
    if (seat == NULL) return ERR_SEAT_NOT_FOUND;
    if (result != NULL) {
        *result = *seat;
        result->next = NULL;
    }
    return SUCCESS;
}

ErrorCode updateSeatStatus(SeatHashTable *table, const char *seatId,
                           SeatStatus newStatus) {
    Seat *seat = findSeatInHash(table, seatId);
    if (seat == NULL) return ERR_SEAT_NOT_FOUND;
    if (newStatus < SEAT_AVAILABLE || newStatus > SEAT_DISABLED) {
        return ERR_SYSTEM_ERROR;
    }
    seat->status = newStatus;
    if (newStatus == SEAT_AVAILABLE) {
        seat->currentStudent[0] = '\0';
    }
    seat->lastActiveTime = time(NULL);
    return SUCCESS;
}

ErrorCode recommendSeats(SeatHashTable *seatTable,
                         ReservationHashTable *resTable,
                         const char *studentId,
                         time_t startTime, time_t endTime,
                         Seat **resultList, int *count) {
    int i;
    int total = 0;
    Seat *list = NULL;
    SeatHashNode *node;
    (void)studentId;

    if (seatTable == NULL || resTable == NULL || startTime >= endTime ||
        resultList == NULL || count == NULL) {
        return ERR_INVALID_TIME;
    }

    for (i = 0; i < HASH_TABLE_SIZE; i++) {
        node = seatTable->buckets[i];
        while (node != NULL) {
            Seat *seat = node->value;
            if (seat != NULL &&
                seat->status == SEAT_AVAILABLE &&
                !hasTimeConflict(resTable, seat->seatId, startTime, endTime)) {
                if (!insertSeat(&list, seat)) {
                    destroySeatList(&list);
                    *resultList = NULL;
                    *count = 0;
                    return ERR_MEMORY_ALLOC;
                }
                total++;
            }
            node = node->next;
        }
    }

    *resultList = list;
    *count = total;
    return SUCCESS;
}

ErrorCode getSeatLayout(SeatHashTable *table, const char *roomId,
                        Seat ***layout, int *rows, int *cols) {
    int i;
    int r;
    int maxRow = 0;
    int maxCol = 0;
    SeatHashNode *node;
    Seat **grid;

    if (table == NULL || isBlank(roomId) || layout == NULL ||
        rows == NULL || cols == NULL) {
        return ERR_SYSTEM_ERROR;
    }

    for (i = 0; i < HASH_TABLE_SIZE; i++) {
        node = table->buckets[i];
        while (node != NULL) {
            Seat *seat = node->value;
            if (seat != NULL && strcmp(seat->roomId, roomId) == 0) {
                if (seat->row > maxRow) maxRow = seat->row;
                if (seat->column > maxCol) maxCol = seat->column;
            }
            node = node->next;
        }
    }

    if (maxRow <= 0 || maxCol <= 0) {
        *layout = NULL;
        *rows = 0;
        *cols = 0;
        return ERR_SEAT_NOT_FOUND;
    }

    grid = (Seat **)calloc((size_t)maxRow, sizeof(Seat *));
    if (grid == NULL) return ERR_MEMORY_ALLOC;

    for (r = 0; r < maxRow; r++) {
        grid[r] = (Seat *)calloc((size_t)maxCol, sizeof(Seat));
        if (grid[r] == NULL) {
            while (r > 0) {
                r--;
                free(grid[r]);
            }
            free(grid);
            return ERR_MEMORY_ALLOC;
        }
    }

    for (i = 0; i < HASH_TABLE_SIZE; i++) {
        node = table->buckets[i];
        while (node != NULL) {
            Seat *seat = node->value;
            if (seat != NULL &&
                strcmp(seat->roomId, roomId) == 0 &&
                seat->row > 0 && seat->column > 0) {
                grid[seat->row - 1][seat->column - 1] = *seat;
                grid[seat->row - 1][seat->column - 1].next = NULL;
            }
            node = node->next;
        }
    }

    *layout = grid;
    *rows = maxRow;
    *cols = maxCol;
    return SUCCESS;
}

void destroySeatLayout(Seat **layout, int rows, int cols) {
    int r;
    (void)cols;
    if (layout == NULL) return;
    for (r = 0; r < rows; r++) {
        free(layout[r]);
    }
    free(layout);
}

ErrorCode addSeatBaseData(SeatHashTable *table, const Seat *seat) {
    Seat temp;
    if (table == NULL || seat == NULL || isBlank(seat->seatId) || isBlank(seat->roomId)) {
        return ERR_SYSTEM_ERROR;
    }
    if (findSeatInHash(table, seat->seatId) != NULL) {
        return ERR_SYSTEM_ERROR;
    }
    temp = *seat;
    temp.next = NULL;
    temp.currentStudent[0] = '\0';
    if (temp.status < SEAT_AVAILABLE || temp.status > SEAT_DISABLED) {
        temp.status = SEAT_AVAILABLE;
    }
    if (temp.lastActiveTime == 0) {
        temp.lastActiveTime = time(NULL);
    }
    return insertSeatToHash(table, &temp) ? SUCCESS : ERR_MEMORY_ALLOC;
}

ErrorCode updateSeatBaseData(SeatHashTable *table, const char *seatId,
                             const Seat *newInfo) {
    Seat *seat = findSeatInHash(table, seatId);
    if (seat == NULL) return ERR_SEAT_NOT_FOUND;
    if (newInfo == NULL) return ERR_SYSTEM_ERROR;
    copyString(seat->roomId, sizeof(seat->roomId), newInfo->roomId);
    seat->row = newInfo->row;
    seat->column = newInfo->column;
    seat->status = newInfo->status;
    return SUCCESS;
}

ErrorCode addStudyRoomBaseData(StudyRoom **roomList, const StudyRoom *room) {
    StudyRoom temp;
    if (roomList == NULL || room == NULL || isBlank(room->roomId)) {
        return ERR_SYSTEM_ERROR;
    }
    if (findStudyRoom(*roomList, room->roomId) != NULL) {
        return ERR_SYSTEM_ERROR;
    }
    temp = *room;
    temp.next = NULL;
    temp.isActive = temp.isActive ? 1 : 0;
    return insertStudyRoom(roomList, &temp) ? SUCCESS : ERR_MEMORY_ALLOC;
}

ErrorCode updateStudyRoomBaseData(StudyRoom *roomList, const char *roomId,
                                  const StudyRoom *newInfo) {
    StudyRoom *room = findStudyRoom(roomList, roomId);
    if (room == NULL) return ERR_SYSTEM_ERROR;
    if (newInfo == NULL) return ERR_SYSTEM_ERROR;
    copyString(room->roomName, sizeof(room->roomName), newInfo->roomName);
    room->capacity = newInfo->capacity;
    copyString(room->location, sizeof(room->location), newInfo->location);
    copyString(room->openTime, sizeof(room->openTime), newInfo->openTime);
    copyString(room->closeTime, sizeof(room->closeTime), newInfo->closeTime);
    room->isActive = newInfo->isActive ? 1 : 0;
    return SUCCESS;
}

int loadSeatTestData(SeatHashTable *table) {
    Seat seats[] = {
        {"A101-001", "A101", 1, 1, SEAT_AVAILABLE, "", 0, NULL},
        {"A101-002", "A101", 1, 2, SEAT_AVAILABLE, "", 0, NULL},
        {"A101-003", "A101", 1, 3, SEAT_MAINTENANCE, "", 0, NULL},
        {"A101-004", "A101", 2, 1, SEAT_AVAILABLE, "", 0, NULL},
        {"A101-005", "A101", 2, 2, SEAT_DISABLED, "", 0, NULL},
        {"B201-001", "B201", 1, 1, SEAT_AVAILABLE, "", 0, NULL}
    };
    int i;
    int n = (int)(sizeof(seats) / sizeof(seats[0]));
    for (i = 0; i < n; i++) {
        if (addSeatBaseData(table, &seats[i]) != SUCCESS) return 0;
    }
    return 1;
}
