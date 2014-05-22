#include "stdafx.h"
#include "GUIView.h"

using namespace yaps;

GUIView::GUIView() {
}

GUIView::~GUIView() {
}

void GUIView::run() {
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Yet Another Pathfinding Simulator", 
		sf::Style::Titlebar | sf::Style::Close);
	sf::Event event;

	// Main application loop
	while (window.isOpen()) {
		
		// Event processing
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		// Rendering
		window.clear();
		window.display();
	}
}