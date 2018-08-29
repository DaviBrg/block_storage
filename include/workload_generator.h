#ifndef WORKLOAD_GENERATOR_H
#define WORKLOAD_GENERATOR_H

#include <vector>
#include <random>
#include <cmath>
#include <chrono>

#include "txentry.h"
#include "performance_logger.h"

template <typename DBType>
class WorkloadGenerator {
    using DBKey = typename DBType::key_type;
    using DBValue = typename  DBType::value_type;
public:
    WorkloadGenerator(double skew_factor,int skew_window,
                      int tx_size, DBType *db, const std::string &log_file):
        skew_window_(skew_window),
        tx_size_(tx_size),
        r_(),
        mt_(r_()),
        exp_(skew_factor),
        db_(db),
        pl_(log_file){}

    virtual ~WorkloadGenerator() {}

    void GenerateTx() {

    std::vector<TxEntry<DBKey,DBValue>> tx;
    do {
        int obj_id = 0;
        do {
            obj_id = floor(-exp_(mt_)) + newest_;
        } while (obj_id < 0);
        tx.push_back(GenerateEntry(obj_id));
    } while (tx.size() < std::min(tx_size_, newest_));
    advance_counter_++;
    if (advance_counter_ == skew_window_) {
        advance_counter_ = 0;
        newest_++;
    }

    size_t n_tx = 0;
    auto before = std::chrono::high_resolution_clock::now();
    while (0 == n_tx) {
        n_tx= db_->ExecuteTransaction(tx);
    }
    auto after = std::chrono::high_resolution_clock::now();
    size_t ms = std::chrono::duration_cast<std::chrono::milliseconds>
            (after - before).count();
    pl_.Log(n_tx, ms);
}

private:
    TxEntry<DBKey,DBValue> GenerateEntry(int obj_id) {
        return TxEntry<DBKey,DBValue>(TxWrite, static_cast<DBKey>(obj_id),
                                      std::unique_ptr<DBValue>(new DBValue()));
    }
    int skew_window_ = 1;
    int tx_size_ = 1;
    std::random_device r_;
    std::mt19937 mt_;
    std::exponential_distribution<double> exp_;
    int advance_counter_ = 0;
    int newest_ = 1;
    DBType *db_ = nullptr;
    PerformanceLogger pl_;
};

#endif // WORKLOAD_GENERATOR_H
