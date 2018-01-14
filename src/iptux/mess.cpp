//
// C++ Implementation: mess
//
// Description:
//
//
// Author: Jally <jallyx@163.com>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "mess.h"

#include "iptux/utils.h"

namespace iptux {

GroupInfo::GroupInfo():grpid(0), type(GROUP_BELONG_TYPE_REGULAR), name(NULL),
 member(NULL), buffer(NULL), dialog(NULL)
{}
GroupInfo::~GroupInfo()
{
        g_free(name);
        g_slist_free(member);
        g_object_unref(buffer);
}

FileInfo::FileInfo():fileid(0), packetn(0), fileattr(0), filesize(-1),
    finishedsize(0),fileown(NULL), filepath(NULL)
{}
FileInfo::~FileInfo()
{
        g_free(filepath);
}

MsgPara::MsgPara():pal(NULL), stype(MESSAGE_SOURCE_TYPE_PAL),
 btype(GROUP_BELONG_TYPE_REGULAR), dtlist(NULL)
{}
MsgPara::~MsgPara()
{
        for (GSList *tlist = dtlist; tlist; tlist = g_slist_next(tlist))
                delete (ChipData *)tlist->data;
        g_slist_free(dtlist);
}

ChipData::ChipData():type(MESSAGE_CONTENT_TYPE_STRING), data(NULL)
{}
ChipData::~ChipData()
{
        g_free(data);
}

NetSegment::NetSegment():startip(NULL), endip(NULL), description(NULL)
{}
NetSegment::~NetSegment()
{
        g_free(startip);
        g_free(endip);
        g_free(description);
}

Json::Value NetSegment::ToJsonValue() const {
  Json::Value value;
  value["startip"] = startip;
  value["endip"] = endip;
  value["description"] = description;
  return value;
}

//static
NetSegment* NetSegment::NewFromJsonValue(const Json::Value& value) {
  NetSegment* res = new NetSegment();
  res->startip = g_strdup(value["startip"].asString().c_str());
  res->endip = g_strdup(value["startip"].asString().c_str());
  res->description = g_strdup(value["startip"].asString().c_str());
  return res;
}

SessionAbstract::SessionAbstract()
{}
SessionAbstract::~SessionAbstract()
{}

TransAbstract::TransAbstract()
{}
TransAbstract::~TransAbstract()
{}

}
