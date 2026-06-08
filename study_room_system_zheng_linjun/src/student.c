#include <string.h>
#include <time.h>
#include "student.h"

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

ErrorCode registerStudent(StudentHashTable *table, const Student *student) {
    Student temp;
    if (table == NULL || student == NULL || isBlank(student->studentId)) {
        return ERR_SYSTEM_ERROR;
    }
    if (findStudentInHash(table, student->studentId) != NULL) {
        return ERR_SYSTEM_ERROR;
    }
    temp = *student;
    temp.next = NULL;
    if (temp.creditScore <= 0) temp.creditScore = 100;
    if (temp.registerTime == 0) temp.registerTime = time(NULL);
    return insertStudentToHash(table, &temp) ? SUCCESS : ERR_MEMORY_ALLOC;
}

ErrorCode loginStudent(StudentHashTable *table, const char *studentId,
                       const char *password, Student *result) {
    Student *student = findStudentInHash(table, studentId);
    (void)password;
    if (student == NULL) return ERR_STUDENT_NOT_FOUND;
    if (result != NULL) {
        *result = *student;
        result->next = NULL;
    }
    return SUCCESS;
}

ErrorCode getStudentInfo(StudentHashTable *table, const char *studentId,
                         Student *result) {
    Student *student = findStudentInHash(table, studentId);
    if (student == NULL) return ERR_STUDENT_NOT_FOUND;
    if (result != NULL) {
        *result = *student;
        result->next = NULL;
    }
    return SUCCESS;
}

ErrorCode updateStudentInfo(StudentHashTable *table, const char *studentId,
                            const Student *newInfo) {
    Student *student = findStudentInHash(table, studentId);
    if (student == NULL) return ERR_STUDENT_NOT_FOUND;
    if (newInfo == NULL) return ERR_SYSTEM_ERROR;
    copyString(student->name, sizeof(student->name), newInfo->name);
    copyString(student->phone, sizeof(student->phone), newInfo->phone);
    copyString(student->department, sizeof(student->department), newInfo->department);
    return SUCCESS;
}

ErrorCode deductCredit(StudentHashTable *table, const char *studentId,
                       int points) {
    Student *student = findStudentInHash(table, studentId);
    if (student == NULL) return ERR_STUDENT_NOT_FOUND;
    if (points < 0) return ERR_SYSTEM_ERROR;
    student->creditScore -= points;
    if (student->creditScore < 0) student->creditScore = 0;
    return SUCCESS;
}

ErrorCode getCreditScore(StudentHashTable *table, const char *studentId,
                         int *score) {
    Student *student = findStudentInHash(table, studentId);
    if (student == NULL) return ERR_STUDENT_NOT_FOUND;
    if (score != NULL) *score = student->creditScore;
    return SUCCESS;
}

int loadStudentTestData(StudentHashTable *table) {
    Student s1 = {"20240001", "Zhang San", "13800000001", "Computer", 100, 0, NULL};
    Student s2 = {"20240002", "Li Si", "13800000002", "Software", 100, 0, NULL};
    Student s3 = {"20240003", "Wang Wu", "13800000003", "Network", 100, 0, NULL};
    return registerStudent(table, &s1) == SUCCESS &&
           registerStudent(table, &s2) == SUCCESS &&
           registerStudent(table, &s3) == SUCCESS;
}
