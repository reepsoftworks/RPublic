/*
MIT License

Copyright (c) 2019 Reep Softworks

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef BASECLASS_H
#define BASECLASS_H
#if defined( _WIN32 )
#pragma once
#endif

#include <map>
#include <vector>

//-----------------------------------------------------------------------------
// A base class for all classes. This class can be added to a Bank for easy 
// storing and safe keeping.
//-----------------------------------------------------------------------------
class BaseClass
{
public:
	unsigned long long id;

	BaseClass() {};
	virtual ~BaseClass() {};
	virtual void CleanUp() {};
};

//-----------------------------------------------------------------------------
// A structure to properly manage classes.  
//-----------------------------------------------------------------------------
struct ClassBank
{
	std::vector<BaseClass*> classes;
	std::map<unsigned long long, BaseClass*> class_id;

	void Add(BaseClass* pClass);
	bool Exists(BaseClass* pClass);
	BaseClass* Find(unsigned long long pID);
	void Remove(BaseClass* pClass);
	void Delete(BaseClass* pClass);
	void Empty();
	void DeleteAll();
};

#endif // BASECLASS_H