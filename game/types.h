//
// Created by nbollom on 25/05/16.
//

#ifndef PQ2_TYPES_H
#define PQ2_TYPES_H

#include <string>
#include <list>

typedef struct {
    std::string label;
    int value;
} Attribute;

typedef struct {
    std::string label;
    int level;
} Item;

typedef struct {
    std::string name;
    int level;
    std::string drop;
} Monster;

typedef struct {
    std::string name;
    std::list<std::string> attributes;
} Race;

typedef struct {
    std::string name;
    std::list<std::string> attributes;
} Class;

#endif //PQ2_TYPES_H
