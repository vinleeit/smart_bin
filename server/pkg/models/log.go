package models

import (
	"time"
)

type Log struct {
	DateTime time.Time `gorm:"primaryKey"`
	Height   float64
	Weight   float64
}
