# include <Siv3D.hpp> // OpenSiv3D v0.6.3

void Main()
{
	Vec2 p = { 100, 100 };

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

		RectF(p, Size(30, 30)).draw(Palette::Blue);
	}
}
