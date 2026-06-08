#ifndef SEAT_H
#define SEAT_H

#include "hashtable.h"
#include "linkedlist.h"

ErrorCode getAvailableSeats(SeatHashTable *seatTable,
                            ReservationHashTable *resTable,
                            const char *roomId,
                            time_t startTime, time_t endTime,
                            Seat **resultList, int *count);
ErrorCode getSeatInfo(SeatHashTable *table, const char *seatId,
                      Seat *result);
ErrorCode updateSeatStatus(SeatHashTable *table, const char *seatId,
                           SeatStatus newStatus);
ErrorCode recommendSeats(SeatHashTable *seatTable,
                         ReservationHashTable *resTable,
                         const char *studentId,
                         time_t startTime, time_t endTime,
                         Seat **resultList, int *count);
ErrorCode getSeatLayout(SeatHashTable *table, const char *roomId,
                        Seat ***layout, int *rows, int *cols);
void destroySeatLayout(Seat **layout, int rows, int cols);

ErrorCode addSeatBaseData(SeatHashTable *table, const Seat *seat);
ErrorCode updateSeatBaseData(SeatHashTable *table, const char *seatId,
                             const Seat *newInfo);
ErrorCode addStudyRoomBaseData(StudyRoom **roomList, const StudyRoom *room);
ErrorCode updateStudyRoomBaseData(StudyRoom *roomList, const char *roomId,
                                  const StudyRoom *newInfo);
int loadSeatTestData(SeatHashTable *table);
int hasTimeConflict(ReservationHashTable *table, const char *seatId,
                    time_t startTime, time_t endTime);

#endif
