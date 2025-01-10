//
// Created by nbollom on 3/06/16.
//

#pragma once

#include <stack>
#include <array>
#include <random>
#include <memory>
#include <string>
#include <functional>
#include "types.hpp"
#include "character.hpp"

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
    [[nodiscard]] std::string GetName() const;
    void SetName(std::string name);
    [[nodiscard]] static std::vector<std::string> GetAvailableRaces();
    [[nodiscard]] std::string GetRace() const;
    void SetRace(const std::string& name);
    [[nodiscard]] static std::vector<std::string> GetAvailableClasses();
    [[nodiscard]] std::string GetClass() const;
    void SetClass(const std::string& name);
    void ReRoll();
    [[nodiscard]] bool CanUnroll() const;
    void UnRoll();
    [[nodiscard]] uint64_t GetSTR() const;
    [[nodiscard]] uint64_t GetCON() const;
    [[nodiscard]] uint64_t GetDEX() const;
    [[nodiscard]] uint64_t GetINT() const;
    [[nodiscard]] uint64_t GetWIS() const;
    [[nodiscard]] uint64_t GetCHA() const;
    [[nodiscard]] uint64_t GetTotal() const;
    [[nodiscard]] ui::Color GetTotalColor() const;
    void ConfirmCharacter() const;
};
