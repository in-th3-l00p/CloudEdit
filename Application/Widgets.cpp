#include "Widgets.h"

#include <utility>

namespace UI {
    Widget::Widget(
            std::string name,
            const Math::Vector2<float> &position,
            const Math::Vector2<float> &size
    ):
        EntitySystem::GraphicsEntity(std::move(name)),
        position(position),
        size(size)
    {
        eventContainer.add(new EntitySystem::Event("onResize"));
    }

    const Math::Vector2<float> &Widget::getPosition() const {
        return position;
    }

    void Widget::setPosition(const Math::Vector2<float> &position) {
        this->position = position;
    }

    const Math::Vector2<float> &Widget::getSize() const {
        return size;
    }

    void Widget::setSize(const Math::Vector2<float> &size) {
        this->size = size;
    }


    Label::Label(
            const std::string &name,
            const Math::Vector2<float>& position,
            std::string text
            )
        : Widget(name),
          text(std::move(text)),
          surface(TTF_RenderText_Solid(
                  font,
                  this->text.c_str(),
                  foreground.toSDL_Color())
                  )
    {
        this->position = position;
    }

    void Label::render(Graphics::Window &window) {
        SDL_Texture* texture = SDL_CreateTextureFromSurface(window.renderer, surface);
        SDL_Rect rect = {
                static_cast<int>(position.x),
                static_cast<int>(position.y),
                100, 100
        };
        SDL_RenderCopy(window.renderer, texture, nullptr, &rect);
        SDL_DestroyTexture(texture);
    }

    void Label::update(double deltaTime) {

    }


    Button::Button(
            std::string name,
            const Math::Vector2<float> &position,
            const Math::Vector2<float> &size
    ) : Widget(std::move(name), position, size)
    {
        eventContainer.add(new EntitySystem::Event("onHover"));
        eventContainer.add(new EntitySystem::Event("onHoverEnd"));
        eventContainer.add(new EntitySystem::Event("onClick"));
        eventContainer.add(new EntitySystem::Event("onRelease"));
    }

    Button::Button(
            const std::string &name,
            const Math::Vector2<float> &position,
            const Math::Vector2<float> &size,
            const Color &background,
            const Color &foreground,
            const Color &border,
            float borderWidth,
            std::string text
    ) :
            Widget(name, position, size),
            background(background),
            foreground(foreground),
            border(border),
            borderWidth(borderWidth),
            text(std::move(text))
    {}

    void Button::render(Graphics::Window &window) {
        SDL_FRect rect = {
                position.x, position.y,
                size.x, size.y
        };

        SDL_SetRenderDrawColor(
                window.renderer,
                background.r,
                background.g,
                background.b,
                background.a
                );
        SDL_RenderFillRectF(window.renderer, &rect);

        SDL_FRect upperBorder {
            position.x, position.y,
            size.x, borderWidth
        };
        SDL_FRect rightBorder {
            position.x + size.x - borderWidth, position.y,
            borderWidth, size.y
        };
        SDL_FRect bottomBorder {
            position.x, position.y + size.y - borderWidth,
            size.x, borderWidth
        };
        SDL_FRect leftBorder {
            position.x, position.y,
            borderWidth, size.y
        };

        SDL_SetRenderDrawColor(window.renderer, border.r, border.g, border.b, border.a);
        SDL_RenderFillRectF(window.renderer, &upperBorder);
        SDL_RenderFillRectF(window.renderer, &rightBorder);
        SDL_RenderFillRectF(window.renderer, &bottomBorder);
        SDL_RenderFillRectF(window.renderer, &leftBorder);
    }

    void Button::update(double deltaTime) {

    }

    const Color &Button::getBackground() const {
        return background;
    }

    void Button::setBackground(const Color &background) {
        Button::background = background;
    }

    const Color &Button::getForeground() const {
        return foreground;
    }

    void Button::setForeground(const Color &foreground) {
        Button::foreground = foreground;
    }

    const std::string &Button::getText() const {
        return text;
    }

    void Button::setText(const std::string &text) {
        Button::text = text;
    }

    Button::Button(
            const std::string &name,
            const Math::Vector2<float> &position,
            const Math::Vector2<float> &size,
            const Color &background,
            const Color &foreground,
            std::string text
    ) : Widget(name, position, size),
        background(background),
        foreground(foreground),
        text(std::move(text))
    {}

    const Color &Button::getBorder() const {
        return border;
    }

    void Button::setBorder(const Color &border) {
        Button::border = border;
    }

    float Button::getBorderWidth() const {
        return borderWidth;
    }

    void Button::setBorderWidth(float borderWidth) {
        Button::borderWidth = borderWidth;
    }
} // UI
