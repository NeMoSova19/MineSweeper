#pragma once

#include "Dll_reader.hpp"

#include "Engine.h"

#include "FileWatcher.h"
#include <filesystem>
#include <string>
#include <fstream>


void operator <<(std::ofstream& o, std::ifstream& i) {
    std::string line;
    while (std::getline(i, line)) {
        o << line << '\n';
    }
}

void operator <<(std::string& o, std::ifstream& i) {
    std::string line;
    while (std::getline(i, line)) {
        o += line + '\n';
    }
}


const std::string VC_VersionPath{ "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.38.32919/" };
const std::string VC_LibraryPath_x64{ VC_VersionPath + "lib/x64/" };
const std::string VC_IncludePath{ VC_VersionPath + "include/" };
const std::string ConsolePath{ VC_VersionPath + "bin/Hostx64/x64/cl.exe" };

const std::string WindowsSDK_LibraryPath_um_x64{ "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.22000.0/um/x64/" };
const std::string WindowsSDK_LibraryPath_ucrt_x64{ "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.22000.0/ucrt/x64/" };
const std::string WindowsSDK_IncludePath{ "C:/Program Files (x86)/Windows Kits/10/Include/10.0.22000.0/ucrt/" };


typedef void* (*getNewClass)();
typedef std::vector<Variable_C>* (*getProps)(void*);


class Path abstract {
    static inline std::string PathToSimpleEngine;
    static inline std::string SelectedProject;

public:
    static void SetPath(std::string path) {
        PathToSimpleEngine = path;
    }
    static void SelectProject(std::string project) {
        SelectedProject = project;
    }
    static bool IsProjectSelected() {
        return !SelectedProject.empty();
    }
    static std::string ToProjects() {
        return PathToSimpleEngine + "Projects/";
    }

    static std::string ToEngine() {
        return PathToSimpleEngine + "Engine/";
    }
    static std::string ToProject() {
        return ToProjects() + SelectedProject + '/';
    }

    static std::string ToTempEngine() {
        return ToEngine()+"Temp/";
    }
    static std::string ToTempProject() {
        return ToProject()+"Temp/";
    }

    static std::string ToBinEngine() {
        return ToEngine()+"Bin/";
    }
    static std::string ToBinProject() {
        return ToProject()+"Bin/";
    }
    
    static std::string ToSourceEngine() {
        return ToEngine()+"Source/";
    }
    static std::string ToSourceProject() {
        return ToProject()+"Source/";
    }

    static std::string ToDevenv() {
        return R"("C:/Program Files/Microsoft Visual Studio/2022/Community/Common7/IDE/devenv")";
    }
    static std::string ToMsbuild() {
        return R"("C:/Program Files/Microsoft Visual Studio/2022/Community/MSBuild/Current/Bin/msbuild")";
    }
    static std::string ToProjectSln() {
        return ToProject() + SelectedProject + ".sln";
    }
    static std::string ToProjectVcxproj() {
        return ToProject() + SelectedProject + ".vcxproj";
    }

    static inline std::string Path_left(std::string path, size_t left) {
        std::vector<std::string> path_v;
        std::string path_l;
        for (const char& c : path)
        {
            if (c == '/' || c == '\\') {
                path_v.push_back(path_l);
                path_l = "";
                continue;
            }
            path_l += c;
        }
        if (!path_l.empty())
            path_v.push_back(path_l);

        std::string otvet = path_v[0] + '/';
        for (size_t i = 1; i < path_v.size() - left; i++)
        {
            otvet += path_v[i] + '/';
        }
        return otvet;
    }
    static inline std::string get_file_name_from_path(std::string path) {
        size_t p1 = path.rfind('/');
        size_t p2 = path.rfind('\\');
        size_t point = path.rfind('.');
        if (p1 != std::string::npos) {
            return path.substr(p1 + 1, point - p1 - 1);
        }
        else if (p2 != std::string::npos) {
            return path.substr(p2 + 1, point - p2 - 1);
        }
        return path;
    }
    static inline std::string get_extension_from_path(std::string path) {
        size_t point = path.rfind('.');
        if (point != std::string::npos) {
            return path.substr(point + 1);
        }
        return path;
    }

};


