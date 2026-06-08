#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

static int isBlank(const char *text) {
    return text == NULL || text[0] == '\0';
}

Student *createStudentNode(const Student *data) {
    Student *node;
    if (data == NULL) return NULL;
    node = (Student *)calloc(1, sizeof(Student));
    if (node == NULL) return NULL;
    *node = *data;
    node->next = NULL;
    return node;
}

Seat *createSeatNode(const Seat *data) {
    Seat *node;
    if (data == NULL) return NULL;
    node = (Seat *)calloc(1, sizeof(Seat));
    if (node == NULL) return NULL;
    *node = *data;
    node->next = NULL;
    return node;
}

Reservation *createReservationNode(const Reservation *data) {
    Reservation *node;
    if (data == NULL) return NULL;
    node = (Reservation *)calloc(1, sizeof(Reservation));
    if (node == NULL) return NULL;
    *node = *data;
    node->next = NULL;
    return node;
}

StudyRoom *createStudyRoomNode(const StudyRoom *data) {
    StudyRoom *node;
    if (data == NULL) return NULL;
    node = (StudyRoom *)calloc(1, sizeof(StudyRoom));
    if (node == NULL) return NULL;
    *node = *data;
    node->next = NULL;
    return node;
}

int insertStudent(Student **head, const Student *data) {
    Student *node = createStudentNode(data);
    if (head == NULL || node == NULL) {
        free(node);
        return 0;
    }
    node->next = *head;
    *head = node;
    return 1;
}

int insertSeat(Seat **head, const Seat *data) {
    Seat *node = createSeatNode(data);
    if (head == NULL || node == NULL) {
        free(node);
        return 0;
    }
    node->next = *head;
    *head = node;
    return 1;
}

int insertReservation(Reservation **head, const Reservation *data) {
    Reservation *node = createReservationNode(data);
    if (head == NULL || node == NULL) {
        free(node);
        return 0;
    }
    node->next = *head;
    *head = node;
    return 1;
}

int insertStudyRoom(StudyRoom **head, const StudyRoom *data) {
    StudyRoom *node = createStudyRoomNode(data);
    if (head == NULL || node == NULL) {
        free(node);
        return 0;
    }
    node->next = *head;
    *head = node;
    return 1;
}

Student *findStudent(Student *head, const char *studentId) {
    while (head != NULL) {
        if (strcmp(head->studentId, studentId) == 0) return head;
        head = head->next;
    }
    return NULL;
}

Seat *findSeat(Seat *head, const char *seatId) {
    while (head != NULL) {
        if (strcmp(head->seatId, seatId) == 0) return head;
        head = head->next;
    }
    return NULL;
}

Reservation *findReservation(Reservation *head, const char *reservationId) {
    while (head != NULL) {
        if (strcmp(head->reservationId, reservationId) == 0) return head;
        head = head->next;
    }
    return NULL;
}

StudyRoom *findStudyRoom(StudyRoom *head, const char *roomId) {
    while (head != NULL) {
        if (strcmp(head->roomId, roomId) == 0) return head;
        head = head->next;
    }
    return NULL;
}

int deleteStudent(Student **head, const char *studentId) {
    Student *cur;
    Student *prev = NULL;
    if (head == NULL || isBlank(studentId)) return 0;
    cur = *head;
    while (cur != NULL) {
        if (strcmp(cur->studentId, studentId) == 0) {
            if (prev == NULL) *head = cur->next;
            else prev->next = cur->next;
            free(cur);
            return 1;
        }
        prev = cur;
        cur = cur->next;
    }
    return 0;
}

int deleteSeat(Seat **head, const char *seatId) {
    Seat *cur;
    Seat *prev = NULL;
    if (head == NULL || isBlank(seatId)) return 0;
    cur = *head;
    while (cur != NULL) {
        if (strcmp(cur->seatId, seatId) == 0) {
            if (prev == NULL) *head = cur->next;
            else prev->next = cur->next;
            free(cur);
            return 1;
        }
        prev = cur;
        cur = cur->next;
    }
    return 0;
}

int deleteReservation(Reservation **head, const char *reservationId) {
    Reservation *cur;
    Reservation *prev = NULL;
    if (head == NULL || isBlank(reservationId)) return 0;
    cur = *head;
    while (cur != NULL) {
        if (strcmp(cur->reservationId, reservationId) == 0) {
            if (prev == NULL) *head = cur->next;
            else prev->next = cur->next;
            free(cur);
            return 1;
        }
        prev = cur;
        cur = cur->next;
    }
    return 0;
}

int deleteStudyRoom(StudyRoom **head, const char *roomId) {
    StudyRoom *cur;
    StudyRoom *prev = NULL;
    if (head == NULL || isBlank(roomId)) return 0;
    cur = *head;
    while (cur != NULL) {
        if (strcmp(cur->roomId, roomId) == 0) {
            if (prev == NULL) *head = cur->next;
            else prev->next = cur->next;
            free(cur);
            return 1;
        }
        prev = cur;
        cur = cur->next;
    }
    return 0;
}

void destroyStudentList(Student **head) {
    Student *cur;
    if (head == NULL) return;
    while (*head != NULL) {
        cur = *head;
        *head = (*head)->next;
        free(cur);
    }
}

void destroySeatList(Seat **head) {
    Seat *cur;
    if (head == NULL) return;
    while (*head != NULL) {
        cur = *head;
        *head = (*head)->next;
        free(cur);
    }
}

void destroyReservationList(Reservation **head) {
    Reservation *cur;
    if (head == NULL) return;
    while (*head != NULL) {
        cur = *head;
        *head = (*head)->next;
        free(cur);
    }
}

void destroyStudyRoomList(StudyRoom **head) {
    StudyRoom *cur;
    if (head == NULL) return;
    while (*head != NULL) {
        cur = *head;
        *head = (*head)->next;
        free(cur);
    }
}

int getStudentListLength(Student *head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

int getSeatListLength(Seat *head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

int getReservationListLength(Reservation *head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

int getStudyRoomListLength(StudyRoom *head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}
