#pragma once

#include <string>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

//
// Ce fichier contient les constantes relatives à l'apparence de l'interface de l'application
// C'est à dire :
// - La position, couleur et style des widgets de l'interface
// - La position et la couleur des autres éléments de l'interface: les panels, etc...
//

//
// Général
//

// Le nom du fichier de la police d'écriture de l'application (le fichier doit bien sûr être contenu dans le même dossier que l'éxécutable)
const std::string STR_APPLICATION_FONT_FILENAME = "BebasNeue-Regular.ttf";

// Taille de la fenêtre
const sf::Vector2f V2F_WINDOW_SIZE = { 1600,800 };

// Couleur de fond de la fenêtre en mode Création
const sf::Color COLOR_BACKGROUND_CREATION_MODE = { 200,200,200 };

// Couleur de fond de la fenêtre en mode Simulation
const sf::Color COLOR_BACKGROUND_SIMULATION_MODE = { 180,180,180 };

//
// Style général des widgets
//

// Couleurs
const sf::Color COLOR_BUTTON_FILL = { 231,250,70 };
const sf::Color COLOR_HOVERED_BUTTON_FILL = { 231,157,70 };
const sf::Color COLOR_CLICKED_BUTTON_FILL = { 129,9,27 };
const sf::Color COLOR_OUTLINE_BUTTON = sf::Color::Black;
const sf::Color COLOR_BUTTON_TEXT = sf::Color::Black;

const sf::Color COLOR_SLIDER_SIDE_BARS = sf::Color::Black;
const sf::Color COLOR_SLIDER_SLIDING_BAR = sf::Color(150, 150, 150);
const sf::Color COLOR_SLIDER_CURSOR = sf::Color(150, 150, 150);
const sf::Color COLOR_OUTLINE_SLIDER_CURSOR = sf::Color::White;
const sf::Color COLOR_SLIDER_VALUE_TEXT = sf::Color::White;
const sf::Color COLOR_SLIDER_VALUE_TEXT_OUTLINE = sf::Color::Black;

// Epaisseur de la bordure extérieure du texte des sliders
const float FLT_SLIDER_TEXT_OUTLINE_THICKNESS = 0.f;

// Tailles de police
const unsigned int UINT_BUTTON_TEXT_CHARACTER_SIZE = 50;
const unsigned int UINT_SLIDER_TEXT_CHARACTER_SIZE = 15;

// Dimensions des sliders
const sf::Vector2f V2F_SLIDER_BARS_SIZE = { 8, 20 };
const sf::Vector2f V2F_SLIDER_CURSOR_SIZE = { 8, 40 };
const float FLT_SLIDER_SLIDING_BAR_WIDTH = 2.f;
const float FLT_SLIDER_OUTLINE_THICKNESS = 1.f;

// Espace entre le texte du bouton et le coté du bouton (permet d'éviter que le texte soit collé au bord)
const float FLT_BUTTON_SIDES_PADDING = 10.f;

// Espace entre le texte d'information sur la valeur du slider et le slider lui-même (permet d'éviter que le texte soit collé au slider)
const float FLT_SLIDER_TEXT_INFO_PADDING = 10.f;

//
// Dimensions, et positionnement des panels de l'interface (dont la fenêtre de propriétés)
//

// Couleurs
const sf::Color COLOR_INTERFACE_TOP_PANEL = { 41,41,41,220 };
const sf::Color COLOR_LEFT_PANEL_TOP_GRADIENT = { 60,60,60,200 };
const sf::Color COLOR_LEFT_PANEL_BOTTOM_GRADIENT = { 100,100,100,150 };
const sf::Color COLOR_PROPERTY_TAB_TOP_GRADIENT = { 60,60,60,200 };
const sf::Color COLOR_PROPERTY_TAB_BOTTOM_GRADIENT = { 100,100,100,150 };

