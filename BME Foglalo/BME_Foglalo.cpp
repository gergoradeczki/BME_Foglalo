#include <string>
#include <iostream>
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"




class BME_Foglalo : public olc::PixelGameEngine {
public:
	BME_Foglalo() {
		// A program neve
		sAppName = "BME Foglalo";
	}
private:

	struct DecPos {
		olc::Sprite* spr = nullptr; // A sprite pointerét tárolja
		olc::Decal* dec = nullptr; // a decal pointerét tárolja
		olc::vi2d pos; // Ez alapján helyeződik el az ablakban a kép
		olc::vi2d midPoint; // A képszerkesztő alapján ez lesz a középppontja a megyéknek (ez alapján lehet kijelölni őket)
		bool highlight = false; // Ki legyen-e jelölve rajzoláskor
		olc::Pixel color = olc::RED; // A kijelölés színe
	};

	// A kijelölt megyéhez használt változók
	int minDistance = 19113; // A tényleges távolság értékéhez gyököt kell vonni belőle, de úgy viszont lassabb lesz a program.
	int minIndex = -1;
	// Ebben tárolom az egérnek a helyzetét, ez alapján dől el, melyik megye van a legközelebb
	olc::vi2d mouse = { 0,0 };

	// 20 elemű lista, ebben lesznek a képek
	DecPos magyarorszag[20];


public:
	// Csak 1-szer futnak le az itt leírt dolgok, inicializáláshoz tökéletes
	bool OnUserCreate() override {
		// betöltöm a megyéket és az országhatárt, majd eltárolom őket a tömbben
		for (int i = 0; i < 20; i++) {
			std::string str = "./Magyarorszag/smaller/";
			str += std::to_string(i);
			std::cout << str << std::endl;
			olc::Sprite* spr = new olc::Sprite(str + ".png");
			olc::Decal* dec = new olc::Decal(spr);
			magyarorszag[i] = { spr, dec, {0,0}, {0,0} };
		}

		// A képszerkesztőből kinyert adatok
		// Az értékek az eredeti képméretből származnak, ezt később átszámolom egy ciklussal
		magyarorszag[0] =  { magyarorszag[0].spr, magyarorszag[0].dec, {730, 603}, {396, 494} };
		magyarorszag[1] = { magyarorszag[1].spr, magyarorszag[1].dec, {417, 892}, {348, 273} };
		magyarorszag[2] = { magyarorszag[2].spr, magyarorszag[2].dec, {1199, 557}, {350, 395} };
		magyarorszag[3] = { magyarorszag[3].spr, magyarorszag[3].dec, {1093, 5}, {553, 377} };
		magyarorszag[4] = { magyarorszag[4].spr, magyarorszag[4].dec, {987, 729}, {314, 277} };
		magyarorszag[5] =  { magyarorszag[5].spr, magyarorszag[5].dec, {539, 422}, {255, 357} };
		magyarorszag[6] =  { magyarorszag[6].spr, magyarorszag[6].dec, {103, 237}, {407, 299} };
		magyarorszag[7] =  { magyarorszag[7].spr, magyarorszag[7].dec, {1307, 256}, {355, 410} };
		magyarorszag[8] =  { magyarorszag[8].spr, magyarorszag[8].dec, {964, 184}, {325, 294} };
		magyarorszag[9] =  { magyarorszag[9].spr, magyarorszag[9].dec, {987, 376}, {375, 373} };
		magyarorszag[10] = { magyarorszag[10].spr, magyarorszag[10].dec, {497, 325}, {289, 190} };
		magyarorszag[11] = { magyarorszag[11].spr, magyarorszag[11].dec, {790, 150}, {310, 222} };
		magyarorszag[12] = { magyarorszag[12].spr, magyarorszag[12].dec, {721, 228}, {391, 446} };
		magyarorszag[13] = { magyarorszag[13].spr, magyarorszag[13].dec, {210, 658}, {373, 456} };
		magyarorszag[14] = { magyarorszag[14].spr, magyarorszag[14].dec, {1375, 62}, {489, 334} };
		magyarorszag[15] = { magyarorszag[15].spr, magyarorszag[15].dec, {528, 715}, {277, 301} };
		magyarorszag[16] = { magyarorszag[16].spr, magyarorszag[16].dec, {5, 463}, {325, 292} };
		magyarorszag[17] = { magyarorszag[17].spr, magyarorszag[17].dec, {273, 457}, {325, 293} };
		magyarorszag[18] = { magyarorszag[18].spr, magyarorszag[18].dec, {73, 632}, {289, 301} };
		magyarorszag[19] = { magyarorszag[19].spr, magyarorszag[19].dec, {0,0}, {0,0} };

		// Minden egyes képnek a méretét megfelezem, így helyesen jelennek meg a képernyőn
		for (int i = 0; i < 20; i++) {
			int x = (magyarorszag[i].pos.x % 2 == 0) ? magyarorszag[i].pos.x / 2 : magyarorszag[i].pos.x / 2 + 1;
			int y = (magyarorszag[i].pos.y % 2 == 0) ? magyarorszag[i].pos.y / 2 : magyarorszag[i].pos.y / 2 + 1;
			int mx = (magyarorszag[i].midPoint.x % 2 == 0) ? x + magyarorszag[i].midPoint.x / 4 : x + magyarorszag[i].midPoint.x / 4 + 1;
			int my = (magyarorszag[i].midPoint.y % 2 == 0) ? y + magyarorszag[i].midPoint.y / 4 : y + magyarorszag[i].midPoint.y / 4 + 1;
			// Az új értékek beállítása
			magyarorszag[i].pos = { x,y };
			magyarorszag[i].midPoint = { mx,my };
		}

		return true;
	}
	bool OnUserUpdate(float fElapsedTime) override {
		// A kép megtisztítása
		Clear(olc::GREY);

		// Legközelebbi megye megkeresése
		// Ebben a ciklusban rendezem le az előzőleg legközelebbinek megjelölt megye színének a visszaállítását
		for (int i = 0; i < 19; i++) {
			mouse = { GetMouseX(), GetMouseY() };
			int currDis = std::pow(magyarorszag[i].midPoint.x - mouse.x, 2) + std::pow(magyarorszag[i].midPoint.y - mouse.y, 2);

			if (currDis < minDistance) {
				minDistance = currDis;
				minIndex = i;
			}

			magyarorszag[i].highlight = false;
		}

		// Legközelebbi megye kijelölése, ha létezik
		if(minIndex > -1 && minIndex < 19)
			magyarorszag[minIndex].highlight = true;

		// Megyék majd a határvonalak megrajzolása
		// Ha megrajzolod a megyéket, akkor a középpontok nem fognak látszani (BUG?)
		for (int i = 0; i < 20; i++) {
			if (magyarorszag[i].highlight) {
				DrawDecal(magyarorszag[i].pos, magyarorszag[i].dec, { 0.5,0.5 }, magyarorszag[i].color);
				DrawCircle(magyarorszag[i].midPoint, 2, olc::RED);
			} else {
				DrawDecal(magyarorszag[i].pos, magyarorszag[i].dec, { 0.5,0.5 });
				DrawCircle(magyarorszag[i].midPoint, 2, olc::DARK_BLUE);
			}

		}
		
		// Debughoz, kiírja az ablakra a cursor jelenlegi helyét
		DrawString({ 50, 720 - 50 }, std::to_string(GetMouseX()));
		DrawString({ 50, 720 - 40 }, std::to_string(GetMouseY()));

		// Alapértékre állítom a legközelebbi megyét.
		minDistance = 19113;
		minIndex = -1;
		return true;
	}
};

int main() {
	BME_Foglalo game;

	// Ha nincs elég hely a kijelzőn (értsd: túl nagy ablakot választottál), akkor nem tud létrejönni az ablak.
	// A Start()-ból csak akkor lép ki, ha false-ot ad vissza, vagy bezáródik az ablak
	if (game.Construct(1280, 720, 1, 1))
		game.Start();

	return 0;
}