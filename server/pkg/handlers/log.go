package handlers

import "github.com/gofiber/fiber/v2"

func GetLog(c *fiber.Ctx) error {
	return c.SendStatus(200)
}

func PostLog(c *fiber.Ctx) error {
	return c.SendStatus(200)
}
