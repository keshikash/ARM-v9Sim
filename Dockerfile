FROM alpine:latest

# Install make and other common build dependencies
RUN apk add --no-cache make build-base

WORKDIR /app

COPY . .

CMD ["make", "run"]
