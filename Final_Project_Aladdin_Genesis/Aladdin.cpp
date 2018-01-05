#include "Aladdin.h"
#define ALADDIN_XMLFILEPATH "Xml/Aladdin.xml"
#define ALADDIN_SPEED 1.0f

Aladdin* Aladdin::instance = 0;

//contructor of Aladdin class
Aladdin::Aladdin()
{
	aladdin_image = NULL;
	objType = OBJAladdin;
}

//get aladdin current instance (get aladdin pointer)
Aladdin* Aladdin::GetInstance()
{
	if (instance == 0)
	{
		instance = new Aladdin();
	}
	return instance;
}

//load aladdin animation
void Aladdin::LoadResources()
{
	arx = 200;
	ary = 4600;
	x = arx - 18;
	y = ary - 50;
	initx = x;
	inity = y;
	w = 37;
	h = 50;

	keyUp[0] = true;
	keyUp[1] = true;
	keyUp[2] = true;
	status = STANDING;
	standing_time = GetTickCount();
	last_status = status;
	direction = true;
	animation_rate = 10;
	collType = CollAladdin;
	isDead = false;
	isDie = false;
	normalx = 0.0f;
	normaly = 0.0f;
	last_vy = 0;
	isCreateApple = false;
	isBlink = 0;
	blood = 12;
	score = 0;
	numberofapples = 10;
	numberofrubies = 0;
	numberoflifes = 3;
	isCollStair = false;
	isCutted = false;

	aladdin_image = new Sprite(TextureManager::GetInstance()->GetAladdinTexture(), 0, 0);
}

//update key
void Aladdin::UpdateKey()
{
	if (!dx.Key_Down(DIK_Z))
		keyUp[0] = true;
	if (!dx.Key_Down(DIK_X))
		keyUp[1] = true;
	if (!dx.Key_Down(DIK_C))
		keyUp[2] = true;

	KeyZ = dx.Key_Down(DIK_Z);
	KeyX = dx.Key_Down(DIK_X);
	KeyC = dx.Key_Down(DIK_C);
	KeyLeft = dx.Key_Down(DIK_LEFT);
	KeyRight = dx.Key_Down(DIK_RIGHT);
	KeyDown = dx.Key_Down(DIK_DOWN);
	KeyUp = dx.Key_Down(DIK_UP);
}

//process input
void Aladdin::ProcessInput()
{
	if (status == DIE || isDie)
	{
		Die();
		return;
	}

	//các hành động không thể thay đổi trong khi nó xảy ra
	switch (status)
	{
	case RESETPOSITION:
		ResetPosition();
		return;
	case FLY:
		Fly();
		return;
	case HUG:
		Hug();
		return;
	case RUNNEXT:
		RunNext();
		return;
	}

	UpdateKey();

	//đặt khoảng thời gian nhấp nháy khi bị thương
	if (isBlink != 0)
	{
		isBlink = isBlink % 2 + 1;
		DWORD endBlink = GetTickCount();
		if (endBlink - startBlink > 1200)
		{
			isBlink = 0;
			if (status == HURT)
				status = last_status;
		}
	}

	bool isKeyDown = false;
	if (KeyZ && keyUp[0] && numberofapples > 0)
	{
		Throw();
		isKeyDown = true;
	}
	if (KeyX && keyUp[1])
	{
		Cut();
		isKeyDown = true;
	}
	if (KeyC && keyUp[2])
	{
		Jump();
		isKeyDown = true;
	}
	if (KeyRight || KeyLeft)
	{
		if (normaly == -1.0f && vy >= 0 || isCollStair)
		{
			if (!(normalx != 0 && vx == 0))
			{
				if (status != JUMPING && status != SITTING && status != LOOK_UP)
				{
					Run();
					isKeyDown = true;
				}
			}
			else
			{
				Push();
				isKeyDown = true;
			}
		}
		if (status == SWING || status == SWINGING)
		{
			Swinging();
			isKeyDown = true;
		}

		//Set direction of aladdin
		switch (status)
		{
		case JUMPING: case RUNNING: case RUN_LONG_ENOUGH: case STUNTING:
		case LOOK_UP: case SITTING: case STANDING:
		{
						  if (KeyRight)
							  direction = true;
						  else if (KeyLeft)
							  direction = false;
						  break;
		}
		case CLIMB: case CLIMBING: case SWING: case SWINGING:
		{
						if (KeyLeft)
							direction = true;
						else if (KeyRight)
							direction = false;
						break;
		}
		case CUTTING: case THROWING:
		{
						  if (last_status == CLIMB || last_status == SWING)
						  {
							  if (KeyLeft)
								  direction = true;
							  else if (KeyRight)
								  direction = false;
						  }
						  else
						  {
							  if (KeyRight)
								  direction = true;
							  else if (KeyLeft)
								  direction = false;
						  }
						  break;
		}
		}

		//Set vx of aladdin
		switch (status)
		{
		case JUMPING: case RUNNING: case RUN_LONG_ENOUGH: case STUNTING: case CUTTING: case THROWING:
		{
						  if (KeyRight)
							  vx = ALADDIN_SPEED;
						  else if (KeyLeft)
							  vx = -ALADDIN_SPEED;
						  break;
		}
		case SWINGING:
		{
						 if (KeyLeft)
							 vx = -ALADDIN_SPEED * 2 / 3;
						 else if (KeyRight)
							 vx = ALADDIN_SPEED * 2 / 3;
						 break;
		}
		}
	}
	else
		vx = 0;

	if (KeyDown)
	{
		switch (status)
		{
		case STANDING: case RUNNING: case RUN_LONG_ENOUGH: case SITTING:
		case WAITING_1: case WAITING_2:
		{
							Sit();
							isKeyDown = true;
							break;
		}
		}
	}
	if (KeyUp)
	{
		switch (status)
		{
		case STANDING: case RUNNING: case RUN_LONG_ENOUGH: case LOOK_UP:
		case WAITING_1: case WAITING_2:
		{
							LookUp();
							isKeyDown = true;
							break;
		}
		}
	}
	if (isKeyDown == false)
	{
		switch (status)
		{
		case HURT:
			Hurt();
			break;
		case RUN_LONG_ENOUGH: case BRAKING:
		{
								  if (normalx == 0 && vx != 0 && normaly == -1.0f && vy == 0)
								  {
									  Brake();
								  }
								  else
								  {
									  if (normaly == 0 && !isCollStair)
									  {
										  status = SWING;
										  Jump();
									  }
									  else
										  Stand();
								  }
								  break;
		}
		case THROWING:
			Throw();
			break;
		case CUTTING:
			Cut();
			break;
		case JUMPING:
			Jump();
			break;
		case CLIMB: case CLIMBING:
			break;
		case WAITING_1: case WAITING_2: case WAITING_3:
			Wait();
			break;
		case STUNTING:
			Stunt();
			break;
		case SWINGING: case SWING:
			break;
		default:
		{
				   if (normaly == 0 && normalx == 0 && !isCollStair)
				   {
					   status = SWING;
					   Jump();
				   }
				   else
					   Stand();
				   break;
		}
		}
	}

	if (this->left() < 0 && vx < 0 || this->right() > 4773 && vx > 0)
		vx = 0;

	if (vy > 0)
		last_vy = vy;
	//simulate fall down (gravity)
	vy += 0.1f;
}

