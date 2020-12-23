cmake_minimum_required(VERSION 3.13)
project(cedu)

set(CMAKE_CXX_STANDARD 14)

add_executable(cedu main.c lexer.c lexer.h parser.c parser.h interpretator.c interpretator.h run.c run.h)