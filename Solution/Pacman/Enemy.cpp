#include "Enemy.h"
#include "SceneStage.h"
#include "Map.h"

static const int MOVE_SPEED = 5;
static const int MAX_SPEED = 6;

Enemy::Enemy( const Vector& pos ) :
Character( pos ),
_auto_move( false ),
_goal_pos( Vector( -1, -1 ) ) {
}

Enemy::~Enemy( ) {
}

void Enemy::act( ) {
	if ( !_auto_move ) {
		moving( );
	} else {
		checkGoal( );
	}
}

void Enemy::moveGoal( const Vector goal ) {
	_auto_move = true;
	_goal_pos = goal;
	const int CHIP_SIZE = SceneStage::getTask( )->getChipSize( );
	Vector pos = getPos( );
	Vector vec = ( goal - pos ).normalize( ) * MOVE_SPEED + getVec( );

	if ( vec.getLength2( ) > MAX_SPEED * MAX_SPEED ) {
		vec = vec.normalize( ) * MAX_SPEED;
	}
	setVec( vec );
}

void Enemy::checkGoal( ) {
	int chara_size = SceneStage::getTask( )->getCharaSize( );
	Vector distance = getPos( ) - _goal_pos;
	if ( distance.getLength2( ) < chara_size * chara_size ) {
		_auto_move = false;
		_goal_pos = Vector( -1, -1 );
	}
	if ( distance.getLength2( ) < getVec( ).getLength2( ) ) {
		_auto_move = false;
		_goal_pos = Vector( -1, -1 );
	}
	if ( isBumped( ) ) {
		_auto_move = false;
		_goal_pos = Vector( -1, -1 );
	}
}

