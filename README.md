# Shohih

CXX chess library

## Build

```sh
git clone --recurse-submodules https://github.com/vaezim/Shohih.git
cd Shohih
./build.sh
```

## Run Tests

```sh
./output/exe/test
```

## TODO
- [X] Implement and test `GetAvailableMoves()` function for all pieces.
  - [X] Pawn (Including En-Passant)
    - [X] In case of En-Passant, remove the other pawn from the board.
  - [X] Knight
  - [X] Bishop
  - [X] Rook
  - [X] Queen
  - [X] King
- [ ] Implement board class.
  - [ ] Support giving checks and checkmate.
  - [ ] Add full support for FEN notation (Including player turn).
- [ ] Implement Game manager.
- [ ] GUI with Raylib.
  - [ ] Board
  - [ ] Pieces
    - [ ] Show available moves when clicking on a piece
    - [ ] Drag and drop