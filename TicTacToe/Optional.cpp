#pragma once

template<class T>
struct Optional
{
	bool is_null = false;
	T value;

	Optional() {}
	Optional(const T& default_value) : value(default_value) {}

	operator bool() const
	{
		return !is_null;
	}

	T& operator()()
	{
		return value;
	}
};