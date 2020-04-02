# Build on image
FROM node

# Use /usr/src/app as the working directory
WORKDIR /usr/src/app

# Copy package.json & package-lock.json
# into container at /usr/src/app
COPY package*.json ./

# Run npm install inside the container
#RUN npm install
RUN npm ci --only=production

# Copy the rest of the source code
# from the host to the container
COPY . .

# The job of this contianer:
EXPOSE 8080
CMD [ "node", "app.js", "8080" ]