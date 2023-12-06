#include "Minesweeper.hpp"
#include "Settings.hpp"
#include <functional>
#include "Windower.hpp"
#include "Canvas.hpp"

Tile::Tile(Vector2 pos, Vector2 size, size_t i, size_t j)
	:_i(i), _j(j)
{
	SetPosition(pos, Global);
	SetSizeAcrossPos(size);
};

void Tile::SetGameOver(std::function<void()>f) {
	FgameOver = f;
}

void Tile::OnMousePress(SuperMouse::Key key) {
	Button::OnMousePress(key);

	auto f_digging = [&]() {
		if (isFlag) return;

		if (firstStep) {
			CalculateMap(type, _i, _j);
			firstStep = false;
			Game::isPause = false;
		}

		if (stat == -1) { // бомба
			Boom_queue.push({ _i,_j });
			map[_i][_j]->stat = 99;
			FgameOver();
			return;
		}

		if (stat == 0) {
			if (!isOpen) OpenZero(_i, _j);
			return;
		}

		if (isOpen) {
			if (Settings::GetEasyDigging()) TryOpenAround(_i, _j);
			if (Settings::GetEasyFlagging()) TryFlaggingAround(_i, _j);

		}
		else Open(_i, _j);
		};

	auto f_set_flag = [&]() {
		if (isOpen) return;

		if (isFlag) {
			isFlag = false; // флаг убран
			total_placed_flags--;
			SetSpriteNumber(0);
			return;
		}

		if (total_placed_flags < total_bombs) {
			isFlag = true; // флаг поставлен
			total_placed_flags++;
			SetSpriteNumber(1);
			return;
		}

		};

	if (Settings::GetLeftClickFlag()) {
		if (key == SuperMouse::Left) f_set_flag();
		if (key == SuperMouse::Right) f_digging();
		return;
	}
	if (key == SuperMouse::Left) f_digging();
	if (key == SuperMouse::Right) f_set_flag();
}

bool Tile::isExist(size_t i, size_t j) {
	return !(i < 0 || j < 0 || i >= map.size() || j >= map[0].size());
}


void Tile::Open(size_t i, size_t j) { //
	if (map[i][j]->stat == 0) {
		map[i][j]->SetSpriteNumber(10);
	}
	else {
		map[i][j]->SetSpriteNumber(map[i][j]->stat + 1);
	}
	total_opened_tiles++;
	map[i][j]->isOpen = true;
}

void Tile::OpenZero(size_t i, size_t j) { //
	if (isExist(i, j)) {
		if (map[i][j]->isOpen) return;
		if (map[i][j]->stat != -1) {
			if (map[i][j]->isFlag) total_placed_flags--;
			Open(i, j);
			if (map[i][j]->stat == 0) {
				OpenZero(i - 1, j);
				OpenZero(i + 1, j);
				OpenZero(i, j - 1);
				OpenZero(i, j + 1);

				OpenZero(i + 1, j + 1);
				OpenZero(i - 1, j + 1);
				OpenZero(i + 1, j - 1);
				OpenZero(i - 1, j - 1);
			}
		}
	}
}

bool Tile::isBomb(size_t i, size_t j) {
	return isExist(i, j) && (map[i][j]->stat == -1);
}

bool Tile::_isFlag(size_t i, size_t j) { //
	return isExist(i, j) && map[i][j]->isFlag;
}
bool Tile::_isClosed(size_t i, size_t j) { //
	return isExist(i, j) && !map[i][j]->isOpen;
}

void Tile::_plus(size_t i, size_t j) { //
	if (isExist(i, j) && (map[i][j]->stat != -1))
		map[i][j]->stat++;
}

