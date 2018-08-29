//#include "pmem_log.h"

//#include <map>

//constexpr size_t kPoolSize = 2000000000;

//PmemLog::PmemLog(const char *path_) : path(path_) {
//    plp = pmemlog_create(path, kPoolSize, 0666);

//    if (plp == NULL) {
//        plp = pmemlog_open(path);
//    }
//    if (plp == NULL) {
//        perror(path);
//        exit(1);
//    }
//    pmemlog_rewind(plp);
//}

//PmemLog::~PmemLog() {
//    pmemlog_close(plp);
//}

//void PmemLog::write(const disk_pmem::LogEntry &logE) {
//    if (pmemlog_append(plp, &logE, sizeof(logE)) < 0) {
//        perror("pmemlog_append");
//        exit(1);
//    }
//}


//void PmemLog::read(void* arg, int (*function)(const void *buf, size_t len, void *arg)) {
//    pmemlog_walk(plp, 0, function, arg);
//}

