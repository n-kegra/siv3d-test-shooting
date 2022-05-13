﻿# include <Siv3D.hpp> // OpenSiv3D v0.6.3

void Main()
{
	Vec2 p = { 100, 100 };

	Array<Vec2> shots;

	Array<Vec2> enemies;

	Timer enemy_timer;
	enemy_timer.set(1s);
	enemy_timer.start();

	while (System::Update())
	{
		// process
		if (KeyUp.pressed()) {
			p.y -= 10;
		}
		if (KeyDown.pressed()) {
			p.y += 10;
		}
		if (KeyLeft.pressed()) {
			p.x -= 10;
		}
		if (KeyRight.pressed()) {
			p.x += 10;
		}

		if (KeySpace.down()) {
			shots.push_back(p);
		}

		for (auto& shot : shots) {
			shot.x += 20;
		}

		shots.remove_if([](auto shot) {
			return shot.x > 800;
		});

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
		for (const auto& enemy : enemies) {
			RectF(Arg::center(enemy), Size(60, 60)).draw(Palette::Red);
		}

		for (const auto& shot : shots) {
			Circle(Arg::center(shot), 5).draw(Palette::Cyan);
		}

		RectF(Arg::center(p), Size(30, 30)).draw(Palette::Blue);
	}
}
