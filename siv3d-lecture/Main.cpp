# include <Siv3D.hpp> // OpenSiv3D v0.6.3

void Main()
{
	Vec2 p = { 100, 100 };

	Array<Vec2> shots;

	while (System::Update())
	{
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

		for (const auto& shot : shots) {
			Circle(shot, 5).draw(Palette::Green);
		}

		RectF(Arg::center(p), Size(30, 30)).draw(Palette::Blue);
	}
}
