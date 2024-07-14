# Shohih

CXX chess library

## Build

```sh
git clone --recurse-submodules https://github.com/vaezim/Shohih.git
cd Shohih
./build.sh
```

## Run Shohih

```sh
cd ./output/exe
./shohih_main
```

## Run Tests

```sh
cd ./output/exe
./test
```

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
- [X] Implement board class
  - [ ] Add turns (black should not play in white's turn)
  - [ ] Support giving checks and checkmate
  - [ ] Pieces cannot take kings.
  - [ ] Add full support for FEN notation (Including player turn)
- [X] Implement Game manager
- [ ] GUI with Raylib
  - [X] Board texture
  - [X] Piece texture
  - [X] Show available moves when clicking on a piece
  - [X] Update piece texture position with piece objects
  - [ ] King square turning red if in check
  - [ ] If a piece can be taken, change square corner shapes instead of a circle