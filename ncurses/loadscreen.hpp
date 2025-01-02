//
// Created by nbollom on 2/01/25.
//

#pragma once
#include <filesystem>
#include <vector>
#include <string>
#include "ncursesview.hpp"

class LoadScreen final : public NCursesView {

    int current_index = 0;
    std::filesystem::path path;
    std::vector<std::filesystem::path> files;
    bool has_error = false;

    void ChangeDir(const std::filesystem::path& new_path);

public:
    LoadScreen(const std::shared_ptr<Game>& game, const MessageHandler& message_handler);
    void Render() override;
    void HandleKey(int key) override;

};
