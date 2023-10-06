testsUser.exe: TestUserRules.o MockUserRepository.o UserRules.o ModelUser.o exceptions.o
	g++ -o $@ $^ -lgtest

testsManager.exe: TestManagerRules.o MockManagerRepository.o MockUserRepository.o MockBankRepository.o MockClientRepository.o ManagerRules.o ModelManager.o ModelClient.o ModelUser.o ModelBank.o exceptions.o
	g++ -o $@ $^ -lgtest

testsClient.exe: TestClientRules.o MockClientRepository.o MockUserRepository.o MockManagerRepository.o ClientRules.o ModelClient.o ModelManager.o ModelUser.o exceptions.o
	g++ -o $@ $^ -lgtest

testsBank.exe: TestBankRules.o MockBankRepository.o BankRules.o ModelBank.o exceptions.o
	g++ -o $@ $^ -lgtest

testsProduct.exe: TestProductRules.o MockProductRepository.o MockBankRepository.o ProductRules.o ModelProduct.o ModelBank.o exceptions.o
	g++ -o $@ $^ -lgtest

testsRequest.exe: TestRequestRules.o MockRequestRepository.o MockClientRepository.o MockUserRepository.o MockManagerRepository.o MockProductRepository.o RequestRules.o ModelRequest.o ModelProduct.o ModelUser.o ModelClient.o ModelManager.o exceptions.o
	g++ -o $@ $^ -lgtest

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

TestUserRules.o: TestUserRules.cpp
	g++ -c -o $@ $<

TestManagerRules.o: TestManagerRules.cpp
	g++ -c -o $@ $<

TestClientRules.o: TestClientRules.cpp
	g++ -c -o $@ $<

TestBankRules.o: TestBankRules.cpp
	g++ -c -o $@ $<

MockUserRepository.o: ../../data_access/MockRepositories/MockUserRepository.cpp
	g++ -c -o $@ $<

MockManagerRepository.o: ../../data_access/MockRepositories/MockManagerRepository.cpp
	g++ -c -o $@ $<

MockRequestRepository.o: ../../data_access/MockRepositories/MockRequestRepository.cpp
	g++ -c -o $@ $<

MockProductRepository.o: ../../data_access/MockRepositories/MockProductRepository.cpp
	g++ -c -o $@ $<

MockClientRepository.o: ../../data_access/MockRepositories/MockClientRepository.cpp
	g++ -c -o $@ $<

MockBankRepository.o: ../../data_access/MockRepositories/MockBankRepository.cpp
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

f.o: f.cpp
	g++ -c -o $@ $<

clean:
	rm -rf *.o *.exe
#./tests.exe --gtest_filter=g