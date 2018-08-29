#ifndef PERFORMANCE_LOGGER_H
#define PERFORMANCE_LOGGER_H

#include <fstream>
#include <string>

class PerformanceLogger {
public:
    PerformanceLogger(const std::string &file_name);
    ~PerformanceLogger();

    void Log(size_t txs_completed, size_t time);
private:
    std::fstream fs_;
};


#endif // PERFORMANCE_LOGGER_H
