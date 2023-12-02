#include "Windower.hpp"
//#include <Windows.h>

void Windower::SetSize(Vector2 s) {
	rw.setSize(sf::Vector2u(s.x, s.y));
	UIregion::SetSizeAcrossPos(s);
}
void Windower::SetPosition(Vector2 p) {
	rw.setPosition(sf::Vector2i(p.x, p.y));
}
void Windower::SetCenter(Vector2 c) {
	SetPosition(c - GetSize() / 2);
}

void Windower::Centering()
{
	auto mode = sf::VideoMode::getFullscreenModes()[0];
	SetCenter({ mode.width/2.f, mode.height/2.f });
}

Vector2 Windower::GetSize() {
	auto s = rw.getSize();
	return Vector2(s.x, s.y);
}
Vector2 Windower::GetPosition() {
	auto p = rw.getPosition();
	return Vector2(p.x, p.y);
}
Vector2 Windower::GetCenter() {
	return GetSize() / 2;
}	

void Windower::Create(Vector2 size, std::string _name, uint8_t _style = sf::Style::Default, sf::ContextSettings _settings = sf::ContextSettings()) {
	rw.create(sf::VideoMode((size_t)size.x, (size_t)size.y), _name, _style, _settings);
	view = rw.getDefaultView();
	UIregion::SetSizeAcrossPos(size);
}
#include <dwmapi.h>
void Windower::SetTitlebarColor(Color c)
{
	COLORREF COLOR = size_t(c.b)<<16 | size_t(c.g) << 8 | size_t(c.r);// 0x00867059;
	BOOL SET_CAPTION_COLOR = SUCCEEDED(DwmSetWindowAttribute(
		Windower::Win.rw.getSystemHandle(), DWMWINDOWATTRIBUTE::DWMWA_CAPTION_COLOR,
		&COLOR, sizeof(COLOR)));
}
//WINDOWPLACEMENT wpc{ 0 };

void Windower::CheckEvents() {
	sf::Event event;
	while (rw.pollEvent(event))
	{
		if (event.type == sf::Event::EventType::Resized) {
			view.setSize({
					static_cast<float>(event.size.width),
					static_cast<float>(event.size.height)
				});
			view.setCenter(event.size.width / 2, event.size.height / 2);
			rw.setView(view);
			UIregion::SetSizeAcrossPos({ (float)event.size.width, (float)event.size.height });
		}
		//if (event.type == sf::Event::EventType::KeyPressed) {
		//	if (event.key.code == sf::Keyboard::Key::F11) {
		//		HWND hWnd = rw.getSystemHandle();
		//		if (!isFullscreen) {
		//			GetWindowPlacement(hWnd, &wpc);//Сохраняем параметры оконного режима
		//			SetWindowLong(hWnd, GWL_STYLE, WS_POPUP);//Устанавливаем новые стили
		//			SetWindowLong(hWnd, GWL_EXSTYLE, WS_EX_TOPMOST);
		//			ShowWindow(hWnd, SW_SHOWMAXIMIZED);//Окно во весь экран
		//			isFullscreen = true;
		//		}
		//		else {
		//			SetWindowLong(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);//Устанавливаем стили окнного режима
		//			SetWindowLong(hWnd, GWL_EXSTYLE, 0L);
		//			ShowWindow(hWnd, SW_SHOWDEFAULT);//Показываем обычное окно
		//			SetWindowPlacement(hWnd, &wpc);//Загружаем парметры предыдущего оконного режима
		//			isFullscreen = false;
		//		}
		//	}
		//}

		for (auto& u : EventBinds[event.type]) {
			u(event);
		}
	}
}


void Windower::AddEventCallback(sf::Event::EventType type, std::function<void(sf::Event)> function)
{
	EventBinds[type].push_back(function);
}

Windower Windower::Win;