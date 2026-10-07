#include "logger.h"
#include <stdio.h>

/* step8 */
static void logger_file_log(struct logger *logger, const char *message) {
        FILE *file = fopen("log.txt", "a");
        if (file) {
                fprintf(file, "[%s] %s\n", logger->name, message);
                fclose(file);
        }
}

/* step7 */
static struct logger_ops logger_file_ops = {
    .log = logger_file_log,
};

struct logger logger_file = {
    .name = "logger_file",
    .ops = &logger_file_ops,
};