//wait action
void Aladdin::Wait()
{
	DWORD start_wait = GetTickCount();
	int i = aladdin_image->getIndex();
	if (start_wait - standing_time > 2000)
	{
		switch (status)
		{
		case STANDING:
		{
						 last_status = status;
						 status = WAITING_1;
						 aladdin_image->setFrame(0, 3);
						 animation_rate = 15;
						 count = -1;
						 break;
		}
		case SWING:
		{
					  last_status = status;
					  status = WAITING_3;
					  aladdin_image->setFrame(183, 179);
					  animation_rate = 10;
					  break;
		}
		case WAITING_1:
		{
						  srand(time(0));
						  int a[4] = { 3, 2, 4, 6 };

						  if (aladdin_image->isActionFinish())
						  {
							  if (rand() % 20 != 19)
							  {
								  count += 2;
								  if (count == 5)
								  {
									  count = -count;
									  count += 2;
								  }
								  if (count > 0)
									  aladdin_image->setFrame(a[count - 1], a[count]);
								  else
									  aladdin_image->setFrame(a[abs(count)], a[abs(count) - 1]);
							  }
							  else
							  {
								  status = WAITING_2;
								  animation_rate = 15;
								  Wait();
								  break;
							  }
						  }
						  if (i == 6 || i == 3)
							  animation_rate = 1;
						  else
							  animation_rate = 15;
						  break;
		}
		case WAITING_2:
		{
						  if (aladdin_image->isActionFinish() && rand() % 5 != 4)
						  {
							  if (i <= 6)
								  aladdin_image->setFrame(13, 27);
							  else
								  aladdin_image->setFrame(18, 27);
							  animation_rate = 15;
						  }
						  else if (aladdin_image->isActionFinish())
						  {
							  aladdin_image->setFrame(28, 44);
							  animation_rate = 15;
						  }
						  break;
		}
		case WAITING_3:
		{
						  if (aladdin_image->isActionFinish())
						  {
							  if (i == 183)
								  aladdin_image->setFrame(179, 183);
							  else
								  aladdin_image->setFrame(183, 179);
						  }
						  if (i == 183 || i == 179)
							  animation_rate = 1;
						  else
							  animation_rate = 10;
						  break;
		}
		}
	}
}

