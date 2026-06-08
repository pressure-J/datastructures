#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "types.h"

unsigned int hashString(const char *key);

int initStudentHashTable(StudentHashTable *table);
int initSeatHashTable(SeatHashTable *table);
int initReservationHashTable(ReservationHashTable *table);

int insertStudentToHash(StudentHashTable *table, const Student *student);
int insertSeatToHash(SeatHashTable *table, const Seat *seat);
int insertReservationToHash(ReservationHashTable *table, const Reservation *res);

Student *findStudentInHash(StudentHashTable *table, const char *studentId);
Seat *findSeatInHash(SeatHashTable *table, const char *seatId);
Reservation *findReservationInHash(ReservationHashTable *table, const char *resId);

int deleteStudentFromHash(StudentHashTable *table, const char *studentId);
int deleteSeatFromHash(SeatHashTable *table, const char *seatId);
int deleteReservationFromHash(ReservationHashTable *table, const char *resId);

void destroyStudentHashTable(StudentHashTable *table);
void destroySeatHashTable(SeatHashTable *table);
void destroyReservationHashTable(ReservationHashTable *table);

#endif
