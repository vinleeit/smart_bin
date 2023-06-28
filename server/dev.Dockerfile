# Source:
# - https://gophercoding.com/docker-setup-for-go-development/
# - https://bartlomiejmika.com/post/2022/how-to-containerize-a-golang-app-with-docker-for-development-and-production/
FROM golang:1.20

ENV GO111MODULE=on \
    CGO_ENABLED=1 \
    GOOS=linux \
    GOARCH=amd64

WORKDIR /smart_bin/server

# Create "db" folder for SQLite database.
RUN mkdir ./db

COPY go.mod .
COPY go.sum .
RUN go mod download

# Install compile daemon for hot reload.
RUN go get github.com/githubnemo/CompileDaemon
RUN go install github.com/githubnemo/CompileDaemon

COPY .env .
COPY cmd ./cmd/
COPY pkg ./pkg/

ENTRYPOINT CompileDaemon -polling -log-prefix=false -build="go build -o bin/smart_bin ./cmd/api/main.go" -command="./bin/smart_bin" -directory="./"