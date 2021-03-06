#include "widget_value.hpp"

#include <math.h>

#define ACCELERATION_DELAY 50

WidgetValue::WidgetValue(LuaSaveParser *saveParser, std::string readEquation, std::string writeEquation, s64 minValue, s64 maxValue, u64 stepSize, u64 stepSizeMultiplier) :
 Widget(saveParser), m_readEquation(readEquation), m_writeEquation(writeEquation), m_minValue(minValue), m_maxValue(maxValue), m_stepSize(stepSize), m_stepSizeMultiplier(stepSizeMultiplier) {
  m_widgetDataType = INT;

  if (stepSize == 0)
    m_stepSize = floor((maxValue - minValue) / 500.0F);

  m_currValue = 0;

}

WidgetValue::~WidgetValue() {

}

void WidgetValue::draw(Gui *gui, u16 x, u16 y) {
  std::stringstream ss;
  ss << m_currValue;

  if (m_currValue == 0)
    m_currValue = Widget::m_saveParser->evaluateEquation(m_readEquation, Widget::getIntegerValue());

  gui->drawTextAligned(font20, x + WIDGET_WIDTH - 140, y + (WIDGET_HEIGHT / 2.0F), currTheme.selectedColor, ss.str().c_str(), ALIGNED_RIGHT);
}

void WidgetValue::onInput(u32 kdown) {
  m_currValue = Widget::m_saveParser->evaluateEquation(m_readEquation, Widget::getIntegerValue());

  u64 incrementValue = m_stepSizeMultiplier * m_stepSize;

  if (kdown & KEY_LEFT) {
    if (static_cast<s64>(m_currValue - incrementValue) > m_minValue) {
        Widget::setIntegerValue(Widget::m_saveParser->evaluateEquation(m_writeEquation, m_currValue) - incrementValue);
    }
    else Widget::setIntegerValue(Widget::m_saveParser->evaluateEquation(m_writeEquation, m_maxValue));
  }

  if (kdown & KEY_RIGHT) {
    if (static_cast<s64>(m_currValue + incrementValue) < m_maxValue) {
        Widget::setIntegerValue(Widget::m_saveParser->evaluateEquation(m_writeEquation, m_currValue) + incrementValue);
    }
    else Widget::setIntegerValue(Widget::m_saveParser->evaluateEquation(m_writeEquation, m_minValue));
  }
}

void WidgetValue::onTouch(touchPosition &touch) {

}
