#ifndef KATZE_APP_HPP
#define KATZE_APP_HPP

/**
 * Basic wrappers around SDL application functions.
 */
namespace katze {
/**
 * Set basic application metadata and initialize the SDL video and events
 * subsystems.
 * @return true on success, false on failure
 */
bool init(const char *name, const char *version, const char *appId);

/**
 * Check if the application should quit.
 */
bool shouldQuit();

/**
 * Clean everything up.
 */
void quit();
} // namespace katze

#endif // !KATZE_APP_HPP
