//
// Created by nbollom on 25/05/16.
//

#ifndef PQ2_TYPES_H
#define PQ2_TYPES_H

#include <string>
#include <list>
#include <array>
#include <cstdint>

namespace data {

    struct Attribute {
        std::string label;
        int64_t value;
    };

    struct Item {
        std::string label;
        uint64_t level;
    };

    struct Monster {
        std::string name;
        uint64_t level;
        std::string drop;
    };

    struct Race {
        std::string name;
        std::list<std::string> attributes;
    };

    struct Class {
        std::string name;
        std::list<std::string> attributes;
    };

    struct Stack {
        std::string name;
        uint64_t count;
    };

    struct Quest {
        std::string label;
        Monster monster;
    };

    typedef enum {
        Weapon = 0,
        Shield,
        Helm,
        Hauberk,
        Brassairts,
        Vambraces,
        Gauntlets,
        Gambeson,
        Cuisses,
        Greaves,
        Sollerets
    } Equipment;

    static const std::array<std::string, 11> EquipmentLabels = {
            "Weapon",
            "Shield",
            "Helm",
            "Hauberk",
            "Brassairts",
            "Vambraces",
            "Gauntlets",
            "Gambeson",
            "Cuisses",
            "Greaves",
            "Sollerets"
    };

    enum QueueItemType {
        QueueItemTask = 0,
        QueueItemPlot
    };

    struct QueueItem {
        QueueItemType type = QueueItemTask;
        std::string label;
        uint64_t ms;
    };

    enum CurrentActionType {
        CurrentActionLoading = 0,
        CurrentActionKill,
        CurrentActionBuying,
        CurrentActionSelling,
        CurrentActionMarket,
        CurrentActionNone,
        CurrentActionHeading
    };

}

namespace ui {

    enum Color {
        ColorGray = 1,
        ColorSilver,
        ColorWhite,
        ColorYellow,
        ColorRed
    };

}

namespace file {

    enum LoadError {
        LoadErrorNone,
        LoadErrorFileNotFound,
        LoadErrorInvalidPermissions,
        LoadErrorNotValidSaveFile,
        LoadErrorUnknownSaveVersion
    };

    enum SaveError {
        SaveErrorNone,
        SaveErrorInvalidPath,
        SaveErrorInvalidPermissions,
        SaveErrorOutOfSpace
    };

}

namespace game {

    enum GameState {
        GameStateNone,
        GameStateReady,
        GameStateFinished
    };

}

#endif //PQ2_TYPES_H
