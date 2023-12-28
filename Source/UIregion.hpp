#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <map>
#include "SuperMouse.hpp"
#include "Vector2.hpp"
#include "Color.hpp"

class Point {
public:
	enum Type : uint8_t{ Local, Global };

	Point(Point&&) = delete;
	Point() = default;
	Point(float x, float y);
	virtual ~Point();
	
	// Set
	Point& SetPosition(Vector2 const& p, Type t);
	Point& SetGlobalPosition(Vector2 const& p);
	Point& SetLocalPosition(Vector2 const& p);
	Point& SetGlobalX(float x);
	Point& SetGlobalY(float y);
	Point& SetLocalX(float x);
	Point& SetLocalY(float y);
	Point& SetParent(Point* ptr);

	// Get
	Vector2				 GetPosition(Type t) const;
	Vector2				 GetGlobalPosition() const;
	Vector2				 GetLocalPosition() const;
	std::vector<Point*>& GetChildrens();
	Point*				 GetParent();
	
	// Other
	void UnParent();
	void Move(Vector2 const& d);
	void MoveX(float x);
	void MoveY(float y);

private:
	Vector2 Point_Global_position;
	Vector2 Point_Local_position;

	std::vector<Point*> Point_childrens{};
	Point* Point_parent{ nullptr };

	void UpdatePositionForChildrens();
	void RecursiveUpdatePositionForChildrens();
};


struct Rect : public Point{
	Rect() = default;
	Rect(float x, float y, float w, float h);
	virtual ~Rect() = default;

	Rect& SetCenter(Vector2 const& center);
	Rect& SetSizeAcrossPos(Vector2 const& size);
	Rect& SetSizeAcrossCenter(Vector2 const& size);
	
	Rect& SetWidth(float width);
	Rect& SetHeight(float height);

	float		  GetUp()     const;
	Vector2		  GetSize()   const;
	float		  GetLeft()   const;
	float		  GetDown()   const;
	float		  GetRight()  const;
	float		  GetWidth()  const;
	Vector2		  GetCenter() const;
	float		  GetHeight() const;

	bool  Contains(Vector2 const& p);

	enum class EditState :uint8_t
	{
		Null = 0b0,
		Resize = 0b1,
		Move = 0b10,
		Edit = Resize | Move,
	};
	virtual void OnEditable() { }

protected:
	EditState m_editState{ EditState::Null };
private:
	Vector2 Rect_size;
};

enum class SpriteDrawType {
	TextureRect,
	SpriteAnim
};

class Drawable : public Rect {
public:
	// Set
	Drawable& SetTexture(std::string const& texture_path);
	Drawable& SetBGColor(Color const& col);
	Drawable& SetTextureRect(Rect const& r);
	Drawable& SetSpriteSize(Vector2 const& size);
	Drawable& SetSpriteNumber(size_t n);
	Drawable& SetSpriteNext();
	Drawable& SetSpriteDrawType(SpriteDrawType sdt);

	// Get
	Color GetBGColor() const;
	std::string GetBGTexturePath() const;
	sf::Texture& GetBGTexture() const;

	virtual void Draw();
	void OnEditable() override { DrawUpdate(); }
	void DrawUpdate();
	
private:
	Color m_BGcolor{255,255,255};
	std::string m_BGtexturePath;

	Rect m_TextureRect;
	Vector2 m_SpriteSize;
	size_t m_SpriteNum{ 0 };
	SpriteDrawType m_SpriteDrawType{ SpriteDrawType::TextureRect };

	sf::VertexArray var{ sf::PrimitiveType::TrianglesFan, 4 };
	sf::RenderStates rs;
};

struct UIregion : public Drawable {
	UIregion(UIregion&&) = delete;
	UIregion();
	virtual ~UIregion();

	UIregion&		SetName(std::string name);
	std::string		GetName() const;
	UIregion&		Clicable(bool b);

	UIregion& SetCallbackOnMouseGrab(std::function<void(SuperMouse::Key, UIregion*)> f);
	UIregion& SetCallbackOnMousePress(std::function<void(SuperMouse::Key, UIregion*)> f);
	UIregion& SetCallbackOnMouseRelease(std::function<void(SuperMouse::Key, UIregion*)> f);
	UIregion& SetCallbackOnMouseHold(std::function<void(SuperMouse::Key, UIregion*)> f);
	UIregion& SetCallbackOnMouseEnter(std::function<void(UIregion*)> f);
	UIregion& SetCallbackOnMouseExit(std::function<void(UIregion*)> f);

	UIregion& SetCallbackOnEditable(std::function<void()> f);
	void RecursiveOnEditable(UIregion* reg);

	// Virtual
	virtual void	Update();
	bool			ClickUpdate(bool dont_handle_clicks = false);

	// Static
	template<class T = UIregion> 
	static T*	FindByName(std::string name)
	{
		if (!m_UIregions.contains(name)) return nullptr;
		return dynamic_cast<T*>(m_UIregions[name]);
	}

private:
	std::string Name;
	Vector2 M_position, M_size; // сохраненные предыдущие позиция и размер
	
	// Static
	static inline size_t m_lastNameNumber{ 0 };
	static inline std::map<std::string, UIregion*> m_UIregions{};
	
	
protected:
	// Click
	bool m_isClicable{ false };
	bool isGrab[SuperMouse::Key::Count], isAvailable{ false }, inRectNow{ false }, inRectPrev{ false };

	// Mouse keys
	std::vector<std::function<void(SuperMouse::Key, UIregion*)>> FOnMouseGrab;
	std::vector<std::function<void(SuperMouse::Key, UIregion*)>> FOnMousePress;
	std::vector<std::function<void(SuperMouse::Key, UIregion*)>> FOnMouseRelease;
	std::vector<std::function<void(SuperMouse::Key, UIregion*)>> FOnMouseHold;

	// Mouse in/out rect
	std::vector<std::function<void(UIregion*)>> FOnMouseEnter;
	std::vector<std::function<void(UIregion*)>> FOnMouseExit;

	// Edit event
	std::vector<std::function<void()>> FOnEditable;

	// Virtual events 
	virtual void OnMousePress(SuperMouse::Key) { }		  // 
	virtual void OnMouseRelease(SuperMouse::Key) { }	  // 
	virtual void OnMouseHold(SuperMouse::Key) { }		  // сделать таймер в SuperMouse  // или пока не делать)
	virtual void OnMouseGrab(SuperMouse::Key) { }		  // когда hold без таймера		  // 
	virtual void OnMousePressOut(SuperMouse::Key) {}
	virtual void OnMouseEnter() { }		  
	virtual void OnMouseExit() { }		  
};