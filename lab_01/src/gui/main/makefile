R_DIR = ../../business_logic/rules/
M_DIR = ../../business_logic/models/
E_DIR = ../../business_logic/exceptions/
PG_REP_DIR = ../../data_access/PostgresRepositories/
PG_CMD_DIR = ../../data_access/commands/
CONNECT_DIR = ../../data_access/connection/
LOGGER_DIR = ../../logger/
CONFIG_DIR = ../../config/
M_GUIMANAGER_DIR = ../managers_manager/
M_GUICLIENT_DIR = ../client_manager/
M_GUIPRODUCT_DIR = ../product_manager/
M_GUIAUTH_DIR = ../auth_manager/
M_GUIREQUEST_DIR = ../request_manager/
M_GUIBANK_DIR = ../bank_manager/
LIB_DIR = /home/pavela/arper/PPO/ppo/src/tech_ui/main/

app:
	$(MAKE) business_logic
	$(MAKE) data_access_pg
	$(MAKE) tech_ui
	$(MAKE) config
	$(MAKE) logger
	$(MAKE) main.exe
	
	
gui:
	g++ -fPIC -shared $(M_GUIMANAGER_DIR)GuiManagersManager.cpp $(M_GUIBANK_DIR)GuiBankManager.cpp \
	$(M_GUIREQUEST_DIR)GuiRequestManager.cpp $(M_GUICLIENT_DIR)GuiClientManager.cpp $(M_GUIPRODUCT_DIR)GuiProductManager.cpp \
	$(M_GUIAUTH_DIR)GuiAuthManager.cpp -o libgui.so

business_logic:
	g++ -fPIC -shared $(R_DIR)BankRules.cpp $(R_DIR)UserRules.cpp $(R_DIR)ClientRules.cpp $(R_DIR)ManagerRules.cpp $(R_DIR)ProductRules.cpp \
	$(R_DIR)RequestRules.cpp $(M_DIR)ModelBank.cpp $(M_DIR)ModelUser.cpp $(M_DIR)ModelClient.cpp $(M_DIR)ModelRequest.cpp $(M_DIR)ModelManager.cpp \
	$(M_DIR)ModelProduct.cpp $(E_DIR)exceptions.cpp -o libbl.so
	sudo rm /usr/lib/libbl.so
	sudo cp libbl.so /usr/lib/

data_access_pg:
	g++ -fPIC -shared $(PG_REP_DIR)PgBankRepository.cpp $(PG_REP_DIR)PgUserRepository.cpp $(PG_REP_DIR)PgClientRepository.cpp \
	$(PG_REP_DIR)PgManagerRepository.cpp $(PG_REP_DIR)PgProductRepository.cpp $(PG_REP_DIR)PgRequestRepository.cpp \
	$(PG_CMD_DIR)PostgresCommands.cpp $(CONNECT_DIR)connection.cpp -o libpg_da.so
	sudo rm /usr/lib/libpg_da.so
	sudo cp libpg_da.so /usr/lib/

tech_ui:
	g++ -fPIC -shared App.cpp Commands.cpp Printer.cpp AuthStates.cpp $(M_MANAGER_DIR)ManagerGetter.cpp \
	$(M_MANAGER_DIR)ManagerPrinter.cpp $(M_MANAGER_DIR)ManagersManager.cpp $(M_BANK_DIR)BankManager.cpp \
	$(M_BANK_DIR)BankPrinter.cpp $(M_REQUEST_DIR)RequestGetter.cpp $(M_REQUEST_DIR)RequestManager.cpp \
	$(M_REQUEST_DIR)RequestPrinter.cpp $(M_CLIENT_DIR)ClientGetter.cpp $(M_CLIENT_DIR)ClientManager.cpp \
	$(M_CLIENT_DIR)ClientPrinter.cpp $(M_PRODUCT_DIR)ProductGetter.cpp $(M_PRODUCT_DIR)ProductManager.cpp \
	$(M_PRODUCT_DIR)ProductPrinter.cpp $(M_AUTH_DIR)AuthGetter.cpp $(M_AUTH_DIR)AuthManager.cpp \
	$(M_AUTH_DIR)AuthPrinter.cpp -o libtech_ui.so
	sudo rm /usr/lib/libtech_ui.so
	sudo cp libtech_ui.so /usr/lib/


logger:
	g++ -fPIC -shared $(LOGGER_DIR)Logger.cpp -o liblogger.so
	sudo rm /usr/lib/liblogger.so
	sudo cp liblogger.so /usr/lib/

config:
	g++ -fPIC -shared $(CONFIG_DIR)ConfigManager.cpp -o libconfig.so
	sudo rm /usr/lib/libconfig.so
	sudo cp libconfig.so /usr/lib/

main.o: main.cpp
	g++ -c -o $@ $<


main.exe: main.o
	g++ -o $@ $^ -lpqxx -L$(LIB_DIR) -llogger -ltech_ui -lbl -lpg_da -lconfig

clean:
	rm -rf *.o *.exe *.so
