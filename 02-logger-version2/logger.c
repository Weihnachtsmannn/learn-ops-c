#include "logger.h"

/* step4 */
void logger_log(struct logger *logger, const char *message) {
        if (logger && logger->ops && logger->ops->log) {
                logger->ops->log(logger, message);
        }
}