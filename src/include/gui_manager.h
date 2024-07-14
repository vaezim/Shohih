/**************************************************
 * @date    2024-07-01
 * @brief   Graphical UI manager
 **************************************************/

#pragma once
#ifndef GUI_MGR_H
#define GUI_MGR_H

#include <array>
#include "board.h"
#include "raylib.h"

namespace Shohih {

class GuiManager {
public:
    GuiManager(std::shared_ptr<Board> board);
    ~GuiManager() = default;

    void Run();

protected:

    //--------------------------------------------------
    // Utility functions
    //--------------------------------------------------
    static GuiWindowPos GetSquareCentrePosition(Square sq);
    static GuiWindowPos ConvertSquareToWindowPos(Square sq);
    static Square ConvertWindowPosToSquare(GuiWindowPos pos);

private:

    //--------------------------------------------------
    // Drawing functions
    //--------------------------------------------------
    void HandleMouseClicks();
    void DrawPieceTextures() const;
    void DrawMarkedSquareCircles() const;

    //--------------------------------------------------
    // Pointer to Shohih board handler
    //--------------------------------------------------
    std::shared_ptr<Board> m_board{ nullptr };

    //--------------------------------------------------
    // Board texture
    //--------------------------------------------------
    Texture2D m_boardTexture;

    //--------------------------------------------------
    // Piece images & textures
    //--------------------------------------------------
    std::array<Image,
        NUM_PIECE_TYPES * NUM_PIECE_COLORS> m_pieceImages{};
    std::array<Texture2D,
        NUM_PIECE_TYPES * NUM_PIECE_COLORS> m_pieceTextures{};

    Texture2D GetPieceTexture(PieceColor color, PieceType type) const;

    //--------------------------------------------------
    // Marked squares
    //--------------------------------------------------
    std::unordered_set<Square, SquareHash> m_markedSquares{};

    //--------------------------------------------------
    // Last square that was clicked
    //--------------------------------------------------
    Square m_lastClickedSquare{ NULL_SQUARE };

    //--------------------------------------------------
    // Image file paths
    //--------------------------------------------------
    static const char *g_boardImgPath;
    static const std::array<const char*,
        NUM_PIECE_TYPES * NUM_PIECE_COLORS> g_pieceImgPaths;
};

} // namespace Shohih

#endif // GUI_MGR_H