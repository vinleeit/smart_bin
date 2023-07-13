package envs

import (
	"fmt"
	"os"
	"strconv"

	"github.com/joho/godotenv"
	"github.com/xiaoming857/smart_bin/server/pkg/utils"
)

var (
	SQLiteDBName        string
	ServerPort          string
	TokenHourLifespan   int
	ApiSecret           string
	DefaultUsername     string
	DefaultUserPassword string
)

func Init() error {
	if err := godotenv.Load(".env"); err != nil {
		return fmt.Errorf("error loading .env: %s", err)
	}

	if SQLiteDBName = os.Getenv("SQLITE_DB_NAME"); SQLiteDBName == "" {
		return fmt.Errorf("SQLITE_DB_NAME is not provided")
	}

	if ServerPort = os.Getenv("SERVER_PORT"); ServerPort == "" {
		return fmt.Errorf("SERVER_PORT is not provided")
	}

	if tokenHourLifespan, err := strconv.Atoi(os.Getenv("TOKEN_HOUR_LIFESPAN")); err != nil {
		return fmt.Errorf("TOKEN_HOUR_LIFESPAN is not provided")
	} else {
		TokenHourLifespan = tokenHourLifespan
	}

	if ApiSecret = os.Getenv("API_SECRET"); ApiSecret == "" {
		return fmt.Errorf("API_SECRET is not provided")
	}

	if DefaultUsername = os.Getenv("DEFAULT_USERNAME"); DefaultUsername == "" {
		return fmt.Errorf("DEFAULT_USERNAME is not provided")
	}

	if DefaultUserPassword = os.Getenv("DEFAULT_USER_PASSWORD"); DefaultUserPassword == "" {
		return fmt.Errorf("DEFAULT_USER_PASSWORD is not provided")
	} else {
		if pwd, err := utils.HashPassword(DefaultUserPassword); err != nil {
			return fmt.Errorf("unable to hash password: %s", err.Error())
		} else {
			DefaultUserPassword = pwd
		}
	}

	return nil
}
