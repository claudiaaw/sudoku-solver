#pragma once

struct Box {
	int number = 0;
	bool fixed = false;
	int m_possible[9] = { 0 }; // stores possible numbers
};