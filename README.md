# Passmate — Local Password Manager (C++)

Passmate is a local, console-based password manager written in C++.
It is designed as a learning and systems-oriented project focused on C++ program structure, secure credential handling concepts, database interaction, and CLI workflows, rather than as a production-ready security tool.

The application allows users to create accounts, authenticate locally, and manage credential records stored in a MySQL database.

## Features

Console-based user interface (CLI)

Local user account creation and authentication

Password complexity validation

Salted SHA-256 password hashing (OpenSSL EVP)

MySQL-backed persistent storage

Modular C++ design with separation of concerns

## Password Handling

Passwords are never stored in plaintext.

During account creation:

A random salt is generated per user.

The plaintext password is concatenated with the salt.

The result is hashed using SHA-256 via OpenSSL’s EVP API.

Only the hash and salt are stored in the database.

## Database

Backend: MySQL

Environment: Running locally inside WSL

Access via MySQL Connector/C++

## Dependencies

C++17 or newer

MySQL Connector/C++

OpenSSL

MySQL Server (local)

Linux / WSL environment recommended

## Current Status


### Implemented:

User account creation

Password validation

Salted password hashing

Database-backed authentication

CLI navigation

### Planned:

Credential item encryption

Secure credential storage

Password reset functionality

Improved error handling

Configuration externalization
