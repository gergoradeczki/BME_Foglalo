#include "BME_Foglalo.h"

int main() {
	BME_Foglalo game;

	// Ha nincs elég hely a kijelzőn (értsd: túl nagy ablakot választottál), akkor nem tud létrejönni az ablak.
	// A Start()-ból csak akkor lép ki, ha false-ot ad vissza, vagy bezáródik az ablak
	if (game.Construct(1280, 720, 1, 1))
		game.Start();
	return 0;
}