testsUser.exe: TestUserRules.o MockUserRepository.o UserRules.o ModelUser.o exceptions.o
	g++ -o $@ $^ -lgtest

testsUserMock.exe: TestUserRulesMock.o MockUserRepository.o UserRules.o ModelUser.o UserOM.o UserBuilder.o Logger.o exceptions.o
	g++ -o $@ $^ -lgtest -lgmock -pthread
	
testsManager.exe: TestManagerRules.o MockManagerRepository.o MockUserRepository.o MockBankRepository.o MockClientRepository.o ManagerRules.o ModelManager.o ModelClient.o ModelUser.o ModelBank.o Logger.o exceptions.o
	g++ -o $@ $^ -lgtest

testsClient.exe: TestClientRules.o MockClientRepository.o MockUserRepository.o MockManagerRepository.o ClientRules.o ModelClient.o ModelManager.o ModelUser.o Logger.o exceptions.o
	g++ -o $@ $^ -lgtest

testsBank.exe: TestBankRules.o MockBankRepository.o BankStub.o BankRules.o ModelBank.o Logger.o exceptions.o
	g++ -o $@ $^ -lgtest

testsProduct.exe: TestProductRules.o ProductStub.o BankStub.o ProductRules.o ModelProduct.o ModelBank.o MockBankRepository.o MockProductRepository.o Logger.o exceptions.o
	g++ -o $@ $^ -lgtest

testsRequest.exe: TestRequestRules.o MockRequestRepository.o MockClientRepository.o MockUserRepository.o MockManagerRepository.o MockProductRepository.o RequestRules.o ModelRequest.o ModelProduct.o ModelUser.o ModelClient.o ModelManager.o Logger.o exceptions.o
	g++ -o $@ $^ -lgtest

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

TestUserRules.o: TestUserRules.cpp
	g++ -c -o $@ $<
	
TestUserRulesMock.o: TestUserRulesMock.cpp
	g++ -c -o $@ $<
	
TestManagerRules.o: TestManagerRules.cpp
	g++ -c -o $@ $<

TestClientRules.o: TestClientRules.cpp
	g++ -c -o $@ $<

TestBankRules.o: TestBankRules.cpp
	g++ -c -o $@ $<

TestProductRules.o: TestProductRules.cpp
	g++ -c -o $@ $<
	
MockUserRepository.o: ../../src/data_access/MockRepositories/MockUserRepository.cpp
	g++ -c -o $@ $<

MockManagerRepository.o: ../../src/data_access/MockRepositories/MockManagerRepository.cpp
	g++ -c -o $@ $<

MockRequestRepository.o: ../../src/data_access/MockRepositories/MockRequestRepository.cpp
	g++ -c -o $@ $<

MockBankRepository.o: ../../src/data_access/MockRepositories/MockBankRepository.cpp
	g++ -c -o $@ $<

MockProductRepository.o: ../../src/data_access/MockRepositories/MockProductRepository.cpp
	g++ -c -o $@ $<

ProductStub.o: ../stub/ProductStub.cpp
	g++ -c -o $@ $<

MockClientRepository.o: ../../src/data_access/MockRepositories/MockClientRepository.cpp
	g++ -c -o $@ $<

BankStub.o: ../stub/BankStub.cpp
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

Logger.o: ../../src/logger/Logger.cpp
	g++ -c -o $@ $<

%.o: ../../src/business_logic/models/%.cpp
	g++ -c -o $@ $<
	
%.o: ../../src/data_access/MockRepositories/%.cpp
	g++ -c -o $@ $<

%.o: ../../src/business_logic/rules/%.cpp
	g++ -c -o $@ $<
	
%.o: ../builders/%.cpp
	g++ -c -o $@ $<

%.o: ../stub/%.cpp
	g++ -c -o $@ $<
	
f.o: f.cpp
	g++ -c -o $@ $<

clean:
	rm -rf *.o *.exe
#./tests.exe --gtest_filter=g