void Tile::TryOpen(size_t i, size_t j) { //
	if (isExist(i, j) && !map[i][j]->isOpen && !map[i][j]->isFlag)
		if (map[i][j]->stat == -1) {
			Boom_queue.push({ i,j });
			FgameOver();
		}
		else OpenZero(i, j);
}
void Tile::TryFlagging(size_t i, size_t j) { //
	if (isExist(i, j) && !map[i][j]->isOpen && !map[i][j]->isFlag)
	{
		map[i][j]->isFlag = true;
		total_placed_flags++;
		map[i][j]->SetSpriteNumber(1);
	}
}


void Tile::TryFlaggingAround(size_t i, size_t j) { //
	size_t cnt{ 0 };
	if (_isClosed(i - 1, j + 1)) cnt++;
	if (_isClosed(i - 1, j)) cnt++;
	if (_isClosed(i - 1, j - 1)) cnt++;
	if (_isClosed(i + 1, j + 1)) cnt++;
	if (_isClosed(i + 1, j)) cnt++;
	if (_isClosed(i + 1, j - 1)) cnt++;
	if (_isClosed(i, j + 1)) cnt++;
	if (_isClosed(i, j - 1)) cnt++;

	if (map[i][j]->stat == cnt) {
		TryFlagging(i - 1, j + 1);
		TryFlagging(i - 1, j);
		TryFlagging(i - 1, j - 1);
		TryFlagging(i + 1, j + 1);
		TryFlagging(i + 1, j);
		TryFlagging(i + 1, j - 1);
		TryFlagging(i, j + 1);
		TryFlagging(i, j - 1);
	}
}

void Tile::TryOpenAround(size_t i, size_t j) { //
	size_t cnt{ 0 };
	if (_isFlag(i - 1, j + 1)) cnt++;
	if (_isFlag(i - 1, j)) cnt++;
	if (_isFlag(i - 1, j - 1)) cnt++;
	if (_isFlag(i + 1, j + 1)) cnt++;
	if (_isFlag(i + 1, j)) cnt++;
	if (_isFlag(i + 1, j - 1)) cnt++;
	if (_isFlag(i, j + 1)) cnt++;
	if (_isFlag(i, j - 1)) cnt++;

	if (map[i][j]->stat == cnt) {
		TryOpen(i - 1, j + 1);
		TryOpen(i - 1, j);
		TryOpen(i - 1, j - 1);
		TryOpen(i + 1, j + 1);
		TryOpen(i + 1, j);
		TryOpen(i + 1, j - 1);
		TryOpen(i, j + 1);
		TryOpen(i, j - 1);
	}
}

void Tile::CalculateMap(int type, size_t ii, size_t jj) {
	Tile::type = type;
	firstStep = true;

	switch (type)
	{
	case 1:
		total_bombs = 10;
		break;
	case 2:
		total_bombs = 40;
		break;
	case 3:
		total_bombs = 99;
		break;
	}
	srand(time(NULL));
	volatile size_t cnt{ total_bombs };

	for (size_t i = 0; i < map.size(); i++)
	{
		for (size_t j = 0; j < map[0].size(); j++)
		{
			map[i][j]->stat = 0;
		}
	}
	while (cnt) {
		size_t i, j;
		i = rand() % map.size();
		j = rand() % map[0].size();
		if (i == ii && j == jj) continue;
		if (map[i][j]->stat != -1) {
			map[i][j]->stat = -1;
			cnt--;
			_plus(i - 1, j - 1);
			_plus(i - 1, j);
			_plus(i - 1, j + 1);
			_plus(i + 1, j - 1);
			_plus(i + 1, j);
			_plus(i + 1, j + 1);
			_plus(i, j - 1);
			_plus(i, j + 1);
		}
	}
}

void Tile::clear(int8_t t)
{
	type = t;
	firstStep = true;
	total_placed_flags = 0;
	total_opened_tiles = 0;
	total_bombs = 0;
	map.clear();
}












