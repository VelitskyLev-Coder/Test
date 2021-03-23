#include "Game.h"

Game::Game()
	:window(VideoMode(WIDTH + 300, HEIGHT), GAME_WINDOW_NAME, Style::Close),
	textures(),
	player(textures),
	levelManager(player, enemySpawner,soundManager)
{
	window.setFramerateLimit(100);

	background.setTexture(textures.background);

}

Game::~Game()
{
}

void Game::mainLoop()
{
	while (window.isOpen())
	{
		eventsProcessing();
		update();
		draw();
	}



}

void Game::eventsProcessing()
{

	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::EventType::Closed)
			window.close();
		if (event.type == Event::EventType::KeyPressed)
			switch (event.key.code)
			{
			case Keyboard::Key::Escape:
				window.close();
				break;
			case Keyboard::Key::BackSpace:
				//off/on sound (A very bad solution)
				soundManager.bounceOffWall.setVolume(abs(soundManager.bounceOffWall.getVolume() - 100));
				soundManager.explosion.setVolume(abs(soundManager.explosion.getVolume() - 100));
				soundManager.fail.setVolume(abs(soundManager.fail.getVolume() - 100));
				soundManager.lvlup.setVolume(abs(soundManager.lvlup.getVolume() - 100));
				soundManager.shot.setVolume(abs(soundManager.shot.getVolume() - 50));
				soundManager.win.setVolume(abs(soundManager.win.getVolume() - 100));

			default:
				break;
			}
	}


	if (Keyboard::isKeyPressed(Keyboard::Key::A))
		player.sendAction(Player::Actions::LEFT);
	if (Keyboard::isKeyPressed(Keyboard::Key::D))
		player.sendAction(Player::Actions::RIGHT);
	if (Keyboard::isKeyPressed(Keyboard::Key::Space))
		player.sendAction(Player::Actions::SHOOT);
}

void Game::update()
{
	float dt = gameClock.getElapsedTime().asSeconds();
	//dt /= 3;

	t++;
	if(t%100==0)
		cout <<"Updates per second\t"<< 1 / dt << endl;
	if (!window.hasFocus())
		dt = 0;

	levelManager.update();

	player.update(dt,bullets,soundManager.shot);

	for (Bullet &bul : bullets)
		bul.update(dt);

	for (Enemy& enemy : enemys)
		enemy.update(dt);

	deletingOutOfBord();
	collisionProcessing();

	for (Explosion&	explosion : explosions)
		explosion.update(dt);

	if (enemySpawner.readyToSpawn(dt))
		enemys.push_back(enemySpawner.spawn(enemys, textures));

	gameClock.restart();
}

void Game::draw()
{
	window.clear();
	window.draw(background);
	player.draw(window);

	for (Bullet &bul : bullets)
		bul.draw(window);

	for (Enemy& enemy : enemys)
		enemy.draw(window);

	for (Explosion& explosion : explosions)
		explosion.draw(window);

	levelManager.draw(window);
	window.display();
}

void Game::deletingOutOfBord()
{
	auto iterToLastValidBullet = remove_if(bullets.begin(), bullets.end(), [](const Bullet& bulet) {
		return bulet.getPosition().y < -bulet.BULET_RADIUS; });
	bullets.erase(iterToLastValidBullet, bullets.end());

	auto iterToLastValidEnemy = remove_if(enemys.begin(), enemys.end(), [](const Enemy& enemy) {
		return enemy.getPosition().y > 900.f; });
	if (iterToLastValidEnemy != enemys.end())
	{
		soundManager.fail.play();
		levelManager.score -= 54 * levelManager.scoreMult*5;
	}
	enemys.erase(iterToLastValidEnemy, enemys.end());
	

	auto iterToLastValidExplosion = remove_if(explosions.begin(), explosions.end(), [](const Explosion& explosion) {
		return explosion.finished(); });
	explosions.erase(iterToLastValidExplosion, explosions.end());
}

