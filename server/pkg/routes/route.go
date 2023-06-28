package routes

import (
	"github.com/gofiber/fiber/v2"
	"github.com/gofiber/fiber/v2/middleware/logger"
)

func Init(app *fiber.App) {
	app.Use(logger.New())
	app.Get("", func(c *fiber.Ctx) error {
		return c.SendString("Welcome to Smart Bin server!")
	})

	// api := app.Group("api")

}
