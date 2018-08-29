#include <iostream>

#include "data_base_pmem_disk.h"
#include "data_base_disk.h"
#include "data_base_pmem.h"
#include "workload_generator.h"


struct Tuple {
    size_t id;
    char data[120];
};

constexpr size_t kPoolSize = 2000000000;
constexpr size_t kSafePoolSize = 1700000000;
constexpr size_t kTxExpSize = 3;
constexpr size_t const_n_tx = kSafePoolSize / ((sizeof(Tuple) + sizeof(ListNode<size_t,Tuple>)*kTxSize));


int main() {
    size_t n_tx = 20000;
//    DataBasePmemDisk<size_t,Tuple> db(kPoolSize, "/mnt/mem/pmem_content", "queue");
//    DataBaseDisk<size_t,Tuple> db("/home/luiky/block_storage");
    DataBasePmem<size_t,Tuple> db("/mnt/mem/pmem_content", kPoolSize);
    WorkloadGenerator<decltype(db)> wg(0.05, 50, disk_pmem::kTxSize, &db, "/home/luiky/log_pmem.txt");
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
