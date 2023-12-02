#include "UIregion.hpp"
#include "../SuperMouse.hpp"
#include "../ResourceManager.hpp"

// class Point ///////////////////////////////////////////////
Point::Point(float x, float y)
{
	SetGlobalPosition({ x, y });
}
Point::~Point()
{
	UnParent();
	for (auto u : Point_childrens) {
		u->Point_parent = nullptr;
		u->Point_Local_position = u->Point_Global_position;
	}
	Point_childrens.clear();
}
Point& Point::SetParent(Point* ptr)
{
	UnParent();

	Point_parent = ptr;
	Point_parent->Point_childrens.push_back(this);

	Point_Local_position = Point_Global_position - ptr->Point_Global_position;
	UpdatePositionForChildrens();
	return *this;
}
void Point::UnParent()
{
	if (Point_parent)
		for (size_t i = 0; i < Point_parent->Point_childrens.size(); i++) {
			if (Point_parent->Point_childrens[i] == this) {
				Point_parent->Point_childrens.erase(Point_parent->Point_childrens.begin() + i);
				break;
			}
		}
	Point_parent = nullptr;
	Point_Local_position = Point_Global_position;
}
Point* Point::GetParent()
{
	return Point_parent;
}
std::vector<Point*>& Point::GetChildrens()
{
	return Point_childrens;
}

Point& Point::SetLocalPosition(Vector2 const& position)
{
	if (position.x == Point_Local_position.x && position.y == Point_Local_position.y) return *this;;
	Point_Global_position += position - Point_Local_position;
	Point_Local_position = position;
	UpdatePositionForChildrens();
	return *this;
}
Point& Point::SetGlobalPosition(Vector2 const& position) {
	if (position.x == Point_Global_position.x && position.y == Point_Global_position.y) return *this;;
	Point_Local_position += position - Point_Global_position;
	Point_Global_position = position;
	UpdatePositionForChildrens();
	return *this;
}

Point& Point::SetPosition(Vector2 const& p, Type t)
{
	if (t == Local) {
		SetLocalPosition(p);
		return *this;;
	}
	SetGlobalPosition(p);
	return *this;
}

Point& Point::SetLocalX(float x)
{
	SetLocalPosition({ x, Point_Local_position.y });
	return *this;
}
Point& Point::SetLocalY(float y)
{
	SetLocalPosition({ Point_Local_position.x, y });
	return *this;
}

Point& Point::SetGlobalX(float x)
{
	SetGlobalPosition({ x, Point_Global_position.y });
	return *this;
}
Point& Point::SetGlobalY(float y)
{
	SetGlobalPosition({ Point_Global_position.x, y });
	return *this;
}

Vector2 Point::GetLocalPosition() const
{
	return Point_Local_position;
}
Vector2 Point::GetGlobalPosition() const {
	return Point_Global_position;
}

Vector2 Point::GetPosition(Type t) const
{
	if (t == Local) {
		return GetLocalPosition();
	}
	return GetGlobalPosition();
}

void Point::Move(Vector2 const& delta) {
	if (delta.is_zero()) return;
	Point_Local_position += delta;
	Point_Global_position += delta;
	UpdatePositionForChildrens();
}

void Point::MoveX(float x)
{
	Move({ x, 0 });
}
void Point::MoveY(float y)
{
	Move({ 0, y });
}

//const Vector2* Point::GetPositionPtr() const {
//	return &Point_Global_position;
//}

void Point::UpdatePositionForChildrens()
{
	for (auto u : Point_childrens) {
		u->RecursiveUpdatePositionForChildrens();
	}
}

void Point::RecursiveUpdatePositionForChildrens()
{
	Point_Global_position = Point_parent->Point_Global_position + Point_Local_position;
	UpdatePositionForChildrens();
}
// Point /////////////////////////////////////////////////////












