#include "Enemy.h"
#include "Game.h"
#include "Map.h"

Enemy::Enemy( const Vector& pos ) :
Character( pos ) {
}

Enemy::~Enemy( ) {
}

Vector Enemy::getVecToGoal( const Vector& start, const Vector& goal ) {
	MapPtr map = Game::getTask( )->getMap( );
	Vector s_pos( map->getMapX( start ), map->getMapY( start ) );
	Vector g_pos( map->getMapX( goal ), map->getMapY( goal ) );

	std::vector< PROCEED > proceeds;
	
	DIRECTION next = DIRECTION_START;
	Vector next_pos = s_pos;
	bool back = false;
	int count = 0;
	while ( true ) {
		if ( next_pos == g_pos ) {
			break;
		}
		count++;
		PROCEED pro;
		pro.before_dir = next;
		pro.pos = next_pos;
		if ( back ) {
			int idx = ( int )proceeds.size( ) - 1;
			pro.up = proceeds[ idx ].up;
			pro.down = proceeds[ idx ].down;
			pro.left = proceeds[ idx ].left;
			pro.right = proceeds[ idx ].right;
		}

		back = false;

		if ( map->getObject( ( int )pro.pos.x, ( int )pro.pos.y - 1 ) == OBJECT_WALL ) {
			pro.up = false;
		}
		if ( map->getObject( ( int )pro.pos.x, ( int )pro.pos.y + 1 ) == OBJECT_WALL ) {
			pro.down = false;
		}
		if ( map->getObject( ( int )pro.pos.x - 1, ( int )pro.pos.y ) == OBJECT_WALL ) {
			pro.left = false;
		}
		if ( map->getObject( ( int )pro.pos.x + 1, ( int )pro.pos.y ) == OBJECT_WALL ) {
			pro.right = false;
		}

		Vector goal_dir = g_pos - pro.pos;
		if ( goal_dir.x < 0 ) {
			// left
			if ( moveLeft( &pro, &proceeds, &next, &next_pos, &back ) ) {
				continue;
			}
			// left-up
			if ( goal_dir.y < 0 ) {
				if ( moveUp( &pro, &proceeds, &next, &next_pos, &back ) ) {
					continue;
				}
				if ( moveDown( &pro, &proceeds, &next, &next_pos, &back ) ) {
					continue;
				}
			}
			// left-down
			if ( goal_dir.y > 0 ) {
				if ( moveDown( &pro, &proceeds, &next, &next_pos, &back ) ) {
					continue;
				}
				if ( moveUp( &pro, &proceeds, &next, &next_pos, &back ) ) {
					continue;
				}
			}
			// left-right
			if ( moveRight( &pro, &proceeds, &next, &next_pos, &back ) ) {
				continue;
			}
		} 
		if ( goal_dir.x > 0 ) {
			// right
			if ( moveRight( &pro, &proceeds, &next, &next_pos, &back ) ) {
				continue;
			}
			// right-up
			if ( goal_dir.y < 0 ) {
				if ( moveUp( &pro, &proceeds, &next, &next_pos, &back ) ) {
					continue;
				}
				if ( moveDown( &pro, &proceeds, &next, &next_pos, &back ) ) {
					continue;
				}
			}
			// right-down
			if ( goal_dir.y > 0 ) {
				if ( moveDown( &pro, &proceeds, &next, &next_pos, &back ) ) {
					continue;
				}
				if ( moveUp( &pro, &proceeds, &next, &next_pos, &back ) ) {
					continue;
				}
			}
			// right-left
			if ( moveLeft( &pro, &proceeds, &next, &next_pos, &back ) ) {
				continue;
			}
		}
		if ( goal_dir.y < 0 ) {
			// up
			if ( moveUp( &pro, &proceeds, &next, &next_pos, &back ) ) {
				continue;
			}
			// up-left
			if ( goal_dir.x < 0 ) {
				if ( moveLeft( &pro, &proceeds, &next, &next_pos, &back ) ) {
					continue;
				}
				if ( moveRight( &pro, &proceeds, &next, &next_pos, &back ) ) {
					continue;
				}
			}
			// up-right
			if ( goal_dir.x > 0 ) {
				if ( moveRight( &pro, &proceeds, &next, &next_pos, &back ) ) {
					continue;
				}
				if ( moveLeft( &pro, &proceeds, &next, &next_pos, &back ) ) {
					continue;
				}
			}
			// up-down
			if ( moveDown( &pro, &proceeds, &next, &next_pos, &back ) ) {
				continue;
			}
		}
		if ( goal_dir.y > 0 ) {
			// down
			if ( moveDown( &pro, &proceeds, &next, &next_pos, &back ) ) {
				continue;
			}
			// down-left
			if ( goal_dir.x < 0 ) {
				if ( moveLeft( &pro, &proceeds, &next, &next_pos, &back ) ) {
					continue;
				}
				if ( moveRight( &pro, &proceeds, &next, &next_pos, &back ) ) {
					continue;
				}
			}
			// down-right
			if ( goal_dir.x > 0 ) {
				if ( moveRight( &pro, &proceeds, &next, &next_pos, &back ) ) {
					continue;
				}
				if ( moveLeft( &pro, &proceeds, &next, &next_pos, &back ) ) {
					continue;
				}
			}
			// down-up
			if ( moveUp( &pro, &proceeds, &next, &next_pos, &back ) ) {
				continue;
			}
		}
	}

	int size = ( int )proceeds.size( );
	Vector result = g_pos - s_pos;
	if ( size > 1 ) {
		result = proceeds[ 1 ].pos - s_pos;
	}
	return result;
}

