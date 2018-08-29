#include "performance_logger.h"


PerformanceLogger::PerformanceLogger(const std::string &file_name):
    fs_(file_name, std::ios_base::out |/*std::ios_base::app | */std::ios_base::trunc) {
    if (!fs_.is_open()) {
        throw std::runtime_error("Could not open file");
    }

}

PerformanceLogger::~PerformanceLogger() {
    try {
        fs_.flush();
        fs_.close();
    }
    catch (const std::exception&) {}
}

void PerformanceLogger::Log(size_t txs_completed, size_t time) {
    fs_ << txs_completed << ", " << time << "\n";
}