//stand action
void Aladdin::Stand()
{
	int i = aladdin_image->getIndex();
	switch (status)
	{
	case SITTING:
	{
					last_status = status;
					status = STANDING;
					aladdin_image->setFrame(74, 71);
					animation_rate = 15;
					break;
	}
	case LOOK_UP:
	{
					last_status = status;
					status = STANDING;
					aladdin_image->setFrame(70, 68);
					animation_rate = 15;
					break;
	}
	case STANDING:
	{
					 if (!aladdin_image->isActionFinish())
						 break;
					 else
					 {
						 if (i == 70 || i == 74 || i == 106)
						 {
							 last_status = STANDING;
							 status = STANDING;
							 vx = 0;
							 aladdin_image->setFrame(0, 0);
							 standing_time = GetTickCount();
						 }
					 }
					 Wait();
					 break;
	}
	default:
	{
			   if (status == JUMPING && last_vy >= 2.0f)
			   {
				   status = STANDING;
				   vx = 0;
				   aladdin_image->setFrame(106, 117);
				   animation_rate = 17;
				   break;
			   }
			   if (status == PUSHING)
			   {
				   if (direction == true)
					   arx = arx - w / 2;
				   else
					   arx = arx + w / 2;
			   }
			   status = STANDING;
			   last_status = STANDING;
			   vx = 0;
			   aladdin_image->setFrame(0, 0);
			   standing_time = GetTickCount();
			   break;
	}
	}
}

//run action
void Aladdin::Run()
{
	switch (status)
	{
	case RUNNING:
	{
					int i = aladdin_image->getIndex();
					if (i == 138)
						aladdin_image->setFrame(139, 149);
					if (i == 142)
						status = RUN_LONG_ENOUGH;
					break;
	}
	case RUN_LONG_ENOUGH:
		break;
	case JUMPING:
	{
					status = RUN_LONG_ENOUGH;
					aladdin_image->setFrame(139, 149);
					aladdin_image->setIndex(144);
					animation_rate = 15;
					break;
	}
	default:
	{
			   status = RUNNING;
			   aladdin_image->setFrame(137, 149);
			   animation_rate = 15;
			   break;
	}
	}
}

//brake action
void Aladdin::Brake()
{
	switch (status)
	{
	case RUN_LONG_ENOUGH:
	{
							status = BRAKING;
							if (vx > 0)
								vx = 0.25f;
							else
								vx = -0.25f;
							aladdin_image->setFrame(150, 158);
							animation_rate = 20;
							break;
	}
	default:
	{
			   int i = aladdin_image->getIndex();
			   if (i == 150 && aladdin_image->isActionFinish() == true)
				   Stand();
			   break;
	}
	}
}

//jump action
void Aladdin::Jump()
{
	switch (status)
	{
	case STUNTING:
		break;
	case RUNNING: case RUN_LONG_ENOUGH:
	{
					  status = JUMPING;
					  vy -= 1.8f;						//start jump if is not "on-air"
					  aladdin_image->setFrame(87, 95);
					  animation_rate = 10;
					  keyUp[2] = false;
					  break;
	}
	case CLIMB: case CLIMBING:
	{
					last_status = status;
					status = JUMPING;
					vy -= 1.8f;
					aladdin_image->setFrame(196, 204);
					animation_rate = 6;
					keyUp[2] = false;
					break;
	}
	case SWING: case SWINGING: case WAITING_3:
	{
					last_status = STANDING;
					status = JUMPING;
					vy -= 0.3f;
					ary += h;
					aladdin_image->setFrame(99, 105);
					animation_rate = 10;
					keyUp[2] = false;
					break;
	}
	case CUTTING: case THROWING:
	{
					  //
					  if (last_status == SWING || last_status == CLIMB)
					  {
						  status = last_status;
						  Jump();
						  break;
					  }//
					  status = JUMPING;
					  aladdin_image->setFrame(87, 95);
					  aladdin_image->setIndex(92);
					  animation_rate = 10;
					  keyUp[2] = false;
					  break;
	}
	case JUMPING:
	{
					int i = aladdin_image->getIndex();
					if (last_status == CLIMB || last_status == CLIMBING)
					{
						if (i == 196)
							animation_rate = 15;
						if (i == 197)
							animation_rate = 5;
						if (i == 198)
							animation_rate = 17;
					}

					if (i == 105 && normaly == 0.0f)
						aladdin_image->setFrame(105, 105);
					if (i == 93 && normaly == 0.0f)
						aladdin_image->setFrame(93, 93);
					if (i == 204)
					{
						ary += 37;
						aladdin_image->setFrame(99, 105);
					}
					if (normaly == -1.0f && vy == 0)
					{
						if (i > 96 && i <= 105 || i > 87 && i < 95 || 196 < i && i < 204)
						{
							if (KeyRight || KeyLeft)
								Run();
							else
								Stand();
						}
						if (i > 196 && i < 204)
						{
							vy += 0.1;
							normaly = 0;
						}
					}
					break;
	}
	default:
	{
			   if (status == PUSHING)
			   {
				   if (direction == true)
					   arx = arx - w / 2;
				   else
					   arx = arx + w / 2;
			   }
			   last_status = status;
			   status = JUMPING;
			   vy -= 2.0f;						//start jump if is not "on-air"
			   aladdin_image->setFrame(96, 105);
			   animation_rate = 10;
			   keyUp[2] = false;
			   break;
	}
	}
}

