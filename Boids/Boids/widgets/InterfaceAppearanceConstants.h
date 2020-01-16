#pragma once

#include <string>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

const sf::Color COLOR_SLIDER_SIDE_BARS = sf::Color(150, 150, 150);
const sf::Color COLOR_SLIDER_SLIDING_BAR = sf::Color(150, 150, 150);
const sf::Color COLOR_SLIDER_CURSOR = sf::Color(150, 150, 150);
const sf::Color COLOR_OUTLINE_SLIDER_CURSOR = sf::Color::White;
const sf::Color COLOR_SLIDER_VALUE_TEXT = sf::Color::White;
const sf::Color COLOR_SLIDER_VALUE_TEXT_OUTLINE = sf::Color::Black;

// Epaisseur de la bordure extérieure du texte des sliders
const float FLT_SLIDER_TEXT_OUTLINE_THICKNESS = 0.f;

// Tailles de police
const unsigned int UINT_TEXT_CHARACTER_SIZE = 15;

// Sliders
const unsigned int UINT_SLIDER_DECIMALS_COUNT = 2;
const float FLT_SLIDERS_LENGTH = 340.f;
const float FLT_SLIDERS_SPACING = 110.f;
const float FLT_SLIDER_TEXT_OFFSET = -40.f;

// Dimensions des sliders
const sf::Vector2f V2F_SLIDER_BARS_SIZE = { 8, 20 };
const sf::Vector2f V2F_SLIDER_CURSOR_SIZE = { 8, 40 };
const float FLT_SLIDER_SLIDING_BAR_WIDTH = 2.f;
const float FLT_SLIDER_OUTLINE_THICKNESS = 1.f;

// Espace entre le texte d'information sur la valeur du slider et le slider lui-même (permet d'éviter que le texte soit collé au slider)
const float FLT_SLIDER_TEXT_INFO_PADDING = 20.f;

const float FLT_WIDGETS_RIGHT = 460.f;