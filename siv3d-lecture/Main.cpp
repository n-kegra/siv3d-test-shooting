# include <Siv3D.hpp> // OpenSiv3D v0.6.3

void Main()
{
	while (System::Update())
	{
		if (KeySpace.pressed()) {
			RectF(Vec2(100, 100), Size(30, 30)).draw(Palette::Blue);
		}
	}
}
