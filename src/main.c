#include <pebble.h>

Window *my_window;
TextLayer *text_layer;
TextLayer *what_layer;

static char out_string[140];

static char who[][25] = {"jews", "masons", "reptiloids", "kittens", "neighbors", 
                      "government", "aliens", "Illuminati", "Great Old Ones", 
                      "police", "CIA", "KGB", "owls", "narwhals", "amoebas", "gays", "Iternet trolls", "secret services",
                      "Templars", "hipsters", "Great Ancestors", "spirits", "koalas", "sloths", "clergy", 
                      "necromophs", "xenomorphs", "shoggoths", "Santa's little helpers", "Reapers",
                      "grandmas", "immigrants", "terrorists", "jet fuel"
                          };

static char what[][100] = {"are watching me", "secretly rule the world", "are behind 9/11", "can melt steel beams", 
                       "are wating me for a dinner", "have psychic powers", "are not real", "are not afraid of me", 
                        "are trying to kill me", "are actually nice", "are not what they seem", "are here for fish",
                        "don't know the Truth", "are under my bed", "are using me", 
                        "are just a figment of my imagination", "control me", "control media", 
                        "are responsible for climate change", "are work of the devil", "have a hivemind", 
                        "making a better world", "also do drugs", "also writing apps for Pebble", 
                        "are gonna steal my job", "are better than me"
                              };

void deep_thought() {
  srand(time(NULL));
  int who_rnd = rand() % sizeof(who) / sizeof(who[0]);
  int what_rnd = rand() % sizeof(what) / sizeof(what[0]);
  snprintf(out_string, 140, "What if %s %s?", who[who_rnd], what[what_rnd]);
}

void clock_runner(struct tm *tick_time, TimeUnits units_changed) {
  time_t now = time(NULL);
  struct tm *current_time = localtime(&now);
  static char time[] = "XX:XX";
  
  strftime(time, sizeof(time), "%H:%M", current_time);
  text_layer_set_text(text_layer, time);

  deep_thought();
}

void handle_init(void) {  
  
  my_window = window_create();
  window_set_background_color(my_window, GColorBlack);
  
  text_layer = text_layer_create(GRect(12, 15, 120, 55));
  text_layer_set_background_color(text_layer, GColorBlack);
  text_layer_set_text_color(text_layer, GColorWhite);
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_MEDIUM_NUMBERS));
  
  what_layer = text_layer_create(GRect(12, 80, 120, 80));
  text_layer_set_background_color(what_layer, GColorBlack);
  text_layer_set_text_color(what_layer, GColorWhite);
  text_layer_set_text_alignment(what_layer, GTextAlignmentCenter);

  layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(text_layer));
  layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(what_layer));

  text_layer_set_text(what_layer, out_string);
  window_stack_push(my_window, true);
  
  tick_timer_service_subscribe(MINUTE_UNIT, &clock_runner);  
  
}


void handle_deinit(void) {
  text_layer_destroy(text_layer);
  text_layer_destroy(what_layer);
  window_destroy(my_window);
  tick_timer_service_unsubscribe();
}

int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}