//throw apple action
void Aladdin::Throw()
{
	switch (status)
	{
	case RUNNING: case RUN_LONG_ENOUGH: case SWINGING: case CLIMBING: case PUSHING:
		break;
	case SITTING:
	{
					last_status = SITTING;
					status = THROWING;
					vx = 0;
					aladdin_image->setFrame(75, 79);
					animation_rate = 15;
					keyUp[0] = false;
					isCreateApple = false;
					break;
	}
	case JUMPING:
	{
					status = THROWING;
					currentIndex = aladdin_image->getIndex();
					aladdin_image->setFrame(118, 122);
					animation_rate = 11;
					keyUp[0] = false;
					isCreateApple = false;
					break;
	}
	case CLIMB: case SWING: case WAITING_3:
	{
					last_status = status;
					status = THROWING;
					vy = 0;
					if (last_status == CLIMB)
						ary -= 20;
					aladdin_image->setFrame(184, 188);
					animation_rate = 15;
					keyUp[0] = false;
					isCreateApple = false;
					break;
	}
	case THROWING:
	{
					 int i = aladdin_image->getIndex();
					 if ((i == 48 || i == 121 || i == 188 || i == 78) && isCreateApple == false)
					 {
						 GameSound::getInstance()->play(THROW_MUSIC);

						 createApple();
						 isCreateApple = true;
					 }
					 if (aladdin_image->isActionFinish())
					 {
						 switch (last_status)
						 {
						 case CLIMB:
							 ary += 20;
							 Climb();
							 break;
						 case SITTING:
						 {
										 if (KeyDown)
											 Sit();
										 else
										 {
											 status = SITTING;
											 Stand();
										 }
										 break;
						 }
						 case WAITING_3: case SWING:
							 Swing();
							 break;
						 default:
						 {
									if (normaly == 0.0f)
										Jump();
									else
										Stand();
									break;
						 }
						 }
					 }
					 if (118 <= i && i <= 122 && normaly == -1.0f && vy == 0)
						 Stand();
					 break;
	}
	default:
	{
			   if (last_status == SITTING && status != STANDING || last_status == CLIMB || last_status == SWING || last_status == WAITING_3)
			   {
				   if (last_status == CLIMB)
					   ary += 20;
				   status = last_status;
				   Throw();
				   break;
			   }
			   if (last_status == SITTING && status == STANDING)
				   last_status = STANDING;
			   if (normaly == 0.0f || (normaly == -1.0f && vy != 0))
			   {
				   status = JUMPING;
				   Throw();
				   break;
			   }
			   status = THROWING;
			   vx = 0;
			   aladdin_image->setFrame(45, 50);
			   animation_rate = 15;
			   keyUp[0] = false;
			   isCreateApple = false;
			   break;
	}
	}

}

//cut action
void Aladdin::Cut()
{
	switch (status)
	{
	case RUNNING: case RUN_LONG_ENOUGH: case SWINGING: case CLIMBING: case PUSHING:
		break;
	case LOOK_UP:
	{
					last_status = status;
					status = CUTTING;
					vx = 0;
					aladdin_image->setFrame(56, 67);
					animation_rate = 15;
					keyUp[1] = false;
					break;
	}
	case SITTING:
	{
					last_status = SITTING;
					status = CUTTING;
					vx = 0;
					aladdin_image->setFrame(80, 86);
					animation_rate = 15;
					keyUp[1] = false;
					break;
	}
	case CLIMB: case SWING: case WAITING_3:
	{
					last_status = status;
					status = CUTTING;
					vy = 0;
					if (last_status == CLIMB)
						ary -= 20;
					aladdin_image->setFrame(189, 195);
					animation_rate = 15;
					keyUp[1] = false;
					break;
	}
	case JUMPING:
	{
					status = CUTTING;
					aladdin_image->setFrame(123, 128);
					animation_rate = 11;
					keyUp[1] = false;
					break;
	}
	case CUTTING:
	{
					int i = aladdin_image->getIndex();
					if (i == 66 && aladdin_image->getFirstFrame() == 56)
						aladdin_image->setFrame(58, 65);
					if (aladdin_image->isActionFinish())
					{
						GameSound::getInstance()->play(CUT_MUSIC);

						switch (last_status)
						{
						case CLIMB:
						{
									  ary += 20;
									  Climb();
									  break;
						}
						case SITTING:
						{
										if (KeyDown)
											Sit();
										else
										{
											status = SITTING;
											Stand();
										}
										break;
						}
						case LOOK_UP:
						{
										if (i == 58 && aladdin_image->getLastFrame() == 65)
											aladdin_image->setFrame(58, 67);
										else
											Stand();
										break;
						}
						case SWING: case WAITING_3:
							Swing();
							break;
						default:
						{
								   if (normaly == 0.0f || (normaly == -1.0f && vy != 0))
									   Jump();
								   else
									   Stand();
								   break;
						}
						}
					}
					if (123 <= i && i <= 128 && normaly == -1.0f && vy == 0)
						Stand();
					break;
	}
	default:
	{
			   if (last_status == SITTING && status != STANDING || last_status == CLIMB || last_status == SWING || last_status == WAITING_3)
			   {
				   if (last_status == CLIMB)
					   ary += 20;
				   status = last_status;
				   Cut();
				   break;
			   }
			   if (last_status == SITTING && status == STANDING)
				   last_status = STANDING;
			   if (!(normaly == -1.0f && vy == 0))
			   {
				   status = JUMPING;
				   Cut();
				   break;
			   }
			   status = CUTTING;
			   vx = 0;
			   aladdin_image->setFrame(51, 55);
			   animation_rate = 15;
			   keyUp[1] = false;
			   break;
	}
	}

}

