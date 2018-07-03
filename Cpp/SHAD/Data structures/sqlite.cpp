#include "gtest/gtest.h"
#include <sqlite3.h>

#include <memory>
#include <vector>
#include <algorithm>
#include <string>


namespace sqlite {

    class Transaction {
    public:
        Transaction(std::shared_ptr<sqlite3> db): db_(db), open(true) {};
        ~Transaction() {
            if (open) {
                sqlite3_exec(db_.get(), "ROLLBACK;", nullptr, nullptr, nullptr);
            }
        }
        void Commit() {
            char* errMsg;
            int rc = sqlite3_exec(db_.get(), "COMMIT;", nullptr, nullptr, &errMsg);
            open = false;
            if (rc != SQLITE_OK) {
                sqlite3_exec(db_.get(), "ROLLBACK;", nullptr, nullptr, nullptr);
                throw std::runtime_error(errMsg);
            }
        }
        void Abort() {
            sqlite3_exec(db_.get(), "ROLLBACK;", nullptr, nullptr, nullptr);
            open = false;
        }
    private:
        std::shared_ptr<sqlite3> db_;
        bool open;
    };

    class Row {
    public:
        Row(std::vector<sqlite3_value*> data) {
            data_.resize(data.size());
            std::copy(data.begin(), data.end(), data_.begin());
        }
        int GetColumnsCount() {
            return data_.size();
        }
        int GetInt(int i) {
            if (i < 0 || i >= data_.size()) {
                throw std::runtime_error("Wrong number of column!");
            }
            return sqlite3_value_int(data_[i]);
        }
        std::string GetString(int i) {
            if (i < 0 || i >= data_.size()) {
                throw std::runtime_error("Wrong number of column!");
            }
            return std::string((const char*)sqlite3_value_text(data_[i]));
        }
    private:
        std::vector<sqlite3_value*> data_;
    };

    class RowSet {
    public:
        void AddRow(const Row& row) {
            rows.push_back(row);
        }
        std::vector<Row>::iterator begin() {
            return rows.begin();
        }
        std::vector<Row>::iterator end() {
            return rows.end();
        }
        int Size() {
            return rows.size();
        }
        Row& GetRow(int i) {
            if (i < 0 || i >= rows.size()) {
                throw std::runtime_error("Wrong number of row!");
            }
            return rows[i];
        }
    private:
        std::vector<Row> rows;
    };

    class Statement {
    public:
        Statement(sqlite3_stmt* stmt) {
            stmt_.reset(stmt);
        }
        void Bind(int i, int param) {
            int rc = sqlite3_bind_int(stmt_.get(), i, param);
            if (rc != SQLITE_OK) {
                throw std::runtime_error(sqlite3_errstr(rc));
            }
        }
        void Bind(int i, const std::string& param) {
            int rc = sqlite3_bind_text(stmt_.get(), i, param.c_str(), strlen(param.c_str()), nullptr);
            if (rc != SQLITE_OK) {
                throw std::runtime_error(sqlite3_errstr(rc));
            }
        }
        std::unique_ptr<RowSet> Execute() {
            std::unique_ptr<RowSet> rowSet(new RowSet());
            int rc = sqlite3_step(stmt_.get());
            while (rc != SQLITE_DONE) {
                if (rc == SQLITE_ROW) {
                    int column_count = sqlite3_column_count(stmt_.get());
                    std::vector<sqlite3_value*> data(column_count);
                    for (int i = 0; i < column_count; i++) {
                        data[i] = sqlite3_value_dup(sqlite3_column_value(stmt_.get(), i));
                    }
                    Row row(data);
                    rowSet.get()->AddRow(row);
                    rc = sqlite3_step(stmt_.get());
                } else {
                    throw std::runtime_error(sqlite3_errstr(rc));
                }
            }
            sqlite3_reset(stmt_.get());
            return rowSet;
        }
    private:
        struct Deleter {
            void operator()(sqlite3_stmt* stmt) {
                sqlite3_finalize(stmt);
            }
        };
        std::unique_ptr<sqlite3_stmt, Deleter> stmt_;
    };

