#include "Player.h"
#include <chrono>
#include <iostream>

Player::Player(int x, int y) : Entity(x, y, 10, '@', "Hero")
{
	_coins = 0;
	_potions = 3; 
	_currentWeapon = WeaponType::SWORD;
	_playerMutex = new std::mutex();
	_moveCooldown = 200; //ms
	_lastMoveTime = 0;
}

Player::~Player()
{
	delete _playerMutex;
}

int Player::GetWeaponRange()
{
	switch (_currentWeapon)
	{
	case WeaponType::SWORD:
		return 1;
	case WeaponType::SPEAR:
		return 2;
	default:
		return 1;
	}
}

void Player::AddCoins(unsigned int amount)
{
	_coins += amount;
}

void Player::AddPotions(unsigned int amount)
{
	_potions += amount;
}

void Player::SetWeapon(WeaponType weapon)
{
	_currentWeapon = weapon;
}

void Player::UsePotion()
{
	if (_potions > 0)
	{
		_potions--;
		Heal(5); 
	}
}

bool Player::CanMove()
{
	auto now = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
	).count();

	return (now - _lastMoveTime) >= _moveCooldown;
}

void Player::UpdateMoveTime()
{
	_lastMoveTime = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
	).count();
}