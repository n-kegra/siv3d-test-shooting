# include <Siv3D.hpp> // OpenSiv3D v0.6.3

struct Shot {
	Vec2 pos;
	Vec2 vel;
	bool alive;
};

struct Enemy {
	Vec2 pos;
	int size;
	bool alive;
};

void Main()
{
	Vec2 player = { 100, 100 };

	Array<Shot> shots;

	Array<Enemy> enemies;

	Timer enemy_timer;
	enemy_timer.set(1s);
	enemy_timer.start();

	const Font font{ 32 };
	int score = 0;

	const Texture player_image(U"player.png");
	const Texture player_shot_image(U"player_shot.png");
	const Texture enemy_image(U"enemy.png");

	const Audio player_shot_se(U"player_shot_se.wav");
	const Audio boom_se(U"boom.wav");

	while (System::Update())
	{
		// process
		// shot vs enemy
		for (auto& shot : shots) {
			for (auto& enemy : enemies) {
				if (!shot.alive || !enemy.alive)
					continue;

				if (Circle(Arg::center(shot.pos), 5).intersects(RectF(Arg::center(enemy.pos), Size(enemy.size, enemy.size)))) {
					shot.alive = false;
					enemy.alive = false;
					score += 1;
					boom_se.playOneShot();
				}
			}
		}

		// player process
		if (KeyUp.pressed()) {
			player.y -= 10;
		}
		if (KeyDown.pressed()) {
			player.y += 10;
		}
		if (KeyLeft.pressed()) {
			player.x -= 10;
		}
		if (KeyRight.pressed()) {
			player.x += 10;
		}

		if (KeySpace.down()) {
			shots.push_back(Shot{ player, Vec2{20, -2}, true });
			shots.push_back(Shot{ player, Vec2{20,  0}, true });
			shots.push_back(Shot{ player, Vec2{20, +2}, true });
			player_shot_se.playOneShot();
		}

		// shots process
		for (auto& shot : shots) {
			shot.pos += shot.vel;
		}

		shots.remove_if([](auto shot) {
			return shot.pos.x > 800 || !shot.alive;
		});

		// enemies process
		for (auto& enemy : enemies) {
			enemy.pos.x -= 2;
		}

		if (enemy_timer.reachedZero()) {
			enemies.push_back(Enemy{ Vec2{ 800, Random(0, 600) }, Random(30, 90), true });

			enemy_timer.restart();
		}

		enemies.remove_if([&shots](auto enemy) {
			return !enemy.alive;
		});

		// draw
		// draw player
		for (const auto& enemy : enemies) {
			enemy_image.resized(enemy.size, enemy.size).drawAt(enemy.pos);
		}

		// draw shots
		for (const auto& shot : shots) {
			player_shot_image.drawAt(shot.pos);
		}

		// draw enemies
		player_image.drawAt(player);

		// draw score
		font(U"Score: "+ Format(score)).draw(0, 0, Palette::White);
	}
}
