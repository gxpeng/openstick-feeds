#
# Copyright (C) 2020 gSpot (https://github.com/gSpotx2f/luci-app-temp-status)
#
# This is free software, licensed under the MIT License.
#

include $(TOPDIR)/rules.mk

PKG_VERSION:=0.3-5
LUCI_TITLE:=Temperature sensors data for the LuCI status page
LUCI_DEPENDS:=+lua +luci-lib-nixio +luci-lib-jsonc
LUCI_PKGARCH:=all
PKG_LICENSE:=MIT

define Package/luci-app-temp-status
  SECTION:=luci
  CATEGORY:=LuCI
  SUBMENU:=3. Applications
endef

#include ../../luci.mk
include $(TOPDIR)/feeds/luci/luci.mk

# call BuildPackage - OpenWrt buildroot signature
