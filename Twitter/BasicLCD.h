#pragma once

struct cursorP {

	int x;
	int y;

};


class BasicLCD {
public:
	BasicLCD(void);
	~BasicLCD(void);

	virtual bool lcdInitOK() = 0;
	virtual bool lcdMoveCursorUp() = 0;
	virtual bool lcdMoveCursorDown() = 0;
	virtual bool lcdMoveCursorRight() = 0;
	virtual bool lcdMoveCursorLeft() = 0;
	virtual bool lcdClearToEOL() = 0;
	virtual bool lcdGetError() = 0;
	virtual bool lcdClear() = 0;
	virtual BasicLCD& operator<< (const unsigned char c) = 0;
	virtual BasicLCD& operator<<(const unsigned char* c) = 0;
	virtual bool lcdSetCursorPosition(const cursorP) = 0;

private:
	unsigned int cadd;

};
