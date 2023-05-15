#ifndef APPLICATION_WIDGETS_H
#define APPLICATION_WIDGETS_H

#include <string>
#include <SDL2/SDL_ttf.h>
#include "EntitySystem.h"
#include "Window.h"
#include "Math.h"
#include "Color.h"

namespace UI {
    inline TTF_Font* defaultFont = TTF_OpenFont("Helvetica.ttf", 12);

    /**
     * Simple entity with coordinates and size
     */
    class Widget: public EntitySystem::GraphicsEntity {
    protected:
        Math::Vector2<float> position = {0, 0};
        Math::Vector2<float> size = {0, 0};

    public:
        explicit Widget(
                std::string name,
                const Math::Vector2<float>& position = {0.f, 0.f},
                const Math::Vector2<float>& size = {1.f, 1.f}
                );

        [[nodiscard]] const Math::Vector2<float> &getPosition() const;
        void setPosition(const Math::Vector2<float> &position);

        [[nodiscard]] const Math::Vector2<float> &getSize() const;
        void setSize(const Math::Vector2<float> &size);
    };

    class Label: public Widget {
    private:
        Color foreground = Color::White();
        std::string text;

        TTF_Font* font = defaultFont;
        SDL_Surface* surface;

    public:
        Label(
                const std::string &name,
                const Math::Vector2<float>& position,
                std::string text
                );

        void update(double deltaTime) override;

        void render(Graphics::Window &window) override;
    };

    class Button: public Widget {
    private:
        Color background = Color::White(),
              foreground = Color::Black(),
              border = Color::Cyan();
        float borderWidth = 1;
        std::string text;

    public:
        explicit Button(
                std::string name,
                const Math::Vector2<float>& position = {0.f, 0.f},
                const Math::Vector2<float>& size = {1.f, 1.f}
                );

        Button(
                const std::string &name,
                const Math::Vector2<float> &position,
                const Math::Vector2<float> &size,
                const Color &background,
                const Color &foreground,
                std::string text
                );

        Button(
                const std::string &name,
                const Math::Vector2<float> &position,
                const Math::Vector2<float> &size,
                const Color &background,
                const Color &foreground,
                const Color &border,
                float borderWidth,
                std::string text
                );

        void update(double deltaTime) override;
        void render(Graphics::Window& window) override;

        [[nodiscard]] const Color &getBackground() const;
        void setBackground(const Color &background);

        [[nodiscard]] const Color &getForeground() const;
        void setForeground(const Color &foreground);

        [[nodiscard]] const std::string &getText() const;
        void setText(const std::string &text);

        [[nodiscard]] const Color &getBorder() const;
        void setBorder(const Color &border);

        [[nodiscard]] float getBorderWidth() const;
        void setBorderWidth(float borderWidth);
    };
}

#endif //APPLICATION_WIDGETS_H
