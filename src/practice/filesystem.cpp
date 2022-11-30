# include <meow.h>

# include <filesystem>

int main() {
    std::filesystem::path cwd = std::filesystem::current_path()/"";
    std::cout << cwd.string();
    return 0;
}