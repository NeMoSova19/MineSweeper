#pragma once
#include <vector>

struct Object;
struct Component;

struct Component
{
	std::string name, tag;
	Object* gameObject{ nullptr };

	virtual void Start() {}
	virtual void Tick(float delta) {}
	virtual void FixedUpdate() {}
	virtual void End() {}
};


struct ComponentData {
	ComponentData(std::string type, void* p, Object* go) {
		type_name = type;
		ptr = p;
		comp = static_cast<Component*>(p);
		comp->gameObject = go;
	}
	void update(void* p, Object* go) {
		ptr = p;
		comp = static_cast<Component*>(p);
		comp->gameObject = go;
	}

	Component* comp;
	std::string type_name;
	void* ptr;
};

struct Object {
	Object(std::string n) {
		m_name = n;
	}
	static inline void Create(std::string n) {
		objects.emplace_back(new Object(n));
	}
	~Object() {
		std::cout << "Object " << m_name << " delete\n";
	}
	std::string m_name;

	void addComponent(std::string name, void* ptr) {
		for (auto u : components) {
			if (u.type_name == name) {
				u.update(ptr, this);
				return;
			}
		}
		components.emplace_back(name, ptr, this);
	}

	template<class T> void addComponent() {
		std::string name = typeid(T).name();
		name = name.substr(name.find(' ') + 1);
		void* ptr = new T;
		addComponent(name, ptr);
	}

	Component& getComponent(std::string name)
	{
		for (auto u : components) {
			if (u.type_name == name) {
				return *u.comp;
			}
		}
		printf_s("Error: getComponent()");
		throw "error";
	}

	static Object& findObject(std::string name) {
		for (auto& u : objects) {
			if (u->m_name == name)
				return *u;
		}
		throw(std::exception());
	}

	template<class T> T& getOriginalComponent()
	{
		std::string find = typeid(T).name();
		find = find.substr(find.find(' ') + 1);

		for (auto& u : components) {
			if (u.type_name == find) {
				return *static_cast<T*>(u.ptr);
			}
		}
		printf_s("Error: getOriginalComponent()");
		throw "error";
	}

	std::vector<ComponentData> components{};

	static inline std::vector<Object*> objects;
};