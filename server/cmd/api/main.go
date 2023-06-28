package main

import (
	"fmt"
	"log"

	"github.com/gofiber/fiber/v2"
	"github.com/xiaoming857/smart_bin/server/pkg/db"
	"github.com/xiaoming857/smart_bin/server/pkg/envs"
	"github.com/xiaoming857/smart_bin/server/pkg/routes"
)

func main() {
	if err := envs.Init(); err != nil {
		log.Fatalln(err.Error())
	}

	if err := db.InitSQLite(); err != nil {
		log.Fatalln(err.Error())
	}

	app := fiber.New()
	routes.Init(app)
	app.Listen(fmt.Sprintf(":%s", envs.ServerPort))
}
