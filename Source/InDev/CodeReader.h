#pragma once
#include <iostream>
#include <string>
using namespace std;

inline void reflect(const string& cpp, const string& txt)
{
	std::ifstream file;
	string text, line, lline; bool comment{ false }; size_t comment_start{0};
	file.open(cpp);
	while(getline(file, line))
	{
		size_t p = line.find("//");
		if(p != string::npos)
		{
			line = line.substr(0, p);
		}

		if (!comment) // false
		{
			p = line.find("/*");
			if (p != string::npos)	 // found
			{
				comment = true;
				comment_start = p;
			}
		}

		if(comment)
		{
			lline += line;
			p = lline.rfind("*/");
			if (p != string::npos)	 // found
			{
				comment = false;
				lline = "";
				text += lline.substr(comment_start, p - comment_start);
				text += '\n';
			}
			continue;
		}
		text += line + '\n';
	}
	file.close();
	// чтение и очистка кода
	//
	// поиск макросов
	vector<string> component_props;
	size_t class_pos_start = text.find("CLASS");
	size_t class_pos_end = text.find("};", class_pos_start);
	size_t pos = class_pos_start;
	while (true)
	{
		pos = text.find("PROPERTY", pos + 1);
		if (pos == string::npos) break;

		size_t left, right;
		left = text.rfind('\n', pos)+1;
		left = max(left, text.rfind(';', pos) + 1);
		left = max(left, text.rfind(':', pos) + 1);
		right = text.find(';', pos);
		stringstream sg_sm(text.substr(left, right - left));

		string word, type, name, val;
		while(sg_sm >> word)
		{
			if(word.contains("PROPERTY"))
			{
				sg_sm >> name;
				val = name.substr(name.find('{') + 1, name.find('}') - name.find('{') - 1);
				name = name.substr(0, name.find('{'));
				break;
			}
			type += word;
		}
		printf_s("(%s) (%s) = (%s)\n", type.c_str(), name.c_str(), val.c_str());
	}



	//
	// запись в файл

	// class name
	// private type name val;
	ofstream out(txt);
	out << "file declaration user script\n.\n.\n.\n.\n.\n.\n.\n.\n.";
	out.close();
}




