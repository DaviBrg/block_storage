#include <iostream>

#include "data_base_pmem_disk.h"
#include "workload_generator.h"



class TxPrinter {
public:
  TxPrinter() = default;
  void ExecuteTransaction(std::vector<TxEntry<size_t,double>> &tx) {
      using namespace std;
      for (auto &elem : tx) {
          cout << elem.key() << " ";
      }
      cout << endl;
  }

};

struct Tuple {
    size_t id;
    char data[128];
};

constexpr size_t ntx = 20000;

#include "performance_logger.h"


int main() {
//    DataBasePmemDisk<size_t,Tuple> db_pmem_disk(1000000000, "/mnt/mem/pmem_content", "queue");
//    WorkloadGenerator<decltype(db_pmem_disk)> wg(0.05, 10, 3, &db_pmem_disk);
//    for (size_t i=0;i<ntx;i++) {
//        wg.GenerateTx();
//        std::cout << (double(i)/ntx)*100<< "%" << std::endl;
//    }

    PerformanceLogger pl("/home/davi/log");
    pl.Log(10,10);
    return 0;
}
