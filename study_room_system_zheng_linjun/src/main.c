#include <stdio.h>
#include <time.h>
#include "student.h"
#include "seat.h"

static void printSeatList(Seat *head) {
    while (head != NULL) {
        printf("%s room=%s row=%d col=%d status=%d\n",
               head->seatId, head->roomId, head->row, head->column, head->status);
        head = head->next;
    }
}

int main(void) {
    StudentHashTable studentTable;
    SeatHashTable seatTable;
    ReservationHashTable resTable;
    Student student;
    Seat *available = NULL;
    int count = 0;
    int score = 0;
    time_t now = time(NULL);

    initStudentHashTable(&studentTable);
    initSeatHashTable(&seatTable);
    initReservationHashTable(&resTable);

    loadStudentTestData(&studentTable);
    loadSeatTestData(&seatTable);

    if (getStudentInfo(&studentTable, "20240001", &student) == SUCCESS) {
        printf("student: %s %s\n", student.studentId, student.name);
    }

    deductCredit(&studentTable, "20240001", 10);
    getCreditScore(&studentTable, "20240001", &score);
    printf("credit: %d\n", score);

    getAvailableSeats(&seatTable, &resTable, "A101", now, now + 7200,
                      &available, &count);
    printf("available seats: %d\n", count);
    printSeatList(available);

    destroySeatList(&available);
    destroyStudentHashTable(&studentTable);
    destroySeatHashTable(&seatTable);
    destroyReservationHashTable(&resTable);
    return 0;
}
