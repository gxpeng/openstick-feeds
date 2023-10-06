#
# Copyright (C) 2023 by Peng
#
# This is free software, licensed under the GNU General Public License v3.
#
#
include $(TOPDIR)/rules.mk

PKG_NAME:=openstick-ledmonitor-mf32
PKG_VERSION:=v1.0

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
	SECTION:=Utilities
	CATEGORY:=Utilities
	TITLE:=LED monitor For OpenStick MF32(4 battery leds)
	DEPENDS:=+modemmanager
endef

define Build/Configure
endef

define Build/Compile
endef

define Package/$(PKG_NAME)/preinst 
	rm -f $(1)/etc/rc.button/power
endef 

define Package/$(PKG_NAME)/install 
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/ledmonitor_init $(1)/etc/init.d/ledmonitor
	$(INSTALL_BIN) ./files/ledinit_init $(1)/etc/init.d/ledinit
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_CONF) ./files/ledmonitor_conf $(1)/etc/config/ledmonitor
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) ./files/ledmonitor_bin $(1)/usr/bin/ledmonitor
	$(INSTALL_DIR) $(1)/tmp
	$(INSTALL_BIN) ./files/power $(1)/tmp/power
	$(INSTALL_DIR) $(1)/etc/uci-defaults
	$(INSTALL_BIN) ./files/ledmonitor_uci $(1)/etc/uci-defaults/ledmonitor
endef 


$(eval $(call BuildPackage,$(PKG_NAME)))
