# simple-whatsapp-messager
A small messager using GREEN-API.

## Initial setup
Before anything else, you must have an account in the [green-api website](https://green-api.com/en?gad_source=1&gad_campaignid=22572945051&gclid=CjwKCAiAqKbMBhBmEiwAZ3UboM8-6FYENQVIngbR7S0nVpDeGKztL92t1II_mhpVfPEvSzakDBRh4BoCIIEQAvD_BwE) so you could create an instance for you. 

After that, you can clone this repo.

After clone the repository, open it on your IDE of choice.
In the root folder of your version of the project, create a `.env` file. This file **MUST** have the following fields:

- ID_INSTANCE
- TOKEN
- MESSAGE
- SENDER_NUMBER

All this information is being expected by the code to set things up properly, and you can get it from your instance page of the GREEN-API.

And install the dependencies from your favorite package manager:
- [CURL](https://curl.se/)
- [JSON](https://github.com/nlohmann/json) by nlohmann

## Building and running it
Since this project still doesn't have a proper build system, so we're doing it in the *like-the-cavemen* way.
- To build it:
```
g++ -std=c++17 main.cpp -o send_whatsapp \
    -I$(brew --prefix nlohmann-json)/include \
    -I$(brew --prefix curl)/include \
    -L$(brew --prefix curl)/lib -lcurl
```

- To run it:
```
./send_whatsapp 
```

When you execute this generated file, you should receive a message in the WhatsApp used to create the instance in the GREEN-API containg a message you defined in the `.env`'s `MESSAGE` field.
You can change this `send_whatsapp` name when building it, on the previous command, for whatever you like.
