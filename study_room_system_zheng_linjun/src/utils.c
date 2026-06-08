#include "types.h"

const char *getErrorMessage(ErrorCode code) {
    switch (code) {
        case SUCCESS: return "操作成功";
        case ERR_STUDENT_NOT_FOUND: return "学生不存在";
        case ERR_SEAT_NOT_FOUND: return "座位不存在";
        case ERR_SEAT_UNAVAILABLE: return "座位不可用";
        case ERR_TIME_CONFLICT: return "时间冲突";
        case ERR_RESERVATION_NOT_FOUND: return "预约不存在";
        case ERR_INVALID_TIME: return "无效时间";
        case ERR_CREDIT_INSUFFICIENT: return "信用分不足";
        case ERR_CHECK_IN_TIMEOUT: return "签到超时";
        case ERR_MEMORY_ALLOC: return "内存分配失败";
        case ERR_SYSTEM_ERROR: return "系统错误";
        default: return "未知错误";
    }
}
