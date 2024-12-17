//
// Created by nbollom on 2/06/16.
//

#ifndef PQ2_CLASSES_H
#define PQ2_CLASSES_H

#include <string>
#include <random>
#include <memory>
#include "types.h"

namespace data {

    Class get_random_class(const std::shared_ptr<std::mt19937_64>& engine);

    std::vector<Class> get_class_list();

}

#endif //PQ2_CLASSES_H
