#include <ai/Game.h>
#include <ai/AI.h>
#include <time.h>
void AI_Placement()
{
	AI* p_AI = AI::GetInstance();
	if (p_AI->GetMyTeam() == TEAM_1) {
		Game::PlaceTank(1, 5, 8); //id = 0
		Game::PlaceTank(2, 7, 6);// id =1
		Game::PlaceTank(2, 7, 15); // id =2
		Game::PlaceTank(1, 5, 21 - 8);//id =3
	}
	else if (p_AI->GetMyTeam() == TEAM_2) {
		Game::PlaceTank(1, 21 - 5, 8);
		Game::PlaceTank(2, 14, 6);
		Game::PlaceTank(2, 14, 15);
		Game::PlaceTank(1, 21 - 5, 13);
	}
}

#pragma region MY API
bool HaveWater(float x, float y) {
	if (x >= 9.5 && x <= 11.5 && y >= 2.5 && y <= 8.5) {
		return true;
	}
	else if (x >= 9.5 && x <= 11.5 && y >= 12.5 && y <= 18.5) {
		return true;
	}
	return false;
}
bool IHaveWater(float x, float y) {
	if (x > 9.5 && x < 11.5 && y > 2.5 && y < 8.5) {
		return true;
	}
	else if (x > 9.5 && x < 11.5 && y > 12.5 && y < 18.5) {
		return true;
	}
	return false;
}
bool HaveStone(float x, float y) {
	if (x >= 1.5 && x <= 4.5 && y >= 1.5 && y <= 4.5) {
		return true;
	}
	else if (x >= 16.5 && x <= 19.5 && y >= 1.5 && y <= 4.5) {
		return true;
	}
	else if (x >= 1.5 && x <= 4.5 && y >= 16.5 && y <= 19.5) {
		return true;
	}
	else if (x >= 16.5 && x <= 19.5 && y >= 16.5 && y <= 19.5) {
		return true;
	}
	else if (x >= 0.5 && x <= 2.5 && y >= 9.5 && y <= 11.5) {
		return true;
	}
	else if (x >= 18.5 && x <= 20.5 && y >= 9.5 && y <= 11.5) {
		return true;
	}
	else if (x >= 6.5 && x <= 7.5 && y >= 7.5 && y <= 13.5) {
		return true;
	}
	else if (x >= 13.5 && x <= 14.5 && y >= 7.5 && y <= 13.5) {
		return true;
	}
	else if (x >= 0.5 && x <= 20.5 && y >= -0.5 && y <= 0.5) {
		return true;
	}
	else if (x >= 0.5 && x <= 20.5 && y >= 20.5 && y <= 21.5) {
		return true;
	}
	else if (x >= -0.5 && x <= 0.5 && y >= -0.5 && y <= 21.5) {
		return true;
	}
	else if (x >= 20.5 && x <= 21.5 && y >= -0.5 && y <= 21.5) {
		return true;
	}
	return false;
}
bool HaveObs(float x, float y) {
	AI* ai = AI::GetInstance();
	if (HaveWater(x, y)) {
		return true;
	}
	else if (HaveStone(x, y)) {
		return true;
	}
	else {
		for (int i = 0; i < NUMBER_OF_TANK; i++) {
			Tank* tank = ai->GetMyTank(i);
			float tx = tank->GetX();
			float ty = tank->GetY();
			if (x >= tx - 0.5 && x <= tx + 0.5 && y >= ty - 0.5 && y <= ty + 0.5) {
				return true;
			}
		}
		for (int i = 0; i < NUMBER_OF_TANK; i++) {
			Tank* tank = ai->GetEnemyTank(i);
			float tx = tank->GetX();
			float ty = tank->GetY();
			if (x >= tx - 0.5 && x <= tx + 0.5 && y >= ty - 0.5 && y <= ty + 0.5) {
				return true;
			}
		}
	}
	return false;
}
bool HaveBullet(float x1, float x2, float y1, float y2, int direc) {
	AI* ai = AI::GetInstance();
	std::vector<Bullet*> bls = ai->GetEnemyBullets();
	for (int i = 0; i < bls.size(); i++) {
		if (!bls[i]->IsAlive() || bls[i]->GetDirection() != direc) {
			continue;
		}
		else
		{
			if (bls[i]->GetTeam() == ai->GetOpponentTeam()) {
				float bx = bls[i]->GetX();
				float by = bls[i]->GetY();
				if (bx >= x1 && bx <= x2 && by >= y1 && by <= y2) {
					return true;
				}
			}
		}
	}
	if (direc == 6) {
		if (HaveBullet(x1, x2, y1, y2, 2) || HaveBullet(x1, x2, y1, y2, 4)) {
			return true;
		}
	}
	else if (direc == 5) {
		if (HaveBullet(x1, x2, y1, y2, 1) || HaveBullet(x1, x2, y1, y2, 3)) {
			return true;
		}
	}
	return false;
}
bool HaveBulletOfType(float x1, float x2, float y1, float y2, int direc, int type) {
	AI* ai = AI::GetInstance();
	std::vector<Bullet*> bls = ai->GetEnemyBullets();
	for (int i = 0; i < bls.size(); i++) {
		if (!bls[i]->IsAlive() || bls[i]->GetDirection() != direc) {
			continue;
		}
		else
		{
			if (bls[i]->GetTeam() == ai->GetOpponentTeam()) {
				float bx = bls[i]->GetX();
				float by = bls[i]->GetY();
				if (bx >= x1 && bx <= x2 && by >= y1 && by <= y2 && bls[i]->GetType() == type) {
					return true;
				}
			}
		}
	}
	if (direc == 6) {
		if (HaveBullet(x1, x2, y1, y2, 2) || HaveBullet(x1, x2, y1, y2, 4)) {
			return true;
		}
	}
	else if (direc == 5) {
		if (HaveBullet(x1, x2, y1, y2, 1) || HaveBullet(x1, x2, y1, y2, 3)) {
			return true;
		}
	}
	return false;
}
bool HaveTankEOfType(float x1, float x2, float y1, float y2, int type) {
	AI* ai = AI::GetInstance();
	for (int i = 0; i < NUMBER_OF_TANK; i++)
	{
		Tank* tempTank = ai->GetEnemyTank(i);
		if (tempTank->GetType() == type) {
			float tx = tempTank->GetX();
			float ty = tempTank->GetY();
			if (tx >= x1 && tx <= x2 && ty >= y1 && ty <= y2) {
				return true;
			}
		}

	}
	return false;
}
bool IHaveTankEOfType(float x1, float x2, float y1, float y2, int type) {
	AI* ai = AI::GetInstance();
	for (int i = 0; i < NUMBER_OF_TANK; i++)
	{
		Tank* tempTank = ai->GetEnemyTank(i);
		if (tempTank->GetType() == type) {
			float tx = tempTank->GetX();
			float ty = tempTank->GetY();
			if (tx > x1 && tx < x2 && ty > y1 && ty < y2) {
				return true;
			}
		}

	}
	return false;
}
bool VHaveTankEOfType(float x1, float x2, float y1, float y2, int type) {
	AI* ai = AI::GetInstance();
	for (int i = 0; i < NUMBER_OF_TANK; i++)
	{
		Tank* tempTank = ai->GetEnemyTank(i);
		if (tempTank->GetType() == type) {
			float tx = tempTank->GetX();
			float ty = tempTank->GetY();
			if (tx + 0.5 > x1 && tx - 0.5 < x2 && ty + 0.5 > y1 && ty - 0.5 < y2) {
				return true;
			}
		}
	}
	return false;
}
bool HaveNongSungEOfType(float x1, float x2, float y1, float y2, int type) {
	AI* ai = AI::GetInstance();
	for (int i = 0; i < NUMBER_OF_TANK; i++)
	{
		Tank* tempTank = ai->GetEnemyTank(i);
		if (tempTank->GetType() == type && tempTank->GetHP() > 0) {
			float tx = tempTank->GetX();
			float ty = tempTank->GetY();
			if (tx + 0.2 > x1 && tx - 0.2 < x2 && ty + 0.2 > y1 && ty - 0.2 < y2) {
				return true;
			}
		}
	}
	return false;
}
bool HaveTankMOfType(float x1, float x2, float y1, float y2, int type) {
	AI* ai = AI::GetInstance();
	for (int i = 0; i < NUMBER_OF_TANK; i++)
	{
		Tank* tempTank = ai->GetMyTank(i);
		if (tempTank->GetType() == type) {
			float tx = tempTank->GetX();
			float ty = tempTank->GetY();
			if (tx >= x1 && tx <= x2 && ty >= y1 && ty <= y2) {
				return true;
			}
		}
	}
	return false;
}
bool HaveTankE(float x1, float x2, float y1, float y2) {
	AI* ai = AI::GetInstance();
	for (int i = 0; i < NUMBER_OF_TANK; i++)
	{
		Tank* tempTank = ai->GetEnemyTank(i);
		float tx = tempTank->GetX();
		float ty = tempTank->GetY();
		if (tx >= x1 && tx <= x2 && ty >= y1 && ty <= y2) {
			return true;
		}
	}
	return false;
}
bool HaveTankELive(float x1, float x2, float y1, float y2) {
	AI* ai = AI::GetInstance();
	for (int i = 0; i < NUMBER_OF_TANK; i++)
	{
		Tank* tempTank = ai->GetEnemyTank(i);
		if (tempTank->GetHP() <= 0) {
			continue;
		}
		float tx = tempTank->GetX();
		float ty = tempTank->GetY();
		if (tx >= x1 && tx <= x2 && ty >= y1 && ty <= y2) {
			return true;
		}
	}
	return false;
}
bool IHaveTankE(float x1, float x2, float y1, float y2) {
	AI* ai = AI::GetInstance();
	for (int i = 0; i < NUMBER_OF_TANK; i++)
	{
		Tank* tempTank = ai->GetEnemyTank(i);
		float tx = tempTank->GetX();
		float ty = tempTank->GetY();
		if (tx > x1 && tx < x2 && ty > y1 && ty < y2) {
			return true;
		}
	}
	return false;
}
bool VHaveTankE(float x1, float x2, float y1, float y2) {
	AI* ai = AI::GetInstance();
	for (int i = 0; i < NUMBER_OF_TANK; i++)
	{
		Tank* tempTank = ai->GetEnemyTank(i);
		float tx = tempTank->GetX();
		float ty = tempTank->GetY();
		if ((tx + 0.5 > x1 && tx - 0.5 < x2) && (ty + 0.5 > y1 && ty - 0.5 < y2)) {
			return true;
		}
	}
	return false;
}
bool HaveNongSungE(float x1, float x2, float y1, float y2) {
	AI* ai = AI::GetInstance();
	for (int i = 0; i < NUMBER_OF_TANK; i++)
	{
		Tank* tempTank = ai->GetEnemyTank(i);
		if (tempTank->GetHP() <= 0) continue;
		float tx = tempTank->GetX();
		float ty = tempTank->GetY();
		if ((tx + 0.2 > x1 && tx - 0.2 < x2) && (ty + 0.2 > y1 && ty - 0.2 < y2)) {
			return true;
		}
	}
	return false;
}
bool IsBaseSideEUnderBoth(int hp) {
	AI* ai = AI::GetInstance();
	vector<Base*> bs = ai->GetEnemyBases();
	int count = 0;
	for (int i = 0; i < bs.size(); i++) {
		if (bs[i]->GetHP() <= hp && bs[i]->GetType() == 2) {
			count++;
		}
	}
	if (count == 2) {
		return true;
	}
	else return false;
}
bool IsBaseSideELive(int hp, int id) {
	AI* ai = AI::GetInstance();
	vector<Base*> bs = ai->GetEnemyBases();
	if (bs[id]->GetHP() <= hp && bs[id]->GetType() == 2) {
		return true;
	}
	else return false;
}
bool HaveTankE(float x, float y) {
	AI* ai = AI::GetInstance();
	for (int i = 0; i < NUMBER_OF_TANK; i++)
	{
		Tank* tempTank = ai->GetEnemyTank(i);
		float tx = tempTank->GetX();
		float ty = tempTank->GetY();
		if (x >= tx - 0.5 && x <= tx + 0.5 && y >= ty - 0.5 && y <= ty + 0.5) {
			return true;
		}
	}
	return false;
}
bool DefingBase(Tank* tank) {
	AI* ai = AI::GetInstance();
	float tx = tank->GetX();
	float ty = tank->GetY();
	if (tank->GetTeam() == 1) {
		if (tx >= 1 && tx <= 4 && (ty == 8 || ty == 13)) {
			return true;
		}
		else if (tx == 4 && ty >= 8 && ty <= 13) {
			return true;
		}
		else return false;
	}
	else if (tank->GetTeam() == 2) {
		if (tx >= 17 && tx <= 20 && (ty == 8 || ty == 13)) {
			return true;
		}
		else if (tx == 17 && ty >= 8 && ty <= 13) {
			return true;
		}
		else return false;
	}
	else return false;
}
bool IsDangerous(float x1, float x2, float y1, float y2, int direc) {
	if (HaveBullet(x1, x2, y1, y2, direc) || VHaveTankE(x1, x2, y1, y2)) {
		return true;
	}
}
bool IsDangerousLow(float x1, float x2, float y1, float y2, int direc) {
	if (HaveBullet(x1, x2, y1, y2, direc) || HaveNongSungE(x1, x2, y1, y2)) {
		return true;
	}
}
float Magnitude(Tank* t1, Tank* t2) {
	if (t1->GetHP() <= 0 || t2->GetHP() <= 0) {
		return 100;
	}
	float t1x = t1->GetX();
	float t2x = t2->GetX();
	float t1y = t1->GetY();
	float t2y = t2->GetY();
	float x = t1x - t2x;
	float y = t1y - t2y;
	float x2 = pow(x, 2);
	float y2 = pow(y, 2);
	return sqrt(x2 + y2);
}

