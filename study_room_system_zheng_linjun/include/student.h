#ifndef STUDENT_H
#define STUDENT_H

#include "hashtable.h"

ErrorCode registerStudent(StudentHashTable *table, const Student *student);
ErrorCode loginStudent(StudentHashTable *table, const char *studentId,
                       const char *password, Student *result);
ErrorCode getStudentInfo(StudentHashTable *table, const char *studentId,
                         Student *result);
ErrorCode updateStudentInfo(StudentHashTable *table, const char *studentId,
                            const Student *newInfo);
ErrorCode deductCredit(StudentHashTable *table, const char *studentId,
                       int points);
ErrorCode getCreditScore(StudentHashTable *table, const char *studentId,
                         int *score);
int loadStudentTestData(StudentHashTable *table);

#endif
