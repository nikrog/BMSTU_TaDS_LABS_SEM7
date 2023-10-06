#ifndef PPO_GUIAPP_H
#define PPO_GUIAPP_H

#include <iostream>
#include <QApplication>
#include "../../business_logic/rules/UserRules.h"
#include "../../business_logic/rules/ClientRules.h"
#include "../../business_logic/rules/BankRules.h"
#include "../../business_logic/rules/ManagerRules.h"
#include "../../business_logic/rules/ProductRules.h"
#include "../../business_logic/rules/RequestRules.h"

#include "../../business_logic/models/ModelUser.h"
#include "../auth_manager/GuiAuthManager.h"
#include "../product_manager/GuiProductManager.h"
#include "../request_manager/GuiRequestManager.h"
#include "../client_manager/GuiClientManager.h"
#include "../bank_manager/GuiBankManager.h"
#include "../managers_manager/GuiManagersManager.h"

#include "../../data_access/PostgresRepositories/PgUserRepository.h"
#include "../../data_access/PostgresRepositories/PgBankRepository.h"
#include "../../data_access/PostgresRepositories/PgManagerRepository.h"
#include "../../data_access/PostgresRepositories/PgClientRepository.h"
#include "../../data_access/PostgresRepositories/PgProductRepository.h"
#include "../../data_access/PostgresRepositories/PgRequestRepository.h"
#include "../../config/ConfigManager.h"
#include "../../business_logic/rules/ILogger.h"
#include "../../logger/Logger.h"

#include "../ui/mainwindow.h"

#endif //PPO_GUIAPP_H
