#pragma once

const sf::Vector2f TILE_SPACING(32, 27.75f);
const sf::Vector2f START_OFFSET(16, 26.5f);

inline sf::Vector2f gridToScreen(sf::Vector2u pos) {
	sf::Vector2f res = START_OFFSET + sf::Vector2f(pos.x * TILE_SPACING.x, pos.y * TILE_SPACING.y);
	if (int(pos.y) % 2 != 0)
		res.x += 16;
	return res;
}

inline sf::Vector2u screenToGrid(sf::Vector2f pos) {
	sf::Vector2u res;
	res.y = unsigned int ((pos.y - START_OFFSET.y) / TILE_SPACING.y);
	if (res.y % 2 != 0)
		pos.x -= 16;
	res.x = unsigned int((pos.x - START_OFFSET.x) / TILE_SPACING.x);

	return res;
}

const unsigned int RED = 0;
const unsigned int BLUE = 1;

enum PlayerState {
	NONE,       // Par défaut
	DOWN,       // Au sol
	ASSISTING,  // Dans un ruck, maul, touche ou melee
	TACKLER,    // Plaqueur
	TACKLED,    // Plaqué
	AIRBORNE,   // En l'air
	INJURED     // Blessé
};

const sf::Vector2u	POS[30] = { sf::Vector2u(27,2),		sf::Vector2u(27,3),		sf::Vector2u(27,4),		sf::Vector2u(27,5),		sf::Vector2u(27,6),
								sf::Vector2u(27,7),		sf::Vector2u(27,8),		sf::Vector2u(27,9),		sf::Vector2u(27,11),	sf::Vector2u(28,14),
								sf::Vector2u(27,0),		sf::Vector2u(27,19),	sf::Vector2u(27,21),	sf::Vector2u(27,23),	sf::Vector2u(27,17),

								sf::Vector2u(35,1),		sf::Vector2u(38,1),		sf::Vector2u(35,6),		sf::Vector2u(35,2),		sf::Vector2u(34,7),
								sf::Vector2u(41,3),		sf::Vector2u(38,12),	sf::Vector2u(47,6),		sf::Vector2u(41,9),		sf::Vector2u(47,14),
								sf::Vector2u(49,2),		sf::Vector2u(35,15),	sf::Vector2u(35,21),	sf::Vector2u(38,27),	sf::Vector2u(44,24),
};

const std::string	NAM[30] = {	"Crockett", "Coles", "Franks", "Retallick", "Whitelock", "Kaino", "McCaw", "Read", "A. Smith", "Carter", "Savea", "Nonu", "Williams", "Milner-Skudder", "B. Smith",
								"Ben Arous", "Guirado", "Slimani", "Papé", "Maestri", "Dusautoir", "Le Roux", "Picamoles", "Parra", "Michalak", "Dulin", "Fofana", "Dumoulin", "Nakaitaci", "Spedding" };
const unsigned int	HEI[30] = {	193, 184, 185, 204, 203, 196, 188, 193, 171, 178, 192, 182, 194, 180, 187,
								183, 183, 178, 195, 202, 188, 197, 192, 180, 181, 176, 178, 189, 190, 186 };
const unsigned int	WEI[30] = {	116, 103, 120, 117, 114, 113, 108, 110,  85,  94, 109, 107, 108,  90,  91,
								117, 105, 110, 118, 121, 100, 116, 116,  77,  87,  82,  93,  98,  97, 100 };
const unsigned int	AGE[30] = {	33, 29, 28, 25, 27, 33, 35, 30, 27, 34, 25, 34, 30, 25, 30,
								25, 29, 26, 35, 28, 34, 27, 30, 27, 33, 26, 28, 26, 25, 30 };

						//   1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15
const unsigned int	MOV[30] = {	 3,  3,  3,  4,  4,  6,  6,  5,  8,  7,  9,  7,  8,  9,  8,
								3,  3,  3,  4,  4,  6,  6,  5,  8,  7,  9,  7,  8,  9,  8 };
						//   1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15
const unsigned int	ACT[30] = {	 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
								2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2 };
						//   1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15
const unsigned int	FOR[30] = {	80, 75, 80, 75, 75, 70, 70, 75, 45, 55, 60, 70, 70, 60, 65,
								80, 75, 80, 75, 75, 70, 70, 75, 45, 55, 60, 70, 70, 60, 65 };
						//   1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15
const unsigned int	DEF[30] = { 80, 75, 80, 75, 75, 70, 70, 75, 45, 55, 60, 70, 70, 60, 65,
								80, 75, 80, 75, 75, 70, 70, 75, 45, 55, 60, 70, 70, 60, 65 };
						//   1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15
const unsigned int	DEX[30] = {	40, 45, 40, 45, 45, 50, 50, 55, 85, 80, 65, 55, 60, 65, 70,
								40, 45, 40, 45, 45, 50, 50, 55, 85, 80, 65, 55, 60, 65, 70 };
						//   1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15
const unsigned int	KIC[30] = {	10, 10, 10, 10, 10, 10, 10, 40, 80, 85, 70, 75, 75, 70, 80,
								10, 10, 10, 10, 10, 10, 10, 40, 80, 85, 70, 75, 75, 70, 80 };