//look action
void Aladdin::LookUp()
{
	switch (status)
	{
	case STANDING: case RUNNING: case RUN_LONG_ENOUGH:
	case WAITING_1: case WAITING_2:
	{
						last_status = STANDING;
						status = LOOK_UP;
						vx = 0;
						aladdin_image->setFrame(68, 70);
						animation_rate = 1;
						break;
	}
	case LOOK_UP: case CUTTING: case THROWING:
	{
					  last_status == LOOK_UP;
					  status = LOOK_UP;
					  vx = 0;
					  aladdin_image->setFrame(70, 70);
					  break;
	}
	}
}

//sit action
void Aladdin::Sit()
{
	switch (status)
	{
	case STANDING: case RUNNING: case RUN_LONG_ENOUGH:
	case WAITING_1: case WAITING_2:
	{
						last_status = STANDING;
						status = SITTING;
						vx = 0;
						aladdin_image->setFrame(71, 74);
						animation_rate = 1;
						break;
	}
	case SITTING: case CUTTING: case THROWING:
	{
					  last_status = SITTING;
					  status = SITTING;
					  vx = 0;
					  aladdin_image->setFrame(74, 74);
					  break;
	}
	}
}

//climbing action
void Aladdin::Climb()
{
	switch (status)
	{
	case JUMPING:
	{
					if ((last_status != CLIMB && last_status != CLIMBING) || (last_status == CLIMB && vy > 1.0f) || (last_status == CLIMBING && vy > 1.0f))
					{
						status = CLIMB;
						vx = 0;
						vy = 0;
						currentIndex = rand() % 10 + 159;
						aladdin_image->setFrame(currentIndex, currentIndex);

					}
					break;
	}
	case CLIMB:
	{
				  if (KeyUp)
				  {
					  last_status = status;
					  status = CLIMBING;
					  vx = 0;
					  vy = -0.4f;
					  aladdin_image->setFrame(159, 168);
					  animation_rate = 10;
					  aladdin_image->setIndex(currentIndex);
				  }
				  else if (KeyDown)
				  {
					  last_status = status;
					  status = CLIMBING;
					  vx = 0;
					  vy = 0.4f;
					  aladdin_image->setFrame(168, 159);
					  animation_rate = 10;
					  aladdin_image->setIndex(currentIndex);
				  }
				  break;
	}
	case CLIMBING:
	{
					 if (KeyUp)
					 {
						 vx = 0;
						 vy = -0.4f;
					 }
					 else if (KeyDown)
					 {
						 vx = 0;
						 vy = 0.4f;
					 }
					 else
					 {
						 last_status = status;
						 status = CLIMB;
						 vx = 0;
						 vy = 0;
						 currentIndex = aladdin_image->getIndex();
						 aladdin_image->setFrame(currentIndex, currentIndex);
					 }
					 break;
	}
	case CUTTING: case THROWING:
	{
					  if (aladdin_image->isActionFinish())
					  {
						  status = CLIMB;
						  vx = 0;
						  vy = 0;
						  aladdin_image->setFrame(currentIndex, currentIndex);
					  }
					  break;
	}
	}
}

//swinging action
void Aladdin::Swinging()
{
	switch (status)
	{
	case SWINGING:
		break;
	default:
	{
			   status = SWINGING;
			   aladdin_image->setFrame(169, 178);
			   animation_rate = 15;
			   break;
	}
	}
}

