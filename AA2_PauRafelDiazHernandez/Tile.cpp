#include "Tile.h"
#include "ConsoleControl.h"

Tile::Tile()
{
	SetType(TileType::EMPTY);
}

Tile::Tile(TileType type)
{
	SetType(type);
}

void Tile::SetType(TileType newType)
{
	type = newType;

	switch (type)
	{
	case TileType::EMPTY:
		symbol = ' ';
		colorForeground = CC::WHITE;
		colorBackground = CC::BLACK;
		break;

	case TileType::WALL:
		symbol = '#';
		colorForeground = CC::LIGHTGREY;
		colorBackground = CC::DARKGREY;
		break;

	case TileType::PORTAL_UP:
		symbol = '^';
		colorForeground = CC::CYAN;
		colorBackground = CC::BLACK;
		break;

	case TileType::PORTAL_DOWN:
		symbol = 'v';
		colorForeground = CC::CYAN;
		colorBackground = CC::BLACK;
		break;

	case TileType::PORTAL_LEFT:
		symbol = '<';
		colorForeground = CC::CYAN;
		colorBackground = CC::BLACK;
		break;

	case TileType::PORTAL_RIGHT:
		symbol = '>';
		colorForeground = CC::CYAN;
		colorBackground = CC::BLACK;
		break;

	case TileType::PLAYER:
		symbol = '@';
		colorForeground = CC::YELLOW;
		colorBackground = CC::BLACK;
		break;

	case TileType::ENEMY:
		symbol = 'E';
		colorForeground = CC::RED;
		colorBackground = CC::BLACK;
		break;

	case TileType::CHEST:
		symbol = 'C';
		colorForeground = CC::DARKYELLOW;
		colorBackground = CC::BLACK;
		break;

	case TileType::ITEM:
		symbol = '*';
		colorForeground = CC::MAGENTA;
		colorBackground = CC::BLACK;
		break;

	default:
		symbol = '?';
		colorForeground = CC::WHITE;
		colorBackground = CC::BLACK;
		break;
	}
}

bool Tile::IsWalkable()
{
	return type != TileType::WALL;
}

bool Tile::IsPortal()
{
	return type == TileType::PORTAL_UP ||
		type == TileType::PORTAL_DOWN ||
		type == TileType::PORTAL_LEFT ||
		type == TileType::PORTAL_RIGHT;
}