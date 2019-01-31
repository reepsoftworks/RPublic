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

#include <algorithm>
#include "baseclass.h"
#include "dbg.h"

//-----------------------------------------------------------------------------
// Purpose: Check to see if the class pointer is within our map.
//-----------------------------------------------------------------------------
bool ClassBank::Exists(BaseClass* pClass)
{
	if (std::find(classes.begin(), classes.end(), pClass) != classes.end())
	{
		unsigned long long classid = reinterpret_cast<unsigned long long>(pClass);
		auto iter = class_id.find(classid);
		if (iter != class_id.end())
		{
			return true;
		}
	}

	return false;
}

//-----------------------------------------------------------------------------
// Purpose: Grab the class pointer base on it's ID.
//-----------------------------------------------------------------------------
BaseClass* ClassBank::Find(unsigned long long pID)
{
	auto itr = class_id.find(pID);
	if (itr != class_id.end())
	{
		return itr->second;
	}

	return nullptr;
}

//-----------------------------------------------------------------------------
// Purpose: Add the class pointer to the bank.
//-----------------------------------------------------------------------------
void ClassBank::Add(BaseClass* pClass)
{
	if (pClass != nullptr || pClass != NULL)
	{
		if (Exists(pClass) == false)
		{
			unsigned long long classid = reinterpret_cast<unsigned long long>(pClass);
			pClass->id = classid;

			classes.push_back(pClass);
			class_id[pClass->id] = pClass;

			DMsg("ClassBank: Adding BaseClass with index number %d\n", pClass->id);
		}
	}
}

//-----------------------------------------------------------------------------
// Purpose: Remove the class pointer from the bank.
//-----------------------------------------------------------------------------
void ClassBank::Remove(BaseClass* pClass)
{
	if (Exists(pClass))
	{
		DMsg("ClassBank: Removing BaseClass index number %d\n", pClass->id);

		class_id[pClass->id] = nullptr;
		class_id.erase(pClass->id);
		classes.erase(std::remove(classes.begin(), classes.end(), pClass), classes.end());
	}
}

//-----------------------------------------------------------------------------
// Purpose: Remove the pointer from the bank, and then delete it from memory.
//-----------------------------------------------------------------------------
void ClassBank::Delete(BaseClass* pClass)
{
	if (Exists(pClass))
	{
		auto itr = class_id.find(pClass->id);
		if (itr != class_id.end())
		{
			if (itr->second != nullptr || itr->second != NULL)
			{
				itr->second->CleanUp();
				DMsg("ClassBank: Removing and deleting BaseClass index number %d\n", itr->second->id);
				classes.erase(std::remove(classes.begin(), classes.end(), pClass), classes.end());
				delete itr->second;

				// Cleanup
				itr->second = nullptr;
				class_id[pClass->id] = nullptr;
				class_id.erase(pClass->id);
			}
		}
	}
}

//-----------------------------------------------------------------------------
// Purpose: Clear the bank but do not delete any of the pointers.
//-----------------------------------------------------------------------------
void ClassBank::Empty()
{
	if (classes.size() > 0)
	{
		for (auto p : classes)
		{
			Remove(p);
		}
	}
}

//-----------------------------------------------------------------------------
// Purpose: Clear and delete all class pointers.
//-----------------------------------------------------------------------------
void ClassBank::DeleteAll()
{
	if (classes.size() > 0)
	{
		for (auto p : classes)
		{
			Delete(p);
		}
	}
}