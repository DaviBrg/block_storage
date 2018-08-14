#include <unistd.h>

#include "persistent_list.h"

struct Tuple {
    uint64_t id;
    char data[500];
};

int main(int argc, char *argv[]) {

    const char* path = "/mnt/mem/pmem_content";
    const char* layout = "queue";

    pmem::obj::pool<PersistentList<Tuple>> pool;


    size_t pool_size = 4000000000;

    bool first_time = false;


    if (access(path, F_OK) != 0) {
        pool = pmem::obj::pool<PersistentList<Tuple>>::create(
                                                path, layout, pool_size,
                                                S_IWUSR | S_IRUSR);
        first_time = true;
        }
    else {
        pool = pmem::obj::pool<PersistentList<Tuple>>::open(path, layout);
        first_time = false;
    }

    auto recovery_manager = pool.get_root();

    std::unordered_map<uint64_t,
                    pmem::obj::persistent_ptr<ListNode<Tuple>>> lookup_table;
    std::unordered_map<uint64_t, Tuple> data_base;


    if (first_time) {
        Tuple t = {0};
        std::vector<Tuple> intention_list;
        intention_list.push_back(t);
        intention_list.push_back(t);
        intention_list.push_back(t);

        for (uint64_t i = 0; i < 20; i +=3) {
            intention_list[0].id = i;
            intention_list[1].id = i+1;
            intention_list[2].id = i+2;
            recovery_manager->Commit(pool, intention_list, lookup_table);
            std::cout << i << std::endl;
        }
    }
    else {
        recovery_manager->RecoverNVM(pool, data_base, lookup_table);
    }



    pool.close();

    return 0;
}
