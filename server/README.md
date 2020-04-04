# Chatter Server
The chat server

## Starting the server
### Locally
```bash
npm install --only=production
node app.js <port number>
```
Port number defaults to 8080.

### In a container
```bash
docker image build -t <image> .
docker container run --publish <host port>:8080 --detach --name <container name> <image>
```

## Stopping the server
### Locally
Kill the process with Ctrl+C

### In a container
```bash
docker stop <container name>
```

## Viewing the server logs
```bash
docker logs <container name>
```

## Deleting the container
```bash
docker container rm --force <container name>
```