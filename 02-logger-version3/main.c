/**
 * @brief 四种方式使用不同的 logger 对象
 *
 * 1. 使用 extern 声明全局对象
 *
 *    在 logger.h 或对应的实现头文件中声明：
 *      extern struct logger logger_printf;
 *      extern struct logger logger_file;
 *
 *    在对应的 .c 文件中定义对象，然后在 main 中直接使用：
 *      logger_log(&logger_printf, "Hello, console!");
 *      logger_log(&logger_file, "Hello, file!");
 *
 *    对象在整个程序运行期间存在。
 *
 * 2. 通过获取函数访问已有对象
 *
 *    在 logger_printf.h 和 logger_file.h 中分别声明：
 *      struct logger *logger_printf_get(void);
 *      struct logger *logger_file_get(void);
 *
 *    对象可以在对应的 .c 文件中定义为 static，
 *    获取函数返回该对象的地址。
 *
 *    在 main 中使用：
 *      struct logger *console_logger = logger_printf_get();
 *      struct logger *file_logger = logger_file_get();
 *
 *      logger_log(console_logger, "Hello, console!");
 *      logger_log(file_logger, "Hello, file!");
 *
 *    获取函数不创建新对象；调用者不负责释放这些对象。
 *
 * 3. 初始化调用者提供的对象
 *
 *    在 logger_printf.h 和 logger_file.h 中分别声明：
 *      int logger_printf_init(struct logger *logger);
 *      int logger_file_init(struct logger *logger);
 *
 *    调用者创建对象，初始化函数负责设置字段、绑定操作表，
 *    并初始化具体实现需要的资源。
 *
 *    在 main 中使用，假设成功返回 0，失败返回非 0：
 *      struct logger console_logger;
 *      struct logger file_logger;
 *
 *      if (logger_printf_init(&console_logger) != 0)
 *          return 1;
 *
 *      if (logger_file_init(&file_logger) != 0) {
 *          logger_deinit(&console_logger);
 *          return 1;
 *      }
 *
 *      logger_log(&console_logger, "Hello, console!");
 *      logger_log(&file_logger, "Hello, file!");
 *
 *      logger_deinit(&file_logger);
 *      logger_deinit(&console_logger);
 *
 *    如果初始化获取了资源，需要提供清理函数，例如：
 *      void logger_deinit(struct logger *logger);
 *
 *    清理函数释放文件等内部资源，但不 free(logger)，
 *    因为对象本身由调用者提供。
 *
 * 4. 动态创建对象，并显式销毁
 *
 *    在 logger_printf.h 和 logger_file.h 中分别声明：
 *      int logger_printf_create(struct logger **logger);
 *      int logger_file_create(struct logger **logger);
 *
 *    提供统一销毁函数：
 *      void logger_destroy(struct logger *logger);
 *
 *    create 函数分配并初始化对象，通过二级指针返回对象地址。
 *    假设成功返回 0，失败返回非 0，且失败时清理已获取的资源。
 *
 *    在 main 中使用：
 *      struct logger *console_logger = NULL;
 *      struct logger *file_logger = NULL;
 *
 *      if (logger_printf_create(&console_logger) != 0)
 *          return 1;
 *
 *      if (logger_file_create(&file_logger) != 0) {
 *          logger_destroy(console_logger);
 *          return 1;
 *      }
 *
 *      logger_log(console_logger, "Hello, console!");
 *      logger_log(file_logger, "Hello, file!");
 *
 *      logger_destroy(file_logger);
 *      logger_destroy(console_logger);
 *
 *    destroy 函数先清理具体实现的内部资源，再释放对象本身。
 *    只能用于与其约定匹配的动态创建对象。
 */

 