#include <unistd.h>

#include "persistent_list.h"

int main(int argc, char *argv[]) {

    const char* path = "/mnt/mem/pmem_content";
    const char* layout = "queue";

    pmem::obj::pool<PersistentList<uint64_t>> pool;

    if (access(path, F_OK) != 0) {
        pool = pmem::obj::pool<PersistentList<uint64_t>>::create(
                                                path, layout,
                                                PMEMOBJ_MIN_POOL,
                                                S_IWUSR | S_IRUSR);
        } else {
        pool = pmem::obj::pool<PersistentList<uint64_t>>::open(path, layout);
    }

    auto list = pool.get_root();

    if (list->IsEmpty()) {
        std::cout << "Empty!" << std::endl;
    }
    else {
        std::cout << "Not empty!" << std::endl;
    }

    pool.close();

    return 0;
}
