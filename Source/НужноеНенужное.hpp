//void func(std::string);
//
//void ButtonClick1() {
//	auto name = UIregion::FindByName<UItextInput>("textinput_filename")->GetText();
//	auto path = UIregion::FindByName<UItextInput>("textinput_projname")->GetText();
//	auto p = L"C:/Users/yaffr/source/MyEngineProjects/" + path + L'/';
//	//ComponentFile cf(p+name+".cpp", p+name+".hpp");
//}
//void ButtonClick2() {
//	auto path = UIregion::FindByName<UItextInput>("textinput_projname")->GetText();
//	auto* logger = UIregion::FindByName<UIlogger>("Logger");
//
//	logger->Print(L"Path is empty");
//	//if (path.empty()) {
//	//	logger->Print("Path is empty");
//	//	return;
//	//}
//	//
//	//if (std::filesystem::exists("C:/Users/yaffr/source/MyEngineProjects/" + path)) {
//	//	logger->Print("Opening...");
//	//	VSProject::VOpenProject("C:/Users/yaffr/source/MyEngineProjects/" + path + '/' + path + ".sln");
//	//	logger->Print("Successful");
//	//	func("C:/Users/yaffr/source/MyEngineProjects/" + path + '/');
//	//	return;
//	//}
//	//
//	//logger->Print("Creating...");
//	//VSProject::VCreateProject("C:/Users/yaffr/source/MyEngineProjects", path);
//	//VSProject::VOpenProject("C:/Users/yaffr/source/MyEngineProjects/" + path + '/' + path + ".sln");
//	//logger->Print("Successful");
//	//func("C:/Users/yaffr/source/MyEngineProjects/" + path + '/');
//}
//void func(std::string path) {
//	std::filesystem::directory_iterator dir(path);
//	auto* logger = UIregion::FindByName<UIlogger>("Logger");
//
//	std::vector<std::string> classes;
//	//for (auto& u : dir) {
//	//	if (!u.is_directory() && get_extension_from_path(u.path().string()) == "cpp") {
//	//		classes.push_back(get_file_name_from_path(u.path().string()));
//	//	}
//	//}
//
//	std::string s{ "Find Projects:\n" };
//	for (size_t i = 0; i < classes.size()-1; i++)
//	{
//		s += std::to_string(i+1) + ") " + classes[i] + '\n';
//	}
//	s += std::to_string(classes.size()) + ") " + classes[classes.size() - 1];
//
//	logger->Print(std::wstring(s.begin(), s.end()));
//}