bool Enemy::moveUp( PROCEED * proceed, std::vector< PROCEED > * proceeds, DIRECTION * next_dir, Vector * next_pos, bool * back ) {
	if ( proceed->up ) {
		next_pos->y--;
		if ( proceed->before_dir == DIRECTION_DOWN ) {
			(*proceeds).pop_back( );
			*back = true;
		} else {
			*next_dir = DIRECTION_UP;
			proceed->up = false;
			(*proceeds).push_back( *proceed );
		}
		return true;
	}
	return false;
}

bool Enemy::moveDown( PROCEED * proceed, std::vector< PROCEED > * proceeds, DIRECTION * next_dir, Vector * next_pos, bool * back ) {
	if ( proceed->down ) {
		next_pos->y++;
		if ( proceed->before_dir == DIRECTION_UP ) {
			(*proceeds).pop_back( );
			*back = true;
		} else {
			*next_dir = DIRECTION_DOWN;
			proceed->down = false;
			(*proceeds).push_back( *proceed );
		}
		return true;
	}
	return false;
}

bool Enemy::moveLeft( PROCEED * proceed, std::vector< PROCEED > * proceeds, DIRECTION * next_dir, Vector * next_pos, bool * back ) {
	if ( proceed->left ) {
		next_pos->x--;
		if ( proceed->before_dir == DIRECTION_RIGHT ) {
			(*proceeds).pop_back( );
			*back = true;
		} else {
			*next_dir = DIRECTION_LEFT;
			proceed->left = false;
			(*proceeds).push_back( *proceed );
		}
		return true;
	}
	return false;
}

bool Enemy::moveRight( PROCEED * proceed, std::vector< PROCEED > * proceeds, DIRECTION * next_dir, Vector * next_pos, bool * back ) {
	if ( proceed->right ) {
		next_pos->x++;
		if ( proceed->before_dir == DIRECTION_LEFT ) {
			(*proceeds).pop_back( );
			*back = true;
		} else {
			*next_dir = DIRECTION_RIGHT;
			proceed->right = false;
			(*proceeds).push_back( *proceed );
		}
		return true;
	}
	return false;
}
