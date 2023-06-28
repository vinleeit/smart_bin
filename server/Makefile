run: docker-start

stop: docker-stop

clean: docker-clean

docker-start:
	docker compose -f dev.docker-compose.yml up

docker-stop:
	docker compose -f dev.docker-compose.yml down

docker-clean: docker-stop
	docker rmi smart_bin_server

docker-prune: docker-stop
	docker system prune -af
	docker volume prune -f
