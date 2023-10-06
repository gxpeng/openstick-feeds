#
# Copyright (C) 2021 gSpot (https://github.com/gSpotx2f/luci-app-cpu-status-mini)
#
# This is free software, licensed under the MIT License.
#

include $(TOPDIR)/rules.mk

PKG_VERSION:=0.1-5
LUCI_TITLE:=CPU utilization info for the LuCI status page
LUCI_DEPENDS:=+luci-mod-admin-full
LUCI_PKGARCH:=all
PKG_LICENSE:=MIT

define Package/luci-app-cpu-status-mini
  SECTION:=luci
  CATEGORY:=LuCI
  SUBMENU:=3. Applications
endef

#include ../../luci.mk
include $(TOPDIR)/feeds/luci/luci.mk

# call BuildPackage - OpenWrt buildroot signature