//swing action
void Aladdin::Swing()
{
	switch (status)
	{
	case SWING:
	{
				  Wait();
				  break;
	}
	default:
	{
			   if ((status == CUTTING || status == THROWING) && !aladdin_image->isActionFinish())
				   break;
			   if (status == WAITING_3)
				   break;
			   else
			   {
				   status = SWING;
				   vx = 0;
				   ary -= h;
				   aladdin_image->setFrame(183, 183);
				   standing_time = GetTickCount();
				   Wait();
				   break;
			   }
	}
	}
}

//push action
void Aladdin::Push()
{
	switch (status)
	{
	case PUSHING:
	{
					int i = aladdin_image->getIndex();
					if (direction == true)
					{
						if (KeyLeft)
						{
							Stand();
							break;
						}
						vx = ALADDIN_SPEED;
					}
					else
					{
						if (KeyRight)
						{
							Stand();
							break;
						}
						vx = -ALADDIN_SPEED;
					}
					if (aladdin_image->getFirstFrame() == 205)
						aladdin_image->setFrame(206, 213);
					break;
	}
	default:
	{
			   status = PUSHING;
			   if (direction == true)
			   {
				   arx = x + w;
				   vx = ALADDIN_SPEED;
			   }
			   else
			   {
				   arx = x;
				   vx = -ALADDIN_SPEED;
			   }
			   aladdin_image->setFrame(205, 213);
			   animation_rate = 15;
			   break;
	}
	}
}

//stunt action
void Aladdin::Stunt()
{
	switch (status)
	{
	case STUNTING:
	{
					 int i = aladdin_image->getIndex();
					 if (i == 136 && aladdin_image->getFirstFrame() == 129)
						 aladdin_image->setFrame(130, 135);
					 if (aladdin_image->isActionFinish())
					 {
						 if (aladdin_image->getFirstFrame() == 135)
							 aladdin_image->setFrame(130, 136);
						 else
						 {
							 status = SWING;
							 Jump();
						 }
					 }
					 break;
	}
	default:
	{
			   status = STUNTING;
			   aladdin_image->setFrame(129, 136);
			   animation_rate = 20;
			   vy = -2.5f;
			   break;
	}
	}
}

//hurt action
void Aladdin::Hurt()
{
	switch (status)
	{
	case HURT:
	{
				 break;
	}
	default:
	{
			   if ((status == STANDING || status == WAITING_1 || status == WAITING_3) && !isCollStair)
			   {
				   GameSound::getInstance()->play(HURT_MUSIC);

				   status = HURT;
				   aladdin_image->setFrame(228, 233);
				   animation_rate = 12;
				   vx = 0;
			   }
			   isBlink = 1;
			   startBlink = GetTickCount();
			   blood--;

			   if (blood == 0)
				   Die();
			   break;
	}
	}
}

//die action
void Aladdin::Die()
{
	switch (status)
	{
	case DIE:
	{
				if (aladdin_image->isActionFinish())
				{
					if (numberoflifes == 0)
						isDead = true;
					else
						ResetPosition();
				}
				//isBlink = 0;
				break;
	}
	default:
	{
			   status = DIE;
			   aladdin_image->setFrame(234, 261);
			   animation_rate = 10;
			   isDie = true;
			   direction = true;
			   numberoflifes--;
			   vy = 0;
			   vx = 0;
			   isBlink = 0;
			   break;
	}
	}
}

//run next action
void Aladdin::RunNext()
{
	switch (status)
	{
	case RUNNEXT:
	{
					break;
	}
	default:
	{
			   vx = -0.43f;
			   vy = 0;
			   status = RUNNEXT;
			   aladdin_image->setFrame(276, 283);
			   animation_rate = 15;
			   isBlink = 0;
			   break;
	}
	}
}

//fly action
void Aladdin::Fly()
{
	switch (status)
	{
	case FLY:
	{
				break;
	}
	default:
	{
			   vx = 0.2f;
			   vy = -0.2f;
			   status = FLY;
			   aladdin_image->setFrame(285, 289);
			   animation_rate = 15;
			   isBlink = 0;
			   break;
	}
	}
}

//hug action
void Aladdin::Hug()
{
	switch (status)
	{
	case HUG:
	{
				if (aladdin_image->getIndex() == 299)
				{
					aladdin_image->setFrame(299, 299);
				}
				break;
	}
	default:
	{
			   vx = 0;
			   vy = 0;
			   status = HUG;
			   aladdin_image->setFrame(290, 299);
			   animation_rate = 10;
			   isBlink = 0;
			   break;
	}
	}
}

