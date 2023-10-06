#
# Copyright (C) 2023 by Peng
#
# This is free software, licensed under the GNU General Public License v3.
#
#
include $(TOPDIR)/rules.mk

PKG_NAME:=openstick-tweaks-mf32
PKG_VERSION:=v1.0

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
	SECTION:=Utilities
	CATEGORY:=Utilities
	TITLE:=Customized Setting For OpenStick MF32
	DEPENDS:=+opkg +luci
endef

define Build/Configure
endef

define Build/Compile
endef

define Package/$(PKG_NAME)/install 
	$(INSTALL_DIR) $(1)/etc/uci-defaults
	$(INSTALL_BIN) ./files/openstick_tweak_mf32 $(1)/etc/uci-defaults
endef 

$(eval $(call BuildPackage,$(PKG_NAME)))
