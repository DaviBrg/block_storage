#include <iostream>

#include "data_base_pmem_disk.h"
#include "workload_generator.h"


struct Tuple {
    size_t id;
    char data[120];
};

constexpr size_t kPoolSize = 4000000000;
constexpr size_t kSafePoolSize = 3500000000;
constexpr size_t kTxSize = 3;
constexpr size_t n_tx = kSafePoolSize / ((sizeof(Tuple) + sizeof(ListNode<size_t,Tuple>)*kTxSize));


int main() {
    DataBasePmemDisk<size_t,Tuple> db_pmem_disk(kPoolSize, "/mnt/mem/pmem_content", "queue");
    WorkloadGenerator<decltype(db_pmem_disk)> wg(0.05, 50, kTxSize, &db_pmem_disk, "/home/davi/log.txt");
    for (size_t i=0;i<n_tx;i++) {
        wg.GenerateTx();
        std::cout << (double(i)/n_tx)*100<< "%" << std::endl;
    }
    std::cout << "Transactions Completed: " << n_tx << std::endl;
    return 0;
}



//class TxPrinter {
//public:
//  TxPrinter() = default;
//  void ExecuteTransaction(std::vector<TxEntry<size_t,double>> &tx) {
//      using namespace std;
//      for (auto &elem : tx) {
//          cout << elem.key() << " ";
//      }
//      cout << endl;
//  }

//};