enum class Standart_Type {
    Int8,  // int8_t
    Int16, // int16_t
    Int32, // int / int32_t 
    Int64, // int64_t

    UInt8,	// uint8_t
    UInt16,	// uint16_t
    UInt32,	// uint32_t
    UInt64,	// uint64_t

    Char,
    Wchar,

    String,
    Wstring,

    Bool,
    BoolMask, // Engine::BoolMask

    Float,
    Double,

    Color,
    Vector2,
    Vector3,

    Pointer,
    
    Vector = 0b100000, // vector								  // iterator use
    Set, // set / multiset / ...								  // iterator use
    Map, // map / unordered_map / multimap / unordered_multimap	  // iterator use
    List // list												  // iterator use
};
std::map<std::string, Standart_Type> Dictionary_Types{
    {"int8_t",  Standart_Type::Int8 },
    {"int16_t", Standart_Type::Int16 },
    {"int32_t", Standart_Type::Int32 },
    {"int64_t", Standart_Type::Int64 },
    {"int",     Standart_Type::Int32 },

    {"uint8_t", Standart_Type::UInt8 },
    {"uint16_t",Standart_Type::UInt16 },
    {"uint32_t",Standart_Type::UInt32 },
    {"uint64_t",Standart_Type::UInt64 },

    {"string",  Standart_Type::String },
    {"wstring", Standart_Type::Wstring },

    {"char",    Standart_Type::Char },
    {"wchar_t", Standart_Type::Wchar },

    {"float",   Standart_Type::Float },
    {"double",  Standart_Type::Double },

    {"bool",     Standart_Type::Bool },




    {"vector",Standart_Type::Vector},

    {"set",Standart_Type::Set},
    {"unordered_set",Standart_Type::Set},
    {"multiset",Standart_Type::Set},

    {"map",Standart_Type::Map},
    {"unordered_map",Standart_Type::Map},
    {"multimap",Standart_Type::Map},

    {"list",Standart_Type::List}
};





struct Variable {
    std::string name{};
    std::vector<Standart_Type> type;
    void* ptr{ nullptr };
    void* iterator{ nullptr };
};






std::vector<std::string> split(const std::string& s);
std::string get_text_for_reflection_file(std::string class_name, std::vector<Variable> vars);
Variable getVariable(std::vector<std::string> spl_line, size_t PROP_pos);
void create_reflection_file(std::string path);
void create_empty_reflection_file(std::string path);
std::string FormatingString(std::string const& _str, std::map<std::string, std::string> const& vs);
std::string ReadAll(std::ifstream& fs);










class VSProject {
public:
    static void VCreateProject(std::string name);
    static void VOpenProject();
    static void VSelectProject(std::string name);
    static void VCreateFile(std::string name);
    static void VOpenFile(std::string name);

private:
    static std::string GetTextForSln(const std::string proj_guid, std::string name);
    static std::string GetTextForVcxporj(std::string guid, std::string name);
    static std::string GetTextForFilters();
    static std::string GetTextForUser();
};









struct ComponentFile {
    ComponentFile(std::string name);
    void updateDLL();
    bool findErrors(const std::string&, std::string&);
    void set(std::string obj_name);

    bool dll_is_compile{ false };
    std::string dll_path;
    getNewClass dll_getClassFunc{ nullptr };
    getProps dll_getPropsFunc{ nullptr };

    std::string name, cpp_path, hpp_path;

    static inline bool Recompiling{ false };

    static inline std::vector<ComponentFile*> componentFiles;
    static void fileUpdated(File* f);
};










