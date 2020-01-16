#pragma once

// Librairie standard
#include <iostream>

// SFML
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

// Autres fichiers
#include "InterfaceAppearanceConstants.h"
//#include "UtilityFunctionsNamespace.h"

class WidgetSlider : public sf::Drawable
{
public:

	//
	// Constructeur par défaut
	//
	WidgetSlider();

	~WidgetSlider();

	//
	// Constructeur complet
	//
	WidgetSlider(sf::Vector2f v2f_position, const sf::Font &font, float flt_minValue, float flt_maxValue, float flt_length, std::string str_unit, size_t decimalsCount);

	//
	// Permet d'initialiser le Slider après sa déclaration
	//
	void Init(sf::Vector2f v2f_position, const sf::Font &font, float flt_minValue, float flt_maxValue, float flt_length, std::string str_unit, size_t decimalsCount);

	//
	// Retourne "true" si la valeur du slider a été changée par l'utilisateur
	//
	bool ValueChanged(const sf::RenderWindow &window, const sf::Event &event);

	//
	// Retourne la valeur du slider
	//
	float GetValue();

	//
	// Définit la valeur du slider
	//
	// Si la valeur spécifiée dépasse la valeur maximale ou minimale, la valeur sera fixée à un des deux extremums
	//
	void SetValue(float flt_newValue);

	//
	// Retourne "true" si la coordonnée spécifiée (en principe celle de la souris) survole la hitbox du slider
	//
	bool IsHovered(sf::Vector2i v2i_mousePos) const;

private:

	//
	// Calcule la valeur du slider en fonction de la position du curseur
	//
	void CalculateSliderValue();

	//
	// Met à jour le texte du slider avec la valeur du slider
	//
	void UpdateValueInfoText();

	//
	// Surcharge de la méthode draw de sf::Drawable permettant de considérer l'objet comme étant affichable et donc de faciliter son affichage sur la fenêtre
	//
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	// Il y a 4 rectangles :
	// - 2 pour les barres de gauche et de droite
	// - un pour la barrre du slider, sur laquelle glisse le curseur
	// - un dernier pour le curseur
	sf::RectangleShape _rect_leftBar;
	sf::RectangleShape _rect_rightBar;
	sf::RectangleShape _rect_slidingBar;
	sf::RectangleShape _rect_cursor;

	// Texte contenant la valeur du slider
	sf::Text _txt_valueInfo;

	// Valeurs maximum/minimum
	float _flt_minValue;
	float _flt_maxValue;

	// Nombre de décimales après la virgule
	size_t _sizet_decimalsCount;

	// La valeur du slider
	float _flt_sliderValue;

	// L'unité avec laquelle la valeur est exprimée
	std::string _str_unit;

	// La hitbox du slider (la partie ou l'on peut cliquer), on la définit plus grande que le curseur même du slider, pour faciliter l'utilisation de ce dernier
	sf::FloatRect _fltrect_hitbox;
};

