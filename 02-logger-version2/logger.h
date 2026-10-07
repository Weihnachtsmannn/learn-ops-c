#ifndef LOGGER_H
#define LOGGER_H

struct logger;

/* step1 */
struct logger_ops {
        void (*log)(struct logger *logger, const char *message);
};

/**
 * @brief 这个版本中，对logger有两种实现
 *   1. 实现了向控制台打印 logger_printf
 *   2. 实现了向文件打印 logger_file
 * @todo 但是如何访问这两个对象logger_printf和logger_file，
 *       详细见version3
 */
struct logger {
        const char *name;
        struct logger_ops *ops; /* step2 */
};

/* step3 */
void logger_log(struct logger *logger, const char *message);

#endif