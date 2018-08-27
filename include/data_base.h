#ifndef DATA_BASE_H
#define DATA_BASE_H

#include "disk_log.h"

#include <map>
#include <set>

template <typename Key, typename Value>
class DataBase {
public:

    virtual void ExecuteTransaction(const std::set<int> &tx) = 0;
    virtual void Recover() = 0;
};

#endif // DATA_BASE_H

//#include <algorithm>
//#include <cmath>
//#include <iostream>
//#include <random>
//#include <string>
//#include <set>
//#include <vector>
//#include <map>

//#include "block_storage.h"
//#include "blkstorage.h"
//#include "data_base_disk.h"
//#include "disk_log.h"
//#include "workload_generator.h"

//using namespace std;

//const string kStorageFilePath = "/home/luiky/Documents/log";

//int main(int argc, char *argv[])
//{

//    WorkloadGenerator wg;
//    map<int, double> database;
//    DataBaseDisk d(kStorageFilePath);

//    auto txs= wg.Generate(78*2,0.005,5,3);
//    cout << endl << "-------------------------IDs E OBJETOS-------------------------" << endl;
//    for(auto& tx:txs)
//    {
//        for (auto& obj:tx)
//        {
//            cout << "ID: " << obj << " OBJ: " << ++database[obj] << '\t';
//        }
//        cout << endl;
//        d.executeTransaction(tx);
//    }
//    cout << endl << "------------------------COMPARAÇÃO------------------------" << endl;

//    map<int,double> before = d.getDataBase();

//    d.recover();

//    map<int,double> after = d.getDataBase();

//    for_each(after.begin(),after.end(),[&before](pair<int,double> p)
//        {
//            cout << (before[p.first] == p.second) << endl;
//        });
//    return 0;
//}
