# Shohih

CXX chess library

## Build

```sh
sh build.sh
```

## Run Tests

```sh
./output/exe/test
```

## TODO
- [ ] Implement and test `GetAvailableMoves()` function for all pieces.
  - [X] Pawn (Including En-Passant)
    - [ ] In case of En-Passant, remove the other pawn from the board.
  - [X] Knight
  - [X] Bishop
  - [X] Rook
  - [X] Queen
  - [X] King
- [ ] Implement board class.
  - [ ] Add full support for FEN notation (Including player turn).
- [ ] Implement Game manager.
- [ ] GUI with Raylib.
