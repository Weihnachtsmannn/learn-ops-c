#ifndef LOGGER_H
#define LOGGER_H

struct logger {
        const char *name;
};

void logger_log(struct logger *logger, const char *message);

#endif