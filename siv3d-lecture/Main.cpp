# include <Siv3D.hpp> // OpenSiv3D v0.6.3

void Main()
{
	Vec2 player = { 100, 100 };

	Array<Vec2> shots;

	Array<Vec2> enemies;

	Timer enemy_timer;
	enemy_timer.set(1s);
	enemy_timer.start();

	while (System::Update())
	{
		// process
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
			shots.push_back(player);
		}

		// shots process
		for (auto& shot : shots) {
			shot.x += 20;
		}

		shots.remove_if([](auto shot) {
			return shot.x > 800;
		});

		// enemies process
		for (auto& enemy : enemies) {
			enemy.x -= 2;
		}

		if (enemy_timer.reachedZero()) {
			enemies.push_back(Vec2{ 800, Random(0, 600) });

			enemy_timer.restart();
		}

		enemies.remove_if([&shots](auto enemy) {
			for (const auto& shot : shots) {
				if (Circle(Arg::center(shot), 5).intersects(RectF(Arg::center(enemy), Size(60, 60)))) {
					return true;
				}
			}
			return false;
		});

		// draw
		// draw player
		for (const auto& enemy : enemies) {
			RectF(Arg::center(enemy), Size(60, 60)).draw(Palette::Red);
		}

		// draw shots
		for (const auto& shot : shots) {
			Circle(Arg::center(shot), 5).draw(Palette::Cyan);
		}

		// draw enemies
		RectF(Arg::center(player), Size(30, 30)).draw(Palette::Blue);
	}
}
