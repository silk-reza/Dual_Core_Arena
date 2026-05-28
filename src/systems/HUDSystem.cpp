//
// Created by reza on 5/28/26.
//

#include "../../include/systems/HUDSystem.hpp"

static std::string getStateText(GameState state)
{
    switch (state)
    {
        case GameState::Playing:  return "PLAYING";
        case GameState::Paused:   return "PAUSED";
        case GameState::GameOver: return "GAME OVER";
    }
    return "UNKNOWN";
}

static void drawPanel(
    sf::RenderWindow& window,
    sf::Vector2f position,
    sf::Vector2f size,
    sf::Color outlineColor,
    sf::Color fillColor = sf::Color(10, 15, 25, 210),
    float outlineThickness = 2.f
)
{
    sf::RectangleShape panel(size);
    panel.setPosition(position);
    panel.setFillColor(fillColor);
    panel.setOutlineThickness(outlineThickness);
    panel.setOutlineColor(outlineColor);
    window.draw(panel);
}

static void drawText(
    sf::RenderWindow& window,
    sf::Font& font,
    const std::string& content,
    unsigned int size,
    sf::Vector2f position,
    sf::Color color,
    bool bold = false
)
{
    sf::Text text(font);
    text.setString(content);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setPosition(position);
    if (bold)
        text.setStyle(sf::Text::Bold);
    window.draw(text);
}

// Dibuja una tecla con fondo oscuro y borde de color, con el label centrado
static void drawKeyCap(
    sf::RenderWindow& window,
    sf::Font& font,
    const std::string& label,
    sf::Vector2f position,
    sf::Vector2f size,
    sf::Color outlineColor,
    unsigned int fontSize = 13
)
{
    sf::RectangleShape key(size);
    key.setPosition(position);
    key.setFillColor(sf::Color(18, 22, 38, 235));
    key.setOutlineThickness(2.f);
    key.setOutlineColor(outlineColor);
    window.draw(key);

    sf::Text text(font);
    text.setString(label);
    text.setCharacterSize(fontSize);
    text.setFillColor(outlineColor);
    text.setStyle(sf::Text::Bold);

    sf::FloatRect b = text.getLocalBounds();
    text.setPosition({
        position.x + (size.x - b.size.x)  / 2.f - b.position.x,
        position.y + (size.y - b.size.y) / 2.f - b.position.y - 1.f
    });
    window.draw(text);
}

// ─────────────────────────────────────────────────────────────────────────────

void HUDSystem::renderTopHUD(
    sf::RenderWindow& window,
    sf::Font& font,
    EntityManager& entityManager,
    ScoreSystem& scoreSystem,
    AmmoSystem& ammoSystem,
    GameState gameState
)
{
    // ── Panel izquierdo: debug info ───────────────────────────────────────────
    drawPanel(window, {20.f, 22.f}, {365.f, 52.f}, sf::Color(0, 220, 100));

    drawText(
        window, font,
        "Enms: " + std::to_string(entityManager.getEnemies().size()) +
        "  |  Prjt: " + std::to_string(entityManager.getProjectiles().size()) +
        "  |  State: " + getStateText(gameState),
        15,
        {35.f, 38.f},
        sf::Color(80, 255, 150),
        true
    );

    // ── Scores centrados ──────────────────────────────────────────────────────
    drawText(
    window, font,
    "P1: " + std::to_string(scoreSystem.getPlayer1Score()),
    30,
    {400.f, 28.f},
    sf::Color(40,160,255),
    true
);

    drawText(
        window, font,
        "|",
        30,
        {500.f, 28.f},
        sf::Color(180,180,180),
        true
    );

    drawText(
        window, font,
        "P2: " + std::to_string(scoreSystem.getPlayer2Score()),
        30,
        {530.f, 28.f},
        sf::Color(255,50,70),
        true
    );

    // ── Ammo P1 ───────────────────────────────────────────────────────────────
    drawPanel(window, {650.f, 22.f}, {145.f, 52.f}, sf::Color(40,160,255));

    drawText(
        window, font,
        "P1 AMMO: " + std::to_string(ammoSystem.getPlayer1Ammo()),
        18,
        {665.f, 38.f},
        sf::Color(80, 190, 255),
        true
    );

    // ── Ammo P2 ───────────────────────────────────────────────────────────────
    drawPanel(window, {805.f, 22.f}, {155.f, 52.f}, sf::Color(255,50,70));

    drawText(
        window, font,
        "P2 AMMO: " + std::to_string(ammoSystem.getPlayer2Ammo()),
        18,
        {820.f, 38.f},
        sf::Color(255, 90, 100),
        true
    );
}

// ─────────────────────────────────────────────────────────────────────────────

