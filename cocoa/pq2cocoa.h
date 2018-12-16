//
// Created by nbollom on 12/12/18.
//

#ifndef PQ2_PQ2COCOA_H
#define PQ2_PQ2COCOA_H

#include <pq2gui.h>
#include <memory>
#include <functional>

class CocoaGUI : public GUI {
private:
	std::function<void(std::string, void*)> message_handler;
	
public:
	explicit CocoaGUI(std::shared_ptr<Game> game);
	~CocoaGUI() override;
	void Run() override;
	
	void ShowMainMenu() override;
	void ShowCharacterCreator() override;
	void ShowGameScreen() override;
	void Close() override;
	void HandleMessage(std::string message, void *data);
};

#endif //PQ2_PQ2COCOA_H
