//
// Created by nbollom on 29/12/24.
//

#include "gamescreen.hpp"
#include <format>
#include <ranges>

#include "romannumerals.hpp"

#define LEFT 2
#define RIGHT 78
#define TIMER_MS 100
#define TEN_SECONDS 10000

template<typename T>
void GameScreen::ShowProgress(const int line, const T progress_current, const T progress_max, const std::string& custom_label) const {
    constexpr std::array<wchar_t, 8> characters = {0, 0x258F, 0x258E, 0x258D, 0x258C, 0x258B, 0x258A, 0x2589};
    constexpr float max_progress = 76 * characters.size();
    const float base_progress = std::clamp(static_cast<float>(progress_current) / static_cast<float>(progress_max), 0.0f, 1.0f);
    const float progress = base_progress * max_progress;
    const int full_progress = static_cast<int>(progress / characters.size());
    const int remaining_progress = static_cast<int>(progress) % static_cast<int>(characters.size());
    const auto progress_str = std::wstring(full_progress, 0x2588) + characters[remaining_progress];
    mvwprintw(win, line, LEFT, "%lc", 0x258F);
    mvwprintw(win, line, RIGHT - 1, "%lc", 0x2595);
    mvwprintw(win, line, LEFT, "%ls", progress_str.c_str());
    if (!custom_label.empty()) {
        CenterAlign(win, custom_label, 40, line);
    }
    else {
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
    LeftAlign(win, std::format("Gold({}) Items({})", character.Gold, character.Inventory.size()), LEFT, 12);
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
}

void GameScreen::HandleKey(const int key) {
    if (key == 27) {
        message_handler("quit");
    }
}