// class Rect
Rect::Rect(float x, float y, float w, float h)
	: Point(x, y)
{
	Rect_size.x = w;
	Rect_size.y = h;
}
Rect& Rect::SetRectType(RectType rt)
{
	m_RectType = rt;
	return *this;
}
Rect& Rect::SetCenter(Vector2 const& center) {
	SetGlobalPosition(center - Rect_size / 2);
	return *this;
}
Rect& Rect::SetSizeAcrossPos(Vector2 const& size) {
	Rect_size = size;
	return *this;
}
Rect& Rect::SetSizeAcrossCenter(Vector2 const& size) {
	Move(-size / 2);
	Rect_size = size;
	return *this;
}
Rect& Rect::SetRadius(float r)
{
	SetSizeAcrossCenter({ r*2,r*2 });
	return *this;
}
Rect& Rect::SetWidth(float width)
{
	Rect_size.x = width;
	return *this;
}
Rect& Rect::SetHeight(float height)
{
	Rect_size.y = height;
	return *this;
}
Rect& Rect::SetLeftUp(Vector2 const& pos) {
	Rect_size = GetGlobalPosition() + Rect_size - pos;
	SetGlobalPosition(pos);
	return *this;
}
Rect& Rect::SetRightUp(Vector2 const& pos)
{
	Rect_size.y += GetGlobalPosition().y - pos.y;
	SetGlobalY(pos.y);
	Rect_size.x = pos.x - GetGlobalPosition().x;
	return *this;
}
Rect& Rect::SetRightDown(Vector2 const& pos) {
	Rect_size = pos - GetGlobalPosition();
	return *this;
}
Rect& Rect::SetLeftDown(Vector2 const& pos)
{
	Rect_size.x += GetGlobalPosition().x - pos.x;
	SetGlobalX(pos.x);
	Rect_size.y = pos.y - GetGlobalPosition().y;
	return *this;
}
Rect& Rect::SetLeftBorder(float pos) {
	SetGlobalX(pos);
	return *this;
}
Rect& Rect::SetRightBorder(float pos) {
	SetGlobalX(pos - GetWidth());
	return *this;
}
Rect& Rect::SetUpBorder(float pos) {
	SetGlobalY(pos);
	return *this;
}
Rect& Rect::SetDownBorder(float pos) {
	SetGlobalY(pos - GetHeigth());
	return *this;
}
//void Rect::MoveLeftBorder(float delta) {
//	MoveX(delta);
//	Rect_size.x -= delta;
//}
//void Rect::MoveRightBorder(float delta) {
//	Rect_size.x += delta;
//}
//void Rect::MoveUpBorder(float delta) {
//	MoveY(delta);
//	Rect_size.y -= delta;
//}
//void Rect::MoveDownBorder(float delta) {
//	Rect_size.y += delta;
//}
//const Vector2* Rect::GetSizePtr() const {
//	return &Rect_size;
//}
Vector2 Rect::GetCenter() const {
	return GetGlobalPosition() + Rect_size / 2;
}
Vector2 Rect::GetSize() const {
	return Rect_size;
}
float Rect::GetLeft() const {
	return GetGlobalPosition().x;
}
float Rect::GetRight() const {
	return GetGlobalPosition().x + Rect_size.x;
}
float Rect::GetUp() const {
	return GetGlobalPosition().y;
}
float Rect::GetDown() const {
	return GetGlobalPosition().y + Rect_size.y;
}
float Rect::GetWidth() const {
	return Rect_size.x;
}
float Rect::GetHeigth() const {
	return Rect_size.y;
}
float Rect::GetRadius() const
{
	return GetWidth()/2;
}
bool Rect::AABBContains(Vector2 const& lu, Vector2 const& size, Vector2 const& p) {
	Vector2 v = p - lu;
	return v <= size && v >= Vector2();
}
bool Rect::AABBContains(Vector2 const& p) {
	Vector2 v = p - GetGlobalPosition();
	return v <= Rect_size && v >= Vector2(0, 0);
}
bool Rect::AABBIntersect(UIregion const& aabb) {
	return true;
}
Vector2 Rect::AABBrelativelyLine(Vector2 const& start, Vector2 const& dir) {
	return Vector2();
}
bool Rect::Contains(Vector2 const& p)
{
	switch (m_RectType)
	{
	case RectType::Rect: {
		Vector2 v = p - GetGlobalPosition();
		return v <= GetSize() && v >= Vector2(0, 0);
	}
	case RectType::Circle:
		return (p - GetCenter()).length_squared() <= std::powf(std::min(GetSize().x, GetSize().y), 2) / 4;
	}
	return false;
}
// Rect

