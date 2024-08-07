# Shohih

A multiplayer graphical chess game written in C++ with support for both Offline and Online modes.

## How to build

Clone the repository and third-party libraries.
```sh
git clone --recurse-submodules https://github.com/vaezim/Shohih.git
cd Shohih/
```

### Build the main program only (excluding tests)
```sh
./build.sh
cd ./output/exe
./shohih_main  # main executable
```

### Build the main program and tests

```sh
./build.sh --test
cd ./output/exe
./test         # test executable
./shohih_main  # main executable
```

### Build in debug mode
```sh
./build.sh --debug
```

## Playing in Online mode
- On the computer hosting the server:
```sh
cd ./output/exe
./shohih_server
```
- Players' computer (can be the same as the server's computer):
```sh
cd ./output/exe
./shohih_main
```

## Demo videos

### Offline mode

https://github.com/user-attachments/assets/62ad3c25-f878-4192-b87b-db71052376bc

## TODO
- [X] Implement and test `GetAvailableMoves()` function for all pieces
  - [X] Pawn (Including En-Passant)
    - [X] In case of En-Passant, remove the other pawn from the board
    - [ ] Pawn promotion
  - [X] Knight
  - [X] Bishop
  - [X] Rook
  - [X] Queen
  - [X] King
- [ ] Implement board class
  - [X] Add turns (black should not play in white's turn)
  - [ ] Support giving checks and checkmate
  - [ ] Pieces cannot take kings.
  - [ ] Add full support for FEN notation (Including player turn)
  - [X] Support castling
- [X] Implement Game manager
- [ ] GUI with Raylib
  - [X] Board texture
  - [X] Piece texture
  - [X] Show available moves when clicking on a piece
  - [X] Update piece texture position with piece objects
  - [ ] King square turning red if in check
  - [ ] If a piece can be taken, change square corner shapes instead of a circle
  - [ ] Add menu to select Online/Offline mode and enter server address
- [ ] Update demo video after fixing bugs
- [X] Implement online mode
  - [X] Add /exit http request