// Tailles des panels (voir plus loin pour la taille de la fenêtre de propriétés)
const sf::Vector2f V2F_TOP_PANEL_SIZE = { V2F_WINDOW_SIZE.x, 100 };
const sf::Vector2f V2F_LEFT_PANEL_SIZE = { 245,280 };
// Seule la largeur de la fenêtre de propriétés est unique (voir plus loin pour la hauteur)
const float FLT_PROPERTY_TAB_WIDTH = 500.f;

// Positions des panels
const sf::Vector2f V2F_TOP_PANEL_POSITION = { 0,0 };
const sf::Vector2f V2F_LEFT_PANEL_POSITION = { 0,V2F_TOP_PANEL_SIZE.y };
const sf::Vector2f V2F_PROPERTY_TAB_POSITION = { V2F_WINDOW_SIZE.x - FLT_PROPERTY_TAB_WIDTH,V2F_TOP_PANEL_SIZE.y };

// Hauteur du panel de la fenêtre de propriété en fonction du type d'élément éditable séléctionné
const float FLT_RIGIDBODY_PROPERTY_TAB_HEIGHT = 240.f;
const float FLT_WALL_PROPERTY_TAB_HEIGHT = 150.f;
const float FLT_EXPLOSIVE_PROPERTY_TAB_HEIGHT = 150.f;

//
// Widgets de la fenêtre propriétés
//

// Positions (relatives à la position de la fenêtre de propriétés)
const sf::Vector2f V2F_PROPERTY_TAB_NAME_POSITION = { 10,10 };
const float FLT_SLIDER_DISTANCE_FROM_LEFT_SIDE = 270.f;

// Couleurs
const sf::Color COLOR_PROPERTY_TAB_TEXT = sf::Color::Black;

// Dimensions des sliders
const float FLT_PROPERTY_TAB_SLIDER_LENGTH = 150.f;

// Constantes relatives aux valeur maximales/minimales des propriétés des différents éléments éditables
const float FLT_RIGIDBODY_SIZE_MINIMUM = 0.1f;
const float FLT_RIGIDBODY_SIZE_MAXIMUM = 7.f;

const float FLT_RIGIDBODY_DENSITY_MINIMUM = 10.f;
const float FLT_RIGIDBODY_DENSITY_MAXIMUM = 5000.f;

const float FLT_WALL_SIZE_PROPERTY_MINIMUM = 0.1f;
const float FLT_WALL_SIZE_PROPERTY_MAXIMUM = 20.f;

const float FLT_EXPLOSIVE_ENERGY_MINIMUM = 0.1f;
const float FLT_EXPLOSIVE_ENERGY_MAXIMUM = 1000.f;

const float FLT_PROPERTY_EXPLOSIVE_TIMER_MINIMUM = 0.1f;
const float FLT_PROPERTY_EXPLOSIVE_TIMER_MAXIMUM = 8.f;

// Taille de police du texte de la fenêtre de propriétés
const unsigned int FLT_PROPERTY_TAB_NAME_CHARACTER_SIZE = 24;

// Nombre de décimales pour les sliders des différentes propriétés
const size_t SIZET_SIZE_PROPERTY_DECIMALS_COUNT = 2;
const size_t SIZET_ENERGY_PROPERTY_DECIMALS_COUNT = 3;
const size_t SIZET_DENSITY_PROPERTY_DECIMALS_COUNT = 2;
const size_t SIZET_TIME_PROPERTY_DECIMALS_COUNT = 2;

//
// Positions des widgets de l'interface
//

// Widgets du panel du haut
const float FLT_TOP_PANEL_WIDGETS_DISTANCE_FROM_TOP = 25.f;
const float FLT_BTN_STARTSIM_XPOS = 20.f;
const float FLT_SLIDER_TIME_CONTROL_XPOS = 500.f;
const float FLT_SLIDER_GRAVITY_CONTROL_XPOS = 900.f;
const float FLT_TXT_FPS_XPOS = 1160.f;

// Widgets du panel de gauche
const float FLT_LEFT_PANEL_SPAWNBUTTONS_DISTANCE_FROM_LEFT = 20.f;
const float FLT_LEFT_PANEL_SAVEBUTTON_DISTANCE_FROM_LEFT = 10.f;