// Drawable
Drawable& Drawable::SetBGColor(Color const& col) {
	m_BGcolor = col;
	DrawUpdate();
	return *this;
}
Drawable& Drawable::SetTexture(std::string const& texture_path) {
	m_BGtexturePath = texture_path;
	DrawUpdate();
	return *this;
}
Drawable& Drawable::SetTextureRect(Rect const& r) {
	m_TextureRect.SetGlobalPosition(r.GetGlobalPosition());
	m_TextureRect.SetSizeAcrossPos(r.GetSize());
	DrawUpdate();
	return *this;
}
Drawable& Drawable::SetSpriteSize(Vector2 const& size) {
	m_SpriteSize = size;
	DrawUpdate();
	return *this;
}
Drawable& Drawable::SetSpriteNumber(size_t n) {
	m_SpriteNum = n;
	DrawUpdate();
	return *this;
}
Drawable& Drawable::SetSpriteNext() {
	if (!m_BGtexturePath.empty()) {
		if (!m_SpriteSize.is_zero()) {
			sf::Vector2u s = ResourceManager::GetTexture(m_BGtexturePath).getSize();
			size_t max_n = size_t(s.x / m_SpriteSize.x);
			m_SpriteNum++;
			m_SpriteNum %= max_n;
		}
	}
	DrawUpdate();
	return *this;
}
Drawable& Drawable::SetSpriteDrawType(SpriteDrawType sdt) {
	m_SpriteDrawType = sdt;
	DrawUpdate();
	return *this;
}
Color Drawable::GetBGColor() const
{
	return m_BGcolor;
}
std::string Drawable::GetBGTexturePath() const
{
	return m_BGtexturePath;
}
sf::Texture& Drawable::GetBGTexture() const
{
	return ResourceManager::GetTexture(m_BGtexturePath);
}
#define M_PI_2     1.57079632679489661923
#define M_PI       3.14159265358979323846
void Drawable::Draw(sf::RenderWindow& rw)
{
	switch (m_RectType)
	{
	case RectType::Rect:
		rw.draw(var, rs);
	break;
	case RectType::Circle:
		rw.draw(vac, rs);
		break;
	}
}
void Drawable::DrawUpdate()
{
	rs = sf::RenderStates::Default;
	switch (m_RectType)
	{
	case RectType::Rect:
	{
		var[0].position = GetGlobalPosition();
		var[1].position = GetGlobalPosition() + Vector2(GetWidth(), 0);
		var[2].position = GetGlobalPosition() + GetSize();
		var[3].position = GetGlobalPosition() + Vector2(0, GetHeigth());

		var[0].color = var[1].color = var[2].color = var[3].color = GetBGColor();

		if (!GetBGTexturePath().empty()) {
			Rect r;
			if (m_SpriteDrawType == SpriteDrawType::SpriteAnim) {
				r.SetGlobalPosition({m_SpriteSize.x*m_SpriteNum,0});
				r.SetSizeAcrossPos(m_SpriteSize);
			}
			else {
				if (m_TextureRect.GetSize().is_zero()) {
					auto s = GetBGTexture().getSize();
					m_TextureRect.SetSizeAcrossPos({ (float)s.x,(float)s.y });
					m_TextureRect.SetGlobalPosition({ 0,0 });
				}
				r.SetGlobalPosition(m_TextureRect.GetGlobalPosition());
				r.SetSizeAcrossPos(m_TextureRect.GetSize());
			}

			var[0].texCoords = { r.GetLeft(), r.GetUp()};
			var[1].texCoords = { r.GetRight(), r.GetUp() };
			var[2].texCoords = { r.GetRight(), r.GetDown() };
			var[3].texCoords = { r.GetLeft(), r.GetDown() };
			rs.texture = &GetBGTexture();
		}
	}
	break;
	case RectType::Circle:
		/*
		sf::VertexArray var(sf::PrimitiveType::TrianglesFan, 32);
			double ang{ 2 * M_PI / 32 };
			Vector2 c = GetCenter();
			float ratio = GetWidth() / GetHeigth(); // >= 1 в большинстве случаев

			for (size_t i = 0; i < 32; i++)
			{
				Vector2 r_vec = Vector2(cos(i * ang), sin(i * ang));
				r_vec.x *= ratio;
				var[i].position = c + r_vec * GetHeigth()/2;
				var[i].color = Color::Green;
			}
			rw.draw(var);
		*/
	{
		double ang{ 2 * M_PI / 32 };
		float r = GetWidth() / 2;
		float texture_rad{ 0 };
		Vector2 texture_center;
		std::vector<Vector2> dirs(32);

		if (!GetBGTexturePath().empty()) {
			texture_center = { GetBGTexture().getSize().x / 2.f, GetBGTexture().getSize().y / 2.f };
			texture_rad = std::min(texture_center.x, texture_center.y);
			rs.texture = &GetBGTexture();
		}

		for (size_t i = 0; i < 32; i++)
		{
			Vector2 r_vec = Vector2(cos(i * ang), sin(i * ang));
			dirs[i] = r_vec;
			vac[i].position = GetCenter() + r_vec * r;
			vac[i].color = GetBGColor();
			vac[i].texCoords = texture_center + r_vec * texture_rad;
		}
	}
	break;
	}
}
// Drawable