//reset position when aladdin was dead
void Aladdin::ResetPosition()
{
	switch (status)
	{
	case RESETPOSITION:
	{
						  if (aladdin_image->isActionFinish())
						  {
							  ary -= 20;
							  Stand();
						  }
						  break;
	}
	default:
	{
			   GameSound::getInstance()->play(COMEIN_MUSIC);
			   if (initx > 500)
			   {
				   status = RESETPOSITION;
				   aladdin_image->setFrame(262, 275);
				   animation_rate = 10;
				   isBlink = 0;
				   x = initx;
				   y = inity;
				   arx = x + 6;
				   ary = y + 33;
			   }
			   else
			   {
				   isBlink = 1;
				   x = initx;
				   y = inity;
				   arx = x + 18;
				   ary = y + 50;
				   startBlink = GetTickCount();
				   Stand();
			   }
			   isDie = false;
			   blood = 10;
			   break;
	}
	}
}

//sprite redering
void Aladdin::Render(int Delta)
{
	if (status != CUTTING)
		isCutted = false;

	//update aladdin position
	arx += vx * Delta;
	ary += vy * Delta;

	//render sprite
	aladdin_image->Render(ALADDIN_XMLFILEPATH, x, y, w, h, arx, ary, direction, isBlink);

	//install frame per second (animate rate)
	DWORD now = GetTickCount();
	if (now - last_time > 1000 / animation_rate)
	{
		aladdin_image->Next();
		last_time = now;
	}

}

//collision
void Aladdin::OnCollision(BaseObject* obj, float normalx, float normaly)
{

	switch (obj->collType)
	{
	case CollGround:
		Collision::PreventMove(this, obj, normalx, normaly);
		break;
	case CollStair:
	{
					  isCollStair = true;
					  Collision::CollisionLine(this, obj, normalx, normaly);
	}
		break;
	case CollLine:
	{
					 Collision::CollisionLine(this, obj, normalx, normaly);
					 break;
	}
	case CollCamel:
	{
					  Collision::CollisionLine(this, obj, normalx, normaly);
					  if (normaly == -1.0f && normalx == 0)
						  Jump();
					  break;
	}
	case CollRod:
	{
					Collision::CollisionLine(this, obj, normalx, normaly);
					if (normaly == -1.0f && normalx == 0)
					{
						status = JUMPING;
						Stunt();
					}
					break;
	}
	}
}

//interserct
void Aladdin::OnInterSerct(BaseObject* obj)
{
	if (obj->collType == CollStair)
	{
		isCollStair = true;
		if (ary > obj->top())
		{
			if (vx != 0)
				vy = -0.45f;
			normaly = -1.0f;
		}
		else if (ary == obj->top() && vy < 0 && vy > -0.5)
			vy = 0.1f;
	}

	if (obj->collType == CollCollarBeam)
	{
		//Nhảy khi trèo đến hết 2 đầu xà ngang
		if ((arx < obj->x || arx > obj->x + obj->w) && normalx == 0)
		{
			Jump();
			return;
		}
		if (this->top() < obj->y + obj->h / 2 + 5 && this->top() > obj->y + obj->h / 2 - 5 && vy > 0)
		{
			vy = 0;
			if (!KeyLeft&&!KeyRight || status == JUMPING)
				Swing();
			ary = obj->y + obj->h / 2;
		}
	}

	if (obj->collType == CollRope)
	{
		//Khi trèo xuống hết dây thì Aladdin tự nhảy xuống
		if (ary > obj->y + obj->h && KeyDown)
		{
			if (status == CLIMBING)
				status = SWING;
			Jump();
			return;
		}
		//Khi chạm dây Aladdin sẽ chuyển sang trạng thái trèo (CLIMB)
		if (arx > obj->x + obj->w / 2 - 5 && arx < obj->x + obj->w / 2 + 5 && y > obj->y - 2)
		{
			if (!((last_status == CLIMB || last_status == CLIMBING) && status == JUMPING))
			{
				vy = 0;
				arx = obj->x + obj->w / 2;
				if (ary > obj->bottom())
					ary = obj->bottom();
			}
			if (y < obj->y)
				KeyUp = false;
			Climb();
		}
	}

	if (obj->collType == CollEnemy)
	{
		switch (obj->objType)
		{
		case OBJJar:
		{

					   if (isBlink == 0)
						   Hurt();
					   break;
		}
		case OBJFire:
		{
						if (this->bottom() > obj->top() + 20)
						{
							if (isBlink == 0)
								Hurt();
						}
						break;
		}
		case OBJSword:
		{
						 if (last_status != CLIMB || last_status != CLIMBING || last_status != SWING || last_status != SWINGING)
						 {
							 if (status == CUTTING && (this->direction && this->right() - 2 < obj->arx || !this->direction && this->left() + 2 > obj->arx)){}
							 else
							 {
								 if (isBlink == 0)
									 Hurt();
							 }
						 }
						 else
						 {
							 if (status == CUTTING && ((this->direction && this->left() + 2 > obj->arx) || (!this->direction &&this->right() - 2 < obj->arx))){}
							 else
							 {
								 if (isBlink == 0)
									 Hurt();
							 }
						 }
						 break;
		}
		case OBJBoss:
		{
						if (Collision::AABBCheck(this, obj))
						{
							if (isBlink == 0)
								Hurt();
						}
						break;
		}
		case OBJGuard1: case OBJTheft:
		{
							if (obj->getStatus() == 2)
							{
								if ((!obj->direction && obj->right() > this->left() && obj->arx < this->arx) || (obj->direction && obj->left()<this->right() && obj->arx>this->arx))
								{
									if (isBlink == 0)
										Hurt();
								}
							}
							break;
		}
		case OBJGuard2:
		{
						  if (obj->getStatus() == 2 || obj->getStatus() == 3)
						  {
							  if ((!obj->direction && obj->right() > this->left() && obj->arx < this->arx) || (obj->direction && obj->left()<this->right() && obj->arx>this->arx))
							  {
								  if (isBlink == 0)
									  Hurt();
							  }
						  }
						  break;
		}
		}
	}
	if (obj->collType == CollItem && obj->isActive == false)
	{
		switch (obj->objType)
		{
		case OBJAbuItem:
			score += 250;
			numberoflifes += 1;
			GameSound::getInstance()->play(WOW_MUSIC);
			break;
		case OBJApple:
			numberofapples++;
			break;
		case OBJGenieFace:
			score += 250;
			GameSound::getInstance()->play(WOW_MUSIC);
			break;
		case OBJGenieJar:
			initx = obj->x;
			inity = obj->y;
			break;
		case OBJBlueHeart:
			score += 150;
			blood += 3;
			break;
		case OBJRuby:
			score += 150;
			numberofrubies++;
			break;
		}
	}
}

