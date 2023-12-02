#pragma once
#include <fstream>
#include <string>
#include <thread>

class FileReader {
public:
	static std::string ReadAllText(const std::string& path) {
		std::string output;
		file.open(path);
		std::string line;
		while (getline(file, line)) {
			output += line + '\n';
		}
		file.close();
		return output;
	}

private:
	static inline std::ifstream file{};
};