void VSProject::VCreateProject(std::string name) {
    Path::SelectProject(name);
    if (std::filesystem::exists(Path::ToProject())) {        //
        std::cout << "Project alredy exist\n";               // deprecated
        return;                                              //
    }                                                        //

    std::filesystem::create_directory(Path::ToProject());
    std::filesystem::create_directory(Path::ToBinProject());
    std::filesystem::create_directory(Path::ToSourceProject());
    std::filesystem::create_directory(Path::ToTempProject());

    std::ofstream sln(Path::ToProjectSln());
    std::ofstream vcxproj(Path::ToProjectVcxproj());
    std::ofstream filters(Path::ToProjectVcxproj() + ".filters");
    std::ofstream user(Path::ToProjectVcxproj() + ".user");

    sln << GetTextForSln("DCFE9C67-0F07-4978-9C01-776250E3554D", name);
    vcxproj << GetTextForVcxporj("{DCFE9C67-0F07-4978-9C01-776250E3554D}", name);
    filters << GetTextForFilters();
    user << GetTextForUser();

    sln.close();
    vcxproj.close();
    filters.close();
    user.close();
}
void VSProject::VOpenProject() {
    auto com = Path::ToDevenv() + ' ' + Path::ToProjectSln();
    system(com.c_str());
   
    std::this_thread::sleep_for(std::chrono::seconds(1));
}
inline void VSProject::VSelectProject(std::string name)
{
    Path::SelectProject(name);
}
void VSProject::VCreateFile(std::string name) {
    if (!Path::IsProjectSelected()) {
        std::cout << "Project not opened\n";
        throw std::exception("Project not opened");
    }
    if (std::filesystem::exists(Path::ToSourceProject() + name + ".cpp") && std::filesystem::exists(Path::ToSourceProject() + name + ".h")) {
        std::cout << "Already exist\n";
        return;
    }

    std::ifstream cpp_example(Path::ToSourceEngine() + "cpp.txt");
    std::ifstream hpp_example(Path::ToSourceEngine() + "hpp.txt");
    std::ofstream cpp(Path::ToSourceProject() + name + ".cpp");
    std::ofstream hpp(Path::ToSourceProject() + name + ".h");

    
    cpp << FormatingString(ReadAll(cpp_example), { {"name", name } });
    hpp << FormatingString(ReadAll(hpp_example), { {"name", name } });
    

    cpp.close();
    hpp.close();
    cpp_example.close();
    hpp_example.close();


    std::ifstream vcx_i(Path::ToProjectVcxproj());
    std::string vcx_text;
    vcx_text << vcx_i;

    size_t finish = vcx_text.rfind("</ItemGroup>");
    std::string src_name = "Source/" + name;
    vcx_text.insert(finish, "<ClInclude Include=\"" + src_name + ".h\" />\n<ClCompile Include=\"" + src_name + ".cpp\" />\n");
    vcx_i.close();

    std::ofstream vcx_o(Path::ToProjectVcxproj());
    vcx_o << vcx_text;
    vcx_o.close();
}
void VSProject::VOpenFile(std::string name) {
    if (!Path::IsProjectSelected()) {
        std::cout << "Project not opened\n";
        throw std::exception("Project not opened");
    }
    
    std::string com = Path::ToDevenv() + " /edit " + Path::ToSourceProject() + name + ".h";
    system(com.c_str());
}

