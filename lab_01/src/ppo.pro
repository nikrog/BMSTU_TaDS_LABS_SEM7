QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS += -lpqxx

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gui/main/GuiApp.cpp \
    gui/ui/addbankwindow.cpp \
    gui/ui/addproductwindow.cpp \
    gui/ui/adminwindow.cpp \
    gui/ui/changepasswordwindow.cpp \
    gui/ui/clientwindow.cpp \
    gui/ui/mainwindow.cpp \
    gui/managers_manager/GuiManagersManager.cpp \
    gui/client_manager/GuiClientManager.cpp \
    gui/product_manager/GuiProductManager.cpp \
    gui/request_manager/GuiRequestManager.cpp \
    gui/bank_manager/GuiBankManager.cpp \
    gui/auth_manager/GuiAuthManager.cpp \
    business_logic/rules/UserRules.cpp \
    business_logic/rules/ClientRules.cpp \
    business_logic/rules/BankRules.cpp \
    business_logic/rules/ProductRules.cpp \
    business_logic/rules/RequestRules.cpp \
    business_logic/rules/ManagerRules.cpp \
    business_logic/exceptions/exceptions.cpp \
    business_logic/models/ModelUser.cpp \
    business_logic/models/ModelBank.cpp \
    business_logic/models/ModelClient.cpp \
    business_logic/models/ModelManager.cpp \
    business_logic/models/ModelProduct.cpp \
    business_logic/models/ModelRequest.cpp \
    business_logic/models/errors.cpp \
    config/ConfigManager.cpp \
    gui/ui/makerequestwindow.cpp \
    gui/ui/managerupdateclientwindow.cpp \
    gui/ui/managerwindow.cpp \
    gui/ui/rateproductwindow.cpp \
    gui/ui/registerclient2window.cpp \
    gui/ui/registerclientwindow.cpp \
    gui/ui/updatebankwindow.cpp \
    gui/ui/updateclientwindow.cpp \
    gui/ui/updateproductwindow.cpp \
    gui/ui/userwindow.cpp \
    logger/Logger.cpp \
    data_access/connection/connection.cpp \
    data_access/commands/PostgresCommands.cpp \
    data_access/PostgresRepositories/PgBankRepository.cpp \
    data_access/PostgresRepositories/PgClientRepository.cpp \
    data_access/PostgresRepositories/PgManagerRepository.cpp \
    data_access/PostgresRepositories/PgUserRepository.cpp \
    data_access/PostgresRepositories/PgProductRepository.cpp \
    data_access/PostgresRepositories/PgRequestRepository.cpp


HEADERS += \
    gui/ui/addbankwindow.h \
    gui/ui/addproductwindow.h \
    gui/ui/adminwindow.h \
    gui/ui/changepasswordwindow.h \
    gui/ui/clientwindow.h \
    gui/ui/mainwindow.h \
    gui/main/GuiApp.h \
    gui/managers_manager/GuiManagersManager.h \
    gui/client_manager/GuiClientManager.h \
    gui/product_manager/GuiProductManager.h \
    gui/request_manager/GuiRequestManager.h \
    gui/bank_manager/GuiBankManager.h \
    gui/auth_manager/GuiAuthManager.h \
    business_logic/rules/UserRules.h \
    business_logic/rules/BankRules.h \
    business_logic/rules/ManagerRules.h \
    business_logic/rules/ClientRules.h \
    business_logic/rules/ProductRules.h \
    business_logic/rules/RequestRules.h \
    business_logic/rules/ILogger.h \
    business_logic/IRepositories/CRUDRepository.h \
    business_logic/IRepositories/IBankRepository.h \
    business_logic/IRepositories/IClientRepository.h \
    business_logic/IRepositories/IManagerRepository.h \
    business_logic/IRepositories/IProductRepository.h \
    business_logic/IRepositories/IRequestRepository.h \
    business_logic/IRepositories/IUserRepository.h \
    business_logic/exceptions/exceptions.h \
    business_logic/models/ModelUser.h \
    business_logic/models/ModelBank.h \
    business_logic/models/ModelClient.h \
    business_logic/models/ModelManager.h \
    business_logic/models/ModelProduct.h \
    business_logic/models/ModelRequest.h \
    business_logic/models/errors.h \
    business_logic/models/constants.h \
    config/ConfigManager.h \
    gui/ui/makerequestwindow.h \
    gui/ui/managerupdateclientwindow.h \
    gui/ui/managerwindow.h \
    gui/ui/rateproductwindow.h \
    gui/ui/registerclient2window.h \
    gui/ui/registerclientwindow.h \
    gui/ui/updatebankwindow.h \
    gui/ui/updateclientwindow.h \
    gui/ui/updateproductwindow.h \
    gui/ui/userwindow.h \
    logger/Logger.h \
    data_access/connection/connection.h \
    data_access/commands/PostgresCommands.h \
    data_access/PostgresRepositories/PgBankRepository.h \
    data_access/PostgresRepositories/PgClientRepository.h \
    data_access/PostgresRepositories/PgManagerRepository.h \
    data_access/PostgresRepositories/PgUserRepository.h \
    data_access/PostgresRepositories/PgProductRepository.h \
    data_access/PostgresRepositories/PgRequestRepository.h \
    config.txt


FORMS += \
    gui/ui/addbankwindow.ui \
    gui/ui/addproductwindow.ui \
    gui/ui/adminwindow.ui \
    gui/ui/changepasswordwindow.ui \
    gui/ui/clientwindow.ui \
    gui/ui/mainwindow.ui \
    gui/ui/makerequestwindow.ui \
    gui/ui/managerupdateclientwindow.ui \
    gui/ui/managerwindow.ui \
    gui/ui/rateproductwindow.ui \
    gui/ui/registerclient2window.ui \
    gui/ui/registerclientwindow.ui \
    gui/ui/updatebankwindow.ui \
    gui/ui/updateclientwindow.ui \
    gui/ui/updateproductwindow.ui \
    gui/ui/userwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
