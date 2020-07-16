#include <string>
#include <iostream>
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class BME_Foglalo : public olc::PixelGameEngine {
public:
	BME_Foglalo() {
		sAppName = "BME Foglalo";
	}
private:
	struct DecPos {
		olc::Decal* dec;
		olc::vi2d pos;
	};

	DecPos magyarorszag[20];

	//std::list<DecPos> magyarorszag;
	olc::Sprite* sprTile;
	olc::Decal* decTile;

public:
	bool OnUserCreate() override {
		for (int i = 0; i < 20; i++) {
			std::string str = "./Magyarorszag/smaller/";
			str += std::to_string(i);
			std::cout << str << std::endl;
			olc::Sprite* spr = new olc::Sprite(str + ".png");
			olc::Decal* dec = new olc::Decal(spr);
			magyarorszag[i] = { dec, {0,0} };
		}

		magyarorszag[0] = { magyarorszag[0].dec, {730/2, 603/2+1} };
		magyarorszag[1] = { magyarorszag[1].dec, {417 / 2 + 1, 892 / 2} };
		magyarorszag[2] = { magyarorszag[2].dec, {1199 / 2 + 1, 557 / 2 + 1} };
		magyarorszag[3] = { magyarorszag[3].dec, {1093/2 + 1, 5/2+1} };
		magyarorszag[4] = { magyarorszag[4].dec, {987 / 2 + 1, 729 / 2 + 1} };
		magyarorszag[5] = { magyarorszag[5].dec, {539 / 2 + 1, 422 / 2} };
		magyarorszag[6] = { magyarorszag[6].dec, {103 / 2 + 1, 237 / 2 + 1} };
		magyarorszag[7] = { magyarorszag[7].dec, {1307 / 2 + 1, 256 / 2} };
		magyarorszag[8] = { magyarorszag[8].dec, {964 / 2, 184 / 2} };
		magyarorszag[9] = { magyarorszag[9].dec, {987 / 2 + 1, 376 / 2} };
		magyarorszag[10] = { magyarorszag[10].dec, {497 / 2 + 1, 325 / 2 + 1} };
		magyarorszag[11] = { magyarorszag[11].dec, {790 / 2, 150 / 2 + 1} };
		magyarorszag[12] = { magyarorszag[12].dec, {721 / 2 + 1, 228 / 2} };
		magyarorszag[13] = { magyarorszag[13].dec, {210 / 2, 658 / 2} };
		magyarorszag[14] = { magyarorszag[14].dec, {1375 / 2 + 1, 62 / 2} };
		magyarorszag[15] = { magyarorszag[15].dec, {528 / 2, 715 / 2 + 1} };
		magyarorszag[16] = { magyarorszag[16].dec, {5 / 2 + 1, 463 / 2 + 1} };
		magyarorszag[17] = { magyarorszag[17].dec, {273 / 2 + 1, 457 / 2 + 1} };
		magyarorszag[18] = { magyarorszag[18].dec, {73 / 2 + 1, 632 / 2} };
		magyarorszag[19] = { magyarorszag[19].dec, {0,0} };
		//magyarorszag[20] = { magyarorszag[20].dec, {0,0} };
		
		/*
		magyarorszag.push_back(olc::Sprite("./Magyarorszag/Bacs.png");
		magyarorszag.push_back(olc::Sprite("./Magyarorszag/Baranya.png");
		magyarorszag.push_back(olc::Sprite("./Magyarorszag/Bekes.png");
		magyarorszag.push_back(olc::Sprite("./Magyarorszag/Borsod.png");
		magyarorszag.push_back(olc::Sprite("./Magyarorszag/Csongrad.png");
		magyarorszag.push_back(olc::Sprite("./Magyarorszag/Fejer.png");
		magyarorszag.push_back(olc::Sprite("./Magyarorszag/Gyor.png");
		magyarorszag.push_back(olc::Sprite("./Magyarorszag/Hajdu.png");
		magyarorszag.push_back(olc::Sprite("./Magyarorszag/Heves.png");
		magyarorszag.push_back(olc::Sprite("./Magyarorszag/Jasz.png");
		magyarorszag.push_back(olc::Sprite("./Magyarorszag/Komarom.png");
		magyarorszag.push_back(olc::Sprite("./Magyarorszag/Nograd.png");
		magyarorszag.push_back(olc::Sprite("./Magyarorszag/Pest.png");
		magyarorszag.push_back(olc::Sprite("./Magyarorszag/Somogy.png");
		magyarorszag.push_back(olc::Sprite("./Magyarorszag/Szabolcs.png");
		magyarorszag.push_back(olc::Sprite("./Magyarorszag/Tolna.png");
		magyarorszag.push_back(olc::Sprite("./Magyarorszag/Vas.png");
		magyarorszag.push_back(olc::Sprite("./Magyarorszag/Veszprem.png");
		magyarorszag.push_back(olc::Sprite("./Magyarorszag/Zala.png");
		*/
		sprTile = new olc::Sprite("./Magyarorszag/Magyarorszag.png");
		decTile = new olc::Decal(sprTile);

		//sprBg = new olc::Sprite("./img/Counties_of_Hungary_2020.png");
		//decBg = new olc::Decal(sprBg);
		return true;
	}
	bool OnUserUpdate(float fElapsedTime) override {
		Clear(olc::GREY);

		for (int i = 0; i < 20; i++) {
			DrawDecal(magyarorszag[i].pos, magyarorszag[i].dec, { 0.5,0.5 });
		}

		/*for (auto& d : magyarorszag) {
			DrawDecal({ d.pos.x, d.pos.y }, d.dec, { 0.5,0.5 });
		}*/
		return true;
	}
};

int main() {
	BME_Foglalo game;

	if (game.Construct(1280, 720, 1, 1))
	//if (game.Construct(320, 180, 4, 4))
		game.Start();

	return 0;
}