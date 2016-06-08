//
// Created by nbollom on 25/05/16.
//

#ifndef PQ2_TYPES_H
#define PQ2_TYPES_H

#include <string>
#include <list>

typedef struct {
    std::string label;
    int8_t value;
} Attribute;

typedef struct {
    std::string label;
    int8_t level;
} Item;

typedef struct {
    std::string name;
    int8_t level;
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

typedef struct {
    std::string name;
    int count;
} Stack;

enum Color{
    Gray = 1,
    Silver,
    White,
    Yellow,
    Red
};

#endif //PQ2_TYPES_H