//struct UIdropDownList : public UIregion {
//	UIdropDownList(UIdropDownList&&) = delete;
//	~UIdropDownList() = default;
//	UIdropDownList(Vector2 const& pos, Vector2 const& size, Color const& col) {
//		Clicable(true);
//		SetGlobalPosition(pos);
//		SetSizeAcrossPos(size);
//		SetBGColor(col);
//
//		DDL_text.SetParent(this);
//		DDL_text.SetLocalPosition({0,0});
//		DDL_text.SetSizeAcrossPos(size);
//		DDL_text.SetText(L"Not selected");
//		Color hsv = Color::RGBtoHSV(col.r, col.g, col.b);
//		hsv.h += 10;
//		hsv.h %= 360;
//		
//		DDL_text.SetBGColor(Color::HSVtoRGB(hsv.h, hsv.s, hsv.v));
//	}
//
//	std::string GetType() { return "UIdropDownList"; }
//
//	void SetCallbackOnDDLSelected(std::function<void(UItext*)> f) {
//		f_selected = f;
//	}
//
//	void OnMousePress(SuperMouse::Key key) override{
//		DDL_isOpen = !DDL_isOpen;
//	}
//
//	void OnMousePressOut() {
//		DDL_waitClose = true;
//	}
//
//	void UpdateText() {
//		if (DDL_selected == -1) {
//			DDL_text.SetText(L"Not selected");
//			return;
//		}
//		DDL_text.SetText(DDL_map[DDL_selected]->GetText());
//	}
//
//	void Update() override {
//		UIregion::Update();
//		DDL_text.Update();
//
//		if (DDL_isOpen) {
//			for (auto u : DDL_map) {
//				u.second->Update();
//			}
//		}
//		if (DDL_waitClose) {
//			DDL_isOpen = false;
//			DDL_waitClose = false;
//		}
//	}
//
//	bool ClickUpd(bool dont_handle_clicks = false) {
//		if (DDL_isOpen) {
//			for (auto u : DDL_map) {
//				dont_handle_clicks |= u.second->ClickUpdate(dont_handle_clicks);
//			}
//		}
//		return dont_handle_clicks;
//	}
//
//	void Draw(sf::RenderWindow& rw) override {
//		UIregion::Draw(rw);
//		DDL_text.Draw(rw);
//
//		if (DDL_isOpen) {
//			for (auto u : DDL_map) {
//				u.second->Draw(rw);
//			}
//		}
//	}
//
//	void Set(int k, std::wstring txt) {
//		if (DDL_map.contains(k)) {
//			delete DDL_map[k];
//		}
//		UItext* ptr = new UItext;
//		ptr->SetText(txt);
//		ptr->SetSizeAcrossPos(GetSize());
//		ptr->SetGlobalPosition(GetGlobalPosition() + Vector2(0, GetHeigth() * (k + 1)));
//		ptr->Clicable(true);
//		ptr->SetBGColor(GetBGColor());
//		ptr->SetCallbackOnMousePress([&](SuperMouse::Key, UIregion* r) { for (auto u : DDL_map) { if (u.second->GetText() == static_cast<UItext*>(r)->GetText()) { Select(u.first); } } });
//		DDL_map[k] = ptr;
//	}
//
//	void Set(std::vector<std::wstring> txt) {
//		for(auto var : DDL_map)
//		{
//			delete var.second;
//		}
//		DDL_map.clear();
//
//		for (size_t i = 0; i < txt.size(); i++)
//		{
//			Set((int)i, txt[i]);
//		}
//	}
//
//	void Reset() {
//		DDL_isOpen = false;
//		DDL_selected = DDL_selectedDefault;
//		UpdateText();
//	}
//
//	void Select(int k) {
//		DDL_selected = k;
//		DDL_isOpen = false;
//		UpdateText();
//		f_selected(DDL_map[k]);
//	}
//
//	int GetSelectedNum() {
//		return DDL_selected;
//	}
//
//	std::wstring GetSelectedStr() {
//		return DDL_map[DDL_selected]->GetText();
//	}
//
//	void SetDefault(int k) {
//		DDL_selectedDefault = k;
//		if (DDL_selected == -1) DDL_selected = k;
//		UpdateText();
//	}
//
//	void Clear() {
//		for (auto& i : DDL_map) {
//			delete i.second;
//		}
//		DDL_map.clear();
//		DDL_text.SetText(L"Not selected");
//	}
//
//private:
//	std::function<void(UItext*)> f_selected{ [](UItext*){} };
//
//	std::map<int, UItext*> DDL_map;
//	UItext DDL_text;
//	bool DDL_isOpen{ false };
//	int DDL_selected{ -1 };
//	int DDL_selectedDefault{ -1 };
//	bool DDL_waitClose{ false };
//};
//
//


//struct UIcolorCircle : public __UIcircle {
//	UIcolorCircle() = default;
//	~UIcolorCircle() = default;
//
//	UIcolorCircle(Vector2 pos, float rad) {
//		SetCenter(pos);
//		SetRadius(rad);
//	}
//
//	void Update() override {
//		__UIcircle::Update();
//	}
//	float ator(float a) const{
//		return a / 180.f * pi;
//	}
//
//	void Draw(sf::RenderWindow& rw) override{
//		__UIcircle::Draw(rw);
//
//		int rays = 100, steps = 100;
//		float ray_ang = ator(360 / (float)rays);
//		float ray_ang_deg = 360.f / rays;
//		float step_h = GetRadius()/steps;
//		int color_step = 255 / steps;
//		Vector2 c = GetCenter();
//		for (int i = 0; i < rays; i++)
//		{
//			Vector2 p1, p2, p3, p4, dir1, dir2;
//			dir1 = { cos(ray_ang * i),  sin(ray_ang * i) };
//			dir2 = { cos(ray_ang * (i + 1)),  sin(ray_ang * (i + 1)) };
//
//			for (int j = 0; j < steps; j++)
//			{
//
//				p1 = c + dir1 * j * step_h;
//				p2 = c + dir1 * (j + 1) * step_h;
//				p3 = c + dir2 * (j + 1) * step_h;
//				p4 = c + dir2 * j * step_h;
//				
//				Color c = Color::HSVtoRGB(ray_ang_deg * i, j, velos);
//				//Windower::Win.DrawQuad(p1, p2, p3, p4, c);
//			}
//		}
//	}
//	const float pi = 3.1415926535f;
//	uint8_t velos = 100;
//};

