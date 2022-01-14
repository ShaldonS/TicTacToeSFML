#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace sf;
using namespace std;


int main(int argc, char** argv) {
	sf::RenderWindow window;

	window.create(sf::VideoMode(500,500), "TicTacToe");
	window.clear(sf::Color::White);
	sf::Texture texture_back, texture_back_x, texture_back_o;
	texture_back.loadFromFile("back.png");
	texture_back_x.loadFromFile("back_x.png");
	texture_back_o.loadFromFile("back_o.png");
	sf::Sprite field(texture_back);

	sf::Font font;
	font.loadFromFile("C:/WINDOWS/Fonts/arial.ttf");
	sf::Text win;
	win.setFont(font);
	win.setFont(font);
	win.setCharacterSize(24);
	win.setFillColor(sf::Color::Black);
	win.setStyle(sf::Text::Bold);

	sf::RectangleShape squares[9];
	float xb = 5.0f, yb = 5.0f;
	for (int i(1); i < 10; ++i) {
		squares[i-1].setSize(Vector2f(136.0f, 136.0f));
		//squares[i].setFillColor(Color::Red);
		squares[i-1].setPosition(xb, yb);
		squares[i-1].setTexture(&texture_back);
		xb += 136.0f;
		if (i % 3 == 0) {
			xb = 5.0f;
			yb += 136.0f;
		}
	}

	std::vector<vector<int>> count;
	std::vector<int> to_push(9, 2);
	bool turn = true, check = false, check_2 = false;
	int last_pos = -1;

	while (window.isOpen()) {
		for (int num : to_push) {
			if (num == 2) {
				check_2 = false;
				break;
			}
			else {
				check_2 = true;
			}
		}
		if (to_push.size() == 9) {
			for (int i(0); i < to_push.size(); ++i) {
				if (to_push[i] != 2 && to_push[4] != 2) {
					if ((i % 3 == 0 && to_push[i] == to_push[i + 1] && to_push[i + 1] == to_push[i + 2])
						|| (i <= 2 && to_push[i] == to_push[i + 3] && to_push[i + 3] == to_push[i + 6])
						|| (to_push[0] == to_push[4] && to_push[4] == to_push[8])
						|| (to_push[2] == to_push[4] && to_push[4] == to_push[6])) {

							sf::String str1, str2;
							str1 = "Winner is ";
							if (to_push[last_pos] == 0) {
								str2 = "0!";
							}
							else {
								str2 = "X!";
							}
							str1 += str2;
							win.setString(str1);
							check = true;
							break;
					}
					else if (check_2){
						sf::String str;
						str = "No winner";
						win.setString(str);
						check = true;
						break;
					}
				}
				else {
					continue;
				}
			}
		}
		window.clear(sf::Color::White);

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::MouseButtonPressed) {
				for (int pos(0); pos < 9; ++pos) {
					if (Mouse::getPosition(window).x <= squares[pos].getPosition().x + 136.0f && Mouse::getPosition(window).y <= squares[pos].getPosition().y + 136.0f) {
						if (turn) {
							to_push[pos] = 1;
							squares[pos].setTexture(&texture_back_x);
							turn = false;
							last_pos = pos;
						}
						else {
							to_push[pos] = 0;
							squares[pos].setTexture(&texture_back_o);
							turn = true;
							last_pos = pos;
						}
						break;
					}
				}
			}
		}
		//std::cout << to_push.size() << "\n";
		if (to_push.size() == 9 && check) {
			window.draw(win);
		}
		else {
			for (int i(0); i < 9; ++i) {
				window.draw(squares[i]);
			}
		}
		window.display();
		
	}
	return 0;
}
