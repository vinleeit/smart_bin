package envs

import (
	"fmt"
	"os"

	"github.com/joho/godotenv"
)

var (
	SQLiteDBName string
	ServerPort   string
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

	return nil
}
