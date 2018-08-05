#pragma once

template<class Con1, class Con2>
void Union(Con1 &a, const Con2 &b)
{
	for (const auto &v : b)
	{
		if (!a.Find(v))
			a << v;
	}
}

template<class Con>
void Merge(const Con &a, const Con &b, Con &c)
{
	c.Clear();
	auto pa = a.begin();
	auto pb = b.begin();
	while (pa != a.end() && pb != b.end())
	{
		if (*pa <= *pb)
		{
			c << *pa;
			++pa;
		}
		else
		{
			c << *pb;
			++pb;
		}
	}
	while (pa != a.end())
	{
		c << *pa;
		++pa;
	}
	while (pb != b.end())
	{
		c << *pb;
		++pb;
	}
}