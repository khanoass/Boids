#include "WidgetSlider.h"



WidgetSlider::WidgetSlider()
{

}

WidgetSlider::WidgetSlider(sf::Vector2f v2f_position, const sf::Font &font, float flt_minValue, float flt_maxValue, float flt_length, std::string str_unit, size_t decimalsCount)
{
	Init(v2f_position, font, flt_minValue, flt_maxValue, flt_length, str_unit, decimalsCount);
}

void WidgetSlider::Init(sf::Vector2f v2f_position, const sf::Font &font, float flt_minValue, float flt_maxValue, float flt_length, std::string str_unit, size_t decimalsCount)
{	
	// Le texte affichant la valeur
	_txt_valueInfo.setFont(font);
	_txt_valueInfo.setCharacterSize(UINT_TEXT_CHARACTER_SIZE);
	_txt_valueInfo.setString("TESTSTRING");
	_txt_valueInfo.setPosition(10 + flt_length + v2f_position.x + FLT_SLIDER_TEXT_INFO_PADDING, v2f_position.y);
	_txt_valueInfo.setFillColor(COLOR_SLIDER_VALUE_TEXT);
	_txt_valueInfo.setOutlineThickness(FLT_SLIDER_TEXT_OUTLINE_THICKNESS);
	_txt_valueInfo.setOutlineColor(COLOR_SLIDER_VALUE_TEXT_OUTLINE);

	// Les composants du slider; les différents rectangles
	_rect_leftBar.setFillColor(COLOR_SLIDER_SIDE_BARS);
	_rect_leftBar.setSize(V2F_SLIDER_BARS_SIZE);
	_rect_leftBar.setPosition(v2f_position);

	_rect_rightBar.setFillColor(COLOR_SLIDER_SIDE_BARS);
	_rect_rightBar.setSize(V2F_SLIDER_BARS_SIZE);
	_rect_rightBar.setPosition(v2f_position.x + V2F_SLIDER_BARS_SIZE.x + flt_length, v2f_position.y);

	_rect_slidingBar.setFillColor(COLOR_SLIDER_SLIDING_BAR);
	_rect_slidingBar.setSize({ flt_length, FLT_SLIDER_SLIDING_BAR_WIDTH });
	_rect_slidingBar.setPosition(v2f_position.x + V2F_SLIDER_BARS_SIZE.x, v2f_position.y + (V2F_SLIDER_BARS_SIZE.y - FLT_SLIDER_SLIDING_BAR_WIDTH) / 2);

	_rect_cursor.setFillColor(COLOR_SLIDER_CURSOR);
	_rect_cursor.setOutlineColor(COLOR_OUTLINE_SLIDER_CURSOR);
	_rect_cursor.setOutlineThickness(FLT_SLIDER_OUTLINE_THICKNESS);
	_rect_cursor.setSize(V2F_SLIDER_CURSOR_SIZE);
	_rect_cursor.setPosition(v2f_position.x + V2F_SLIDER_BARS_SIZE.x + (flt_length - V2F_SLIDER_CURSOR_SIZE.x) / 2, v2f_position.y + (V2F_SLIDER_BARS_SIZE.y - V2F_SLIDER_CURSOR_SIZE.y) / 2);

	// La hitbox du slider
	_fltrect_hitbox = { v2f_position.x, v2f_position.y, 2 * V2F_SLIDER_BARS_SIZE.x + flt_length, V2F_SLIDER_BARS_SIZE.y };

	// Valeur maximum/minimum
	_flt_minValue = flt_minValue;
	_flt_maxValue = flt_maxValue;

	// Nombres de décimales après la virgule
	_sizet_decimalsCount = decimalsCount;

	// Unité de l'indicateur
	_str_unit = str_unit;

	// Calcul de la valeur du slider initiale
	CalculateSliderValue();
}

WidgetSlider::~WidgetSlider()
{

}

bool WidgetSlider::ValueChanged(const sf::RenderWindow &window, const sf::Event &event)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	if (IsHovered(mousePos))
	{
		// Si la souris est cliquée et que le curseur survole la hitbox du slider
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{		
			if ((mousePos.x + V2F_SLIDER_CURSOR_SIZE.x / 2) < (_fltrect_hitbox.left + V2F_SLIDER_BARS_SIZE.x + V2F_SLIDER_CURSOR_SIZE.x)) // On touche la barre de gauche
			{
				// On positionne le curseur tout à gauche
				_rect_cursor.setPosition(_fltrect_hitbox.left + V2F_SLIDER_BARS_SIZE.x, _rect_cursor.getPosition().y);
			}	
			else if ((mousePos.x + V2F_SLIDER_CURSOR_SIZE.x / 2) > (_fltrect_hitbox.left + _fltrect_hitbox.width - V2F_SLIDER_BARS_SIZE.x)) // On touche la barre de droite
			{
				// On positionne le curseur tout à droite
				_rect_cursor.setPosition(_fltrect_hitbox.left + _rect_slidingBar.getSize().x + V2F_SLIDER_BARS_SIZE.x - V2F_SLIDER_CURSOR_SIZE.x, _rect_cursor.getPosition().y);
			}
			else
			{
				_rect_cursor.setPosition(sf::Mouse::getPosition(window).x - V2F_SLIDER_CURSOR_SIZE.x / 2, _rect_cursor.getPosition().y);
			}

			// Mise à jour de la valeur du slider
			CalculateSliderValue();

			return true;
		}
	}
	return false;
}