void Game::Start() {
	Tile::SetGameOver([]() {
		isPause = true;
		GameLose = true;
		Scene::CanvasSettings("Game", true, false);
		Scene::CanvasSettings("LoseGame", true, true);
		Settings::Where = WHERE::LoseGame;

		for (auto& line : Tile::map) {
			for (auto& u : line) {
				if (u->stat == -1)
					u->SetSpriteNumber(11);
				if (u->stat == 99)
					u->SetSpriteNumber(12);
			}
		}

		Settings::SetStat({0, 1, (size_t)m_time}, type);
		});

	auto& m_bg = Scene::AddOnCanvas("Game", new UIregion);
	auto& cnt_flag1 = Scene::AddOnCanvas("Game", new UIregion);
	auto& cnt_flag2 = Scene::AddOnCanvas("Game", new UIregion);
	auto& cnt_flag3 = Scene::AddOnCanvas("Game", new UIregion);
	auto& time_1 = Scene::AddOnCanvas("Game", new UIregion);
	auto& time_2 = Scene::AddOnCanvas("Game", new UIregion);
	auto& time_3 = Scene::AddOnCanvas("Game", new UIregion);
	cnt_flag2.SetParent(&cnt_flag1);
	cnt_flag3.SetParent(&cnt_flag2);
	time_2.SetParent(&time_1);
	time_3.SetParent(&time_2);

	m_bg
		// UIregion
		.SetName("Game_bg9x9")
		.SetTexture("BG9x9")
		.SetTextureRect({ 0,0,0,0 })
		.SetSpriteDrawType(SpriteDrawType::TextureRect)
		.SetBGColor(Color(255, 255, 255, 255))
		// Rect
		.SetSizeAcrossPos({ 660,840 })
		.SetGlobalPosition({ 0,0 });

	cnt_flag1
		// UIregion
		.SetName("Game_cnt_flag1")
		.SetTexture("Numbers")
		.SetSpriteDrawType(SpriteDrawType::SpriteAnim)
		.SetSpriteSize({ 34,58 })
		.SetBGColor(Color::White)
		.SetSpriteNumber(0)
		// Rect
		.SetSizeAcrossPos({ 66,116 })
		.SetGlobalPosition({ 60,60 });
	cnt_flag2
		// UIregion
		.SetName("Game_cnt_flag2")
		.SetTexture("Numbers")
		.SetSpriteDrawType(SpriteDrawType::SpriteAnim)
		.SetSpriteSize({ 34,58 })
		.SetBGColor(Color::White)
		.SetSpriteNumber(0)
		// Rect
		.SetSizeAcrossPos({ 66,116 })
		.SetLocalPosition({ 66,0 });
	cnt_flag3
		// UIregion
		.SetName("Game_cnt_flag3")
		.SetTexture("Numbers")
		.SetSpriteDrawType(SpriteDrawType::SpriteAnim)
		.SetSpriteSize({ 34,58 })
		.SetBGColor(Color::White)
		.SetSpriteNumber(0)
		// Rect
		.SetSizeAcrossPos({ 66,116 })
		.SetLocalPosition({ 66,0 });
	time_1
		// UIregion
		.SetName("Game_time_1")
		.SetTexture("Numbers")
		.SetSpriteDrawType(SpriteDrawType::SpriteAnim)
		.SetSpriteSize({ 34,58 })
		.SetBGColor(Color::White)
		.SetSpriteNumber(0)
		// Rect
		.SetSizeAcrossPos({ 66,116 })
		.SetGlobalPosition({ 660-60-66*3,60 });
	time_2
		// UIregion
		.SetName("Game_time_2")
		.SetTexture("Numbers")
		.SetSpriteDrawType(SpriteDrawType::SpriteAnim)
		.SetSpriteSize({ 34,58 })
		.SetBGColor(Color::White)
		.SetSpriteNumber(0)
		// Rect
		.SetSizeAcrossPos({ 66,116 })
		.SetLocalPosition({ 66,0 });
	time_3
		// UIregion
		.SetName("Game_time_3")
		.SetTexture("Numbers")
		.SetSpriteDrawType(SpriteDrawType::SpriteAnim)
		.SetSpriteSize({ 34,58 })
		.SetBGColor(Color::White)
		.SetSpriteNumber(0)
		// Rect
		.SetSizeAcrossPos({ 66,116 })
		.SetLocalPosition({ 66,0 });

	// Reset Game vars
	GameLose = false;
	isStart = true;
	isPause = true;
	GameWin = false;
	m_time = 0;

	// Reset Tile vars
	Tile::clear(type);


	Vector2 p{60,60*4};
	float tile_size{ 1 };
	switch (type)
	{
	case Game::x9x9:
		Tile::map.resize(9, std::vector<Tile*>(9));
		tile_size = 60.f;
		break;
	case Game::x16x16:
		Tile::map.resize(16, std::vector<Tile*>(16));
		tile_size = 33.74999999f;
		break;
	case Game::x30x16:
		Tile::map.resize(30, std::vector<Tile*>(16));
		tile_size = 33.74999999f;
		m_bg
			.SetTexture("BG30x16")
			.SetTextureRect({ 0,0,0,0 })
			.SetSizeAcrossPos({ 1140,840 });
		p.x = 64;
		cnt_flag1.SetGlobalX(64);
		time_1.SetGlobalX(1140-64-66*3);
		break;
	}
	float s_x{ Tile::map.size() * tile_size / 2.f };
	float s_y{ Tile::map[0].size() * tile_size / 2.f };
	for (float i = 0; i < Tile::map.size(); i++)

	{
		for (float j = 0; j < Tile::map[0].size(); j++)
		{
			Tile::map[i][j] = new Tile({ p.x + i * tile_size,  p.y + j * tile_size }, { tile_size,tile_size }, i, j); 
			Tile::map[i][j]->SetBGColor(Color::White);
			Tile::map[i][j]->SetTexture("Tiles");
			Tile::map[i][j]->SetSpriteSize({ 64,64 });
			Tile::map[i][j]->SetSpriteNumber(0);
			Tile::map[i][j]->SetSpriteDrawType(SpriteDrawType::SpriteAnim);
			Tile::map[i][j]->text->SetCharacterSize(tile_size);
			Tile::map[i][j]->text->SetSizeAcrossPos({ tile_size, tile_size });
			Scene::AddOnCanvas("Game", Tile::map[i][j]);
		}
	}
	while (!Tile::Boom_queue.empty()) {
		Tile::Boom_queue.pop();
	}
}

