include <iostream>
#include <fstream>
#include <string>

bool handleLineComment(std::ifstream & in)
{
	char c;
	while (in.get(c))
		if (c == '\n')
			return false;
	return true;
}

bool handleMultilineComment(std::ifstream & in)
{
	char c;
	while (in.get(c))
	{
		if (c == '*')
		{
			if (!in.get(c))
				break;
			if (c == '/')
				return false;
		}
	}
	return true;
}

void flushLine(std::string & line, std::ofstream & out)
{
	static bool prevEmptyLine = false;

	for (size_t i = 0; i < line.length(); ++i)
	{
		if (!isspace(line[i]))
		{

			prevEmptyLine = false;
			out.write(line.c_str(), line.length());
			line = "";
			return;
		}
	}

	if (!prevEmptyLine)
	{

		out.put('\n');
		prevEmptyLine = true;
	}
	line = "";
}

void handleFile(std::string fileName)
{
	std::string line;

	std::ifstream in(fileName.c_str());
	if (!in) return;

	fileName += ".nocomments.cpp";
	std::ofstream out(fileName.c_str());
	if (!out) return;

	char c;
	bool inString = false;
	while (in.get(c))
	{
		if (inString || c != '/')
		{
			line += c;
			if (c == '\n') flushLine(line, out);
			else if (c == '\"') inString = !inString;
			continue;
		}

		if (!in.get(c))
			break;

		bool end = true;
		if (c == '/')
		{
			// обрабатываем однострочный коммент
			end = handleLineComment(in);
			line += '\n';
			flushLine(line, out);
		}
		else if (c == '*')
		{
			// обрабатываем многострочный коммент
			end = handleMultilineComment(in);
			// добавляем пробел вместо многострочного комента
			line += ' ';
		}
		else
		{
			line += '/';
			line += c;
			continue;
		}

		if (end) break;
	}
	flushLine(line, out);

	// закрвывает открытые ранее файлы
	in.close();
	out.close();
}

// ///////////////////////////////////////////////////////////////////////// //
// 
// входная точка программы
//
int main(int argc, char **argv)
{
	handleFile("program.pas");
	return 0;
}