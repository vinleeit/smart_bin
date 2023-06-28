package models

type Device struct {
	ProductKey  string `gorm:"primaryKey"`
	Description string
	Logs        []Log
}
