FROM "mcr.microsoft.com/devcontainers/base:alpine-3.18"

RUN sed -i -e 's/v3\.18/latest-stable/g' /etc/apk/repositories;\
	apk add --no-cache -u gcc gdb
