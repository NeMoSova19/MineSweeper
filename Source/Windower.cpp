#include "Windower.hpp"
#include <dwmapi.h>

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

void Windower::Create(Vector2 size, std::string _name, uint8_t _style, sf::ContextSettings _settings) {
	rw.create(sf::VideoMode((size_t)size.x, (size_t)size.y), _name, _style, _settings);
	view = rw.getDefaultView();
	UIregion::SetSizeAcrossPos(size);
}
void Windower::SetTitlebarColor(Color c)
{
	COLORREF COLOR = size_t(c.b)<<16 | size_t(c.g) << 8 | size_t(c.r);// 0x00867059;
	BOOL SET_CAPTION_COLOR = SUCCEEDED(DwmSetWindowAttribute(
		Windower::Win.rw.getSystemHandle(), DWMWINDOWATTRIBUTE::DWMWA_CAPTION_COLOR,
		&COLOR, sizeof(COLOR)));
}

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