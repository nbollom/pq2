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

    const Class get_random_class(std::shared_ptr<std::mt19937_64> engine);

    const std::vector<Class> get_class_list();

}

#endif //PQ2_CLASSES_H
