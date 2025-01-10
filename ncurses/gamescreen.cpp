//
// Created by nbollom on 29/12/24.
//

#include "gamescreen.hpp"
#include <format>
#include <ranges>

#include "plural.hpp"
#include "romannumerals.hpp"

#define LEFT 2
#define RIGHT 78
#define TEN_SECONDS 10000

template<typename T>
void GameScreen::ShowProgress(const int line, const T progress_current, const T progress_max) const {
    constexpr std::array<wchar_t, 8> characters = {0, 0x258F, 0x258E, 0x258D, 0x258C, 0x258B, 0x258A, 0x2589};
    constexpr float max_progress = 76 * characters.size();
    const float base_progress = std::clamp(static_cast<float>(progress_current) / static_cast<float>(progress_max), 0.0f, 1.0f);
    const float progress = base_progress * max_progress;
    const int full_progress = static_cast<int>(progress / characters.size());
    const int remaining_progress = static_cast<int>(progress) % static_cast<int>(characters.size());
    const auto progress_str = std::wstring(full_progress, 0x2588) + characters[remaining_progress];
    mvwprintw(win, line, LEFT, "%lc", 0x258F);
    mvwprintw(win, line, LEFT, "%ls", progress_str.c_str());
    if (show_progress_labels) {
        CenterAlign(win, std::to_string(static_cast<int>(std::round(base_progress * 100))) + "%", 40, line);
    }
}

GameScreen::GameScreen(const std::shared_ptr<Game> &game, const MessageHandler &message_handler) : NCursesView(game, message_handler){
    last_update = std::chrono::system_clock::now();
}

void GameScreen::Render() {
    const auto time = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(time - last_update).count();
    if (elapsed > TEN_SECONDS) {
        // if 10 seconds have passed since last update, the system was either sleeping or badly locked up
        // regardless we should consider that time as dead to avoid cheating by "sleep progressing"
        elapsed = TIMER_MS;
    }
    last_update = time;
    game->Tick(elapsed);
    LeftAlign(win, "Progress Quest 2", LEFT, 0);
    const auto &character = game->GetCharacter();
    LeftAlign(win, std::format("{}: lvl {} {} / {}", character.Name, character.Level, character.CharacterRace.name, character.CharacterClass.name).substr(0, 76), LEFT, 1);
    LeftAlign(win, std::format("STR({}) CON({}) DEX({}) INT({}) WIS({}) CHA({}) HP({}) MP({})", character.STR, character.CON, character.DEX, character.INT, character.WIS, character.CHA, character.MAX_HP, character.MAX_MP).substr(0, 76), LEFT, 2);
    const uint64_t max_experience = game->GetLevelUpMaxValue();
    const uint64_t needed = max_experience - character.Experience;
    LeftAlign(win, std::to_string(needed) + " XP needed for next level", LEFT, 3);
    ShowProgress(4, character.Experience, max_experience);

    LeftAlign(win, "Equipment:", LEFT, 6);
    RightAlign(win, "<F1>", RIGHT, 6);

    LeftAlign(win, "Spells:", LEFT, 8);
    RightAlign(win, "<F2>", RIGHT, 8);
    if (character.Spells.empty()) {
        LeftAlign(win, "Best: None", LEFT, 9);
    }
    else {
        data::Stack best_spell = character.Spells.front();
        for (auto &spell : character.Spells | std::ranges::views::drop(1)) {
            if (spell.count > best_spell.count) {
                best_spell = spell;
            }
        }
        LeftAlign(win, std::format("Best: {} {}", best_spell.name, GetRomanNumerals(best_spell.count)), LEFT, 9);
    }

    LeftAlign(win, "Inventory:", LEFT, 11);
    RightAlign(win, "<F3>", RIGHT, 11);
    auto items = std::accumulate(character.Inventory.begin(), character.Inventory.end(), 0, [](const int sum, const data::Stack &item) {
        return sum + item.count;
    });
    LeftAlign(win, std::format("Gold({}) Items({})", character.Gold, items), LEFT, 12);
    ShowProgress(13, game->GetEncumbrance(), game->GetEncumbranceMaxValue());

    LeftAlign(win, std::format("Plot Development: {}", character.Plot.back()), LEFT, 15);
    RightAlign(win, "<F4>", RIGHT, 15);
    ShowProgress(16, character.CurrentPlotProgress, game->GetPlotMaxValue());

    if (character.Quests.empty()) {
        LeftAlign(win, "Quest: None", LEFT, 18);
        ShowProgress(19, 0, 100);
    }
    else {
        LeftAlign(win, std::format("Quest: {}", character.Quests.back().label).substr(0, 76), LEFT, 18);
        ShowProgress(19, character.CurrentQuestProgress, character.MaxQuestProgress);
    }
    RightAlign(win, "<F5>", RIGHT, 18);

    LeftAlign(win, character.CurrentActionLabel.substr(0, 76), LEFT, 21);
    ShowProgress(22, character.CurrentProgress, character.MaxProgress);

    LeftAlign(win, "<p> Toggle %", LEFT, 23);

    if (show_equipment) {
        std::vector<std::string> equipment;
        equipment.reserve(character.Equipment.size());
        for (int i = 0; i < static_cast<int>(character.Equipment.size()); i++) {
            equipment.push_back(std::format("{:11}: {}", data::EquipmentLabels[i], character.Equipment[i]));
        }
        ShowPopup("Equipment:", equipment, equipment_index);
    }

    if (show_spells) {
        std::vector<std::string> spells;
        spells.reserve(character.Spells.size());
        std::transform(character.Spells.begin(), character.Spells.end(), std::back_inserter(spells), [](const data::Stack &s) {
            return std::format("{} {}", s.name, GetRomanNumerals(s.count));
        });

        ShowPopup("Spells:", spells, spell_index);
    }

    if (show_inventory) {
        std::vector<std::string> inventory_items;
        inventory_items.reserve(character.Inventory.size());
        std::transform(character.Inventory.begin(), character.Inventory.end(), std::back_inserter(inventory_items), [](const data::Stack &s) {
            if (s.count > 1) {
                return std::format("{} {}", s.count, Plural(s.name));
            }
            return s.name;
        });

        // Make sure we reduce the selected index if items have been sold
        inventory_index = std::min(inventory_index, static_cast<int>(character.Inventory.size()) - 1);

        ShowPopup("Inventory:", inventory_items, inventory_index);
    }

    if (show_plot) {
        std::vector<std::string> plot_labels;
        plot_labels.reserve(character.Plot.size());
        std::transform(character.Plot.begin(), character.Plot.end(), std::back_inserter(plot_labels), [&](const std::string &s) {
            // Only the last item should not be marked as done so check the pointer to see if it is the last one by comparing memory location
            if (&s == &character.Plot.back()) {
                return std::format("[ ] {}", s);
            }
            return std::format("[X] {}", s);
        });

        ShowPopup("Plot:", plot_labels, plot_index);
    }

    if (show_quests) {
        std::vector<std::string> quests;
        quests.reserve(character.Quests.size());
        std::transform(character.Quests.begin(), character.Quests.end(), std::back_inserter(quests), [&](const data::Quest &q) {
            // Only the last item should not be marked as done so check the pointer to see if it is the last one by comparing memory location
            if (&q == &character.Quests.back()) {
                return std::format("[ ] {}", q.label);
            }
            return std::format("[X] {}", q.label);
        });

        ShowPopup("Quests:", quests, quest_index);
    }
}

