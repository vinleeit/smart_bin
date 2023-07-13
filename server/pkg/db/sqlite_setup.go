package db

import (
	"fmt"
	"log"

	"github.com/xiaoming857/smart_bin/server/pkg/envs"
	"github.com/xiaoming857/smart_bin/server/pkg/models"
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

	if err := SQLiteDB.AutoMigrate(&models.User{}); err != nil {
		return fmt.Errorf("failed to automigrate user model: %s", err)
	}

	var isUserExist bool
	if SQLiteDB.Model(&models.User{}).Select("count(*) > 0").Where("username = ?", envs.DefaultUsername).Find(&isUserExist); !isUserExist {
		user := models.User{
			Username: envs.DefaultUsername,
			Password: envs.DefaultUserPassword,
		}
		if err := SQLiteDB.Create(&user).Error; err != nil {
			return fmt.Errorf("unable to create default user: %s", err.Error())
		}
		log.Println("default user created")
	}
	return nil
}
