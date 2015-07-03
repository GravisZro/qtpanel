#ifndef TEXTGRAPHICSITEM_H
#define TEXTGRAPHICSITEM_H

#include <QtGui>

class TextGraphicsItem: public QGraphicsItem
{
public:
  TextGraphicsItem(QGraphicsItem* parent = nullptr);
  ~TextGraphicsItem(void);

  void setColor(const QColor& color);
  void setFont(const QFont& font);
  void setText(const QString& text);

  const QFont& font(void) const
  {
    return m_font;
  }

  QRectF boundingRect(void) const;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

private:
  QColor m_color;
  QFont m_font;
  QString m_text;
};

#endif
