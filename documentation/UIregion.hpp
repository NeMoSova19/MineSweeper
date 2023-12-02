 #pragma once
#include <SFML/Graphics/Texture.hpp>
#include "../StandartTypes.hpp"
#include <functional>
#include <map>
#include "../SuperMouse.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct BindPoint {
	enum BindType :uint8_t { SpringSide, MoveSide }; // пружина (весь прямоугольник) / только грань

	BindPoint& Pos(const Vector2* p) {
		pos = p;
		return *this;
	}
	BindPoint& Delta(const Vector2* d) {
		size = d;
		return *this;
	}
	BindPoint& Type(BindType t) {
		bindType = t;
		return *this;
	}
	BindPoint& Rigidity(uint32_t r) {
		springRigid = r;
		return *this;
	}

	void operator = (BindPoint& bp) {
		pos = bp.pos;
		size = bp.size;
		bindType = bp.bindType;
		springRigid = bp.springRigid;
	}

	bool IsExist() {
		return !!pos;
	}

	Vector2 GetPoint() {
		if (!pos) return Vector2();
		Vector2 p = *pos;
		if (size) p += *size;
		return p;
	}
	BindType GetType() const {
		return bindType;
	}
	uint32_t GetSpringRigid() const {
		return springRigid;
	}
	void Reset() {
		pos = nullptr;
		size = nullptr;
		springRigid = 0;
	}

private:
	const Vector2* pos{ nullptr };
	const Vector2* size{ nullptr };
	BindType bindType{ MoveSide };
	uint32_t springRigid{ 0 };
};

struct UIregion;

class Point {
public:
	enum Type : uint8_t{ Local, Global };

	Point(Point&&) = delete;
	Point() = default;
	Point(float x, float y);
	virtual ~Point();
	
	// Set
	Point& SetParent(Point* ptr);
	Point& SetLocalPosition(Vector2 const& p);
	Point& SetGlobalPosition(Vector2 const& p);
	Point& SetPosition(Vector2 const& p, Type t);
	Point& SetLocalX(float x);
	Point& SetLocalY(float y);
	Point& SetGlobalX(float x);
	Point& SetGlobalY(float y);

	// Get
	Point*				GetParent();
	std::vector<Point*>&GetChildrens();
	Vector2				GetLocalPosition() const;
	Vector2				GetGlobalPosition() const;
	Vector2				GetPosition(Type t) const;
	
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

enum class RectType {
	Rect,
	Circle
};

struct Rect : public Point{
	Rect() = default;
	Rect(float x, float y, float w, float h);
	virtual ~Rect() = default;

	Rect& SetRectType(RectType rt);
	Rect& SetCenter(Vector2 const& center);
	Rect& SetSizeAcrossPos(Vector2 const& size);
	Rect& SetSizeAcrossCenter(Vector2 const& size);
	
	Rect& SetRadius(float r);
	Rect& SetWidth(float width);
	Rect& SetHeight(float height);
	
	Rect& SetLeftUp(Vector2 const& pos);
	Rect& SetRightUp(Vector2 const& pos);
	Rect& SetRightDown(Vector2 const& pos);
	Rect& SetLeftDown(Vector2 const& pos);
	
	Rect& SetLeftBorder(float delta);
	Rect& SetRightBorder(float delta);
	Rect& SetUpBorder(float delta);
	Rect& SetDownBorder(float delta);

	//void MoveLeftBorder(float delta);
	//void MoveRightBorder(float delta);
	//void MoveUpBorder(float delta);
	//void MoveDownBorder(float delta);

	//const Vector2*	GetSizePtr() const;
	float		  GetUp()     const;
	Vector2		  GetSize()   const;
	float		  GetLeft()   const;
	float		  GetDown()   const;
	float		  GetRight()  const;
	float		  GetWidth()  const;
	Vector2		  GetCenter() const;
	float         GetRadius() const;
	float		  GetHeigth() const;

