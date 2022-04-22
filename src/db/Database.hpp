#ifndef LP_SERVER_OATPP_DATABASE_HPP
#define LP_SERVER_OATPP_DATABASE_HPP

#include "dto/DTOs.hpp"

#include <oatpp/orm/SchemaMigration.hpp>
#include <oatpp/orm/DbClient.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DbClient)

namespace network {
    class Database : public oatpp::orm::DbClient {
    public:

        explicit Database(const std::shared_ptr<oatpp::orm::Executor>& executor)
                : oatpp::orm::DbClient(executor) {
            oatpp::orm::SchemaMigration migration(executor);
            migration.addFile(1, DATABASE_MIGRATIONS"init.sql");
            migration.migrate();
            auto version = executor->getSchemaVersion();
            OATPP_LOGD("Database", "Migration - OK. Version=%lld", version);
        }

        QUERY(testSelect,
              "SELECT * FROM test WHERE testInt=:testInt;",
              PARAM(oatpp::Int32, testInt)
        )

        QUERY(testInsert,
              "INSERT INTO test "
              "(testString, testFloat, testInt, testBool) "
              "VALUES "
              "(:test.testString, :test.testFloat, :test.testInt, :test.testBool)"
              ";",
              PARAM(oatpp::Object<DtoTest>, test)
        )

        QUERY(testDelete,
              "DELETE FROM test WHERE testInt=:testInt;",
              PARAM(oatpp::Int32, testInt)
        )
    };
}

#include OATPP_CODEGEN_END(DbClient)

#endif //LP_SERVER_OATPP_DATABASE_HPP
