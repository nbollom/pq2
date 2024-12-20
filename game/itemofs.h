//
// Created by nbollom on 1/06/16.
//

#ifndef PQ2_ITEMOFS_H
#define PQ2_ITEMOFS_H

#include <string>
#include <random>
#include <memory>

namespace data {

    std::string get_random_item_of(const std::shared_ptr<std::mt19937_64>& engine);

}

#endif //PQ2_ITEMOFS_H
