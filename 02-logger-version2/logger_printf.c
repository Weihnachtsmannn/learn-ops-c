#include "logger.h"
#include <stdio.h>

/* step6 */
static void logger_printf_log(struct logger *logger, const char *message) {
        printf("[%s] %s\n", logger->name, message);
}

/* step5 */
static struct logger_ops logger_printf_ops = {
        .log = logger_printf_log,
};

struct logger logger_printf = {
        .name = "logger_printf",
        .ops = &logger_printf_ops,
};