void Game::collisionProcessing()
{

	bool flag;

	//Bullets vs 
	float width = WIDTH;
	Sound* pwall = &soundManager.bounceOffWall;
	for_each(bullets.begin(), bullets.end(), [width, pwall](Bullet& bullet) {
		if (bullet.getPosition().x<0 ||
			bullet.getPosition().x>width - 2*bullet.BULET_RADIUS)
		{
			bullet.shiftHorizontalVelosity();
			(*pwall).play();
		}
		});
	/////


	
	//Enemy vs Bullet
	float bulletRadius = 5.f;
	flag = false;
	while (!flag) 
	{
		flag = true;
		for (auto itEnemy = enemys.begin(); itEnemy != enemys.end(); ++itEnemy)
		{
			for (auto itBullet = bullets.begin(); itBullet != bullets.end(); ++itBullet)
			{
				float enemyRadius = (*itEnemy).getRadius();
				Vector2f positionsRefresh = (*itEnemy).getPosition()+Vector2f(enemyRadius, enemyRadius) 
					- (*itBullet).getPosition()- Vector2f(bulletRadius, bulletRadius);
				positionsRefresh = positionsRefresh;
				float scalarProduct =
					positionsRefresh.x * positionsRefresh.x
					+ positionsRefresh.y * positionsRefresh.y;
				if (scalarProduct < (enemyRadius + bulletRadius) * (enemyRadius + bulletRadius))
				{
					explosions.push_back(Explosion((*itEnemy).getPosition() + Vector2f(enemyRadius, enemyRadius),
						textures.explosion, enemyRadius * 5));
					soundManager.explosion.play();
					levelManager.score += 54 * levelManager.scoreMult;
					enemys.erase(itEnemy);
					bullets.erase(itBullet);
					flag = false;
					break;
				}
			}
			if (!flag)
				break;
		}
	}
	/////

	//Enemy vs Explosion
	list<Explosion>* pExplosions = &explosions;
	while (true)
	{
		auto itEnemy = find_if(enemys.begin(), enemys.end(), [pExplosions](Enemy enemy)
			{
				bool flag = false;
				for (Explosion explosion : *pExplosions)
				{
					if (explosion.is_danger()&&enemy.getPosition().y>10.f)
					{
						Vector2f expCenter = explosion.getPosition() + Vector2f(explosion.getRadius(), explosion.getRadius());
						Vector2f enemyCenter = enemy.getPosition() + Vector2f(enemy.getRadius(), enemy.getRadius())-enemy.getVelosity()*0.35f;
						Vector2f refresh = expCenter - enemyCenter;
						float scalarProduct = refresh.x * refresh.x + refresh.y * refresh.y;
						if (scalarProduct*1.2f < (enemy.getRadius() + explosion.getRadius()) * (enemy.getRadius() + explosion.getRadius()))
						{
							flag = true;
							break;
						}
					}
					if (flag)
						break;
				}
				return flag;
			});
		if (itEnemy == enemys.end())
			break;
		explosions.push_back(Explosion((*itEnemy).getPosition() + Vector2f((*itEnemy).getRadius(), (*itEnemy).getRadius()),
			textures.explosion, (*itEnemy).getRadius()*5));
		soundManager.explosion.play();
		levelManager.score += 54 * levelManager.scoreMult;
		enemys.erase(itEnemy);

	}

	//Enemy vs Player
	Player* pplayer = &player;
	while (true)
	{
		auto itEnemy = find_if(enemys.begin(), enemys.end(), [pplayer](Enemy enemy)
			{
				return (*pplayer).getGlobalBounds().intersects(enemy.getGlobalBounds());
			});
		if (itEnemy == enemys.end())
			break;
		explosions.push_back(Explosion((*itEnemy).getPosition() + Vector2f((*itEnemy).getRadius(), (*itEnemy).getRadius()),
			textures.explosion, (*itEnemy).getRadius() * 5));
		levelManager.score += 54 * levelManager.scoreMult;
		enemys.erase(itEnemy);
		soundManager.explosion.play();
		
	}

}