void NeDanDocUltra(Tank* tank) {
	float tx = tank->GetX();
	float ty = tank->GetY();
	int i = tank->GetID();
	if (HaveBullet(tx + 0.5, tx + 10, ty, ty + 1, 4)) {
		Game::CommandTank(i, 1, true, false);
	}
	//Dan ben duoi, di len
	else if (HaveBullet(tx + 0.5, tx + 10, ty - 1, ty, 4)) {
		Game::CommandTank(i, 3, true, false);
	}
	//Dan ben tren, di xuong
	else if (HaveBullet(tx - 10, tx - 0.5, ty, ty + 1, 2)) {
		Game::CommandTank(i, 1, true, false);
	}
	//Dan ben duoi, di len
	else if (HaveBullet(tx - 10, tx - 0.5, ty - 1, ty, 2)) {
		Game::CommandTank(i, 3, true, false);
	}
}
void NeDanNgangUltra(Tank* tank) {
	float tx = tank->GetX();
	float ty = tank->GetY();
	int i = tank->GetID();
	//Dan huong 1 ben trai
	if (HaveBullet(tx - 1, tx, ty + 0.5, ty + 10, 1)) {
		Game::CommandTank(i, 2, true, false);
	}
	//Dan huong 1 ben phai
	else if (HaveBullet(tx, tx + 1, ty + 0.5, ty + 10, 1)) {
		Game::CommandTank(i, 4, true, false);
	}
	//Dan huong 3 ben trai
	else if (HaveBullet(tx - 1, tx, ty - 10, ty - 0.5, 1)) {
		Game::CommandTank(i, 2, true, false);
	}
	//Dan huong 3 ben phai
	else if (HaveBullet(tx, tx + 1, ty - 10, ty - 0.5, 1)) {
		Game::CommandTank(i, 4, true, false);
	}
}
#pragma endregion





