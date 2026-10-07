#include "logger.h"
#include <stdio.h>

/**
 * @attention 这一个版本的log只能向控制台打印
 */
void logger_log(struct logger *logger, const char *message) {
        printf("[%s] %s\n", logger->name, message);
}

/**
 * @todo 改成支持两种实现
 *  1.控制台打印，本程logger_log的printf
 *  2. 文件打印，向指定文件写入日志
 */
int main() {
        struct logger my_logger = {
            .name = "MyLogger",
        };
        logger_log(&my_logger, "Hello, world!");
        return 0;
}