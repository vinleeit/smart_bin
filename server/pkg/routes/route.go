package routes

import (
	"github.com/gofiber/fiber/v2"
	"github.com/gofiber/fiber/v2/middleware/logger"
	"github.com/xiaoming857/smart_bin/server/pkg/handlers"
)

func Init(app *fiber.App) {
	app.Use(logger.New())
	app.Get("", func(c *fiber.Ctx) error {
		return c.SendString("Welcome to Smart Bin server!")
	})

	api := app.Group("/api")
	public := api.Group("/public")
	public.Post("/login", handlers.Login)

	user := api.Group("/user")
	user.Get("/device/log", handlers.GetLog)

	device := api.Group("/device")
	device.Post("/refresh", handlers.DeviceRefresh)
	device.Post("/log", handlers.PostLog)
}
