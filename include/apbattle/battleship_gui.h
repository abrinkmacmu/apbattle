#ifndef __battleship__gui__
#define __battleship__gui__

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace bship {

enum HitStatus {
	Unknown,
	Hit,
	Miss
};

/**
 * @brief GUI manager, has interactive component for manual modes
 */
class BattleshipGui {
public:
	/**
	 * @brief Default Constructor
	 */
	BattleshipGui();


	/**
	 * @brief Handle all keyboard and mouse events
	 */
	bool handleEvents(bool& isNewClick, int& row, int& col);

	/**
	 * @brief updates plot window
	 */
	bool updateWindow();


	/**
	 * @brief sets hit map
	 */
	bool setHit(int row, int col, HitStatus status);

private:

	void updateHitMapGraphics();
	
	int nCells_;
	int displaySize_;
	int cellSize_;
	std::vector<std::vector<int>> hit_map_;
	sf::RenderWindow window_;
	sf::VertexArray vArray_;


}; // class
} // namespace

#endif
