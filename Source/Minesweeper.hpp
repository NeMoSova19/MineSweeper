#pragma once
#include "Button.hpp"

struct Tile : public Button {
	Tile(Vector2 pos, Vector2 size, size_t i, size_t j);
	
	static void SetGameOver(std::function<void()>f);
	void OnMousePress(SuperMouse::Key key) override;
	static bool isExist(size_t i, size_t j);
	static void clear(int8_t);

	static inline int8_t type{ 1 };
	static inline bool firstStep{ true };
	static inline size_t total_bombs{ 0 };
	static inline size_t total_placed_flags{ 0 };
	static inline size_t total_opened_tiles{ 0 };
	static inline std::vector<std::vector<Tile*>> map{};

	int8_t stat{ 0 };
private:
	size_t _i, _j;
	bool isOpen: 1{ false };
	bool isFlag: 1{ false };
	static inline std::function<void()> FgameOver{ []() {} };

	static void Open(size_t i, size_t j);
	static void OpenZero(size_t i, size_t j);
	static bool isBomb(size_t i, size_t j);
	static bool _isFlag(size_t i, size_t j);
	static void _plus(size_t i, size_t j);
	static bool _isClosed(size_t i, size_t j);
	static void TryOpen(size_t i, size_t j);
	static void TryFlagging(size_t i, size_t j);
	static void TryOpenAround(size_t i, size_t j);
	static void TryFlaggingAround(size_t i, size_t j);
	static void CalculateMap(int type, size_t ii, size_t jj);
};


struct Game {
	static void Start();
	static void Update();
	static void Pause();
	static void UnPause();
	static void Restart();
	static void Close();

	enum Type {
		none,
		x9x9,
		x16x16,
		x30x16
	};
	
	static inline Type type{ none };
	static inline bool isStart{ false };
	static inline bool isPause{ false };

private:
	static inline bool GameLose{ false };
	static inline bool GameWin{ false };
	static inline float m_time{ 0 };
	static inline const int8_t bomb_tile{ -1 };
};