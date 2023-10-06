#include <gtest/gtest.h>

#include "../../src/data_access/PostgresRepositories/PgBankRepository.h"
#include "../../src/business_logic/rules/BankRules.h"
#include "../../src/business_logic/models/ModelBank.h"

void load_data(ConnectionParams params)
{   
    std::string connect_str = params.getString();
    std::shared_ptr<pqxx::connection> connection = std::make_shared<pqxx::connection>(connect_str.c_str());

    if (connection->is_open())
    {
        //std::string sql = PostgreSQLGetUserID().get_str(login);
        pqxx::work curConnect(*connection);
        curConnect.exec("TRUNCATE TABLE BA.requests RESTART IDENTITY CASCADE;");
        curConnect.exec("TRUNCATE TABLE BA.products RESTART IDENTITY CASCADE;");
        curConnect.exec("TRUNCATE TABLE BA.clients RESTART IDENTITY CASCADE;");
        curConnect.exec("TRUNCATE TABLE BA.managers RESTART IDENTITY CASCADE;");
        curConnect.exec("TRUNCATE TABLE BA.banks RESTART IDENTITY CASCADE;");
        curConnect.exec("TRUNCATE TABLE BA.users RESTART IDENTITY CASCADE;");
        curConnect.exec("INSERT INTO BA.banks (name, license_num, address, email, phone, website) VALUES " \
        "('Альфа банк', 1234, 'Москва', 'alphabank@alpha.ru', '+74953459872', 'alphabank.ru')");
        curConnect.exec("INSERT INTO BA.banks (name, license_num, address, email, phone, website) VALUES " \
        "('Райфайзен банк', 1235, 'Москва', 'raifaizen@raif.ru', '+74953459873', 'raiffaizen.ru');");
        curConnect.exec("INSERT INTO BA.banks (name, license_num, address, email, phone, website) VALUES " \
        "('Россельхоз банк', 6667, 'Москва', 'rosselhoz@rsb.ru', '+74953479973', 'rosselhoz.ru');");
        curConnect.exec("INSERT INTO BA.banks (name, license_num, address, email, phone, website) VALUES " \
        "('ПСБ', 345669, 'Москва', 'promsvyaz@psb.ru', '+74953473673', 'psb.ru')");
        curConnect.exec("INSERT INTO BA.banks (name, license_num, address, email, phone, website) VALUES " \
        "('Локо-банк', 345669, 'Москва', 'locko@bank.ru', '+74953473689', 'lockobank.ru')");
        curConnect.exec("INSERT INTO BA.banks (name, license_num, address, email, phone, website) VALUES " \
        "('ВТБ', 7654, 'Москва', 'vtb@bank.ru', '+74953476589', 'vtb.ru')");
        curConnect.exec("INSERT INTO BA.banks (name, license_num, address, email, phone, website) VALUES " \
        "('Сбербанк', 4556, 'Москва', 'sberbank@sber.ru', '+74953473633', 'sberbank.ru')");
        curConnect.exec("INSERT INTO BA.banks (name, license_num, address, email, phone, website) VALUES " \
        "('Тинькофф', 546463, 'Москва', 'tinkoff@tink.ru', '+74924473689', 'tinkoff.ru')");
        curConnect.commit();
    }
}

struct TestPgBankRepo : public testing::Test {
    ConnectionParams *connectParams;

    void SetUp() 
    {
        connectParams = new ConnectionParams("postgres", "localhost", "postgres", "admin", 5435);
        load_data(*connectParams);
    }
    void TearDown() 
    { 
        delete connectParams;
    }
};

TEST_F(TestPgBankRepo, TestGetBankByID)
{
    PgBankRepository rep = PgBankRepository(connectParams);

    Bank tmpBank = rep.getBankByID(6);

    EXPECT_EQ(tmpBank.getID(), 6);
    EXPECT_EQ(tmpBank.getLicenseNum(), 7654);
    EXPECT_EQ(tmpBank.getName(), "ВТБ");
}

TEST_F(TestPgBankRepo, TestGetBankByName)
{
    PgBankRepository rep = PgBankRepository(connectParams);

    Bank tmpBank = rep.getBankByName("ВТБ");

    EXPECT_EQ(tmpBank.getID(), 6);
    EXPECT_EQ(tmpBank.getLicenseNum(), 7654);
    EXPECT_EQ(tmpBank.getName(), "ВТБ");
}

TEST_F(TestPgBankRepo, TestGetAllBanks)
{
    PgBankRepository rep = PgBankRepository(*connectParams);
    std::vector<Bank> banks = std::vector<Bank>();

    banks = rep.getAllBanks();

    EXPECT_EQ(banks.size(), 8);
}

TEST_F(TestPgBankRepo, TestAddBank)
{
    PgBankRepository rep = PgBankRepository(*connectParams);

    int id = rep.addBank({.name="Alfa", .license_num=1236, .address="Street 54",
     .email="alfa@alfa.ru", .phone="+749567890999", .website="alfa.ru"});

    Bank tmpBank = rep.getBankByID(id);
    EXPECT_EQ(tmpBank.getID(), id);
    EXPECT_EQ(tmpBank.getLicenseNum(), 1236);
    EXPECT_EQ(tmpBank.getName(), "Alfa");
}

TEST_F(TestPgBankRepo, TestUpdateBank)
{
    PgBankRepository rep = PgBankRepository(*connectParams);
    Bank tmpBank = Bank(8, "Тинькофф", 546463, "Москва", "tinkoff@tink.ru", "+74924473689", "tinkoff.ru");
    tmpBank.setAddress("Street 90");

    rep.updateEl(tmpBank);

    EXPECT_EQ(rep.getBankByID(8).getAddress(), "Street 90");
}

TEST_F(TestPgBankRepo, TestDeleteBank)
{
    PgBankRepository rep = PgBankRepository(*connectParams);

    rep.deleteEl(8);

    EXPECT_EQ(rep.getAllBanks().size(), 7);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}