//create font
void Aladdin::createFont(LPDIRECT3DDEVICE9 d3ddev, D3DXFONT_DESC desc)
{
	D3DXCreateFontIndirect(d3ddev, &desc, &font);
}

//draw font
void Aladdin::drawFont(int x, int y, int width, int height)
{
	//set position of font 
	RECT rect;
	rect.top = y;
	rect.left = x;
	rect.bottom = y + height;
	rect.right = x + width;

	char intStr[20];
	_itoa_s(this->ary, intStr, 10);
	//strcpy_s(intStr, status.c_str());

	font->DrawText(NULL, intStr, -1, &rect, DT_TOP | DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
}

int Aladdin::getStatus()
{
	return status;
}

int Aladdin::getLastStatus()
{
	return last_status;
}

vector<BaseObject*>* Aladdin::GetList()
{
	return &listApple;
}

//create apple
void Aladdin::createApple()
{
	numberofapples--;
	BaseObject* obj = new Apple();
	obj->id = 6;
	obj->setObjectFromID();
	if (last_status == SWING || last_status == SWINGING || last_status == CLIMB || last_status == CLIMBING)
	{
		obj->y = (this->top() + this->bottom()) / 2;
		obj->vy = -0.45f;
		if (!direction)
		{
			obj->x = this->right();
			obj->vx = 2.0f;
		}
		else
		{
			obj->x = this->left();
			obj->vx = -2.0f;
		}
	}
	else
	{
		obj->y = this->top();
		obj->vy = -0.7f;
		if (direction)
		{
			obj->x = this->right();
			obj->vx = 1.7f;
		}
		else
		{
			obj->x = this->left();
			obj->vx = -1.7f;
		}
	}
	obj->direction = this->direction;
	obj->LoadResources();
	listApple.push_back(obj);
}

void Aladdin::createApple(BaseObject*obj)
{
	listApple.push_back(obj);
}

void Aladdin::deleteApple(BaseObject* apple)
{
	for (int i = 0; i < listApple.size(); i++)
	{
		if (listApple.at(i) == apple)
		{
			listApple.erase(listApple.begin() + i);
			delete apple;
			apple = 0;
		}
	}
}

//reset properties
void Aladdin::resetProper()
{
	arx = 200;
	ary = 4600;
	x = arx - 18;
	y = ary - 50;
	initx = 200;
	inity = 4600;
	w = 37;
	h = 50;

	keyUp[0] = true;
	keyUp[1] = true;
	keyUp[2] = true;
	status = STANDING;
	standing_time = GetTickCount();
	last_status = status;
	direction = true;
	animation_rate = 10;
	collType = CollAladdin;
	isDead = false;
	isDie = false;
	normalx = 0.0f;
	normaly = 0.0f;
	last_vy = 0;
	isCreateApple = false;
	isBlink = 0;
	blood = 12;
	score = 0;
	numberofapples = 10;
	numberofrubies = 0;
	numberoflifes = 3;
	isCollStair = false;
	isCutted = false;

	aladdin_image->setFrame(0, 0);
}

//destructor of aladdin class
Aladdin::~Aladdin()
{
	if (instance != NULL){ delete instance; instance = nullptr; }
	if (aladdin_image != NULL){ delete aladdin_image; aladdin_image = nullptr; }
	if (font != NULL){ font->Release(); font = nullptr; }
}