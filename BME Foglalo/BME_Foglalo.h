//#define OLC_PGE_APPLICATION
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
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
};