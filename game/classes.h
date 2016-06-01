//
// Created by nbollom on 2/06/16.
//

#ifndef PQ2_CLASSES_H
#define PQ2_CLASSES_H

#include <string>
#include <random>
#include "types.h"

namespace data {

    const Class get_random_class(std::random_device *engine);

//const std::list<Class> get_class_list();
    const std::vector<Class> get_class_list();

}

#endif //PQ2_CLASSES_H