std::string VSProject::GetTextForSln(const std::string proj_guid, std::string name) {
    static std::string fs = R"(Microsoft Visual Studio Solution File, Format Version 12.00
# Visual Studio Version 17
VisualStudioVersion = 17.6.33706.43
MinimumVisualStudioVersion = 10.0.40219.1
Project("{{proj_guid}}") = "{{name}}", "{{name}}.vcxproj", "{15A4848B-EEF7-4BAE-941F-43F7FEB0DE80}"
EndProject
Global
	GlobalSection(SolutionConfigurationPlatforms) = preSolution
		Release|x64 = Release|x64
	EndGlobalSection
	GlobalSection(ProjectConfigurationPlatforms) = postSolution
		{15A4848B-EEF7-4BAE-941F-43F7FEB0DE80}.Release|x64.ActiveCfg = Release|x64
		{15A4848B-EEF7-4BAE-941F-43F7FEB0DE80}.Release|x64.Build.0 = Release|x64
	EndGlobalSection
	GlobalSection(SolutionProperties) = preSolution
		HideSolutionNode = FALSE
	EndGlobalSection
	GlobalSection(ExtensibilityGlobals) = postSolution
		SolutionGuid = {{proj_guid}}
	EndGlobalSection
EndGlobal)";
    return FormatingString(fs,
        {
        {"proj_guid", '{' + proj_guid + '}'},
        {"name", name}
        });
}
std::string VSProject::GetTextForVcxporj(std::string guid, std::string name) {
    
    std::ifstream example(Path::ToSourceEngine()+"vcxproj.txt");
    std::string text, line;

    while (std::getline(example, line)) {
        text += line + '\n';
    }

    std::string output;
    
    output = FormatingString(text, 
        { 
        {"ProjectGuid", guid}, 
        {"RootNamespace", name}, 
        {"AdditionalIncludeDirectories", Path::ToSourceEngine()}
        });

    return output;
}
std::string VSProject::GetTextForFilters() {
    return R"(<?xml version="1.0" encoding="utf-8"?>
<Project ToolsVersion="4.0" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
  <ItemGroup>
    <Filter Include="Source Files">
      <UniqueIdentifier>{4FC737F1-C7A5-4376-A066-2A32D752A2FF}</UniqueIdentifier>
      <Extensions>cpp;c;cc;cxx;c++;cppm;ixx;def;odl;idl;hpj;bat;asm;asmx</Extensions>
    </Filter>
    <Filter Include="Header Files">
      <UniqueIdentifier>{93995380-89BD-4b04-88EB-625FBE52EBFB}</UniqueIdentifier>
      <Extensions>h;hh;hpp;hxx;h++;hm;inl;inc;ipp;xsd</Extensions>
    </Filter>
    <Filter Include="Resourses">
      <UniqueIdentifier>{67DA6AB6-F800-4c08-8B7A-83BB121AAD01}</UniqueIdentifier>
      <Extensions>rc;ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe;resx;tiff;tif;png;wav;mfcribbon-ms</Extensions>
    </Filter>
  </ItemGroup>
</Project>)";
}
std::string VSProject::GetTextForUser() {
    return R"(<?xml version="1.0" encoding="utf-8"?>
<Project ToolsVersion="Current" xmlns = "http://schemas.microsoft.com/developer/msbuild/2003">
  <PropertyGroup/>
</Project>)";
}












