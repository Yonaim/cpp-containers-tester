#ifndef ANSI_UI_H
#define ANSI_UI_H

namespace ui
{
    extern const char *C_RESET;
    extern const char *C_DIM;
    extern const char *C_BOLD;
    extern const char *C_RED;
    extern const char *C_GREEN;
    extern const char *C_YELLOW;
    extern const char *C_BLUE;
    extern const char *C_MAG;
    extern const char *C_CYAN;
    extern const char *C_GRAY;

    void hr(char ch);
    void title_bar();
    void hint_bar();
    void clear_screen();
} // namespace ui

#endif
