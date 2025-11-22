#pragma once
#include <string>

class Entity
{
protected:
	int _x;
	int _y;
	int _health;
	int _maxHealth;
	char _symbol;
	std::string _name;
	bool _isAlive;

public:
	Entity(int x, int y, int maxHealth, char symbol, std::string name);
	virtual ~Entity() {}

	int GetX() { return _x; }
	int GetY() { return _y; }
	int GetHealth() { return _health; }
	int GetMaxHealth() { return _maxHealth; }
	char GetSymbol() { return _symbol; }
	std::string GetName() { return _name; }
	bool IsAlive() { return _isAlive; }

	void SetPosition(int x, int y);
	void SetHealth(int health);

	virtual void TakeDamage(int damage);
	virtual void Heal(int amount);
	virtual void Die();
};