    class Database {
    public:
        Database(const std::string& filename) {
            sqlite3* db;
            if (sqlite3_open(filename.c_str(), &db) != SQLITE_OK) {
                sqlite3_close(db);
                throw std::runtime_error(sqlite3_errmsg(db));
            }
            db_ = std::shared_ptr<sqlite3>(db, Deleter());
        }
        void Execute(const std::string& query) {
            char* errMsg;
            if (sqlite3_exec(db_.get(), query.c_str(), nullptr, 0, &errMsg) != SQLITE_OK) {
                throw std::runtime_error(errMsg);
            }
        }
        std::unique_ptr<Statement> PrepareStatement(const std::string& query) {
            sqlite3_stmt* stmt;
            if (sqlite3_prepare_v2(db_.get(), query.c_str(), strlen(query.c_str()), &stmt, NULL) != SQLITE_OK) {
                throw std::runtime_error(sqlite3_errmsg(db_.get()));
            }
            return std::unique_ptr<Statement>(new Statement(stmt));
        }
        std::unique_ptr<Transaction> BeginTransaction() {
            this->Execute("BEGIN TRANSACTION;");
            return std::unique_ptr<Transaction>(new Transaction(db_));
        }
    private:
        struct Deleter {
            void operator()(sqlite3* db) {
                sqlite3_close(db);
            }
        };
        std::shared_ptr<sqlite3> db_;
    };

}

