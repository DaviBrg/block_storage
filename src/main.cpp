//#include <unistd.h>

//#include "persistent_list.h"

//constexpr size_t kDataSize = 1000000;
//constexpr size_t kMetaDataSize = 24;
//constexpr size_t kPoolSize = 4000000000;
//constexpr size_t kPracticalPoolSize = 3500000000;
//constexpr size_t kNumObjToWrite = kPracticalPoolSize/(kDataSize+kMetaDataSize);
//constexpr double kPercentNumObjToWrite = ((double)kNumObjToWrite)/100.0;

//struct Tuple {
//    uint64_t id;
//    char data[kDataSize];
//};

//int main(int argc, char *argv[]) {

//    const char* path = "/mnt/mem/pmem_content";
//    const char* layout = "queue";

//    pmem::obj::pool<PersistentList<Tuple>> pool;


//    bool first_time = false;


//    if (access(path, F_OK) != 0) {
//        pool = pmem::obj::pool<PersistentList<Tuple>>::create(
//                                                path, layout, kPoolSize,
//                                                S_IWUSR | S_IRUSR);
//        first_time = true;
//        }
//    else {
//        pool = pmem::obj::pool<PersistentList<Tuple>>::open(path, layout);
//        first_time = false;
//    }

//    auto recovery_manager = pool.get_root();

//    std::unordered_map<uint64_t,
//                    pmem::obj::persistent_ptr<ListNode<Tuple>>> lookup_table;
//    std::unordered_map<uint64_t, Tuple> data_base;


//    if (first_time) {
//        Tuple t = {0};
//        std::vector<Tuple> intention_list;
//        intention_list.push_back(t);
//        intention_list.push_back(t);
//        intention_list.push_back(t);


//        for (uint64_t i = 0; i < kNumObjToWrite; i +=3) {
//            intention_list[0].id = i;
//            intention_list[1].id = i+1;
//            intention_list[2].id = i+2;
//            recovery_manager->Commit(pool, intention_list, lookup_table);
//            std::cout  <<  (((double)i)/kPercentNumObjToWrite)<< "%" << std::endl;
//        }
//    }
//    else {
//        recovery_manager->RecoverNVM(pool, data_base, lookup_table);
//    }



//    pool.close();

//    return 0;
//}
#include "workload_generator.h"
#include <iostream>

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
int main(int argc, char **argv) {
    TxEntry<size_t, double> entry(TxRead, 10, std::unique_ptr<double>(new double(10)));
    return 0;
}