//#include <string>
//#include <vector>
//
//template<typename T> struct ListSet
//{
//	ListSet() = default;
//	explicit ListSet(std::initializer_list<T> l)
//	{
//		for (auto b : l)
//		{
//			add(b);
//		}
//	}
//
//	ListSet<T>* left{nullptr}, * right{ nullptr };
//
//	ListSet<T> *next{ nullptr }, * prev{ nullptr };
//	T var{};
//
//	long long lenght{ 0 };
//
//	void addIfNot(T v)
//	{
//		if(left == nullptr && right == nullptr)
//		{
//			left = right = this;
//			right->var = v;
//			lenght++;
//			return;
//		}
//
//		ListSet<T>* it = left;
//		while(it != right)
//		{
//			if (it->var == v) return;
//			it = it->next;
//		}
//
//		right->next = new ListSet<T>;
//		right->next->prev = right;
//		right = right->next;
//		right->var = v;
//		lenght++;
//	}
//	void add(T v)
//	{
//		if (left == nullptr && right == nullptr)
//		{
//			left = right = this;
//			right->var = v;
//			lenght++;
//			return;
//		}
//
//		right->next = new ListSet<T>;
//		right->next->prev = right;
//		right = right->next;
//		right->var = v;
//		lenght++;
//	}
//	void add(ListSet<T> v)
//	{
//		if (left == nullptr && right == nullptr)
//		{
//			left = v.left;
//			right = v.right;
//			lenght = v.lenght;
//			return;
//		}
//
//		if (v.left == nullptr && v.right == nullptr) return;
//
//		right->next = v.left;
//		v.left->prev = right;
//		right = v.right;
//		lenght += v.lenght;
//	}
//	ListSet<T>* find(const T& f)
//	{
//		ListSet<T>* it = left;
//		if (it->var == f) return it;
//
//		while (it != right && it != nullptr)
//		{
//			if (it->var == f) return it;
//			it = it->next;
//		}
//		return nullptr;
//	}
//
//	T& at(int n)
//	{
//		if (n >= lenght) return nullptr;
//
//		ListSet<T>* it = left;
//		for(int i = 0; i < n; i++)
//		{
//			it = it->next;
//		}
//		return it;
//	}
//
//	void print() const
//	{
//		auto it = left;
//
//		std::cout << it->var << ' ';
//		for (int i = 1; i < lenght; i++)
//		{
//			it = it->next;
//			std::cout << it->var << ' ';
//		}
//
//	}
//};
//
//template<class T> void operator += (std::vector<T>& Left, std::vector<T>& Right)
//{
//	Left.insert(Left.end(), Right.begin(), Right.end());
//}
//
//inline static ListSet<std::string> types{"int", "float", "double", "bool", "auto", "char", "void", "string", "vector", "Vector2", "Vector3", "Vector4"};
//inline static ListSet<std::string> pre_types{"short", "long", "signed", "unsigned", "static", "const", "inline"};
//inline static ListSet<std::string> class_modify{"private", "public", "protected"};
//inline static ListSet<std::string> constants{"true", "false", "NULL", "nullptr"};
//inline static ListSet<std::string> clases{"class", "struct"}; // enum
//inline static ListSet<std::string> namespaces{};
//inline static std::string first_letter_warning = "-+={}[](),./;:\'\"\\|<>&*!0123456789\t\n%#";
//inline static ListSet<std::string> not_name_warning{"operator"};
//inline static ListSet<std::string> includes{""};
//
//struct _Variable
//{
//	std::string name_space;
//	std::vector<std::string> pre_type;
//	std::string type; std::string name; std::string value;
//};
//struct _CVariable
//{
//	std::string name_space;
//	std::string access;
//	std::vector<std::string> pre_type;
//	std::string type; std::string name; std::string value;
//};
//struct _Class
//{
//	std::string name_space;
//	std::string c; std::string name;
//	std::vector<_CVariable> properties;
//	_Class* parent;
//};
//
//inline std::vector<_Class> Vclass{};
//inline std::vector<_Variable> Vvar{};
//
//// нарисовать все возможные варианты объ€влений переменных и классов с наследованием
//// сломались модификаторы доступа в классе
//
//class CodeReader {
//public:
//	static void Convert(std::string path) {
//		//std::cout << path << '\n';
//		not_name_warning.add(pre_types);
//		not_name_warning.add(types);
//		not_name_warning.add(class_modify);
//		not_name_warning.add(constants);
//		not_name_warning.add(clases);
//		not_name_warning.add(namespaces);
//
//		using namespace std;
//		std::string line;
//		std::ifstream file;
//		vector<string> sl;
//		std::string c_mod;
//
//		bool class_open = false;
//		int string_open = -1;
//
//		file.open(path);
//		while (getline(file, line)) {
//			split(line, sl);
//		}
//			
//		for (int i = 0; i < sl.size(); i++)
//		{
//			if(sl[i] == "#include")
//			{
//				if (sl[i + 1] == "\"")
//				{
//					if(path[path.size()-1] == '\\')
//					{
//						path.erase(path.end());
//						if (path[path.size() - 1] == '\\')
//						{
//							path.erase(path.end());
//						}
//					}
//					path.erase(path.rfind('\\')+1);
//
//					string new_path = path + sl[i + 2];
//
//					cout << "To the " << new_path << '\n';
//					Convert(new_path);
//					cout << '\n' << "From the " << new_path << '\n';
//				}
//			}
//			else if((i - 1 >= 0) && (i + 1 < sl.size()) && sl[i-1] == "\"" && sl[i+1] == "\"")
//			{
//				continue;
//			}
//			else if(class_modify.find(sl[i]))
//			{
//				//cout << ">>> " << sl[i] << '\n';
//				c_mod = sl[i];
//			}
//			else if (sl[i] == "}" && sl[i+1] == ";")
//			{
//				class_open = false;
//			}
//
//			else if (sl[i] == ":" && sl[i+1] == ":")
//			{
//				std::string name_sp = sl[i - 1];
//				std::string type = sl[i + 2];
//				if(types.find(type))
//				{
//					string name = sl[i + 3];
//					if (In(name[0], first_letter_warning) || not_name_warning.find(name)) continue;
//					
//
//					if (sl[i + 4] != "(") // не функци€
//					{
//						std::vector<std::string> modif;
//						int ii = i - 2;
//						while (ii >= 0 && pre_types.find(sl[ii])) // поиск модификаторов типа 
//						{
//							modif.push_back(sl[ii--]);
//						}
//
//						std::string val;
//						if (sl[i + 4] == "=" || sl[i+4] == "{")
//						{
//							val = sl[i + 5];
//							if(val == "\"")
//							{
//								while(true)
//								{
//									if(sl[++i] == "\"")
//									{
//										break;
//									}
//									val += sl[i];
//								}
//							}
//						}
//
//						if (class_open)
//						{
//							Vclass[Vclass.size() - 1].properties.emplace_back(name_sp, c_mod, modif, type, name, val);
//						}
//						else
//						{
//							Vvar.emplace_back(name_sp, modif, type, name, val);
//						}
//					}
//				}
//			}
//			else if (types.find(sl[i])) // поиск по типу переменной
//			{
//				std::string t = sl[i];
//				std::string n = sl[i + 1];
//				if (In(n[0], first_letter_warning)) continue;
//				if (not_name_warning.find(n)) continue;
//				
//
//				if (i + 3 < static_cast<int>(sl.size()) && sl[i + 2] != "(") // не функци€
//				{
//					std::vector<std::string> pt;
//					int ii = i - 1;
//					while (ii >= 0 && pre_types.find(sl[ii])) // поиск модификаторов типа 
//					{
//						pt.push_back(sl[ii--]);
//					}
//
//					std::string v;
//					if(sl[i+2] == "=" || sl[i + 2] == "{")
//					{
//						v = sl[i + 3];
//						if (v == "\"")
//						{
//							ii =i + 4;
//							while (true)
//							{
//								v += sl[ii];
//								if (sl[ii++] == "\"")
//								{
//									break;
//								}
//							}
//						}
//					}
//					
//						//i += 1;
//					
//					
//
//					if (class_open)
//					{
//						Vclass[Vclass.size()-1].properties.emplace_back("", c_mod, t, n, v);
//					}
//					else
//					{
//						Vvar.emplace_back("", t, n, v);
//					}
//				}
//			}
//
//			else if (clases.find(sl[i])) // поиск по объ€влению класса
//			{
//				//cout << ">>> " << sl[i] << '\n';
//				if (sl[i + 2] == "{" || sl[i + 2] == ":" || sl[i + 2] == ";")
//				{
//					types.addIfNot(sl[i + 1]);
//
//					if (sl[i + 2] == "{")
//					{
//						Vclass.emplace_back(sl[i], sl[i + 1]);
//						//i += 2;
//						class_open = true;
//						if (sl[i+2] == "class")
//						{
//							c_mod = "private";
//						}
//						else
//						{
//							c_mod = "public";
//						}
//					}
//					//else if(sl[i + 2] == ":")
//					//{
//					//	Vclass.emplace_back(sl[i], sl[i + 1]);
//					//	i += 2;
//					//	class_open = true;
//					//	if (sl[i] == "class")
//					//	{
//					//		c_mod = "private";
//					//	}
//					//	else
//					//	{
//					//		c_mod = "public";
//					//	}
//					//
//					//	if(class_modify.find(sl[i + 3]))
//					//	{
//					//		for (int j = 0; j < Vclass.size(); j++)
//					//		{
//					//			if(Vclass[j].name == sl[i+4])
//					//			{
//					//				Vclass[Vclass.size() - 1].parent = &Vclass[j];
//					//				break;
//					//			}
//					//		}
//					//	}
//					//	else
//					//	{
//					//		for (int j = 0; j < Vclass.size(); j++)
//					//		{
//					//			if (Vclass[j].name == sl[i + 3])
//					//			{
//					//				Vclass[Vclass.size() - 1].parent = &Vclass[j];
//					//				break;
//					//			}
//					//		}
//					//	}
//					//}
//					else // ;
//					{
//						//i += 1;
//					}
//				}
//			}
//			
//		}
//		cout << '\n';
//		
//		file.close();
//	}
//
//	template<typename T>
//	static void print(const std::vector<T>& v)
//	{
//		for (auto& _v : v)
//		{
//			std::cout << _v << ' ';
//		}
//	}
//
//	static void print(const _Variable& v)
//	{
//		for(auto& u: v.pre_type)
//		{
//			printf_s("%s ", u.c_str());
//		}
//		printf_s("(%s) (%s) = (%s);", v.type.c_str(), v.name.c_str(), v.value.c_str());
//	}
//
//	static void print(const _CVariable& v)
//	{
//		for (auto& u : v.pre_type)
//		{
//			printf_s("%s ", u.c_str());
//		}
//		printf_s("(%s) (%s) (%s) = (%s);", v.access.c_str(), v.type.c_str(), v.name.c_str(), v.value.c_str());
//	}
//
//	static void print(const _Class& c)
//	{
//		printf_s("%s %s{\n", c.c.c_str(), c.name.c_str());
//		for(auto& u: c.properties)
//		{
//			print(u); printf_s("\n");
//		}
//		printf_s("}");
//	}
//private:
//	// вырезать все комментарии
//	// собирать строки из ковычек
//	static void split(std::string s, std::vector<std::string>& vec) {
//		std::string split_seq{" \t\n{}[](),;:+-=<>\"&*"};
//		std::string delete_seq{" \t\n"};
//		size_t T = s.size();
//		bool isfind{ false };
//
//		for (size_t i = 0; i < T;)
//		{
//			// игнорирование однострочного комментари€
//			if(i+1 < s.size() && s.at(i) == '/' && s.at(i+1) == '/')
//			{
//				return;
//			}
//			isfind = false;
//			for (char seq : split_seq)
//			{
//				if (s.at(i) == seq)
//				{
//					// : : string
//					std::string new_s = s.substr(0, i);
//					std::string chr{s[i]};
//					s = s.substr(i + 1);
//					i = 0; T = s.size();
//
//					for (char del_seq : delete_seq)
//					{
//						std::erase(new_s, del_seq);
//					}
//
//					if (!new_s.empty()) {
//						vec.push_back(new_s);
//					}
//					if (delete_seq.find(chr) == std::string::npos)
//						vec.push_back(chr);
//
//					isfind = true;
//					break;
//				}
//			}
//			if(!isfind) i++;
//		}
//		std::string new_s = s;
//
//		if (!new_s.empty()) {
//
//			for (char del_seq : delete_seq)
//			{
//				std::erase(new_s, del_seq);
//			}
//
//			if (!new_s.empty()) {
//				vec.push_back(new_s);
//			}
//		}
//	}
//
//	template<typename T> static bool In(const T& what, std::vector<T>& where)
//	{
//		for (auto & w : where)
//		{
//			if (w == what) return true;
//		}
//		return false;
//	}
//	static bool In(const char& what, const std::string& where)
//	{
//		for (auto& w : where)
//		{
//			if (w == what) return true;
//		}
//		return false;
//	}
//};