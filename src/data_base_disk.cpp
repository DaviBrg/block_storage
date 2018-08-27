//#include "data_base_disk.h"

//#include <iostream>

//DataBaseDisk::DataBaseDisk(std::string path): diskLog(path), tx_id(0)
//{}

//void DataBaseDisk::ExecuteTransaction(const std::set<int> &tx)
//{
//    int counter = 0;

//    for (auto& obj:tx) {
//        LogUpdate logU;

//        logU.obj_id = obj;
//        logU.tx_id = tx_id;
//        logU.img_after = ++dataBase[obj];
//        (logB.entries[indexBlock]).updates[counter++] = logU;

//    }
//    if(counter < 3)
//    {
//        for(int i = counter; i < 3; i++ )
//        {
//            (logB.entries[indexBlock]).updates[i].obj_id = -1;
//            (logB.entries[indexBlock]).updates[i].tx_id = -1;
//        }
//    }
//    LogCommit logC;

//    logC.tx_id = tx_id;
//    (logB.entries[indexBlock++]).commit = logC;
//    tx_id++;
//    if(indexBlock == 78)
//    {
//        indexBlock = 0;
//        diskLog.write(logB);
//    }
//}

//void DataBaseDisk::Recover()
//{
//    dataBase.clear();

//    int offsetNumber = diskLog.getOffSet();
//    int counter;
//    Block<LogBlock> block;
//    LogBlock logB;

//    for(int i = 0; i< offsetNumber; i++)
//    {
//        block =  diskLog.read(i);
//        logB = block.data();
//        for(auto& entry:logB.entries)
//        {
//            for(auto& update:entry.updates)
//            {
//                dataBase[update.obj_id] = update.img_after;
//            }
//        }
//    }

//}

//std::map<int,double> DataBaseDisk::getDataBase()
//{
//    return dataBase;
//}