ComponentFile::ComponentFile(std::string name) { // попытка загрузки из папки <Project>/Bin
    //std::cout << "Создаю ассоциации файлов\n";
    
    cpp_path = Path::ToSourceProject() + name + ".cpp";
    hpp_path = Path::ToSourceProject() + name + ".h";
    this->name = name;

    dll_path = Path::ToBinProject() + name + ".dll";

    FileWatcher::addFile(cpp_path);
    FileWatcher::addFile(hpp_path);

    componentFiles.push_back(this);
    
    if (!std::filesystem::exists(dll_path)) {
        std::cout << "dll not found. creating...\n";
        updateDLL();
        return;
    }


    bool isFind = _LoadLibrary(dll_path.c_str());
    if (!isFind) {
        std::cout << "dll opening error\n";
        return;
    }
    
    getNewClass getClassFunc = (getNewClass)_GetProcAddress(dll_path.c_str(), "getNewClass");
    getProps getPropsFunc = (getProps)_GetProcAddress(dll_path.c_str(), "getProps");
    
    if (!(getClassFunc && getPropsFunc)) {
        std::cout << "functions not defined in dll\n";
        return;
    }
    
    dll_getClassFunc = getClassFunc;
    dll_getPropsFunc = getPropsFunc;
    dll_is_compile = true;
}
void ComponentFile::updateDLL() { // обновление dll и загрузка в папку <Project>/Bin при успешной сборке из <Project>/Temp
    //std::cout << "Обновляю Dll " << dll_path << '\n';

    //std::cout << "Создаю пустые файлы рефлексии\n";
    for (auto& u : componentFiles) {
        create_empty_reflection_file(u->hpp_path);
    }

    //std::cout << "Создаю файл рефлексии для Dll\n";
    create_reflection_file(hpp_path);

    //std::cout << "Запускаю поиск ошибок\n";
    std::string errors;
    if (findErrors(cpp_path, errors)) {
        std::cout << "Errors:\n";
        std::cout << errors << '\n';
        std::cout << "End errors\n";
        return;
    }

    //std::cout << "Освобождаю текущюю Dll\n";
    _FreeLibrary(dll_path.c_str());
    //std::cout << "Копирую\n";
    std::filesystem::remove(dll_path);
    std::filesystem::copy_file(Path::ToTempProject() + name + ".dll", dll_path);
    std::filesystem::remove(Path::ToTempProject() + name + ".dll");
     
    //std::cout << "Проверяю\n";
    bool isFind = _LoadLibrary(dll_path.c_str());
    if (!isFind) {
        std::cout << "Dll not found\n";
        return;
    }

    getNewClass getClassFunc = (getNewClass)_GetProcAddress(dll_path.c_str(), "getNewClass");
    getProps getPropsFunc = (getProps)_GetProcAddress(dll_path.c_str(), "getProps");

    if (!(getClassFunc && getPropsFunc)) {
        std::cout << "Functions not found\n";
        return;
    }
    //std::cout << "Ок\n";

    dll_getClassFunc = getClassFunc;
    dll_getPropsFunc = getPropsFunc;

    for (auto& obj : Object::objects) {
        for (auto& comp : obj->components) {

            if (name == comp.type_name) {
                comp.update(getClassFunc(), obj);
                //std::vector<Variable_C> d(*getPropsFunc(comp.ptr));
                break;
            }
        }
    }
}
bool ComponentFile::findErrors(const std::string& path, std::string& errors)
{ 
    std::ofstream file(Path::ToTempProject() + "/command.bat");
    std::string str = format(R"("{}" /LD /EHsc /std:c++latest /nologo /I"{}" /I"{}" /I"{}" /I"{}" "{}" /link /LIBPATH:"{}" /LIBPATH:"{}" /LIBPATH:"{}")", // подключать dll с помощью lib 
        ConsolePath, VC_IncludePath, WindowsSDK_IncludePath, Path::ToSourceEngine(), Path::ToSourceProject(), path,  VC_LibraryPath_x64, WindowsSDK_LibraryPath_um_x64, WindowsSDK_LibraryPath_ucrt_x64);
    
    file << str; 
    file.close(); 

    char buffer[128];
    std::string result;
    FILE* pipe = _popen(("cd " + Path::ToTempProject() + " & command.bat").c_str(), "r");
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
    {
        result += buffer;
    }
    _pclose(pipe);
    
    std::filesystem::remove(Path::ToTempProject() + "/command.bat");
    
    std::stringstream s(result);
    std::string s_line;
    errors = "";

    while (std::getline(s, s_line))
    {
        if (s_line.find("error") != std::string::npos)
        {
            if (!errors.empty()) errors += '\n';
            errors += s_line;
        }
    }
    if (errors.empty())
        return false;
    return true;
}
void ComponentFile::fileUpdated(File* f) {
    Recompiling = true;
    //std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Updating...";
    for (auto& u : componentFiles) {
        if (u->cpp_path == f->path_to_file || u->hpp_path == f->path_to_file) {
            u->updateDLL();
        }
    }
    std::cout << "\rUpdated             \n";
    //std::this_thread::sleep_for(std::chrono::milliseconds(100));
    Recompiling = false;
}
void ComponentFile::set(std::string obj_name) {
    void* ptr{ nullptr };
    ptr = dll_getClassFunc();
    Object::findObject(obj_name).addComponent(name, ptr);
}












