package db

import (
	"fmt"

	"github.com/xiaoming857/smart_bin/server/pkg/envs"
	"gorm.io/driver/sqlite"
	"gorm.io/gorm"
	"gorm.io/gorm/logger"
)

var (
	SQLiteDB *gorm.DB
)

func InitSQLite() error {
	if db, err := gorm.Open(sqlite.Open(fmt.Sprintf("./db/%s", envs.SQLiteDBName)), &gorm.Config{
		Logger: logger.Default.LogMode(logger.Silent),
	}); err != nil {
		return fmt.Errorf("failed to connect to database: %s", err.Error())
	} else {
		SQLiteDB = db
	}

	// SQLiteDB.AutoMigrate()
	return nil
}