void GameScreen::HandleKey(const int key) {
    if (key == 27) {
        ClearPopup(); // No matter the context we can clean up the popup
        if (show_equipment) {
            show_equipment = false;
        }
        else if (show_spells) {
            show_spells = false;
        }
        else if (show_inventory)
            show_inventory = false;
        else if (show_plot) {
            show_plot = false;
        }
        else if (show_quests) {
            show_quests = false;
        }
        else {
            message_handler("quit");
        }
    }
    else if (key == 'p') {
        show_progress_labels = !show_progress_labels;
    }
    else if (key == KEY_F(1)) {
        show_equipment = true;
        show_spells = false;
        show_inventory = false;
        show_plot = false;
        show_quests = false;
    }
    else if (key == KEY_F(2)) {
        show_equipment = false;
        show_spells = true;
        show_inventory = false;
        show_plot = false;
        show_quests = false;
    }
    else if (key == KEY_F(3)) {
        show_equipment = false;
        show_spells = false;
        show_inventory = true;
        show_plot = false;
        show_quests = false;
    }
    else if (key == KEY_F(4)) {
        show_equipment = false;
        show_spells = false;
        show_inventory = false;
        show_plot = true;
        show_quests = false;
    }
    else if (key == KEY_F(5)) {
        show_equipment = false;
        show_spells = false;
        show_inventory = false;
        show_plot = false;
        show_quests = true;
    }
    else if (key == KEY_DOWN) {
        const auto &character = game->GetCharacter();
        if (show_equipment) {
            equipment_index = std::min(equipment_index + 1, static_cast<int>(character.Equipment.size()) - 1);
        }
        else if (show_spells) {
            spell_index = std::min(spell_index + 1, static_cast<int>(character.Spells.size()) - 1);
        }
        else if (show_inventory) {
            inventory_index = std::min(inventory_index + 1, static_cast<int>(character.Inventory.size() - 1));
        }
        else if (show_plot) {
            plot_index = std::min(plot_index + 1, static_cast<int>(character.Plot.size() - 1));
        }
        else if (show_quests) {
            quest_index = std::min(quest_index + 1, static_cast<int>(character.Quests.size() - 1));
        }
    }
    else if (key == KEY_UP) {
        if (show_equipment) {
            equipment_index = std::max(equipment_index - 1, 0);
        }
        else if (show_spells) {
            spell_index = std::max(spell_index - 1, 0);
        }
        else if (show_inventory) {
            inventory_index = std::max(inventory_index - 1, 0);
        }
        else if (show_plot) {
            plot_index = std::max(plot_index - 1, 0);
        }
        else if (show_quests) {
            quest_index = std::max(quest_index - 1, 0);
        }
    }
}



