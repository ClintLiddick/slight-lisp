#include <iostream>

#include <slightlisp/parser.hpp>
#include <slightlisp/env.hpp>
#include <slightlisp/eval.hpp>
#include <readline/readline.h>

using namespace slightlisp;

int main(int argc, char** argv)
{
  EnvPtr env = std::make_unique<Env>(global_env());
  char *p;
  while ((p = readline("> ")) != NULL) {
    std::string expr{p};
    try {
    std::cout << eval(parse(tokenize(expr)), env)->to_string() << std::endl;
    } catch (const std::exception& e) {
      std::cout << "ERROR: " << e.what() << std::endl;
    }
    delete[] p;
  }
  std::cout << std::endl;
  return 0;
}
