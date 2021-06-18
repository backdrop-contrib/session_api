<?php

/**
 * @file
 * Session API admin functions.
 */

/**
 * Session API admin settings form.
 */
function session_api_settings_form() {
  $config = config('session_api.settings');
  // Find modules that implement hook_session_api_cleanup().
  $modules = module_implements('session_api_cleanup');

  // Bypass cookies enabled checking.
  $form['bypass_cookie_check'] = array(
    '#type' => 'checkbox',
    '#title' => t('Bypass checking if cookies are enabled'),
    '#description' => t("The <strong>Session API</strong> module assumes sessions are not available if there are no cookies set. Tick this to bypass this check (for example in an environment where a reverse proxy strips cookies for anonymous users)."),
    '#default_value' => $config->get('bypass_cookie_check'),
  );

  // Cookie expiry.
  $form['#config'] = 'session_api.settings';
  $form['cookie_expire_time'] = array(
    '#type' => 'textfield',
    '#title' => t('Cookie expire time'),
    '#description' => t(
      "An additional cookie is set in the end users' browser in order to better track sessions across logins and logouts. This is the amount of time, in seconds, that the cookie will stay valid in a user's browser. If set to 0, then the cookie will expire when the session ends (i.e, when the browser closes)."
    ),
    '#default_value' => $config->get('cookie_expire_time'),
  );

  // Cookie purging.
  $form['cookie_purge_time'] = array(
    '#type' => 'textfield',
    '#title' => t('Cookie purge time'),
    '#description' => t(
      "Cookies will be purged on cron run when they have become unused for the number of seconds set here. This is separate from the cookie expire time, so sessions won't be purged before the corresponding cookie expires."
    ),
    '#default_value' => $config->get('cookie_purge_time'),
  );

  // Cookie name.
  $description = t('This name will be used for the cookie key used by this module. Certain names for cookies might be incompatible with caching systems such as Varnish.');
  $description .= ' ' . t('<strong>Warning</strong>: Changing the cookie name will invalidate all current Session API sessions. A new cookie could also conflict with another module\'s cookie name.');
  $form['cookie_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Cookie name'),
    '#default_value' => session_api_get_cookie_name(),
    '#description' => $description,
  );

  return system_settings_form($form);
}
