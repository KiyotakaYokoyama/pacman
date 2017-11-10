#include "Enemy.h"
#include "Game.h"
#include "Map.h"
#include <vector>

Enemy::Enemy( const Vector& pos ) :
Character( pos ) {
}

Enemy::~Enemy( ) {
}

Vector Enemy::getVecToGoal( const Vector& start, const Vector& goal ) {
	MapPtr map = Game::getTask( )->getMap( );
	Vector s_pos( map->getMapX( start ), map->getMapY( start ) );
	Vector g_pos( map->getMapX( goal ), map->getMapY( goal ) );
	Vector distance = goal - start;

	std::vector< PROCEED > proceeds;
	
	DIRECTION next = DIRECTION_START;
	Vector next_pos = s_pos;
	while ( true ) {
		PROCEED pro;
		pro.dir = next;
		if ( map->getObject( ( int )pro.pos.x, ( int )pro.pos.y + 1 ) == OBJECT_WALL ) {
			pro.up = false;
		}
		if ( map->getObject( ( int )pro.pos.x, ( int )pro.pos.y - 1 ) == OBJECT_WALL ) {
			pro.down = false;
		}
		if ( map->getObject( ( int )pro.pos.x - 1, ( int )pro.pos.y ) == OBJECT_WALL ) {
			pro.left = false;
		}
		if ( map->getObject( ( int )pro.pos.x + 1, ( int )pro.pos.y ) == OBJECT_WALL ) {
			pro.right = false;
		}

		if ( fabs( distance.x ) < fabs( distance.y ) ) {
			if ( distance.x < 0 ) {
				// left
				if ( pro.left ) {
					pro.left = false;
					if ( pro.dir = DIRECTION_LEFT ) {
						proceeds.pop_back( );
						proceeds[ proceeds.size( ) - 1 ].left = false;
					} else {
						next = DIRECTION_LEFT;
						pro.pos.x--;
						proceeds.push_back( pro );
					}
					continue;
				}
				if ( distance.y < 0 ) {
					// left-up
					if ( pro.up ) {
						pro.up = false;
						if ( pro.dir = DIRECTION_UP ) {
							proceeds.pop_back( );
							proceeds[ proceeds.size( ) - 1 ].up = false;
						} else {
							next = DIRECTION_UP;
							pro.pos.y--;
							proceeds.push_back( pro );
						}
						continue;
					}
				} else if ( distance.y > 0 ) {
					// left-down
					if ( pro.down ) {
						pro.down = false;
						if ( pro.dir = DIRECTION_DOWN ) {
							proceeds.pop_back( );
							proceeds[ proceeds.size( ) - 1 ].down = false;
						} else {
							next = DIRECTION_DOWN;
							pro.pos.y++;
							proceeds.push_back( pro );
						}
						continue;
					}
				}
				if ( pro.right ) {
					// left-right
					if ( pro.right ) {
						pro.right = false;
						if ( pro.dir = DIRECTION_RIGHT ) {
							proceeds.pop_back( );
							proceeds[ proceeds.size( ) - 1 ].right = false;
						} else {
							next = DIRECTION_RIGHT;
							pro.pos.x++;
							proceeds.push_back( pro );
						}
						continue;
					}
				}
			} else {
				// right
				if ( pro.right ) {
					if ( pro.right ) {
						pro.right = false;
						if ( pro.dir = DIRECTION_RIGHT ) {
							proceeds.pop_back( );
							proceeds[ proceeds.size( ) - 1 ].right = false;
						} else {
							next = DIRECTION_RIGHT;
							pro.pos.x++;
							proceeds.push_back( pro );
						}
						continue;
					}
				}
				if ( distance.y < 0 ) {
					// right-up
					if ( pro.up ) {
						pro.up = false;
						if ( pro.dir = DIRECTION_UP ) {
							proceeds.pop_back( );
							proceeds[ proceeds.size( ) - 1 ].up = false;
						} else {
							next = DIRECTION_UP;
							pro.pos.y--;
							proceeds.push_back( pro );
						}
						continue;
					}
				} else if ( distance.y > 0 ) {
					// right-down
					if ( pro.down ) {
						pro.down = false;
						if ( pro.dir = DIRECTION_DOWN ) {
							proceeds.pop_back( );
							proceeds[ proceeds.size( ) - 1 ].down = false;
						} else {
							next = DIRECTION_DOWN;
							pro.pos.y++;
							proceeds.push_back( pro );
						}
						continue;
					}
				}				
				if ( pro.left ) {
					pro.left = false;
					if ( pro.dir = DIRECTION_LEFT ) {
						proceeds.pop_back( );
						proceeds[ proceeds.size( ) - 1 ].left = false;
					} else {
						next = DIRECTION_LEFT;
						pro.pos.x--;
						proceeds.push_back( pro );
					}
					continue;
				}
			}
		} else {
			if ( distance.y < 0 ) {
				// up
				if ( pro.up ) {
					pro.up = false;
					if ( pro.dir = DIRECTION_UP ) {
							proceeds.pop_back( );
							proceeds[ proceeds.size( ) - 1 ].up = false;
						} else {
						next = DIRECTION_UP;
						pro.pos.y--;
						proceeds.push_back( pro );
					}
					continue;
				}
				if ( distance.x < 0 ) {
					// up-left
					if ( pro.left ) {
						pro.left = false;
						if ( pro.dir = DIRECTION_LEFT ) {
							proceeds.pop_back( );
							proceeds[ proceeds.size( ) - 1 ].left = false;
						} else {
							next = DIRECTION_LEFT;
							pro.pos.x--;
							proceeds.push_back( pro );
						}
						continue;
					}
				} else if ( distance.x > 0 ) {
					// up-right
					if ( pro.right ) {
						pro.right = false;

						next = DIRECTION_RIGHT;
						proceeds.push_back( pro );
						continue;
					}
				}
				if ( pro.down ) {
					// up-down
					if ( pro.down ) {
						pro.down = false;
						next = DIRECTION_DOWN;
						proceeds.push_back( pro );
						continue;
					}
				}
			} else {
				if ( distance.y > 0 ) {
					// down
					if ( pro.down ) {
						pro.down = false;
						next = DIRECTION_DOWN;
						proceeds.push_back( pro );
						continue;
					}
					if ( distance.x < 0 ) {
						// down-left
						if ( pro.left ) {
							pro.left = false;
							next = DIRECTION_LEFT;
							proceeds.push_back( pro );
							continue;
						}
					} else if ( distance.x > 0 ) {
						// down-right
						if ( pro.right ) {
							pro.right = false;
							next = DIRECTION_RIGHT;
							proceeds.push_back( pro );
							continue;
						}
					}
					if ( pro.up ) {
						// down-up
						if ( pro.up ) {
							pro.up = false;
							next = DIRECTION_UP;
							proceeds.push_back( pro );
							continue;
						}
					}
				}
			}
		}
	}

	return Vector( );
}
