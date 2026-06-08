#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "types.h"

Student *createStudentNode(const Student *data);
Seat *createSeatNode(const Seat *data);
Reservation *createReservationNode(const Reservation *data);
StudyRoom *createStudyRoomNode(const StudyRoom *data);

int insertStudent(Student **head, const Student *data);
int insertSeat(Seat **head, const Seat *data);
int insertReservation(Reservation **head, const Reservation *data);
int insertStudyRoom(StudyRoom **head, const StudyRoom *data);

Student *findStudent(Student *head, const char *studentId);
Seat *findSeat(Seat *head, const char *seatId);
Reservation *findReservation(Reservation *head, const char *reservationId);
StudyRoom *findStudyRoom(StudyRoom *head, const char *roomId);

int deleteStudent(Student **head, const char *studentId);
int deleteSeat(Seat **head, const char *seatId);
int deleteReservation(Reservation **head, const char *reservationId);
int deleteStudyRoom(StudyRoom **head, const char *roomId);

void destroyStudentList(Student **head);
void destroySeatList(Seat **head);
void destroyReservationList(Reservation **head);
void destroyStudyRoomList(StudyRoom **head);

int getStudentListLength(Student *head);
int getSeatListLength(Seat *head);
int getReservationListLength(Reservation *head);
int getStudyRoomListLength(StudyRoom *head);

#endif
