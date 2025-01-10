//
// Created by nbollom on 22/12/24.
//

#include "character.hpp"

using namespace data;

template<>
struct std::hash<Race>
{
    std::size_t operator()(const Race& race) const noexcept
    {
        size_t hash = 17;
        hash = hash * 31 + std::hash<std::string>{}(race.name);
        for (const auto &attribute : race.attributes) {
            hash = hash * 31 + std::hash<std::string>{}(attribute);
        }
        return hash;
    }
};

template<>
struct std::hash<Class>
{
    std::size_t operator()(const Class& cls) const noexcept
    {
        size_t hash = 17;
        hash = hash * 31 + std::hash<std::string>{}(cls.name);
        for (const auto &attribute : cls.attributes) {
            hash = hash * 31 + std::hash<std::string>{}(attribute);
        }
        return hash;
    }
};

template<>
struct std::hash<Stack>
{
    std::size_t operator()(const Stack& stack) const noexcept
    {
        size_t hash = 17;
        hash = hash * 31 + std::hash<std::string>{}(stack.name);
        hash = hash * 31 + std::hash<uint64_t>{}(stack.count);
        return hash;
    }
};

template<>
struct std::hash<Monster>
{
    std::size_t operator()(const Monster& monster) const noexcept
    {
        size_t hash = 17;
        hash = hash * 31 + std::hash<std::string>{}(monster.name);
        hash = hash * 31 + std::hash<uint64_t>{}(monster.level);
        hash = hash * 31 + std::hash<std::string>{}(monster.drop);
        return hash;
    }
};

template<>
struct std::hash<Quest>
{
    std::size_t operator()(const Quest& quest) const noexcept
    {
        size_t hash = 17;
        hash = hash * 31 + std::hash<std::string>{}(quest.label);
        if (quest.monster.has_value()) {
            hash = hash * 31 + std::hash<Monster>{}(quest.monster.value());
        }
        return hash;
    }
};

template<>
struct std::hash<QueueItem>
{
    std::size_t operator()(const QueueItem& queue_item) const noexcept
    {
        size_t hash = 17;
        hash = hash * 31 + std::hash<std::string>{}(queue_item.label);
        hash = hash * 31 + std::hash<uint64_t>{}(queue_item.ms);
        hash = hash * 31 + std::hash<QueueItemType>{}(queue_item.type);
        return hash;
    }
};


uint64_t Character::CalculateHash() const {
    size_t hash = 17;
    hash = hash * 31 + std::hash<std::string>{}(Name);
    hash = hash * 31 + std::hash<Race>{}(CharacterRace);
    hash = hash * 31 + std::hash<Class>{}(CharacterClass);
    hash = hash * 31 + std::hash<uint64_t>{}(Level);
    hash = hash * 31 + std::hash<uint64_t>{}(Experience);
    hash = hash * 31 + std::hash<uint64_t>{}(STR);
    hash = hash * 31 + std::hash<uint64_t>{}(CON);
    hash = hash * 31 + std::hash<uint64_t>{}(DEX);
    hash = hash * 31 + std::hash<uint64_t>{}(INT);
    hash = hash * 31 + std::hash<uint64_t>{}(WIS);
    hash = hash * 31 + std::hash<uint64_t>{}(CHA);
    hash = hash * 31 + std::hash<uint64_t>{}(MAX_HP);
    hash = hash * 31 + std::hash<uint64_t>{}(MAX_MP);
    hash = hash * 31 + std::hash<uint64_t>{}(Gold);

    for (const auto &spell : Spells) {
        hash = hash * 31 + std::hash<Stack>{}(spell);
    }

    for (const auto &equipment : Equipment) {
        hash = hash * 31 + std::hash<std::string>{}(equipment);
    }

    for (const auto &item : Inventory) {
        hash = hash * 31 + std::hash<Stack>{}(item);
    }

    for (const auto &plot_item : Plot) {
        hash = hash * 31 + std::hash<std::string>{}(plot_item);
    }

    for (const auto &quest : Quests) {
        hash = hash * 31 + std::hash<Quest>{}(quest);
    }

    for (const auto &queue_item : Queue) {
        hash = hash * 31 + std::hash<QueueItem>{}(queue_item);
    }

    hash = hash * 31 + std::hash<CurrentActionType>{}(CurrentAction);
    hash = hash * 31 + std::hash<std::string>{}(CurrentActionLabel);
    hash = hash * 31 + std::hash<Monster>{}(CurrentMonster);
    hash = hash * 31 + std::hash<uint64_t>{}(CurrentProgress);
    hash = hash * 31 + std::hash<uint64_t>{}(MaxProgress);
    hash = hash * 31 + std::hash<uint64_t>{}(CurrentPlotProgress);
    hash = hash * 31 + std::hash<uint64_t>{}(CurrentQuestProgress);
    hash = hash * 31 + std::hash<uint64_t>{}(MaxQuestProgress);

    return hash;
}

