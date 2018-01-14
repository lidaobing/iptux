#ifndef IPTUX_PAL_INFO_H
#define IPTUX_PAL_INFO_H

#include <stdint.h>

#include <netinet/in.h>

namespace iptux {

/**
 * 好友信息.
 * flags位含义: \n
 * 更改(:2);好友的信息被用户手工修改，程序不应再更改好友的信息 \n
 * 在线(:1);好友依旧在线 \n
 * 兼容(:0);完全兼容iptux，程序将采用扩展协议与好友通信 \n
 */
class PalInfo {
public:
        PalInfo();
        ~PalInfo();

        bool isCompatible() const;
        bool isOnline() const;
        bool isChanged() const;

        void setCompatible(bool value);
        void setOnline(bool value);
        void setChanged(bool vallue);

        in_addr_t ipv4; ///< 好友IP
        char *segdes;   ///< 所在网段描述
        char *version;  ///< 版本串 *
        char *user;     ///< 好友用户 *
        char *host;     ///< 好友主机 *
        char *name;     ///< 昵称 *
        char *group;    ///< 所在群组
        char *photo;    ///< 形象照片
        char *sign;     ///< 个性签名
        char *iconfile; ///< 好友头像 *
        char *encode;   ///< 好友编码 *
        uint32_t packetn;       ///< 已接受最大的包编号
        uint32_t rpacketn;      ///< 需要接受检查的包编号
private:
  bool compatible;
  bool online;
  bool changed;
};

}

#endif
