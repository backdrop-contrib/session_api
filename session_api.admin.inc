<?php

// $Id$

/**
 * @file
 * Session API admin functions.
 */

/**
 * Session API admin settings form.
 */
function session_api_settings_form() {
  // find modules that implement hook_session_api_cleanup()
  $modules = module_implements('session_api_cleanup');

  $form['maintenance'] = array(
    '#type' => 'fieldset',
    '#title' => t('Maintenance Tasks'),
    '#description' => t('The following modules have jobs that are run on cron to cleanup expired session information.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  foreach ($modules as $module) {
    // gather module-specific information about the cleanup process each on
    // implements.
    $info = module_invoke($module, 'session_api_cleanup', 'info');
    $form['maintenance']['session_api_run_cron_' . $module] = array(
      '#title' => $info['title'],
      '#description' => $info['description'],
      '#type' => 'checkbox',
      '#default_value' => variable_get('session_api_run_cron_' . $module, FALSE),
    );
  }

  return system_settings_form($form);
}