// UIregion
json UIregion::GetJson()
{
	json js;
	js["type"] = "UIregion";
	js["name"] = Name;
	js["local_position"] = { GetLocalPosition().x, GetLocalPosition().y };
	js["size"] = { GetSize().x, GetSize().y };
	js["childrens"] = json::array();
	for (auto& i : GetChildrens()) {
		js["childrens"].push_back(static_cast<UIregion*>(i)->GetName());
	}
	js["isClicable"] = m_isClicable;
	js["isActive"] = m_isActive;
	js["editState"] = (int)m_editState;
	js["BGcolor"] = { m_BGcolor.r, m_BGcolor.g, m_BGcolor.b, m_BGcolor.a };
	js["BGtexture"] = m_BGtexturePath;
	
	return js;
}
void UIregion::SetJson(json js)
{
	SetName(js["name"]);
	SetLocalPosition({js["local_position"][0], js["local_position"][1]});
	SetSizeAcrossPos({ js["size"][0],js["size"][1] });

	m_isClicable = js["isClicable"];
	m_isActive = js["isActive"];
	m_editState = (EditState)js["editState"];
	 m_BGcolor.r = js["BGcolor"][0];
	 m_BGcolor.g = js["BGcolor"][1];
	 m_BGcolor.b = js["BGcolor"][2];
	 m_BGcolor.a = js["BGcolor"][3];
	m_BGtexturePath = js["BGtexture"];
}
void UIregion::PostSetJson(json js)
{
	for (auto& i : js["childrens"]) {
		FindByName<UIregion>(i)->SetParent(this);
	}
}
UIregion& UIregion::SetName(std::string name)
{
	m_UIregions.erase(Name);
	m_UIregions[name] = this;
	Name = name;
	return *this;
}
std::string UIregion::GetName() const
{
	return Name;
}

