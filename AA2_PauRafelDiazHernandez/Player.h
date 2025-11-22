#pragma once
#include "Entity.h"
#include <mutex>

enum class WeaponType
{
	SWORD = 1,  //Range 1
	SPEAR = 2   //Range 2
};

class Player : public Entity
{
private:
	unsigned int _coins;
	unsigned int _potions;
	WeaponType _currentWeapon;
	std::mutex* _playerMutex;

	unsigned long _lastMoveTime;
	unsigned long _moveCooldown; //ms

public:
	Player(int x, int y);
	~Player();

	unsigned int GetCoins() { return _coins; }
	unsigned int GetPotions() { return _potions; }
	WeaponType GetWeapon() { return _currentWeapon; }
	int GetWeaponRange();

	void AddCoins(unsigned int amount);
	void AddPotions(unsigned int amount);
	void SetWeapon(WeaponType weapon);

	void UsePotion();
	bool CanMove(); 
	void UpdateMoveTime();

	void Lock() { _playerMutex->lock(); }
	void Unlock() { _playerMutex->unlock(); }
};