//
// Created by nbollom on 3/06/16.
//

#ifndef PQ2_NEWGAME_H
#define PQ2_NEWGAME_H

#include <stack>
#include <array>
#include <random>
#include <memory>
#include <string>
#include <functional>
#include "types.h"
#include "character.h"

class NewGame {

private:
    std::shared_ptr<std::mt19937_64> engine;
    Character character;
    std::stack<std::array<uint64_t, 6>> unrollBuffer;
    std::function<void(Character character)> callback;

    void RollEm();
    void RollStat(uint64_t *stat) const;

public:
    NewGame(std::shared_ptr<std::mt19937_64> random_engine, std::function<void(Character character)> complete_callback);
    void GenerateName();
    std::string GetName() const;
    void SetName(std::string name);
    static std::vector<std::string> GetAvailableRaces();
    std::string GetRace() const;
    void SetRace(const std::string& name);
    static std::vector<std::string> GetAvailableClasses();
    std::string GetClass() const;
    void SetClass(const std::string& name);
    void ReRoll();
    bool CanUnroll() const;
    void UnRoll();
    uint64_t GetSTR() const;
    uint64_t GetCON() const;
    uint64_t GetDEX() const;
    uint64_t GetINT() const;
    uint64_t GetWIS() const;
    uint64_t GetCHA() const;
    uint64_t GetTotal() const;
    ui::Color GetTotalColor() const;
    void ConfirmCharacter() const;
};

#endif //PQ2_NEWGAME_H