UIregion::UIregion()
{
	Name = "UIregion" + std::to_string(m_lastNameNumber++);
	m_UIregions[Name] = this;
	for (int8_t i = 0; i < SuperMouse::NumKeys; i++)
	{
		isGrab[i] = false;
	}
}
UIregion::~UIregion() {
	m_UIregions.erase(Name);
}
UIregion& UIregion::SetBindLeftBorder(BindPoint bp) {
	m_bindPoint[0] = bp;
	return *this;
}
UIregion& UIregion::SetBindRightBorder(BindPoint bp) {
	m_bindPoint[2] = bp;
	return *this;
}
UIregion& UIregion::SetBindUpBorder(BindPoint bp) {
	m_bindPoint[1] = bp;
	return *this;
}
UIregion& UIregion::SetBindDownBorder(BindPoint bp) {
	m_bindPoint[3] = bp;
	return *this;
}
UIregion& UIregion::ResetBind(uint8_t p) {
	m_bindPoint[0].Reset();
	return *this;
}
UIregion& UIregion::SetActive(bool active)
{
	m_isActive = active;
	return *this;
}
bool UIregion::GetActive() const
{
	return m_isActive;
}
UIregion& UIregion::Clicable(bool b) {
	m_isClicable = b;
	return *this;
}
UIregion& UIregion::SetCallbackOnMouseGrab(std::function<void(SuperMouse::Key, UIregion*)> f) {
	FOnMouseGrab.push_back(f);
	return *this;
}

UIregion& UIregion::SetCallbackOnMousePress(std::function<void(SuperMouse::Key, UIregion*)> f) {
	FOnMousePress.push_back(f);
	return *this;
}
UIregion& UIregion::SetCallbackOnMouseRelease(std::function<void(SuperMouse::Key, UIregion*)> f) {
	FOnMouseRelease.push_back(f);
	return *this;
}
UIregion& UIregion::SetCallbackOnMouseHold(std::function<void(SuperMouse::Key, UIregion*)> f) {
	FOnMouseHold.push_back(f);
	return *this;
}
UIregion& UIregion::SetCallbackOnMouseEnter(std::function<void(UIregion*)> f) {
	FOnMouseEnter.push_back(f);
	return *this;
}
UIregion& UIregion::SetCallbackOnMouseExit(std::function<void(UIregion*)> f) {
	FOnMouseExit.push_back(f);
	return *this;
}
UIregion& UIregion::SetCallbackOnEditable(std::function<void()> f)
{
	FOnEditable.push_back(f);
	return *this;
}

