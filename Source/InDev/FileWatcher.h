#pragma once
#include <thread>
#include <functional>
#include <filesystem>


struct File {
	File(const std::string& path_to_file) {
		this->path_to_file = path_to_file;
	}

	std::string path_to_file{ };
	std::filesystem::file_time_type last_time{};
};

class FileWatcher
{
public:
	static void Start() {
		thr = new std::thread(MainThread, &threadIsActive, &updateIsBind, &files);
	}
	static bool addFile(const std::string& _path) {
		if (_path.empty()) {
			printf_s("ERROR >> path is empty\n");
			return false;
		}
		if (!std::filesystem::exists(_path)) {
			printf_s("ERROR >> file %s not exist\n", _path.c_str());
			return false;
		}
		for (const auto& u : files) {
			if (u.path_to_file == _path) {
				printf_s("ERROR >> already open\n");
				return false;
			}
		}
		
		File f(_path);
		f.last_time = std::filesystem::last_write_time(_path);
		files.push_back(f);
		return true;
	}
	template<class T, class D> static void onUpdate(T&& func, D&& clas) {
		update = std::bind(func);
		updateIsBind = true;
	}
	static void onUpdate(void (func)(File*)) {
		update = func;
		updateIsBind = true;
	}
	static size_t size() {
		return files.size();
	}
	static void Close() {
		printf_s("Closing...\r");
		threadIsActive = false;
		thr->join();
		delete thr;
		printf_s("Close");
	}

private:
	static inline std::thread* thr;
	static inline bool threadIsActive{ true };
	static inline bool updateIsBind{ false };
	static inline std::vector<File> files;
	static inline std::function<void(File* file)> update;


	static void MainThread(const bool* stat, const bool* updisbind, std::vector<File>* files2) {
		while (*stat) {
			for (auto& i : *files2)
			{
				try {
					auto time = std::filesystem::last_write_time(i.path_to_file);
					if (i.last_time != time) {
						i.last_time = time;
						if (*updisbind) update(&i);
					}
				}
				catch (std::exception) {}
			}
		}
	}
};


