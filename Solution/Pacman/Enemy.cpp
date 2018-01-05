#include "Enemy.h"
#include "SceneStage.h"
#include "Map.h"

static const int MOVE_SPEED = 2;
static const int MAX_SPEED = 1;
static const int MAX_CEARCH_LENGTH = 15;
static const int INIT_HIDE_TIME = 150;
static const int POP_TIME = 30;

Enemy::Enemy( const Vector& pos ) :
Character( pos ),
_action( ACTION_ACT ),
_start_pos( pos ),
_hide_time( -1 ) {
}

Enemy::~Enemy( ) {
}

void Enemy::act( ) {
	if ( _action == ACTION_HIDE ) {
		_hide_time--;
		if ( _hide_time < 0 ) {
			_action = ACTION_ACT;
			setColl( true );
		}
		return;
	}

	SceneStagePtr scene_stage = SceneStage::getTask( );
	const int CHIP_SIZE = scene_stage->getChipSize( );
	const int CHARA_SIZE = scene_stage->getCharaSize( );
	Vector pos = getPos( );
	bool center = ( int )pos.x % CHIP_SIZE == CHIP_SIZE / 2 &&
				  ( int )pos.y % CHIP_SIZE == CHARA_SIZE;

	if ( center ) {
		moving( );
		decisionMoveDir( );
	} else {
		adjustVec( );
	}
}

void Enemy::decisionMoveDir( ) {
	Vector vec = getVec( );
	if ( vec.y * vec.y < vec.x * vec.x ) {
		vec.y = 0;
	} else {
		vec.x = 0;
	}
	setVec( vec );
}

void Enemy::moveGoal( const Vector goal ) {
	const int CHIP_SIZE = SceneStage::getTask( )->getChipSize( );
	Vector diff = goal - getPos( );
	int root_num = ( int )( ( diff.x + 0.5 ) / CHIP_SIZE + ( diff.y + 0.5 ) / CHIP_SIZE );
	if ( abs( root_num ) > MAX_CEARCH_LENGTH ) {
		Vector vec = toStraight( getPos( ), goal ) * MOVE_SPEED + getVec( );
		if ( vec.getLength( ) > MAX_SPEED ) {
			vec = vec.normalize( ) * MAX_SPEED;
		}
		setVec( vec );
	} else {
		Vector vec = AStar( getNearRoadPos( goal ) );
		if ( vec.getLength( ) == 1.0 ) {
			vec = vec * MOVE_SPEED + getVec( );
		}

		if ( vec.getLength2( ) > MAX_SPEED * MAX_SPEED ) {
			vec = vec.normalize( ) * MAX_SPEED;
		}
		setVec( vec );
	}
}

void Enemy::adjustVec( ) {
	SceneStagePtr scene_stage = SceneStage::getTask( );
	const int CHIP_SIZE = scene_stage->getChipSize( );
	const int CHARA_SIZE = scene_stage->getCharaSize( );
	Vector f_pos = getPos( ) + getVec( );
	Vector vec = getVec( );
	if ( ( int )f_pos.x % CHIP_SIZE != CHIP_SIZE / 2 && vec.x == 0 ) {
		vec.x += CHIP_SIZE / 2 - ( int )f_pos.x % CHIP_SIZE ;
	}
	if ( ( int )f_pos.y % CHIP_SIZE != CHARA_SIZE && vec.y == 0 ) {
		vec.y += ( CHARA_SIZE ) - ( int )f_pos.y % CHIP_SIZE;
	}

	if ( vec.getLength( ) > MAX_SPEED ) {
		vec = vec.normalize( ) * MAX_SPEED;
	}
	setVec( vec );
}

void Enemy::setHide( ) {
	_action = ACTION_HIDE;
	_hide_time = INIT_HIDE_TIME;
	setPos( _start_pos );
	setVec( Vector( ) );
	setColl( false ); //characterの処理を軽く
}

bool Enemy::isAction( ) const {
	return _action == ACTION_ACT;
}

bool Enemy::isDrawing( ) const {
	bool result = true;
	if ( _action == ACTION_HIDE ) {
		if ( _hide_time > POP_TIME ) {
			result = false;
		}
		if ( _hide_time < POP_TIME && _hide_time % 4 < 2 ) {
			result = false;
		}
	}

	return result;
}

Vector Enemy::getCharaSize( ) const {
	const int CHARA_SIZE = SceneStage::getTask( )->getCharaSize( );
	return Vector( 0, -CHARA_SIZE / 2 );
}

