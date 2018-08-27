//#include "data_base_pmem.h"

//int pmem_read(const void *buf, size_t len, void *arg) {
//    std::map<int,double>* ptr = static_cast<std::map<int,double>*> (arg);
//    const void *endp = buf + len;

//    while (buf < endp) {
//        disk_pmem::LogEntry* entry = (disk_pmem::LogEntry*)(buf);
//        for(int i = 0; i < disk_pmem::kTxSize; i++) {
//            if(entry->updates[i].tx_id != -1) {
////                (*ptr)[entry->updates[i].obj_id] = entry->updates[i].img_after;
//            }
//        }

//        buf += sizeof(disk_pmem::LogEntry);
//    }
//    return 0;
//}

//DataBasePmem::DataBasePmem(const char* path_) : path(path_), pmemLog(path), tx_id(0)  {

//}

//void DataBasePmem::executeTransaction(const std::set<double> &tx) {
//    int counter = 0;
//    disk_pmem::LogEntry logE;

//    for (auto& obj:tx) {
//        disk_pmem::LogUpdate logU;

//        logU.obj_id = obj;
//        logU.tx_id = tx_id;
//        logE.updates[counter++] = logU;
//    }
//    if(counter < disk_pmem::kTxSize) {
//        for(int i = counter; i < disk_pmem::kTxSize; i++ ) {
//            logE.updates[i].tx_id = -1;
//        }
//    }
//    disk_pmem::LogCommit logC;

//    logC.tx_id = tx_id;
//    logE.commit = logC;
//    tx_id++;
//    pmemLog.write(logE);
//}

//void DataBasePmem::recover() {
//    dataBase.clear();
//    pmemLog.read(&dataBase, pmem_read);
//}

//std::map<int,double> DataBasePmem::getDataBase() {
//    return dataBase;
//}