void HUDSystem::renderControlsHUD(
    sf::RenderWindow& window,
    sf::Font& font
)
{
    constexpr float PX = 20.f;
    constexpr float PY = 600.f;
    constexpr float PW = 960.f;
    constexpr float PH = 90.f;

    // Panel exterior dorado
    drawPanel(window, {PX, PY}, {PW, PH}, sf::Color(210, 170, 30));

    // Divisores verticales
    auto vline = [&](float x)
    {
        sf::RectangleShape d({2.f, PH - 20.f});
        d.setPosition({x, PY + 10.f});
        d.setFillColor(sf::Color(210, 170, 30, 110));
        window.draw(d);
    };
    vline(PX + 320.f);
    vline(PX + 640.f);

    // ── Constantes de teclas ──────────────────────────────────────────────────
    constexpr float KW  = 30.f;   // ancho tecla estándar
    constexpr float KH  = 22.f;   // alto  tecla estándar
    constexpr float GAP = 3.f;    // separación entre teclas

    const sf::Color P1C(40, 160, 255);
    const sf::Color P2C(255, 50, 70);
    const sf::Color GKC(210, 170, 30);
    const sf::Color LBL(200, 200, 200);

    // ════════════════════════════════════════════════════════════════════════
    // COLUMNA 1 — PLAYER 1
    // ════════════════════════════════════════════════════════════════════════
    const float C1X = PX + 18.f;
    const float C1Y = PY + 12.f;

    drawText(window, font, "PLAYER 1", 15, {C1X + 60.f, C1Y - 6.f}, P1C, true);

    // Bloque WASD: W centrada arriba, A-S-D abajo
    float wx = C1X + KW + GAP;          // X de W (centrada sobre S)
    float wy = C1Y + 22.f;              // Y primera fila

    drawKeyCap(window, font, "W", {wx,                     wy},            {KW, KH}, P1C);
    drawKeyCap(window, font, "A", {C1X,                    wy + KH + GAP}, {KW, KH}, P1C);
    drawKeyCap(window, font, "S", {C1X + KW + GAP,         wy + KH + GAP}, {KW, KH}, P1C);
    drawKeyCap(window, font, "D", {C1X + (KW + GAP) * 2.f, wy + KH + GAP}, {KW, KH}, P1C);

    drawText(window, font, "MOVE", 11,
        {C1X + (KW + GAP) * 3.f + 4.f, wy + KH + GAP + 4.f}, LBL, true);

    // SPACE — fila inferior, columna derecha
    float spx = C1X + 160.f;
    drawKeyCap(window, font, "SPACE", {spx, wy + KH + GAP}, {74.f, KH}, P1C, 12);
    drawText(window, font, "SHOOT",  11, {spx + 82.f, wy + KH + GAP + 6.f}, LBL, true);

    // R — fila superior, columna derecha
    drawKeyCap(window, font, "R", {spx, wy}, {KW, KH}, P1C);
    drawText(window, font, "RELOAD", 11, {spx + KW + 6.f, wy + 6.f}, LBL, true);

    // ════════════════════════════════════════════════════════════════════════
    // COLUMNA 2 — PLAYER 2
    // ════════════════════════════════════════════════════════════════════════
    const float C2X = PX + 340.f;
    const float C2Y = C1Y;

    drawText(window, font, "PLAYER 2", 15, {C2X + 60.f, C2Y - 6.f}, P2C, true);

    float aky = C2Y + 22.f;

    // Flechas: ↑ centrada, ← ↓ → abajo
    drawKeyCap(window, font, "^",  {C2X + KW + GAP,          aky},            {KW, KH}, P2C);
    drawKeyCap(window, font, "<",  {C2X,                      aky + KH + GAP}, {KW, KH}, P2C);
    drawKeyCap(window, font, "v",  {C2X + KW + GAP,           aky + KH + GAP}, {KW, KH}, P2C);
    drawKeyCap(window, font, ">",  {C2X + (KW + GAP) * 2.f,  aky + KH + GAP}, {KW, KH}, P2C);

    drawText(window, font, "MOVE", 11,
        {C2X + (KW + GAP) * 3.f + 4.f, aky + KH + GAP + 4.f}, LBL, true);

    // CTRL y SHIFT apilados
    float csx = C2X + 160.f;
    drawKeyCap(window, font, "CTRL",  {csx, aky},            {56.f, KH}, P2C, 12);
    drawText(window, font, "SHOOT",   11, {csx + 64.f, aky + 6.f}, LBL, true);

    drawKeyCap(window, font, "SHIFT", {csx, aky + KH + GAP}, {56.f, KH}, P2C, 11);
    drawText(window, font, "RELOAD",  11, {csx + 64.f, aky + KH + GAP + 6.f}, LBL, true);

    // ════════════════════════════════════════════════════════════════════════
    // COLUMNA 3 — GLOBAL CONTROLS
    // ════════════════════════════════════════════════════════════════════════
    const float C3X = PX + 662.f;
    const float C3Y = C1Y - 2.f;

    struct GKey { const char* key; const char* label; float w; };
    const GKey gkeys[] = {
        {"F5",    "SAVE GAME",     38.f},
        {"F9",    "LOAD GAME",     38.f},
        {"P",     "PAUSE / RESUME",34.f},
        {"ENTER", "RESTART",       56.f},
    };

    float gy = C3Y;
    for (const auto& g : gkeys)
    {
        drawKeyCap(window, font, g.key, {C3X, gy}, {g.w, 17.f}, GKC, 10);
        drawText(window, font, g.label, 11, {C3X + g.w + 10.f, gy},
            sf::Color(230, 210, 150), true);
        gy += 19.f;
    }
}