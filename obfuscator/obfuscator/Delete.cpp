#include "stdafx.h"
#include "Delete.h"

using namespace std;

const set<char> DELIMITER{ '.', ',', ':', ';', '-', '+',  '*',  '/', '=',  '(', ')' };

CDelete::CDelete(std::vector<std::string> const& vector1)
	:m_inputText(vector1)
{
}

void CDelete::DeleteTabAndHyph()
{
	for (string  &str : m_inputText)
	{ 
		if (( str.find('\t') != -1) || (str.find('/n') != -1))
		{
			str = "";
		}

	}
}

void CDelete::DeleteSpaces()
{
	{
		//удалить лиишние пробелы
		for (auto &str : m_inputText)
		{
			for (int i = 0; i < str.length(); i++)
				if (str[i] == ' ' && str[i + 1] == ' ')
				{
					str.erase(i, 1);
					i = (i - 1);
				}
			cout << str << endl;
		}
		//удалить пробелы между разделителями
	}
}