void Game::Update(float deltaTime) {
	if (isStart) {
		if (!isPause) {
			if (Tile::total_opened_tiles + Tile::total_placed_flags == Tile::map.size() * Tile::map[0].size()) {
				isPause = true;
				Scene::CanvasSettings("Game", true, false);
				Scene::CanvasSettings("WinGame", true, true);
				Settings::Where = WHERE::WinGame;
				
				Settings::SetStat({ 1, 0, (size_t)m_time }, type);
				
				return;
			}
			m_time += deltaTime;
		}

		size_t tt = Tile::total_bombs - Tile::total_placed_flags;
		UIregion::FindByName("Game_cnt_flag1")->SetSpriteNumber(tt / 100 % 10);
		UIregion::FindByName("Game_cnt_flag2")->SetSpriteNumber(tt / 10 % 10);
		UIregion::FindByName("Game_cnt_flag3")->SetSpriteNumber(tt % 10);

		UIregion::FindByName("Game_time_1")->SetSpriteNumber((int)m_time / 100 % 10);
		UIregion::FindByName("Game_time_2")->SetSpriteNumber((int)m_time / 10 % 10);
		UIregion::FindByName("Game_time_3")->SetSpriteNumber((int)m_time % 10);
	}
}

void Game::Pause() {
	isPause = true;
}

void Game::UnPause() {
	isPause = false;
}

void Game::Restart() {
	isStart = true;
	isPause = false;
	m_time = 0;
	Scene::Clear("Game");
	Start();
}

void Game::Close() {
	isStart = false;
	isPause = false;
	m_time = 0;
	Scene::Clear("Game");
}