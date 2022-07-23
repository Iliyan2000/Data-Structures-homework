#include <iostream>
#include <fstream>
#include "interface.h"

int main()
{
	std::string file1, file2;
	std::cin >> file1 >> file2;
	Comparator c;
	std::ifstream a(file1.data()), b(file2.data());
	ComparisonReport report = c.compare(a, b);

	size_t cnt_com_w = report.commonWords.countOfAllWords(),
		cnt_f1_w = report.uniqueWords[0].countOfAllWords() + cnt_com_w,
		cnt_f2_w = report.uniqueWords[1].countOfAllWords() + cnt_com_w;
	std::cout << file1 << " contains " << cnt_f1_w << " words and " << cnt_com_w << " of them are common in " << file2 << " (" << (cnt_com_w * 100) / cnt_f1_w << "%)\n";
	std::cout << file2 << " contains " << cnt_f2_w << " words and " << cnt_com_w << " of them are common in " << file1 << " (" << (cnt_com_w * 100) / cnt_f2_w << "%)\n";

	return 0;
}