#pragma once
#include <iostream>
#include <exception>


using namespace std;

// Базовый класс ошибки
class Error : public std::exception {
public:
	virtual const char* what() const noexcept override {
		return "Ошибка";
	}
	virtual void exit_code() const noexcept {
		cerr << "Ошибка" << endl;
		exit (1);
	}
};

class WrongInputError : public Error {
public:
	const char* what() const noexcept override {
		return "Неправильный config.txt";
	}
	virtual void exit_code() const noexcept {
		cerr << "Неправильный config.txt" << endl;
		exit(2);
	}
};

class LargeInputError : public Error {
public:
	const char* what() const noexcept override {
		return "Слишком длинный конвертер в config.txt";		
	}
	virtual void exit_code() const noexcept {
		cerr << "Слишком длинный конвертер в config.txt" << endl;
		exit(3);
	}
};

class ArgumentsError : public Error {
public:
	const char* what() const noexcept override {
		return "Неправильно заданы аргументы";
	}
	virtual void exit_code() const noexcept {
		cerr << "Неправильно заданы аргументы" << endl;
		exit(4);
	}
};

class FileSearchError : public Error {
public:
	const char* what() const noexcept override {
		return "Не удаётся найти файл";
	}
	virtual void exit_code() const noexcept {
		cerr << "Не удаётся найти файл" << endl;
		exit(5);
	}
};

class WavParsingError : public Error {
public:
	const char* what() const noexcept override {
		return "Ошибка обработки wav файла";
	}
	virtual void exit_code() const noexcept {
		cerr << "Ошибка обработки wav файла" << endl;
		exit(6);
	}
};