//struct UIcolorPanel : public __UIrectangle {
//	UIcolorPanel() = default;
//	~UIcolorPanel() = default;
//
//	UIcolorPanel(Vector2 pos, Vector2 size, Color col) {
//		SetGlobalPosition(pos);
//		SetSizeAcrossPos(size);
//		SetBGColor(col);
//
//
//		cc.SetRadius(80.f);
//		r.SetSizeAcrossPos({ 200, 20 });
//		g.SetSizeAcrossPos({ 200, 20 });
//		b.SetSizeAcrossPos({ 200, 20 });
//		hue.SetSizeAcrossPos({ 200, 20 });
//		satur.SetSizeAcrossPos({ 200, 20 });
//		velos.SetSizeAcrossPos({ 200, 20 });
//
//
//		BindPoint bp;
//		bp.Pos(GetPositionPtr());
//		bp.Type(BindPoint::BindType::SpringSide);
//		bp.Rigidity(1);
//
//		cc.SetBindUpBorder(bp);
//
//		r.SetBindLeftBorder(bp);
//		g.SetBindLeftBorder(bp);
//		b.SetBindLeftBorder(bp);
//		hue.SetBindLeftBorder(bp);
//		satur.SetBindLeftBorder(bp);
//		velos.SetBindLeftBorder(bp);
//
//		bp.Delta(GetSizePtr()).Rigidity(1);
//
//		r.SetBindRightBorder(bp);
//		g.SetBindRightBorder(bp);
//		b.SetBindRightBorder(bp);
//		hue.SetBindRightBorder(bp);
//		satur.SetBindRightBorder(bp);
//		velos.SetBindRightBorder(bp);
//
//		cc.SetBindLeftBorder(BindPoint().Pos(r.GetPositionPtr()).Type(BindPoint::BindType::SpringSide).Rigidity(1));
//		cc.SetBindRightBorder(BindPoint().Pos(r.GetPositionPtr()).Delta(r.GetSizePtr()).Type(BindPoint::BindType::SpringSide).Rigidity(1));
//
//		r.SetBindUpBorder(BindPoint().Pos(cc.GetPositionPtr()).Delta(cc.GetSizePtr()).Type(BindPoint::BindType::SpringSide).Rigidity(1));
//		r.SetBindDownBorder(BindPoint().Pos(g.GetPositionPtr()).Type(BindPoint::BindType::SpringSide).Rigidity(1));
//
//		g.SetBindUpBorder(BindPoint().Pos(r.GetPositionPtr()).Delta(r.GetSizePtr()).Type(BindPoint::BindType::SpringSide).Rigidity(1));
//		g.SetBindDownBorder(BindPoint().Pos(b.GetPositionPtr()).Type(BindPoint::BindType::SpringSide).Rigidity(1));
//
//		b.SetBindUpBorder(BindPoint().Pos(g.GetPositionPtr()).Delta(g.GetSizePtr()).Type(BindPoint::BindType::SpringSide).Rigidity(1));
//		b.SetBindDownBorder(BindPoint().Pos(hue.GetPositionPtr()).Type(BindPoint::BindType::SpringSide).Rigidity(1));
//
//		hue.SetBindUpBorder(BindPoint().Pos(b.GetPositionPtr()).Delta(b.GetSizePtr()).Type(BindPoint::BindType::SpringSide).Rigidity(1));
//		hue.SetBindDownBorder(BindPoint().Pos(satur.GetPositionPtr()).Type(BindPoint::BindType::SpringSide).Rigidity(1));
//
//		satur.SetBindUpBorder(BindPoint().Pos(hue.GetPositionPtr()).Delta(hue.GetSizePtr()).Type(BindPoint::BindType::SpringSide).Rigidity(1));
//		satur.SetBindDownBorder(BindPoint().Pos(velos.GetPositionPtr()).Type(BindPoint::BindType::SpringSide).Rigidity(1));
//
//		velos.SetBindUpBorder(BindPoint().Pos(satur.GetPositionPtr()).Delta(satur.GetSizePtr()).Type(BindPoint::BindType::SpringSide).Rigidity(1));
//		velos.SetBindDownBorder(BindPoint().Pos(GetPositionPtr()).Delta(GetSizePtr()).Type(BindPoint::BindType::SpringSide).Rigidity(1));
//
//		r.SetCallbackOnSlide([&](float p) {R_edit(p); });
//		g.SetCallbackOnSlide([&](float p) {G_edit(p); });
//		b.SetCallbackOnSlide([&](float p) {B_edit(p); });
//		hue.SetCallbackOnSlide([&](float p) {Hue_edit(p); });
//		satur.SetCallbackOnSlide([&](float p) {Satur_edit(p); });
//		velos.SetCallbackOnSlide([&](float p) {Velos_edit(p); });
//		cc.Clicable(true);
//		cc.SetCallbackOnMouseGrab([&](SuperMouse::Key, UIregion*) {CC_grab(); });
//
//		r.SetValue(1.f);
//		g.SetValue(0.f);
//		b.SetValue(0.f);
//		hue.SetValue(0.f);
//		satur.SetValue(1.f);
//		velos.SetValue(1.f);
//	}
//
//	void Update() override{
//		__UIrectangle::Update();
//		cc.Update();
//		r.Update();
//		g.Update();
//		b.Update();
//		hue.Update();
//		satur.Update();
//		velos.Update();
//	}
//
//	void Draw(sf::RenderWindow& rw) override {
//		__UIrectangle::Draw(rw);
//		cc	 .Draw(rw);
//		r	 .Draw(rw);
//		g	 .Draw(rw);
//		b	 .Draw(rw);
//		hue	 .Draw(rw);
//		satur.Draw(rw);
//		velos.Draw(rw);
//
//		float hue_val = hue.GetValue()*pi2;
//		Vector2 dir = { cos(hue_val), sin(hue_val) };
//
//		Color rgb = Vector3(r.GetValue(), g.GetValue(), b.GetValue()) * 255;
//		Color hsv = Color::RGBtoHSV(rgb.r, rgb.g, rgb.b);
//
//		//Windower::Win.DrawCircle(cc.GetCenter() + dir * cc.GetRadius() * (hsv.s / 100.f), 11, { 40,40,40 });
//		//Windower::Win.DrawCircle(cc.GetCenter() + dir * cc.GetRadius() * (hsv.s / 100.f), 8, rgb);
//	}
//
//	void R_edit(float p) {
//		Color c = Color::RGBtoHSV(p * 255, g.GetValue() * 255, b.GetValue() * 255);
//		hue.SetValue(c.h / 360.f);
//		satur.SetValue(c.s / 100.f);
//		velos.SetValue(c.v / 100.f);
//		cc.velos = c.v;
//	}
//	void G_edit(float p) {
//		Color c = Color::RGBtoHSV(r.GetValue() * 255, p * 255, b.GetValue() * 255);
//		hue.SetValue(c.h / 360.f);
//		satur.SetValue(c.s / 100.f);
//		velos.SetValue(c.v / 100.f);
//		cc.velos = c.v;
//	}
//	void B_edit(float p) {
//		Color c = Color::RGBtoHSV(r.GetValue() * 255, g.GetValue() * 255, p * 255);
//		hue.SetValue(c.h / 360.f);
//		satur.SetValue(c.s / 100.f);
//		velos.SetValue(c.v / 100.f);
//		cc.velos = c.v;
//	}
//	void Hue_edit(float p) {
//		Color c = Color::HSVtoRGB(uint16_t(p*360), uint8_t(satur.GetValue()*100), uint8_t(velos.GetValue() * 100));
//		r.SetValue(c.r / 255.f);
//		g.SetValue(c.g / 255.f);
//		b.SetValue(c.b / 255.f);
//	}
//	void Satur_edit(float p) {
//		Color c = Color::HSVtoRGB(uint16_t(hue.GetValue() * 360), uint8_t(p * 100), uint8_t(velos.GetValue() * 100));
//		r.SetValue(c.r / 255.f);
//		g.SetValue(c.g / 255.f);
//		b.SetValue(c.b / 255.f);
//	}
//	void Velos_edit(float p) {
//		Color c = Color::HSVtoRGB(uint16_t(hue.GetValue() * 360), uint8_t(satur.GetValue() * 100), uint8_t(p * 100));
//		r.SetValue(c.r / 255.f);
//		g.SetValue(c.g / 255.f);
//		b.SetValue(c.b / 255.f);
//		cc.velos = uint8_t(p * 100);
//	}
//
//	void CC_grab() {
//		Vector2 d = (SuperMouse::map_pose - cc.GetCenter()) / cc.GetRadius();
//		float ang = std::atan2f(d.y, d.x);
//		if (ang < 0.f) ang += pi2;
//		ang /= pi2;
//		hue.SetValue(ang);
//		float len_d = d.length();
//		len_d = len_d <= 1.f ? len_d : 1.f;
//		Color c = Color::HSVtoRGB(uint16_t(ang * 360), uint8_t(len_d *100), cc.velos);
//		r.SetValue(c.r / 255.f);
//		g.SetValue(c.g / 255.f);
//		b.SetValue(c.b / 255.f);
//		satur.SetValue(len_d);
//		
//		//FindByName<UIlogger>("Logger")->Print(std::to_string(ang) + ' ' + std::to_string(ang / (2 * 3.1415926535f)));
//	}
//
//private:
//	const float pi{ 3.1415926535f };
//	const float pi2{ 2.f*pi };
//
//	UIcolorCircle cc ;
//	UIslider      r  ; 
//	UIslider      g  ;
//	UIslider      b  ;
//	UIslider      hue;
//	UIslider      satur;
//	UIslider      velos;
//
//};