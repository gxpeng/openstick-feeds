#
# Copyright (C) 2023 by Peng
#
# This is free software, licensed under the GNU General Public License v3.
#
#
include $(TOPDIR)/rules.mk

PKG_NAME:=openstick-operatorswitch
PKG_VERSION:=v1.0

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
	SECTION:=Utilities
	CATEGORY:=Utilities
	TITLE:=switch operator baseband For OpenStick
	DEPENDS:=+modemmanager +gc
endef

define Build/Configure
endef

define Build/Compile
endef

define Package/$(PKG_NAME)/install 
	$(INSTALL_DIR)  $(1)/etc/init.d
	$(INSTALL_BIN)  ./files/operatorswitch_init  $(1)/etc/init.d/operatorswitch
	$(INSTALL_DIR)  $(1)/etc/config
	$(INSTALL_CONF) ./files/operatorswitch_conf  $(1)/etc/config/operatorswitch
	$(INSTALL_DIR)  $(1)/operator
	$(INSTALL_DIR)  $(1)/operator/ChinaMobile
	$(INSTALL_DIR)  $(1)/operator/ChinaUnicom
	$(INSTALL_DIR)  $(1)/operator/ChinaTelecom
endef 

$(eval $(call BuildPackage,$(PKG_NAME)))
