#pragma once
#include "stdafx.h"

class CDelete
{
public:
	CDelete(std::vector<std::string> const& vector1);
	~CDelete()= default;
	void DeleteTabAndHyph();
	void DeleteSpaces();
	
private:
	std::vector<std::string> m_inputText;
};

	


