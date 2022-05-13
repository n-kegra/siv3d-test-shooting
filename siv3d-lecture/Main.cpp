# include <Siv3D.hpp> // OpenSiv3D v0.6.3

void Main()
{
	Vec2 p = { 100, 100 };

	while (System::Update())
	{
		RectF(p, Size(30, 30)).draw(Palette::Blue);
	}
}