TEST(Database, Execute) {
    sqlite::Database db("movies.db");
    ASSERT_NO_THROW(db.Execute("CREATE TABLE MyMoviesDB(name VARCHAR(100) PRIMARY KEY,"
    "length TIME, year INTEGER, myRate INTEGER);"));
    ASSERT_THROW(db.Execute("DELETE FROM trololo WHERE azaz = \"ogoogo\";"), std::runtime_error);
}
TEST(Statement, PrepareAndExecute) {
    sqlite::Database db("movies.db");
    ASSERT_NO_THROW(db.Execute("INSERT INTO MyMoviesDB VALUES (\"Atonement\", \"2:00:00\", 2007, 8);"));
    db.Execute("INSERT INTO MyMoviesDB VALUES (\"Le Petit Prince\", \"1:48:00\", 2015, 10);");
    db.Execute("INSERT INTO MyMoviesDB VALUES (\"Pride and Prejudice\", \"2:09:00\", 2005, 10);");
    db.Execute("INSERT INTO MyMoviesDB VALUES (\"Blade Runner\", \"1:57:00\", 1982, 6);");
    db.Execute("INSERT INTO MyMoviesDB VALUES (\"Gravity\", \"1:30:00\", 2013, 7);");
    db.Execute("INSERT INTO MyMoviesDB VALUES (\"La La Land\", \"2:08:00\", 2016, 9);");
    db.Execute("INSERT INTO MyMoviesDB VALUES (\"Rise of the Guardians\", \"1:37:00\", 2012, 8);");
    db.Execute("INSERT INTO MyMoviesDB VALUES (\"Avatar\", \"2:58:00\", 2009, 9);");
    db.Execute("INSERT INTO MyMoviesDB VALUES (\"X-Men: Apocalypse\", \"2:23:00\", 2016, 6);");
    db.Execute("INSERT INTO MyMoviesDB VALUES (\"Код Каина\", \"1:42:00\", 2015, 6);");
    ASSERT_NO_THROW(db.PrepareStatement("SELECT * FROM MyMoviesDB WHERE year = 1982;"));
    auto stmt = db.PrepareStatement("SELECT * FROM MyMoviesDB WHERE year = 2015;");
    ASSERT_NO_THROW(stmt->Execute());
    auto result = stmt->Execute();
    ASSERT_EQ(result->Size(), 2);
    ASSERT_THROW(db.PrepareStatement("SELECT genre from MyMoviesDB;"), std::runtime_error);
}
TEST(Statement, BindAndExecuteManyTimes) {
    sqlite::Database db("movies.db");
    auto stmt = db.PrepareStatement("SELECT * FROM MyMoviesDB WHERE year = ?1;");
    for (int i = 1900; i < 2017; i++) {
        ASSERT_NO_THROW(stmt->Bind(1, i));
        ASSERT_NO_THROW(stmt->Execute());
        auto result = stmt->Execute();
        if (i == 2015) {
            ASSERT_EQ(result->Size(), 2);
        } else if (i == 2000) {
            ASSERT_EQ(result->Size(), 0);
        } else if (i == 2009) {
            ASSERT_NE(result->Size(), 2);
        }
    }
    ASSERT_THROW(stmt->Bind(666, 2018), std::runtime_error);
}
TEST(Statement, BindingByString) {
    sqlite::Database db("movies.db");
    auto stmt = db.PrepareStatement("SELECT * FROM MyMoviesDB WHERE name = @1;");
    ASSERT_NO_THROW(stmt->Bind(1, "Atonement"));
    ASSERT_NO_THROW(stmt->Execute());
    auto result = stmt->Execute();
    ASSERT_EQ(result->Size(), 1);
    ASSERT_NO_THROW(stmt->Bind(1, "Last Vegas"));
    ASSERT_NO_THROW(stmt->Execute());
    auto result_ = stmt->Execute();
    ASSERT_NE(result_->Size(), 1);
    ASSERT_THROW(stmt->Bind(666, "Movie 43"), std::runtime_error);
}
TEST(RowAndRowSet, GetData) {
    sqlite::Database db("movies.db");
    auto stmt = db.PrepareStatement("SELECT * FROM MyMoviesDB WHERE myRate = 10;");
    auto result = stmt->Execute();
    ASSERT_NO_THROW(result->GetRow(0).GetInt(2));
    ASSERT_EQ(result->GetRow(0).GetInt(2), 2015);
    ASSERT_EQ(result->GetRow(1).GetInt(2), 2005);
    ASSERT_NO_THROW(result->GetRow(0).GetString(0));
    ASSERT_EQ(result->GetRow(0).GetString(0), "Le Petit Prince");
    ASSERT_EQ(result->GetRow(1).GetString(0), "Pride and Prejudice");
    ASSERT_THROW(result->GetRow(100500), std::runtime_error);
    ASSERT_THROW(result->GetRow(1).GetString(-45), std::runtime_error);
}
TEST(RowAndRowSet, Other) {
    sqlite::Database db("movies.db");
    auto stmt = db.PrepareStatement("SELECT * FROM MyMoviesDB WHERE myRate = 6;");
    auto result = stmt->Execute();
    ASSERT_EQ(result->GetRow(1).GetColumnsCount(), 4);
    ASSERT_NO_THROW((*(result->begin())).GetString(0));
    ASSERT_EQ((*(result->begin())).GetString(0), "Blade Runner");
    for (auto it = result->begin(); it != result->end(); it++) {
        ASSERT_EQ((*it).GetInt(3), 6);
    }
}
TEST(Transaction, CommitAndAbort) {
    sqlite::Database db("movies.db");
    auto stmt = db.PrepareStatement("SELECT * FROM MyMoviesDB WHERE myRate = 10;");
    auto result = stmt->Execute();
    auto transaction = db.BeginTransaction();
    db.Execute("DELETE FROM MyMoviesDB WHERE year = 2015;");
    db.Execute("INSERT INTO MyMoviesDB VALUES (\"The Help\", \"2:26:00\", 2011, 10);");
    ASSERT_NO_THROW(transaction->Commit());
    auto newResult = stmt->Execute();
    ASSERT_NE(result->GetRow(1).GetString(0), newResult->GetRow(1).GetString(0));
    auto newTransaction = db.BeginTransaction();
    db.Execute("DELETE FROM MyMoviesDB WHERE year = 2011;");
    db.Execute("INSERT INTO MyMoviesDB VALUES (\"Whiplash\", \"1:47:00\", 2014, 10);");
    ASSERT_NO_THROW(transaction->Abort());
    auto newNewResult = stmt->Execute();
    ASSERT_EQ(newNewResult->GetRow(1).GetString(0), newResult->GetRow(1).GetString(0));
}
