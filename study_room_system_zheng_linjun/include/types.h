#ifndef TYPES_H
#define TYPES_H

#include <time.h>

#define MAX_STUDENT_ID_LEN 20
#define MAX_NAME_LEN 50
#define MAX_PHONE_LEN 15
#define MAX_DEPT_LEN 100
#define MAX_ROOM_ID_LEN 20
#define MAX_ROOM_NAME_LEN 50
#define MAX_LOCATION_LEN 100
#define MAX_TIME_LEN 10
#define MAX_SEAT_ID_LEN 30
#define MAX_RES_ID_LEN 30
#define MAX_REASON_LEN 200
#define HASH_TABLE_SIZE 101

typedef enum {
    SEAT_AVAILABLE,
    SEAT_RESERVED,
    SEAT_OCCUPIED,
    SEAT_MAINTENANCE,
    SEAT_DISABLED
} SeatStatus;

typedef enum {
    RES_PENDING,
    RES_CHECKED_IN,
    RES_COMPLETED,
    RES_CANCELLED,
    RES_EXPIRED,
    RES_TIMEOUT
} ReservationStatus;

typedef enum {
    SUCCESS = 0,
    ERR_STUDENT_NOT_FOUND,
    ERR_SEAT_NOT_FOUND,
    ERR_SEAT_UNAVAILABLE,
    ERR_TIME_CONFLICT,
    ERR_RESERVATION_NOT_FOUND,
    ERR_INVALID_TIME,
    ERR_CREDIT_INSUFFICIENT,
    ERR_CHECK_IN_TIMEOUT,
    ERR_MEMORY_ALLOC,
    ERR_SYSTEM_ERROR
} ErrorCode;

typedef struct Student {
    char studentId[MAX_STUDENT_ID_LEN];
    char name[MAX_NAME_LEN];
    char phone[MAX_PHONE_LEN];
    char department[MAX_DEPT_LEN];
    int creditScore;
    time_t registerTime;
    struct Student *next;
} Student;

typedef struct StudyRoom {
    char roomId[MAX_ROOM_ID_LEN];
    char roomName[MAX_ROOM_NAME_LEN];
    int capacity;
    char location[MAX_LOCATION_LEN];
    char openTime[MAX_TIME_LEN];
    char closeTime[MAX_TIME_LEN];
    int isActive;
    struct StudyRoom *next;
} StudyRoom;

typedef struct Seat {
    char seatId[MAX_SEAT_ID_LEN];
    char roomId[MAX_ROOM_ID_LEN];
    int row;
    int column;
    SeatStatus status;
    char currentStudent[MAX_STUDENT_ID_LEN];
    time_t lastActiveTime;
    struct Seat *next;
} Seat;

typedef struct Reservation {
    char reservationId[MAX_RES_ID_LEN];
    char studentId[MAX_STUDENT_ID_LEN];
    char seatId[MAX_SEAT_ID_LEN];
    char roomId[MAX_ROOM_ID_LEN];
    time_t reserveTime;
    time_t startTime;
    time_t endTime;
    time_t checkInTime;
    time_t checkOutTime;
    ReservationStatus status;
    char cancelReason[MAX_REASON_LEN];
    struct Reservation *next;
} Reservation;

typedef struct StudentHashNode {
    char key[MAX_STUDENT_ID_LEN];
    Student *value;
    struct StudentHashNode *next;
} StudentHashNode;

typedef struct SeatHashNode {
    char key[MAX_SEAT_ID_LEN];
    Seat *value;
    struct SeatHashNode *next;
} SeatHashNode;

typedef struct ReservationHashNode {
    char key[MAX_RES_ID_LEN];
    Reservation *value;
    struct ReservationHashNode *next;
} ReservationHashNode;

typedef struct {
    StudentHashNode *buckets[HASH_TABLE_SIZE];
    int count;
} StudentHashTable;

typedef struct {
    SeatHashNode *buckets[HASH_TABLE_SIZE];
    int count;
} SeatHashTable;

typedef struct {
    ReservationHashNode *buckets[HASH_TABLE_SIZE];
    int count;
} ReservationHashTable;

const char *getErrorMessage(ErrorCode code);

#endif
