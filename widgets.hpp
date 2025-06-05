#pragma once
#include "Gctx.hpp"
#include <memory>
#include <raygui.h>
#include <vector>

struct ButtonColors {
  Color border;
  Color base;
  Color text;
};

/**
 * A basic widget for a retained mode GUI library.
 */
class Widget {
public:
  bool hexpand, vexpand;

  Widget();
  virtual ~Widget() {}

  /** A rectangle with the retained position and size. */
  Rectangle getBox() const;

  /************/
  /* Position */
  /************/

  /** The retained x-coordinate. */
  float getX() const;
  /** The retained y-coordinate. */
  float getY() const;
  /** The retained position in x and y-coordinates. */
  Vector2 getPosition() const;

  /** Change the retained position. */
  void setPosition(Vector2 p);

  /********/
  /* Size */
  /********/

  /** The size on the x-axis (width) or y-axis (height). */
  float getSize(Axis a) const;
  /** The retained width. */
  float getWidth() const;
  /** The retained height. */
  float getHeight() const;

  /** Remeasure and save the width. */
  void updateWidth();
  /** Remeasure and save the height. */
  void updateHeight();
  /** Remeasure and save the size for the x-axis (width) or y-axis (height). */
  void updateSize(Axis a);

  /**********/
  /* Bounds */
  /**********/

  int getMinSize(Axis a) const;
  int getMinWidth() const;
  int getMinHeight() const;

  int getMaxSize(Axis a) const;
  int getMaxWidth() const;
  int getMaxHeight() const;

  bool expands(Axis a) const;

  void setMinWidth(int w);
  void setMinHeight(int h);
  void setMinSize(int w, int h);

  void setMaxWidth(int w);
  void setMaxHeight(int h);
  void setMaxSize(int w, int h);

  void setExternalBound(float bound, Axis a);
  void setExternalBounds(Vector2 bounds);

  /***********/
  /* Padding */
  /***********/

  int getPaddingEdge(Edge edge) const;
  Edges getPadding() const;

  /** The sum of the left and right padding. */
  int getTotalPaddingX() const;
  /** The sum of the top and bottom padding. */
  int getTotalPaddingY() const;

  /**
   * The sum of the padding on the x-axis (left and right padding)
   * or y-axis (top and bottom padding).
   */
  int getTotalPadding(Axis a) const;

  void setPadding(Edge edge, int value);
  void setPadding(int pad);
  void setPadding(int padY, int padX);
  void setPadding(int padTop, int padRight, int padBottom, int padLeft);

  virtual void repaint(Gctx g);

  /** Render the widget on the screen at its retained position. */
  void draw();

  /**
   * A utility function to render the widget on the screen at a
   * given position.
   *
   * This is meant for widgets to draw the widgets they inherited from.
   */
  virtual void draw(Vector2 p) = 0;

protected:
  /**
   * A utility function to translate the Gctx position and restrict its
   * bounds by the widget's padding.
   */
  void pad(Gctx &g) const;

  /** Recalculate and returns the width. */
  float measureWidth() const;
  /** Recalculate and return the height. */
  float measureHeight() const;
  /** Recalculate and return the size on the x-axis (width) or y-axis (height).
   */
  virtual float measureSize(Axis a) const = 0;

  Edges padding;
  Bounds internalBounds;
  Point externalBounds;

private:
  Rectangle box;
};

/**
 * A widget that displays text.
 */
class Label : public Widget {
public:
  bool wrapWords;
  Color color;

  Label(const Font &font, const char *text);
  Label(const Font &font, const char *text, float size);

  const char *getText() const;
  void setText(const char *text);

  /** Check whether the label is an empty string. */
  bool isEmpty() const;

  float measureText(Axis a) const;
  float measureTextWidth() const;
  float measureTextHeight() const;

  bool willWrap() const;

  void draw(Vector2 p) override;

protected:
  const Font &font;
  const char *text;
  float fontSize;
  int fontSpacing;

  float measureSize(Axis a) const override;

private:
  void init(const char *text);
};

class Icon : public Widget {
public:
  GuiIconName iconName;
  Color color;

  Icon(GuiIconName iconName);
  Icon(GuiIconName iconName, int iconSize);

  int getIconSize() const;
  void setIconSize(int size);

  /** Check whether there is no icon to be drawn */
  bool isEmpty() const;
  void draw(Vector2 p) override;

protected:
  int measureIconSize() const;
  float measureSize(Axis a) const override;

private:
  int iconSize;
};

class IconLabel : public Widget {
public:
  IconLabel(GuiIconName icon, const Font &font, const char *text);
  IconLabel(GuiIconName icon, const Font &font, const char *text, float size);

  void repaint(Gctx g) override;
  void draw(Vector2 p) override;

protected:
  float measureSize(Axis a) const override;

private:
  Icon icon;
  Label label;
  const static int spacing = 4;
};

/**
 * A widget that calls a function when pressed.
 */
class Button : public Widget {
public:
  Button(std::unique_ptr<Widget> &&child);
  Button(std::unique_ptr<Widget> &&child, void (*clickAction)(void));

  GuiState getState() const;

  void enable();
  void disable();
  void toggleEnabled();

  void setClickAction(void (*clickAction)(void));

  void repaint(Gctx g) override;
  void draw(Vector2 p) override;

protected:
  float measureSize(Axis a) const override;
  void updateState();

private:
  std::unique_ptr<Widget> child;
  GuiState state;
  ButtonColors colors;

  unsigned int borderWidth;
  void (*action)(void);

  void init();
};

/**
 * A widget that contains other widgets.
 * It handles their sizes and alignments.
 */
class Box : public Widget {
public:
  int spacing;
  Align halign;
  Align valign;
  Axis direction;

  Box();
  Box(int spacing, Axis direction, Align halign, Align valign);

  Align getAlign(Axis a) const;

  /**
   * Add a child widget and give its ownership to the Box widget.
   * @param w The child widget to add
   */
  void addChild(std::unique_ptr<Widget> &&w);

  /** Remove all children. */
  void clearChildren();

  void repaint(Gctx g) override;
  void draw(Vector2 p) override;

protected:
  float measureChildren(Axis a) const;
  float measureSize(Axis a) const override;

private:
  std::vector<std::unique_ptr<Widget>> children;
};
