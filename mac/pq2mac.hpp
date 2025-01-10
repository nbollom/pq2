//
// Created by nbollom on 12/12/18.
//

#pragma once

#include <pq2gui.hpp>
#include <memory>
#include <functional>

class MacGUI : public GUI {
private:
	std::function<void(std::string)> message_handler;
	
public:
	explicit MacGUI(std::shared_ptr<Game> game);
	~MacGUI() override;
	void Run() override;
	
	void ShowMainMenu() override;
	void ShowCharacterCreator() override;
	void ShowGameScreen() override;
	void Close() override;
	void HandleMessage(std::string message);
};

