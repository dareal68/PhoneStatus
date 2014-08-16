#include <pebble.h>

char buffer[] = "00:00";

Window *window;

TextLayer *text_layer;
InverterLayer *inv_layer;

void tick_handler(struct tm *tick_time, TimeUnits units_changed)
{
    //Update the display
    strftime(buffer, sizeof("00:00"), "%H:%M", tick_time);
    text_layer_set_text(text_layer, buffer);
}

void window_load(Window *window)
{
    //Window's creation elements
    
    
}

void window_unload(Window *window)
{
    //Window's destroy elements
}

void init()
{
    //Initialization
    window = window_create();
    window_set_window_handlers(window, (WindowHandlers) {
        .load = window_load,
        .unload = window_unload,
    });
    window_stack_push(window, true);
    
    tick_timer_service_subscribe(MINUTE_UNIT, (TickHandler) tick_handler);
    struct tm *t;
    time_t temp;
    temp = time(NULL);
    t = localtime(&temp);
    tick_handler(t, MINUTE_UNIT);
    
    text_layer = text_layer_create(GRect(0, 53, 132, 168));
    text_layer_set_background_color(text_layer, GColorClear);
    text_layer_set_text_color(text_layer, GColorBlack);
    text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
    text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
    
    layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));
    // text_layer_set_text(text_layer, "Anything you want, as long as it is in quotes!");   inutile pour afficher l'heure
    
    inv_layer = inverter_layer_create(GRect (0, 50, 144, 62));
    layer_add_child(window_get_root_layer(window), (Layer*) inv_layer);
}

void deinit()
{
    //De-initialization
    text_layer_destroy(text_layer);
    inverter_layer_destroy(inv_layer);
    window_destroy(window);
    tick_timer_service_unsubscribe();
}
int main(void) {
    init();
    app_event_loop();
    deinit();
}
