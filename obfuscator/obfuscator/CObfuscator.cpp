﻿#include "stdafx.h"
#include "CObfuscator.h"
#include <boost/algorithm/string/split.hpp>
#include <boost/range/algorithm/transform.hpp>
#include <boost/algorithm/string.hpp>
using namespace std;

const set<char> DELIMITER{ '.', ',', ':', ';', '-', '+',  '*',  '/', '=',  '(', ')' };

CObfuscator::CObfuscator(string const& fileName)
{
	ReadInputData(fileName);
}

void CObfuscator::ReadInputData(std::string const & fileName)
{
	ifstream fin(fileName);
	if (fin.is_open())
	{
		string newStr;
		while (getline(fin, newStr))
		{
			m_inputText.push_back(newStr);
		}
	}
	else
	{
		throw invalid_argument("Invalid file name");
	}
}

void CObfuscator::DeleteComments()
{
	for (string & str : m_inputText)
	{
		size_t posOpen = str.find("{");
		size_t posEnd = str.find("}");
		size_t onelinePos = str.find("//");
		if ((posOpen >= 0 && posOpen < str.length()) && (posEnd >= 0 && posEnd < str.length()) && (m_commentState != STATE::MILTILINE)) //íàøëè ìíîãîñòðî÷íûé íå çàêðûòûé êîììåíòàðèé
		{
			str.erase(begin(str) + posOpen, begin(str) + posEnd + 1);
		}
		else if ((posOpen >= 0 && posOpen <= str.length()) && (posEnd < 0 || posEnd >= str.length()) && (m_commentState != STATE::MILTILINE)) //íàøëè ìíîãîñòðî÷íûé íå çàêðûòûé êîììåíòàðèé
		{
			str.erase(begin(str) + posOpen, end(str));
			m_commentState = STATE::MILTILINE;
		}
		else if (m_commentState == STATE::MILTILINE && (posEnd >= 0 && posEnd <= str.length()))
		{
			str.erase(begin(str), begin(str) + posEnd);
			m_commentState = STATE::NOTHING;
		}
		else if ((onelinePos >= 0 && onelinePos < str.length()) && (m_commentState != STATE::MILTILINE))
		{
			str.erase(begin(str) + onelinePos, end(str));
		}
	}
}

void CObfuscator::DeleteTabAndHyph()
{
	for (auto &str : m_inputText)
	{
		
		if (str.find('\t') != -1) 
		{
			str.erase(str.find('\t'), 1);
		}
		
	}	
}

void CObfuscator::DeleteSpaces()
{
	//удалить лиишние пробелы
	for (auto &str : m_inputText)
	{
		for (int i = 0; i < str.length(); i++)
		{
			if (str[i] == ' ' && str[i + 1] == ' ')
			{
				str.erase(i, 1);
				i = (i - 1);
			}
		}
		//cout << str;
		// удалить пробелы между разделителями
	}
}

void CObfuscator::ShowCode() const
{
	for (auto str : m_inputText)
	{
		cout << str << endl;
	}
}