	virtual bool  Contains(Vector2 const& p);
	static bool   AABBContains(Vector2 const& lu, Vector2 const& size, Vector2 const& p);
	bool		  AABBContains(Vector2 const& p);
	bool		  AABBIntersect(UIregion const& aabb);
	Vector2		  AABBrelativelyLine(Vector2 const& start, Vector2 const& dir);

	enum class EditState :uint8_t
	{
		Null = 0b0,
		Resize = 0b1,
		Move = 0b10,
		Edit = Resize | Move,
	};
	virtual void OnEditable() { std::cout << "UIregion Update\n"; }

protected:
	RectType m_RectType{ RectType::Rect };
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

	virtual void Draw(sf::RenderWindow& rw);
	void OnEditable() override { DrawUpdate(); }
	void DrawUpdate();
	
	Color m_BGcolor{255,255,255};
	std::string m_BGtexturePath;

	Rect m_TextureRect;
	Vector2 m_SpriteSize;
	size_t m_SpriteNum{ 0 };
	SpriteDrawType m_SpriteDrawType{ SpriteDrawType::TextureRect };

private:
	sf::VertexArray vac{ sf::PrimitiveType::TrianglesFan, 32 };
	sf::VertexArray var{ sf::PrimitiveType::TrianglesFan, 4 };
	sf::RenderStates rs;
};

struct UIregion : public Drawable {
	UIregion(UIregion&&) = delete;
	UIregion();
	virtual ~UIregion();

	friend void RecursiveOnEditable(UIregion* reg);

	bool			GetActive() const;
	std::string		GetName() const;
	UIregion&		Clicable(bool b);
	UIregion&		SetName(std::string name);
	UIregion&		SetActive(bool active);

	UIregion& SetBindLeftBorder(BindPoint bp);
	UIregion& SetBindRightBorder(BindPoint bp);
	UIregion& SetBindUpBorder(BindPoint bp);
	UIregion& SetBindDownBorder(BindPoint bp);
	UIregion& ResetBind(uint8_t p);

	UIregion& SetCallbackOnMouseGrab(std::function<void(SuperMouse::Key, UIregion*)> f);
	UIregion& SetCallbackOnMousePress(std::function<void(SuperMouse::Key, UIregion*)> f);
	UIregion& SetCallbackOnMouseRelease(std::function<void(SuperMouse::Key, UIregion*)> f);
	UIregion& SetCallbackOnMouseHold(std::function<void(SuperMouse::Key, UIregion*)> f);
	UIregion& SetCallbackOnMouseEnter(std::function<void(UIregion*)> f);
	UIregion& SetCallbackOnMouseExit(std::function<void(UIregion*)> f);

	UIregion& SetCallbackOnEditable(std::function<void()> f);

	// Virtual
	virtual void	Update();
	virtual std::string GetType() { return "UIregion"; };
	bool			ClickUpdate(bool dont_handle_clicks = false);
	
	// Json
	virtual json GetJson();
	virtual void SetJson(json);
	virtual void PostSetJson(json);

	// Static
	template<class T = UIregion> 
	static T*	FindByName(std::string name)
	{
		if (!m_UIregions.contains(name)) return nullptr;
		return dynamic_cast<T*>(m_UIregions[name]);
	}

	// Enums
	

private:
	std::string Name;
	bool m_isActive{ true };
	BindPoint m_bindPoint[4]; // L U R D
	Vector2 M_position, M_size; // сохраненные предыдущие позиция и размер
	
	// Static
	static inline size_t m_lastNameNumber{ 0 };
	static inline std::map<std::string, UIregion*> m_UIregions{};
	
	
protected:
	// Click
	bool m_isClicable{ false };
	bool isGrab[SuperMouse::NumKeys], isAvailable{ false }, inRectNow{ false }, inRectPrev{ false };

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
	virtual void OnMouseEnter() { }		  
	virtual void OnMouseExit() { }		  
	virtual void OnMousePressOut() {}
};