bool UIregion::ClickUpdate(bool dont_handle_clicks)
{
	bool is_click{ false };

	if (m_isClicable) {
		inRectPrev = inRectNow;
		inRectNow = Contains(SuperMouse::map_pose);

		if (!inRectPrev && !inRectNow) { // не в rect 
			for (int8_t i = 0; i < SuperMouse::NumKeys; i++) {
				if (SuperMouse::mButtonState[i] == SuperMouse::Hold) {
					if (isGrab[i]) {
						OnMouseGrab((SuperMouse::Key)i);
						for (auto& f : FOnMouseGrab) {
							f((SuperMouse::Key)i, this);
						}
					}
				}
				else if (SuperMouse::mButtonState[i] == SuperMouse::Not_press) {
					isGrab[i] = false;
				}

			}
			return false;
		}

		if (!inRectNow && inRectPrev) { // вышел из rect
			isAvailable = false;
			OnMouseExit();
			for (auto& f : FOnMouseExit) {
				f(this);
			}
			return false;
		}

		if (inRectNow && !inRectPrev) { // зашел в rect
			bool preAvailable{ false };
			for (int8_t i = 0; i < SuperMouse::NumKeys; i++) {
				preAvailable |= SuperMouse::mButtonState[i] != SuperMouse::Not_press;
			}
			isAvailable = !preAvailable;
			OnMouseEnter();
			for (auto& f : FOnMouseEnter) {
				f(this);
			}
			return false;
		}

		if (inRectNow && inRectPrev) {
			bool preAvailable{ false };
			for (int8_t i = 0; i < SuperMouse::NumKeys; i++) {
				preAvailable |= SuperMouse::mButtonState[i] != SuperMouse::Not_press;
			}
			if(!preAvailable) isAvailable = true;
		}

		if (inRectNow && inRectPrev && !dont_handle_clicks && isAvailable) { // в rect 
			for (int8_t i = 0; i < SuperMouse::NumKeys; i++) {
				switch (SuperMouse::mButtonState[i])
				{
				case SuperMouse::Press:
					OnMousePress((SuperMouse::Key)i);
					for (auto& f : FOnMousePress) {
						f((SuperMouse::Key)i, this);
					}
					is_click = true;
					break;
				case SuperMouse::Release:
					OnMouseRelease((SuperMouse::Key)i);
					for (auto& f : FOnMouseRelease) {
						f((SuperMouse::Key)i, this);
					}

					if (isGrab[i]) isGrab[i] = false;

					break;
				case SuperMouse::Hold:
					OnMouseHold((SuperMouse::Key)i);
					for (auto& f : FOnMouseHold) {
						f((SuperMouse::Key)i, this);
					}

					OnMouseGrab((SuperMouse::Key)i);
					for (auto& f : FOnMouseGrab) {
						f((SuperMouse::Key)i, this);
					}

					isGrab[i] = true;

					break;
				}
			}
		}
		return is_click;
	}
	inRectNow = inRectPrev = false;
	return false;
}

void UIregion::Update()
{
	// Bind point - в разработке(доработке)
	//Vector2 poses[4];
	//uint32_t rigids[4];
	//for (size_t i = 0; i < 4; i++)
	//{
	//	poses[i] = m_bindPoint[i].GetPoint();
	//	rigids[i] = m_bindPoint[i].GetSpringRigid();
	//}
	//if (m_bindPoint[0].GetType() == BindPoint::BindType::MoveSide && m_bindPoint[0].IsExist()) 
	//	SetLeftBorder(poses[0].x);
	//if (m_bindPoint[1].GetType() == BindPoint::BindType::MoveSide && m_bindPoint[1].IsExist())
	//	SetUpBorder(poses[1].y);
	//if (m_bindPoint[2].GetType() == BindPoint::BindType::MoveSide && m_bindPoint[2].IsExist())
	//	SetRightBorder(poses[2].x);
	// 
	//if (m_bindPoint[3].GetType() == BindPoint::BindType::MoveSide && m_bindPoint[3].IsExist())
	//	SetDownBorder(poses[3].y);
	//
	//if (m_bindPoint[0].IsExist() || m_bindPoint[2].IsExist()) { // x
	//	if(rigids[0] + rigids[2] != 0)
	//		SetGlobalX( poses[0].x + (poses[2].x - poses[0].x - Rect_size.x) * rigids[2] / (rigids[0] + rigids[2]));
	//}
	//if (m_bindPoint[1].IsExist() || m_bindPoint[3].IsExist()) { // y
	//	if (rigids[1] + rigids[3] != 0)
	//		SetGlobalY(poses[1].y + (poses[3].y - poses[1].y - Rect_size.y) * rigids[3] / (rigids[1] + rigids[3]));
	//}
	
	/// Проверка на изменение позиции или размера
	m_editState = static_cast<EditState>((char(GetGlobalPosition() != M_position) << 1) | char(GetSize() != M_size));

	if (m_editState != EditState::Null) {
		RecursiveOnEditable(this);
	};

	M_position = GetGlobalPosition();
	M_size = GetSize();
}

void RecursiveOnEditable(UIregion* reg) {
	reg->OnEditable();
	for (auto& f : reg->FOnEditable) {
		f();
	}
	for (auto& u : reg->GetChildrens()) {
		RecursiveOnEditable(dynamic_cast<UIregion*>(u));
	}
}