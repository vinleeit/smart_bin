package handlers

import (
	"github.com/gofiber/fiber/v2"
	"github.com/xiaoming857/smart_bin/server/pkg/db"
	"github.com/xiaoming857/smart_bin/server/pkg/models"
	"github.com/xiaoming857/smart_bin/server/pkg/utils/tokens"
	"golang.org/x/crypto/bcrypt"
)

type loginData struct {
	Username string `json:"username"`
	Password string `json:"password"`
}

func Login(c *fiber.Ctx) error {
	var data loginData
	if err := c.BodyParser(&data); err != nil {
		return c.Status(fiber.StatusBadRequest).JSON(fiber.Error{Code: fiber.StatusBadRequest, Message: err.Error()})
	}

	var user models.User
	if err := db.SQLiteDB.First(&user, "username = ?", data.Username); err.Error != nil {
		return c.SendStatus(fiber.StatusBadRequest)
	}

	if err := (bcrypt.CompareHashAndPassword([]byte(user.Password), []byte(data.Password))); err != nil {
		return c.SendStatus(fiber.StatusBadRequest)
	}

	token, err := tokens.GenerateUserToken(&user)
	if err != nil {
		return c.Status(fiber.StatusBadRequest).JSON(fiber.Error{Code: fiber.ErrBadRequest.Code, Message: err.Error()})
	}

	return c.Status(fiber.StatusOK).JSON(fiber.Map{
		"token": token,
	})
}

func DeviceRefresh(c *fiber.Ctx) error {
	return c.SendStatus(200)
}
