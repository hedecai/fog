// [Fog-Core]
//
// [License]
// MIT, See COPYING file in package

// [Precompiled Headers]
#if defined(FOG_PRECOMP)
#include FOG_PRECOMP
#endif // FOG_PRECOMP

// [Dependencies]
#include <Fog/Core/Tools/Strings.h>
#include <Fog/Core/Xml/XmlComment.h>

namespace Fog {

// ============================================================================
// [Fog::XmlComment]
// ============================================================================

XmlComment::XmlComment(const StringW& data) :
  XmlNoText(fog_strings->getString(STR_XML__comment)),
  _data(data)
{
  _type = XML_ELEMENT_COMMENT;
  _flags &= ~(XML_ALLOWED_TAG | XML_ALLOWED_ATTRIBUTES);
}

XmlComment::~XmlComment()
{
}

XmlElement* XmlComment::clone() const
{
  return fog_new XmlComment(_data);
}

const StringW& XmlComment::getData() const
{
  FOG_ASSERT(getType() == XML_ELEMENT_COMMENT);
  return _data;
}

err_t XmlComment::setData(const StringW& data)
{
  FOG_ASSERT(getType() == XML_ELEMENT_COMMENT);
  return _data.set(data);
}

} // Fog namespace