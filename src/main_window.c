#include <pebble.h>


static Window *s_main_window;
static GBitmap *s_bitmap;
static BitmapLayer *s_bitmap_layer;

static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = GRect(0, 0, 30, 30);//layer_get_bounds(window_layer);
  
  // Load the resource
  s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_BACKGROUND_01);
  
  // Create the BitmapLayer
  s_bitmap_layer = bitmap_layer_create(bounds);
  
  bitmap_layer_set_bitmap(s_bitmap_layer, s_bitmap);
  
  // Set the correct compositing mode
  bitmap_layer_set_compositing_mode(s_bitmap_layer, GCompOpSet);
  
  //s_bitmap_layer = createAngelIslandZone();
  
  // Add to the Window
  layer_add_child(window_layer, bitmap_layer_get_layer(s_bitmap_layer));
}

static void main_window_unload(Window *window) {
  bitmap_layer_destroy(s_bitmap_layer);
  gbitmap_destroy(s_bitmap);
}

static void init() {
  // Create main Window
  s_main_window = window_create();
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload,
  });
  window_stack_push(s_main_window, true);
}

static void deinit() {
  // Destroy main Window
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}