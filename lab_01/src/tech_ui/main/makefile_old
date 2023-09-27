main.exe: main.o App.o Commands.o Printer.o AuthStates.o ManagerGetter.o ManagerPrinter.o ManagersManager.o \
BankManager.o BankPrinter.o RequestGetter.o RequestManager.o RequestPrinter.o ClientGetter.o ClientManager.o \
ClientPrinter.o ProductGetter.o ProductManager.o ProductPrinter.o AuthGetter.o AuthManager.o AuthPrinter.o \
PgBankRepository.o PgUserRepository.o PgClientRepository.o PgManagerRepository.o PgProductRepository.o PgRequestRepository.o \
BankRules.o UserRules.o ClientRules.o ManagerRules.o ProductRules.o RequestRules.o ModelBank.o ModelUser.o ModelClient.o \
ModelRequest.o ModelManager.o ModelProduct.o PostgresCommands.o exceptions.o connection.o
	g++ -o $@ $^ -lpqxx

App.o: App.cpp
	g++ -c -o $@ $<

main.o: main.cpp
	g++ -c -o $@ $<

Commands.o: Commands.cpp
	g++ -c -o $@ $<

Printer.o: Printer.cpp
	g++ -c -o $@ $<

AuthStates.o: AuthStates.cpp
	g++ -c -o $@ $<

ManagerGetter.o: ../managers_manager/ManagerGetter.cpp
	g++ -c -o $@ $<

ManagerPrinter.o: ../managers_manager/ManagerPrinter.cpp
	g++ -c -o $@ $<

ManagersManager.o: ../managers_manager/ManagersManager.cpp
	g++ -c -o $@ $<

ClientGetter.o: ../client_manager/ClientGetter.cpp
	g++ -c -o $@ $<

ClientPrinter.o: ../client_manager/ClientPrinter.cpp
	g++ -c -o $@ $<

ClientManager.o: ../client_manager/ClientManager.cpp
	g++ -c -o $@ $<

ProductGetter.o: ../product_manager/ProductGetter.cpp
	g++ -c -o $@ $<

ProductPrinter.o: ../product_manager/ProductPrinter.cpp
	g++ -c -o $@ $<

ProductManager.o: ../product_manager/ProductManager.cpp
	g++ -c -o $@ $<

AuthGetter.o: ../auth_manager/AuthGetter.cpp
	g++ -c -o $@ $<

AuthPrinter.o: ../auth_manager/AuthPrinter.cpp
	g++ -c -o $@ $<

AuthManager.o: ../auth_manager/AuthManager.cpp
	g++ -c -o $@ $<

RequestGetter.o: ../request_manager/RequestGetter.cpp
	g++ -c -o $@ $<

RequestPrinter.o: ../request_manager/RequestPrinter.cpp
	g++ -c -o $@ $<

RequestManager.o: ../request_manager/RequestManager.cpp
	g++ -c -o $@ $<

BankPrinter.o: ../bank_manager/BankPrinter.cpp
	g++ -c -o $@ $<

BankManager.o: ../bank_manager/BankManager.cpp
	g++ -c -o $@ $<

ModelUser.o: ../../business_logic/models/ModelUser.cpp
	g++ -c -o $@ $<

ModelManager.o: ../../business_logic/models/ModelManager.cpp
	g++ -c -o $@ $<

ModelBank.o: ../../business_logic/models/ModelBank.cpp
	g++ -c -o $@ $<

ModelClient.o: ../../business_logic/models/ModelClient.cpp
	g++ -c -o $@ $<

ModelProduct.o: ../../business_logic/models/ModelProduct.cpp
	g++ -c -o $@ $<

ModelRequest.o: ../../business_logic/models/ModelRequest.cpp
	g++ -c -o $@ $<

PgUserRepository.o: ../../data_access/PostgresRepositories/PgUserRepository.cpp
	g++ -c -o $@ $<

PgClientRepository.o: ../../data_access/PostgresRepositories/PgClientRepository.cpp
	g++ -c -o $@ $<

PgProductRepository.o: ../../data_access/PostgresRepositories/PgProductRepository.cpp
	g++ -c -o $@ $<

PgBankRepository.o: ../../data_access/PostgresRepositories/PgBankRepository.cpp
	g++ -c -o $@ $<

PgManagerRepository.o: ../../data_access/PostgresRepositories/PgManagerRepository.cpp
	g++ -c -o $@ $<

PgRequestRepository.o: ../../data_access/PostgresRepositories/PgRequestRepository.cpp
	g++ -c -o $@ $<

UserRules.o: ../../business_logic/rules/UserRules.cpp
	g++ -c -o $@ $<

ManagerRules.o: ../../business_logic/rules/ManagerRules.cpp
	g++ -c -o $@ $<

ProductRules.o: ../../business_logic/rules/ProductRules.cpp
	g++ -c -o $@ $<

RequestRules.o: ../../business_logic/rules/RequestRules.cpp
	g++ -c -o $@ $<

ClientRules.o: ../../business_logic/rules/ClientRules.cpp
	g++ -c -o $@ $<

BankRules.o: ../../business_logic/rules/BankRules.cpp
	g++ -c -o $@ $<

exceptions.o: ../../business_logic/exceptions/exceptions.cpp
	g++ -c -o $@ $<

connection.o: ../../data_access/connection/connection.cpp
	g++ -c -o $@ $<

PostgresCommands.o: ../../data_access/commands/PostgresCommands.cpp
	g++ -c -o $@ $<

clean:
	rm -rf *.o *.exe