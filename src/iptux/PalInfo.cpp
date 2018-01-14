#include "PalInfo.h"

#include <glib.h>

namespace iptux {


PalInfo::PalInfo():
  ipv4(0),
  segdes(nullptr),
  version(nullptr), user(NULL), host(NULL),
 name(NULL), group(NULL), photo(NULL), sign(NULL), iconfile(NULL), encode(NULL),
 packetn(0), rpacketn(0),
 compatible(false),
 online(false),
 changed(false)
{
}
PalInfo::~PalInfo()
{
        g_free(segdes);
        g_free(version);
        g_free(user);
        g_free(host);
        g_free(name);
        g_free(group);
        g_free(photo);
        g_free(sign);
        g_free(iconfile);
        g_free(encode);
}

bool PalInfo::isCompatible() const {
  return compatible;
}

bool PalInfo::isOnline() const {
  return online;
}

bool PalInfo::isChanged() const {
  return changed;
}

void PalInfo::setCompatible(bool value) {
  compatible = value;
}

void PalInfo::setOnline(bool value) {
  online = value;
}

void PalInfo::setChanged(bool value) {
  changed = value;
}
}
