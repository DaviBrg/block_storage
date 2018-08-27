#ifndef TXENTRY_H
#define TXENTRY_H

#include <memory>

enum TxType {
    TxInsert,
    TxRead,
    TxUpdate,
    TxDelete
};

template <typename Key, typename Value>
class TxEntry {
public:
    TxEntry(TxType type, Key key, std::unique_ptr<Value> &&value = nullptr):
    type_(type), key_(key), value_(std::move(value)){}

    TxType type() {return type_;}
    Key key() {return key_;}
    Value* value() {return value_.get();}

private:
    TxType type_;
    Key key_;
    std::unique_ptr<Value> value_;

};

#endif // TXENTRY_H