float WidgetSlider::GetValue()
{
	return _flt_sliderValue;
}

void WidgetSlider::SetValue(float flt_newValue)
{
	if (flt_newValue > _flt_maxValue) // Supérieur à la valeur maximale...
	{
		_rect_cursor.setPosition(_fltrect_hitbox.left + _rect_slidingBar.getSize().x + V2F_SLIDER_BARS_SIZE.x - V2F_SLIDER_CURSOR_SIZE.x, _rect_cursor.getPosition().y);
		flt_newValue = _flt_maxValue;
	}
	else if (flt_newValue < _flt_minValue) // Inférieur à la valeur minimale...
	{
		_rect_cursor.setPosition(_fltrect_hitbox.left + V2F_SLIDER_BARS_SIZE.x, _rect_cursor.getPosition().y);
		flt_newValue = _flt_minValue;
	}
	else // Entre la valeur maximale et minimale...
	{
		// Calcul de la longueur de slide
		// La longueur de "slide" représente la distance sur laquelle le curseur peut se déplacer
		float slidingLength = _rect_slidingBar.getSize().x - V2F_SLIDER_CURSOR_SIZE.x;

		// Ecart entre la valeur minimale et la valeur maximale
		float valueRange = std::abs(_flt_maxValue - _flt_minValue);

		// Du coup, pour connaître la nouvelle position du curseur, on calcule le pourcentage de complétion de la barre
		float completionRatio = flt_newValue / valueRange;

		// Et la nouvelle position du curseur (relative au début de la barre de "slide")
		float newXPosRelativeToSlidingBar = completionRatio * slidingLength;

		// Et la nouvelle vraie position
		_rect_cursor.setPosition(_rect_slidingBar.getPosition().x + newXPosRelativeToSlidingBar, _rect_cursor.getPosition().y);
	}

	_flt_sliderValue = flt_newValue;

	// Mise à jour du texte du slider
	UpdateValueInfoText();
}

bool WidgetSlider::IsHovered(sf::Vector2i v2i_mousePos) const
{
	// Si la coordonnée se trouve dans la hitbox du slider...
	if (_fltrect_hitbox.contains(sf::Vector2f(v2i_mousePos)))
	{
		return true;
	}
	else return false;
}

void WidgetSlider::CalculateSliderValue()
{
	// Ecart entre la valeur minimale et la valeur maximale
	float valueRange = std::abs(_flt_maxValue - _flt_minValue);

	// La valeur réelle n'est pas égale à la longueur du slider, puisque le centre du curseur ne va jamais toucher les bords. On retire donc la largeur du slider à cette valeur
	float realSlidingLength = _rect_slidingBar.getSize().x - V2F_SLIDER_CURSOR_SIZE.x;

	// La position locale du curseur sur le slider
	float localCursorPos = _rect_cursor.getPosition().x - _rect_slidingBar.getPosition().x;

	// Ratio de complétion du slider...
	// Ok, ça parait un peu compliqué mais c'est très simple :
	// C'est un ratio (de 0 à 1) représentant ou se trouve le curseur. Par exemple, quand le ratio est à 0.5, le curseur est pile au milieu.
	float sliderCompletionRatio = localCursorPos / realSlidingLength;

	// La valeur finale
	_flt_sliderValue = _flt_minValue + sliderCompletionRatio * valueRange;

	// On met à jour la valeur affichée sur le texte
	UpdateValueInfoText();
}

void WidgetSlider::UpdateValueInfoText()
{
	std::string textString = std::to_string(_flt_sliderValue);
	
	// On enlève un peu les virgules en trop
	for (int i = 0; i < (6 - _sizet_decimalsCount); ++i)
	{
		textString.pop_back();
	}

	// On applique le string au texte
	textString += _str_unit;
	_txt_valueInfo.setString(textString);
}

void WidgetSlider::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	// Dessin de tous les éléments du slider
	target.draw(_rect_leftBar);
	target.draw(_rect_rightBar);
	target.draw(_rect_slidingBar);
	target.draw(_rect_cursor);
	target.draw(_txt_valueInfo);
}
