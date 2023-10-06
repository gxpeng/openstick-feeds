#
# Copyright (C) 2020 gSpot (https://github.com/gSpotx2f/luci-app-cpu-status)
#
# This is free software, licensed under the MIT License.
#

include $(TOPDIR)/rules.mk

PKG_VERSION:=0.4-2
LUCI_TITLE:=CPU utilization info for the LuCI status page
LUCI_PKGARCH:=all
PKG_LICENSE:=MIT

define Package/luci-app-cpu-status
  SECTION:=luci
  CATEGORY:=LuCI
  SUBMENU:=3. Applications
endef

#include ../../luci.mk
include $(TOPDIR)/feeds/luci/luci.mk

# call BuildPackage - OpenWrt buildroot signature
