package tokens

import (
	"time"

	"github.com/dgrijalva/jwt-go"
	"github.com/xiaoming857/smart_bin/server/pkg/envs"
	"github.com/xiaoming857/smart_bin/server/pkg/models"
)

func GenerateToken(lifespan int, sign string, mapClaims map[string]interface{}) (string, error) {
	claims := jwt.MapClaims{}
	for key, value := range mapClaims {
		if key != "exp" {
			claims[key] = value
		}
	}
	claims["exp"] = time.Now().Add(time.Hour * time.Duration(lifespan)).Unix()
	token := jwt.NewWithClaims(jwt.SigningMethodHS256, claims)
	return token.SignedString([]byte(sign))
}

func GenerateUserToken(user *models.User) (string, error) {
	return GenerateToken(
		envs.TokenHourLifespan,
		envs.ApiSecret,
		map[string]interface{}{
			"userID": user.Username,
		},
	)
}

// func GenerateParticipantToken(participant *models.Participant) (string, error) {
// 	return GenerateToken(
// 		24,
// 		"secret",
// 		map[string]interface{}{
// 			"participantID": participant.ID,
// 			"otp":           participant.OTP,
// 		},
// 	)
// }

// func ValidateToken(c *fiber.Ctx, isAdmin bool) error {
// 	var tokenConfig envs.TokenConfig
// 	if _, err := envs.LoadEnvData(&tokenConfig); err != nil {
// 		return err
// 	}
// 	if claims, err := ExtractClaims(ExtractToken(c)); err != nil {
// 		return err
// 	} else {
// 		objID, err := primitive.ObjectIDFromHex(ExtractUserID(&claims))
// 		if err != nil {
// 			return err
// 		}

// 		var user dtos.UserOutput
// 		db.UsersCollection.FindOne(context.TODO(), bson.M{"_id": objID})
// 		if user.IsAdmin {
// 			return nil
// 		} else if !user.IsAdmin && !isAdmin {
// 			return nil
// 		}
// 		return fmt.Errorf("unauthorized")
// 	}
// }

// func ExtractToken(c *fiber.Ctx) string {
// 	bearerToken := strings.Split(c.GetReqHeaders()["Authorization"], " ")

// 	if len(bearerToken) == 2 {
// 		return bearerToken[1]
// 	}
// 	return ""
// }

// func ExtractClaims(tokenString string) (jwt.MapClaims, error) {
// 	var tokenConfig envs.TokenConfig
// 	if _, err := envs.LoadEnvData(&tokenConfig); err != nil {
// 		return nil, err
// 	}
// 	token, err := jwt.Parse(tokenString, func(token *jwt.Token) (interface{}, error) {
// 		if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
// 			return nil, fmt.Errorf("unexpected signing method: %v", token.Header["alg"])
// 		}
// 		return []byte(tokenConfig.ApiSecret), nil
// 	})
// 	if err != nil {
// 		return nil, err
// 	}
// 	if claims, ok := token.Claims.(jwt.MapClaims); ok {
// 		return claims, nil
// 	} else {
// 		return nil, fmt.Errorf("invalid JWT token")
// 	}
// }

// func ExtractUserID(claims *jwt.MapClaims) string {
// 	return fmt.Sprintf("%.0f", (*claims)["userID"])
// }
