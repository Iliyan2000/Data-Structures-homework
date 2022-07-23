#include "interface.h"

//some code
void WordsMultiset::add(const std::string& word, size_t times)
{
	if (word == "")
		return;
	size_t new_index = countOf(word) + times;
	if (new_index >= quantity.size())
	{
		quantity.resize(new_index + 1);
		quantity[new_index] = new BST_str();
	}
	removeAll(word);
	quantity[new_index]->insert(word);
}
bool WordsMultiset::contains(const std::string& word) const
{
	for (BST_str* tree : quantity)
	{
		if (tree != nullptr && tree->find(word))
			return true;
	}
	return false;
}
size_t WordsMultiset::countOf(const std::string& word) const
{
	size_t length = quantity.size();
	for (size_t i = 0; i < length; i++)
	{
		if (quantity[i] != nullptr && quantity[i]->find(word))
			return i;
	}
	return 0;
}
size_t WordsMultiset::countOfUniqueWords() const
{
	size_t cnt = 0;
	for (BST_str* tree : quantity)
	{
		if (tree == nullptr)
			continue;
		cnt += tree->getSize();
	}
	return cnt;
}
std::multiset<std::string> WordsMultiset::words() const
{
	std::multiset<std::string> m_set;
	size_t length = quantity.size();
	for (size_t i = 0; i < length; i++)
	{
		if (quantity[i] == nullptr)
			continue;
		for (size_t j = 0; j < i; j++)
		{
			std::vector<std::string> vec = quantity[i]->inorder();
			m_set.insert(vec.begin(), vec.end());
		}
	}
	return m_set;
}
void WordsMultiset::removeAll(const std::string& word)
{
	if (!contains(word))
		return;
	quantity[countOf(word)]->remove(word);
}
void WordsMultiset::remove(const std::string& word, const size_t times)
{
	int cnt = countOf(word) - times;
	removeAll(word);
	if (cnt > 0)
		add(word, cnt);
}
size_t WordsMultiset::countOfAllWords() const
{
	size_t cnt = 0;
	size_t length = quantity.size();
	for (size_t i = 0; i < length; i++)
	{
		if (quantity[i] == nullptr)
			continue;
		cnt += quantity[i]->getSize() * i;
	}
	return cnt;
}

ComparisonReport Comparator::compare(std::istream& a, std::istream& b)
{
	ComparisonReport rep;
	std::string str;

	while (!a.eof())
	{
		a >> str;
		rep.uniqueWords[0].add(str);
	}
	str = "";
	while (!b.eof())
	{
		b >> str;
		if (rep.uniqueWords[0].contains(str))
		{
			rep.uniqueWords[0].remove(str);
			rep.commonWords.add(str);
		}
		else
			rep.uniqueWords[1].add(str);
	}

	return rep;
}