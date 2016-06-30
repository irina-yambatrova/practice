
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <set>
#include <iterator>
#include <string>
//#include "Delete.h"
#include "CObfuscator.h"

using namespace std;


int main()
{
	CObfuscator obfuscator("input.txt");
	obfuscator.DeleteComments();
	obfuscator.DeleteTabAndHyph();
	obfuscator.DeleteSpaces();
	obfuscator.ShowCode();
}

