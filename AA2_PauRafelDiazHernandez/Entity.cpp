#include "Entity.h"

Entity::Entity(int x, int y, int maxHealth, char symbol, std::string name)
{
	_x = x;
	_y = y;
	_maxHealth = maxHealth;
	_health = maxHealth;
	_symbol = symbol;
	_name = name;
	_isAlive = true;
}

void Entity::SetPosition(int x, int y)
{
	_x = x;
	_y = y;
}

void Entity::SetHealth(int health)
{
	_health = health;
	if (_health > _maxHealth)
		_health = _maxHealth;
	if (_health <= 0)
	{
		_health = 0;
		Die();
	}
}

void Entity::TakeDamage(int damage)
{
	_health -= damage;
	if (_health <= 0)
	{
		_health = 0;
		Die();
	}
}

void Entity::Heal(int amount)
{
	_health += amount;
	if (_health > _maxHealth)
		_health = _maxHealth;
}

void Entity::Die()
{
	_isAlive = false;
}