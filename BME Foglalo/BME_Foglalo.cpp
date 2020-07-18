#include <string>
#include <iostream>
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "BME_Foglalo.h"


// Csak 1-szer futnak le az itt leírt dolgok, inicializáláshoz tökéletes
bool BME_Foglalo::OnUserCreate() {

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
	magyarorszag[0] = { magyarorszag[0].spr, magyarorszag[0].dec, {730, 603}, {396, 494} };
	magyarorszag[1] = { magyarorszag[1].spr, magyarorszag[1].dec, {417, 892}, {348, 273} };
	magyarorszag[2] = { magyarorszag[2].spr, magyarorszag[2].dec, {1199, 557}, {350, 395} };
	magyarorszag[3] = { magyarorszag[3].spr, magyarorszag[3].dec, {1093, 5}, {553, 377} };
	magyarorszag[4] = { magyarorszag[4].spr, magyarorszag[4].dec, {987, 729}, {314, 277} };
	magyarorszag[5] = { magyarorszag[5].spr, magyarorszag[5].dec, {539, 422}, {255, 357} };
	magyarorszag[6] = { magyarorszag[6].spr, magyarorszag[6].dec, {103, 237}, {407, 299} };
	magyarorszag[7] = { magyarorszag[7].spr, magyarorszag[7].dec, {1307, 256}, {355, 410} };
	magyarorszag[8] = { magyarorszag[8].spr, magyarorszag[8].dec, {964, 184}, {325, 294} };
	magyarorszag[9] = { magyarorszag[9].spr, magyarorszag[9].dec, {987, 376}, {375, 373} };
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

	/*
	Mivel az ablak méretét HD-ra lőttem be (1280x720p), ezért a megyék nem férnének ki
	Ezt kikerülve, fele akkora méretben jelnnek meg a megyék és az határvonal, így belefér az ablakba
	Ezzel a ciklussal az eredeti méreteket átváltom, így jó helyen jelennek meg a fele akkora képek
	*/
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

// Képkockánként futnak le az itt leírtak
bool BME_Foglalo::OnUserUpdate(float fElapsedTime) {
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
	if (minIndex > -1 && minIndex < 19)
		magyarorszag[minIndex].highlight = true;

	// Megyék majd a határvonalak megrajzolása
	// Ha megrajzolod a megyéket, akkor a középpontok nem fognak látszani (BUG?)
	for (int i = 0; i < 20; i++) {
		if (magyarorszag[i].highlight) {
			// Itt történik a képek fele akkora megjelenítése { 0.5,0.5 }, ez egy transzformáció
			DrawDecal(magyarorszag[i].pos, magyarorszag[i].dec, { 0.5,0.5 }, magyarorszag[i].color);
			DrawCircle(magyarorszag[i].midPoint, 2, olc::RED);
		}
		else {
			// Itt történik a képek fele akkora megjelenítése { 0.5,0.5 }, ez egy transzformáció
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
