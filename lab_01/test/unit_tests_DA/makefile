testsUserRepo.exe: TestUserRepo.o PgUserRepository.o ModelUser.o ModelBank.o ModelProduct.o ModelRequest.o ModelManager.o ModelClient.o connection.o PostgresCommands.o exceptions.o
	g++ -o $@ $^ -lgtest -lpqxx

testsUserRepo2.exe: TestUserRepo.o PgUserRepository.o ModelUser.o ModelBank.o ModelProduct.o ModelRequest.o ModelManager.o ModelClient.o connection.o PostgresCommands.o exceptions.o
	g++ -o $@ $^ -lgtest -lpqxx
	
testsBankRepo.exe: TestBankRepo.o PgBankRepository.o BankRules.o ModelUser.o ModelBank.o ModelProduct.o ModelRequest.o ModelManager.o ModelClient.o connection.o PostgresCommands.o exceptions.o
	g++ -o $@ $^ -lgtest -lpqxx

testsBankRepo2.exe: TestBankRepo.o PgBankRepository.o BankRules.o ModelUser.o ModelBank.o ModelProduct.o ModelRequest.o ModelManager.o ModelClient.o connection.o PostgresCommands.o exceptions.o
	g++ -o $@ $^ -lgtest -lpqxx
	
testsManagerRepo.exe: TestManagerRepo.o PgManagerRepository.o PgUserRepository.o PgBankRepository.o PgClientRepository.o ManagerRules.o ModelUser.o ModelBank.o ModelProduct.o ModelRequest.o ModelManager.o ModelClient.o connection.o PostgresCommands.o exceptions.o
	g++ -o $@ $^ -lgtest -lpqxx

testsManagerRepo2.exe: TestManagerRepo.o PgManagerRepository.o PgUserRepository.o PgBankRepository.o PgClientRepository.o ManagerRules.o ModelUser.o ModelBank.o ModelProduct.o ModelRequest.o ModelManager.o ModelClient.o connection.o PostgresCommands.o exceptions.o
	g++ -o $@ $^ -lgtest -lpqxx
	
testsClientRepo.exe: TestClientRepo.o PgClientRepository.o PgUserRepository.o PgManagerRepository.o ClientRules.o ModelUser.o ModelBank.o ModelProduct.o ModelRequest.o ModelManager.o ModelClient.o connection.o PostgresCommands.o exceptions.o
	g++ -o $@ $^ -lgtest -lpqxx

testsClientRepo2.exe: TestClientRepo.o PgClientRepository.o PgUserRepository.o PgManagerRepository.o ClientRules.o ModelUser.o ModelBank.o ModelProduct.o ModelRequest.o ModelManager.o ModelClient.o connection.o PostgresCommands.o exceptions.o
	g++ -o $@ $^ -lgtest -lpqxx

testsProductRepo.exe: TestProductRepo.o PgProductRepository.o PgBankRepository.o ProductRules.o ModelUser.o ModelBank.o ModelProduct.o ModelRequest.o ModelManager.o ModelClient.o connection.o PostgresCommands.o exceptions.o
	g++ -o $@ $^ -lgtest -lpqxx

testsProductRepo2.exe: TestProductRepo.o PgProductRepository.o PgBankRepository.o ProductRules.o ModelUser.o ModelBank.o ModelProduct.o ModelRequest.o ModelManager.o ModelClient.o connection.o PostgresCommands.o exceptions.o
	g++ -o $@ $^ -lgtest -lpqxx
	
testsRequestRepo.exe: TestRequestRepo.o PgRequestRepository.o PgUserRepository.o PgManagerRepository.o PgProductRepository.o PgClientRepository.o RequestRules.o ModelUser.o ModelBank.o ModelProduct.o ModelRequest.o ModelManager.o ModelClient.o connection.o PostgresCommands.o exceptions.o
	g++ -o $@ $^ -lgtest -lpqxx
	
testsRequestRepo2.exe: TestRequestRepo.o PgRequestRepository.o PgUserRepository.o PgManagerRepository.o PgProductRepository.o PgClientRepository.o RequestRules.o ModelUser.o ModelBank.o ModelProduct.o ModelRequest.o ModelManager.o ModelClient.o connection.o PostgresCommands.o exceptions.o
	g++ -o $@ $^ -lgtest -lpqxx

ModelUser.o: ../../src/business_logic/models/ModelUser.cpp
	g++ -c -o $@ $<

ModelManager.o: ../../src/business_logic/models/ModelManager.cpp
	g++ -c -o $@ $<

ModelBank.o: ../../src/business_logic/models/ModelBank.cpp
	g++ -c -o $@ $<

ModelClient.o: ../../src/business_logic/models/ModelClient.cpp
	g++ -c -o $@ $<

ModelProduct.o: ../../src/business_logic/models/ModelProduct.cpp
	g++ -c -o $@ $<

ModelRequest.o: ../../src/business_logic/models/ModelRequest.cpp
	g++ -c -o $@ $<

TestUserRepo.o: TestUserRepo.cpp
	g++ -c -o $@ $<

TestManagerRepo.o: TestManagerRepo.cpp
	g++ -c -o $@ $<

TestClientRepo.o: TestClientRepo.cpp
	g++ -c -o $@ $<

TestBankRepo.o: TestBankRepo.cpp
	g++ -c -o $@ $<

TestProductRepo.o: TestProductRepo.cpp
	g++ -c -o $@ $<

TestRequestRepo.o: TestRequestRepo.cpp
	g++ -c -o $@ $<

PgUserRepository.o: ../../src/data_access/PostgresRepositories/PgUserRepository.cpp
	g++ -c -o $@ $<

PgClientRepository.o: ../../src/data_access/PostgresRepositories/PgClientRepository.cpp
	g++ -c -o $@ $<

PgProductRepository.o: ../../src/data_access/PostgresRepositories/PgProductRepository.cpp
	g++ -c -o $@ $<

PgBankRepository.o: ../../src/data_access/PostgresRepositories/PgBankRepository.cpp
	g++ -c -o $@ $<

PgManagerRepository.o: ../../src/data_access/PostgresRepositories/PgManagerRepository.cpp
	g++ -c -o $@ $<

PgRequestRepository.o: ../../src/data_access/PostgresRepositories/PgRequestRepository.cpp
	g++ -c -o $@ $<
	
UserRules.o: ../../src/business_logic/rules/UserRules.cpp
	g++ -c -o $@ $<

ManagerRules.o: ../../src/business_logic/rules/ManagerRules.cpp
	g++ -c -o $@ $<

ProductRules.o: ../../src/business_logic/rules/ProductRules.cpp
	g++ -c -o $@ $<

RequestRules.o: ../../src/business_logic/rules/RequestRules.cpp
	g++ -c -o $@ $<

ClientRules.o: ../../src/business_logic/rules/ClientRules.cpp
	g++ -c -o $@ $<

BankRules.o: ../../src/business_logic/rules/BankRules.cpp
	g++ -c -o $@ $<

exceptions.o: ../../src/business_logic/exceptions/exceptions.cpp
	g++ -c -o $@ $<

connection.o: ../../src/data_access/connection/connection.cpp
	g++ -c -o $@ $<

PostgresCommands.o: ../../src/data_access/commands/PostgresCommands.cpp
	g++ -c -o $@ $<

f.o: f.cpp
	g++ -c -o $@ $<

clean:
	rm -rf *.o *.exe
#./tests.exe --gtest_filter=g