Vector Enemy::toStraight( const Vector& start, const Vector& goal ) {
	SceneStagePtr scene_stage = SceneStage::getTask( );
	const int CHIP_SIZE = scene_stage->getChipSize( );
	MapPtr map = scene_stage->getMap( );

	enum DIRECTION {
		UP,
		DOWN,
		LEFT,
		RIGHT,
		MAX_DIRECTION
	};

	const Vector DIRECT[ MAX_DIRECTION ] = {
		Vector(  0, -1 ) * CHIP_SIZE,
		Vector(  0,  1 ) * CHIP_SIZE,
		Vector( -1,  0 ) * CHIP_SIZE,
		Vector(  1,  0 ) * CHIP_SIZE
	};

	Vector count = Vector( );
	int root[ MAX_DIRECTION ] = { 0 };
	for ( int i = 0; i < MAX_DIRECTION; i++, count = Vector( ) ) {
		while ( map->getObject( start + count ) != OBJECT_WALL ) {
			root[ i ]++;
			count += DIRECT[ i ];
		}
	}

	Vector result;
	if ( root[ UP ] > root[ DOWN ] &&
		 root[ UP ] > root[ LEFT ] &&
		 root[ UP ] > root[ RIGHT ] ) {
		result = DIRECT[ UP ]; 
	}
	if ( root[ DOWN ] > root[ UP ] &&
		 root[ DOWN ] > root[ LEFT ] &&
		 root[ DOWN ] > root[ RIGHT ] ) {
		result = DIRECT[ DOWN ];
	}
	if ( root[ LEFT ] > root[ UP ] &&
		 root[ LEFT ] > root[ DOWN ] &&
		 root[ LEFT ] > root[ RIGHT ] ) {
		result = DIRECT[ LEFT ];
	}
	if ( root[ RIGHT ] > root[ UP ] &&
		 root[ RIGHT ] > root[ DOWN ] &&
		 root[ RIGHT ] > root[ LEFT ] ) {
		result = DIRECT[ RIGHT ];
	}
	return result;
}

Vector Enemy::getNearRoadPos( const Vector& goal ) {
	SceneStagePtr scene_stage = SceneStage::getTask( );
	const int CHIP_SIZE = scene_stage->getChipSize( );
	MapPtr map = scene_stage->getMap( );

	if ( map->getObject( goal ) != OBJECT_WALL ) {
		return goal;
	}
	
	enum DIRECTION {
		UP,
		DOWN,
		LEFT,
		RIGHT,
		MAX_DIRECTION
	};

	const Vector DIRECT[ MAX_DIRECTION ] = {
		Vector(  0, -1 ) * CHIP_SIZE,
		Vector(  0,  1 ) * CHIP_SIZE,
		Vector( -1,  0 ) * CHIP_SIZE,
		Vector(  1,  0 ) * CHIP_SIZE
	};

	
	Vector count = Vector( );
	int chip[ MAX_DIRECTION ] = { 0 };
	for ( int i = 0; i < MAX_DIRECTION; i++, count = Vector( ) ) {
		while ( map->getObject( goal + count ) == OBJECT_WALL ) {
			chip[ i ]++;
			count += DIRECT[ i ];
		}
	}

	DIRECTION min_dir = UP;
	for ( int i = 0; i < MAX_DIRECTION; i++ ) {
		if ( chip[ min_dir ] > chip[ i ] ) {
			min_dir = ( DIRECTION )i;
		}
	}

	return goal + DIRECT[ min_dir ] * chip[ min_dir ];
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
	
	while ( true ) {
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
					}
						if ( pro_up.pos == goal_pos ) {
							pro_up.state = STATE_COLSE;
							open_tmp.push_back( pro_up );
							break;
						}
					if ( map->getObject( ( int )pro_down.pos.x, ( int )pro_down.pos.y ) != OBJECT_WALL ) {
						pro_down.state = STATE_OPEN;
					}
						if ( pro_down.pos == goal_pos ) {
							pro_down.state = STATE_COLSE;
							open_tmp.push_back( pro_down );
							break;
						}
					if ( map->getObject( ( int )pro_left.pos.x, ( int )pro_left.pos.y ) != OBJECT_WALL ) {
						pro_left.state = STATE_OPEN;
					}
						if ( pro_left.pos == goal_pos ) {
							pro_left.state = STATE_COLSE;
							open_tmp.push_back( pro_left );
							break;
						}
					if ( map->getObject( ( int )pro_right.pos.x, ( int )pro_right.pos.y ) != OBJECT_WALL ) {
						pro_right.state = STATE_OPEN;
					}
						if ( pro_right.pos == goal_pos ) {
							pro_right.state = STATE_COLSE;
							open_tmp.push_back( pro_right );
							break;
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
		root.push_back( check );
	}

	int size = ( int )root.size( );
	Vector dir = goal - getPos( );
	const int CHARA_SIZE = SceneStage::getTask( )->getCharaSize( );
	if ( size > 1 ) {
		dir = ( root[ size - 2 ].pos - root[ size - 1 ].pos ).normalize( );
	}
	return dir;
}