Vector Enemy::AStar( const Vector& goal ) {
	MapPtr map = SceneStage::getTask( )->getMap( );
	Vector start_pos( map->getMapPos( getPos( ) ) );
	Vector goal_pos( map->getMapPos( goal ) );

	std::vector< PROCEED > proceeds;
	int min_score = 0;
	{
		PROCEED pro;
		pro.pos = start_pos;
		pro.state = STATE_OPEN;
		pro.cost = 0;
		pro.heristic = ( int )( fabs( goal_pos.x - start_pos.x ) + fabs( goal_pos.y - start_pos.y ) );
		pro.setScore( );
		min_score = pro.score;
		proceeds.push_back( pro );
	}

	int count = 0;

	while ( true ) {
		count++;
		if ( count > 10 ) {
			int a = 0;
		}

		// 一番小さいscoreを検索
		{
			std::vector< PROCEED >::iterator ite = proceeds.begin( );
			bool score_up = true;
			while ( ite != proceeds.end( ) ) {
				PROCEED pro = *ite;
				if ( min_score == pro.score &&
					 pro.state == STATE_OPEN ) {
					score_up = false;
					break;
				}
				ite++;
			}
			if ( score_up ) {
				min_score++;
			}
		}
		
		// 一番小さいscoreのチップをclose
		std::vector< PROCEED > open_tmp;
		{
			std::vector< PROCEED >::iterator ite = proceeds.begin( );
			while ( ite != proceeds.end( ) ) {
				PROCEED origin = *ite;
				if ( min_score != origin.score ||
					 origin.state == STATE_COLSE ) {
					ite++;
					continue;
				}
				(*ite).state = STATE_COLSE;
				ite++;
				PROCEED pro_up;
				PROCEED pro_down;
				PROCEED pro_left;
				PROCEED pro_right;

				//初期代入
				{
					pro_up.pos    = origin.pos + Vector(  0, -1 );
					pro_down.pos  = origin.pos + Vector(  0,  1 );
					pro_left.pos  = origin.pos + Vector( -1,  0 );
					pro_right.pos = origin.pos + Vector(  1,  0 );

					pro_up.cost    = origin.cost + 1;
					pro_down.cost  = origin.cost + 1;
					pro_left.cost  = origin.cost + 1;
					pro_right.cost = origin.cost + 1;

					if ( map->getObject( ( int )pro_up.pos.x, ( int )pro_up.pos.y ) != OBJECT_WALL ) {
						pro_up.state = STATE_OPEN;
						if ( pro_up.pos == goal_pos ) {
							pro_up.state = STATE_COLSE;
							open_tmp.push_back( pro_up );
							break;
						}
					}
					if ( map->getObject( ( int )pro_down.pos.x, ( int )pro_down.pos.y ) != OBJECT_WALL ) {
						pro_down.state = STATE_OPEN;
						if ( pro_down.pos == goal_pos ) {
							pro_down.state = STATE_COLSE;
							open_tmp.push_back( pro_down );
							break;
						}
					}
					if ( map->getObject( ( int )pro_left.pos.x, ( int )pro_left.pos.y ) != OBJECT_WALL ) {
						pro_left.state = STATE_OPEN;
						if ( pro_left.pos == goal_pos ) {
							pro_left.state = STATE_COLSE;
							open_tmp.push_back( pro_left );
							break;
						}
					}
					if ( map->getObject( ( int )pro_right.pos.x, ( int )pro_right.pos.y ) != OBJECT_WALL ) {
						pro_right.state = STATE_OPEN;
						if ( pro_right.pos == goal_pos ) {
							pro_right.state = STATE_COLSE;
							open_tmp.push_back( pro_right );
							break;
						}
					}

					pro_up.heristic    = ( int )( fabs( goal_pos.x - pro_up.pos.x )    + fabs( goal_pos.y - pro_up.pos.y ) );
					pro_down.heristic  = ( int )( fabs( goal_pos.x - pro_down.pos.x )  + fabs( goal_pos.y - pro_down.pos.y ) );
					pro_left.heristic  = ( int )( fabs( goal_pos.x - pro_left.pos.x )  + fabs( goal_pos.y - pro_left.pos.y ) );
					pro_right.heristic = ( int )( fabs( goal_pos.x - pro_right.pos.x ) + fabs( goal_pos.y - pro_right.pos.y ) );

					pro_up.setScore( );
					pro_down.setScore( );
					pro_left.setScore( );
					pro_right.setScore( );
				}
				
				// すでにopenされているか確認
				{
					std::vector< PROCEED >::iterator open_ite = proceeds.begin( );
					while ( open_ite != proceeds.end( ) ) {
						PROCEED pro = *open_ite;
						if ( pro.pos == pro_up.pos    ) pro_up    = PROCEED( );
						if ( pro.pos == pro_down.pos  ) pro_down  = PROCEED( );
						if ( pro.pos == pro_left.pos  ) pro_left  = PROCEED( );
						if ( pro.pos == pro_right.pos ) pro_right = PROCEED( );
						open_ite++;
					}
					std::vector< PROCEED >::iterator pro_ite = open_tmp.begin( );
					while ( pro_ite != open_tmp.end( ) ) {
						PROCEED pro = *pro_ite;
						if ( pro.pos == pro_up.pos    ) pro_up    = PROCEED( );
						if ( pro.pos == pro_down.pos  )	pro_down  = PROCEED( );
						if ( pro.pos == pro_left.pos  ) pro_left  = PROCEED( );
						if ( pro.pos == pro_right.pos ) pro_right = PROCEED( );
						pro_ite++;
					}
				}

				// open_tmpにセット
				{
					if ( pro_up.state    == STATE_OPEN ) {
						open_tmp.push_back( pro_up    );
					}
					if ( pro_down.state  == STATE_OPEN ) {
						open_tmp.push_back( pro_down  );
					}
					if ( pro_left.state  == STATE_OPEN ) {
						open_tmp.push_back( pro_left  );
					}
					if ( pro_right.state == STATE_OPEN ) {
						open_tmp.push_back( pro_right );
					}
				}
			}
			
			// proceedsにセット
			{
				std::vector< PROCEED >::iterator ite = open_tmp.begin( );
				while ( ite != open_tmp.end( ) ) {
					proceeds.push_back( *ite );
					ite++;
				}
			}
		}

		// openされたチップの中にgoal地点があったら終了
		{
			bool finish = false;
			std::vector< PROCEED >::iterator ite = open_tmp.begin( );
			while ( ite != open_tmp.end( ) ) {
				if ( (*ite).pos == goal_pos ) {
					finish = true;
					break;
				}
				ite++;
			}
			if ( finish ) {
				break;
			}
		}

		open_tmp.clear( );
	}

	// goalからstartへの道を検索
	std::vector< PROCEED > root;
	{
		int size = ( int )proceeds.size( ) - 1;
		PROCEED check = proceeds[ size ];
		if ( check.pos != goal_pos ) {
			for ( int i = size; i > 0; i-- ) {
				check = proceeds[ i ];
				if ( check.pos == goal_pos ) break;
			}
		}
		std::vector< PROCEED >::iterator ite = proceeds.begin( );
		while ( check.pos != start_pos ) {
			PROCEED pro = *ite;
			if ( pro.pos == check.pos && pro.state == STATE_COLSE ) {
				root.push_back( pro );
				std::vector< PROCEED >::iterator next_ite = proceeds.begin( );
				while ( next_ite != proceeds.end( ) ) {
					if ( pro.pos + Vector(  1,  0 ) == (*next_ite).pos && check.cost > (*next_ite).cost ) {
						check = *next_ite;
					}
					if ( pro.pos + Vector( -1,  0 ) == (*next_ite).pos && check.cost > (*next_ite).cost ) {
						check = *next_ite;
					}
					if ( pro.pos + Vector(  0,  1 ) == (*next_ite).pos && check.cost > (*next_ite).cost ) {
						check = *next_ite;
					}
					if ( pro.pos + Vector(  0, -1 ) == (*next_ite).pos && check.cost > (*next_ite).cost ) {
						check = *next_ite;
					}
					next_ite++;
				}
			}
			ite++;
			if ( ite == proceeds.end( ) ) {
				ite = proceeds.begin( );
			}
		}
	}

	int size = ( int )root.size( );
	Vector dir = goal_pos - start_pos;
	if ( size > 1 ) {
		dir = ( root[ size - 2 ].pos - root[ size - 1 ].pos ).normalize( );
	}
	return dir;
}
