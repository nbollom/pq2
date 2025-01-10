//
// Created by nbollom on 19/12/24.
//

#include <nlohmann/json.hpp>
#include "jsonserialiser.hpp"
#include "game.hpp"

using namespace std;
using namespace game;
using namespace data;
using namespace file;

nlohmann::json serialise_race(const Race& race) {
    nlohmann::json json;
    json["name"] = race.name;
    for (const auto &attr : race.attributes) {
        json["attributes"].push_back(attr);
    }
    return json;
}

nlohmann::json serialise_class(const Class& cls) {
    nlohmann::json json;
    json["name"] = cls.name;
    for (const auto &attr : cls.attributes) {
        json["attributes"].push_back(attr);
    }
    return json;
}

nlohmann::json serialise_stack_item(const Stack& stack) {
    nlohmann::json json;
    json["name"] = stack.name;
    json["count"] = stack.count;
    return json;
}

nlohmann::json serialise_equipment(const std::array<std::string, 11> &equipment) {
    nlohmann::json json;
    for (size_t i = 0; i < equipment.size(); i++) {
        json[EquipmentLabels[i]] = equipment[i];
    }
    return json;
}

nlohmann::json serialise_monster(const Monster& monster) {
    nlohmann::json json;
    json["name"] = monster.name;
    json["level"] = monster.level;
    json["drop"] = monster.drop;
    return json;
}

nlohmann::json serialise_quest(const Quest& quest) {
    nlohmann::json json;
    json["label"] = quest.label;
    if (quest.monster.has_value()) {
        json["monster"] = serialise_monster(*quest.monster);
    }
    return json;
}

nlohmann::json serialise_queue_item(const QueueItem& item) {
    nlohmann::json json;
    json["type"] = item.type;
    json["label"] = item.label;
    json["ms"] = item.ms;
    return json;
}

std::string serialise(const Character &character) {
    nlohmann::json json;
    json["name"] = character.Name;
    json["race"] = serialise_race(character.CharacterRace);
    json["class"] = serialise_class(character.CharacterClass);
    json["level"] = character.Level;
    json["experience"] = character.Experience;
    json["str"] = character.STR;
    json["con"] = character.CON;
    json["dex"] = character.DEX;
    json["int"] = character.INT;
    json["wis"] = character.WIS;
    json["cha"] = character.CHA;
    json["max_hp"] = character.MAX_HP;
    json["max_mp"] = character.MAX_MP;
    json["gold"] = character.Gold;
    for (const auto &item: character.Spells) {
        json["spells"].push_back(serialise_stack_item(item));
    }
    json["equipment"] = serialise_equipment(character.Equipment);
    for (const auto &item: character.Inventory) {
        json["inventory"].push_back(serialise_stack_item(item));
    }
    for (const auto &plot_string : character.Plot) {
        json["plot"].push_back(plot_string);
    }
    for (const auto &quest: character.Quests) {
        json["quests"].push_back(serialise_quest(quest));
    }
    for (const auto &queue_item: character.Queue) {
        json["queue"].push_back(serialise_queue_item(queue_item));
    }
    json["current_action"] = character.CurrentAction;
    json["current_action_label"] = character.CurrentActionLabel;
    json["current_monster"] = serialise_monster(character.CurrentMonster);
    json["current_progress"] = character.CurrentProgress;
    json["max_progress"] = character.MaxProgress;
    json["current_plot_progress"] = character.CurrentPlotProgress;
    json["current_quest_progress"] = character.CurrentQuestProgress;
    json["max_quest_progress"] = character.MaxQuestProgress;
    json["hash"] = character.CalculateHash();
    return json.dump();
}

Race deserialize_race(const nlohmann::json &json) {
    Race race;
    race.name = json["name"].get<std::string>();
    for (const auto &attr : json["attributes"]) {
        race.attributes.push_back(attr.get<std::string>());
    }
    return race;
}

Class deserialize_class(const nlohmann::json &json) {
    Class cls;
    cls.name = json["name"].get<std::string>();
    for (const auto &attr : json["attributes"]) {
        cls.attributes.push_back(attr.get<std::string>());
    }
    return cls;
}

Stack deserialise_stack_item(nlohmann::json json) {
    return {json["name"].get<std::string>(), json["count"].get<uint64_t>()};
}

Monster deserialise_monster(nlohmann::json json) {
    Monster monster;
    monster.name = json["name"].get<std::string>();
    monster.level = json["level"].get<uint64_t>();
    monster.drop = json["drop"].get<std::string>();
    return monster;
}

Quest deserialise_quest(nlohmann::json json) {
    Quest quest;
    quest.label = json["label"].get<std::string>();
    if (json.contains("monster")) {
        quest.monster = deserialise_monster(json["monster"]);
    }
    return quest;
}

QueueItem deserialise_queue_item(nlohmann::json json) {
    QueueItem item;
    item.type = static_cast<QueueItemType>(json["type"].get<int>());
    item.label = json["label"].get<std::string>();
    item.ms = json["ms"].get<uint64_t>();
    return item;
}

void deserialize(const std::string& value, Character &character) {
    nlohmann::json json = nlohmann::json::parse(value);
    character.Name = json["name"].get<std::string>();
    character.CharacterRace = deserialize_race(json["race"]);
    character.CharacterClass = deserialize_class(json["class"]);
    character.Level = json["level"].get<uint64_t>();
    character.Experience = json["experience"].get<uint64_t>();
    character.STR = json["str"].get<uint64_t>();
    character.CON = json["con"].get<uint64_t>();
    character.DEX = json["dex"].get<uint64_t>();
    character.INT = json["int"].get<uint64_t>();
    character.WIS = json["wis"].get<uint64_t>();
    character.CHA = json["cha"].get<uint64_t>();
    character.MAX_HP = json["max_hp"].get<uint64_t>();
    character.MAX_MP = json["max_mp"].get<uint64_t>();
    character.Gold = json["gold"].get<uint64_t>();
    character.Spells.clear();
    for (const auto &item: json["spells"]) {
        character.Spells.push_back(deserialise_stack_item(item));
    }
    for (const auto &element: json["equipment"].items()) {
        const size_t index = std::ranges::find(EquipmentLabels, element.key()) - EquipmentLabels.begin();
        character.Equipment[index] = element.value();
    }
    character.Inventory.clear();
    for (const auto &item: json["inventory"]) {
        character.Inventory.push_back(deserialise_stack_item(item));
    }
    character.Plot = json["plot"].get<std::vector<std::string>>();
    character.Quests.clear();
    for (const auto &item: json["quests"]) {
        character.Quests.push_back(deserialise_quest(item));
    }
    character.Queue.clear();
    for (const auto &item: json["queue"]) {
        character.Queue.push_back(deserialise_queue_item(item));
    }
    character.CurrentAction = static_cast<CurrentActionType>(json["current_action"].get<int>());
    character.CurrentActionLabel = json["current_action_label"].get<std::string>();
    character.CurrentMonster = deserialise_monster(json["current_monster"]);
    character.CurrentProgress = json["current_progress"].get<uint64_t>();
    character.MaxProgress = json["max_progress"].get<uint64_t>();
    character.CurrentPlotProgress = json["current_plot_progress"].get<uint64_t>();
    character.CurrentQuestProgress = json["current_quest_progress"].get<uint64_t>();
    character.MaxQuestProgress = json["max_quest_progress"].get<uint64_t>();
    const auto hash = json["hash"].get<uint64_t>();
    if (hash != character.CalculateHash()) {
        throw std::runtime_error("Invalid hash");
    }
}
