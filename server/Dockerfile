FROM ubuntu
WORKDIR /app
COPY ./package*.json .
RUN apt-get update
RUN apt install curl -y
RUN apt-get install nodejs -y
RUN apt install npm -y
RUN npm i -g n -y
RUN n lts
RUN hash -r
RUN npm i -g node-gyp
RUN node-gyp configure
RUN node-gyp build
RUN apt-get install libusb-dev


COPY . .
EXPOSE 3010
# CMD ["npm","start"]