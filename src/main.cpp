#include <Arduino.h>
#include "M5Dial.h"
#include "M5Unified.h"

#define BTN_TEST
#define TOUCH_TEST
#define ENCODER_TEST
void setup()
{
    auto cfg = M5.config();
    M5Dial.begin(cfg, true, false);
    M5Dial.Display.setTextColor(GREEN);
    M5Dial.Display.setTextDatum(middle_center);
    M5Dial.Display.setFont(&fonts::Orbitron_Light_24);
    M5Dial.Display.setTextSize(1);

    M5Dial.Display.drawString("Touch Test", M5Dial.Display.width() / 2,
                              M5Dial.Display.height() / 2);
}
#ifdef TOUCH_TEST
long oldPosition = -999;

int prev_x = -1;
int prev_y = -1;

static m5::touch_state_t prev_state;
#endif

void loop()
{
    M5Dial.update();
#ifdef ENCODER_TEST
    long newPosition = M5Dial.Encoder.read();
    if (newPosition != oldPosition)
    {
        M5Dial.Speaker.tone(8000, 20);
        M5Dial.Display.clear();
        oldPosition = newPosition;
        ESP_LOGI("Encoder","%d", newPosition);
        M5Dial.Display.drawString(String(newPosition),
                                  M5Dial.Display.width() / 2,
                                  M5Dial.Display.height() / 2);
        return;
    }
#endif
#ifdef TOUCH_TEST
    auto t = M5Dial.Touch.getDetail();
    if (prev_state != t.state)
    {
        prev_state = t.state;
        static constexpr const char *state_name[16] = {
            "none", "touch", "touch_end", "touch_begin",
            "___", "hold", "hold_end", "hold_begin",
            "___", "flick", "flick_end", "flick_begin",
            "___", "drag", "drag_end", "drag_begin"};
        ESP_LOGI("TOUCH ", "%s", state_name[t.state]);
        M5Dial.Display.fillRect(0, 0, M5Dial.Display.width(),
                                M5Dial.Display.height() / 2, BLACK);

        M5Dial.Display.drawString(state_name[t.state],
                                  M5Dial.Display.width() / 2,
                                  M5Dial.Display.height() / 2 - 30);
    }
    if (prev_x != t.x || prev_y != t.y)
    {
        M5Dial.Display.fillRect(0, M5Dial.Display.height() / 2,
                                M5Dial.Display.width(),
                                M5Dial.Display.height() / 2, BLACK);
        M5Dial.Display.drawString(
            "X:" + String(t.x) + " / " + "Y:" + String(t.y),
            M5Dial.Display.width() / 2, M5Dial.Display.height() / 2 + 30);
        ESP_LOGI("TOUCH", "(%d,%d)->(%d,%d)", prev_x, prev_y, t.x, t.y);
        prev_x = t.x;
        prev_y = t.y;
        M5Dial.Display.drawPixel(prev_x, prev_y);
    }
#endif
#ifdef BTN_TEST
    if (M5Dial.BtnA.wasPressed())
    {
        M5Dial.Speaker.tone(8000, 20);
        M5Dial.Display.clear();
        M5Dial.Display.drawString("Pressed", M5Dial.Display.width() / 2,
                                  M5Dial.Display.height() / 2);
    }
    if (M5Dial.BtnA.wasReleased())
    {
        M5Dial.Speaker.tone(8000, 20);
        M5Dial.Display.clear();
        M5Dial.Display.drawString("Released", M5Dial.Display.width() / 2,
                                  M5Dial.Display.height() / 2);
    }
#endif
}
