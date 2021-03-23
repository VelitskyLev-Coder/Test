#include "LevelManager.h"


LevelManager::LevelManager(Player& rfPlayer, EnemySpawner& rfEnemySpawner, SoundManager& rfSoundManager):
	player(rfPlayer),enemySpawner(rfEnemySpawner),soundManager(rfSoundManager)
{
	lvl = 1;
	score = 0;
	font.loadFromFile("Fonts/font.otf");
	back.loadFromFile("Textures/backBoard.jpeg");
	background.setTexture(back);
	background.setPosition(600, 0);
	background.setScale(0.6f, 1);

	controlers.setFont(font);
	scoreMsg.setFont(font);
	LvlMsg.setFont(font);

	controlers.setString(string("Left - A\nRight - D\nShoot - Space\nExit - Esc\nOff Sound - \n")
		+string("----------\nBackSpace!!!!!\n----------\n\nbodyBlock is\nallowed\n"));
	controlers.setPosition(630, 100);
	controlers.setOutlineThickness(1.f);
	controlers.setOutlineColor(Color::Black);

	scoreMsg.setString(string("Score\t") + to_string(score));
	scoreMsg.setPosition(630, 550);
	scoreMsg.setOutlineThickness(1);
	scoreMsg.setOutlineColor(Color::Blue);

	LvlMsg.setString(string("Level\t") + to_string(lvl));
	LvlMsg.setPosition(630, 650);
	LvlMsg.setOutlineThickness(1);
	LvlMsg.setOutlineColor(Color::Blue);
	scoreMult = 1;
	
}

void LevelManager::update()
{
	if (lvl * SCORE_TO_LVL < score)
	{
		lvl = score / SCORE_TO_LVL+1;
		soundManager.lvlup.play();
		if (lvl > 10)
			soundManager.win.play();
	}
	switch (lvl)
	{
	case 1:
		player.TIME_FOR_REPEAT_SHOT = 1.f;
		enemySpawner.MIN_RADIUS = 30.f;
		enemySpawner.MAX_RADIUS = 30.f;
		enemySpawner.ENEMY_FALL_VELOSITY = 100.f;
		enemySpawner.TIME_TO_SPAWN = 2.f;
		scoreMult = 10.f;
		break;
	case 2:
		player.TIME_FOR_REPEAT_SHOT = 1.f;
		enemySpawner.MIN_RADIUS = 20.f;
		enemySpawner.MAX_RADIUS = 30.f;
		enemySpawner.ENEMY_FALL_VELOSITY = 130.f;
		enemySpawner.TIME_TO_SPAWN = 1.7f;
		scoreMult = 9.f;
		break;
	case 3:
		player.TIME_FOR_REPEAT_SHOT = 0.8f;
		enemySpawner.MIN_RADIUS = 13.f;
		enemySpawner.MAX_RADIUS = 30.f;
		enemySpawner.ENEMY_FALL_VELOSITY = 150.f;
		enemySpawner.TIME_TO_SPAWN = 1.7f;
		scoreMult = 8.f;
	case 4:
		player.TIME_FOR_REPEAT_SHOT = 0.8f;
		enemySpawner.MIN_RADIUS = 13.f;
		enemySpawner.MAX_RADIUS = 30.f;
		enemySpawner.ENEMY_FALL_VELOSITY = 200.f;
		enemySpawner.TIME_TO_SPAWN = 1.7f;
		scoreMult = 7.f;
		break;
	case 5:
		player.TIME_FOR_REPEAT_SHOT = 0.6f;
		enemySpawner.MIN_RADIUS = 10.f;
		enemySpawner.MAX_RADIUS = 50.f;
		enemySpawner.ENEMY_FALL_VELOSITY = 250.f;
		enemySpawner.TIME_TO_SPAWN = 1.1f;
		scoreMult = 6.f;
		break;
	case 6:
		player.TIME_FOR_REPEAT_SHOT = 0.4f;
		enemySpawner.MIN_RADIUS = 20.f;
		enemySpawner.MAX_RADIUS = 50.f;
		enemySpawner.ENEMY_FALL_VELOSITY = 250.f;
		enemySpawner.TIME_TO_SPAWN = 0.5f;
		scoreMult = 5.f;
		break;
	case 7:
		player.TIME_FOR_REPEAT_SHOT = 0.4f;
		enemySpawner.MIN_RADIUS = 10.f;
		enemySpawner.MAX_RADIUS = 60.f;
		enemySpawner.ENEMY_FALL_VELOSITY = 270.f;
		enemySpawner.TIME_TO_SPAWN = 0.5f;
		scoreMult = 4.f;
		break;
	case 8:
		player.TIME_FOR_REPEAT_SHOT = 0.3f;
		enemySpawner.MIN_RADIUS = 10.f;
		enemySpawner.MAX_RADIUS = 60.f;
		enemySpawner.ENEMY_FALL_VELOSITY = 270.f;
		enemySpawner.TIME_TO_SPAWN = 0.4f;
		scoreMult = 3.f;
		break;
	case 9:
		player.TIME_FOR_REPEAT_SHOT = 0.1f;
		enemySpawner.MIN_RADIUS = 20.f;
		enemySpawner.MAX_RADIUS = 30.f;
		enemySpawner.ENEMY_FALL_VELOSITY = 270.f;
		enemySpawner.TIME_TO_SPAWN = 0.1f;
		scoreMult = 0.5f;
		break;
	case 10:
		player.TIME_FOR_REPEAT_SHOT = 0.04f;
		enemySpawner.MIN_RADIUS = 10.f;
		enemySpawner.MAX_RADIUS = 50.f;
		enemySpawner.ENEMY_FALL_VELOSITY = 450.f;
		enemySpawner.TIME_TO_SPAWN = 0.03f;
		scoreMult = 0.2f;
		break;
	default:
		player.TIME_FOR_REPEAT_SHOT = 100.f;
		enemySpawner.MIN_RADIUS = 295.f;
		enemySpawner.MAX_RADIUS = 295.f;
		enemySpawner.ENEMY_FALL_VELOSITY = 50.f;
		enemySpawner.TIME_TO_SPAWN = 500.f;
		scoreMult = 10.f;
		enemySpawner.reset();

		break;
	}

	scoreMsg.setString(string("Score\t") + to_string(score));
	LvlMsg.setString(string("Level\t") + to_string(lvl));
	if (lvl > 10)
	{
		scoreMsg.setString(string("MAMA-MIA!!!"));
		LvlMsg.setString(string("MAMA-MIA!!!"));
		controlers.setString(string("MAMA-MIA!!!\n")
			+ string("MAMA-MIA!!!\n") + string("MAMA-MIA!!!\n") + string("MAMA-MIA!!!\n")
			+ string("MAMA-MIA!!!\n") + string("MAMA-MIA!!!\n") + string("MAMA-MIA!!!\n"));

	}
}

void LevelManager::draw(RenderWindow& window)
{
	window.draw(background);
	window.draw(controlers);
	window.draw(scoreMsg);
	window.draw(LvlMsg);
}