//UPDATE
void AI_Update()
{
	AI* p_AI = AI::GetInstance();
	Tank* tank0 = p_AI->GetMyTank(0);
	Tank* tank1 = p_AI->GetMyTank(1);
	Tank* tank2 = p_AI->GetMyTank(2);
	Tank* tank3 = p_AI->GetMyTank(3);
	//TANK
	for (int i = 0; i < NUMBER_OF_TANK; i++) {
		Tank* tempTank = p_AI->GetMyTank(i);
		float tx = tempTank->GetX();
		float ty = tempTank->GetY();
		if ((tempTank == NULL) || (tempTank->GetHP() == 0))
			continue;




		if (tempTank->GetTeam() == 1)
		{
			//Phu top
			if (i == 0) {
				//Bound
				if (tx > 5) {
					Game::CommandTank(i, 4, true, false);
				}
				//Neu co dich o ben kia thi se len ban phu
				else if (ty < 6 && !HaveNongSungE(7, 16, 3, 4) && !HaveNongSungE(1, 6, 1, 20) && tempTank->GetCoolDown() > 0) {
					Game::CommandTank(i, 3, true, false);
				}
				else if (ty > 7) {
					Game::CommandTank(i, 1, true, false);
				}
				else if (p_AI->GetIncomingStrike().size() > 0) {
					Game::CommandTank(i, 4, true, false);
				}
				//Da hoi dan
				else if (tempTank->GetCoolDown() <= 0) {
					//Shoot top
					if (HaveNongSungE(tx - 0.2, tx + 0.2, 0, ty)) {
						Game::CommandTank(i, 1, false, true);
					}
					//Shoot bot
					else if (HaveNongSungE(tx - 0.2, tx + 0.2, ty, 20)) {
						Game::CommandTank(i, 3, false, true);
					}
					//Shoot right
					else if (HaveNongSungE(tx, 20, ty - 0.2, ty + 0.2)) {
						Game::CommandTank(i, 2, false, true);
					}
					//Shoot left
					else if (HaveNongSungE(0, tx, ty - 0.2, ty + 0.2)) {
						Game::CommandTank(i, 4, false, true);
					}
					//Ne doc
					//Dan ben tren, di xuong
					else if (HaveBullet(tx, tx + 5, ty - 1, ty, 4) && !HaveNongSungEOfType(tx, tx + 15, ty - 1, ty, 3)) {
						Game::CommandTank(i, 3, true, false);
					}
					else if (HaveBullet(tx - 5, tx, ty - 1, ty, 2) && !HaveNongSungEOfType(tx - 15, tx, ty - 1, ty, 3)) {
						Game::CommandTank(i, 3, true, false);
					}
					//Dan ben duoi, di len
					else if (HaveBullet(tx, tx + 5, ty, ty + 1, 4) && !HaveNongSungEOfType(tx, tx + 15, ty, ty + 1, 3)) {
						Game::CommandTank(i, 1, true, false);
					}
					else if (HaveBullet(tx - 5, tx, ty, ty + 1, 2) && !HaveNongSungEOfType(tx - 15, tx, ty, ty + 1, 3)) {
						Game::CommandTank(i, 1, true, false);
					}
					//Tim theo phuong ngang
					else if (HaveNongSungE(0.5, 1.5, 1, 9) || HaveNongSungE(1.5, 2.5, 5, 9) || HaveNongSungE(2.5, 4.5, 5, 16) || HaveNongSungE(4.5, 5, 1, 20)) {

						if (HaveNongSungE(1, tx, 1, 20)) {
							Game::CommandTank(i, 4, true, false);
						}
						else if (HaveNongSungE(tx, 20, 1, 20)) {
							Game::CommandTank(i, 2, true, false);
						}
						else if (HaveNongSungE(1, 20, 1, ty)) {
							Game::CommandTank(i, 1, true, false);
						}
						else if (HaveNongSungE(1, 20, ty, 20)) {
							Game::CommandTank(i, 3, true, false);
						}
						else {
							Game::CommandTank(i, 2, true, false);
						}
					}
					else if (HaveNongSungE(1, 20, 1, 7.5)) {
						//Tim phuong doc truoc neu co ke dich o ngoai base
						if (HaveNongSungE(1, 20, 1, ty)) {
							Game::CommandTank(i, 1, true, false);
						}
						else if (HaveNongSungE(1, 20, ty, 20)) {
							Game::CommandTank(i, 3, true, false);
						}
						else {
							Game::CommandTank(i, 4, true, false);
						}
					}
					else {
						Game::CommandTank(i, 2, true, false);
					}
				}
				else {
					if (ty < 6) {
						//Ne doc
						if ((HaveBullet(tx - 10, tx + 10, 5.5, 6.5, 6) || HaveNongSungE(tx - 10, tx + 10, 5.5, 6.5)) && (HaveBullet(tx - 10, tx + 10, 6.5, 7.5, 6) || HaveNongSungE(tx - 10, tx + 10, 6.5, 7.5)) && ty < 8) {
							Game::CommandTank(i, 3, true, false);
						}
						else if ((HaveBullet(tx - 10, tx + 10, 5.5, 6.5, 6) || HaveNongSungE(tx - 10, tx + 10, 5.5, 6.5)) && ty < 7) {
							Game::CommandTank(i, 3, true, false);
						}
						else if ((HaveBullet(tx - 10, tx + 10, 6.5, 7.5, 6) || HaveNongSungE(tx - 10, tx + 10, 6.5, 7.5)) && ty > 6) {
							Game::CommandTank(i, 1, true, false);
						}
						else {
							Game::CommandTank(i, 3, true, false);
						}
					}
					//Ne dan
					//Ne ngang, dan ben trai, ne ben phai truoc vi tank ben trai
					else if (HaveBullet(tx - 1, tx, ty - 5, ty + 5, 5) || HaveNongSungE(tx - 1, tx, ty - 5, ty + 5)) {
						Game::CommandTank(i, 2, true, false);
					}
					//Ne ben trai
					else if (HaveBullet(tx, tx + 1, ty - 5, ty + 5, 5) || HaveNongSungE(tx, tx + 1, ty - 5, ty + 5)) {
						Game::CommandTank(i, 4, true, false);
					}
					//Ne doc
					else if ((HaveBullet(tx - 10, tx + 10, 5.5, 6.5, 6) || HaveNongSungE(tx - 10, tx + 10, 5.5, 6.5)) && (HaveBullet(tx - 10, tx + 10, 6.5, 7.5, 6) || HaveNongSungE(tx - 10, tx + 10, 6.5, 7.5)) && ty < 8) {
						Game::CommandTank(i, 3, true, false);
					}
					else if ((HaveBullet(tx - 10, tx + 10, 5.5, 6.5, 6) || HaveNongSungE(tx - 10, tx + 10, 5.5, 6.5)) && ty < 7) {
						Game::CommandTank(i, 3, true, false);
					}
					else if ((HaveBullet(tx - 10, tx + 10, 6.5, 7.5, 6) || HaveNongSungE(tx - 10, tx + 10, 6.5, 7.5)) && ty > 6) {
						Game::CommandTank(i, 1, true, false);
					}
					else {
						Game::CommandTank(i, 2, true, false);
					}
				}
			}
			//Mid top
			else if (i == 1) {
				//Ne strike
				if (p_AI->GetIncomingStrike().size() > 0) {
					if (tx < 9)
						Game::CommandTank(i, 2, true, false);
				}
				//Neu chua pha xong tru
				else if (Magnitude(tempTank, tank2) < 3 && ty >= 16) {
					Game::CommandTank(i, 1, true, false);
				}
				else if (Magnitude(tempTank, tank2) < 3) {
					Game::CommandTank(i, 1, true, false);
				}
				//DEF NHA
				else if (!HaveTankELive(7.5, 20, 1, 20)) {
					if (ty < 6) {
						Game::CommandTank(i, 3, true, false);
					}
					else if (tx > 6) {
						Game::CommandTank(i, 4, true, false);
					}
					else if (ty > 7) {
						Game::CommandTank(i, 1, true, false);
					}
					else if (p_AI->GetIncomingStrike().size() > 0) {
						Game::CommandTank(i, 4, true, false);
					}
					else if (tempTank->GetCoolDown() <= 0) {
						//Shoot top
						if (HaveNongSungE(tx - 0.2, tx + 0.2, 0, ty)) {
							Game::CommandTank(i, 1, false, true);
						}
						//Shoot bot
						else if (HaveNongSungE(tx - 0.2, tx + 0.2, ty, 20)) {
							Game::CommandTank(i, 3, false, true);
						}
						//Shoot right
						else if (HaveNongSungE(tx, 20, ty - 0.2, ty + 0.2)) {
							Game::CommandTank(i, 2, false, true);
						}
						//Shoot left
						else if (HaveNongSungE(0, tx, ty - 0.2, ty + 0.2)) {
							Game::CommandTank(i, 4, false, true);
						}
						//Tim theo phuong ngang
						else if (HaveNongSungE(0.5, 1.5, 1, 9) || HaveNongSungE(1.5, 2.5, 5, 9) || HaveNongSungE(2.5, 4.5, 5, 16) || HaveNongSungE(4.5, 6.5, 1, 20)) {

							if (HaveNongSungE(1, tx, 1, 20)) {
								Game::CommandTank(i, 4, true, false);
							}
							else if (HaveNongSungE(tx, 20, 1, 20)) {
								Game::CommandTank(i, 2, true, false);
							}
							else if (HaveNongSungE(1, 20, 1, ty)) {
								Game::CommandTank(i, 1, true, false);
							}
							else if (HaveNongSungE(1, 20, ty, 20)) {
								Game::CommandTank(i, 3, true, false);
							}
							else {
								Game::CommandTank(i, 2, true, false);
							}
						}
						else if (HaveNongSungE(1, 20, 5.5, 7.5)) {
							//Tim phuong doc truoc neu co ke dich o ngoai base
							if (HaveNongSungE(1, 20, 1, ty)) {
								Game::CommandTank(i, 1, true, false);
							}
							else if (HaveNongSungE(1, 20, ty, 20)) {
								Game::CommandTank(i, 3, true, false);
							}
							else if (HaveNongSungE(1, tx, 1, 20)) {
								Game::CommandTank(i, 4, true, false);
							}
							else if (HaveNongSungE(tx, 20, 1, 20)) {
								Game::CommandTank(i, 2, true, false);
							}
							else {
								Game::CommandTank(i, 2, true, false);
							}
						}
						else {
							Game::CommandTank(i, 2, true, false);
						}
					}
					else {
						//Ne dan
						//Ne ngang, dan ben trai, ne ben phai truoc vi tank ben trai
						if (HaveBullet(tx - 1, tx, ty - 5, ty + 5, 5) || HaveNongSungE(tx - 1, tx, ty - 5, ty + 5)) {
							Game::CommandTank(i, 2, true, false);
						}
						//Ne ben trai
						else if (HaveBullet(tx, tx + 1, ty - 5, ty + 5, 5) || HaveNongSungE(tx, tx + 1, ty - 5, ty + 5)) {
							Game::CommandTank(i, 4, true, false);
						}
						//Ne doc
						else if ((HaveBullet(tx - 10, tx + 10, 5.5, 6.5, 6) || HaveNongSungE(tx - 10, tx + 10, 5.5, 6.5)) && (HaveBullet(tx - 10, tx + 10, 6.5, 7.5, 6) || HaveNongSungE(tx - 10, tx + 10, 6.5, 7.5)) && ty < 8) {
							Game::CommandTank(i, 3, true, false);
						}
						else if ((HaveBullet(tx - 10, tx + 10, 5.5, 6.5, 6) || HaveNongSungE(tx - 10, tx + 10, 5.5, 6.5)) && ty < 7) {
							Game::CommandTank(i, 3, true, false);
						}
						else if ((HaveBullet(tx - 10, tx + 10, 6.5, 7.5, 6) || HaveNongSungE(tx - 10, tx + 10, 6.5, 7.5)) && ty > 6) {
							Game::CommandTank(i, 1, true, false);
						}
						else {
							Game::CommandTank(i, 2, true, false);
						}
					}
				}
				else if (!IsBaseSideELive(0, 1) && ((!HaveBulletOfType(1, 20, 2.5, 3.5, 6, 3) || !HaveBulletOfType(1, 20, 3.5, 4.5, 6, 3)) && (!HaveBulletOfType(1, 20, 16.5, 17.5, 6, 3) || !HaveBulletOfType(1, 20, 17.5, 18.5, 6, 3)) && !HaveNongSungE(7.5, 9.5, 1, 20))) {
					//Bound
					if (tx < 8) {
						Game::CommandTank(i, 2, true, false);
					}
					else if (tx > 9) {
						Game::CommandTank(i, 4, true, false);
					}
					else if (ty < 2.6) {
						Game::CommandTank(i, 3, true, false);
					}
					else if (ty > 4.4) {
						Game::CommandTank(i, 1, true, false);
					}
					// Step 3: trong vung ban duoc
					else if (tx >= 7.5 && tx <= 9.5 && ty >= 2.6 && ty <= 4.4) {
						//Ne dan va ban tru
						if (tempTank->GetCoolDown() <= 0) {
							Game::CommandTank(i, 2, false, true);
						}
						else if ((HaveBullet(tx - 5, tx + 5, 2.2, 3.5, 6)) && ty <= 4.2) {
							Game::CommandTank(i, 3, true, false);
						}
						else if ((HaveBullet(tx - 5, tx + 5, 3.5, 4.7, 6)) && ty >= 2.8) {
							Game::CommandTank(i, 1, true, false);
						}
						else if ((HaveBullet(7.2, 8.5, ty - 8, ty + 8, 5)) && tx <= 9.2) {
							Game::CommandTank(i, 2, true, false);
						}
						else if ((HaveBullet(8.5, 9.8, ty - 8, ty + 8, 5)) && tx >= 7.8) {
							Game::CommandTank(i, 4, true, false);
						}
						else if ((HaveNongSungE(tx - 5, tx + 5, 2.2, 3.5)) && ty <= 4.2) {
							Game::CommandTank(i, 3, true, false);
						}
						else if ((HaveNongSungE(tx - 5, tx + 5, 3.5, 4.7)) && ty >= 2.8) {
							Game::CommandTank(i, 1, true, false);
						}
						else if ((HaveNongSungE(7.2, 8.5, ty - 8, ty + 8)) && tx <= 9.2) {
							Game::CommandTank(i, 2, true, false);
						}
						else if ((HaveNongSungE(8.5, 9.8, ty - 8, ty + 8)) && tx >= 7.8) {
							Game::CommandTank(i, 4, true, false);
						}
						//Replace
						else {
							Game::CommandTank(i, 2, false, true);
						}
					}
					//Replace
					else {
						Game::CommandTank(i, 2, false, true);
					}
				}
				//Da pha tru xong, di san dich
				else {
					//BOUND
					if (tx < 8) {
						Game::CommandTank(i, 2, true, false);
					}
					else if (tx > 9) {
						Game::CommandTank(i, 4, true, false);
					}
					//Da hoi dan
					else if (tempTank->GetCoolDown() <= 0) {
						//Shoot top
						if (HaveNongSungE(tx - 0.3, tx + 0.3, 0, ty)) {
							Game::CommandTank(i, 1, false, true);
						}
						//Shoot bot
						else if (HaveNongSungE(tx - 0.3, tx + 0.3, ty, 20)) {
							Game::CommandTank(i, 3, false, true);
						}
						//Shoot right
						else if (HaveNongSungE(tx, 20, ty - 0.25, ty + 0.25)) {
							Game::CommandTank(i, 2, false, true);
						}
						//Shoot left
						else if (HaveNongSungE(0, tx, ty - 0.25, ty + 0.25)) {
							Game::CommandTank(i, 4, false, true);
						}
						//Ne dan
						//Ne doc
						//Dan ben tren, di xuong
						else if (HaveBullet(tx, tx + 5, ty - 1, ty, 4) && !HaveNongSungEOfType(tx, tx + 15, ty - 1, ty, 3)) {
							Game::CommandTank(i, 3, true, false);
						}
						else if (HaveBullet(tx - 5, tx, ty - 1, ty, 2) && !HaveNongSungEOfType(tx - 15, tx, ty - 1, ty, 3)) {
							Game::CommandTank(i, 3, true, false);
						}
						//Dan ben duoi, di len
						else if (HaveBullet(tx, tx + 5, ty, ty + 1, 4) && !HaveNongSungEOfType(tx, tx + 15, ty, ty + 1, 3)) {
							Game::CommandTank(i, 1, true, false);
						}
						else if (HaveBullet(tx - 5, tx, ty, ty + 1, 2) && !HaveNongSungEOfType(tx - 15, tx, ty, ty + 1, 3)) {
							Game::CommandTank(i, 1, true, false);
						}
						//Ne ngang
						else if ((HaveBullet(7.5, 8.5, ty - 5, ty + 5, 3)) && tx < 9) {
							Game::CommandTank(i, 2, true, false);
						}
						else if ((HaveBullet(7.5, 8.5, ty - 5, ty + 5, 1)) && tx < 9) {
							Game::CommandTank(i, 2, true, false);
						}
						else if ((HaveBullet(8.5, 9.5, ty - 5, ty + 5, 3)) && tx > 8) {
							Game::CommandTank(i, 4, true, false);
						}
						else if ((HaveBullet(8.5, 9.5, ty - 5, ty + 5, 1)) && tx > 8) {
							Game::CommandTank(i, 4, true, false);
						}
						//Tim tank ngang
						//ben trai
						else if (HaveNongSungE(7.5, 8.5, 1, 20)) {
							Game::CommandTank(i, 4, true, false);
						}
						//ben phai
						else if (HaveNongSungE(8.5, 9.5, 1, 20)) {
							Game::CommandTank(i, 2, true, false);
						}
						//Tim tank doc
						//Ben tren
						else if (HaveNongSungE(1, 20, 1, ty)) {
							Game::CommandTank(i, 1, true, false);
						}
						//Ben duoi
						else if (HaveNongSungE(1, 20, ty, 20)) {
							Game::CommandTank(i, 3, true, false);
						}
						//Replace
						else {
							Game::CommandTank(i, 1, true, false);
						}
					}
					//Chua hoi dan
					//NE DAN
					//Ne doc
					//Dan ben tren, di xuong
					else if (HaveBullet(tx, tx + 10, ty - 1, ty, 4)) {
						Game::CommandTank(i, 3, true, false);
					}
					else if (HaveBullet(tx - 10, tx, ty - 1, ty, 2)) {
						Game::CommandTank(i, 3, true, false);
					}
					//Dan ben duoi, di len
					else if (HaveBullet(tx, tx + 10, ty, ty + 1, 4)) {
						Game::CommandTank(i, 1, true, false);
					}
					else if (HaveBullet(tx - 10, tx, ty, ty + 1, 2)) {
						Game::CommandTank(i, 1, true, false);
					}
					//nong sung ben tren, di xuong
					else if (HaveNongSungE(tx - 5, tx + 5, ty - 0.5, ty)) {
						Game::CommandTank(i, 3, true, false);
					}
					//nong sung ben duoi, di len
					else if (HaveNongSungE(tx - 5, tx + 5, ty, ty + 0.5)) {
						Game::CommandTank(i, 1, true, false);
					}
					//Ne Ngang
					else if ((HaveBullet(7.5, 8.5, ty - 5, ty + 5, 3)) && tx <= 9) {
						Game::CommandTank(i, 2, true, false);
					}
					else if ((HaveBullet(7.5, 8.5, ty - 5, ty + 5, 1)) && tx <= 9) {
						Game::CommandTank(i, 2, true, false);
					}
					else if ((HaveBullet(8.5, 9.5, ty - 5, ty + 5, 3)) && tx >= 8) {
						Game::CommandTank(i, 4, true, false);
					}
					else if ((HaveBullet(8.5, 9.5, ty - 5, ty + 5, 1)) && tx >= 8) {
						Game::CommandTank(i, 4, true, false);
					}
					else if ((HaveNongSungE(7.5, 8.5, ty - 5, ty + 5)) && tx <= 9) {
						Game::CommandTank(i, 2, true, false);
					}
					else if ((HaveNongSungE(8.5, 9.5, ty - 5, ty + 5)) && tx >= 8) {
						Game::CommandTank(i, 4, true, false);
					}
					//Replace
					else {
						Game::CommandTank(i, 1, true, false);
					}
				}
			}
			//Mid bot
			else if (i == 2) {
				if (p_AI->GetIncomingStrike().size() > 0) {
					if (tx < 9)
						Game::CommandTank(i, 2, true, false);
				}
				else if (Magnitude(tempTank, tank2) < 3 && ty <= 21 - 16) {
					Game::CommandTank(i, 3, true, false);
				}
				//DEF NHA
				else if (!HaveTankELive(7.5, 20, 1, 20)) {
					//Bound
					if (ty > 21 - 6) {
						Game::CommandTank(i, 1, true, false);
					}
					else if (tx > 6) {
						Game::CommandTank(i, 4, true, false);
					}
					else if (ty < 21 - 7) {
						Game::CommandTank(i, 3, true, false);
					}
					else if (p_AI->GetIncomingStrike().size() > 0) {
						Game::CommandTank(i, 4, true, false);
					}
					else if (tempTank->GetCoolDown() <= 0) {
						//Shoot top
						if (HaveNongSungE(tx - 0.2, tx + 0.2, 0, ty)) {
							Game::CommandTank(i, 1, false, true);
						}
						//Shoot bot
						else if (HaveNongSungE(tx - 0.2, tx + 0.2, ty, 20)) {
							Game::CommandTank(i, 3, false, true);
						}
						//Shoot right
						else if (HaveNongSungE(tx, 20, ty - 0.2, ty + 0.2)) {
							Game::CommandTank(i, 2, false, true);
						}
						//Shoot left
						else if (HaveNongSungE(0, tx, ty - 0.2, ty + 0.2)) {
							Game::CommandTank(i, 4, false, true);
						}
						//Tim theo phuong ngang
						else if (HaveNongSungE(0.5, 1.5, 21 - 9, 21 - 1) || HaveNongSungE(1.5, 2.5, 21 - 9, 21 - 5) || HaveNongSungE(2.5, 4.5, 21 - 16, 21 - 5) || HaveNongSungE(4.5, 6.5, 1, 20)) {

							if (HaveNongSungE(1, tx, 1, 20)) {
								Game::CommandTank(i, 4, true, false);
							}
							else if (HaveNongSungE(tx, 20, 1, 20)) {
								Game::CommandTank(i, 2, true, false);
							}
							else if (HaveNongSungE(1, 20, ty, 20)) {
								Game::CommandTank(i, 3, true, false);
							}
							else if (HaveNongSungE(1, 20, 1, ty)) {
								Game::CommandTank(i, 1, true, false);
							}
							else {
								Game::CommandTank(i, 2, true, false);
							}
						}
						else if (HaveNongSungE(1, 20, 21 - 7.5, 21 - 5.5)) {
							//Tim phuong doc truoc neu co ke dich o ngoai base
							if (HaveNongSungE(1, 20, ty, 20)) {
								Game::CommandTank(i, 3, true, false);
							}
							else if (HaveNongSungE(1, 20, 1, ty)) {
								Game::CommandTank(i, 1, true, false);
							}
							else if (HaveNongSungE(1, tx, 1, 20)) {
								Game::CommandTank(i, 4, true, false);
							}
							else if (HaveNongSungE(tx, 20, 1, 20)) {
								Game::CommandTank(i, 2, true, false);
							}
							else {
								Game::CommandTank(i, 2, true, false);
							}
						}
						else {
							Game::CommandTank(i, 2, true, false);
						}
					}
					else {
						//Ne dan
						//Ne ngang, dan ben trai, ne ben phai truoc vi tank ben trai
						if (HaveBullet(tx - 1, tx, ty - 5, ty + 5, 5) || HaveNongSungE(tx - 1, tx, ty - 5, ty + 5)) {
							Game::CommandTank(i, 2, true, false);
						}
						//Ne ben trai
						else if (HaveBullet(tx, tx + 1, ty - 5, ty + 5, 5) || HaveNongSungE(tx, tx + 1, ty - 5, ty + 5)) {
							Game::CommandTank(i, 4, true, false);
						}
						//Ne doc
						else if ((HaveBullet(tx - 10, tx + 10, 21 - 6.5, 21 - 5.5, 6) || HaveNongSungE(tx - 10, tx + 10, 21 - 6.5, 21 - 5.5)) && (HaveBullet(tx - 10, tx + 10, 21 - 7.5, 21 - 6.5, 6) || HaveNongSungE(tx - 10, tx + 10, 21 - 7.5, 21 - 6.5)) && ty > 21 - 8) {
							Game::CommandTank(i, 1, true, false);
						}
						else if ((HaveBullet(tx - 10, tx + 10, 21 - 6.5, 21 - 5.5, 6) || HaveNongSungE(tx - 10, tx + 10, 21 - 6.5, 21 - 5.5)) && ty > 21 - 7) {
							Game::CommandTank(i, 1, true, false);
						}
						else if ((HaveBullet(tx - 10, tx + 10, 21 - 7.5, 21 - 6.5, 6) || HaveNongSungE(tx - 10, tx + 10, 21 - 7.5, 21 - 6.5)) && ty < 21 - 6) {
							Game::CommandTank(i, 3, true, false);
						}
						else {
							Game::CommandTank(i, 2, true, false);
						}
					}
				}
				//Neu chua pha xong tru
				else if (!IsBaseSideELive(0, 2) && ((!HaveBulletOfType(1, 20, 21 - 3.5, 21 - 2.5, 6, 3) || !HaveBulletOfType(1, 20, 21 - 4.5, 21 - 3.5, 6, 3)) && (!HaveBulletOfType(1, 20, 21 - 17.5, 21 - 16.5, 6, 3) || !HaveBulletOfType(1, 20, 21 - 18.5, 21 - 17.5, 6, 3)) && !HaveNongSungE(7.5, 9.5, 1, 20))) {
					//Bound
					if (tx < 8) {
						Game::CommandTank(i, 2, true, false);
					}
					else if (tx > 9) {
						Game::CommandTank(i, 4, true, false);
					}
					else if (ty > 21 - 2.6) {
						Game::CommandTank(i, 1, true, false);
					}
					else if (ty < 21 - 4.4) {
						Game::CommandTank(i, 3, true, false);
					}
					// Step 3: trong vung ban duoc
					else if (tx >= 7.5 && tx <= 9.5 && ty <= 21 - 2.6 && ty >= 21 - 4.4) {
						//Ne dan va ban tru
						if (tempTank->GetCoolDown() <= 0) {
							Game::CommandTank(i, 2, false, true);
						}
						else if ((HaveBullet(tx - 5, tx + 5, 21 - 3.5, 21 - 2.2, 6)) && ty >= 21 - 4.2) {
							Game::CommandTank(i, 1, true, false);
						}
						else if ((HaveBullet(tx - 5, tx + 5, 21 - 4.7, 21 - 3.5, 6)) && ty <= 21 - 2.8) {
							Game::CommandTank(i, 3, true, false);
						}
						else if ((HaveBullet(7.2, 8.5, ty - 8, ty + 8, 5)) && tx <= 9.2) {
							Game::CommandTank(i, 2, true, false);
						}
						else if ((HaveBullet(8.5, 9.8, ty - 8, ty + 8, 5)) && tx >= 7.8) {
							Game::CommandTank(i, 4, true, false);
						}
						else if ((HaveNongSungE(tx - 5, tx + 5, 21 - 3.5, 21 - 2.2)) && ty >= 21 - 4.2) {
							Game::CommandTank(i, 1, true, false);
						}
						else if ((HaveNongSungE(tx - 5, tx + 5, 21 - 4.7, 21 - 3.5)) && ty <= 21 - 2.8) {
							Game::CommandTank(i, 3, true, false);
						}
						else if ((HaveNongSungE(7.2, 8.5, ty - 8, ty + 8)) && tx <= 9.2) {
							Game::CommandTank(i, 2, true, false);
						}
						else if ((HaveNongSungE(8.5, 9.8, ty - 8, ty + 8)) && tx >= 7.8) {
							Game::CommandTank(i, 4, true, false);
						}
						//Replace
						else {
							Game::CommandTank(i, 2, false, true);
						}
					}
					//Replace
					else {
						Game::CommandTank(i, 2, false, true);
					}
				}
				//Da pha tru xong, di san dich
				else {
					//BOUND
					if (tx < 8) {
						Game::CommandTank(i, 2, true, false);
					}
					else if (tx > 9) {
						Game::CommandTank(i, 4, true, false);
					}
					//Da hoi dan
					else if (tempTank->GetCoolDown() <= 0) {
						//Shoot top
						if (HaveNongSungE(tx - 0.3, tx + 0.3, 0, ty)) {
							Game::CommandTank(i, 1, false, true);
						}
						//Shoot bot
						else if (HaveNongSungE(tx - 0.3, tx + 0.3, ty, 20)) {
							Game::CommandTank(i, 3, false, true);
						}
						//Shoot right
						else if (HaveNongSungE(tx, 20, ty - 0.25, ty + 0.25)) {
							Game::CommandTank(i, 2, false, true);
						}
						//Shoot left
						else if (HaveNongSungE(0, tx, ty - 0.25, ty + 0.25)) {
							Game::CommandTank(i, 4, false, true);
						}
						//Ne dan
						//Ne doc
						//Dan ben duoi, di len
						else if (HaveBullet(tx, tx + 5, ty, ty + 1, 4) && !HaveNongSungEOfType(tx, tx + 15, ty, ty + 1, 3)) {
							Game::CommandTank(i, 1, true, false);
						}
						else if (HaveBullet(tx - 5, tx, ty, ty + 1, 2) && !HaveNongSungEOfType(tx - 15, tx, ty, ty + 1, 3)) {
							Game::CommandTank(i, 1, true, false);
						}
						//Dan ben tren, di xuong
						else if (HaveBullet(tx, tx + 5, ty - 1, ty, 4) && !HaveNongSungEOfType(tx, tx + 15, ty - 1, ty, 3)) {
							Game::CommandTank(i, 3, true, false);
						}
						else if (HaveBullet(tx - 5, tx, ty - 1, ty, 2) && !HaveNongSungEOfType(tx - 15, tx, ty - 1, ty, 3)) {
							Game::CommandTank(i, 3, true, false);
						}
						//Ne ngang
						else if ((HaveBullet(7.5, 8.5, ty - 5, ty + 5, 1)) && tx < 9) {
							Game::CommandTank(i, 2, true, false);
						}
						else if ((HaveBullet(7.5, 8.5, ty - 5, ty + 5, 3)) && tx < 9) {
							Game::CommandTank(i, 2, true, false);
						}
						else if ((HaveBullet(8.5, 9.5, ty - 5, ty + 5, 1)) && tx > 8) {
							Game::CommandTank(i, 4, true, false);
						}
						else if ((HaveBullet(8.5, 9.5, ty - 5, ty + 5, 3)) && tx > 8) {
							Game::CommandTank(i, 4, true, false);
						}
						//Tim tank ngang
						//ben trai
						else if (HaveNongSungE(7.5, 8.5, 1, 20)) {
							Game::CommandTank(i, 4, true, false);
						}
						//ben phai
						else if (HaveNongSungE(8.5, 9.5, 1, 20)) {
							Game::CommandTank(i, 2, true, false);
						}
						//Tim tank doc
						//Ben duoi
						else if (HaveNongSungE(1, 20, ty, 20)) {
							Game::CommandTank(i, 3, true, false);
						}
						//Ben tren
						else if (HaveNongSungE(1, 20, 1, ty)) {
							Game::CommandTank(i, 1, true, false);
						}
						//Replace
						else {
							Game::CommandTank(i, 3, true, false);
						}
					}
					//Chua hoi dan
					//NE DAN
					//Ne doc
					//Dan ben duoi, di len
					else if (HaveBullet(tx, tx + 10, ty, ty + 1, 4)) {
						Game::CommandTank(i, 1, true, false);
					}
					else if (HaveBullet(tx - 10, tx, ty, ty + 1, 2)) {
						Game::CommandTank(i, 1, true, false);
					}
					//Dan ben tren, di xuong
					else if (HaveBullet(tx, tx + 10, ty - 1, ty, 4)) {
						Game::CommandTank(i, 3, true, false);
					}
					else if (HaveBullet(tx - 10, tx, ty - 1, ty, 2)) {
						Game::CommandTank(i, 3, true, false);
					}
					//nong sung ben duoi, di len
					else if (HaveNongSungE(tx - 5, tx + 5, ty, ty + 0.5)) {
						Game::CommandTank(i, 1, true, false);
					}
					//nong sung ben tren, di xuong
					else if (HaveNongSungE(tx - 5, tx + 5, ty - 0.5, ty)) {
						Game::CommandTank(i, 3, true, false);
					}
					//Ne Ngang
					else if ((HaveBullet(7.5, 8.5, ty - 5, ty + 5, 3)) && tx <= 9) {
						Game::CommandTank(i, 2, true, false);
					}
					else if ((HaveBullet(7.5, 8.5, ty - 5, ty + 5, 1)) && tx <= 9) {
						Game::CommandTank(i, 2, true, false);
					}
					else if ((HaveBullet(8.5, 9.5, ty - 5, ty + 5, 3)) && tx >= 8) {
						Game::CommandTank(i, 4, true, false);
					}
					else if ((HaveBullet(8.5, 9.5, ty - 5, ty + 5, 1)) && tx >= 8) {
						Game::CommandTank(i, 4, true, false);
					}
					else if ((HaveNongSungE(7.5, 8.5, ty - 5, ty + 5)) && tx <= 9) {
						Game::CommandTank(i, 2, true, false);
					}
					else if ((HaveNongSungE(8.5, 9.5, ty - 5, ty + 5)) && tx >= 8) {
						Game::CommandTank(i, 4, true, false);
					}
					//Replace
					else {
						Game::CommandTank(i, 3, true, false);
					}
				}
			}
			//Phu bot
			else if (i == 3) {
				//Bound
				if (tx > 5) {
					Game::CommandTank(i, 4, true, false);
				}
				else if (ty > 21 - 6 && !HaveNongSungE(7, 16, 21 - 4, 21 - 3) && !HaveNongSungE(1, 6, 1, 20) && tempTank->GetCoolDown() > 0) {
					Game::CommandTank(i, 1, true, false);
				}
				else if (ty < 21 - 7) {
					Game::CommandTank(i, 3, true, false);
				}
				else if (p_AI->GetIncomingStrike().size() > 0) {
					Game::CommandTank(i, 4, true, false);
				}
				else if (tempTank->GetCoolDown() <= 0) {
					//Shoot top
					if (HaveNongSungE(tx - 0.2, tx + 0.2, 0, ty)) {
						Game::CommandTank(i, 1, false, true);
					}
					//Shoot bot
					else if (HaveNongSungE(tx - 0.2, tx + 0.2, ty, 20)) {
						Game::CommandTank(i, 3, false, true);
					}
					//Shoot right
					else if (HaveNongSungE(tx, 20, ty - 0.2, ty + 0.2)) {
						Game::CommandTank(i, 2, false, true);
					}
					//Shoot left
					else if (HaveNongSungE(0, tx, ty - 0.2, ty + 0.2)) {
						Game::CommandTank(i, 4, false, true);
					}
					//Ne doc
					//Dan ben duoi, di len
					else if (HaveBullet(tx, tx + 5, ty, ty + 1, 4) && !HaveNongSungEOfType(tx, tx + 15, ty, ty + 1, 3)) {
						Game::CommandTank(i, 1, true, false);
					}
					else if (HaveBullet(tx - 5, tx, ty, ty + 1, 2) && !HaveNongSungEOfType(tx - 15, tx, ty, ty + 1, 3)) {
						Game::CommandTank(i, 1, true, false);
					}
					//Dan ben tren, di xuong
					else if (HaveBullet(tx, tx + 5, ty - 1, ty, 4) && !HaveNongSungEOfType(tx, tx + 15, ty - 1, ty, 3)) {
						Game::CommandTank(i, 3, true, false);
					}
					else if (HaveBullet(tx - 5, tx, ty - 1, ty, 2) && !HaveNongSungEOfType(tx - 15, tx, ty - 1, ty, 3)) {
						Game::CommandTank(i, 3, true, false);
					}
					//Tim theo phuong ngang
					else if (HaveNongSungE(0.5, 1.5, 21 - 9, 21 - 1) || HaveNongSungE(1.5, 2.5, 21 - 9, 21 - 5) || HaveNongSungE(2.5, 4.5, 21 - 16, 21 - 5) || HaveNongSungE(4.5, 5, 1, 20)) {

						if (HaveNongSungE(1, tx, 1, 20)) {
							Game::CommandTank(i, 4, true, false);
						}
						else if (HaveNongSungE(tx, 20, 1, 20)) {
							Game::CommandTank(i, 2, true, false);
						}
						else if (HaveNongSungE(1, 20, ty, 20)) {
							Game::CommandTank(i, 3, true, false);
						}
						else if (HaveNongSungE(1, 20, 1, ty)) {
							Game::CommandTank(i, 1, true, false);
						}
						else {
							Game::CommandTank(i, 2, true, false);
						}
					}
					else if (HaveNongSungE(1, 20, 21 - 7.5, 21 - 1)) {
						//Tim phuong doc truoc neu co ke dich o ngoai base
						if (HaveNongSungE(1, 20, ty, 20)) {
							Game::CommandTank(i, 3, true, false);
						}
						else if (HaveNongSungE(1, 20, 1, ty)) {
							Game::CommandTank(i, 1, true, false);
						}
						else if (HaveNongSungE(1, tx, 1, 20)) {
							Game::CommandTank(i, 4, true, false);
						}
						else if (HaveNongSungE(tx, 20, 1, 20)) {
							Game::CommandTank(i, 2, true, false);
						}
						else {
							Game::CommandTank(i, 2, true, false);
						}
					}
					else {
						Game::CommandTank(i, 2, true, false);
					}
				}
				else {
					if (ty > 21 - 6) {
						//Ne doc
						if ((HaveBullet(tx - 10, tx + 10, 21 - 6.5, 21 - 5.5, 6) || HaveNongSungE(tx - 10, tx + 10, 21 - 6.5, 21 - 5.5)) && (HaveBullet(tx - 10, tx + 10, 21 - 7.5, 21 - 6.5, 6) || HaveNongSungE(tx - 10, tx + 10, 21 - 7.5, 21 - 6.5)) && ty > 21 - 8) {
							Game::CommandTank(i, 1, true, false);
						}
						else if ((HaveBullet(tx - 10, tx + 10, 21 - 6.5, 21 - 5.5, 6) || HaveNongSungE(tx - 10, tx + 10, 21 - 6.5, 21 - 5.5)) && ty > 21 - 7) {
							Game::CommandTank(i, 1, true, false);
						}
						else if ((HaveBullet(tx - 10, tx + 10, 21 - 7.5, 21 - 6.5, 6) || HaveNongSungE(tx - 10, tx + 10, 21 - 7.5, 21 - 6.5)) && ty < 21 - 6) {
							Game::CommandTank(i, 3, true, false);
						}
						else {
							Game::CommandTank(i, 1, true, false);
						}
					}
					//Ne dan
					//Ne ngang, dan ben trai, ne ben phai truoc vi tank ben trai
					else if (HaveBullet(tx - 1, tx, ty - 5, ty + 5, 5) || HaveNongSungE(tx - 1, tx, ty - 5, ty + 5)) {
						Game::CommandTank(i, 2, true, false);
					}
					//Ne ben trai
					else if (HaveBullet(tx, tx + 1, ty - 5, ty + 5, 5) || HaveNongSungE(tx, tx + 1, ty - 5, ty + 5)) {
						Game::CommandTank(i, 4, true, false);
					}
					//Ne doc
					else if ((HaveBullet(tx - 10, tx + 10, 21 - 6.5, 21 - 5.5, 6) || HaveNongSungE(tx - 10, tx + 10, 21 - 6.5, 21 - 5.5)) && (HaveBullet(tx - 10, tx + 10, 21 - 7.5, 21 - 6.5, 6) || HaveNongSungE(tx - 10, tx + 10, 21 - 7.5, 21 - 6.5)) && ty > 21 - 8) {
						Game::CommandTank(i, 1, true, false);
					}
					else if ((HaveBullet(tx - 10, tx + 10, 21 - 6.5, 21 - 5.5, 6) || HaveNongSungE(tx - 10, tx + 10, 21 - 6.5, 21 - 5.5)) && ty > 21 - 7) {
						Game::CommandTank(i, 1, true, false);
					}
					else if ((HaveBullet(tx - 10, tx + 10, 21 - 7.5, 21 - 6.5, 6) || HaveNongSungE(tx - 10, tx + 10, 21 - 7.5, 21 - 6.5)) && ty < 21 - 6) {
						Game::CommandTank(i, 3, true, false);
					}
					else {
						Game::CommandTank(i, 2, true, false);
					}
				}
			}
		}
		else if (tempTank->GetTeam() == 2) {
			//Phu top
			if (i == 0) {
				//Bound
				if (tx < 21 - 5) {
					Game::CommandTank(i, 2, true, false);
				}
				else if (ty < 6 && !HaveNongSungE(21 - 16, 21 - 7, 3, 4) && !HaveNongSungE(21 - 6, 21 - 1, 1, 20) && tempTank->GetCoolDown() > 0) {
					Game::CommandTank(i, 3, true, false);
				}
				else if (ty > 7) {
					Game::CommandTank(i, 1, true, false);
				}
				else if (p_AI->GetIncomingStrike().size() > 0) {
					Game::CommandTank(i, 2, true, false);
				}
				else if (tempTank->GetCoolDown() <= 0) {
					//Shoot top
					if (HaveNongSungE(tx - 0.2, tx + 0.2, 0, ty)) {
						Game::CommandTank(i, 1, false, true);
					}
					//Shoot bot
					else if (HaveNongSungE(tx - 0.2, tx + 0.2, ty, 20)) {
						Game::CommandTank(i, 3, false, true);
					}
					//Shoot right
					else if (HaveNongSungE(tx, 20, ty - 0.2, ty + 0.2)) {
						Game::CommandTank(i, 2, false, true);
					}
					//Shoot left
					else if (HaveNongSungE(0, tx, ty - 0.2, ty + 0.2)) {
						Game::CommandTank(i, 4, false, true);
					}
					//Ne doc
						//Dan ben tren, di xuong
					else if (HaveBullet(tx, tx + 5, ty - 1, ty, 4) && !HaveNongSungEOfType(tx, tx + 15, ty - 1, ty, 3)) {
						Game::CommandTank(i, 3, true, false);
					}
					else if (HaveBullet(tx - 5, tx, ty - 1, ty, 2) && !HaveNongSungEOfType(tx - 15, tx, ty - 1, ty, 3)) {
						Game::CommandTank(i, 3, true, false);
					}
					//Dan ben duoi, di len
					else if (HaveBullet(tx, tx + 5, ty, ty + 1, 4) && !HaveNongSungEOfType(tx, tx + 15, ty, ty + 1, 3)) {
						Game::CommandTank(i, 1, true, false);
					}
					else if (HaveBullet(tx - 5, tx, ty, ty + 1, 2) && !HaveNongSungEOfType(tx - 15, tx, ty, ty + 1, 3)) {
						Game::CommandTank(i, 1, true, false);
					}
					//Tim theo phuong ngang
					else if (HaveNongSungE(21 - 1.5, 21 - 0.5, 1, 9) || HaveNongSungE(21 - 2.5, 21 - 1.5, 5, 9) || HaveNongSungE(21 - 4.5, 21 - 2.5, 5, 16) || HaveNongSungE(21 - 5, 21 - 4.5, 1, 20)) {

						if (HaveNongSungE(tx, 20, 1, 20)) {
							Game::CommandTank(i, 2, true, false);
						}
						else if (HaveNongSungE(1, tx, 1, 20)) {
							Game::CommandTank(i, 4, true, false);
						}
						else if (HaveNongSungE(1, 20, 1, ty)) {
							Game::CommandTank(i, 1, true, false);
						}
						else if (HaveNongSungE(1, 20, ty, 20)) {
							Game::CommandTank(i, 3, true, false);
						}
						else {
							Game::CommandTank(i, 4, true, false);
						}
					}
					else if (HaveNongSungE(1, 20, 1, 7.5)) {
						//Tim phuong doc truoc neu co ke dich o ngoai base
						if (HaveNongSungE(1, 20, 1, ty)) {
							Game::CommandTank(i, 1, true, false);
						}
						else if (HaveNongSungE(1, 20, ty, 20)) {
							Game::CommandTank(i, 3, true, false);
						}
						else if (HaveNongSungE(tx, 20, 1, 20)) {
							Game::CommandTank(i, 2, true, false);
						}
						else if (HaveNongSungE(1, tx, 1, 20)) {
							Game::CommandTank(i, 4, true, false);
						}
						else {
							Game::CommandTank(i, 4, true, false);
						}
					}
					else {
						Game::CommandTank(i, 4, true, false);
					}
				}
				else {
					if (ty < 6) {
						//Ne doc
						if ((HaveBullet(tx - 10, tx + 10, 5.5, 6.5, 6) || HaveNongSungE(tx - 10, tx + 10, 5.5, 6.5)) && (HaveBullet(tx - 10, tx + 10, 6.5, 7.5, 6) || HaveNongSungE(tx - 10, tx + 10, 6.5, 7.5)) && ty < 8) {
							Game::CommandTank(i, 3, true, false);
						}
						else if ((HaveBullet(tx - 10, tx + 10, 5.5, 6.5, 6) || HaveNongSungE(tx - 10, tx + 10, 5.5, 6.5)) && ty < 7) {
							Game::CommandTank(i, 3, true, false);
						}
						else if ((HaveBullet(tx - 10, tx + 10, 6.5, 7.5, 6) || HaveNongSungE(tx - 10, tx + 10, 6.5, 7.5)) && ty > 6) {
							Game::CommandTank(i, 1, true, false);
						}
						else {
							Game::CommandTank(i, 3, true, false);
						}
					}
					//Ne dan
					//Ne ben trai
					else if (HaveBullet(tx, tx + 1, ty - 5, ty + 5, 5) || HaveNongSungE(tx, tx + 1, ty - 5, ty + 5)) {
						Game::CommandTank(i, 4, true, false);
					}
					//Ne ngang, dan ben trai, ne ben phai truoc vi tank ben trai
					else if (HaveBullet(tx - 1, tx, ty - 5, ty + 5, 5) || HaveNongSungE(tx - 1, tx, ty - 5, ty + 5)) {
						Game::CommandTank(i, 2, true, false);
					}
					//Ne doc
					else if ((HaveBullet(tx - 10, tx + 10, 5.5, 6.5, 6) || HaveNongSungE(tx - 10, tx + 10, 5.5, 6.5)) && (HaveBullet(tx - 10, tx + 10, 6.5, 7.5, 6) || HaveNongSungE(tx - 10, tx + 10, 6.5, 7.5)) && ty < 8) {
						Game::CommandTank(i, 3, true, false);
					}
					else if ((HaveBullet(tx - 10, tx + 10, 5.5, 6.5, 6) || HaveNongSungE(tx - 10, tx + 10, 5.5, 6.5)) && ty < 7) {
						Game::CommandTank(i, 3, true, false);
					}
					else if ((HaveBullet(tx - 10, tx + 10, 6.5, 7.5, 6) || HaveNongSungE(tx - 10, tx + 10, 6.5, 7.5)) && ty > 6) {
						Game::CommandTank(i, 1, true, false);
					}
					else {
						Game::CommandTank(i, 4, true, false);
					}
				}
			}
			//Mid top
			else if (i == 1) {
				if (p_AI->GetIncomingStrike().size() > 0) {
					if (tx > 21 - 9)
						Game::CommandTank(i, 4, true, true);
				}
				else if (Magnitude(tempTank, tank2) < 3 && ty >= 16) {
					Game::CommandTank(i, 1, true, false);
				}
				else if (Magnitude(tempTank, tank2) < 3) {
					Game::CommandTank(i, 1, true, false);
				}
				//DEF nha
				else if (!HaveTankELive(1, 13.5, 1, 20)) {
					//Bound
					if (ty < 6) {
						Game::CommandTank(i, 3, true, false);
					}
					else if (tx < 21 - 6) {
						Game::CommandTank(i, 2, true, false);
					}
					else if (ty > 7) {
						Game::CommandTank(i, 1, true, false);
					}
					else if (p_AI->GetIncomingStrike().size() > 0) {
						Game::CommandTank(i, 2, true, false);
					}
					else if (tempTank->GetCoolDown() <= 0) {
						//Shoot top
						if (HaveNongSungE(tx - 0.2, tx + 0.2, 0, ty)) {
							Game::CommandTank(i, 1, false, true);
						}
						//Shoot bot
						else if (HaveNongSungE(tx - 0.2, tx + 0.2, ty, 20)) {
							Game::CommandTank(i, 3, false, true);
						}
						//Shoot right
						else if (HaveNongSungE(tx, 20, ty - 0.2, ty + 0.2)) {
							Game::CommandTank(i, 2, false, true);
						}
						//Shoot left
						else if (HaveNongSungE(0, tx, ty - 0.2, ty + 0.2)) {
							Game::CommandTank(i, 4, false, true);
						}
						//Tim theo phuong ngang
						else if (HaveNongSungE(21 - 1.5, 21 - 0.5, 1, 9) || HaveNongSungE(21 - 2.5, 21 - 1.5, 5, 9) || HaveNongSungE(21 - 4.5, 21 - 2.5, 5, 16) || HaveNongSungE(21 - 6.5, 21 - 4.5, 1, 20)) {

							if (HaveNongSungE(tx, 20, 1, 20)) {
								Game::CommandTank(i, 2, true, false);
							}
							else if (HaveNongSungE(1, tx, 1, 20)) {
								Game::CommandTank(i, 4, true, false);
							}
							else if (HaveNongSungE(1, 20, 1, ty)) {
								Game::CommandTank(i, 1, true, false);
							}
							else if (HaveNongSungE(1, 20, ty, 20)) {
								Game::CommandTank(i, 3, true, false);
							}
							else {
								Game::CommandTank(i, 4, true, false);
							}
						}
						else if (HaveNongSungE(1, 20, 5.5, 7.5)) {
							//Tim phuong doc truoc neu co ke dich o ngoai base
							if (HaveNongSungE(1, 20, 1, ty)) {
								Game::CommandTank(i, 1, true, false);
							}
							else if (HaveNongSungE(1, 20, ty, 20)) {
								Game::CommandTank(i, 3, true, false);
							}
							else if (HaveNongSungE(tx, 20, 1, 20)) {
								Game::CommandTank(i, 2, true, false);
							}
							else if (HaveNongSungE(1, tx, 1, 20)) {
								Game::CommandTank(i, 4, true, false);
							}
							else {
								Game::CommandTank(i, 4, true, false);
							}
						}
						else {
							Game::CommandTank(i, 4, true, false);
						}
					}
					else {
						//Ne dan
						//Ne ben trai
						if (HaveBullet(tx, tx + 1, ty - 5, ty + 5, 5) || HaveNongSungE(tx, tx + 1, ty - 5, ty + 5)) {
							Game::CommandTank(i, 4, true, false);
						}
						//Ne ngang, dan ben trai, ne ben phai truoc vi tank ben trai
						else if (HaveBullet(tx - 1, tx, ty - 5, ty + 5, 5) || HaveNongSungE(tx - 1, tx, ty - 5, ty + 5)) {
							Game::CommandTank(i, 2, true, false);
						}
						//Ne doc
						else if ((HaveBullet(tx - 10, tx + 10, 5.5, 6.5, 6) || HaveNongSungE(tx - 10, tx + 10, 5.5, 6.5)) && (HaveBullet(tx - 10, tx + 10, 6.5, 7.5, 6) || HaveNongSungE(tx - 10, tx + 10, 6.5, 7.5)) && ty < 8) {
							Game::CommandTank(i, 3, true, false);
						}
						else if ((HaveBullet(tx - 10, tx + 10, 5.5, 6.5, 6) || HaveNongSungE(tx - 10, tx + 10, 5.5, 6.5)) && ty < 7) {
							Game::CommandTank(i, 3, true, false);
						}
						else if ((HaveBullet(tx - 10, tx + 10, 6.5, 7.5, 6) || HaveNongSungE(tx - 10, tx + 10, 6.5, 7.5)) && ty > 6) {
							Game::CommandTank(i, 1, true, false);
						}
						else {
							Game::CommandTank(i, 4, true, false);
						}
					}
				}
				//Neu chua pha xong tru
				else if (Magnitude(tempTank, tank2) < 2) {
					Game::CommandTank(i, 1, true, false);
				}
				else if (!IsBaseSideELive(0, 1) && ((!HaveBulletOfType(1, 20, 2.5, 3.5, 6, 3) || !HaveBulletOfType(1, 20, 3.5, 4.5, 6, 3)) && (!HaveBulletOfType(1, 20, 16.5, 17.5, 6, 3) || !HaveBulletOfType(1, 20, 17.5, 18.5, 6, 3)) && !HaveNongSungE(21 - 9.5, 21 - 7.5, 1, 20))) {
					//Bound
					if (tx > 21 - 8) {
						Game::CommandTank(i, 4, true, false);
					}
					else if (tx < 21 - 9) {
						Game::CommandTank(i, 2, true, false);
					}
					else if (ty < 2.6) {
						Game::CommandTank(i, 3, true, false);
					}
					else if (ty > 4.4) {
						Game::CommandTank(i, 1, true, false);
					}
					// Step 3: trong vung ban duoc
					else if (tx <= 21 - 7.5 && tx >= 21 - 9.5 && ty >= 2.6 && ty <= 4.4) {
						//Ne dan va ban tru
						if (tempTank->GetCoolDown() <= 0) {
							Game::CommandTank(i, 4, false, true);
						}
						else if ((HaveBullet(tx - 5, tx + 5, 2.2, 3.5, 6)) && ty <= 4.2) {
							Game::CommandTank(i, 3, true, false);
						}
						else if ((HaveBullet(tx - 5, tx + 5, 3.5, 4.7, 6)) && ty >= 2.8) {
							Game::CommandTank(i, 1, true, false);
						}
						else if ((HaveBullet(21 - 8.5, 21 - 7.2, ty - 8, ty + 8, 5)) && tx >= 21 - 9.2) {
							Game::CommandTank(i, 4, true, false);
						}
						else if ((HaveBullet(21 - 9.8, 21 - 8.5, ty - 8, ty + 8, 5)) && tx <= 21 - 7.8) {
							Game::CommandTank(i, 2, true, false);
						}
						else if ((HaveNongSungE(tx - 5, tx + 5, 2.2, 3.5)) && ty <= 4.2) {
							Game::CommandTank(i, 3, true, false);
						}
						else if ((HaveNongSungE(tx - 5, tx + 5, 3.5, 4.7)) && ty >= 2.8) {
							Game::CommandTank(i, 1, true, false);
						}
						else if ((HaveNongSungE(21 - 8.5, 21 - 7.2, ty - 8, ty + 8)) && tx >= 21 - 9.2) {
							Game::CommandTank(i, 4, true, false);
						}
						else if ((HaveNongSungE(21 - 9.8, 21 - 8.5, ty - 8, ty + 8)) && tx <= 21 - 7.8) {
							Game::CommandTank(i, 2, true, false);
						}
						//Replace
						else {
							Game::CommandTank(i, 4, false, true);
						}
					}
					//Replace
					else {
						Game::CommandTank(i, 4, false, true);
					}
				}
				//Da pha tru xong, di san dich
				else {
					//BOUND
					if (tx > 21 - 8) {
						Game::CommandTank(i, 4, true, false);
					}
					else if (tx < 21 - 9) {
						Game::CommandTank(i, 2, true, false);
					}
					//Da hoi dan
					else if (tempTank->GetCoolDown() <= 0) {
						//Shoot top
						if (HaveNongSungE(tx - 0.3, tx + 0.3, 0, ty)) {
							Game::CommandTank(i, 1, false, true);
						}
						//Shoot bot
						else if (HaveNongSungE(tx - 0.3, tx + 0.3, ty, 20)) {
							Game::CommandTank(i, 3, false, true);
						}
						//Shoot right
						else if (HaveNongSungE(tx, 20, ty - 0.25, ty + 0.25)) {
							Game::CommandTank(i, 2, false, true);
						}
						//Shoot left
						else if (HaveNongSungE(0, tx, ty - 0.25, ty + 0.25)) {
							Game::CommandTank(i, 4, false, true);
						}
						//Ne dan
						//Ne doc
						//Dan ben tren, di xuong
						else if (HaveBullet(tx, tx + 5, ty - 1, ty, 4) && !HaveNongSungEOfType(tx, tx + 15, ty - 1, ty, 3)) {
							Game::CommandTank(i, 3, true, false);
						}
						else if (HaveBullet(tx - 5, tx, ty - 1, ty, 2) && !HaveNongSungEOfType(tx - 15, tx, ty - 1, ty, 3)) {
							Game::CommandTank(i, 3, true, false);
						}
						//Dan ben duoi, di len
						else if (HaveBullet(tx, tx + 5, ty, ty + 1, 4) && !HaveNongSungEOfType(tx, tx + 15, ty, ty + 1, 3)) {
							Game::CommandTank(i, 1, true, false);
						}
						else if (HaveBullet(tx - 5, tx, ty, ty + 1, 2) && !HaveNongSungEOfType(tx - 15, tx, ty, ty + 1, 3)) {
							Game::CommandTank(i, 1, true, false);
						}
						//Ne ngang
						else if ((HaveBullet(21 - 8.5, 21 - 7.5, ty - 5, ty + 5, 3)) && tx > 21 - 9) {
							Game::CommandTank(i, 4, true, false);
						}
						else if ((HaveBullet(21 - 8.5, 21 - 7.5, ty - 5, ty + 5, 1)) && tx > 21 - 9) {
							Game::CommandTank(i, 4, true, false);
						}
						else if ((HaveBullet(21 - 9.5, 21 - 8.5, ty - 5, ty + 5, 3)) && tx < 21 - 8) {
							Game::CommandTank(i, 2, true, false);
						}
						else if ((HaveBullet(21 - 9.5, 21 - 8.5, ty - 5, ty + 5, 1)) && tx < 21 - 8) {
							Game::CommandTank(i, 2, true, false);
						}
						//Tim tank ngang
						//ben trai
						else if (HaveNongSungE(21 - 8.5, 21 - 7.5, 1, 20)) {
							Game::CommandTank(i, 2, true, false);
						}
						//ben phai
						else if (HaveNongSungE(21 - 9.5, 21 - 8.5, 1, 20)) {
							Game::CommandTank(i, 4, true, false);
						}
						//Tim tank doc
						//Ben tren
						else if (HaveNongSungE(1, 20, 1, ty)) {
							Game::CommandTank(i, 1, true, false);
						}
						//Ben duoi
						else if (HaveNongSungE(1, 20, ty, 20)) {
							Game::CommandTank(i, 3, true, false);
						}
						//Replace
						else {
							Game::CommandTank(i, 1, true, false);
						}
					}
					//Chua hoi dan
					//NE DAN
					//Ne doc
					//Dan ben tren, di xuong
					else if (HaveBullet(tx, tx + 10, ty - 1, ty, 4)) {
						Game::CommandTank(i, 3, true, false);
					}
					else if (HaveBullet(tx - 10, tx, ty - 1, ty, 2)) {
						Game::CommandTank(i, 3, true, false);
					}
					//Dan ben duoi, di len
					else if (HaveBullet(tx, tx + 10, ty, ty + 1, 4)) {
						Game::CommandTank(i, 1, true, false);
					}
					else if (HaveBullet(tx - 10, tx, ty, ty + 1, 2)) {
						Game::CommandTank(i, 1, true, false);
					}
					//nong sung ben tren, di xuong
					else if (HaveNongSungE(tx - 5, tx + 5, ty - 0.5, ty)) {
						Game::CommandTank(i, 3, true, false);
					}
					//nong sung ben duoi, di len
					else if (HaveNongSungE(tx - 5, tx + 5, ty, ty + 0.5)) {
						Game::CommandTank(i, 1, true, false);
					}
					//Ne Ngang
					else if ((HaveBullet(21 - 8.5, 21 - 7.5, ty - 5, ty + 5, 3)) && tx >= 21 - 9) {
						Game::CommandTank(i, 4, true, false);
					}
					else if ((HaveBullet(21 - 8.5, 21 - 7.5, ty - 5, ty + 5, 1)) && tx >= 21 - 9) {
						Game::CommandTank(i, 4, true, false);
					}
					else if ((HaveBullet(21 - 9.5, 21 - 8.5, ty - 5, ty + 5, 3)) && tx <= 21 - 8) {
						Game::CommandTank(i, 2, true, false);
					}
					else if ((HaveBullet(21 - 9.5, 21 - 8.5, ty - 5, ty + 5, 1)) && tx <= 21 - 8) {
						Game::CommandTank(i, 2, true, false);
					}
					else if ((HaveNongSungE(21 - 8.5, 21 - 7.5, ty - 5, ty + 5)) && tx >= 21 - 9) {
						Game::CommandTank(i, 4, true, false);
					}
					else if ((HaveNongSungE(21 - 9.5, 21 - 8.5, ty - 5, ty + 5)) && tx <= 21 - 8) {
						Game::CommandTank(i, 2, true, false);
					}
					//Replace
					else {
						Game::CommandTank(i, 1, true, false);
					}
				}
			}
			//Mid bot
			else if (i == 2) {
				if (p_AI->GetIncomingStrike().size() > 0) {
					if (tx >= 21 - 9)
						Game::CommandTank(i, 4, true, false);
				}
				else if (Magnitude(tempTank, tank2) < 3 && ty <= 21 - 16) {
					Game::CommandTank(i, 3, true, false);
				}
				//DEF nha
				else if (!HaveTankELive(1, 13.5, 1, 20)) {
					//Bound
					if (ty > 21 - 6) {
						Game::CommandTank(i, 1, true, false);
					}
					else if (tx < 21 - 6) {
						Game::CommandTank(i, 2, true, false);
					}
					else if (ty < 21 - 7) {
						Game::CommandTank(i, 3, true, false);
					}
					else if (p_AI->GetIncomingStrike().size() > 0) {
						Game::CommandTank(i, 2, true, false);
					}
					else if (tempTank->GetCoolDown() <= 0) {
						//Shoot top
						if (HaveNongSungE(tx - 0.2, tx + 0.2, 0, ty)) {
							Game::CommandTank(i, 1, false, true);
						}
						//Shoot bot
						else if (HaveNongSungE(tx - 0.2, tx + 0.2, ty, 20)) {
							Game::CommandTank(i, 3, false, true);
						}
						//Shoot right
						else if (HaveNongSungE(tx, 20, ty - 0.2, ty + 0.2)) {
							Game::CommandTank(i, 2, false, true);
						}
						//Shoot left
						else if (HaveNongSungE(0, tx, ty - 0.2, ty + 0.2)) {
							Game::CommandTank(i, 4, false, true);
						}
						//Tim theo phuong ngang
						else if (HaveNongSungE(21 - 1.5, 21 - 0.5, 21 - 9, 21 - 1) || HaveNongSungE(21 - 2.5, 21 - 1.5, 21 - 9, 21 - 5) || HaveNongSungE(21 - 4.5, 21 - 2.5, 21 - 16, 21 - 5) || HaveNongSungE(21 - 6.5, 21 - 4.5, 1, 20)) {

							if (HaveNongSungE(tx, 20, 1, 20)) {
								Game::CommandTank(i, 2, true, false);
							}
							else if (HaveNongSungE(1, tx, 1, 20)) {
								Game::CommandTank(i, 4, true, false);
							}
							else if (HaveNongSungE(1, 20, ty, 20)) {
								Game::CommandTank(i, 3, true, false);
							}
							else if (HaveNongSungE(1, 20, 1, ty)) {
								Game::CommandTank(i, 1, true, false);
							}
							else {
								Game::CommandTank(i, 4, true, false);
							}
						}
						else if (HaveNongSungE(1, 20, 21 - 7.5, 21 - 5.5)) {
							//Tim phuong doc truoc neu co ke dich o ngoai base
							if (HaveNongSungE(1, 20, ty, 20)) {
								Game::CommandTank(i, 3, true, false);
							}
							else if (HaveNongSungE(1, 20, 1, ty)) {
								Game::CommandTank(i, 1, true, false);
							}
							else if (HaveNongSungE(tx, 20, 1, 20)) {
								Game::CommandTank(i, 2, true, false);
							}
							else if (HaveNongSungE(1, tx, 1, 20)) {
								Game::CommandTank(i, 4, true, false);
							}
							else {
								Game::CommandTank(i, 4, true, false);
							}
						}
						else {
							Game::CommandTank(i, 4, true, false);
						}
					}
					else {
						//Ne dan
						//Ne ben trai
						if (HaveBullet(tx, tx + 1, ty - 5, ty + 5, 5) || HaveNongSungE(tx, tx + 1, ty - 5, ty + 5)) {
							Game::CommandTank(i, 4, true, false);
						}
						//Ne ngang, dan ben trai, ne ben phai truoc vi tank ben trai
						else if (HaveBullet(tx - 1, tx, ty - 5, ty + 5, 5) || HaveNongSungE(tx - 1, tx, ty - 5, ty + 5)) {
							Game::CommandTank(i, 2, true, false);
						}
						//Ne doc
						else if ((HaveBullet(tx - 10, tx + 10, 21 - 6.5, 21 - 5.5, 6) || HaveNongSungE(tx - 10, tx + 10, 21 - 6.5, 21 - 5.5)) && (HaveBullet(tx - 10, tx + 10, 21 - 7.5, 21 - 6.5, 6) || HaveNongSungE(tx - 10, tx + 10, 21 - 7.5, 21 - 6.5)) && ty > 21 - 8) {
							Game::CommandTank(i, 1, true, false);
						}
						else if ((HaveBullet(tx - 10, tx + 10, 21 - 6.5, 21 - 5.5, 6) || HaveNongSungE(tx - 10, tx + 10, 21 - 6.5, 21 - 5.5)) && ty > 21 - 7) {
							Game::CommandTank(i, 1, true, false);
						}
						else if ((HaveBullet(tx - 10, tx + 10, 21 - 7.5, 21 - 6.5, 6) || HaveNongSungE(tx - 10, tx + 10, 21 - 7.5, 21 - 6.5)) && ty < 21 - 6) {
							Game::CommandTank(i, 3, true, false);
						}
						else {
							Game::CommandTank(i, 4, true, false);
						}
					}
				}
				//Neu chua pha xong tru
				else if (!IsBaseSideELive(0, 2) && ((!HaveBulletOfType(1, 20, 21 - 3.5, 21 - 2.5, 6, 3) || !HaveBulletOfType(1, 20, 21 - 4.5, 21 - 3.5, 6, 3)) && (!HaveBulletOfType(1, 20, 21 - 17.5, 21 - 16.5, 6, 3) || !HaveBulletOfType(1, 20, 21 - 18.5, 21 - 17.5, 6, 3)) && !HaveNongSungE(21 - 9.5, 21 - 7.5, 1, 20))) {
					//Bound
					if (tx > 21 - 8) {
						Game::CommandTank(i, 4, true, false);
					}
					else if (tx < 21 - 9) {
						Game::CommandTank(i, 2, true, false);
					}
					else if (ty > 21 - 2.6) {
						Game::CommandTank(i, 1, true, false);
					}
					else if (ty < 21 - 4.4) {
						Game::CommandTank(i, 3, true, false);
					}
					// Step 3: trong vung ban duoc
					else if (tx <= 21 - 7.5 && tx >= 21 - 9.5 && ty <= 21 - 2.6 && ty >= 21 - 4.4) {
						//Ne dan va ban tru
						if (tempTank->GetCoolDown() <= 0) {
							Game::CommandTank(i, 4, false, true);
						}
						else if ((HaveBullet(tx - 5, tx + 5, 21 - 3.5, 21 - 2.2, 6)) && ty >= 21 - 4.2) {
							Game::CommandTank(i, 1, true, false);
						}
						else if ((HaveBullet(tx - 5, tx + 5, 21 - 4.7, 21 - 3.5, 6)) && ty <= 21 - 2.8) {
							Game::CommandTank(i, 3, true, false);
						}
						else if ((HaveBullet(21 - 8.5, 21 - 7.2, ty - 8, ty + 8, 5)) && tx >= 21 - 9.2) {
							Game::CommandTank(i, 4, true, false);
						}
						else if ((HaveBullet(21 - 9.8, 21 - 8.5, ty - 8, ty + 8, 5)) && tx <= 21 - 7.8) {
							Game::CommandTank(i, 2, true, false);
						}
						else if ((HaveNongSungE(tx - 5, tx + 5, 21 - 3.5, 21 - 2.2)) && ty >= 21 - 4.2) {
							Game::CommandTank(i, 1, true, false);
						}
						else if ((HaveNongSungE(tx - 5, tx + 5, 21 - 4.7, 21 - 3.5)) && ty <= 21 - 2.8) {
							Game::CommandTank(i, 3, true, false);
						}
						else if ((HaveNongSungE(21 - 8.5, 21 - 7.2, ty - 8, ty + 8)) && tx >= 21 - 9.2) {
							Game::CommandTank(i, 4, true, false);
						}
						else if ((HaveNongSungE(21 - 9.8, 21 - 8.5, ty - 8, ty + 8)) && tx <= 21 - 7.8) {
							Game::CommandTank(i, 2, true, false);
						}
						//Replace
						else {
							Game::CommandTank(i, 4, false, true);
						}
					}
					//Replace
					else {
						Game::CommandTank(i, 4, false, true);
					}
				}
				//Da pha tru xong, di san dich
				else {
					//BOUND
					if (tx > 21 - 8) {
						Game::CommandTank(i, 4, true, false);
					}
					else if (tx < 21 - 9) {
						Game::CommandTank(i, 2, true, false);
					}
					//Da hoi dan
					else if (tempTank->GetCoolDown() <= 0) {
						//Shoot top
						if (HaveNongSungE(tx - 0.3, tx + 0.3, 0, ty)) {
							Game::CommandTank(i, 1, false, true);
						}
						//Shoot bot
						else if (HaveNongSungE(tx - 0.3, tx + 0.3, ty, 20)) {
							Game::CommandTank(i, 3, false, true);
						}
						//Shoot right
						else if (HaveNongSungE(tx, 20, ty - 0.25, ty + 0.25)) {
							Game::CommandTank(i, 2, false, true);
						}
						//Shoot left
						else if (HaveNongSungE(0, tx, ty - 0.25, ty + 0.25)) {
							Game::CommandTank(i, 4, false, true);
						}
						//Ne dan
						//Ne doc
						//Dan ben duoi, di len
						else if (HaveBullet(tx, tx + 5, ty, ty + 1, 4) && !HaveNongSungEOfType(tx, tx + 15, ty, ty + 1, 3)) {
							Game::CommandTank(i, 1, true, false);
						}
						else if (HaveBullet(tx - 5, tx, ty, ty + 1, 2) && !HaveNongSungEOfType(tx - 15, tx, ty, ty + 1, 3)) {
							Game::CommandTank(i, 1, true, false);
						}
						//Dan ben tren, di xuong
						else if (HaveBullet(tx, tx + 5, ty - 1, ty, 4) && !HaveNongSungEOfType(tx, tx + 15, ty - 1, ty, 3)) {
							Game::CommandTank(i, 3, true, false);
						}
						else if (HaveBullet(tx - 5, tx, ty - 1, ty, 2) && !HaveNongSungEOfType(tx - 15, tx, ty - 1, ty, 3)) {
							Game::CommandTank(i, 3, true, false);
						}
						//Ne ngang
						else if ((HaveBullet(21 - 8.5, 21 - 7.5, ty - 5, ty + 5, 3)) && tx > 21 - 9) {
							Game::CommandTank(i, 4, true, false);
						}
						else if ((HaveBullet(21 - 8.5, 21 - 7.5, ty - 5, ty + 5, 1)) && tx > 21 - 9) {
							Game::CommandTank(i, 4, true, false);
						}
						else if ((HaveBullet(21 - 9.5, 21 - 8.5, ty - 5, ty + 5, 3)) && tx < 21 - 8) {
							Game::CommandTank(i, 2, true, false);
						}
						else if ((HaveBullet(21 - 9.5, 21 - 8.5, ty - 5, ty + 5, 1)) && tx < 21 - 8) {
							Game::CommandTank(i, 2, true, false);
						}
						//Tim tank ngang
						//ben trai
						else if (HaveNongSungE(21 - 8.5, 21 - 7.5, 1, 20)) {
							Game::CommandTank(i, 2, true, false);
						}
						//ben phai
						else if (HaveNongSungE(21 - 9.5, 21 - 8.5, 1, 20)) {
							Game::CommandTank(i, 4, true, false);
						}
						//Tim tank doc
						//Ben duoi
						else if (HaveNongSungE(1, 20, ty, 20)) {
							Game::CommandTank(i, 3, true, false);
						}
						//Ben tren
						else if (HaveNongSungE(1, 20, 1, ty)) {
							Game::CommandTank(i, 1, true, false);
						}
						//Replace
						else {
							Game::CommandTank(i, 3, true, false);
						}
					}
					//Chua hoi dan
					//NE DAN
					//Ne doc
					//Dan ben duoi, di len
					else if (HaveBullet(tx, tx + 10, ty, ty + 1, 4)) {
						Game::CommandTank(i, 1, true, false);
					}
					else if (HaveBullet(tx - 10, tx, ty, ty + 1, 2)) {
						Game::CommandTank(i, 1, true, false);
					}
					//Dan ben tren, di xuong
					else if (HaveBullet(tx, tx + 10, ty - 1, ty, 4)) {
						Game::CommandTank(i, 3, true, false);
					}
					else if (HaveBullet(tx - 10, tx, ty - 1, ty, 2)) {
						Game::CommandTank(i, 3, true, false);
					}
					//nong sung ben duoi, di len
					else if (HaveNongSungE(tx - 5, tx + 5, ty, ty + 0.5)) {
						Game::CommandTank(i, 1, true, false);
					}
					//nong sung ben tren, di xuong
					else if (HaveNongSungE(tx - 5, tx + 5, ty - 0.5, ty)) {
						Game::CommandTank(i, 3, true, false);
					}
					//Ne Ngang
					else if ((HaveBullet(21 - 8.5, 21 - 7.5, ty - 5, ty + 5, 3)) && tx >= 21 - 9) {
						Game::CommandTank(i, 4, true, false);
					}
					else if ((HaveBullet(21 - 8.5, 21 - 7.5, ty - 5, ty + 5, 1)) && tx >= 21 - 9) {
						Game::CommandTank(i, 4, true, false);
					}
					else if ((HaveBullet(21 - 9.5, 21 - 8.5, ty - 5, ty + 5, 3)) && tx <= 21 - 8) {
						Game::CommandTank(i, 2, true, false);
					}
					else if ((HaveBullet(21 - 9.5, 21 - 8.5, ty - 5, ty + 5, 1)) && tx <= 21 - 8) {
						Game::CommandTank(i, 2, true, false);
					}
					else if ((HaveNongSungE(21 - 8.5, 21 - 7.5, ty - 5, ty + 5)) && tx >= 21 - 9) {
						Game::CommandTank(i, 4, true, false);
					}
					else if ((HaveNongSungE(21 - 9.5, 21 - 8.5, ty - 5, ty + 5)) && tx <= 21 - 8) {
						Game::CommandTank(i, 2, true, false);
					}
					//Replace
					else {
						Game::CommandTank(i, 3, true, false);
					}
				}

			}
			//Phu bot
			else if (i == 3) {
				//Bound
				if (tx < 21 - 5) {
					Game::CommandTank(i, 2, true, false);
				}
				else if (ty > 21 - 6 && !HaveNongSungE(21 - 16, 21 - 7, 21 - 4, 21 - 3) && !HaveNongSungE(21 - 6, 21 - 1, 1, 20) && tempTank->GetCoolDown() > 0) {
					Game::CommandTank(i, 1, true, false);
				}
				else if (ty < 21 - 7) {
					Game::CommandTank(i, 3, true, false);
				}
				else if (p_AI->GetIncomingStrike().size() > 0) {
					Game::CommandTank(i, 2, true, false);
				}
				else if (tempTank->GetCoolDown() <= 0) {
					//Shoot top
					if (HaveNongSungE(tx - 0.2, tx + 0.2, 0, ty)) {
						Game::CommandTank(i, 1, false, true);
					}
					//Shoot bot
					else if (HaveNongSungE(tx - 0.2, tx + 0.2, ty, 20)) {
						Game::CommandTank(i, 3, false, true);
					}
					//Shoot right
					else if (HaveNongSungE(tx, 20, ty - 0.2, ty + 0.2)) {
						Game::CommandTank(i, 2, false, true);
					}
					//Shoot left
					else if (HaveNongSungE(0, tx, ty - 0.2, ty + 0.2)) {
						Game::CommandTank(i, 4, false, true);
					}
					//Ne doc
						//Dan ben duoi, di len
					else if (HaveBullet(tx, tx + 5, ty, ty + 1, 4) && !HaveNongSungEOfType(tx, tx + 15, ty, ty + 1, 3)) {
						Game::CommandTank(i, 1, true, false);
					}
					else if (HaveBullet(tx - 5, tx, ty, ty + 1, 2) && !HaveNongSungEOfType(tx - 15, tx, ty, ty + 1, 3)) {
						Game::CommandTank(i, 1, true, false);
					}
					//Dan ben tren, di xuong
					else if (HaveBullet(tx, tx + 5, ty - 1, ty, 4) && !HaveNongSungEOfType(tx, tx + 15, ty - 1, ty, 3)) {
						Game::CommandTank(i, 3, true, false);
					}
					else if (HaveBullet(tx - 5, tx, ty - 1, ty, 2) && !HaveNongSungEOfType(tx - 15, tx, ty - 1, ty, 3)) {
						Game::CommandTank(i, 3, true, false);
					}
					//Tim theo phuong ngang
					else if (HaveNongSungE(21 - 1.5, 21 - 0.5, 21 - 9, 21 - 1) || HaveNongSungE(21 - 2.5, 21 - 1.5, 21 - 9, 21 - 5) || HaveNongSungE(21 - 4.5, 21 - 2.5, 21 - 16, 21 - 5) || HaveNongSungE(21 - 5, 21 - 4.5, 1, 20)) {

						if (HaveNongSungE(tx, 20, 1, 20)) {
							Game::CommandTank(i, 2, true, false);
						}
						else if (HaveNongSungE(1, tx, 1, 20)) {
							Game::CommandTank(i, 4, true, false);
						}
						else if (HaveNongSungE(1, 20, ty, 20)) {
							Game::CommandTank(i, 3, true, false);
						}
						else if (HaveNongSungE(1, 20, 1, ty)) {
							Game::CommandTank(i, 1, true, false);
						}
						else {
							Game::CommandTank(i, 4, true, false);
						}
					}
					else if (HaveNongSungE(1, 20, 21 - 7.5, 21 - 1)) {
						//Tim phuong doc truoc neu co ke dich o ngoai base
						if (HaveNongSungE(1, 20, ty, 20)) {
							Game::CommandTank(i, 3, true, false);
						}
						else if (HaveNongSungE(1, 20, 1, ty)) {
							Game::CommandTank(i, 1, true, false);
						}
						else if (HaveNongSungE(tx, 20, 1, 20)) {
							Game::CommandTank(i, 2, true, false);
						}
						else if (HaveNongSungE(1, tx, 1, 20)) {
							Game::CommandTank(i, 4, true, false);
						}
						else {
							Game::CommandTank(i, 4, true, false);
						}
					}
					else {
						Game::CommandTank(i, 4, true, false);
					}
				}
				else {
					if (ty > 21 - 6) {
						//Ne doc
						if ((HaveBullet(tx - 10, tx + 10, 21 - 6.5, 21 - 5.5, 6) || HaveNongSungE(tx - 10, tx + 10, 21 - 6.5, 21 - 5.5)) && (HaveBullet(tx - 10, tx + 10, 21 - 7.5, 21 - 6.5, 6) || HaveNongSungE(tx - 10, tx + 10, 21 - 7.5, 21 - 6.5)) && ty > 21 - 8) {
							Game::CommandTank(i, 1, true, false);
						}
						else if ((HaveBullet(tx - 10, tx + 10, 21 - 6.5, 21 - 5.5, 6) || HaveNongSungE(tx - 10, tx + 10, 21 - 6.5, 21 - 5.5)) && ty > 21 - 7) {
							Game::CommandTank(i, 1, true, false);
						}
						else if ((HaveBullet(tx - 10, tx + 10, 21 - 7.5, 21 - 6.5, 6) || HaveNongSungE(tx - 10, tx + 10, 21 - 7.5, 21 - 6.5)) && ty < 21 - 6) {
							Game::CommandTank(i, 3, true, false);
						}
						else {
							Game::CommandTank(i, 1, true, false);
						}
					}
					//Ne dan
					//Ne ben trai
					else if (HaveBullet(tx, tx + 1, ty - 5, ty + 5, 5) || HaveNongSungE(tx, tx + 1, ty - 5, ty + 5)) {
						Game::CommandTank(i, 4, true, false);
					}
					//Ne ngang, dan ben trai, ne ben phai truoc vi tank ben trai
					else if (HaveBullet(tx - 1, tx, ty - 5, ty + 5, 5) || HaveNongSungE(tx - 1, tx, ty - 5, ty + 5)) {
						Game::CommandTank(i, 2, true, false);
					}
					//Ne doc
					else if ((HaveBullet(tx - 10, tx + 10, 21 - 6.5, 21 - 5.5, 6) || HaveNongSungE(tx - 10, tx + 10, 21 - 6.5, 21 - 5.5)) && (HaveBullet(tx - 10, tx + 10, 21 - 7.5, 21 - 6.5, 6) || HaveNongSungE(tx - 10, tx + 10, 21 - 7.5, 21 - 6.5)) && ty > 21 - 8) {
						Game::CommandTank(i, 1, true, false);
					}
					else if ((HaveBullet(tx - 10, tx + 10, 21 - 6.5, 21 - 5.5, 6) || HaveNongSungE(tx - 10, tx + 10, 21 - 6.5, 21 - 5.5)) && ty > 21 - 7) {
						Game::CommandTank(i, 1, true, false);
					}
					else if ((HaveBullet(tx - 10, tx + 10, 21 - 7.5, 21 - 6.5, 6) || HaveNongSungE(tx - 10, tx + 10, 21 - 7.5, 21 - 6.5)) && ty < 21 - 6) {
						Game::CommandTank(i, 3, true, false);
					}
					else {
						Game::CommandTank(i, 4, true, false);
					}
				}
			}
		}
	}





	//USE STRIKE
	if (p_AI->HasAirstrike())
	{
		int m_type = 1;
		for (int j = 0; j < 3; j++)
		{
			for (int i = 0; i < NUMBER_OF_TANK; i++)
			{
				Tank* tempTank = p_AI->GetEnemyTank(i);
				if (tempTank->GetHP() > 0) {
					if (tempTank->GetType() == m_type) {
						p_AI->UseAirstrike(tempTank->GetX(), tempTank->GetY());
					}
				}
			}
			m_type++;
		}
	}
	else if (p_AI->HasEMP())
	{
		int m_type = 3;
		for (int j = 0; j < 3; j++)
		{
			for (int i = 0; i < NUMBER_OF_TANK; i++)
			{
				Tank* tempTank = p_AI->GetEnemyTank(i);
				if (tempTank->GetHP() > 0) {
					if (tempTank->GetType() == m_type) {
						p_AI->UseEMP(tempTank->GetX(), tempTank->GetY());
					}
				}
			}
			m_type--;
		}
	}







	//DONT TOUCH
	Game::GetInstance()->SendCommand();
}






#pragma region DONT TOUCH
int main(int argc, char* argv[])
{
	srand(clock());

#ifdef _WIN32
	INT rc;
	WSADATA wsaData;

	rc = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (rc) {
		printf("WSAStartup Failed.\n");
		return 1;
	}
#endif

	Game::CreateInstance();
	Game* p_Game = Game::GetInstance();

	// Create connection
	if (p_Game->Connect(argc, argv) == -1)
	{
		LOG("Failed to connect to server!\n");
		return -1;
	}

	// Set up function pointers
	AI::GetInstance()->PlaceTank = &AI_Placement;
	AI::GetInstance()->Update = &AI_Update;

	// Polling every 100ms until the connection is dead
	p_Game->PollingFromServer();

	Game::DestroyInstance();

#ifdef _WIN32
	WSACleanup();
#endif
	return 0;
}
#pragma endregion