std::string FormatingString(std::string const& _str, std::map<std::string, std::string> const& vs) {
    std::string str(_str);
    size_t p{ 0 }, p1{ 0 };

    while (true) {
        p = str.find("{{", p);
        if (p == std::string::npos) break;
        p1 = str.find("}}", p);
        if (p1 == std::string::npos) break;


        str.replace(p, p1 - p + 2, vs.at(str.substr(p + 2, p1 - p - 2)));
    }
    return str;
}
std::string ReadAll(std::ifstream& fs) {
    std::string s, line;
    while (std::getline(fs, line)) {
        s += line + '\n';
    }
    return s;
}
std::vector<std::string> split(const std::string& s) {
    std::vector<std::string> vec;
    std::string word;
    for (const char& c : s)
    {
        if (c == ' ' || c == '=' || c == '{' || c == '(' || c == ';' || c == '<' || c == '>' || c == '\t' || c == ':' || c == ',') {
            if (!word.empty())
                vec.push_back(word);

            word = "";
            
            if (c != ' ') {
                word = c;
                vec.push_back(word);
                word = "";
            }

            continue;
        }
        word += c;
    }
    if (!word.empty())
        vec.push_back(word);

    //std::cout << "Split: ";
    //for (auto& u : vec) {
    //    std::cout << u << ' ';
    //}
    //std::cout << '\n';
    return vec;
}
std::string GetVector(std::vector<Standart_Type> v) {
    std::string s{ "{ " };
    for (auto u : v) {
        s += std::to_string((int)u) + ',';
    }
    s.pop_back();
    s += " }";
    return s;
}
std::string get_text_for_reflection_file(std::string class_name, std::vector<Variable> vars) {
    static std::string fs1 = R"(#pragma once
#define COMPONENT
#define PROPERTY
#define DLL extern "C" __declspec(dllexport)

std::vector<Variable_C> props;

#define BODY() DLL void* getNewClass() {\
    return static_cast<void*>(new {{class_name}} ); \
}\
DLL std::vector<Variable_C>* getProps({{class_name}}* ptr) {\
    props.clear();\
)";
    static std::string fs2 = R"(    props.push_back({ "{{name}}", {{vector}}, &ptr->{{name}}, new MyIterator2(ptr->{{name}}.begin()) });\
)";
    static std::string fs3 = R"(    props.push_back({ "{{name}}", {{vector}}, &ptr->{{name}}, new MyIterator1(ptr->{{name}}.begin()) });\
)";
    static std::string fs4 = R"(    props.push_back({ "{{name}}", {{vector}}, &ptr->{{name}}, new MyIterator0() });\
)";

    std::string output;

    output = FormatingString(fs1, { { "class_name" , class_name} });

    for (auto& u : vars) {
        if (u.type[0] == Standart_Type::Map) {
            output += FormatingString(fs2, { { "name" , u.name}, {"vector", GetVector(u.type)}});
            continue;
        }
        if (u.type[0] >= Standart_Type::Vector) {
            output += FormatingString(fs3, { { "name" , u.name}, {"vector", GetVector(u.type)}});
            continue;
        }
        output += FormatingString(fs4, { { "name" , u.name}, {"vector", GetVector(u.type)}});
    }
    output += "\treturn &props; \\\n}";

    return output;
}
Variable getVariable(std::vector<std::string> spl_line, size_t PROP_pos) {
    Variable v;
    v.name = spl_line[PROP_pos + 1];


    std::vector<Standart_Type> types;

    for (size_t i = 0; i < PROP_pos; i++)
    {
        if (Dictionary_Types.contains(spl_line[i])) {
            types.push_back(Dictionary_Types[spl_line[i]]);
        }
    }

    v.type = types;
    
    return v;

}
void create_reflection_file(std::string path) {
    std::string save_to = Path::Path_left(path, 1) + "reflection." + Path::get_file_name_from_path(path) + ".h";
    std::string class_name;
    std::vector<Variable> vars;

    std::ifstream file(path);
    std::string line;
    std::string text;
    while (std::getline(file, line)) {
        text += line + '\n';
        if (line.contains("COMPONENT")) {
            std::vector<std::string> spl_line = split(line);
            for (size_t i = 0; i < spl_line.size(); i++)
            {
                if (spl_line[i] == "COMPONENT") {
                    class_name = spl_line[i + 1];
                    continue;
                }
            }
        }
        if (line.contains("PROPERTY")) {
            std::vector<std::string> spl_line = split(line);
            for (size_t i = 0; i < spl_line.size(); i++)
            {
                if (spl_line[i] == "PROPERTY") {
                    Variable v = getVariable(spl_line, i);
                    vars.push_back(v);
                    continue;
                }
            }
        }
    }
    file.close();
    std::ofstream output_file(save_to);
    output_file << get_text_for_reflection_file(class_name, vars);
    output_file.close();
}
void create_empty_reflection_file(std::string path) {
    std::string save_to = Path::Path_left(path, 1) + "reflection." + Path::get_file_name_from_path(path) + ".h";
    std::string blank = R"(#pragma once
#define COMPONENT
#define PROPERTY
#define BODY()
)";

    std::ofstream output_file(save_to);
    output_file << blank;
    output_file.close();
}