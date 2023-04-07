#include <iostream>
#include <string>
#include <fstream>

void run(const std::string& source) {
  
}

void run_prompt() {

}

void run_file(const char* filename) {
  std::ifstream in_file {filename, std::ios_base::in};
  if (!in_file) {
    std::cerr << "Failed to read file " <<
        filename << std::endl;
      std::exit(74);
  }
  std::string file_content {
      std::istreambuf_iterator<char> {in_file},
      std::istreambuf_iterator<char> {}
  };
  run(file_content);
}

int main(int argc, char* argv[]) {
  if (argc == 1) {
    run_prompt();
  } else if (argc == 2) {
    run_file(argv[1]);
  } else {
    // TODO: Script arguments
    run_file(argv[1]);
  }
  return 0;
}
