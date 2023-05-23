#include "pch.h"
#include "Player.h"
#include "Board.h"

void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;

	Pos pos = _pos;

	_dest = board->GetExitPos();
	
}

void Player::Update(uint64 deltaTime)
{
	if (_pos != _dest)
	{
		
		Pos front[4] = {
			{-1,0},
			{0,-1},
			{1,0},
			{0,1}
		};

		int32 newDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT;


		if (_board->GetTileType(_pos + front[newDir]) == TileType::EMPTY)
		{
			_dir = newDir;
			_pos += front[newDir];
		}

		else if (_board->GetTileType(_pos + front[_dir]) == TileType::EMPTY)
		{
			_pos += front[_dir];
		}

		else
			_dir = (_dir + 1) % DIR_COUNT;





		/*switch (_dir)
		{
		case DIR_UP:
		{
			if (_board->GetTileType({ _pos.y, _pos.x + 1 }) == TileType::EMPTY)
			{
				_dir = (DIR_COUNT + _dir - 1) % DIR_COUNT;
				_pos.x += 1;
			}
			else if (_board->GetTileType({ _pos.y - 1, _pos.x }) == TileType::EMPTY)
			{
				_pos.y -= 1;
			}
			else
				_dir = (_dir + 1) % DIR_COUNT;
		}
		break;
		case DIR_RIGHT:
		{
			if (_board->GetTileType({ _pos.y + 1, _pos.x }) == TileType::EMPTY)
			{
				_dir = DIR_DOWN;
				_pos.y += 1;
			}
			else if (_board->GetTileType({ _pos.y, _pos.x + 1 }) == TileType::EMPTY)
			{
				_pos.x += 1;
			}
			else
				_dir = (_dir + 1) % DIR_COUNT;
		}
		break;
		case DIR_DOWN:
		{
			if (_board->GetTileType({ _pos.y, _pos.x - 1 }) == TileType::EMPTY)
			{
				_dir = DIR_LEFT;
				_pos.x -= 1;
			}
			else if (_board->GetTileType({ _pos.y + 1, _pos.x }) == TileType::EMPTY)
			{
				_pos.y += 1;
			}
			else
				_dir = (_dir + 1) % DIR_COUNT;
		}
		break;
		case DIR_LEFT:
		{
			if (_board->GetTileType({ _pos.y - 1, _pos.x }) == TileType::EMPTY)
			{
				_dir = DIR_UP;
				_pos.y -= 1;
			}
			else if (_board->GetTileType({ _pos.y , _pos.x - 1 }) == TileType::EMPTY)
			{
				_pos.x -= 1;
			}
			else
				_dir = (_dir + 1) % DIR_COUNT;
		}
		break;
		}*/
	}
}
