//
// Created by AUGUS on 2021/8/28.
//

#include "augus_list.hh"

using namespace augus_list;

ListSortSptr ListSort::instance() {
    static ListSortSptr _sptr = nullptr;
    if (_sptr == nullptr) {
        _sptr = std::make_shared<ListSort>();
    }
    return _sptr;
}
