#
# Copyright (C) 2023 by Peng
#
# This is free software, licensed under the GNU General Public License v3.
#
#
include $(TOPDIR)/rules.mk

PKG_NAME:=openstick-4gmonitor
PKG_VERSION:=v1.0

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
	SECTION:=Utilities
	CATEGORY:=Utilities
	TITLE:=check and restore 4G network For OpenStick
	DEPENDS:=+modemmanager
endef

define Build/Configure
endef

define Build/Compile
endef

define Package/$(PKG_NAME)/install 
	$(INSTALL_DIR)  $(1)/etc/init.d
	$(INSTALL_BIN)  ./files/4gmonitor_init  $(1)/etc/init.d/4gmonitor
	$(INSTALL_DIR)  $(1)/etc/config
	$(INSTALL_CONF) ./files/4gmonitor_conf  $(1)/etc/config/4gmonitor
endef 

$(eval $(call BuildPackage,$(PKG_NAME)))
