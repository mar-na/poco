//
// ParseHandler.h
//
// $Id$
//
// Library: JSON
// Package: JSON
// Module:  ParseHandler
//
// Definition of the ParseHandler class.
//
// Copyright (c) 2012, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef JSON_ParseHandler_INCLUDED
#define JSON_ParseHandler_INCLUDED


#include "Poco/JSON/Handler.h"
#include <stack>


namespace Poco {
namespace JSON {


class JSON_API ParseHandler : public Handler
	/// Provides a default handler for the JSON parser.
	/// This handler will build up an object or array based
	/// on the handlers called by the parser.
{
public:
	ParseHandler(bool preserveObjectOrder = false);
		/// Creates the ParseHandler.

	virtual ~ParseHandler();
		/// Destroys the ParseHandler.

	void startObject();
		/// Handles a '{'; a new object is started.

	void endObject();
		/// Handles a '}'; the object is closed.

	void startArray();
		/// Handles a '['; a new array is started.

	void endArray();
		/// Handles a ']'; the array is closed.

	void key(const std::string& k);
		/// A key is read

	Dynamic::Var result() const;
		/// Returns the result of the parser (an object or an array).

	virtual void value(int v);
		/// An integer value is read

	virtual void value(unsigned v);
		/// An unsigned value is read. This will only be triggered if the
		/// value cannot fit into a signed int.

#if defined(POCO_HAVE_INT64)
	virtual void value(Int64 v);
		/// A 64-bit integer value is read

	virtual void value(UInt64 v);
		/// An unsigned 64-bit integer value is read. This will only be
		/// triggered if the value cannot fit into a signed 64-bit integer.
#endif

	virtual void value(const std::string& s);
		/// A string value is read.

	virtual void value(double d);
		/// A double value is read.

	virtual void value(bool b);
		/// A boolean value is read.

	virtual void null();
		/// A null value is read.

private:
	void setValue(const Poco::Dynamic::Var& value);
	typedef std::stack<Dynamic::Var> Stack;

	Stack        _stack;
	std::string  _key;
	Dynamic::Var _result;
	bool         _preserveObjectOrder;
};


inline Dynamic::Var ParseHandler::result() const
{
	return _result;
}


inline void ParseHandler::value(int v)
{
	setValue(v);
}


inline void ParseHandler::value(unsigned v)
{
	setValue(v);
}


#if defined(POCO_HAVE_INT64)
inline void ParseHandler::value(Int64 v)
{
	setValue(v);
}


inline void ParseHandler::value(UInt64 v)
{
	setValue(v);
}
#endif


inline void ParseHandler::value(const std::string& s)
{
	setValue(s);
}


inline void ParseHandler::value(double d)
{
	setValue(d);
}


inline void ParseHandler::value(bool b)
{
	setValue(b);
}


inline void ParseHandler::null()
{
	Poco::Dynamic::Var empty;
	setValue(empty);
}


}} // namespace Poco::JSON


#endif // JSON_ParseHandler_INCLUDED
